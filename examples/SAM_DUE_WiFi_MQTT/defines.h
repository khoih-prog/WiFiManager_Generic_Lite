/****************************************************************************************************************************
  defines.h
  For SAM DUE boards using WIFI_GENERIC Modules/Shields, using much less code to support boards with smaller memory
  
  WiFiManager_Generic_WM_Lite is a library for the Mega, Teensy, SAM DUE, SAMD and STM32 boards 
  (https://github.com/khoih-prog/WiFiManager_Generic_Lite) to enable store Credentials in EEPROM/LittleFS for easy 
  configuration/reconfiguration and autoconnect/autoreconnect of WiFi and other services without Hardcoding.
  
  Built by Khoi Hoang https://github.com/khoih-prog/WiFiManager_Generic_Lite
  Licensed under MIT license         
 *****************************************************************************************************************************/

#ifndef defines_h
#define defines_h

/* Comment this out to disable prints and save space */
#define DEBUG_WIFI_WEBSERVER_PORT     Serial
#define WIFI_GENERIC_DEBUG_OUTPUT     Serial

#define _WIFI_GENERIC_LOGLEVEL_       1

#define DRD_GENERIC_DEBUG             true

#if ( defined(ARDUINO_SAM_DUE) || defined(__SAM3X8E__) )
  #if defined(WIFI_GENERIC_USE_SAM_DUE)
    #undef WIFI_GENERIC_USE_SAM_DUE
  #endif
  #define WIFI_GENERIC_USE_SAM_DUE      true
  #warning Use SAM_DUE architecture
#endif

#if ( defined(ESP8266) || defined(ESP32) || defined(ARDUINO_AVR_MEGA2560) || defined(ARDUINO_AVR_MEGA) || \
      defined(CORE_TEENSY) || defined(CORE_TEENSY) || !(WIFI_GENERIC_USE_SAM_DUE) )
  #error This code is intended to run on the SAM DUE platform! Please check your Tools->Board setting.
#endif

#if defined(WIFI_GENERIC_USE_SAM_DUE)
  // For SAM DUE
  #if defined(ARDUINO_SAM_DUE)
    #define BOARD_TYPE      "SAM DUE"
  #elif defined(__SAM3X8E__)
    #define BOARD_TYPE      "SAM SAM3X8E"
  #else
    #define BOARD_TYPE      "SAM Unknown"
  #endif
#endif

#ifndef BOARD_NAME
  #define BOARD_NAME    BOARD_TYPE
#endif

// Start location in EEPROM to store config data. Default 0
// Config data Size currently is 128 bytes)
#define EEPROM_START      0

/////////////////////////////////////////////

#define USE_WIFI_NINA             false
#define USE_WIFI101               true
#define USE_WIFI_CUSTOM           false

#if USE_WIFI_NINA

  #if defined(USE_WIFI101)
    #undef USE_WIFI101
  #endif
  
  #define USE_WIFI101           false

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

  #include "WiFiEspAT.h"
  
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

#include <WiFiManager_Generic_Lite_DUE.h>

#define HOST_NAME   "DUE-MQTT-Controller"

#ifdef LED_BUILTIN
  #define LED_PIN     LED_BUILTIN
#else
  #define LED_PIN     13
#endif

#endif      //defines_h
