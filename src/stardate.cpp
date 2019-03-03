#include "stardate.hpp"

#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define EPOCHFILETIME ( 116444736000000000LL                     )
#define SECSADAY      ( 86400LL                                  )
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

#pragma pack(push,1)


#pragma pack(pop)

#ifndef DONT_USE_NAMESPACE
namespace STARDATE_NAMESPACE {
#endif

StarDate:: StarDate (void)
         : stardate (0   )
{
}

StarDate:: StarDate (const StarDate & sd)
{
  this -> stardate = sd.stardate ;
}

StarDate:: StarDate (int64_t sd)
{
  this -> stardate = sd ;
}

StarDate::~StarDate (void)
{
}

bool StarDate::isValid(void) const
{
  return ( this -> stardate > 0 ) ;
}

StarDate & StarDate::operator = (const StarDate & sd)
{
  this -> stardate = sd . stardate ;
  return (*this)                   ;
}

StarDate & StarDate::operator = (int64_t sd)
{
  this -> stardate = sd ;
  return (*this)        ;
}

StarDate & StarDate::operator += (int64_t seconds)
{
  this -> stardate += seconds ;
  return (*this)              ;
}

StarDate & StarDate::operator -= (int64_t seconds)
{
  this -> stardate -= seconds ;
  return (*this)              ;
}

StarDate & StarDate::Now(void)
{
  this -> setTime ( time (NULL) ) ;
  return (*this)                  ;
}

StarDate & StarDate::assign(const StarDate & sd)
{
  this -> stardate = sd . stardate ;
  return (*this)                   ;
}

StarDate & StarDate::setTime(time_t current)
{
  this -> stardate  = current ;
  this -> stardate += TBASE   ;
  return (*this)              ;
}

time_t StarDate::toTimestamp (void) const
{
  return time_t ( this -> stardate - TBASE ) ;
}

StarDate & StarDate::Add(int64_t seconds)
{
  this -> stardate += seconds ;
  return (*this)              ;
}

StarDate & StarDate::Subtract(int64_t seconds)
{
  this -> stardate -= seconds ;
  return (*this)              ;
}

int64_t StarDate::secondsTo(const StarDate & sd) const
{
  return int64_t ( sd . stardate - this -> stardate ) ;
}

int64_t StarDate::secondsTo(int64_t sd) const
{
  return int64_t ( sd - this -> stardate ) ;
}

#ifndef DONT_USE_NAMESPACE
}
#endif
