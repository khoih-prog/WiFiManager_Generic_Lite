## WiFiManager_Generic_Lite (Light Weight Credentials / WiFi Manager for Generic WiFi (WiFiNINA, WiFi101, WiFiEsp, etc.)  modules/shields)

[![arduino-library-badge](https://www.ardu-badge.com/badge/WiFiManager_Generic_Lite.svg?)](https://www.ardu-badge.com/WiFiManager_Generic_Lite)
[![GitHub release](https://img.shields.io/github/release/khoih-prog/WiFiManager_Generic_Lite.svg)](https://github.com/khoih-prog/WiFiManager_Generic_Lite/releases)
[![GitHub](https://img.shields.io/github/license/mashape/apistatus.svg)](https://github.com/khoih-prog/WiFiManager_Generic_Lite/blob/main/LICENSE)
[![contributions welcome](https://img.shields.io/badge/contributions-welcome-brightgreen.svg?style=flat)](#Contributing)
[![GitHub issues](https://img.shields.io/github/issues/khoih-prog/WiFiManager_Generic_Lite.svg)](http://github.com/khoih-prog/WiFiManager_Generic_Lite/issues)

<a href="https://www.buymeacoffee.com/khoihprog6" title="Donate to my libraries using BuyMeACoffee"><img src="https://cdn.buymeacoffee.com/buttons/v2/default-yellow.png" alt="Donate to my libraries using BuyMeACoffee" style="height: 50px !important;width: 181px !important;" ></a>
<a href="https://www.buymeacoffee.com/khoihprog6" title="Donate to my libraries using BuyMeACoffee"><img src="https://img.shields.io/badge/buy%20me%20a%20coffee-donate-orange.svg?logo=buy-me-a-coffee&logoColor=FFDD00" style="height: 20px !important;width: 200px !important;" ></a>


---
---

## Table of Contents

* [Important Notes about Nano_RP2040_Connect](#important-notes-about-nano_rp2040_connect)
* [Why do we need this WiFiManager_Generic_Lite library](#why-do-we-need-this-wifimanager_generic_lite-library)
  * [Features](#features)
  * [WiFiMulti_Generic library usage](#WiFiMulti_Generic-library-usage)
  * [Currently supported Boards](#currently-supported-boards)
  * [Currently supported WiFi shields/modules](#currently-supported-wifi-shieldsmodules)
* [Changelog](changelog.md)
* [Prerequisites](#prerequisites)
* [Installation](#installation)
  * [Use Arduino Library Manager](#use-arduino-library-manager)
  * [Manual Install](#manual-install)
  * [VS Code & PlatformIO](#vs-code--platformio)
* [Packages' Patches](#packages-patches)
  * [1. For Adafruit nRF52840 and nRF52832 boards](#1-for-adafruit-nRF52840-and-nRF52832-boards)
  * [2. For Teensy boards](#2-for-teensy-boards)
  * [3. For Arduino SAM DUE boards](#3-for-arduino-sam-due-boards)
  * [4. For Arduino SAMD boards](#4-for-arduino-samd-boards)
      * [For core version v1.8.10+](#for-core-version-v1810)
      * [For core version v1.8.9-](#for-core-version-v189-)
  * [5. For Adafruit SAMD boards](#5-for-adafruit-samd-boards)
  * [6. For Seeeduino SAMD boards](#6-for-seeeduino-samd-boards)
  * [7. For STM32 boards](#7-for-stm32-boards) 
    * [7.1. For STM32 boards to use LAN8720](#71-for-stm32-boards-to-use-lan8720)
    * [7.2. For STM32 boards to use Serial1](#72-for-stm32-boards-to-use-serial1)
  * [8. For RP2040-based boards using Earle Philhower arduino-pico core](#8-for-rp2040-based-boards-using-earle-philhower-arduino-pico-core)
    * [8.1. To use BOARD_NAME](#81-to-use-board_name)
    * [8.2. To avoid compile error relating to microsecondsToClockCycles](#82-to-avoid-compile-error-relating-to-microsecondstoclockcycles)
  * [9. For Portenta_H7 boards using Arduino IDE in Linux](#9-for-portenta_h7-boards-using-arduino-ide-in-linux)
  * [10. For RTL8720DN boards using AmebaD core](#10-for-rtl8720dn-boards-using-amebad-core)
  * [11. For SAMD21 and SAMD51 boards using ArduinoCore-fab-sam core](#11-For-SAMD21-and-SAMD51-boards-using-ArduinoCore-fab-sam-core)
  * [12. For Seeeduino RP2040 boards](#12-For-Seeeduino-RP2040-boards)
* [How It Works](#how-it-works)
* [How to use](#how-to-use)
  * [ 1. Basic usage](#1-basic-usage)
  * [ 2. Add custom parameters](#2-add-custom-parameters)
  * [ 3. Not using custom parameters](#3-not-using-custom-parameters)
  * [ 4. To open Config Portal](#4-to-open-config-portal)
  * [ 5. To use different AP WiFi Channel](#5-to-use-different-ap-wifi-channel)
  * [ 6. To use different static AP IP from default](#6-to-use-different-static-ap-ip-from-default)
  * [ 7. To use custom DHCP HostName](#7-to-use-custom-dhcp-hostname)
  * [ 8. To use custom HTML Style](#8-to-use-custom-html-style)
  * [ 9. To use custom Head Elements](#9-to-use-custom-head-elements)
  * [10. To use CORS Header](#10-to-use-cors-header)
  * [11. To use and input only one set of WiFi SSID and PWD](#11-to-use-and-input-only-one-set-of-wifi-ssid-and-pwd)
    * [11.1 If you need to use and input only one set of WiFi SSID/PWD](#111-if-you-need-to-use-and-input-only-one-set-of-wifi-ssidpwd)
    * [11.2 If you need to use both sets of WiFi SSID/PWD](#112-if-you-need-to-use-both-sets-of-wifi-ssidpwd)
  * [12. To enable auto-scan of WiFi networks for selection in Configuration Portal](#12-to-enable-auto-scan-of-wifi-networks-for-selection-in-configuration-portal)
    * [12.1 Enable auto-scan of WiFi networks for selection in Configuration Portal](#121-enable-auto-scan-of-wifi-networks-for-selection-in-configuration-portal)
    * [12.2 Disable manually input SSIDs](#122-disable-manually-input-ssids)
    * [12.3 Select maximum number of SSIDs in the list](#123-select-maximum-number-of-ssids-in-the-list)
  * [13. To avoid blocking in loop when WiFi is lost](#13-To-avoid-blocking-in-loop-when-wifi-is-lost)
    * [13.1 Max times to try WiFi per loop](#131-max-times-to-try-wifi-per-loop)
    * [13.2 Interval between reconnection WiFi if lost](#132-interval-between-reconnection-wifi-if-lost)
  * [14. Not using Board_Name on Config_Portal](#14-Not-using-Board_Name-on-Config_Portal)
  * [15. How to use CONFIG_MODE_LED](#15-How-to-use-CONFIG_MODE_LED)
* [Examples](#examples)
  * [ 1. MKR1000_WiFi101](examples/MKR1000_WiFi101)
  * [ 2. MKR1000_WiFi101_MQTT](examples/MKR1000_WiFi101_MQTT)
  * [ 3. nRF52_WiFi](examples/nRF52_WiFi)
  * [ 4. nRF52_WiFi_MQTT](examples/nRF52_WiFi_MQTT)
  * [ 5. SAM_DUE_WiFi](examples/SAM_DUE_WiFi)
  * [ 6. SAM_DUE_WiFi_MQTT](examples/SAM_DUE_WiFi_MQTT) 
  * [ 7. SAMD_WiFi](examples/SAMD_WiFi)
  * [ 8. SAMD_WiFi_MQTT](examples/SAMD_WiFi_MQTT)
  * [ 9. STM32_WiFi](examples/STM32_WiFi)
  * [10. STM32_WiFi_MQTT](examples/STM32_WiFi_MQTT)
  * [11. Teensy_WiFi](examples/Teensy_WiFi)
  * [12. Teensy_WiFi_MQTT](examples/Teensy_WiFi_MQTT)
  * [13. RP2040_WiFi](examples/RP2040_WiFi) **New**
  * [14. RP2040_WiFi_MQTT](examples/RP2040_WiFi_MQTT) **New**
* [So, how it works?](#so-how-it-works)
  * [1. Without SCAN_WIFI_NETWORKS](#1-without-scan_wifi_networks)
  * [2. With SCAN_WIFI_NETWORKS](#2-with-scan_wifi_networks)
  * [3. With SCAN_WIFI_NETWORKS for ESP8266-AT and ESP32-AT shield](#3-with-scan_wifi_networks-for-esp8266-at-and-esp32-at-shield)
* [Important Notes](#important-notes)
* [How to use default Credentials and have them pre-loaded onto Config Portal](#how-to-use-default-credentials-and-have-them-pre-loaded-onto-config-portal)
  * [1. To always load Default Credentials and override Config Portal data](#1-to-always-load-default-credentials-and-override-config-portal-data)
  * [2. To load Default Credentials when there is no valid Credentials](#2-to-load-default-credentials-when-there-is-no-valid-credentials)
  * [3. Example of Default Credentials](#3-example-of-default-credentials)
* [How to add dynamic parameters from sketch](#how-to-add-dynamic-parameters-from-sketch)
* [Important Notes for using Dynamic Parameters' ids](#important-notes-for-using-dynamic-parameters-ids)
* [Example SAMD_WiFi](#example-samd_wifi)
  * [1. File SAMD_WiFi.ino](#1-file-samd_wifiino)
  * [2. File defines.h](#2-file-definesh)
  * [3. File Credentials.h](#3-file-credentialsh)
  * [4. File dynamicParams.h](#4-file-dynamicparamsh)
* [Debug Terminal Output Samples](#debug-terminal-output-samples)
  * [1. SAMD_WiFi example on Nano-33 IoT](#1-samd_wifi-example-on-nano-33-iot) 
    * [1.1 Open Config Portal](#11-open-config-portal)
    * [1.2 Received data from Config Portal](#12-received-data-from-config-portal)
    * [1.3 Got valid Credential from Config Portal, then connected to WiFi](#13-got-valid-credential-from-config-portal-then-connected-to-wifi)
    * [1.4 Lost a WiFi and autoconnect to another WiFi AP](#14-lost-a-wifi-and-autoconnect-to-another-wifi-ap)
    * [1.5 Reopen Config Portal if can't connect to any of the 2 WiFi APs](#15-reopen-config-portal-if-cant-connect-to-any-of-the-2-wifi-aps)
    * [1.6 DRD Not Detected](#16-drd-not-detected) 
    * [1.7 DRD detected and Config Portal is forcefully opened](#17-drd-detected-and-config-portal-is-forcefully-opened)
  * [2. SAMD_WiFi on ITSYBITSY_M4 using Custom WiFi Library](#2-samd_wifi-on-itsybitsy_m4-using-custom-wifi-library) 
    * [2.1 Open Config Portal](#21-open-config-portal)
    * [2.2 Got valid Credential from Config Portal, then connected to WiFi](#22-got-valid-credential-from-config-portal-then-connected-to-wifi)
* [Debug](#debug)
* [Troubleshooting](#troubleshooting)
* [Issues](#issues)
* [TO DO](#to-do)
* [DONE](#done)
* [Contributions and Thanks](#contributions-and-thanks)
* [Contributing](#contributing)
* [License](#license)
* [Copyright](#copyright)

---
---

### Important Notes about Nano_RP2040_Connect

The LittleFS of the new **Nano_RP2040_Connect** board ( see [New board](pics/New_Board.png) ), using ISSI Flash chip, is currently not working with [`Arduino mbed_rp2040 core 2.4.1+`](https://github.com/arduino/ArduinoCore-mbed/releases/tag/2.4.1). Please downgrade to [`Arduino mbed_rp2040 core 2.3.1`](https://github.com/arduino/ArduinoCore-mbed/releases/tag/2.3.1)

Check [**RP2040 Connect board has faulty components in newest purchase** #318](https://github.com/arduino/ArduinoCore-mbed/issues/318#) for more information of when and how the issue will be fixed.

The old board ( see [Old board](pics/Old_Board.png) ), using Adesto Flash chip, is currently working with [`Arduino mbed_rp2040 core 2.4.1+`](https://github.com/arduino/ArduinoCore-mbed/releases/tag/2.4.1).

---
---

### Why do we need this [WiFiManager_Generic_Lite library](https://github.com/khoih-prog/WiFiManager_Generic_Lite)

#### Features

If you have used the full-fledge WiFiManager such as :

1. [`Tzapu WiFiManager`](https://github.com/tzapu/WiFiManager)
2. [`Ken Taylor WiFiManager`](https://github.com/kentaylor/WiFiManager)
3. [`Khoi Hoang ESP_WiFiManager`](https://github.com/khoih-prog/ESP_WiFiManager)

and have to write **complicated callback functions** to save custom parameters in SPIFFS/LittleFS/EEPROM, you'd appreciate the simplicity of this Light-Weight Credentials / WiFiManager.

This library is a Light Weight Credentials / WiFi Manager for Generic WiFi (WiFiNINA, WINC1500/WiFi101, WiFiEsp, etc.) modules/shields, specially designed to support **Teensy, SAM DUE, SAMD21 (Nano-33 IoT, Itsy-Bitsy M0, etc), SAMD51 (Itsy-Bitsy M4, Metro M4, Grand Central M4, Feather M4 Express, etc.), STM32F (F1, F2, F3, F4, F7, Nucleo-144, etc.), nRF52 (Adafruit NRF52840_FEATHER, NRF52832_FEATHER, NRF52840_FEATHER_SENSE, NRF52840_ITSYBITSY, NRF52840_CIRCUITPLAY, NRF52840_CLUE, NRF52840_METRO, NRF52840_PCA10056, PARTICLE_XENON, NINA_B302_ublox, NINA_B112_ublox, etc.), RP2040-based (Nano RP2040 Connect, RASPBERRY_PI_PICO, ADAFRUIT_FEATHER_RP2040 and GENERIC_RP2040), etc. boards running WiFiNINA modules/shields.** with smaller memory (64+K bytes)

The AVR-family boards (UNO, Nano, Mega, etc.) are **not supported** as they don't have enough memory to run Config Portal WebServer.

This is a Credentials / WiFi Connection Manager, permitting the addition of custom parameters to be configured in Config Portal. The parameters then will be saved automatically, **without the complicated callback functions** to handle data saving / retrieving.

You can also specify DHCP HostName, static AP and STA IP. Use much less memory compared to full-fledge WiFiManager. Config Portal will be auto-adjusted to match the number of dynamic custom parameters. Credentials are saved in EEPROM, (emulated-)EEPROM, FlashStorage_SAMD, FlashStorage_STM32 or DueFlashStorage.

The web configuration portal, served from the `Generic WiFi modules/shields` is operating as an access point (AP) with configurable static IP address or use default IP Address of 192.168.4.1

New recent features:

- **MultiWiFi** feature for configuring/auto(re)connecting **Generic WiFi (WiFiNINA, WINC1500/WiFi101, WiFiEsp, etc.)** shields to the available MultiWiFi APs at runtime.
- **DoubleDetectDetector** feature to force Config Portal when double reset is detected within predetermined time, default 10s.
- **Powerful-yet-simple-to-use feature to enable adding dynamic custom parameters** from sketch and input using the same Config Portal. Config Portal will be auto-adjusted to match the number of dynamic parameters.
- Optional default **Credentials as well as Dynamic parameters to be optionally autoloaded into Config Portal** to use or change instead of manually input.
- Dynamic custom parameters to be saved **automatically in non-volatile memory, such as Teensy EEPROM, SAMD EEPROM-emulated FlashStorage_SAMD, STM32F/L/H/G/WB/MP1 EEPROM-emulated FlashStorage_STM32 or SAM DUE DueFlashStorage**.
- Configurable **Config Portal Title** to be either BoardName or default undistinguishable names.
- Examples are designed to separate Credentials / Defines / Dynamic Params / Code so that you can change Credentials / Dynamic Params quickly for each device.
- Control Config Portal from software or Virtual Switches
- To permit autoreset after configurable timeout if DRD/MRD or non-persistent forced-CP
- Use new nRF52, RP2040 LittleFS, SAMD FlashStorage_SAMD and STM32F/L/H/G/WB/MP1 FlashStorage_STM32 features
- **Scan WiFi networks** for selection in Configuration Portal

---

#### WiFiMulti_Generic library usage

The usage the new [WiFiMulti_Generic](https://github.com/khoih-prog/WiFiMulti_Generic) library to help connect to the best of **multi-WiFi APs**, with **auto-checking / auto-reconnecting** features when WiFi connection is lost.


---

#### Currently supported Boards

This [**WiFiManager_Generic_Lite** library](https://github.com/khoih-prog/WiFiManager_Generic_Lite) currently supports these following boards:

 1. **nRF52 boards**, such as **AdaFruit Feather nRF52832, nRF52840 Express, BlueFruit Sense, Itsy-Bitsy nRF52840 Express, Metro nRF52840 Express, NINA_B302_ublox, NINA_B112_ublox, etc.**
 
 2. **SAMD21**
  - Arduino SAMD21: ZERO, MKRs, NANO_33_IOT, etc.
  - Adafruit SAMD21 (M0): ItsyBitsy M0, Feather M0, Feather M0 Express, Metro M0 Express, Circuit Playground Express, Trinket M0, PIRkey, Hallowing M0, Crickit M0, etc.
  - Seeeduino:  LoRaWAN, Zero, Femto M0, XIAO M0, Wio GPS Board, etc.
  
 3. **SAMD51**
  - Adafruit SAMD51 (M4): Metro M4, Grand Central M4, ItsyBitsy M4, Feather M4 Express, Trellis M4, Metro M4 AirLift Lite, MONSTER M4SK Express, Hallowing M4, etc.
  - Seeeduino: Wio Terminal, Grove UI Wireless
  
 4. **SAM DUE** 
 5. **Teensy (4.1, 4.0, 3.6, 3.5, 3,2, 3.1, 3.0)**
 6. **STM32F/L/H/G/WB/MP1 boards (with 32+K Flash)**
  - Nucleo-144
  - Nucleo-64
  - Discovery
  - Generic STM32F0, STM32F1, STM32F2, STM32F3, STM32F4, STM32F7 (with 64+K Flash): x8 and up
  - STM32L0, STM32L1, STM32L4, STM32L5
  - STM32G0, STM32G4
  - STM32H7
  - STM32WB
  - STM32MP1
  - LoRa boards
  - 3-D printer boards
  - Generic Flight Controllers
  - Midatronics boards

 7. RP2040-based boards, such as **Nano RP2040 Connect**, using [**Arduino mbed OS for Nano boards**](https://github.com/arduino/ArduinoCore-mbed) or [**Earle Philhower's arduino-pico** core](https://github.com/earlephilhower/arduino-pico).

 8. RP2040-based boards, such as **RASPBERRY_PI_PICO, ADAFRUIT_FEATHER_RP2040 and GENERIC_RP2040**, using [**Arduino-mbed RP2040** core](https://github.com/arduino/ArduinoCore-mbed) or [**Earle Philhower's arduino-pico** core](https://github.com/earlephilhower/arduino-pico).

---

#### Currently supported WiFi shields/modules

1. WiFiNINA using [`WiFiNINA_Generic library v1.8.14-3+`](https://github.com/khoih-prog/WiFiNINA_Generic)
2. WiFi101 using [`WiFi101 library v0.16.1+`](https://github.com/arduino-libraries/WiFi101)
3. u-blox W101, W102 using [`WiFiNINA_Generic library`](https://github.com/khoih-prog/WiFiNINA_Generic)
4. ESP826-AT command using [`WiFiEspAT library v1.3.2+`](https://github.com/jandrassy/WiFiEspAT)
5. ESP8266/ESP32-AT command using [`ESP_AT_Lib library v1.4.1+`](https://github.com/khoih-prog/ESP_AT_Lib) and [`ESP8266_AT_WebServer`](ESP8266_AT_WebServer)


---
---

## Prerequisites

 1. [`Arduino IDE 1.8.19+` for Arduino](https://github.com/arduino/Arduino). [![GitHub release](https://img.shields.io/github/release/arduino/Arduino.svg)](https://github.com/arduino/Arduino/releases/latest)
 2. [`Arduino Core for STM32 v2.2.0+`](https://github.com/stm32duino/Arduino_Core_STM32) for STM32 boards. [![GitHub release](https://img.shields.io/github/release/stm32duino/Arduino_Core_STM32.svg)](https://github.com/stm32duino/Arduino_Core_STM32/releases/latest)
 3. [`Teensy core 1.56+`](https://www.pjrc.com/teensy/td_download.html) for Teensy (4.1, 4.0, 3.6, 3.5, 3,2, 3.1, 3.0, LC) boards
 4. [`Arduino SAM DUE core 1.6.12+`](https://github.com/arduino/ArduinoCore-sam) for SAM DUE ARM Cortex-M3 boards
 5. [`Arduino SAMD core 1.8.13+`](https://www.arduino.cc/en/Guide/ArduinoM0) for SAMD ARM Cortex-M0+ boards. [![GitHub release](https://img.shields.io/github/release/arduino/ArduinoCore-samd.svg)](https://github.com/arduino/ArduinoCore-samd/releases/latest)
 6. [`Adafruit SAMD core 1.7.10+`](https://www.adafruit.com/) for SAMD ARM Cortex-M0+ and M4 boards (Nano 33 IoT, etc.). [![GitHub release](https://img.shields.io/github/release/adafruit/ArduinoCore-samd.svg)](https://github.com/adafruit/ArduinoCore-samd/releases/latest)
 7. [`Seeeduino SAMD core 1.8.2+`](https://github.com/Seeed-Studio/ArduinoCore-samd) for SAMD21/SAMD51 boards (XIAO M0, Wio Terminal, etc.). [![Latest release](https://img.shields.io/github/release/Seeed-Studio/ArduinoCore-samd.svg)](https://github.com/Seeed-Studio/ArduinoCore-samd/releases/latest/)
 8. [`Adafruit nRF52 v1.3.0+`](https://www.adafruit.com) for nRF52 boards such as Adafruit NRF52840_FEATHER, NRF52832_FEATHER, NRF52840_FEATHER_SENSE, NRF52840_ITSYBITSY, NRF52840_CIRCUITPLAY, NRF52840_CLUE, NRF52840_METRO, NRF52840_PCA10056, PARTICLE_XENON, **NINA_B302_ublox**, etc. [![GitHub release](https://img.shields.io/github/release/adafruit/Adafruit_nRF52_Arduino.svg)](https://github.com/adafruit/Adafruit_nRF52_Arduino/releases/latest).
 9. [`Arduino mbed_rp2040 core 3.0.1+`](https://github.com/arduino/ArduinoCore-mbed) for Arduino (Use Arduino Board Manager) RP2040-based boards, such as **Arduino Nano RP2040 Connect, RASPBERRY_PI_PICO, etc.**. [![GitHub release](https://img.shields.io/github/release/arduino/ArduinoCore-mbed.svg)](https://github.com/arduino/ArduinoCore-mbed/releases/latest)
10. [`Earle Philhower's arduino-pico core v1.13.3+`](https://github.com/earlephilhower/arduino-pico) for RP2040-based boards such as **RASPBERRY_PI_PICO, ADAFRUIT_FEATHER_RP2040 and GENERIC_RP2040**, etc. [![GitHub release](https://img.shields.io/github/release/earlephilhower/arduino-pico.svg)](https://github.com/earlephilhower/arduino-pico/releases/latest)
11. [`Functional-Vlpp library v1.0.2+`](https://github.com/khoih-prog/functional-vlpp) to use server's lambda function. To install. check [![arduino-library-badge](https://www.ardu-badge.com/badge/Functional-Vlpp.svg?)](https://www.ardu-badge.com/Functional-Vlpp)
12. [`WiFiNINA_Generic library v1.8.14-3+`](https://github.com/khoih-prog/WiFiNINA_Generic). To install. check [![arduino-library-badge](https://www.ardu-badge.com/badge/WiFiNINA_Generic.svg?)](https://www.ardu-badge.com/WiFiNINA_Generic)
13. [`WiFiWebServer library v1.6.1+`](https://github.com/khoih-prog/WiFiWebServer). To install. check [![arduino-library-badge](https://www.ardu-badge.com/badge/WiFiWebServer.svg?)](https://www.ardu-badge.com/WiFiWebServer)
14. [`ESP8266_AT_WebServer library v1.5.4+`](https://github.com/khoih-prog/ESP8266_AT_WebServer) to be able to support ESP32-AT shields. To install, check [![arduino-library-badge](https://www.ardu-badge.com/badge/ESP8266_AT_WebServer.svg?)](https://www.ardu-badge.com/ESP8266_AT_WebServer)
15. [`ESP_AT_Lib library v1.4.1+`](https://github.com/khoih-prog/ESP_AT_Lib) if using ESP8288/ESP32-AT shields. To install, check [![arduino-library-badge](https://www.ardu-badge.com/badge/ESP_AT_Lib.svg?)](https://www.ardu-badge.com/ESP_AT_Lib).
16. [`Modified WiFi101 Library v0.16.1+`](https://github.com/khoih-prog/WiFi101) to use SAMD MKR1000, etc. boards with WiFi101.
17. [`WiFiEspAT library v1.3.2+`](https://github.com/jandrassy/WiFiEspAT) if using ESP8288/ESP32-AT shields. [![GitHub release](https://img.shields.io/github/release/jandrassy/WiFiEspAT.svg)](https://github.com/jandrassy/WiFiEspAT/releases/latest)
18. [`FlashStorage_SAMD library v1.3.2+`](https://github.com/khoih-prog/FlashStorage_SAMD) for SAMD21 and SAMD51 boards (ZERO, MKR, NANO_33_IOT, M0, M0 Pro, AdaFruit Itsy-Bitsy M4, etc.). [![GitHub release](https://img.shields.io/github/release/khoih-prog/FlashStorage_SAMD.svg)](https://github.com/khoih-prog/FlashStorage_SAMD/releases/latest)
19. [`FlashStorage_STM32F1 library v1.1.0+`](https://github.com/khoih-prog/FlashStorage_STM32F1) for STM32F1/F3 boards. To install. check [![arduino-library-badge](https://www.ardu-badge.com/badge/FlashStorage_STM32F1.svg?)](https://www.ardu-badge.com/FlashStorage_STM32F1)
20. [`FlashStorage_STM32 library v1.2.0+`](https://github.com/khoih-prog/FlashStorage_STM32) for STM32F/L/H/G/WB/MP1 boards. To install. check [![arduino-library-badge](https://www.ardu-badge.com/badge/FlashStorage_STM32.svg?)](https://www.ardu-badge.com/FlashStorage_STM32)
21. [`DueFlashStorage library v1.0.0+`](https://github.com/sebnil/DueFlashStorage) for SAM DUE. To install, check [![arduino-library-badge](https://www.ardu-badge.com/badge/DueFlashStorage.svg?)](https://www.ardu-badge.com/DueFlashStorage)
22. [`Adafruit's LittleFS/InternalFS`](www.adafruit.com) for nRF52
23. [`DoubleResetDetector_Generic v1.8.1+`](https://github.com/khoih-prog/DoubleResetDetector_Generic). To install, check [![arduino-library-badge](https://www.ardu-badge.com/badge/DoubleResetDetector_Generic.svg?)](https://www.ardu-badge.com/DoubleResetDetector_Generic)
24. [`WiFiMulti_Generic library v1.1.1+`](https://github.com/khoih-prog/WiFiMulti_Generic) to use WiFiMulti function. To install, check [![arduino-library-badge](https://www.ardu-badge.com/badge/WiFiMulti_Generic.svg?)](https://www.ardu-badge.com/WiFiMulti_Generic). **New**


---

## Installation

### Use Arduino Library Manager

The best and easiest way is to use `Arduino Library Manager`. Search for [**WiFiManager_Generic_Lite**](https://github.com/khoih-prog/WiFiManager_Generic_Lite), then select / install the latest version.
You can also use this link [![arduino-library-badge](https://www.ardu-badge.com/badge/WiFiManager_Generic_Lite.svg?)](https://www.ardu-badge.com/WiFiManager_Generic_Lite) for more detailed instructions.

### Manual Install

1. Navigate to [**WiFiManager_Generic_Lite**](https://github.com/khoih-prog/WiFiManager_Generic_Lite) page.
2. Download the latest release `WiFiManager_Generic_Lite-main.zip`.
3. Extract the zip file to `WiFiManager_Generic_Lite-main` directory 
4. Copy the whole 
  - `WiFiManager_Generic_Lite-main` folder to Arduino libraries' directory such as `~/Arduino/libraries/`.

### VS Code & PlatformIO:

1. Install [VS Code](https://code.visualstudio.com/)
2. Install [PlatformIO](https://platformio.org/platformio-ide)
3. Install [**WiFiManager_Generic_Lite** library](https://registry.platformio.org/libraries/khoih-prog/WiFiManager_Generic_Lite) by using [Library Manager](https://registry.platformio.org/libraries/khoih-prog/WiFiManager_Generic_Lite/installation). Search for **WiFiManager_Generic_Lite** in [Platform.io Author's Libraries](https://platformio.org/lib/search?query=author:%22Khoi%20Hoang%22)
4. Use included [platformio.ini](platformio/platformio.ini) file from examples to ensure that all dependent libraries will installed automatically. Please visit documentation for the other options and examples at [Project Configuration File](https://docs.platformio.org/page/projectconf.html)

---
---

### Packages' Patches

#### 1. For Adafruit nRF52840 and nRF52832 boards

**To be able to compile, run and automatically detect and display BOARD_NAME on nRF52840/nRF52832 boards**, you have to copy the whole [nRF52 Packages_Patches](Packages_Patches/adafruit/hardware/nrf52/1.3.0) directory into Adafruit nRF52 directory (~/.arduino15/packages/adafruit/hardware/nrf52/1.3.0). 

Supposing the Adafruit nRF52 version is 1.3.0. These files must be copied into the directory:
- `~/.arduino15/packages/adafruit/hardware/nrf52/1.3.0/platform.txt`
- `~/.arduino15/packages/adafruit/hardware/nrf52/1.3.0/boards.txt`
- `~/.arduino15/packages/adafruit/hardware/nrf52/1.3.0/cores/nRF5/Udp.h`
- `~/.arduino15/packages/adafruit/hardware/nrf52/1.3.0/cores/nRF5/Print.h`
- `~/.arduino15/packages/adafruit/hardware/nrf52/1.3.0/cores/nRF5/Print.cpp`
- `~/.arduino15/packages/adafruit/hardware/nrf52/1.3.0/variants/NINA_B302_ublox/variant.h`
- `~/.arduino15/packages/adafruit/hardware/nrf52/1.3.0/variants/NINA_B302_ublox/variant.cpp`
- `~/.arduino15/packages/adafruit/hardware/nrf52/1.3.0/variants/NINA_B112_ublox/variant.h`
- `~/.arduino15/packages/adafruit/hardware/nrf52/1.3.0/variants/NINA_B112_ublox/variant.cpp`
- **`~/.arduino15/packages/adafruit/hardware/nrf52/1.3.0/cores/nRF5/Udp.h`**

Whenever a new version is installed, remember to copy these files into the new version directory. For example, new version is x.yy.z
These files must be copied into the directory:

- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/platform.txt`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/boards.txt`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/cores/nRF5/Udp.h`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/cores/nRF5/Print.h`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/cores/nRF5/Print.cpp`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/variants/NINA_B302_ublox/variant.h`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/variants/NINA_B302_ublox/variant.cpp`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/variants/NINA_B112_ublox/variant.h`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/variants/NINA_B112_ublox/variant.cpp`
- **`~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/cores/nRF5/Udp.h`**

#### 2. For Teensy boards
 
 **To be able to compile and run on Teensy boards**, you have to copy the files in [**Packages_Patches for Teensy directory**](Packages_Patches/hardware/teensy/avr) into Teensy hardware directory (./arduino-1.8.19/hardware/teensy/avr/boards.txt). 

Supposing the Arduino version is 1.8.19. These files must be copied into the directory:

- `./arduino-1.8.19/hardware/teensy/avr/boards.txt`
- `./arduino-1.8.19/hardware/teensy/avr/cores/teensy/Stream.h`
- `./arduino-1.8.19/hardware/teensy/avr/cores/teensy3/Stream.h`
- `./arduino-1.8.19/hardware/teensy/avr/cores/teensy4/Stream.h`

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz
These files must be copied into the directory:

- `./arduino-x.yy.zz/hardware/teensy/avr/boards.txt`
- `./arduino-x.yy.zz/hardware/teensy/avr/cores/teensy/Stream.h`
- `./arduino-x.yy.zz/hardware/teensy/avr/cores/teensy3/Stream.h`
- `./arduino-x.yy.zz/hardware/teensy/avr/cores/teensy4/Stream.h`

#### 3. For Arduino SAM DUE boards
 
 **To be able to compile and run on SAM DUE boards**, you have to copy the whole [SAM DUE](Packages_Patches/arduino/hardware/sam/1.6.12) directory into Arduino sam directory (~/.arduino15/packages/arduino/hardware/sam/1.6.12). 

Supposing the Arduino SAM core version is 1.6.12. This file must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/sam/1.6.12/platform.txt`

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz
This file must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/sam/x.yy.zz/platform.txt`

#### 4. For Arduino SAMD boards
 
 ***To be able to compile, run and automatically detect and display BOARD_NAME on Arduino SAMD (Nano-33-IoT, etc) boards***, you have to copy the whole [Arduino SAMD Packages_Patches](Packages_Patches/arduino/hardware/samd/1.8.13) directory into Arduino SAMD directory (~/.arduino15/packages/arduino/hardware/samd/1.8.13).
 
#### For core version v1.8.10+

Supposing the Arduino SAMD version is 1.8.13. Now only one file must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/samd/1.8.13/platform.txt`

Whenever a new version is installed, remember to copy this files into the new version directory. For example, new version is x.yy.zz

This file must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/samd/x.yy.zz/platform.txt`
 
#### For core version v1.8.9-

Supposing the Arduino SAMD version is 1.8.9. These files must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/samd/1.8.9/platform.txt`
- ***`~/.arduino15/packages/arduino/hardware/samd/1.8.9/cores/arduino/Arduino.h`***

Whenever a new version is installed, remember to copy these files into the new version directory. For example, new version is x.yy.z

These files must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/samd/x.yy.z/platform.txt`
- ***`~/.arduino15/packages/arduino/hardware/samd/x.yy.z/cores/arduino/Arduino.h`***
 
 This is mandatory to fix the ***notorious Arduino SAMD compiler error***. See [Improve Arduino compatibility with the STL (min and max macro)](https://github.com/arduino/ArduinoCore-samd/pull/399)
 
```
 ...\arm-none-eabi\include\c++\7.2.1\bits\stl_algobase.h:243:56: error: macro "min" passed 3 arguments, but takes just 2
     min(const _Tp& __a, const _Tp& __b, _Compare __comp)
```

Whenever the above-mentioned compiler error issue is fixed with the new Arduino SAMD release, you don't need to copy the `Arduino.h` file anymore.

#### 5. For Adafruit SAMD boards
 
 ***To be able to compile, run and automatically detect and display BOARD_NAME on Adafruit SAMD (Itsy-Bitsy M4, etc) boards***, you have to copy the whole [Adafruit SAMD Packages_Patches](Packages_Patches/adafruit/hardware/samd/1.7.9) directory into Adafruit samd directory (~/.arduino15/packages/adafruit/hardware/samd/1.7.9). 

Supposing the Adafruit SAMD core version is 1.7.9. This file must be copied into the directory:

- `~/.arduino15/packages/adafruit/hardware/samd/1.7.9/platform.txt`
- `~/.arduino15/packages/adafruit/hardware/samd/1.7.9/cores/arduino/Print.h`
- `~/.arduino15/packages/adafruit/hardware/samd/1.7.9/cores/arduino/Print.cpp`

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz
This file must be copied into the directory:

- `~/.arduino15/packages/adafruit/hardware/samd/x.yy.zz/platform.txt`
- `~/.arduino15/packages/adafruit/hardware/samd/x.yy.zz/cores/arduino/Print.h`
- `~/.arduino15/packages/adafruit/hardware/samd/x.yy.zz/cores/arduino/Print.cpp`

#### 6. For Seeeduino SAMD boards
 
 ***To be able to compile, run and automatically detect and display BOARD_NAME on Seeeduino SAMD (XIAO M0, Wio Terminal, etc) boards***, you have to copy the whole [Seeeduino SAMD Packages_Patches](Packages_Patches/Seeeduino/hardware/samd/1.8.2) directory into Seeeduino samd directory (~/.arduino15/packages/Seeeduino/hardware/samd/1.8.2). 

Supposing the Seeeduino SAMD core version is 1.8.2. This file must be copied into the directory:

- `~/.arduino15/packages/Seeeduino/hardware/samd/1.8.2/platform.txt`
- `~/.arduino15/packages/Seeeduino/hardware/samd/1.8.2/cores/arduino/Arduino.h`
- `~/.arduino15/packages/Seeeduino/hardware/samd/1.8.2/cores/arduino/Print.h`
- `~/.arduino15/packages/Seeeduino/hardware/samd/1.8.2/cores/arduino/Print.cpp`

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz
This file must be copied into the directory:

- `~/.arduino15/packages/Seeeduino/hardware/samd/x.yy.zz/platform.txt`
- `~/.arduino15/packages/Seeeduino/hardware/samd/x.yy.zz/cores/arduino/Arduino.h`
- `~/.arduino15/packages/Seeeduino/hardware/samd/x.yy.zz/cores/arduino/Print.h`
- `~/.arduino15/packages/Seeeduino/hardware/samd/x.yy.zz/cores/arduino/Print.cpp`

#### 7. For STM32 boards

#### 7.1 For STM32 boards to use LAN8720

To use LAN8720 on some STM32 boards 

- **Nucleo-144 (F429ZI, NUCLEO_F746NG, NUCLEO_F746ZG, NUCLEO_F756ZG)**
- **Discovery (DISCO_F746NG)**
- **STM32F4 boards (BLACK_F407VE, BLACK_F407VG, BLACK_F407ZE, BLACK_F407ZG, BLACK_F407VE_Mini, DIYMORE_F407VGT, FK407M1)**

you have to copy the files [stm32f4xx_hal_conf_default.h](Packages_Patches/STM32/hardware/stm32/2.2.0/system/STM32F4xx) and [stm32f7xx_hal_conf_default.h](Packages_Patches/STM32/hardware/stm32/2.2.0/system/STM32F7xx) into STM32 stm32 directory (~/.arduino15/packages/STM32/hardware/stm32/2.2.0/system) to overwrite the old files.

Supposing the STM32 stm32 core version is 2.2.0. These files must be copied into the directory:

- `~/.arduino15/packages/STM32/hardware/stm32/2.2.0/system/STM32F4xx/stm32f4xx_hal_conf_default.h` for STM32F4.
- `~/.arduino15/packages/STM32/hardware/stm32/2.2.0/system/STM32F7xx/stm32f7xx_hal_conf_default.h` for Nucleo-144 STM32F7.

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz,
theses files must be copied into the corresponding directory:

- `~/.arduino15/packages/STM32/hardware/stm32/x.yy.zz/system/STM32F4xx/stm32f4xx_hal_conf_default.h`
- `~/.arduino15/packages/STM32/hardware/stm32/x.yy.zz/system/STM32F7xx/stm32f7xx_hal_conf_default.h


#### 7.2 For STM32 boards to use Serial1

**To use Serial1 on some STM32 boards without Serial1 definition (Nucleo-144 NUCLEO_F767ZI, Nucleo-64 NUCLEO_L053R8, etc.) boards**, you have to copy the files [STM32 variant.h](Packages_Patches/STM32/hardware/stm32/2.2.0) into STM32 stm32 directory (~/.arduino15/packages/STM32/hardware/stm32/2.2.0). You have to modify the files corresponding to your boards, this is just an illustration how to do.

Supposing the STM32 stm32 core version is 2.2.0. These files must be copied into the directory:

- `~/.arduino15/packages/STM32/hardware/stm32/2.2.0/variants/STM32F7xx/F765Z(G-I)T_F767Z(G-I)T_F777ZIT/NUCLEO_F767ZI/variant.h` for Nucleo-144 NUCLEO_F767ZI.
- `~/.arduino15/packages/STM32/hardware/stm32/2.2.0/variants/STM32L0xx/L052R(6-8)T_L053R(6-8)T_L063R8T/NUCLEO_L053R8/variant.h` for Nucleo-64 NUCLEO_L053R8.

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz,
theses files must be copied into the corresponding directory:

- `~/.arduino15/packages/STM32/hardware/stm32/x.yy.zz/variants/STM32F7xx/F765Z(G-I)T_F767Z(G-I)T_F777ZIT/NUCLEO_F767ZI/variant.h`
- `~/.arduino15/packages/STM32/hardware/stm32/x.yy.zz/variants/STM32L0xx/L052R(6-8)T_L053R(6-8)T_L063R8T/NUCLEO_L053R8/variant.h`

#### 8. For RP2040-based boards using [Earle Philhower arduino-pico core](https://github.com/earlephilhower/arduino-pico)

#### 8.1 To use BOARD_NAME

 **To be able to automatically detect and display BOARD_NAME on RP2040-based boards (RASPBERRY_PI_PICO, ADAFRUIT_FEATHER_RP2040, GENERIC_RP2040, etc) boards**, you have to copy the file [RP2040 platform.txt](Packages_Patches/rp2040/hardware/rp2040/1.4.0) into rp2040 directory (~/.arduino15/packages/rp2040/hardware/rp2040/1.4.0). 

Supposing the rp2040 core version is 1.4.0. This file must be copied into the directory:

- `~/.arduino15/packages/rp2040/hardware/rp2040/1.4.0/platform.txt`

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz
This file must be copied into the directory:

- `~/.arduino15/packages/rp2040/hardware/rp2040/x.yy.zz/platform.txt`

With core after v1.5.0, this step is not necessary anymore thanks to the PR [Add -DBOARD_NAME="{build.board}" #136](https://github.com/earlephilhower/arduino-pico/pull/136).

#### 8.2 To avoid compile error relating to microsecondsToClockCycles

Some libraries, such as [Adafruit DHT-sensor-library](https://github.com/adafruit/DHT-sensor-library), require the definition of microsecondsToClockCycles(). **To be able to compile and run on RP2040-based boards**, you have to copy the files in [**RP2040 Arduino.h**](Packages_Patches/rp2040/hardware/rp2040/1.4.0/cores/rp2040/Arduino.h) into rp2040 directory (~/.arduino15/packages/rp2040/hardware/rp2040/1.4.0).

Supposing the rp2040 core version is 1.4.0. This file must be copied to replace:

- `~/.arduino15/packages/rp2040/hardware/rp2040/1.4.0/cores/rp2040/Arduino.h`

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz
This file must be copied to replace:

- `~/.arduino15/packages/rp2040/hardware/rp2040/x.yy.zz/cores/rp2040/Arduino.h`

With core after v1.5.0, this step is not necessary anymore thanks to the PR [Add defs for compatibility #142](https://github.com/earlephilhower/arduino-pico/pull/142).


#### 9. For Portenta_H7 boards using Arduino IDE in Linux

  **To be able to upload firmware to Portenta_H7 using Arduino IDE in Linux (Ubuntu, etc.)**, you have to copy the file [portenta_post_install.sh](Packages_Patches/arduino/hardware/mbed_portenta/3.0.0/portenta_post_install.sh) into mbed_portenta directory (~/.arduino15/packages/arduino/hardware/mbed_portenta/3.0.0/portenta_post_install.sh). 
  
  Then run the following command using `sudo`
  
```
$ cd ~/.arduino15/packages/arduino/hardware/mbed_portenta/3.0.0
$ chmod 755 portenta_post_install.sh
$ sudo ./portenta_post_install.sh
```

This will create the file `/etc/udev/rules.d/49-portenta_h7.rules` as follows:

```
# Portenta H7 bootloader mode UDEV rules

SUBSYSTEMS=="usb", ATTRS{idVendor}=="2341", ATTRS{idProduct}=="035b", GROUP="plugdev", MODE="0666"
```

Supposing the ArduinoCore-mbed core version is 3.0.0. Now only one file must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/mbed_portenta/3.0.0/portenta_post_install.sh`

Whenever a new version is installed, remember to copy this files into the new version directory. For example, new version is x.yy.zz

This file must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/mbed_portenta/x.yy.zz/portenta_post_install.sh`


#### 10. For RTL8720DN boards using AmebaD core
 
 To avoid compile error relating to PROGMEM, you have to copy the file [Realtek AmebaD core pgmspace.h](Packages_Patches/realtek/hardware/AmebaD/3.1.2/cores/arduino/avr/pgmspace.h) into Realtek AmebaD directory (~/.arduino15/packages/realtek/hardware/AmebaD/3.1.2/cores/arduino/avr/pgmspace.h). 

Supposing the Realtek AmebaD core version is 3.1.2. This file must be copied into the directory:

- `~/.arduino15/packages/realtek/hardware/AmebaD/3.1.2/cores/arduino/avr/pgmspace.h`

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz
This file must be copied into the directory:

- `~/.arduino15/packages/realtek/hardware/AmebaD/x.yy.zz/cores/arduino/avr/pgmspace.h`


#### 11. For SAMD21 and SAMD51 boards using ArduinoCore-fab-sam core
 
 To avoid compile error relating to SAMD21/SAMD51, you have to copy the file [ArduinoCore-fab-sam core pgmspace.h](Packages_Patches/Fab_SAM_Arduino/hardware/samd/1.6.18-alpha2/boards.txt) into `ArduinoCore-fab-sam` samd directory (~/.arduino15/packages/Fab_SAM_Arduino/hardware/samd/1.6.18-alpha2/boards.txt). 

Supposing the `ArduinoCore-fab-sam` samd core version is 1.6.18-alpha2. This file must be copied into the directory:

- `~/.arduino15/packages/Fab_SAM_Arduino/hardware/samd/1.6.18-alpha2/boards.txt`

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz
This file must be copied into the directory:

- `~/.arduino15/packages/Fab_SAM_Arduino/hardware/samd/x.yy.zz/boards.txt`


#### 12. For Seeeduino RP2040 boards
 
 ***To be able to compile, run and automatically detect and display BOARD_NAME on Seeeduino RP2040 (XIAO RP2040, Wio RP2040 Mini) boards***, you have to copy the whole [Seeeduino RP2040 Packages_Patches](Packages_Patches/Seeeduino/hardware/rp2040/2.7.2) directory into Seeeduino samd directory (~/.arduino15/packages/Seeeduino/hardware/rp2040/2.7.2). 

Supposing the Seeeduino SAMD core version is 2.7.2. This file must be copied into the directory:

- `~/.arduino15/packages/Seeeduino/hardware/rp2040/2.7.2/boards.txt`
- `~/.arduino15/packages/Seeeduino/hardware/rp2040/2.7.2/variants/Seeed_XIAO_RP2040/pins_arduino.h`

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz
This file must be copied into the directory:

- `~/.arduino15/packages/Seeeduino/hardware/samd/x.yy.zz/boards.txt`
- `~/.arduino15/packages/Seeeduino/hardware/samd/x.yy.zz/variants/Seeed_XIAO_RP2040/pins_arduino.h`


---
---

## How It Works

- The [**SAMD_WiFi**](examples/SAMD_WiFi) example shows how it works and should be used as the basis for a sketch that uses this library.
- The concept of [**SAMD_WiFi**](examples/SAMD_WiFi) is that a new `Generic WiFi module/shield` will start a WiFi configuration portal when powered up, but has no valid stored Credentials or can't connect to WiFi APs after a pre-determined time.
- There are 6 more custom parameters added in the sketch which you can use in your program later. In the example, they are: 2 sets of Blynk Servers and Tokens, Blynk Port and MQTT Server.
- Using any WiFi enabled device with a browser (computer, phone, tablet) connect to the newly created AP and type in the configurable AP IP address (default 192.168.4.1). The Config Portal AP channel (default 10) is also configurable to avoid conflict with other APs.
- The Config Portal is **auto-adjusted** to fix the 4 static parameters (WiFi SSIDs/PWDs) as well as 6 more dynamic custom parameters.
- After the custom data entered, and **Save** button pressed, the configuration data will be saved in host's non-volatile memory, then the board reboots.
- If there is valid stored Credentials, it'll go directly to connect to one of the **MultiWiFi APs** without starting / using the Config Portal.
- `Generic WiFi module/shield` will try to connect. If successful, the dynamic DHCP and/or configured static IP address will be displayed in the configuration portal. 
- The `Generic WiFi module/shield` WiFi Config Portal network and Web Server will shutdown to return control to the sketch code.
- In the operation, if the current WiFi connection is lost because of any reason, the system will **auto(Re)connect** to the remaining WiFi AP.
- **If system can't connect to any of the 2 WiFi APs, the Config Portal will start**, after some pre-determined time, to permit user to update the Credentials.

---

### How to use

#### 1. Basic usage

- Include in your sketch

```cpp
// Must be before #include <WiFiManager_Generic_Lite_SAMD.h>
// Start location in EEPROM to store config data. Default 0
// Config data Siz, not including your custom data, currently is 84 bytes)
#define EEPROM_START      0

#include <WiFiManager_Generic_Lite_SAMD.h>

WiFiManager_Generic_Lite* WiFiManager_Generic;
```

#### 2. Add custom parameters

- To add custom parameters, just add

```
#include "defines.h"

// USE_DYNAMIC_PARAMETERS defined in defined.h

/////////////// Start dynamic Credentials ///////////////

//Defined in <WiFiManager_Generic_Lite_SAMD.h>
/**************************************
  #define MAX_ID_LEN                5
  #define MAX_DISPLAY_NAME_LEN      16

  typedef struct
  {
  char id             [MAX_ID_LEN + 1];
  char displayName    [MAX_DISPLAY_NAME_LEN + 1];
  char *pdata;
  uint8_t maxlen;
  } MenuItem;
**************************************/

#if USE_DYNAMIC_PARAMETERS

#define MAX_BLYNK_SERVER_LEN      34
#define MAX_BLYNK_TOKEN_LEN       34

char Blynk_Server1 [MAX_BLYNK_SERVER_LEN + 1]  = "account.duckdns.org";
char Blynk_Token1  [MAX_BLYNK_TOKEN_LEN + 1]   = "token1";

char Blynk_Server2 [MAX_BLYNK_SERVER_LEN + 1]  = "account.ddns.net";
char Blynk_Token2  [MAX_BLYNK_TOKEN_LEN + 1]   = "token2";

#define MAX_BLYNK_PORT_LEN        6
char Blynk_Port   [MAX_BLYNK_PORT_LEN + 1]  = "8080";

#define MAX_MQTT_SERVER_LEN      34
char MQTT_Server  [MAX_MQTT_SERVER_LEN + 1]   = "mqtt.duckdns.org";

MenuItem myMenuItems [] =
{
  { "sv1", "Blynk Server1", Blynk_Server1,  MAX_BLYNK_SERVER_LEN },
  { "tk1", "Token1",        Blynk_Token1,   MAX_BLYNK_TOKEN_LEN },
  { "sv2", "Blynk Server2", Blynk_Server2,  MAX_BLYNK_SERVER_LEN },
  { "tk2", "Token2",        Blynk_Token2,   MAX_BLYNK_TOKEN_LEN },
  { "prt", "Port",          Blynk_Port,     MAX_BLYNK_PORT_LEN },
  { "mqt", "MQTT Server",   MQTT_Server,    MAX_MQTT_SERVER_LEN },
};

uint16_t NUM_MENU_ITEMS = sizeof(myMenuItems) / sizeof(MenuItem);  //MenuItemSize;

#else

MenuItem myMenuItems [] = {};

uint16_t NUM_MENU_ITEMS = 0;

#endif    //USE_DYNAMIC_PARAMETERS

```

#### 3. Not using custom parameters

- If you don't need to add dynamic parameters, use the following in sketch

```
#define USE_DYNAMIC_PARAMETERS      false
```

#### 4. To open Config Portal

- When you want to open a config portal, just add

```cpp
WiFiManager_Generic = new WiFiManager_Generic_Lite();
WiFiManager_Generic->begin();
```

#### 5. To use different AP WiFi Channel

- To not use default AP WiFi Channel 10 to avoid conflict with other WiFi APs : 

```cpp
WiFiManager_Generic->setConfigPortalChannel(newChannel);
```

- To use random AP WiFi Channel to avoid conflict with other WiFi APs : 

```cpp
WiFiManager_Generic->setConfigPortalChannel(0);
```

#### 6. To use different static AP IP from default

- To use different static AP IP (not use default `192.168.4.1`), call

```cpp
WiFiManager_Generic->setConfigPortalIP(IPAddress(xxx,xxx,xxx,xxx));
```

#### 7. To use custom DHCP HostName

- To set custom DHCP HostName :
 
```
  // Set customized DHCP HostName
  WiFiManager_Generic->begin("SAMD_ABCDEF");
```
 
or just use the default Hostname, for example "SAMD_XXXXXX" for SAMD

```
  //Or use default Hostname "WIFI_GENERIC_XXXXXX"
  //WiFiManager_Generic->begin();
```

#### 8. To use custom HTML Style

```
const char NewCustomsStyle[] /*PROGMEM*/ = "<style>div,input{padding:5px;font-size:1em;}input{width:95%;}body{text-align: center;}\
button{background-color:blue;color:white;line-height:2.4rem;font-size:1.2rem;width:100%;}fieldset{border-radius:0.3rem;margin:0px;}</style>";

...

WiFiManager_Generic->setCustomsStyle(NewCustomsStyle);
```

#### 9. To use custom Head Elements


```
WiFiManager_Generic->setCustomsHeadElement("<style>html{filter: invert(10%);}</style>");
```

#### 10. To use CORS Header

```
WiFiManager_Generic->setCORSHeader("Your Access-Control-Allow-Origin");
```

While in AP mode, connect to it using its `SSID` (WIFI_GENERIC_XXXXXX) / `Password` ("MyWIFI_GENERIC_XXXXXX"), then open a browser to the Portal AP IP, default `192.168.4.1`, configure wifi then click **Save**. The Credentials / WiFi connection information will be saved in non-volatile memory. It will then autoconnect.


Once Credentials / WiFi network information is saved in the host non-volatile memory, it will try to autoconnect to WiFi every time it is started, without requiring any function calls in the sketch.


#### 11. To use and input only one set of WiFi SSID and PWD

#### 11.1 If you need to use and input only one set of WiFi SSID/PWD

```
// Permit input only one set of WiFi SSID/PWD. The other can be "NULL or "blank"
// Default is false (if not defined) => must input 2 sets of SSID/PWD
#define REQUIRE_ONE_SET_SSID_PW       true
```
But it's always advisable to use and input both sets for reliability.
 
#### 11.2 If you need to use both sets of WiFi SSID/PWD

```
// Permit input only one set of WiFi SSID/PWD. The other can be "NULL or "blank"
// Default is false (if not defined) => must input 2 sets of SSID/PWD
#define REQUIRE_ONE_SET_SSID_PW       false
```

#### 12. To enable auto-scan of WiFi networks for selection in Configuration Portal

#### 12.1 Enable auto-scan of WiFi networks for selection in Configuration Portal


```
#define SCAN_WIFI_NETWORKS                  true
```

The manual input of SSIDs is default enabled, so that users can input arbitrary SSID, not only from the scanned list. This is for the sample use-cases in which users can input the known SSIDs of another place, then send the boards to that place. The boards can connect to WiFi without users entering Config Portal to re-configure.

#### 12.2 Disable manually input SSIDs

```
// To disable manually input SSID, only from a scanned SSID lists
#define MANUAL_SSID_INPUT_ALLOWED           false
```

This is for normal use-cases in which users can only select an SSID from a scanned list of SSIDs to avoid typo mistakes and/or security.

#### 12.3 Select maximum number of SSIDs in the list

The maximum number of SSIDs in the list is selectable from 2 to 15 (for ESP8266/ESP32-AT shields, from 2-6). If invalid number of SSIDs is selected, the default number of 10 will be used.


```
// From 2-15
#define MAX_SSID_IN_LIST                    8
```

#### 13. To avoid blocking in loop when WiFi is lost


#### 13.1 Max times to try WiFi per loop

To define max times to try WiFi per loop() iteration. To avoid blocking issue in loop()

Default is 1 if not defined, and minimum is forced to be 1.

To use, uncomment in `defines.h`. 

Check [retries block the main loop #18](https://github.com/khoih-prog/WiFiManager_NINA_Lite/issues/18#issue-1094004380)

```
#define MAX_NUM_WIFI_RECON_TRIES_PER_LOOP     2
```

#### 13.2 Interval between reconnection WiFi if lost

Default is no interval between reconnection WiFi times if lost WiFi. Max permitted interval will be 10mins.

Uncomment to use. Be careful, WiFi reconnection will be delayed if using this method.

Only use whenever urgent tasks in loop() can't be delayed. But if so, it's better you have to rewrite your code, e.g. using higher priority tasks.

Check [retries block the main loop #18](https://github.com/khoih-prog/WiFiManager_NINA_Lite/issues/18#issuecomment-1006197561)

```
#define WIFI_RECON_INTERVAL                   30000     // 30s
```

#### 14. Not using Board_Name on Config_Portal

Default is `true`. Just change to `false` to Not using `Board_Name` on Config_Portal

```
/////////////////////////////////////////////

// Optional, to use Board Name in Menu
#define USING_BOARD_NAME                    false

/////////////////////////////////////////////
```

#### 15. How to use CONFIG_MODE_LED

Check the examples

https://github.com/khoih-prog/WiFiManager_Generic_Lite/blob/49c1aff82d2742a2e0b787a24009d2905b76ee3c/examples/RP2040_WiFi/RP2040_WiFi.ino#L22-L30


https://github.com/khoih-prog/WiFiManager_Generic_Lite/blob/49c1aff82d2742a2e0b787a24009d2905b76ee3c/examples/RP2040_WiFi/defines.h#L191-L208



---
---

### Examples

 1. [MKR1000_WiFi101](examples/MKR1000_WiFi101)
 2. [MKR1000_WiFi101_MQTT](examples/MKR1000_WiFi101_MQTT)
 3. [nRF52_WiFi](examples/nRF52_WiFi)
 4. [nRF52_WiFi_MQTT](examples/nRF52_WiFi_MQTT)
 5. [SAM_DUE_WiFi](examples/SAM_DUE_WiFi)
 6. [SAM_DUE_WiFi_MQTT](examples/SAM_DUE_WiFi_MQTT) 
 7. [SAMD_WiFi](examples/SAMD_WiFi)
 8. [SAMD_WiFi_MQTT](examples/SAMD_WiFi_MQTT)
 9. [STM32_WiFi](examples/STM32_WiFi)
10. [STM32_WiFi_MQTT](examples/STM32_WiFi_MQTT) 
11. [Teensy_WiFi](examples/Teensy_WiFi)
12. [Teensy_WiFi_MQTT](examples/Teensy_WiFi_MQTT)
13. [RP2040_WiFi](examples/RP2040_WiFi) **New**
14. [RP2040_WiFi_MQTT](examples/RP2040_WiFi_MQTT) **New**
 
---
---

## So, how it works?

In `Configuration Portal Mode`, it starts an AP called `WIFI_GENERIC_XXXXXX`. Connect to it using the `configurable password` you can define in the code. For example, `MyWIFI_GENERIC_XXXXXX` (see examples):

After you connected, please, go to http://192.168.4.1 or newly configured AP IP, you'll see this `Main` page:

<p align="center">
    <img src="https://github.com/khoih-prog/WiFiManager_Generic_Lite/blob/main/pics/Main.png">
</p>

Enter your credentials, 

### 1. Without SCAN_WIFI_NETWORKS

<p align="center">
    <img src="https://github.com/khoih-prog/WiFiManager_Generic_Lite/blob/main/pics/Input.png">
</p>

### 2. With SCAN_WIFI_NETWORKS


<p align="center">
    <img src="https://github.com/khoih-prog/WiFiManager_Generic_Lite/blob/main/pics/Input_With_Scan.png">
</p>


### 3. With SCAN_WIFI_NETWORKS for ESP8266-AT and ESP32-AT shield

The number of SSIDs in scanned list is limited at max 6.

<p align="center">
    <img src="https://github.com/khoih-prog/WiFiManager_Generic_Lite/blob/main/pics/ESP_AT_Input_With_Scan.png">
</p>


then click `Save`. 

<p align="center">
    <img src="https://github.com/khoih-prog/WiFiManager_Generic_Lite/blob/main/pics/Save.png">
</p>

The WiFi Credentials will be saved and the board connect to the selected WiFi AP.

If you're already connected to a listed WiFi AP and don't want to change anything, just select `Exit` from the `Main` page to reboot the board and connect to the previously-stored AP. The WiFi Credentials are still intact.

---

### Important Notes

1. Now you can use special chars such as **~, !, @, #, $, %, ^, &, _, -, space,etc.** thanks to [brondolin](https://github.com/brondolin) to provide the amazing fix in [**Blynk_WM**](https://github.com/khoih-prog/Blynk_WM) to permit input special chars such as **%** and **#** into data fields. See [Issue 3](https://github.com/khoih-prog/Blynk_WM/issues/3).
2. The SSIDs, Passwords must be input (or to make them different from **blank**). Otherwise, the Config Portal will re-open until those fields have been changed. If you don't need any field, just input anything or use duplicated data from similar field.
3. WiFi password max length now is 63 chars according to WPA2 standard.

---

### How to use default Credentials and have them pre-loaded onto Config Portal

See this example and modify as necessary

#### 1. To always load [Default Credentials](examples/SAMD_WiFi/Credentials.h) and override Config Portal data

```
// Used mostly for development and debugging. FORCES default values to be loaded each run.
// Config Portal data input will be ignored and overridden by DEFAULT_CONFIG_DATA
bool LOAD_DEFAULT_CONFIG_DATA = true;
```

#### 2. To load [Default Credentials](examples/SAMD_WiFi/Credentials.h) when there is no valid Credentials.

Config Portal data input will be override DEFAULT_CONFIG_DATA

```
// Used mostly once debugged. Assumes good data already saved in device.
// Config Portal data input will be override DEFAULT_CONFIG_DATA
bool LOAD_DEFAULT_CONFIG_DATA = false;
```

#### 3. Example of [Default Credentials](examples/SAMD_WiFi/Credentials.h)

```cpp
/// Start Default Config Data //////////////////

/*
#define SSID_MAX_LEN      32
//From v1.0.3, WPA2 passwords can be up to 63 characters long.
#define PASS_MAX_LEN      64

typedef struct
{
  char wifi_ssid[SSID_MAX_LEN];
  char wifi_pw  [PASS_MAX_LEN];
}  WiFi_Credentials;

#define NUM_WIFI_CREDENTIALS      2

// Configurable items besides fixed Header, just add board_name 
#define NUM_CONFIGURABLE_ITEMS    ( ( 2 * NUM_WIFI_CREDENTIALS ) + 1 )
////////////////

typedef struct Configuration
{
  char header         [16];
  WiFi_Credentials  WiFi_Creds  [NUM_WIFI_CREDENTIALS];
  char board_name     [24];
  int  checkSum;
} WIFI_GENERIC_Configuration;
*/

#define TO_LOAD_DEFAULT_CONFIG_DATA      false

#if TO_LOAD_DEFAULT_CONFIG_DATA

// This feature is primarily used in development to force a known set of values as Config Data
// It will NOT force the Config Portal to activate. Use DRD or erase Config Data with Blynk.clearConfigData()

// Used mostly for development and debugging. FORCES default values to be loaded each run.
// Config Portal data input will be ignored and overridden by DEFAULT_CONFIG_DATA
//bool LOAD_DEFAULT_CONFIG_DATA = true;

// Used mostly once debugged. Assumes good data already saved in device.
// Config Portal data input will be override DEFAULT_CONFIG_DATA
bool LOAD_DEFAULT_CONFIG_DATA = false;


WIFI_GENERIC_Configuration defaultConfig =
{
  //char header[16], dummy, not used
  "WIFI_GENERIC",
  // WiFi_Credentials  WiFi_Creds  [NUM_WIFI_CREDENTIALS];
  // WiFi_Credentials.wifi_ssid and WiFi_Credentials.wifi_pw
  "SSID1",  "password1",
  "SSID2",  "password2",
  //char board_name     [24];
  "SAMD-Control",
  // terminate the list
  //int  checkSum, dummy, not used
  0
  /////////// End Default Config Data /////////////
};

#else

bool LOAD_DEFAULT_CONFIG_DATA = false;

WIFI_GENERIC_Configuration defaultConfig;

#endif    // TO_LOAD_DEFAULT_CONFIG_DATA

/////////// End Default Config Data /////////////
```

### How to add dynamic parameters from sketch

Example of [Default dynamicParams](examples/SAMD_WiFi/dynamicParams.h)

- To add custom parameters, just modify the example below

```
#include "defines.h"

// USE_DYNAMIC_PARAMETERS defined in defined.h

/////////////// Start dynamic Credentials ///////////////

//Defined in <WiFiManager_Generic_Lite_SAMD.h>
/**************************************
  #define MAX_ID_LEN                5
  #define MAX_DISPLAY_NAME_LEN      16

  typedef struct
  {
  char id             [MAX_ID_LEN + 1];
  char displayName    [MAX_DISPLAY_NAME_LEN + 1];
  char *pdata;
  uint8_t maxlen;
  } MenuItem;
**************************************/

#if USE_DYNAMIC_PARAMETERS

#define MAX_BLYNK_SERVER_LEN      34
#define MAX_BLYNK_TOKEN_LEN       34

char Blynk_Server1 [MAX_BLYNK_SERVER_LEN + 1]  = "account.duckdns.org";
char Blynk_Token1  [MAX_BLYNK_TOKEN_LEN + 1]   = "token1";

char Blynk_Server2 [MAX_BLYNK_SERVER_LEN + 1]  = "account.ddns.net";
char Blynk_Token2  [MAX_BLYNK_TOKEN_LEN + 1]   = "token2";

#define MAX_BLYNK_PORT_LEN        6
char Blynk_Port   [MAX_BLYNK_PORT_LEN + 1]  = "8080";

#define MAX_MQTT_SERVER_LEN      34
char MQTT_Server  [MAX_MQTT_SERVER_LEN + 1]   = "mqtt.duckdns.org";

MenuItem myMenuItems [] =
{
  { "sv1", "Blynk Server1", Blynk_Server1,  MAX_BLYNK_SERVER_LEN },
  { "tk1", "Token1",        Blynk_Token1,   MAX_BLYNK_TOKEN_LEN },
  { "sv2", "Blynk Server2", Blynk_Server2,  MAX_BLYNK_SERVER_LEN },
  { "tk2", "Token2",        Blynk_Token2,   MAX_BLYNK_TOKEN_LEN },
  { "prt", "Port",          Blynk_Port,     MAX_BLYNK_PORT_LEN },
  { "mqt", "MQTT Server",   MQTT_Server,    MAX_MQTT_SERVER_LEN },
};

uint16_t NUM_MENU_ITEMS = sizeof(myMenuItems) / sizeof(MenuItem);  //MenuItemSize;

#else

MenuItem myMenuItems [] = {};

uint16_t NUM_MENU_ITEMS = 0;

#endif    //USE_DYNAMIC_PARAMETERS

```
- If you don't need to add dynamic parameters, use the following in sketch

```
#define USE_DYNAMIC_PARAMETERS     false
```

or

```
/////////////// Start dynamic Credentials ///////////////

MenuItem myMenuItems [] = {};

uint16_t NUM_MENU_ITEMS = 0;
/////// // End dynamic Credentials ///////////

```
---

### Important Notes for using Dynamic Parameters' ids

1. These ids (such as "mqtt" in example) must be **unique**.

Please be noted that the following **reserved names are already used in library**:

```
"id"    for WiFi SSID
"pw"    for WiFi PW
"id1"   for WiFi1 SSID
"pw1"   for WiFi1 PW
"nm"    for Board Name
```
---
---

### Example [SAMD_WiFi](examples/SAMD_WiFi)

Please take a look at other examples, as well.

#### 1. File [SAMD_WiFi.ino](examples/SAMD_WiFi/SAMD_WiFi.ino)

https://github.com/khoih-prog/WiFiManager_Generic_Lite/blob/7c28601d1f12a5c92ca8338d1a5acaefb006ee18/examples/SAMD_WiFi/SAMD_WiFi.ino#L13-L167


---

#### 2. File [defines.h](examples/SAMD_WiFi/defines.h)

https://github.com/khoih-prog/WiFiManager_Generic_Lite/blob/7c28601d1f12a5c92ca8338d1a5acaefb006ee18/examples/SAMD_WiFi/defines.h#L13-L307


---

#### 3. File [Credentials.h](examples/SAMD_WiFi/Credentials.h)

https://github.com/khoih-prog/WiFiManager_Generic_Lite/blob/7c28601d1f12a5c92ca8338d1a5acaefb006ee18/examples/SAMD_WiFi/Credentials.h#L13-L89


---

#### 4. File [dynamicParams.h](examples/SAMD_WiFi/dynamicParams.h)


https://github.com/khoih-prog/WiFiManager_Generic_Lite/blob/7c28601d1f12a5c92ca8338d1a5acaefb006ee18/examples/SAMD_WiFi/dynamicParams.h#L13-L74


---
---


### Debug Terminal output Samples

#### 1. SAMD_WiFi example on Nano-33 IoT

This is the terminal output when running [**SAMD_WiFi**](examples/SAMD_WiFi) example on **Nano-33 IoT**:

#### 1.1 Open Config Portal

```
Start SAMD_WiFi on SAMD_NANO_33_IOT with WiFiNINA using WiFiNINA_Generic Library
WiFiManager_Generic_Lite v1.7.0
[WG] Hostname=SAMD-Master-Controller
Flag read = 0xffffffff
No doubleResetDetected
SetFlag write = 0xd0d01234
[WG] ======= Start Default Config Data =======
[WG] Hdr=WIFI_GENERIC,SSID=SSID1,PW=password1
[WG] SSID1=SSID2,PW1=password2
[WG] BName=SAMD-Control
[WG] i=0,id=sv1,data=account.duckdns.org
[WG] i=1,id=tk1,data=token1
[WG] i=2,id=sv2,data=account.ddns.net
[WG] i=3,id=tk2,data=token2
[WG] i=4,id=pt,data=8080
[WG] i=5,id=mq,data=mqtt.duckdns.org
[WG] ChkCrR:CrCCsum=0xaf50,CrRCsum=0xffffffff
[WG] CCSum=0x1360,RCSum=0x0
[WG] Invalid Stored Dynamic Data. Load default from Sketch
[WG] SaveEEPROM,sz=1024,Datasz=0,CSum=0x109a
[WG] CrCCSum=0x1981
[WG] ======= Start Loaded Config Data =======
[WG] Hdr=WIFI_GENERIC,SSID=SSID1,PW=password1
[WG] SSID1=SSID2,PW1=password2
[WG] BName=SAMD-Control
[WG] i=0,id=sv1,data=account.duckdns.org
[WG] i=1,id=tk1,data=token1
[WG] i=2,id=sv2,data=account.ddns.net
[WG] i=3,id=tk2,data=token2
[WG] i=4,id=pt,data=8080
[WG] i=5,id=mq,data=mqtt.duckdns.org
[WG] b:StayInCfgPortal:NoCfgDat
[WG] SSID=WIFI_GENERIC_51F485,PW=MyWIFI_GENERIC_51F485
[WG] IP=192.168.4.1,CH=10
WiFi-beginAP3: return1 = 7
WiFi-beginAP3: return2 = 7
C
Your stored Credentials :
Blynk Server1 = account.duckdns.org
Token1 = token1
Blynk Server2 = account.ddns.net
Token2 = token2
Port = 8080
MQTT Server = mqtt.duckdns.org
Stop doubleResetDetecting
ClearFlag write = 0xd0d04321
CCCCCCCCC
```

#### 1.2 Received data from Config Portal

```
[WG] h: Init menuItemUpdated :6
[WG] h:repl id
[WG] h:items updated =1
[WG] h:key =id, value =HueNet1
[WG] h:repl pw
[WG] h:items updated =2
[WG] h:key =pw, value =12345678
[WG] h:repl id1
[WG] h:items updated =3
[WG] h:key =id1, value =HueNet2
[WG] h:repl pw1
[WG] h:items updated =4
[WG] h:key =pw1, value =12345678
[WG] h:repl nm
[WG] h:items updated =5
[WG] h:key =nm, value =Nano_33_IoT
[WG] h:sv1=account.duckdns.org
[WG] h:items updated =6
[WG] h:key =sv1, value =account.duckdns.org
[WG] h:tk1=token1
[WG] h:items updated =7
[WG] h:key =tk1, value =token1
[WG] h:sv2=192.168.2.32
[WG] h:items updated =8
[WG] h:key =sv2, value =192.168.2.32
[WG] h:tk2=token2
[WG] h:items updated =9
[WG] h:key =tk2, value =token2
[WG] h:prt=8080
[WG] h:items updated =10
[WG] h:key =prt, value =8080
[WG] h:mqt=mqtt_server
[WG] h:items updated =11
[WG] h:key =mqt, value =mqtt_server
[WG] h:UpdEEPROM
[WG] SaveEEPROM,Sz=1024,DataSz=0,WCSum=0x130e
[WG] pdata=account.duckdns.org,len=34
[WG] pdata=token1,len=34
[WG] pdata=192.168.2.32,len=34
[WG] pdata=token2,len=34
[WG] pdata=8080,len=6
[WG] pdata=mqtt_server,len=34
[WG] CrCCSum=0x1330
[WG] h:Rst
```

#### 1.3 Got valid Credential from Config Portal, then connected to WiFi

```
Start SAMD_WiFi on SAMD_NANO_33_IOT with WiFiNINA using WiFiNINA_Generic Library
WiFiManager_Generic_Lite v1.7.0
[WG] Hostname=SAMD-Master-Controller
Flag read = 0xd0d04321
No doubleResetDetected
SetFlag write = 0xd0d01234
[WG] CCSum=0x130e,RCSum=0x130e
[WG] ChkCrR:CrCCsum=0x1330,CrRCsum=0x1330
[WG] CrCCSum=1330,CrRCSum=1330
[WG] Valid Stored Dynamic Data
[WG] ======= Start Stored Config Data =======
[WG] Hdr=WIFI_GENERIC,SSID=HueNet1,PW=12345678
[WG] SSID1=HueNet2,PW1=12345678
[WG] BName=Nano_33_IoT
[WG] i=0,id=sv1,data=account.duckdns.org
[WG] i=1,id=tk1,data=token1
[WG] i=2,id=sv2,data=192.168.2.32
[WG] i=3,id=tk2,data=token2
[WG] i=4,id=prt,data=8080
[WG] i=5,id=mqt,data=mqtt_server
[WG] WiFi connected after time: 1
[WG] SSID:HueNet1,RSSI=-20
[WG] IP address:192.168.2.148
[WG] b:WOK
H
Your stored Credentials :
Blynk Server1 = account.duckdns.org
Token1 = token1
Blynk Server2 = 192.168.2.32
Token2 = token2
Port = 8080
MQTT Server = mqtt_server
Stop doubleResetDetecting
ClearFlag write = 0xd0d04321
HHHHHHHHHH HHHHHHHHHH HHHHHHHHHH HHHHHHHHHH HHHHHHHHHH HHHHHHHHHH HHHHHHHHHH HHHHHHHHHH
HHHHHHHHHH HHHHHHHHHH HHHHHHHHHH HHHHHHHHHH HHHHHHHHHH HHHHHHHHHH HHHHHHHHHH HHHHHHHHHH
```

#### 1.4 Lost a WiFi and autoconnect to another WiFi AP

```
[WG] r:Check&WLost                      <=== Lost primary WiFi
[WG] r:WLost.ReconW
[WG] WiFi connected after time: 1
[WG] SSID:HueNet2,RSSI=-50              <=== Connect secondary WiFi
[WG] IP address:192.168.2.113
[WG] r:WOK                              <=== Success
HHHHHHHHHH HHHHHHHHHH
```

#### 1.5 Reopen Config Portal if can't connect to any of the 2 WiFi APs

```
Start SAMD_WiFi on SAMD_NANO_33_IOT with WiFiNINA using WiFiNINA_Generic Library
WiFiManager_Generic_Lite v1.7.0
[WG] Hostname=SAMD-Master-Controller
Flag read = 0xd0d04321
No doubleResetDetected
SetFlag write = 0xd0d01234
[WG] ======= Start Default Config Data =======
[WG] Hdr=WIFI_GENERIC,SSID=SSID1,PW=password1
[WG] SSID1=SSID2,PW1=password2
[WG] BName=SAMD-Control
[WG] i=0,id=sv1,data=account.duckdns.org
[WG] i=1,id=tk1,data=token1
[WG] i=2,id=sv2,data=account.ddns.net
[WG] i=3,id=tk2,data=token2
[WG] i=4,id=pt,data=8080
[WG] i=5,id=mq,data=mqtt.duckdns.org
[WG] ChkCrR:CrCCsum=0x21ce,CrRCsum=0x21ce
[WG] CCSum=0x1246,RCSum=0x1246
[WG] CrCCsum=0x21ce,CrRCsum=0x21ce
[WG] Valid Stored Dynamic Data
[WG] ======= Start Stored Config Data =======
[WG] Hdr=WIFI_GENERIC,SSID=HueNet1,PW=****
[WG] SSID1=HueNet2,PW1=****
[WG] BName=Air-Control
[WG] i=0,id=sv1,data=new_account.duckdns.org
[WG] i=1,id=tk1,data=new_token1
[WG] i=2,id=sv2,data=new_account.ddns.net
[WG] i=3,id=tk2,data=new_token2
[WG] i=4,id=pt,data=8080
[WG] i=5,id=mq,data=new_mqtt.duckdns.org
[WG] ConMultiWifi
[WG] con2WF:SSID=SSID,PW=password
[WG] Remaining retry_time=3
WiFi-begin: return1 = 4
WiFi-begin: return2 = 4
[WG] Remaining retry_time=2
WiFi-begin: return1 = 4
WiFi-begin: return2 = 4
[WG] Remaining retry_time=1
WiFi-begin: return1 = 4
WiFi-begin: return2 = 4
[WG] Failed using index=0, retry_time=0
[WG] con2WF:failed
[WG] b:NoW
[WG] SSID=WIFI_GENERIC_51F485,PW=MyWIFI_GENERIC_51F485
[WG] IP=192.168.4.1,CH=10
WiFi-beginAP3: return1 = 7
WiFi-beginAP3: return2 = 7
Stop doubleResetDetecting
ClearFlag write = 0xd0d04321
C
Your stored Credentials :
Blynk Server1 = new_account.duckdns.org
Token1 = new_token1
Blynk Server2 = new_account.ddns.net
Token2 = new_token2
Port = 8080
MQTT Server = new_mqtt.duckdns.org
CCCC
```

#### 1.6 DRD Not Detected:

```
Start SAMD_WiFi on SAMD_NANO_33_IOT with WiFiNINA using WiFiNINA_Generic Library
WiFiManager_Generic_Lite v1.7.0
[WG] Hostname=SAMD-Master-Controller
Flag read = 0xd0d04321
No doubleResetDetected
SetFlag write = 0xd0d01234
[WG] ======= Start Default Config Data =======
[WG] Hdr=WIFI_GENERIC,SSID=SSID1,PW=password1
[WG] SSID1=SSID2,PW1=password2
[WG] BName=SAMD-Control
[WG] i=0,id=sv1,data=account.duckdns.org
[WG] i=1,id=tk1,data=token1
[WG] i=2,id=sv2,data=account.ddns.net
[WG] i=3,id=tk2,data=token2
[WG] i=4,id=pt,data=8080
[WG] i=5,id=mq,data=mqtt.duckdns.org
[WG] ChkCrR:CrCCsum=0x21ce,CrRCsum=0x21ce
[WG] CCSum=0x1246,RCSum=0x1246
[WG] CrCCsum=0x21ce,CrRCsum=0x21ce
[WG] Valid Stored Dynamic Data
[WG] ======= Start Stored Config Data =======
[WG] Hdr=WIFI_GENERIC,SSID=HueNet1,PW=****
[WG] SSID1=HueNet2,PW1=****
[WG] BName=Air-Control
[WG] i=0,id=sv1,data=new_account.duckdns.org
[WG] i=1,id=tk1,data=new_token1
[WG] i=2,id=sv2,data=new_account.ddns.net
[WG] i=3,id=tk2,data=new_token2
[WG] i=4,id=pt,data=8080
[WG] i=5,id=mq,data=new_mqtt.duckdns.org
[WG] WiFi connected after time: 1
[WG] SSID:HueNet1,RSSI=-20
[WG] IP address:192.168.2.105
[WG] b:WOK
Stop doubleResetDetecting
ClearFlag write = 0xd0d04321
H
Your stored Credentials :
Blynk Server1 = new_account.duckdns.org
Token1 = new_token1
Blynk Server2 = new_account.ddns.net
Token2 = new_token2
Port = 8080
MQTT Server = new_mqtt.duckdns.org
HHHHHHHHH HHHHHHHHHH
```

#### 1.7 DRD detected and Config Portal is forcefully opened

```
Start SAMD_WiFi on SAMD_NANO_33_IOT with WiFiNINA using WiFiNINA_Generic Library
WiFiManager_Generic_Lite v1.7.0
[WG] Hostname=SAMD-Master-Controller
Flag read = 0xd0d01234
doubleResetDetected
ClearFlag write = 0xd0d04321
[WG] Double Reset Detected
[WG] ======= Start Default Config Data =======
[WG] Hdr=WIFI_GENERIC,SSID=SSID1,PW=password1
[WG] SSID1=SSID2,PW1=password2
[WG] BName=SAMD-Control
[WG] i=0,id=sv1,data=account.duckdns.org
[WG] i=1,id=tk1,data=token1
[WG] i=2,id=sv2,data=account.ddns.net
[WG] i=3,id=tk2,data=token2
[WG] i=4,id=pt,data=8080
[WG] i=5,id=mq,data=mqtt.duckdns.org
[WG] ChkCrR:CrCCsum=0x21ce,CrRCsum=0x21ce
[WG] CCSum=0x1246,RCSum=0x1246
[WG] CrCCsum=0x21ce,CrRCsum=0x21ce
[WG] Valid Stored Dynamic Data
[WG] ======= Start Stored Config Data =======
[WG] Hdr=WIFI_GENERIC,SSID=HueNet1,PW=****
[WG] SSID1=HueNet2,PW1=****
[WG] BName=Air-Control
[WG] i=0,id=sv1,data=new_account.duckdns.org
[WG] i=1,id=tk1,data=new_token1
[WG] i=2,id=sv2,data=new_account.ddns.net
[WG] i=3,id=tk2,data=new_token2
[WG] i=4,id=pt,data=8080
[WG] i=5,id=mq,data=new_mqtt.duckdns.org
[WG] b:StayInCfgPortal:DRD
[WG] SSID=WIFI_GENERIC_51F485,PW=MyWIFI_GENERIC_51F485
[WG] IP=192.168.4.1,CH=10
WiFi-beginAP3: return1 = 7
WiFi-beginAP3: return2 = 7
C
Your stored Credentials :
Blynk Server1 = new_account.duckdns.org
Token1 = new_token1
Blynk Server2 = new_account.ddns.net
Token2 = new_token2
Port = 8080
MQTT Server = new_mqtt.duckdns.org
CCCCC
```

---

#### 2. SAMD_WiFi on ITSYBITSY_M4 using Custom WiFi Library

This is the terminal output when running [**SAMD_WiFi**](examples/SAMD_WiFi) example on **Adafruit SAMD51 ITSYBITSY_M4**:

#### 2.1 Open Config Portal

<p align="center">
    <img src="https://github.com/khoih-prog/WiFiManager_Generic_Lite/blob/main/pics/ESP_AT_Input_With_Scan.png">
</p>


```
Start SAMD_WiFi on ITSYBITSY_M4 with Custom using Custom WiFi Library
WiFiManager_Generic_Lite v1.7.0
[ESP_AT] Use ES8266-AT Command
WiFi shield init done
[WG] Hostname=SAMD-Master-Controller
Flag read = 0xffffffff
No doubleResetDetected
SetFlag write = 0xd0d01234
[WG] CCSum=0xe11e,RCSum=0xffffffff
[WG] InitCfgFile,sz=236
[WG] SaveEEPROM,Sz=1024,DataSz=0,WCSum=0xdb3
[WG] bg: isForcedConfigPortal = false
[WG] bg:Stay forever in CP:No ConfigDat
[WG] Scanning Network
[WG] scanWifiNetworks: Done, Scanned Networks n = 9
[WG] Sorting
[WG] Removing Dup
[WG] DUP AP:Waterhome
[WG] DUP AP:
[WG] WiFi networks found:
[WG] 1: HueNet1, -44dB
[WG] 2: HueNetTek, -32dB
[WG] 3: HueNet2, -58dB
[WG] 4: bacau, -82dB
[WG] 5: dlink-4F96, -86dB
[WG] 6: Waterhome, -88dB
[WG] 7: , -84dB
[WG] 9: BELL627, -63dB
[WG] SSID=WIFI_GENERIC_51F485,PW=MyWIFI_GENERIC_51F485
[WG] IP=192.168.4.1,CH=1
[WG] s:configTimeout = 0
Stop doubleResetDetecting
ClearFlag write = 0xd0d04321
C
```

#### 2.2 Got valid Credential from Config Portal, then connected to WiFi

```
Start SAMD_WiFi on ITSYBITSY_M4 with Custom using Custom WiFi Library
WiFiManager_Generic_Lite v1.7.0
[ESP_AT] Use ES8266-AT Command
WiFi shield init done
[WG] Hostname=SAMD-Master-Controller
Flag read = 0xd0d04321
No doubleResetDetected
SetFlag write = 0xd0d01234
[WG] CCSum=0x14eb,RCSum=0x14eb
[WG] ======= Start Stored Config Data =======
[WG] Hdr=WIFI_GENERIC,SSID=HueNet1,PW=12345678
[WG] SSID1=HueNet2,PW1=12345678
[WG] BName=Itsy-Bitsy-SAMD51
[WG] WiFi connected after time: 1
[WG] SSID:HueNet1,RSSI=-20
[WG] IP address:192.168.2.154
[WG] b:WOK
Stop doubleResetDetecting
ClearFlag write = 0xd0d04321
HHH
```
  
---
---

#### Debug

Debug is enabled by default on Serial. To disable, add at the beginning of sketch

```cpp
/* Comment this out to disable prints and save space */
#define DEBUG_WIFI_WEBSERVER_PORT     Serial
#define WIFI_GENERIC_DEBUG_OUTPUT     Serial

#define _WIFI_GENERIC_LOGLEVEL_       4

#define DRD_GENERIC_DEBUG             true
```

---

## Troubleshooting

If you get compilation errors, more often than not, you may need to install a newer version of the board's core, `Generic WiFi (WiFiNINA, WINC1500/WiFi101, ESP8266/ESP32-AT, etc.) module/shield` libraries or this library version.

Sometimes, the library will only work if you update the `Generic WiFi module/shield` core to the newer or older version because some function compatibility.

---
---


### Issues

Submit issues to: [WiFiManager_Generic_Lite issues](https://github.com/khoih-prog/WiFiManager_Generic_Lite/issues)

---
---

### TO DO

1. Support more boards, shields and libraries
2. Bug Searching and Killing

---

### DONE

 1. Permit EEPROM size and location configurable to avoid conflict with others.
 2. More flexible to configure reconnection timeout.
 3. For fresh config data, don't need to wait for connecting timeout before entering config portal.
 4. If the config data not entered completely (SSIDs, Passwords, etc.), entering config portal
 5. Add configurable Config Portal IP, SSID and Password
 6. Change Synch XMLHttpRequest to Async
 7. Add configurable Static IP, GW, Subnet Mask and 2 DNS Servers' IP Addresses.
 8. Add checksums
 9. Add support to **nRF52, SAMD21/SAMD51, STM32F/L/H/G/WB/MP1, Teensy, SAM-DUE**
10. Add support to **WiFiNINA, WINC1500/WiFi101, ESP8266/ESP32-AT, etc.** shields.
11. Add MultiWiFi features with auto(re)connect
12. Easy-to-use **Dynamic Parameters** without the necessity to write complicated ArduinoJSon functions
13. Permit to input special chars such as **%** and **#** into data fields.
14. Default Credentials and dynamic parameters
15. **DoubleDetectDetector** to force Config Portal when double reset is detected within predetermined time, default 10s.
16. Configurable Config Portal Title
17. Re-structure all examples to separate Credentials / Defines / Dynamic Params / Code so that you can change Credentials / Dynamic Params quickly for each device.
18. Add support to **Seeeduino SAMD21/SAMD51 boards (SEEED_WIO_TERMINAL, SEEED_FEMTO_M0, SEEED_XIAO_M0, Wio_Lite_MG126, WIO_GPS_BOARD, SEEEDUINO_ZERO, SEEEDUINO_LORAWAN, SEEED_GROVE_UI_WIRELESS, etc.)**
19. Add Table of Contents and Version String
20. Use more efficient **FlashStorage_STM32**](https://github.com/khoih-prog/FlashStorage_STM32) and [**FlashStorage_SAMD**](https://github.com/khoih-prog/FlashStorage_SAMD) library versions.
21. Configurable **Customs HTML Headers**, including Customs Style, Customs Head Elements, CORS Header
22. Add functions to control Config Portal from software or Virtual Switches.
23. Permit optionally inputting one set of WiFi SSID/PWD by using `REQUIRE_ONE_SET_SSID_PW == true`
24. Enforce WiFi Password minimum length of 8 chars
25. Enable **scan of WiFi networks** for selection in Configuration Portal
26. Add support to **Arduino Nano RP2040 Connect** using [**Arduino mbed OS for Nano boards**](https://github.com/arduino/ArduinoCore-mbed).
27. Add support to RP2040-based boards, such as **RASPBERRY_PI_PICO, ADAFRUIT_FEATHER_RP2040 and GENERIC_RP2040**, using [**Earle Philhower's arduino-pico** core](https://github.com/earlephilhower/arduino-pico).
28. Add support to RP2040-based boards, such as **RASPBERRY_PI_PICO, ADAFRUIT_FEATHER_RP2040 and GENERIC_RP2040**, using [**Arduino-mbed RP2040** core](https://github.com/arduino/ArduinoCore-mbed)
29. Add `LibraryPatches` for [**Adafruit_MQTT_Library**](https://github.com/adafruit/Adafruit_MQTT_Library) to fix compiler error for RP2040-based and many other boards.
30. Add support to **Arduino Nano RP2040 Connect** using [**Earle Philhower's arduino-pico** core](https://github.com/earlephilhower/arduino-pico).
31. Fix the blocking issue in loop() with configurable `WIFI_RECON_INTERVAL`
32. Update to be compatible with new `FlashStorage_SAMD`
33. Use better `FlashStorage_STM32` or `FlashStorage_STM32F1` library for STM32
34. Add support to generic SAMD21 boards : `__SAMD21E1xA__`, `__SAMD21G1xA__` and `__SAMD21J1xA__`
35. Optimize code by passing by `reference` instead of `value`
36. Optional `Board_Name` in Config Portal
37. Add optional `CONFIG_MODE_LED` to be `ON` when in Config Portal mode.
38. Add function `isConfigMode()` to signal system is in Config Portal mode
39. Use [WiFiMulti_Generic](https://github.com/khoih-prog/WiFiMulti_Generic) library to connect to the best of **multi-WiFi APs**, with **auto-checking / auto-reconnecting** features when WiFi connection is lost.


---
---
 
### Contributions and Thanks

Please help contribute to this project and add your name here.

1. Thanks to [Max Gerhardt in GitHub](https://github.com/maxgerhardt) and [in PIO](https://community.platformio.org/u/maxgerhardt) for the useful fix [**attachInterrupt() on wifi101 unidentified**](https://community.platformio.org/t/attachinterrupt-on-wifi101-unidentified/17543) to enable STM32F/L/H/G/WB/MP1 using ATWINC1500/WiFi101, leading to new v1.0.2
2. Thanks to [Michael H. "bizprof"](https://github.com/bizprof) to report bugs in 
  - [SAMD MultiWiFi issues when first WiFi SSID configured in CP is invalid or not available #6](https://github.com/khoih-prog/WiFiManager_NINA_Lite/issues/6) leading to v1.1.2.
  - [WiFiManager connection attempt to unconfigured ("blank") SSID after restart on SAMD #8](https://github.com/khoih-prog/WiFiManager_NINA_Lite/issues/8) leading to v1.1.3 and v1.2.0
3. Again thanks to [Michael H. "bizprof"](https://github.com/bizprof) to be `collaborator, co-author/maintainer` of this library. With the impressive new feature : 
  - `Enable scan of WiFi networks for selection in Configuration Portal`. Check [PR for v1.3.0 - Enable scan of WiFi networks #10](https://github.com/khoih-prog/WiFiManager_NINA_Lite/pull/10) leading to v1.3.0
4. Thanks to [tomtobback](https://github.com/tomtobback) to report issue [retries block the main loop #18](https://github.com/khoih-prog/WiFiManager_NINA_Lite/issues/18) leading to version v1.5.0 to fix the blocking issue in loop() with `WIFI_RECON_INTERVAL`.
5. Thanks to [nicogou](https://github.com/nicogou) to post enhancement request [Knowing when configuration mode is on or off #26](https://github.com/khoih-prog/WiFiManager_NINA_Lite/issues/26) leading to version v1.6.0 to add optional `CONFIG_MODE_LED` and function `isConfigMode()`

<table>
  <tr>
    <td align="center"><a href="https://github.com/maxgerhardt"><img src="https://github.com/maxgerhardt.png" width="100px;" alt="maxgerhardt"/><br /><sub><b>Maximilian Gerhardt</b></sub></a><br /></td>
    <td align="center"><a href="https://github.com/bizprof"><img src="https://github.com/bizprof.png" width="100px;" alt="bizprof"/><br /><sub><b>⭐️⭐️ Michael H. "bizprof"</b></sub></a><br /></td>
    <td align="center"><a href="https://github.com/tomtobback"><img src="https://github.com/tomtobback.png" width="100px;" alt="tomtobback"/><br /><sub><b>tomtobback</b></sub></a><br /></td>
    <td align="center"><a href="https://github.com/nicogou"><img src="https://github.com/nicogou.png" width="100px;" alt="nicogou"/><br /><sub><b>nicogou</b></sub></a><br /></td>
  </tr> 
</table>

---

### Contributing

If you want to contribute to this project:

- Report bugs and errors
- Ask for enhancements
- Create issues and pull requests
- Tell other people about this library

---

### License

- The library is licensed under [MIT](https://github.com/khoih-prog/WiFiManager_Generic_Lite/blob/main/LICENSE)

---

### Copyright

Copyright 2021- Khoi Hoang - Michale H.


