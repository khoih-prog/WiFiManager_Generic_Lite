/****************************************************************************************************************************
  defines.h for STM32_WiFiNINA.ino
  For STM32 boards using WIFI_GENERIC Modules/Shields, using much less code to support boards with smaller memory
  
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

#if ( defined(STM32F0) || defined(STM32F1)  || defined(STM32F2) || defined(STM32F3)  ||defined(STM32F4) || defined(STM32F7) || \
      defined(STM32L0) || defined(STM32L1)  || defined(STM32L4) || defined(STM32H7)  ||defined(STM32G0) || defined(STM32G4) || \
      defined(STM32WB) || defined(STM32MP1) || defined(STM32L5) )
  #if defined(WIFI_GENERIC_USE_STM32)
    #undef WIFI_GENERIC_USE_STM32
    #undef WIFI_USE_STM32
  #endif
  #define WIFI_GENERIC_USE_STM32      true
  #define WIFI_USE_STM32              true
#else
  #error This code is intended to run on STM32 platform! Please check your Tools->Board setting.  
#endif

#if WIFI_GENERIC_USE_STM32
  #if defined(STM32F0)
    #warning STM32F0 board selected
    #define BOARD_TYPE  "STM32F0"
  #elif defined(STM32F1)
    #warning STM32F1 board selected
    #define BOARD_TYPE  "STM32F1"
  #elif defined(STM32F2)
    #warning STM32F2 board selected
    #define BOARD_TYPE  "STM32F2"
  #elif defined(STM32F3)
    #warning STM32F3 board selected
    #define BOARD_TYPE  "STM32F3"
  #elif defined(STM32F4)
    #warning STM32F4 board selected
    #define BOARD_TYPE  "STM32F4"
  #elif defined(STM32F7)

    #if defined(ARDUINO_NUCLEO_F767ZI)
      #warning Nucleo-144 NUCLEO_F767ZI board selected, using HardwareSerial Serial1 @ pin D0/RX and D1/TX
      // RX TX
      HardwareSerial Serial1(D0, D1);
    #else
    
      #warning STM32F7 board selected
      #define BOARD_TYPE  "STM32F7"

    #endif
    
  #elif defined(STM32L0)
    #if defined(ARDUINO_NUCLEO_L053R8)
      #warning Nucleo-64 NUCLEO_L053R8 board selected, using HardwareSerial Serial1 @ pin D0/RX and D1/TX
      // RX TX
      HardwareSerial Serial1(D0, D1);   // (PA3, PA2);
    #else
    
      #warning STM32L0 board selected
      #define BOARD_TYPE  "STM32L0"

    #endif
    
  #elif defined(STM32L1)
    #warning STM32L1 board selected
    #define BOARD_TYPE  "STM32L1"
  #elif defined(STM32L4)
    #warning STM32L4 board selected
    #define BOARD_TYPE  "STM32L4"
  #elif defined(STM32L5)
    #warning STM32L5 board selected
    #define BOARD_TYPE  "STM32L5"  
  #elif defined(STM32H7)
    #warning STM32H7 board selected
    #define BOARD_TYPE  "STM32H7"
  #elif defined(STM32G0)
    #warning STM32G0 board selected
    #define BOARD_TYPE  "STM32G0"
  #elif defined(STM32G4)
    #warning STM32G4 board selected
    #define BOARD_TYPE  "STM32G4"
  #elif defined(STM32WB)
    #warning STM32WB board selected
    #define BOARD_TYPE  "STM32WB"
  #elif defined(STM32MP1)
    #warning STM32MP1 board selected
    #define BOARD_TYPE  "STM32MP1"
  #else
    #warning STM32 unknown board selected
    #define BOARD_TYPE  "STM32 Unknown"
  #endif
#else
  // For Mega
  #define BOARD_TYPE      "AVR Mega"
#endif

#ifndef BOARD_NAME
  #define BOARD_NAME    BOARD_TYPE
#endif

// Start location in EEPROM to store config data. Default 0
// Config data Size currently is 128 bytes)
#define EEPROM_START      0

/////////////////////////////////////////////

// Add customs headers from v1.1.0
#define USING_CUSTOMS_STYLE           true
#define USING_CUSTOMS_HEAD_ELEMENT    true
#define USING_CORS_FEATURE            true

/////////////////////////////////////////////

#define USE_WIFI_NINA             false
#define USE_WIFI101               false
#define USE_WIFI_CUSTOM           true

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

  // For STM32
  #warning EspSerial using SERIAL_PORT_HARDWARE, can be Serial or Serial1. See your board variant.h
  #define EspSerial     SERIAL_PORT_HARDWARE    //Serial1

  #include "ESP8266_AT_WebServer.h"

  #define USE_ESP_AT_SHIELD       true
  #define WiFiWebServer ESP8266_AT_WebServer
  
#else

  #define SHIELD_TYPE     "Default WiFi using WiFi Library"
  #warning Using fallback WiFi.h Library defined in WiFiWebServer Library.
  
#endif

/////////////////////////////////////////////

// Permit running CONFIG_TIMEOUT_RETRYTIMES_BEFORE_RESET times before reset hardware
// to permit user another chance to config. Only if Config Data is valid.
// If Config Data is invalid, this has no effect as Config Portal will persist
#define RESET_IF_CONFIG_TIMEOUT                   true

// Permitted range of user-defined RETRY_TIMES_RECONNECT_WIFI between 2-5 times
#define RETRY_TIMES_RECONNECT_WIFI                3

// Permitted range of user-defined CONFIG_TIMEOUT_RETRYTIMES_BEFORE_RESET between 2-100
#define CONFIG_TIMEOUT_RETRYTIMES_BEFORE_RESET    5

// Config Timeout 120s (default 60s). Applicable only if Config Data is Valid
#define CONFIG_TIMEOUT                      120000L

/////////////////////////////////////////////

// Permit input only one set of WiFi SSID/PWD. The other can be "NULL or "blank"
// Default is false (if not defined) => must input 2 sets of SSID/PWD
#define REQUIRE_ONE_SET_SSID_PW       false

#define USE_DYNAMIC_PARAMETERS        true

/////////////////////////////////////////////

#define SCAN_WIFI_NETWORKS                  true

// To be able to manually input SSID, not from a scanned SSID lists
#define MANUAL_SSID_INPUT_ALLOWED           true

/////////////////////////////////////////////

#if (USE_WIFI_CUSTOM && USE_ESP_AT_SHIELD)
  // ESP-AT can't use longer than 2K HTML and DYNAMIC_PARAMETERS
  #undef USE_DYNAMIC_PARAMETERS
  #define USE_DYNAMIC_PARAMETERS                   false
  #warning Disable USE_DYNAMIC_PARAMETERS for ESP_AT_SHIELD

  // From 2-6 to keep HTML short for ESP8266-AT. Limited 6 in WiFiEspAT library anyway
  #define MAX_SSID_IN_LIST                  4

#else

  // From 2-15
  #define MAX_SSID_IN_LIST                  8
#endif

/////////////////////////////////////////////

#include <WiFiManager_Generic_Lite_STM32.h>

#define HOST_NAME   "STM32-Master-Controller"

#endif      //defines_h
