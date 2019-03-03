#include "nations.hpp"

#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#pragma pack(push,1)


#pragma pack(pop)

#ifndef DONT_USE_NAMESPACE
namespace NATIONS_NAMESPACE {
#endif

char * Clone (const char * ptr)
{
  if ( nullptr == ptr ) return nullptr ;
  size_t t = strlen ( ptr )            ;
  if ( t <=    0      ) return nullptr ;
  if ( t >  1023      ) t = 1023       ;
  char * p = new char [ t + 1 ]        ;
  p [ t ]  = 0                         ;
  ::memcpy ( p , ptr , t )             ;
  return p                             ;
}

Nation:: Nation (void)
{
  this -> Id    = 0       ;
  this -> Uuid  = 0       ;
  this -> Type  = 0       ;
  this -> Used  = 0       ;
  this -> Code  = 0       ;
  this -> Two   = nullptr ;
  this -> Three = nullptr ;
  this -> Four  = nullptr ;
  this -> Name  = nullptr ;
}

Nation:: Nation (const Nation & nation)
{
  this -> assign ( nation ) ;
}

Nation:: Nation (const NationItem & nation)
{
  this -> assign ( nation ) ;
}

Nation::~Nation (void)
{
  if ( nullptr != this -> Two   ) delete [ ] this -> Two   ;
  if ( nullptr != this -> Three ) delete [ ] this -> Three ;
  if ( nullptr != this -> Four  ) delete [ ] this -> Four  ;
  if ( nullptr != this -> Name  ) delete [ ] this -> Name  ;
  this -> Two   = nullptr                                  ;
  this -> Three = nullptr                                  ;
  this -> Four  = nullptr                                  ;
  this -> Name  = nullptr                                  ;
}

bool Nation::operator == (const Nation & nation) const
{
  if ( this -> Uuid != nation . Uuid ) return false ;
  if ( this -> Code != nation . Code ) return false ;
  if ( this -> Type != nation . Type ) return false ;
  return true                                       ;
}

Nation & Nation::operator = (const Nation & nation)
{
  return this -> assign ( nation ) ;
}

Nation & Nation::operator = (const NationItem & nation)
{
  return this -> assign ( nation ) ;
}

Nation & Nation::assign(const Nation & nation)
{
  this -> Id    =         nation . Id      ;
  this -> Uuid  =         nation . Uuid    ;
  this -> Type  =         nation . Type    ;
  this -> Used  =         nation . Used    ;
  this -> Code  =         nation . Code    ;
  this -> Two   = Clone ( nation . Two   ) ;
  this -> Three = Clone ( nation . Three ) ;
  this -> Four  = Clone ( nation . Four  ) ;
  this -> Name  = Clone ( nation . Name  ) ;
  return (*this)                           ;
}

Nation & Nation::assign(const NationItem & nation)
{
  this -> Id    =         nation . Id      ;
  this -> Uuid  =         nation . Uuid    ;
  this -> Type  =         nation . Type    ;
  this -> Used  =         nation . Used    ;
  this -> Code  =         nation . Code    ;
  this -> Two   = Clone ( nation . Two   ) ;
  this -> Three = Clone ( nation . Three ) ;
  this -> Four  = Clone ( nation . Four  ) ;
  this -> Name  = Clone ( nation . Name  ) ;
  return (*this)                           ;
}

bool Nation::isType(int8_t type) const
{
  return ( Type == type ) ;
}

bool Nation::isCountry(void) const
{
  return ( Country == Type ) ;
}

bool Nation::isRegion(void) const
{
  return ( Region == Type ) ;
}

bool Nation::isNormal(void) const
{
  if ( isCountry ( ) ) return true ;
  if ( isRegion  ( ) ) return true ;
  return false                     ;
}

bool Nation::isActivated (void) const
{
  return ( Using == this -> Used ) ;
}

bool Nation::isValid(uint64_t uuid) const
{
  if ( uuid < 7400000000000000001ULL ) return false ;
  if ( uuid > 7400000000001000000ULL ) return false ;
  return true                                       ;
}

bool Nation::isUuid(uint64_t uuid) const
{
  return ( Uuid == uuid ) ;
}

bool Nation::isEqual(int16_t code) const
{
  return ( Code == code ) ;
}

bool Nation::isEqual(const char * alpha) const
{
  if ( nullptr == alpha ) return false ;
  size_t len = strlen ( alpha )        ;
  if ( len > 4 ) return false          ;
  if ( len < 2 ) return false          ;
  //////////////////////////////////////
  const char * p = nullptr             ;
  switch ( len )                       {
    case 2: p = Two   ; break          ;
    case 3: p = Three ; break          ;
    case 4: p = Four  ; break          ;
  }                                    ;
  if ( nullptr == p ) return false     ;
  //////////////////////////////////////
  for (size_t i = 0 ; i < len ; i++ )  {
    int c = p     [ i ]                ;
    int z = alpha [ i ]                ;
    c = tolower ( c )                  ;
    z = tolower ( z )                  ;
    if ( c != z ) return false         ;
  }                                    ;
  //////////////////////////////////////
  return true                          ;
}

std::string Nation::toStdString(int length)
{
  std::string key                                       ;
  switch ( length )                                     {
    case 2: if ( nullptr != Two   ) key = Two   ; break ;
    case 3: if ( nullptr != Three ) key = Three ; break ;
    case 4: if ( nullptr != Four  ) key = Four  ; break ;
  }                                                     ;
  return key                                            ;
}

int Nation::NationItemCount(NationItem items [ ])
{
  int count = 0                              ;
  while ( items [ count ] . Id > 0 ) count++ ;
  return count                               ;
}

#ifndef DONT_USE_NAMESPACE
}
#endif
