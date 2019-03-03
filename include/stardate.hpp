/****************************************************************************\
 *
 *                         ISO 3166 Country Supports
 *
 * ISO 3166-1
 * ISO 3166-2
 * ISO 3166-3
 *
\****************************************************************************/

#ifndef CIOS_NATIONS_HPP
#define CIOS_NATIONS_HPP

// cmake ... -DBUILD_SHARED_LIBS=1 ... => compile shared library
#if defined (WIN32) && defined(BUILD_SHARED_LIBS)
  #if defined (_MSC_VER)
    #pragma warning(disable: 4251)
    #pragma warning(disable: 4819)
  #endif
  #if defined(EXPORT_LIBNATIONS)
    #define LIBNATIONS_EXPORT __declspec(dllexport)
  #else
    #define LIBNATIONS_EXPORT __declspec(dllimport)
  #endif
#else
    #define LIBNATIONS_EXPORT
#endif

#include <stdint.h>
#include <stdio.h>
#include <string>

#if !defined(NATIONS_NAMESPACE)
#define NATIONS_NAMESPACE CIOS
#endif

// Debug
#ifdef CIOSDEBUG

#endif

#ifndef DONT_USE_NAMESPACE
namespace NATIONS_NAMESPACE {
#endif

class LIBNATIONS_EXPORT Nation ;

#pragma pack(push,1)

// ISO 3166-1
typedef struct        {
  int32_t      Id     ;
  uint64_t     Uuid   ;
  int8_t       Type   ;
  int8_t       Used   ;
  int16_t      Code   ;
  const char * Two    ;
  const char * Three  ;
  const char * Four   ;
  const char * Name   ;
} NationItem          ;

// ISO 3166-2
typedef struct        {
  int32_t      Id     ;
  uint64_t     Uuid   ;
  int8_t       Type   ;
  int8_t       Used   ;
  uint64_t     Nation ;
  int16_t      Code   ;
  const char * Two    ;
  const char * SAC    ;
} RegionItem          ;

#pragma pack(pop)

LIBNATIONS_EXPORT extern NationItem DefaultNations  [ ] ; // Regular ISO 3166 Supports
LIBNATIONS_EXPORT extern NationItem ExtendedNations [ ] ; // Extended ISO 3166 Supports, some other virtual or fiction records

// To disable this, try cmake ... -DDISABLE_NATION_ENUMS=1
#ifndef DISABLE_NATION_ENUMS
LIBNATIONS_EXPORT extern const char * NationTypeStrings       [ ] ; // For Types enum
LIBNATIONS_EXPORT extern const char * NationActivationStrings [ ] ; // For Activations enum
#endif

class LIBNATIONS_EXPORT Nation
{
  public:

    typedef enum
      Types          {
      Any        = 0 ,
      Country    = 1 ,
      Region     = 2 ,
      Dispute    = 3 ,
      Spiritual  = 4 ,
      Expired    = 5 ,
      Historical = 6 ,
      Fiction    = 7 ,
      Virtual    = 8 ,
      Others     = 9 }
      Types          ;

    typedef enum
      Activations    {
      Unused     = 0 ,
      Using      = 1 ,
      Editing    = 2 ,
      Suspension = 3 }
      Activations    ;

    int32_t  Id    ; // SQL Sequence Id or Array Id, start from 1
    uint64_t Uuid  ; // 7400000000000000001 ~  7400000000001000000
    int8_t   Type  ; // Types
    int8_t   Used  ; // Activations
    int16_t  Code  ; // ISO 3166-1 Country Code, 0 for stop list
    char   * Two   ; // ISO 3166-1 Alpha-2 Code
    char   * Three ; // ISO 3166-1 Alpha-3 Code
    char   * Four  ; // ISO 3166-3 Four-letter code
    char   * Name  ; // Country English Name

    explicit    Nation          (void) ;
                Nation          (const Nation     & nation) ;
                Nation          (const NationItem & nation) ;
    virtual    ~Nation          (void) ;

    bool        operator     == (const Nation     & nation) const ;

    Nation    & operator      = (const Nation     & nation) ;
    Nation    & operator      = (const NationItem & nation) ;

    Nation    & assign          (const Nation     & nation) ;
    Nation    & assign          (const NationItem & nation) ;

    bool        isType          (int8_t type) const ;
    bool        isCountry       (void) const ; // is this Id a Country
    bool        isRegion        (void) const ; // is this Id a Region
    bool        isNormal        (void) const ; // is this Id a Country or a Region
    bool        isActivated     (void) const ;
    bool        isValid         (uint64_t uuid) const ;
    bool        isUuid          (uint64_t uuid) const ;
    bool        isEqual         (int16_t code) const ;

    // string length = 2 , compare to Two
    // string length = 3 , compare to Three
    // string length = 4 , compare to Four
    bool        isEqual         (const char * alpha) const ;

    // length = 2 -> Two
    // length = 3 -> Three
    // length = 4 -> Four
    std::string toStdString     (int length) ;

    static int  NationItemCount (NationItem items[]) ;

  protected:

  private:

} ;

class LIBNATIONS_EXPORT Region
{
  public:

    explicit    Region          (void) ;
                Region          (const Region     & region) ;
    virtual    ~Region          (void) ;

  protected:

  private:

} ;

#ifndef DONT_USE_NAMESPACE
}
#endif

#endif
