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

class LIBSTARDATE_EXPORT StarDate
{
  public:

    int64_t stardate ;

    explicit        StarDate     (void) ;
                    StarDate     (const StarDate & sd) ;
                    StarDate     (int64_t sd) ;
    virtual        ~StarDate     (void) ;

    operator        int64_t      ( ) const { return stardate ; }
    virtual int     type         (void) const ;

    bool            isValid      (void) const ;

    virtual int64_t Standard     (void) const ;
    virtual int64_t TimeShift    (void) const ;

    virtual void    adjustments  (void) ;

    StarDate &      operator   = (const StarDate & sd) ;
    StarDate &      operator   = (int64_t sd) ;

    StarDate &      operator  += (int64_t seconds) ;
    StarDate &      operator  -= (int64_t seconds) ;

    bool            isEqual      (const StarDate & sd) const ;
    bool            isEqual      (int64_t sd) const ;

    bool            isGreater    (const StarDate & sd) const ;
    bool            isGreater    (int64_t sd) const ;

    bool            isLess       (const StarDate & sd) const ;
    bool            isLess       (int64_t sd) const ;

    bool            operator  == (const StarDate & sd) const ;
    bool            operator  == (int64_t sd) const ;

    bool            operator   > (const StarDate & sd) const ;
    bool            operator   > (int64_t sd) const ;
    bool            operator   < (const StarDate & sd) const ;
    bool            operator   < (int64_t sd) const ;

    StarDate        operator   + (int64_t seconds) ;
    StarDate        operator   - (int64_t seconds) ;

    StarDate &      Now          (void) ;
    StarDate &      assign       (const StarDate & sd) ;
    StarDate &      setTime      (time_t current) ;
    StarDate &      fromUStamp   (int64_t uts) ;
    time_t          toTimestamp  (void) const ;

    // StarDate Version of Day and Time
    int64_t         toDay        (void) const ;
    int64_t         toTime       (void) const ;

    // Lilian Seconds ... Seconds version of Lilian Date
    int64_t         LilianNumber (void) const ;
    StarDate &      setLilian    (int64_t lilian) ;

    // Millions Years Ago
    long double     toMya        (void) const ;
    long double     setMya       (long double mya) ;

    // Julian Calendar
    StarDate &      setJulianDay (long double JD) ;
    long double     JulianDay    (void) const ;

    long double     RataDie      (void) const ;
    long double     MJD          (void) const ;

    StarDate &      Add          (int64_t seconds) ;
    StarDate &      Subtract     (int64_t seconds) ;

    int64_t         toNow        (void) const ;

    int64_t         secondsTo    (const StarDate & sd) const ;
    int64_t         secondsTo    (int64_t sd) const ;

    int64_t         daysTo       (const StarDate & sd) const ;
    int64_t         daysTo       (int64_t sd) const ;

    // Estimate Complete StarDate Timestamp
    StarDate        ETA          (int64_t index,int64_t total) ;
    StarDate        ETA          (int64_t index,int64_t minv,int64_t maxv) ;

    // Estimate Total Seconds
    int64_t         Estimate     (int64_t index,int64_t total) ;
    int64_t         Estimate     (int64_t index,int64_t minv,int64_t maxv) ;

    static void     sleep        (int64_t seconds) ;
    static void     msleep       (int64_t mseconds) ;
    static void     usleep       (int64_t useconds) ;

    static int64_t  current      (void) ;
    static int64_t  useconds     (void) ;
    static int64_t  ustamp       (void) ;
    static int64_t  tzOffset     (void) ;
    static int64_t  RDTSC        (void) ;
    static int64_t  Clock        (void) ;
    static int64_t  Frequency    (void) ;

  protected:

  private:

} ;

#ifndef DONT_USE_NAMESPACE
}
#endif

#endif
