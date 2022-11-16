/*******************************************************************************************************************************
  WiFiManager_Generic_Lite.h

  WiFiManager_Generic_Lite is a library for the Teensy, nRF52, RP2040, SAMD, SAM DUE, RTL8720 and STM32 boards
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

#ifndef WiFiManager_Generic_Lite_h
#define WiFiManager_Generic_Lite_h

#if  ( defined(ARDUINO_SAMD_ZERO) || defined(ARDUINO_SAMD_MKR1000) || defined(ARDUINO_SAMD_MKRWIFI1010) \
    || defined(ARDUINO_SAMD_NANO_33_IOT) || defined(ARDUINO_SAMD_MKRFox1200) || defined(ARDUINO_SAMD_MKRWAN1300) || defined(ARDUINO_SAMD_MKRWAN1310) \
    || defined(ARDUINO_SAMD_MKRGSM1400) || defined(ARDUINO_SAMD_MKRNB1500) || defined(ARDUINO_SAMD_MKRVIDOR4000) \
    || defined(ARDUINO_SAMD_CIRCUITPLAYGROUND_EXPRESS) || defined(__SAMD51__) || defined(__SAMD51J20A__) \
    || defined(__SAMD51J19A__) || defined(__SAMD51G19A__) || defined(__SAMD51P19A__)  \
    || defined(__SAMD21E15A__) || defined(__SAMD21E16A__) || defined(__SAMD21E17A__) || defined(__SAMD21E18A__) \
    || defined(__SAMD21G15A__) || defined(__SAMD21G16A__) || defined(__SAMD21G17A__) || defined(__SAMD21G18A__) \
    || defined(__SAMD21J15A__) || defined(__SAMD21J16A__) || defined(__SAMD21J17A__) || defined(__SAMD21J18A__) )

#include "WiFiManager_Generic_Lite_SAMD.h"

#elif ( defined(NRF52840_FEATHER) || defined(NRF52832_FEATHER) || defined(NRF52_SERIES) || defined(ARDUINO_NRF52_ADAFRUIT) || \
      defined(NRF52840_FEATHER_SENSE) || defined(NRF52840_ITSYBITSY) || defined(NRF52840_CIRCUITPLAY) || defined(NRF52840_CLUE) || \
      defined(NRF52840_METRO) || defined(NRF52840_PCA10056) || defined(PARTICLE_XENON) || defined(NINA_B302_ublox) || defined(NINA_B112_ublox) )

#include "WiFiManager_Generic_Lite_nRF52.h"

#elif ( defined(NANO_RP2040_CONNECT)    || defined(ARDUINO_ARCH_RP2040) || defined(ARDUINO_RASPBERRY_PI_PICO) || \
      defined(ARDUINO_GENERIC_RP2040) || defined(ARDUINO_ADAFRUIT_FEATHER_RP2040) )

#include "WiFiManager_Generic_Lite_RP2040.h"

#elif ( defined(STM32F0) || defined(STM32F1)   || defined(STM32F2) || defined(STM32F3)  ||defined(STM32F4) || defined(STM32F7) || \
      defined(STM32L0) || defined(STM32L1)   || defined(STM32L4) || defined(STM32H7)  ||defined(STM32G0) || defined(STM32G4) || \
      defined(STM32WB) || defined(STM32MP1)  || defined(STM32L5) )

#include "WiFiManager_Generic_Lite_STM32.h"

#elif ( defined(CORE_TEENSY) )

#include "WiFiManager_Generic_Lite_Teensy.h"

#elif ( defined(ARDUINO_SAM_DUE) || defined(__SAM3X8E__) )

#include "WiFiManager_Generic_Lite_DUE.h"

#elif defined(CONFIG_PLATFORM_8721D)

#include "WiFiManager_Generic_Lite_RTL8720.h"

#else

#error Not supported board

#endif

#ifndef WIFI_MANAGER_GENERIC_LITE_VERSION
  #define WIFI_MANAGER_GENERIC_LITE_VERSION            "WiFiManager_Generic_Lite v1.8.0"

  #define WIFI_MANAGER_GENERIC_LITE_VERSION_MAJOR      1
  #define WIFI_MANAGER_GENERIC_LITE_VERSION_MINOR      8
  #define WIFI_MANAGER_GENERIC_LITE_VERSION_PATCH      0

  #define WIFI_MANAGER_GENERIC_LITE_VERSION_INT        1008000

#endif


#endif    //WiFiManager_Generic_Lite_h
