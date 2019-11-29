#include "stardate.hpp"

#include <Windows.h>
#include <io.h>

#define EPOCHFILETIME (116444736000000000LL)

#pragma pack(push,1)

struct timezone       {
  long tz_minuteswest ; /* minutes W of Greenwich */
  int  tz_dsttime     ; /* type of dst correction */
}                     ;

#pragma pack(pop)

#ifndef DONT_USE_NAMESPACE
namespace STARDATE_NAMESPACE {
#endif

int strcasecmp_local(const char *s1,const char *s2)
{
  while (::toupper((unsigned char)*s1) == ::toupper((unsigned char)*s2++)) {
    if ( *s1++ == '\0' )  return 0                                         ;
  }                                                                        ;
  return (::toupper((unsigned char)*s1) - ::toupper((unsigned char)*--s2)) ;
}

void uSleep(int64_t usec)
{
  HANDLE        timer                                                        ;
  LARGE_INTEGER ft                                                           ;
  ft . QuadPart =                   - ( 10 * usec                          ) ;
  timer         = CreateWaitableTimer ( NULL , TRUE , NULL                 ) ;
  SetWaitableTimer                    ( timer , &ft , 0 , NULL , NULL , 0  ) ;
  WaitForSingleObject                 ( timer , INFINITE                   ) ;
  CloseHandle                         ( timer                              ) ;
}

int gettimeofday(struct timeval * tv, struct timezone * tz)
{
  FILETIME      ft                          ;
  LARGE_INTEGER li                          ;
  int64_t       t                           ;
  static int    tzflag                      ;
  ///////////////////////////////////////////
  if ( nullptr != tv )                      {
    ::GetSystemTimeAsFileTime ( &ft )       ;
    li . LowPart  = ft . dwLowDateTime      ;
    li . HighPart = ft . dwHighDateTime     ;
    t             = li . QuadPart           ; /* In 100-nanosecond intervals */
    t            -= EPOCHFILETIME           ; /* Offset to the Epoch time */
    t            /= 10                      ; /* In microseconds */
    tv -> tv_sec  = long ( t / 1000000LL )  ;
    tv -> tv_usec = long ( t % 1000000LL )  ;
  }                                         ;
  ///////////////////////////////////////////
  if ( nullptr != tz )                      {
    if ( ! tzflag )                         {
      _tzset ( )                            ;
       tzflag++                             ;
    }                                       ;
    /////////////////////////////////////////
    _get_timezone ( &tz -> tz_minuteswest ) ;
    tz -> tz_minuteswest /= 60              ;
    _get_daylight ( &tz -> tz_dsttime     ) ;
    /////////////////////////////////////////
  }                                         ;
  ///////////////////////////////////////////
  return 0                                  ;
}

#ifndef DONT_USE_NAMESPACE
}
#endif
