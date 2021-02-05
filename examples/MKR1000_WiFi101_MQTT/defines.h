/****************************************************************************************************************************
  defines.h for SAMD_WiFiNINA_MQTT.ino
  For SAMD 21 MKR1000 boards using WiFi101 Modules/Shields
  
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

#if ( defined(ARDUINO_SAMD_MKR1000) || defined(ARDUINO_SAMD_MKRWIFI1010) )
  #if defined(WIFI_GENERIC_USE_SAMD)
    #undef WIFI_GENERIC_USE_SAMD
    #undef WIFI_USE_SAMD
  #endif
  #define WIFI_GENERIC_USE_SAMD      true
  #define WIFI_USE_SAMD          true
#else
  #error This code is intended to run only on the SAMD boards using WINC1500 and WiFi101 ! Please check your Tools->Board setting.
#endif

#if defined(WIFI_GENERIC_USE_SAMD)

  #if defined(ARDUINO_SAMD_MKR1000)
    #define BOARD_TYPE      "SAMD MKR1000"
  #elif defined(ARDUINO_SAMD_MKRWIFI1010)
    #define BOARD_TYPE      "SAMD MKRWIFI1010"
  #else
    #define BOARD_TYPE      "SAMD Unknown"
  #endif

#endif

// Start location in EEPROM to store config data. Default 0
// Config data Size currently is 128 bytes)
#define EEPROM_START              0
#define EEPROM_SIZE               (2 * 1024)

/////////////////////////////////////////////

#define USE_WIFI101            true

#if defined(USE_WIFI_NINA)
  #undef USE_WIFI_NINA
#endif

#define USE_WIFI_NINA           false

#define SHIELD_TYPE             "WINC1500 using WiFi101 Library"
#warning Using WiFi101 Library

/////////////////////////////////////////////

// Force some params in Blynk, only valid for library version 1.0.1 and later
#define TIMEOUT_RECONNECT_WIFI                    10000L
#define RESET_IF_CONFIG_TIMEOUT                   true
#define CONFIG_TIMEOUT_RETRYTIMES_BEFORE_RESET    5

// Config Timeout 120s (default 60s)
#define CONFIG_TIMEOUT                            120000L

#define USE_DYNAMIC_PARAMETERS              true

#include <WiFiManager_Generic_Lite_SAMD.h>

#define HOST_NAME   "SAMD-MQTT-Controller"

#ifdef LED_BUILTIN
  #define LED_PIN     LED_BUILTIN
#else
  #define LED_PIN     13
#endif

#endif      //defines_h
