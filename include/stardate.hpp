/****************************************************************************\
 *
 *                         CIOS Star Date System
 *
\****************************************************************************/

#ifndef CIOS_STARDATE_HPP
#define CIOS_STARDATE_HPP

// cmake ... -DBUILD_SHARED_LIBS=1 ... => compile shared library
#if defined (WIN32) && defined(BUILD_SHARED_LIBS)
  #if defined (_MSC_VER)
    #pragma warning(disable: 4251)
    #pragma warning(disable: 4819)
  #endif
  #if defined(EXPORT_LIBSTARDATE)
    #define LIBSTARDATE_EXPORT __declspec(dllexport)
  #else
    #define LIBSTARDATE_EXPORT __declspec(dllimport)
  #endif
#else
    #define LIBSTARDATE_EXPORT
#endif

#include <stdint.h>
#include <stdio.h>
#include <time.h>

#if !defined(STARDATE_NAMESPACE)
#define STARDATE_NAMESPACE CIOS
#endif

// Debug
#ifdef CIOSDEBUG

#endif

#ifndef DONT_USE_NAMESPACE
namespace STARDATE_NAMESPACE {
#endif

#pragma pack(push,1)

#pragma pack(pop)

class LIBSTARDATE_EXPORT StarDate
{
  public:

    int64_t stardate ;

    explicit       StarDate    (void) ;
                   StarDate    (const StarDate & sd) ;
                   StarDate    (int64_t sd) ;
    virtual       ~StarDate    (void) ;

    operator       int64_t     ( ) const { return stardate ; }
    bool           isValid     (void) const ;

    StarDate &     operator  = (const StarDate & sd) ;
    StarDate &     operator  = (int64_t sd) ;

    StarDate &     operator += (int64_t seconds) ;
    StarDate &     operator -= (int64_t seconds) ;

    StarDate &     Now         (void) ;
    StarDate &     assign      (const StarDate & sd) ;
    StarDate &     setTime     (time_t current) ;
    time_t         toTimestamp (void) const ;

    StarDate &     Add         (int64_t seconds) ;
    StarDate &     Subtract    (int64_t seconds) ;

    int64_t        secondsTo   (const StarDate & sd) const ;
    int64_t        secondsTo   (int64_t sd) const ;

    static void    sleep       (int64_t seconds) ;
    static void    msleep      (int64_t mseconds) ;
    static void    usleep      (int64_t useconds) ;

    static int64_t useconds    (void) ;

  protected:

  private:

} ;

#ifndef DONT_USE_NAMESPACE
}
#endif

#endif
