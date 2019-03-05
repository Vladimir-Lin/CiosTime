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

struct timezone       {
  long tz_minuteswest ; /* minutes W of Greenwich */
  int  tz_dsttime     ; /* type of dst correction */
}                     ;

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

StarDate:: StarDate (void)
         : stardate (0   )
{
}

StarDate:: StarDate (const StarDate & sd)
{
  this -> stardate = sd . stardate ;
}

StarDate:: StarDate (int64_t sd)
{
  this -> stardate = sd ;
}

StarDate::~StarDate (void)
{
}

int StarDate::type(void) const
{
  return 0 ;
}

bool StarDate::isValid(void) const
{
  return ( this -> stardate > 0 ) ;
}

void StarDate::adjustments(void)
{
}

int64_t StarDate::Standard(void) const
{
  return ( this -> stardate ) ;
}

int64_t StarDate::TimeShift(void) const
{
  return 0 ;
}

StarDate & StarDate::operator = (const StarDate & sd)
{
  return this -> assign( sd ) ;
}

StarDate & StarDate::operator = (int64_t sd)
{
  return this -> assign( sd ) ;
}

StarDate & StarDate::operator += (int64_t seconds)
{
  this -> stardate += seconds ;
  adjustments ( )             ;
  return (*this)              ;
}

StarDate & StarDate::operator -= (int64_t seconds)
{
  this -> stardate -= seconds ;
  adjustments ( )             ;
  return (*this)              ;
}

bool StarDate::isEqual(const StarDate & sd) const
{
  return ( sd . stardate == this -> stardate ) ;
}

bool StarDate::isEqual(int64_t sd) const
{
  return ( sd == this -> stardate ) ;
}

bool StarDate::isGreater(const StarDate & sd) const
{
  return ( this -> stardate > sd . stardate ) ;
}

bool StarDate::isGreater(int64_t sd) const
{
  return ( this -> stardate > sd ) ;
}

bool StarDate::isLess(const StarDate & sd) const
{
  return ( this -> stardate < sd . stardate ) ;
}

bool StarDate::isLess(int64_t sd) const
{
  return ( this -> stardate < sd ) ;
}

bool StarDate::operator == (const StarDate & sd) const
{
  return ( sd . stardate == this -> stardate ) ;
}

bool StarDate::operator == (int64_t sd) const
{
  return ( sd == this -> stardate ) ;
}

bool StarDate::operator > (const StarDate & sd) const
{
  return ( this -> stardate > sd . stardate ) ;
}

bool StarDate::operator > (int64_t sd) const
{
  return ( this -> stardate > sd ) ;
}

bool StarDate::operator < (const StarDate & sd) const
{
  return ( this -> stardate < sd . stardate ) ;
}

bool StarDate::operator < (int64_t sd) const
{
  return ( this -> stardate < sd ) ;
}

StarDate StarDate::operator + (int64_t seconds)
{
  StarDate sd                       ;
  sd . stardate  = this -> stardate ;
  sd . stardate += seconds          ;
  sd . adjustments ( )              ;
  return sd                         ;
}

StarDate StarDate::operator - (int64_t seconds)
{
  StarDate sd                       ;
  sd . stardate  = this -> stardate ;
  sd . stardate -= seconds          ;
  sd . adjustments ( )              ;
  return sd                         ;
}

StarDate & StarDate::Now(void)
{
  this -> setTime ( time ( nullptr ) ) ;
  return (*this)                       ;
}

StarDate & StarDate::assign(const StarDate & sd)
{
  this -> stardate = sd . stardate ;
  adjustments ( )                  ;
  return (*this)                   ;
}

StarDate & StarDate::assign(int64_t sd)
{
  this -> stardate = sd ;
  adjustments ( )       ;
  return (*this)        ;
}

StarDate & StarDate::setTime(time_t now)
{
  this -> stardate  = now   ;
  this -> stardate += TBASE ;
  adjustments ( )           ;
  return (*this)            ;
}

StarDate & StarDate::fromUStamp(int64_t uts)
{
  return this -> setTime ( uts / UBASE ) ;
}

time_t StarDate::toTimestamp(void) const
{
  return time_t ( this -> stardate - TBASE ) ;
}

int64_t StarDate::toDay(void) const
{
  return int64_t ( this -> stardate / SECSADAY ) ;
}

int64_t StarDate::toTime(void) const
{
  return int64_t ( this -> stardate % SECSADAY ) ;
}

int64_t StarDate::LilianNumber(void) const
{
  return ( this -> stardate - ( ( GMT_START + 1 ) * SECSADAY ) ) ;
}

StarDate & StarDate::setLilian(int64_t lilian)
{
  this -> stardate  = lilian                           ;
  this -> stardate += ( ( GMT_START + 1 ) * SECSADAY ) ;
  adjustments ( )                                      ;
  return (*this)                                       ;
}

long double StarDate::toMya(void) const
{
  int64_t     ds                                ;
  long double ma                                ;
  ds  = StarDate::current ( ) - this -> stardate ;
  ma  = (long double) ds                        ;
  ma /= SECSADAY                                ;
  ma /= 1461                                    ;
  ma *= 4                                       ;
  ma /= (long double) 1000000                   ;
  return ma                                     ;
}

long double StarDate::setMya(long double mya)
{
  /////////////////////////////////////////////
  int64_t     sd  = StarDate::current ( )      ;
  int64_t     nt  = int64_t ( sd % SECSADAY ) ;
  int64_t     day = int64_t ( sd / SECSADAY ) ;
  long double ma = mya                        ;
  /////////////////////////////////////////////
  ma *= (long double) 1000000                 ;
  ma *= 1461                                  ;
  ma /= 4                                     ;
  /////////////////////////////////////////////
  this -> stardate  = day                     ;
  this -> stardate -= int64_t ( ma )          ;
  this -> stardate *= SECSADAY                ;
  this -> stardate += nt                      ;
  /////////////////////////////////////////////
  adjustments ( )                             ;
  /////////////////////////////////////////////
  return mya                                  ;
}

StarDate & StarDate::setJulianDay(long double JD)
{
  int64_t ts = int64_t ( JD * SECSADAY ) ;
  this -> stardate  = GMT_JULIAN         ;
  this -> stardate += ts                 ;
  return (*this)                         ;
}

long double StarDate::JulianDay(void) const
{
  return (long double)( ((long double)(this -> stardate - GMT_JULIAN)) / SECSADAY ) ;
}

long double StarDate::RataDie(void) const
{
  return (long double) ( this -> JulianDay ( ) - ( (long double) 1721425 ) ) ;
}

long double StarDate::MJD(void) const
{
  return (long double) ( this -> JulianDay ( ) - ( (long double) 2400000.5 ) ) ;
}

StarDate & StarDate::Add(int64_t seconds)
{
  this -> stardate += seconds ;
  adjustments ( )             ;
  return (*this)              ;
}

StarDate & StarDate::Subtract(int64_t seconds)
{
  this -> stardate -= seconds ;
  adjustments ( )             ;
  return (*this)              ;
}

int64_t StarDate::toNow(void) const
{
  int64_t now = time ( nullptr ) ;
  now += TBASE                   ;
  now -= this -> stardate        ;
  return now                     ;
}

int64_t StarDate::secondsTo(const StarDate & sd) const
{
  return int64_t ( sd . stardate - this -> stardate ) ;
}

int64_t StarDate::secondsTo(int64_t sd) const
{
  return int64_t ( sd - this -> stardate ) ;
}

int64_t StarDate::daysTo(const StarDate & sd) const
{
  int64_t ds = this -> secondsTo ( sd ) ;
  return ( ds / SECSADAY )              ;
}

int64_t StarDate::daysTo(int64_t sd) const
{
  int64_t ds = this -> secondsTo ( sd ) ;
  return ( ds / SECSADAY )              ;
}

StarDate StarDate::ETA(int64_t index,int64_t total)
{
  StarDate SD                                         ;
  SD . stardate  = this -> stardate                   ;
  SD . stardate += this -> Estimate ( index , total ) ;
  SD . adjustments ( )                                ;
  return SD                                           ;
}

StarDate StarDate::ETA(int64_t index,int64_t minv,int64_t maxv)
{
  return this -> ETA ( index - minv , maxv - minv + 1 ) ;
}

int64_t StarDate::Estimate(int64_t index,int64_t total)
{
  if ( index <= 0     ) return 0                             ;
  if ( total <= 0     ) return 0                             ;
  if ( index >= total ) return 0                             ;
  ////////////////////////////////////////////////////////////
  int64_t tn = this -> toNow ( )                             ;
  if ( tn    <  0     ) return 0                             ;
  ////////////////////////////////////////////////////////////
  tn *= total                                                ;
  tn /= index                                                ;
  ////////////////////////////////////////////////////////////
  return tn                                                  ;
}

int64_t StarDate::Estimate(int64_t index,int64_t minv,int64_t maxv)
{
  if ( minv  >= maxv ) return 0                              ;
  if ( index <  minv ) return 0                              ;
  return this -> Estimate ( index - minv , maxv - minv + 1 ) ;
}

void StarDate::sleep(int64_t seconds)
{
  ::Sleep( DWORD ( seconds * 1000 ) ) ;
}

void StarDate::msleep(int64_t ms)
{
  ::Sleep( DWORD ( ms ) ) ;
}

void StarDate::usleep(int64_t us)
{
  if ( us < 0 ) return                    ;
  /////////////////////////////////////////
  int64_t ms = us / 1000                  ;
  int64_t rs = us % 1000                  ;
  /////////////////////////////////////////
  if ( ms > 0 ) ::Sleep  ( DWORD ( ms ) ) ;
  if ( rs > 0 )   uSleep (         us   ) ;
  /////////////////////////////////////////
}

int64_t StarDate::current(void)
{
  return int64_t ( int64_t ( time ( nullptr ) ) + TBASE ) ;
}

int64_t StarDate::useconds(void)
{
  struct timeval tv              ;
  int64_t        tt              ;
  gettimeofday ( &tv , nullptr ) ;
  tt = int64_t (  tv . tv_usec ) ;
  tt = tt % UBASE                ;
  return tt                      ;
}

int64_t StarDate::ustamp(void)
{
  struct timeval tv               ;
  int64_t        tt               ;
  int64_t        ts               ;
  tt = time     ( nullptr       ) ;
  gettimeofday  ( &tv , nullptr ) ;
  ts  = int64_t (  tv . tv_usec ) ;
  ts  = ts % UBASE                ;
  tt  = tt * UBASE                ;
  tt += ts                        ;
  return tt                       ;
}

int64_t StarDate::tzOffset(void)
{
  struct timeval  tv                    ;
  struct timezone tz                    ;
  int64_t         tt                    ;
  gettimeofday ( &tv , &tz            ) ;
  tt = int64_t (  tz . tz_minuteswest ) ;
  tt = tt * 60LL                        ;
  return tt                             ;
}

int64_t StarDate::RDTSC(void)
{
  return getRDTSC ( ) ;
}

int64_t StarDate::Clock(void)
{
  return HardwareClock ( ) ;
}

int64_t StarDate::Frequency(void)
{
  return HardwareFrequency ( ) ;
}

#ifndef DONT_USE_NAMESPACE
}
#endif
