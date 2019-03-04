#include "stardate.hpp"

#include <Windows.h>

#pragma pack(push,1)


#pragma pack(pop)

#ifndef DONT_USE_NAMESPACE
namespace STARDATE_NAMESPACE {
#endif

#if defined(CIOS_X64)

#include <stdio.h>
#include <intrin.h>

#pragma intrinsic(__rdtsc)

int64_t getRDTSC(void)
{
  return __rdtsc ( ) ;
}

#elif defined(CIOS_X86)

#define rdtsc __asm __emit 0fh __asm __emit 031h

int64_t getRDTSC(void)
{
  LARGE_INTEGER li          ;
  rdtsc                     ;
  ///////////////////////////
  __asm mov li.LowPart , eax;
  __asm mov li.HighPart, edx;
  ///////////////////////////
  return li . QuadPart      ;
}

#endif

int64_t HardwareClock(void)
{
  LARGE_INTEGER HC                 ;
  HC . QuadPart = 0                ;
  QueryPerformanceCounter ( &HC )  ;
  return int64_t ( HC . QuadPart ) ;
}

int64_t HardwareFrequency(void)
{
  LARGE_INTEGER HF                  ;
  HF . QuadPart = 0                 ;
  QueryPerformanceFrequency ( &HF ) ;
  return int64_t ( HF . QuadPart )  ;
}

#ifndef DONT_USE_NAMESPACE
}
#endif
