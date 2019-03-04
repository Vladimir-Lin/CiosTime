#include "stardate.hpp"

#include <Windows.h>

#define NANOBASE      ( 1000000000LL                             )
#define UBASE         ( 1000000LL                                )
#define SECSADAY      ( 86400LL                                  )
#define HALFDAY       ( 43200LL                                  )
#define NANOBASELD    static_cast<long double> ( NANOBASE        )
#define ZEROLD        static_cast<long double> ( 0.0000000000001 )

// Julian Day 0 = ( ( ( GMT_HOLO + 1930988LL ) * SECSADAY) + (12 * 3600) )
//              = 1420092166837276800 + 43200 = 1420092166837320000

// year % 8000 == 4000 -> not leap year
// year % 400  == 0    -> leap year
// year % 100  == 0    -> not leap year
// year % 4    == 0    -> leap year
//
// 8000 years = 2921939 days
// 4000 years = 1460969 days
//  400 years =  146097 days
//  100 years =   36524 days
//    4 years =    1461 days

#pragma pack(push,1)

#pragma pack(pop)

#ifndef DONT_USE_NAMESPACE
namespace STARDATE_NAMESPACE {
#endif

Estimator:: Estimator (void)
{
  Tick    . Now    (    )       ;
  Sizes   . clear  (    )       ;
  setRecent        ( 60 )       ;
  Counter . factor = NANOBASELD ;
  Update  . factor = NANOBASELD ;
  Goal             = 0          ;
  MaxSizes         = 256        ;
  GlobalRate       = 0          ;
  RecentRate       = 0          ;
  Completed        = 0          ;
  Duration         = 0          ;
  Arrival          = 0          ;
}

Estimator::~Estimator (void)
{
}

void Estimator::setGoal(int64_t goal)
{
  Goal = goal ;
}

void Estimator::setRecent(int64_t seconds)
{
  this -> Recent  = seconds  ;
  this -> Recent *= NANOBASE ;
}

std::pair<int64_t,int64_t> Estimator::append(int64_t size)
{
  int64_t Now = this -> Tick . Leaps ( )               ;
  std::pair<int64_t,int64_t> Z ( Now , size )          ;
  this -> Sizes . push_back ( Z )                      ;
  if ( this -> MaxSizes > 0 )                          {
    if ( this -> Sizes . size ( ) > this -> MaxSizes ) {
      this -> Sizes . pop_back ( )                     ;
    }                                                  ;
  }                                                    ;
  this -> Counter += size                              ;
  ++ ( this -> Update )                                ;
  return Z                                             ;
}

std::pair<int64_t,int64_t> Estimator::add(int64_t size)
{
  int64_t Now = this -> Tick . Leaps ( )               ;
  std::pair<int64_t,int64_t> Z ( Now , size )          ;
  this -> Sizes . push_back ( Z )                      ;
  if ( this -> MaxSizes > 0 )                          {
    if ( this -> Sizes . size ( ) > this -> MaxSizes ) {
      this -> Sizes . pop_back ( )                     ;
    }                                                  ;
  }                                                    ;
  this -> Counter += size                              ;
  ++ ( this -> Update )                                ;
  this -> update ( Now )                               ;
  return Z                                             ;
}

void Estimator::operator += (int64_t size)
{
  this -> append ( size ) ;
}

void Estimator::start (void)
{
  this -> StartTime  . Now   ( )           ;
  this -> FinishTime . Now   ( )           ;
  this -> Estimated  . Now   ( )           ;
  this -> Tick       . Now   ( )           ;
  this -> Sizes      . clear ( )           ;
  this -> Counter    . factor = NANOBASELD ;
  this -> Update     . factor = NANOBASELD ;
  this -> Completed           = 0          ;
}

void Estimator::update (void)
{
  this -> update ( Tick . Leaps ( ) ) ;
}

void Estimator::update(int64_t T)
{
  int64_t E                  = T - this -> Recent                           ;
  int64_t S                  = 0                                            ;
  int64_t W                  = 0                                            ;
  size_t  i                  = 0                                            ;
  bool    done               = false                                        ;
  ///////////////////////////////////////////////////////////////////////////
  this -> Duration           = T / NANOBASE                                 ;
  this -> Counter . duration = T                                            ;
  this -> Update  . duration = T                                            ;
  this -> GlobalRate         = static_cast<long double> ( this -> Counter ) ;
  ///////////////////////////////////////////////////////////////////////////
  if ( this -> Goal > 0 )                                                   {
    this -> Completed  = static_cast<long double> ( this -> Counter . events ) ;
    this -> Completed /= static_cast<long double> ( Goal )                  ;
  }                                                                         ;
  this -> FinishTime . Now ( )                                              ;
  ///////////////////////////////////////////////////////////////////////////
  // Remove Obsolete Data By 'Recent' Seconds
  ///////////////////////////////////////////////////////////////////////////
  done = ( this -> Sizes . size ( ) <= 0 )                                  ;
  while ( ! done )                                                          {
    done = ( i >= this -> Sizes . size ( ) )                                ;
    if ( ! done )                                                           {
      if ( E > this -> Sizes . begin ( ) -> first )                         {
        this -> Sizes . pop_back ( )                                        ;
      }                                                                     ;
    }                                                                       ;
  }                                                                         ;
  ///////////////////////////////////////////////////////////////////////////
  std::list< std::pair < int64_t , int64_t > >::iterator it                 ;
  i = 0                                                                     ;
  for ( it = this -> Sizes.begin () ; it != this -> Sizes.end () ; ++it )   {
    E  = it -> first                                                        ;
    W += it -> second                                                       ;
    if ( 0 == i ) S = E                                                     ;
    i++                                                                     ;
  }                                                                         ;
  E -= S                                                                    ;
  ///////////////////////////////////////////////////////////////////////////
  if ( E > 0 )                                                              {
    this -> RecentRate  = static_cast<long double> ( W        )             ;
    this -> RecentRate *= NANOBASELD                                        ;
    this -> RecentRate /= static_cast<long double> ( E        )             ;
  }                                                                         ;
  ///////////////////////////////////////////////////////////////////////////
  bool ignore = false                                                       ;
  if ( this -> Goal               <= 0 ) ignore = true                      ;
  if ( this -> Counter . events   <= 0 ) ignore = true                      ;
  if ( this -> Counter . duration <= 0 ) ignore = true                      ;
  ///////////////////////////////////////////////////////////////////////////
  if ( ignore    )                                                          {
    this -> Arrival    = T                                                  ;
    this -> Estimated  . Now ( )                                            ;
  } else                                                                    {
    int64_t Remains = Goal - this -> Counter . events                       ;
    if ( Remains >= 0 )                                                     {
      long double F = 0                                                     ;
      if ( ( W > 0 ) && ( E > 0 ) ) F = this -> RecentRate                  ;
                               else F = this -> GlobalRate                  ;
      if ( F > ZEROLD )                                                     {
        long double A     = static_cast<long double> ( Remains )            ;
        A                /= F                                               ;
        this -> Arrival   = int64_t ( A )                                   ;
        this -> Estimated = FinishTime                                      ;
        this -> Estimated . AddNano ( this -> Arrival )                     ;
      }                                                                     ;
    }                                                                       ;
  }                                                                         ;
}

#ifndef DONT_USE_NAMESPACE
}
#endif
