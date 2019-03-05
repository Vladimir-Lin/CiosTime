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

#include <string>
#include <list>
#include <utility>

#if !defined(STARDATE_NAMESPACE)
#define STARDATE_NAMESPACE CIOS
#endif

// Debug
#ifdef CIOSDEBUG

#endif

#ifndef DONT_USE_NAMESPACE
namespace STARDATE_NAMESPACE {
#endif

class LIBSTARDATE_EXPORT StarDate  ;
class LIBSTARDATE_EXPORT StarTime  ;
class LIBSTARDATE_EXPORT Frequency ;
class LIBSTARDATE_EXPORT Estimator ;

class LIBSTARDATE_EXPORT StarDate
{
  public:

    int64_t stardate ; // this records only seconds

    explicit        StarDate     (void) ;
                    StarDate     (const StarDate & sd) ;
                    StarDate     (int64_t sd) ;
    virtual        ~StarDate     (void) ;

    operator        int64_t      ( ) const { return stardate ; }
    virtual int     type         (void) const ; // return 0 ;

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
    StarDate &      assign       (int64_t sd) ;
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

class LIBSTARDATE_EXPORT StarTime : public StarDate
{
  public:

    int64_t startime ; // this records only nano-seconds, 10^9

    explicit        StarTime      (void) ;
                    StarTime      (const StarTime & st) ;
    virtual        ~StarTime      (void) ;

    virtual int     type          (void) const ; // return 1 ;

    bool            isValid       (void) const ;

    StarTime &      operator    = (const StarTime & st) ;

    bool            operator   == (const StarTime & sd) const ;
    bool            operator    > (const StarTime & sd) const ;
    bool            operator    < (const StarTime & sd) const ;

    int64_t         operator    - (const StarTime & st) const ;

    bool            isEqual       (const StarTime & st) const ;
    bool            isGreater     (const StarTime & st) const ;
    bool            isLess        (const StarTime & st) const ;

    StarTime &      Now           (void) ;
    StarTime &      assign        (const StarTime & st) ;

    int64_t         nanosecondsTo (const StarTime & st) const ;
    int64_t         Leaps         (void) const ;

    StarTime &      AddNano       (int64_t nanoseconds) ;
    StarTime &      SubtractNano  (int64_t nanoseconds) ;

  protected:

  private:

} ;

class LIBSTARDATE_EXPORT Frequency
{
  public:

    long double factor    ;
    long double frequency ;
    int64_t     events    ;
    int64_t     duration  ;

    operator long double        (    ) const ; // frequency * factor
    // Before you do this, remember to call evaluate() first.
    // For some reasons, the author refuse to add
    // an automatical call to evaluate()

    explicit            Frequency   (void) ;
                        Frequency   (const Frequency & freq) ;
    virtual            ~Frequency   (void) ;

    Frequency &         operator  = (const Frequency & freq) ;
    Frequency &         operator ++ (void) ; // events++
    Frequency &         operator += (int64_t count) ; // events += count

    Frequency &         assign      (const Frequency & freq) ;

    virtual long double evaluate    (void) ; // frequency = events    / duration
    virtual long double velocity    (void) ; // events    = frequency * duration  (double)
    virtual long double length      (void) ; // duration  = events    / frequency (double)
    virtual int64_t     total       (void) ; // events    = frequency * duration
    virtual int64_t     lambda      (void) ; // duration  = events    / frequency

    // If you do this, remember to set the factor to 1000000000.0 manually
    // In this function, it force to use 1000000000.0 as factor
    // If you want these values maintain meaningful, you will have to
    // set the factor to 1000000000.0
    // this function uses duration =  T.Leaps()
    // return value is ( frequency * 1000000000.0 )
    // if T.Leaps() < 0 , duration =  - T.usecondsToNow() will be used
    virtual long double operator  = (const StarTime & T) ;

  protected:

  private:

} ;

/*****************************************************************************
 *                                                                           *
 *                                Data Estimator                             *
 *                                                                           *
 * Normally, this is used for a download or complete percentage rate         *
 *                                                                           *
 *****************************************************************************/

class LIBSTARDATE_EXPORT Estimator
{
  public:

    long double                                   GlobalRate ;
    long double                                   RecentRate ;
    long double                                   Completed  ;
    //////////////////////////////////////////////////////////
    int64_t                                       Duration   ;
    int64_t                                       Arrival    ;
    int64_t                                       Recent     ;
    int64_t                                       Goal       ;
    //////////////////////////////////////////////////////////
    size_t                                        MaxSizes   ;
    //////////////////////////////////////////////////////////
    StarTime                                      StartTime  ;
    StarTime                                      FinishTime ;
    StarTime                                      Estimated  ;
    StarTime                                      Tick       ;
    //////////////////////////////////////////////////////////
    Frequency                                     Counter    ;
    Frequency                                     Update     ;
    //////////////////////////////////////////////////////////
    std::list < std::pair < int64_t , int64_t > > Sizes      ;

    explicit                           Estimator   (void) ;
    virtual                           ~Estimator   (void) ;

    void                               setGoal     (int64_t goal) ;
    void                               setRecent   (int64_t seconds) ;

    virtual void                       operator += (int64_t size) ;
    virtual std::pair<int64_t,int64_t> append      (int64_t size) ;
    virtual std::pair<int64_t,int64_t> add         (int64_t size) ;
    virtual void                       start       (void) ;
    virtual void                       update      (void) ;
    virtual void                       update      (int64_t T) ;

  protected:

  private:

} ;

#ifndef DONT_USE_NAMESPACE
}
#endif

#endif
