#include "stardate.hpp"

#include <Windows.h>

#define EPOCHFILETIME ( 116444736000000000LL                     )
#define NANOBASE      ( 1000000000LL                             )
#define UBASE         ( 1000000LL                                )
#define SECSADAY      ( 86400LL                                  )
#define HALFDAY       ( 43200LL                                  )
#define GMT_HOLO      ( 16436250000000LL - 1                     )
#define GMT_1         ( 16436250000000LL + 3652423LL             )
#define GMT_1582      ( 16436250000000LL + 4229871LL             )
#define GMT_START     ( 16436250000000LL + 4230148LL             )
#define GMT_1583      ( 16436250000000LL + 4230226LL             )
#define GMT_1900      ( 16436250000000LL + 4346008LL             )
#define GMT_1970      ( 16436250000000LL + 4371575LL             )
#define GMT_1601      ( 16436250000000LL + 3652423LL +  584378LL )
#define GMT_4001      ( 16436250000000LL + 3652423LL + 1460960LL )
#define GMT_EPOCH     ( 16436250000000LL + 4371575LL             )
#define GMT_JULIAN    ( 1420092166837320000LL                    )
#define STB           ( 1420092388843632000LL                    )
#define TBASE         ( 1420092377704080000LL                    )

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

extern void    uSleep            (int64_t usec) ;
extern int     gettimeofday      (struct timeval * tv, struct timezone * tz) ;
extern int     strcasecmp_local  (const char *s1,const char *s2) ;
extern int64_t getRDTSC          (void) ;
extern int64_t HardwareClock     (void) ;
extern int64_t HardwareFrequency (void) ;

#define strcasecmp strcasecmp_local

StarTime:: StarTime (void)
         : StarDate (    )
         , startime (0   )
{
}

StarTime:: StarTime (const StarTime & st)
         : StarDate (                   )
{
  this -> stardate = st . stardate ;
  this -> startime = st . startime ;
}

StarTime::~StarTime(void)
{
}

int StarTime::type(void) const
{
  return 1 ;
}

bool StarTime::isValid(void) const
{
  if ( this -> stardate > 0 ) return true  ;
  if ( this -> stardate < 0 ) return false ;
  return ( this -> startime > 0 )          ;
}

bool StarTime::isEqual(const StarTime & st) const
{
  if ( st . stardate != this -> stardate ) return false ;
  return ( st . startime == this -> startime )          ;
}

bool StarTime::isGreater(const StarTime & st) const
{
  if ( this -> stardate > st . stardate ) return true  ;
  if ( this -> stardate < st . stardate ) return false ;
  return ( this -> startime > st . startime )          ;
}

bool StarTime::isLess(const StarTime & st) const
{
  if ( this -> stardate < st . stardate ) return true  ;
  if ( this -> stardate > st . stardate ) return false ;
  return ( this -> startime < st . startime )          ;
}

StarTime & StarTime::operator = (const StarTime & st)
{
  return this -> assign ( st ) ;
}

bool StarTime::operator == (const StarTime & sd) const
{
  return this -> isEqual ( sd ) ;
}

bool StarTime::operator > (const StarTime & sd) const
{
  return this -> isGreater ( sd ) ;
}

bool StarTime::operator < (const StarTime & sd) const
{
  return this -> isLess ( sd ) ;
}

int64_t StarTime::operator - (const StarTime & st) const
{
  return this -> nanosecondsTo ( st ) ;
}

StarTime & StarTime::assign(const StarTime & st)
{
  this -> stardate = st . stardate ;
  this -> startime = st . startime ;
  adjustments ( )                  ;
  return (*this)                   ;
}

StarTime & StarTime::Now(void)
{
  this -> stardate  = Stellar::current   ( ) ;
  int64_t clock     = Stellar::Clock     ( ) ;
  int64_t frequency = Stellar::Frequency ( ) ;
  this -> startime  = 0                      ;
  if ( frequency > 0 )                       {
    clock %= frequency                       ;
    clock *= NANOBASE                        ;
    clock /= frequency                       ;
    this  -> startime = clock                ;
  }                                          ;
  adjustments ( )                            ;
  return (*this)                             ;
}

int64_t StarTime::nanosecondsTo(const StarTime & st) const
{
  int64_t ts                             ;
  ts  = st . stardate - this -> stardate ;
  ts *= NANOBASE                         ;
  ts += st    . startime                 ;
  ts -= this -> startime                 ;
  return ts                              ;
}

int64_t StarTime::Leaps(void) const
{
  StarTime st                         ;
  st . Now ( )                        ;
  return this -> nanosecondsTo ( st ) ;
}

StarTime & StarTime::AddNano(int64_t nanoseconds)
{
  int64_t tt = nanoseconds + this -> startime ;
  if ( tt >= 0 )                              {
    this -> startime  = tt % NANOBASE         ;
    this -> stardate += tt / NANOBASE         ;
  } else                                      {
    int64_t tk = -tt                          ;
    tk   /= NANOBASE                          ;
    tk   += 1                                 ;
    this -> stardate -= tk                    ;
    tk   *= NANOBASE                          ;
    tt   += tk                                ;
    this -> startime  = tt % NANOBASE         ;
    this -> stardate += tt / NANOBASE         ;
  }                                           ;
  adjustments ( )                             ;
  return (*this)                              ;
}

StarTime & StarTime::SubtractNano(int64_t nanoseconds)
{
  return this -> AddNano ( - nanoseconds ) ;
}

#ifndef DONT_USE_NAMESPACE
}
#endif
