<?php

namespace CIOS ;

class StarDate
{

public $Stardate ;

function __construct( $SDT = 0 )
{
  $this -> StarDate ( $SDT ) ;
}

function __destruct()
{
}

public function StarDate ( $SDT )
{
  if ( is_a ( $SDT , "CIOS\StarDate" ) ) {
    $this -> Stardate = $SDT -> Stardate ;
  } else                                 {
    $this -> Stardate = $SDT             ;
  }                                      ;
}

public function setSD($SD)
{
  $this -> StarDate ( $SDT ) ;
}

public function isValid()
{
  return ( $this -> Stardate > 0 ) ;
}

// unix timestamp to stardate
public function setTime($T)
{
  $this -> Stardate = $T + 1420092377704080000 ;
  return $this -> Stardate                     ;
}

public function Seconds($D,$H,$M,$S)
{
  return $this -> Days    ( $D ) +
         $this -> Hours   ( $H ) +
         $this -> Minutes ( $M ) +
         $S                      ;
}

public function Minutes($M)
{
  return ( $M * 60 ) ;
}

public function Hours($H)
{
  return ( $H * 3600 ) ;
}

public function Days($D)
{
  return ( $D * 84600 ) ;
}

public function Add($S)
{
  $this -> Stardate += $S  ;
  return $this -> Stardate ;
}

public function AddDuration($S)
{
  $SS  = explode ( ":" , $S )   ;
  $TT  = 0                      ;
  $CNT = count ( $SS )          ;
  if ( $CNT > 0 )               {
    $II = 0                     ;
    while ( $II < $CNT )        {
      $TT = $TT * 60            ;
      $XX = $SS [ $II ]         ;
      $XX = intval ( $XX , 10 ) ;
      $TT = $TT + $XX           ;
      $II = $II + 1             ;
    }                           ;
    $this -> Add ( $TT )        ;
  }                             ;
  return $this -> Stardate      ;
}

public function Subtract($S)
{
  $this -> Stardate -= $S  ;
  return $this -> Stardate ;
}

public function Now()
{
  return $this -> setTime ( time ( ) ) ;
}

// stardate to unix timestamp
public function Timestamp()
{
  return intval ( $this -> Stardate - 1420092377704080000 , 10 ) ;
}

public function secondsTo($SD)
{
  return ( $SD -> Stardate - $this -> Stardate ) ;
}

public function fromDateTime($DT)
{
  return $this -> setTime ( $DT -> getTimestamp ( ) ) ;
}

public function fromFormat($dtString,$TZ="")
{
  if                                  ( strlen ( $TZ ) > 0              ) {
    $TX = new \DateTimeZone           ( $TZ                             ) ;
    $DT = \DateTime::createFromFormat ( "Y/m/d H:i:s" , $dtString , $TX ) ;
  } else                                                                  {
    $DT = \DateTime::createFromFormat ( "Y/m/d H:i:s" , $dtString       ) ;
  }                                                                       ;
  return $this -> fromDateTime        ( $DT                             ) ;
}

public function fromInput($inpString,$TZ="")
{
  $dtxString = str_replace   ( "T" , " "  , $inpString ) ;
  $dtxString = str_replace   ( "-" , "/"  , $dtxString ) ;
  $cnt       = substr_count  ( $dtxString , ":"        ) ;
  if ( $cnt == 1 ) $dtxString = $dtxString . ":00"       ;
  return $this -> fromFormat ( $dtxString , $TZ        ) ;
}

public function ShrinkMinute()
{
  $TS = $this -> Timestamp ( ) ;
  $TS = $TS % 60               ;
  $this -> Subtract ( $TS )    ;
}

public function ShrinkHour()
{
  $TS = $this -> Timestamp ( ) ;
  $TS = $TS % 3600             ;
  $this -> Subtract ( $TS )    ;
}

public function toDateTime($TZ)
{
  $TX  = new \DateTimeZone ( $TZ                    ) ;
  $DT  = new \DateTime     (                        ) ;
  $DT -> setTimezone       ( $TX                    ) ;
  $DT -> setTimestamp      ( $this -> Timestamp ( ) ) ;
  unset                    ( $TX                    ) ;
  return $DT                                          ;
}

public function Weekday($TZ)
{
  $DT = $this -> toDateTime ( $TZ      ) ;
  $WD = $DT   -> format     ( "N"      ) ;
  ////////////////////////////////////////
  unset                     ( $DT      ) ;
  ////////////////////////////////////////
  return intval             ( $WD , 10 ) ;
}

public function isPM($TZ)
{
  $DT = $this -> toDateTime ( $TZ      ) ;
  $HD = $DT   -> format     ( "G"      ) ;
  ////////////////////////////////////////
  unset                     ( $DT      ) ;
  ////////////////////////////////////////
  $HD = intval              ( $HD , 10 ) ;
  ////////////////////////////////////////
  return ( $HD < 12 ) ? 0 : 1            ;
}

public function toDateString($TZ,$FMT="Y/m/d")
{
  $DT = $this -> toDateTime ( $TZ  ) ;
  $DS = $DT   -> format     ( $FMT ) ;
  unset                     ( $DT  ) ;
  return $DS                         ;
}

public function toTimeString($TZ,$FMT="H:i:s")
{
  $DT = $this -> toDateTime ( $TZ  ) ;
  $DS = $DT   -> format     ( $FMT ) ;
  unset                     ( $DT  ) ;
  return $DS                         ;
}

public function toDateTimeString($TZ,$JOIN="T",$DateFormat="Y-m-d",$TimeFormat="H:i:s")
{
  $DX = $this -> toDateTime ( $TZ         ) ;
  $DS = $DX   -> format     ( $DateFormat ) ;
  $DT = $DX   -> format     ( $TimeFormat ) ;
  unset                     ( $DX         ) ;
  return $DS . $JOIN . $DT                  ;
}

public function toLongString($TZ,$DateFormat="Y-m-d",$TimeFormat="H:i:s")
{
  $Correct = true                                                            ;
  ////////////////////////////////////////////////////////////////////////////
  if  ( isset ( $GLOBALS [ "WeekDays" ] )                                  ) {
    $WeekDays = $GLOBALS [ "WeekDays" ]                                      ;
  } else $Correct = false                                                    ;
  ////////////////////////////////////////////////////////////////////////////
  if  ( isset ( $GLOBALS [ "AMPM"     ] )                                  ) {
    $AMPM     = $GLOBALS [ "AMPM"     ]                                      ;
  } else $Correct = false                                                    ;
  ////////////////////////////////////////////////////////////////////////////
  if ( $Correct                                                            ) {
    $SW  = $WeekDays [ $this -> Weekday ( $TZ ) ]                            ;
    $SP  = $AMPM     [ $this -> isPM    ( $TZ ) ]                            ;
    $SJ  = " {$SW} {$SP} "                                                   ;
  } else $SJ = " "                                                           ;
  ////////////////////////////////////////////////////////////////////////////
  return $this -> toDateTimeString ( $TZ , $SJ , $DateFormat , $TimeFormat ) ;
}

// php time format calcuation
public function Calculate($DTS)
{
  $this -> setTime ( strtotime ( $DTS , $this -> Timestamp ( ) ) ) ;
}

public function SecondsOfDay($TZ)
{
  $DX             = $this -> toDateString ( $TZ , "Y-m-d"     ) ;
  $DX             = "{$DX}T00:00:00"                            ;
  $XS             = new StarDate          (                   ) ;
  $XS -> Stardate = $XS -> fromInput      ( $DX               ) ;
  $XV             = $XS -> secondsTo      ( $this             ) ;
  $XV             = intval                ( (string) $XV , 10 ) ;
  return $XV                                                    ;
}

// calcuate a person's age
public function YearsOld($TZ)
{
  $TDT = $this -> toDateTime ( $TZ  ) ;
  $NDT = new \DateTime       (      ) ;
  $DIF = $NDT -> diff        ( $TDT ) ;
  return $DIF -> y                    ;
}

public static function StarDateToString($DT,$Tz,$FMT)
{
  $SD  = new StarDate      (      ) ;
  $SD -> Stardate = $DT             ;
  $DX  = $SD -> toDateTime ( $Tz  ) ;
  $SS  = $DX -> format     ( $FMT ) ;
  ///////////////////////////////////
  unset                    ( $SD  ) ;
  unset                    ( $DX  ) ;
  ///////////////////////////////////
  return $SS                        ;
}

public static function StarDateString($DT,$FMT)
{
  $Tz = TimeZones::GetTZ        (                  ) ;
  return self::StarDateToString ( $DT , $Tz , $FMT ) ;
}

public static function UntilToday($DATE,$TZ,$YEARSTR,$MONTHSTR)
{
  //////////////////////////////////////////////////////
  if ( strlen ( $DATE ) <= 0 ) return ""               ;
  $NOW  = new StarDate ( )                             ;
  $NOW -> Now          ( )                             ;
  //////////////////////////////////////////////////////
  $XXXZ = $NOW -> toDateString ( $TZ , "Y-m-d" )       ;
  $DATE = str_replace ( "/" , "-" , $DATE  )           ;
  //////////////////////////////////////////////////////
  $ZZZ  = explode ( "-" , $DATE )                      ;
  $WWW  = explode ( "-" , $XXXZ )                      ;
  //////////////////////////////////////////////////////
  $YYY  = intval ( $WWW [ 0 ] , 10 )                   ;
  $YYY -= intval ( $ZZZ [ 0 ] , 10 )                   ;
  //////////////////////////////////////////////////////
  $MMM  = intval ( $WWW [ 1 ] , 10 )                   ;
  $MMM -= intval ( $ZZZ [ 1 ] , 10 )                   ;
  //////////////////////////////////////////////////////
  $DDD  = intval ( $WWW [ 2 ] , 10 )                   ;
  $DDD -= intval ( $ZZZ [ 2 ] , 10 )                   ;
  //////////////////////////////////////////////////////
  if ( $DDD < 0 ) $MMM = $MMM - 1                      ;
  if ( $MMM < 0 )                                      {
    $MMM = $MMM + 12                                   ;
    $YYY = $YYY - 1                                    ;
  }                                                    ;
  //////////////////////////////////////////////////////
  $YST = str_replace ( "$(TOTAL)" , $YYY , $YEARSTR  ) ;
  $MST = str_replace ( "$(TOTAL)" , $MMM , $MONTHSTR ) ;
  $MSG = ""                                            ;
  if ( $YYY > 0 ) $MSG = $MSG . $YST                   ;
  if ( $MMM > 0 ) $MSG = $MSG . $MST                   ;
  if ( strlen ( $MSG ) <= 0 ) $MSG = "0"               ;
  //////////////////////////////////////////////////////
  return $MSG                                          ;
}
//////////////////////////////////////////////////////////////////////////////
}
//////////////////////////////////////////////////////////////////////////////
?>
