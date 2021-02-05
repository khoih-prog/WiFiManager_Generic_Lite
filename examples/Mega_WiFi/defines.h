/****************************************************************************************************************************
  defines.h for Mega_WiFiNINA.ino
  For AVR boards using WIFI_GENERIC Modules/Shields, using much less code to support boards with smaller memory

  WiFiManager_Generic_WM_Lite is a library for the Mega, Teensy, SAM DUE, SAMD and STM32 boards 
  (https://github.com/khoih-prog/WiFiManager_Generic_Lite) to enable store Credentials in EEPROM/LittleFS for easy 
  configuration/reconfiguration and autoconnect/autoreconnect of WiFi and other services without Hardcoding.
  
  Built by Khoi Hoang https://github.com/khoih-prog/WiFiManager_Generic_Lite
  Licensed under MIT license       
 *****************************************************************************************************************************/

#ifndef defines_h
#define defines_h

/* Comment this out to disable prints and save space */
#define DEBUG_WIFI_WEBSERVER_PORT Serial
#define WIFI_GENERIC_DEBUG_OUTPUT     Serial

#define WIFI_GENERIC_DEBUG            false //true

#define DRD_GENERIC_DEBUG         false //true

#if !( defined(ARDUINO_AVR_ADK) || defined(ARDUINO_AVR_MEGA) || defined(ARDUINO_AVR_MEGA2560) )
  #error This code is intended to run only on the Arduino Mega ADK/1280/2560 boards ! Please check your Tools->Board setting.
#endif

#if defined(ARDUINO_AVR_MEGA2560)
  #define BOARD_TYPE      "AVR Mega2560"
#elif defined(ARDUINO_AVR_MEGA)
  #define BOARD_TYPE      "AVR Mega"
#elif defined(ARDUINO_AVR_ADK)
  #define BOARD_TYPE      "AVR Mega ADK"  
#else
  #define BOARD_TYPE      "AVR Mega Unknown"  
#endif

// Start location in EEPROM to store config data. Default 0
// Config data Size currently is 128 bytes)
#define EEPROM_START      0

#ifndef BOARD_NAME
  #define BOARD_NAME    BOARD_TYPE
#endif

/////////////////////////////////////////////

#define USE_WIFI_NINA             false
#define USE_WIFI101               true
#define USE_WIFI_CUSTOM           false

#if USE_WIFI_NINA

  #warning Using WIFININA_Generic Library
  #define SHIELD_TYPE     "WiFiNINA using WiFiNINA_Generic Library"

  #include "WiFiNINA_Pinout_Generic.h"
  
#elif USE_WIFI101

  #if defined(USE_WIFI_NINA)
    #undef USE_WIFI_NINA
  #endif
  
  #define USE_WIFI_NINA           false

  #define SHIELD_TYPE     "WINC1500 using WiFi101 Library"
  #warning Using WiFi101 Library

#elif USE_WIFI_CUSTOM

  #if defined(USE_WIFI_NINA)
    #undef USE_WIFI_NINA
  #endif
  
  #define USE_WIFI_NINA           false
  
  #if defined(USE_WIFI101)
    #undef USE_WIFI101
  #endif
  
  #define USE_WIFI101             false

  #define SHIELD_TYPE     "Custom using Custom WiFi Library"
  #warning Using Custom WiFi Library. You must include here or compile error
  
#else

  #define SHIELD_TYPE     "Default WiFi using WiFi Library"
  #warning Using fallback WiFi.h Library defined in WiFiWebServer Library.
  
#endif

/////////////////////////////////////////////

// Force some params in Blynk, only valid for library version 1.0.1 and later
#define TIMEOUT_RECONNECT_WIFI                    10000L
#define RESET_IF_CONFIG_TIMEOUT                   true
#define CONFIG_TIMEOUT_RETRYTIMES_BEFORE_RESET    5

// Config Timeout 120s (default 60s)
#define CONFIG_TIMEOUT                            120000L

#define USE_DYNAMIC_PARAMETERS              true

#include <WiFiManager_Generic_Lite.h>

#define HOST_NAME   "AVR-Master-Controller"

#endif      //defines_h
