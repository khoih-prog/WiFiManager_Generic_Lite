/*******************************************************************************************************************************
  WiFiManager_Generic_Lite_Debug.h
  For Mega, Teensy, SAM DUE, SAMD and STM32 boards using WIFI_GENERIC modules/shields,
  using much less code to support boards with smaller memory

  WiFiManager_Generic_WM_Lite is a library for the Mega, Teensy, SAM DUE, SAMD and STM32 boards
  (https://github.com/khoih-prog/WiFiManager_Generic_Lite) to enable store Credentials in EEPROM/LittleFS for easy
  configuration/reconfiguration and autoconnect/autoreconnect of WiFi and other services without Hardcoding.

  Built by Khoi Hoang https://github.com/khoih-prog/WiFiManager_Generic_Lite
  Licensed under MIT license

  Version: 1.8.0

  Version Modified By   Date        Comments
  ------- -----------  ----------   -----------
  1.0.0   K Hoang      04/02/2021  Initial coding for generic boards using generic WiFi.
  ....
  1.5.0   K Hoang      07/01/2022  Configurable WIFI_RECON_INTERVAL. Add support to RP2040 using arduino-pico core
  1.5.1   K Hoang      26/01/2022  Update to be compatible with new FlashStorage libraries. Add support to more RTL8720/STM32 boards
  1.6.0   K Hoang      26/01/2022  Optional Board_Name in Menu. Optimize code by using passing by reference
                                   Add optional CONFIG_MODE_LED. Add function isConfigMode()
  1.7.0   K Hoang      27/04/2022  Use WiFiMulti_Generic library for auto-checking / auto-reconnecting MultiWiFi
  1.7.1   K Hoang      27/04/2022  Optimize code
  1.8.0   K Hoang      18/05/2022  Add support to Ameba Realtek RTL8720DN, RTL8722DM and RTL8722CSM
 ********************************************************************************************************************************/

#ifndef WiFiManager_Generic_Lite_Debug_h
#define WiFiManager_Generic_Lite_Debug_h

#ifdef WIFI_GENERIC_DEBUG_OUTPUT
  #define DBG_PORT_WG       WIFI_GENERIC_DEBUG_OUTPUT
#else
  #define DBG_PORT_WG       Serial
#endif

// Change _WIFI_GENERIC_LOGLEVEL_ to set tracing and logging verbosity
// 0: DISABLED: no logging
// 1: ERROR: errors
// 2: WARN: errors and warnings
// 3: INFO: errors, warnings and informational (default)
// 4: DEBUG: errors, warnings, informational and debug

#ifndef _WIFI_GENERIC_LOGLEVEL_
  #define _WIFI_GENERIC_LOGLEVEL_       0
#endif

////////////////////////////////////////////////////////////////////////////////////////////

const char WG_MARK[] = "[WG] ";

#define WG_PRINT_MARK   DBG_PORT_WG.print(WG_MARK)

#define WG_PRINT        DBG_PORT_WG.print
#define WG_PRINTLN      DBG_PORT_WG.println

// Error waitResponse message
#define ERROR_RESPONSE  ":Error waitResponse"

////////////////////////////////////////////////////////////////////////////////////////////

#define WG_LOGERROR0(x)     if(_WIFI_GENERIC_LOGLEVEL_>0) { WG_PRINT(x); }
#define WG_LOGERROR(x)      if(_WIFI_GENERIC_LOGLEVEL_>0) { WG_PRINT_MARK; WG_PRINTLN(x); }
#define WG_LOGERROR1(x,y)   if(_WIFI_GENERIC_LOGLEVEL_>0) { WG_PRINT_MARK; WG_PRINT(x); WG_PRINTLN(y); }
#define WG_LOGERROR2(x,y,z) if(_WIFI_GENERIC_LOGLEVEL_>0) { WG_PRINT_MARK; WG_PRINT(x); WG_PRINT(y); WG_PRINTLN(z); }
#define WG_LOGERROR3(x,y,z,w) if(_WIFI_GENERIC_LOGLEVEL_>0) { WG_PRINT_MARK; WG_PRINT(x); WG_PRINT(y); WG_PRINT(z); WG_PRINTLN(w); }
#define WG_LOGERROR5(x,y,z,w,xx,yy) if(_WIFI_GENERIC_LOGLEVEL_>0) { WG_PRINT_MARK; WG_PRINT(x); WG_PRINT(y); WG_PRINT(z); WG_PRINT(w); WG_PRINT(xx); WG_PRINTLN(yy); }

////////////////////////////////////////////////////////////////////////////////////////////

#define WG_LOGWARN0(x)     if(_WIFI_GENERIC_LOGLEVEL_>1) { WG_PRINT(x); }
#define WG_LOGWARN(x)      if(_WIFI_GENERIC_LOGLEVEL_>1) { WG_PRINT_MARK; WG_PRINTLN(x); }
#define WG_LOGWARN1(x,y)   if(_WIFI_GENERIC_LOGLEVEL_>1) { WG_PRINT_MARK; WG_PRINT(x); WG_PRINTLN(y); }
#define WG_LOGWARN2(x,y,z) if(_WIFI_GENERIC_LOGLEVEL_>1) { WG_PRINT_MARK; WG_PRINT(x); WG_PRINT(y); WG_PRINTLN(z); }
#define WG_LOGWARN3(x,y,z,w) if(_WIFI_GENERIC_LOGLEVEL_>1) { WG_PRINT_MARK; WG_PRINT(x); WG_PRINT(y); WG_PRINT(z); WG_PRINTLN(w); }
#define WG_LOGWARN5(x,y,z,w,xx,yy) if(_WIFI_GENERIC_LOGLEVEL_>1) { WG_PRINT_MARK; WG_PRINT(x); WG_PRINT(y); WG_PRINT(z); WG_PRINT(w); WG_PRINT(xx); WG_PRINTLN(yy); }

////////////////////////////////////////////////////////////////////////////////////////////

#define WG_LOGINFO0(x)     if(_WIFI_GENERIC_LOGLEVEL_>2) { WG_PRINT(x); }
#define WG_LOGINFO(x)      if(_WIFI_GENERIC_LOGLEVEL_>2) { WG_PRINT_MARK; WG_PRINTLN(x); }
#define WG_LOGINFO1(x,y)   if(_WIFI_GENERIC_LOGLEVEL_>2) { WG_PRINT_MARK; WG_PRINT(x); WG_PRINTLN(y); }
#define WG_LOGINFO2(x,y,z) if(_WIFI_GENERIC_LOGLEVEL_>3) { WG_PRINT_MARK; WG_PRINT(x); WG_PRINT(y); WG_PRINTLN(z); }
#define WG_LOGINFO3(x,y,z,w) if(_WIFI_GENERIC_LOGLEVEL_>3) { WG_PRINT_MARK; WG_PRINT(x); WG_PRINT(y); WG_PRINT(z); WG_PRINTLN(w); }
#define WG_LOGINFO5(x,y,z,w,xx,yy) if(_WIFI_GENERIC_LOGLEVEL_>2) { WG_PRINT_MARK; WG_PRINT(x); WG_PRINT(y); WG_PRINT(z); WG_PRINT(w); WG_PRINT(xx); WG_PRINTLN(yy); }

////////////////////////////////////////////////////////////////////////////////////////////

#define WG_LOGDEBUG0(x)     if(_WIFI_GENERIC_LOGLEVEL_>3) { WG_PRINT(x); }
#define WG_LOGDEBUG(x)      if(_WIFI_GENERIC_LOGLEVEL_>3) { WG_PRINT_MARK; WG_PRINTLN(x); }
#define WG_LOGDEBUG1(x,y)   if(_WIFI_GENERIC_LOGLEVEL_>3) { WG_PRINT_MARK; WG_PRINT(x); WG_PRINTLN(y); }
#define WG_LOGDEBUG2(x,y,z) if(_WIFI_GENERIC_LOGLEVEL_>3) { WG_PRINT_MARK; WG_PRINT(x); WG_PRINT(y); WG_PRINTLN(z); }
#define WG_LOGDEBUG3(x,y,z,w) if(_WIFI_GENERIC_LOGLEVEL_>3) { WG_PRINT_MARK; WG_PRINT(x); WG_PRINT(y); WG_PRINT(z); WG_PRINTLN(w); }
#define WG_LOGDEBUG5(x,y,z,w,xx,yy) if(_WIFI_GENERIC_LOGLEVEL_>3) { WG_PRINT_MARK; WG_PRINT(x); WG_PRINT(y); WG_PRINT(z); WG_PRINT(w); WG_PRINT(xx); WG_PRINTLN(yy); }

////////////////////////////////////////////////////////////////////////////////////////////

#endif    //WiFiManager_Generic_Lite_Debug_h
