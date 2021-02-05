## WiFiManager_Generic_Lite (Light Weight Credentials / WiFi Manager for Generic WiFi (WiFiNINA, WiFi101, WiFiEsp, etc.)  modules/shields)

[![arduino-library-badge](https://www.ardu-badge.com/badge/WiFiManager_Generic_Lite.svg?)](https://www.ardu-badge.com/WiFiManager_Generic_Lite)
[![GitHub release](https://img.shields.io/github/release/khoih-prog/WiFiManager_Generic_Lite.svg)](https://github.com/khoih-prog/WiFiManager_Generic_Lite/releases)
[![GitHub](https://img.shields.io/github/license/mashape/apistatus.svg)](https://github.com/khoih-prog/WiFiManager_Generic_Lite/blob/main/LICENSE)
[![contributions welcome](https://img.shields.io/badge/contributions-welcome-brightgreen.svg?style=flat)](#Contributing)
[![GitHub issues](https://img.shields.io/github/issues/khoih-prog/WiFiManager_Generic_Lite.svg)](http://github.com/khoih-prog/WiFiManager_Generic_Lite/issues)

---
---

## Table of Contents

* [Why do we need this WiFiManager_Generic_Lite library](#why-do-we-need-this-wifimanager_generic_lite-library)
  * [Features](#features)
  * [Currently supported Boards](#currently-supported-boards)
  * [Currently supported WiFi shields/modules](#currently-supported-wifi-shieldsmodules)
* [Changelog](#changelog)
  * [Release v1.0.0](#release-v100)
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
* [How It Works](#how-it-works)
* [How to use](#how-to-use)
* [Examples](#examples)
  * [ 1. Mega_WiFi](examples/Mega_WiFi)
  * [ 2. MKR1000_WiFi101](examples/MKR1000_WiFi101)
  * [ 3. MKR1000_WiFi101_MQTT](examples/MKR1000_WiFi101_MQTT)
  * [ 4. nRF52_WiFi](examples/nRF52_WiFi)
  * [ 5. nRF52_WiFi_MQTT](examples/nRF52_WiFi_MQTT)
  * [ 6. SAM_DUE_WiFi](examples/SAM_DUE_WiFi)
  * [ 7. SAM_DUE_WiFi_MQTT](examples/SAM_DUE_WiFi_MQTT) 
  * [ 8. SAMD_WiFi](examples/SAMD_WiFi)
  * [ 9. SAMD_WiFi_MQTT](examples/SAMD_WiFi_MQTT)
  * [10. STM32_WiFi](examples/STM32_WiFi)
  * [11. STM32_WiFi_MQTT](examples/STM32_WiFi_MQTT)
  * [12. Teensy_WiFi](examples/Teensy_WiFi)
  * [13. Teensy_WiFi_MQTT](examples/Teensy_WiFi_MQTT)
* [So, how it works?](#so-how-it-works)
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
* [Debug Termimal Output Samples](#debug-terminal-output-samples)
  * [1. Open Config Portal](#1-open-config-portal)
  * [2. Received data from Config Portal](#2-received-data-from-config-portal)
  * [3. Got valid Credential from Config Portal, then connected to WiFi](#3-got-valid-credential-from-config-portal-then-connected-to-wifi)
  * [4. Lost a WiFi and autoconnect to another WiFi AP](#4-lost-a-wifi-and-autoconnect-to-another-wifi-ap)
  * [5. Reopen Config Portal if can't connect to any of the 2 WiFi APs](#5-reopen-config-portal-if-cant-connect-to-any-of-the-2-wifi-aps)
  * [6. DRD Not Detected](#6-drd-not-detected) 
  * [7. DRD detected and Config Portal is forcefully opened](#7drd-detected-and-config-portal-is-forcefully-opened)
* [Debug](#debug)
* [Troubleshooting](#troubleshooting)
* [Releases](#releases)
* [Issues](#issues)
* [TO DO](#to-do)
* [DONE](#done)
* [Contributions and Thanks](#contributions-and-thanks)
* [Contributing](#contributing)
* [License](#license)
* [Copyright](#copyright)

---
---

### Why do we need this [WiFiManager_Generic_Lite library](https://github.com/khoih-prog/WiFiManager_Generic_Lite)

#### Features

If you have used the full-fledge WiFiManager such as :

1. [`Tzapu WiFiManager`](https://github.com/tzapu/WiFiManager)
2. [`Ken Taylor WiFiManager`](https://github.com/kentaylor/WiFiManager)
3. [`Khoi Hoang ESP_WiFiManager`](https://github.com/khoih-prog/ESP_WiFiManager)

and have to write **complicated callback functions** to save custom parameters in SPIFFS/LittlFS/EEPROM, you'd appreciate the simplicity of this Light-Weight Credentials / WiFiManager.

This library is a Light Weight Credentials / WiFi Manager for Generic WiFi (WiFiNINA, WINC1500/WiFi101, WiFiEsp, etc.) modules/shields, specially designed to support **Teensy, SAM DUE, SAMD21 (Nano-33 IoT, Itsy-Bitsy M0, etc), SAMD51 (Itsy-Bitsy M4, Metro M4, Grand Central M4, Feather M4 Express, etc.), STM32F/L/H/G/WB/MP1 (F1, F2, F3, F4, F7, Nucleo-144, etc.), nRF52 (Adafruit NRF52840_FEATHER, NRF52832_FEATHER, NRF52840_FEATHER_SENSE, NRF52840_ITSYBITSY, NRF52840_CIRCUITPLAY, NRF52840_CLUE, NRF52840_METRO, NRF52840_PCA10056, PARTICLE_XENON, NINA_B302_ublox, NINA_B112_ublox, etc.), etc. boards running Generic WiFi modules/shields.** with smaller memory (64+K bytes)

The AVR-family boards (UNO, Nano, etc.) are **not supported** as they don't have enough memory to run Config Portal WebServer.

This is a Credentials / WiFi Connection Manager, permitting the addition of custom parameters to be configured in Config Portal. The parameters then will be saved automatically, **without the complicated callback functions** to handle data saving / retrieving.

You can also specify DHCP HostName, static AP and STA IP. Use much less memory compared to full-fledge WiFiManager. Config Portal will be auto-adjusted to match the number of dynamic custom parameters. Credentials are saved in EEPROM, (emulated-)EEPROM, FlashStorage_SAMD, FlashStorage_STM32 or DueFlashStorage.

The web configuration portal, served from the `Generic WiFi modules/shields` is operating as an access point (AP) with configurable static IP address or use default IP Address of 192.168.4.1

New recent features:

- **MultiWiFi** feature for configuring/auto(re)connecting **Generic WiFi (WiFiNINA, WINC1500/WiFi101, WiFiEsp, etc.)** shields to the available MultiWiFi APs at runtime.
- **DoubleDetectDetector** feature to force Config Portal when double reset is detected within predetermined time, default 10s.
- **Powerful-yet-simple-to-use feature to enable adding dynamic custom parameters** from sketch and input using the same Config Portal. Config Portal will be auto-adjusted to match the number of dynamic parameters.
- Optional default **Credentials as well as Dynamic parameters to be optionally autoloaded into Config Portal** to use or change instead of manually input.
- Dynamic custom parameters to be saved **automatically in non-volatile memory, such as Mega, Teensy EEPROM, SAMD EEPROM-emulated FlashStorage_SAMD, STM32F/L/H/G/WB/MP1 EEPROM-emulated FlashStorage_STM32 or SAM DUE DueFlashStorage**.
- Configurable **Config Portal Title** to be either BoardName or default undistinguishable names.
- Examples are designed to separate Credentials / Defines / Dynamic Params / Code so that you can change Credentials / Dynamic Params quickly for each device.
- Control Config Portal from software or Virtual Switches
- To permit autoreset after configurable timeout if DRD/MRD or non-persistent forced-CP
- Use new nRF52 LittleFS, SAMD FlashStorage_SAMD and STM32F/L/H/G/WB/MP1 FlashStorage_STM32 features


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
 6. **AVR Mega1280, 2560, ADK.**
 7. **STM32F/L/H/G/WB/MP1 boards (with 32+K Flash)**
  - Nucleo-144
  - Nucleo-64
  - Discovery
  - Generic STM32F0, STM32F1, STM32F2, STM32F3, STM32F4, STM32F7 (with 64+K Flash): x8 and up
  - STM32L0, STM32L1, STM32L4
  - STM32G0, STM32G4
  - STM32H7
  - STM32WB
  - STM32MP1
  - LoRa boards
  - 3-D printer boards
  - Generic Flight Controllers
  - Midatronics boards


#### Currently supported WiFi shields/modules

1. WiFiNINA using [`WiFiNINA_Generic library`](https://github.com/khoih-prog/WiFiNINA_Generic)
2. WiFi101 using [`WiFi101 library v0.16.1+`](https://github.com/arduino-libraries/WiFi101)
3. U-Blox W101, W102 using [`WiFiNINA_Generic library`](https://github.com/khoih-prog/WiFiNINA_Generic)
4. ESP826-AT command using [`WiFiEspAT library v1.3.0+`](https://github.com/jandrassy/WiFiEspAT)
5. ESP8266/ESP32-AT command using [`ESP_AT_Lib library v1.0.0+`](https://github.com/khoih-prog/ESP_AT_Lib)

---
---

## Changelog

### Release v1.0.0

1. Initial release to support many boards and Generic WiFi (WiFiNINA, WINC1500/WiFi101, WiFiEsp, etc.) using WiFiNINA_Generic, WiFi101, WiFiEsp, etc. libraries.

---
---

## Prerequisites

 1. [`Arduino IDE 1.8.13+` for Arduino](https://www.arduino.cc/en/Main/Software)
 2. [`Arduino Core for STM32 v1.9.0+`](https://github.com/khoih-prog/Arduino_Core_STM32) for STM32 boards
 3. [`Teensy core 1.51`](https://www.pjrc.com/teensy/td_download.html) for Teensy (4.1, 4.0, 3.6, 3.5, 3,2, 3.1, 3.0, LC) boards
 4. [`Arduino SAM DUE core 1.6.12+`](https://www.arduino.cc/en/Guide/ArduinoDue) for SAM DUE ARM Cortex-M3 boards
 5. [`Arduino SAMD core 1.8.11+`](https://www.arduino.cc/en/Guide/ArduinoM0) for SAMD ARM Cortex-M0+ boards
 6. [`Adafruit SAMD core 1.6.5+`](https://www.adafruit.com/) for SAMD ARM Cortex-M0+ and M4 boards (Nano 33 IoT, etc.)
 7. [`Seeeduino SAMD core 1.8.1+`](https://www.seeedstudio.com/) for SAMD21/SAMD51 boards (XIAO M0, Wio Terminal, etc.) 
 8. [`Adafruit nRF52 v0.21.0+`](www.adafruit.com) for nRF52 boards such as Adafruit NRF52840_FEATHER, NRF52832_FEATHER, NRF52840_FEATHER_SENSE, NRF52840_ITSYBITSY, NRF52840_CIRCUITPLAY, NRF52840_CLUE, NRF52840_METRO, NRF52840_PCA10056, PARTICLE_XENON, **NINA_B302_ublox**, etc.
 9. [`Functional-VLPP library v1.0.1+`](https://github.com/khoih-prog/functional-vlpp) to use server's lambda function. To install. check [![arduino-library-badge](https://www.ardu-badge.com/badge/Functional-Vlpp.svg?)](https://www.ardu-badge.com/Functional-Vlpp)
10. [`WiFiNINA_Generic library v1.8.2+`](https://github.com/khoih-prog/WiFiNINA_Generic). To install. check [![arduino-library-badge](https://www.ardu-badge.com/badge/WiFiNINA_Generic.svg?)](https://www.ardu-badge.com/WiFiNINA_Generic)
11. [`WiFiWebServer library v1.1.1+`](https://github.com/khoih-prog/WiFiWebServer). To install. check [![arduino-library-badge](https://www.ardu-badge.com/badge/WiFiWebServer.svg?)](https://www.ardu-badge.com/WiFiWebServer)
12. [`ESP_AT_Lib library v1.0.0+`](https://github.com/khoih-prog/ESP_AT_Lib) if using ESP8288/ESP32-AT shields. To install, check [![arduino-library-badge](https://www.ardu-badge.com/badge/ESP_AT_Lib.svg?)](https://www.ardu-badge.com/ESP_AT_Lib).
13. [`WiFi101 library v0.16.1+`](https://www.arduino.cc/en/Reference/WiFi101) if using WINC1500/WiFi101 shields (MKR1000, etc.)
14. [`WiFiEspAT library v1.3.0+`](https://github.com/jandrassy/WiFiEspAT) if using ESP8288/ESP32-AT shields.
15. [`FlashStorage_SAMD library v1.1.0+`](https://github.com/khoih-prog/FlashStorage_SAMD) for SAMD21 and SAMD51 boards (ZERO, MKR, NANO_33_IOT, M0, M0 Pro, AdaFruit Itsy-Bitsy M4, etc.)
16. [`FlashStorage_STM32 library v1.0.0+`](https://github.com/khoih-prog/FlashStorage_STM32) for STM32F/L/H/G/WB/MP1 boards.
17. [`DueFlashStorage library v1.0.0+`](https://github.com/sebnil/DueFlashStorage) for SAM DUE
18. [`Adafruit's LittleFS/InternalFS`](www.adafruit.com) for nRF52
19. [`DoubleResetDetector_Generic v1.0.3+`](https://github.com/khoih-prog/DoubleResetDetector_Generic). To install, check [![arduino-library-badge](https://www.ardu-badge.com/badge/DoubleResetDetector_Generic.svg?)](https://www.ardu-badge.com/DoubleResetDetector_Generic)

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
3. Install [**WiFiManager_Generic_Lite** library](https://platformio.org/lib/show/11761/WiFiManager_Generic_Lite) by using [Library Manager](https://platformio.org/lib/show/11761/WiFiManager_Generic_Lite/installation). Search for **WiFiManager_Generic_Lite** in [Platform.io Author's Libraries](https://platformio.org/lib/search?query=author:%22Khoi%20Hoang%22)
4. Use included [platformio.ini](platformio/platformio.ini) file from examples to ensure that all dependent libraries will installed automatically. Please visit documentation for the other options and examples at [Project Configuration File](https://docs.platformio.org/page/projectconf.html)

---
---

### Packages' Patches

#### 1. For Adafruit nRF52840 and nRF52832 boards

**To be able to compile, run and automatically detect and display BOARD_NAME on nRF52840/nRF52832 boards**, you have to copy the whole [nRF52 0.21.0](Packages_Patches/adafruit/hardware/nrf52/0.21.0) directory into Adafruit nRF52 directory (~/.arduino15/packages/adafruit/hardware/nrf52/0.21.0). 

Supposing the Adafruit nRF52 version is 0.21.0. These files must be copied into the directory:
- `~/.arduino15/packages/adafruit/hardware/nrf52/0.21.0/platform.txt`
- `~/.arduino15/packages/adafruit/hardware/nrf52/0.21.0/boards.txt`
- `~/.arduino15/packages/adafruit/hardware/nrf52/0.21.0/variants/NINA_B302_ublox/variant.h`
- `~/.arduino15/packages/adafruit/hardware/nrf52/0.21.0/variants/NINA_B302_ublox/variant.cpp`
- `~/.arduino15/packages/adafruit/hardware/nrf52/0.21.0/variants/NINA_B112_ublox/variant.h`
- `~/.arduino15/packages/adafruit/hardware/nrf52/0.21.0/variants/NINA_B112_ublox/variant.cpp`
- **`~/.arduino15/packages/adafruit/hardware/nrf52/0.21.0/cores/nRF5/Udp.h`**

Whenever a new version is installed, remember to copy these files into the new version directory. For example, new version is x.yy.z
These files must be copied into the directory:

- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/platform.txt`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/boards.txt`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/variants/NINA_B302_ublox/variant.h`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/variants/NINA_B302_ublox/variant.cpp`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/variants/NINA_B112_ublox/variant.h`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/variants/NINA_B112_ublox/variant.cpp`
- **`~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/cores/nRF5/Udp.h`**

#### 2. For Teensy boards
 
 **To be able to compile and run on Teensy boards**, you have to copy the files in [**Packages_Patches for Teensy directory**](Packages_Patches/hardware/teensy/avr) into Teensy hardware directory (./arduino-1.8.13/hardware/teensy/avr/boards.txt). 

Supposing the Arduino version is 1.8.13. These files must be copied into the directory:

- `./arduino-1.8.13/hardware/teensy/avr/boards.txt`
- `./arduino-1.8.13/hardware/teensy/avr/cores/teensy/Stream.h`
- `./arduino-1.8.13/hardware/teensy/avr/cores/teensy3/Stream.h`
- `./arduino-1.8.13/hardware/teensy/avr/cores/teensy4/Stream.h`

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
 
 ***To be able to compile without error and automatically detect and display BOARD_NAME on Arduino SAMD (Nano-33-IoT, etc) boards***, you have to copy the whole [Arduino SAMD cores 1.8.11](Packages_Patches/arduino/hardware/samd/1.8.11) directory into Arduino SAMD directory (~/.arduino15/packages/arduino/hardware/samd/1.8.11).
 
#### For core version v1.8.10+

Supposing the Arduino SAMD version is 1.8.11. Now only one file must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/samd/1.8.11/platform.txt`

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
 
 ***To be able to automatically detect and display BOARD_NAME on Adafruit SAMD (Itsy-Bitsy M4, etc) boards***, you have to copy the file [Adafruit SAMD platform.txt](Packages_Patches/adafruit/hardware/samd/1.6.5) into Adafruit samd directory (~/.arduino15/packages/adafruit/hardware/samd/1.6.5). 

Supposing the Adafruit SAMD core version is 1.6.5. This file must be copied into the directory:

- `~/.arduino15/packages/adafruit/hardware/samd/1.6.5/platform.txt`

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz
This file must be copied into the directory:

- `~/.arduino15/packages/adafruit/hardware/samd/x.yy.zz/platform.txt`

#### 6. For Seeeduino SAMD boards
 
 ***To be able to automatically detect and display BOARD_NAME on Seeeduino SAMD (XIAO M0, Wio Terminal, etc) boards***, you have to copy the file [Seeeduino SAMD platform.txt](Packages_Patches/Seeeduino/hardware/samd/1.8.1) into Adafruit samd directory (~/.arduino15/packages/Seeeduino/hardware/samd/1.8.1). 

Supposing the Seeeduino SAMD core version is 1.8.1. This file must be copied into the directory:

- `~/.arduino15/packages/Seeeduino/hardware/samd/1.8.1/platform.txt`

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz
This file must be copied into the directory:

- `~/.arduino15/packages/Seeeduino/hardware/samd/x.yy.zz/platform.txt`

#### 7. For STM32 boards

**To use Serial1 on some STM32 boards without Serial1 definition (Nucleo-144 NUCLEO_F767ZI, Nucleo-64 NUCLEO_L053R8, etc.) boards**, you have to copy the files [STM32 variant.h](Packages_Patches/STM32/hardware/stm32/1.9.0) into STM32 stm32 directory (~/.arduino15/packages/STM32/hardware/stm32/1.9.0). You have to modify the files corresponding to your boards, this is just an illustration how to do.

Supposing the STM32 stm32 core version is 1.9.0. These files must be copied into the directory:

- `~/.arduino15/packages/STM32/hardware/stm32/1.9.0/variants/NUCLEO_F767ZI/variant.h` for Nucleo-144 NUCLEO_F767ZI.
- `~/.arduino15/packages/STM32/hardware/stm32/1.9.0/variants/NUCLEO_L053R8/variant.h` for Nucleo-64 NUCLEO_L053R8.

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz,
theses files must be copied into the corresponding directory:

- `~/.arduino15/packages/STM32/hardware/stm32/x.yy.zz/variants/NUCLEO_F767ZI/variant.h`
- `~/.arduino15/packages/STM32/hardware/stm32/x.yy.zz/variants/NUCLEO_L053R8/variant.h`


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

- Include in your sketch

```cpp
// Must be before #include <WiFiManager_Generic_Lite_SAMD.h>
// Start location in EEPROM to store config data. Default 0
// Config data Siz, not including your custom data, currently is 84 bytes)
#define EEPROM_START      0

#include <WiFiManager_Generic_Lite_SAMD.h>

WiFiManager_Generic_Lite* WiFiManager_Generic;
```

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

- If you don't need to add dynamic parameters, use the following in sketch

```
#define USE_DYNAMIC_PARAMETERS      false
```

- When you want to open a config portal, just add

```cpp
WiFiManager_Generic = new WiFiManager_Generic_Lite();
WiFiManager_Generic->begin();
```

- To not use default AP WiFi Channel 10 to avoid conflict with other WiFi APs, call 

```cpp
WiFiManager_Generic->setConfigPortalChannel(newChannel);
```

- To use different static AP IP (not use default `192.168.4.1`), call

```cpp
WiFiManager_Generic->setConfigPortalIP(IPAddress(xxx,xxx,xxx,xxx));
```

- To set custom DHCP HostName, cal
 
```
  // Set customized DHCP HostName
  WiFiManager_Generic->begin("SAMD_ABCDEF");
```
 
or just use the default Hostname, for example "SAMD_XXXXXX" for SAMD

```
  //Or use default Hostname "WIFI_GENERIC_XXXXXX"
  //WiFiManager_Generic->begin();
```

While in AP mode, connect to it using its `SSID` (WIFI_GENERIC_XXXXXX) / `Password` ("MyWIFI_GENERIC_XXXXXX"), then open a browser to the Portal AP IP, default `192.168.4.1`, configure wifi then click **Save**. The Credentials / WiFi connection information will be saved in non-volatile memory. It will then autoconnect.


Once Credentials / WiFi network information is saved in the host non-volatile memory, it will try to autoconnect to WiFi every time it is started, without requiring any function calls in the sketch.

---
---

### Examples

 1. [Mega_WiFi](examples/Mega_WiFi)
 2. [MKR1000_WiFi101](examples/MKR1000_WiFi101)
 3. [MKR1000_WiFi101_MQTT](examples/MKR1000_WiFi101_MQTT)
 4. [nRF52_WiFi](examples/nRF52_WiFi)
 5. [nRF52_WiFi_MQTT](examples/nRF52_WiFi_MQTT)
 6. [SAM_DUE_WiFi](examples/SAM_DUE_WiFi)
 7. [SAM_DUE_WiFi_MQTT](examples/SAM_DUE_WiFi_MQTT) 
 8. [SAMD_WiFi](examples/SAMD_WiFi)
 9. [SAMD_WiFi_MQTT](examples/SAMD_WiFi_MQTT)
10. [STM32_WiFi](examples/STM32_WiFi)
11. [STM32_WiFi_MQTT](examples/STM32_WiFi_MQTT) 
12. [Teensy_WiFi](examples/Teensy_WiFi)
13. [Teensy_WiFi_MQTT](examples/Teensy_WiFi_MQTT)

---
---

## So, how it works?

In `Configuration Portal Mode`, it starts an AP called `WIFI_GENERIC_XXXXXX`. Connect to it using the `configurable password` you can define in the code. For example, `MyWIFI_GENERIC_XXXXXX` (see examples):

After you connected, please, go to http://192.168.4.1 or newly configured AP IP, you'll see this `Main` page:

<p align="center">
    <img src="https://github.com/khoih-prog/WiFiManager_Generic_Lite/blob/main/pics/Main.png">
</p>

Enter your credentials, 

<p align="center">
    <img src="https://github.com/khoih-prog/WiFiManager_Generic_Lite/blob/main/pics/Input.png">
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

#### 1. To always load [Default Credentials](examples//Credentials.h) and override Config Portal data

```
// Used mostly for development and debugging. FORCES default values to be loaded each run.
// Config Portal data input will be ignored and overridden by DEFAULT_CONFIG_DATA
bool LOAD_DEFAULT_CONFIG_DATA = true;
```

#### 2. To load [Default Credentials](examples//Credentials.h) when there is no valid Credentials.

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

```cpp
#include "defines.h"
#include "Credentials.h"
#include "dynamicParams.h"

void heartBeatPrint(void)
{
  static int num = 1;

  if (WiFi.status() == WL_CONNECTED)
    Serial.print(F("H"));        // H means connected to WiFi
  else
    Serial.print(F("F"));        // F means not connected to WiFi

  if (num == 80)
  {
    Serial.println();
    num = 1;
  }
  else if (num++ % 10 == 0)
  {
    Serial.print(F(" "));
  }
}

void check_status()
{
  static unsigned long checkstatus_timeout = 0;

  //KH
#define HEARTBEAT_INTERVAL    20000L
  // Print hearbeat every HEARTBEAT_INTERVAL (20) seconds.
  if ((millis() > checkstatus_timeout) || (checkstatus_timeout == 0))
  {
    heartBeatPrint();
    checkstatus_timeout = millis() + HEARTBEAT_INTERVAL;
  }
}

WiFiManager_Generic_Lite* WiFiManager_Generic;

void setup()
{
  // Debug console
  Serial.begin(115200);
  while (!Serial);

  delay(200);

  Serial.print(F("\nStart SAMD_WiFi on ")); Serial.print(BOARD_NAME);
  Serial.print(F(" with ")); Serial.println(SHIELD_TYPE);
  Serial.println(WIFI_MANAGER_GENERIC_LITE_VERSION);


  WiFiManager_Generic = new WiFiManager_Generic_Lite();

  // Optional to change default AP IP(192.168.4.1) and channel(10)
  //WiFiManager_Generic->setConfigPortalIP(IPAddress(192, 168, 120, 1));
  //WiFiManager_Generic->setConfigPortalChannel(1);

  // Set customized DHCP HostName
  WiFiManager_Generic->begin(HOST_NAME);
  //Or use default Hostname "SAMD-WIFI-XXXXXX"
  //WiFiManager_Generic->begin();
  
}

#if USE_DYNAMIC_PARAMETERS
void displayCredentials(void)
{
  Serial.println("\nYour stored Credentials :");

  for (uint16_t i = 0; i < NUM_MENU_ITEMS; i++)
  {
    Serial.println(String(myMenuItems[i].displayName) + " = " + myMenuItems[i].pdata);
  }
}
#endif

void loop()
{
  WiFiManager_Generic->run();
  check_status();

#if USE_DYNAMIC_PARAMETERS
  static bool displayedCredentials = false;

  if (!displayedCredentials)
  {
    for (uint16_t i = 0; i < NUM_MENU_ITEMS; i++)
    {
      if (!strlen(myMenuItems[i].pdata))
      {
        break;
      }

      if ( i == (NUM_MENU_ITEMS - 1) )
      {
        displayedCredentials = true;
        displayCredentials();
      }
    }
  }
#endif
}
```
---

#### 2. File [defines.h](examples/SAMD_WiFi/defines.h)

```cpp
#ifndef defines_h
#define defines_h

/* Comment this out to disable prints and save space */
#define DEBUG_WIFI_WEBSERVER_PORT     Serial
#define WIFI_GENERIC_DEBUG_OUTPUT     Serial

#define _WIFI_GENERIC_LOGLEVEL_       1

#define DRD_GENERIC_DEBUG             true

#if    ( defined(ARDUINO_SAMD_ZERO) || defined(ARDUINO_SAMD_MKR1000) || defined(ARDUINO_SAMD_MKRWIFI1010) \
      || defined(ARDUINO_SAMD_NANO_33_IOT) || defined(ARDUINO_SAMD_MKRFox1200) || defined(ARDUINO_SAMD_MKRWAN1300) || defined(ARDUINO_SAMD_MKRWAN1310) \
      || defined(ARDUINO_SAMD_MKRGSM1400) || defined(ARDUINO_SAMD_MKRNB1500) || defined(ARDUINO_SAMD_MKRVIDOR4000) || defined(__SAMD21G18A__) \
      || defined(ARDUINO_SAMD_CIRCUITPLAYGROUND_EXPRESS) || defined(__SAMD21E18A__) || defined(__SAMD51__) || defined(__SAMD51J20A__) || defined(__SAMD51J19A__) \
      || defined(__SAMD51G19A__) || defined(__SAMD51P19A__) || defined(__SAMD21G18A__) )
  #if defined(WIFI_GENERIC_USE_SAMD)
    #undef WIFI_GENERIC_USE_SAMD
    #undef WIFI_USE_SAMD
  #endif
  #define WIFI_GENERIC_USE_SAMD      true
  #define WIFI_USE_SAMD          true
#else
  #error This code is intended to run only on the SAMD boards ! Please check your Tools->Board setting.
#endif

#if defined(WIFI_GENERIC_USE_SAMD)

  #if ( defined(ARDUINO_SAMD_ZERO) && !defined(SEEED_XIAO_M0) )
    #define BOARD_TYPE      "SAMD Zero"
  #elif defined(ARDUINO_SAMD_MKR1000)
    #define BOARD_TYPE      "SAMD MKR1000"
  #elif defined(ARDUINO_SAMD_MKRWIFI1010)
    #define BOARD_TYPE      "SAMD MKRWIFI1010"
  #elif defined(ARDUINO_SAMD_NANO_33_IOT)
    #define BOARD_TYPE      "SAMD NANO_33_IOT"
  #elif defined(ARDUINO_SAMD_MKRFox1200)
    #define BOARD_TYPE      "SAMD MKRFox1200"
  #elif ( defined(ARDUINO_SAMD_MKRWAN1300) || defined(ARDUINO_SAMD_MKRWAN1310) )
    #define BOARD_TYPE      "SAMD MKRWAN13X0"
  #elif defined(ARDUINO_SAMD_MKRGSM1400)
    #define BOARD_TYPE      "SAMD MKRGSM1400"
  #elif defined(ARDUINO_SAMD_MKRNB1500)
    #define BOARD_TYPE      "SAMD MKRNB1500"
  #elif defined(ARDUINO_SAMD_MKRVIDOR4000)
    #define BOARD_TYPE      "SAMD MKRVIDOR4000"
  #elif defined(ARDUINO_SAMD_CIRCUITPLAYGROUND_EXPRESS)
    #define BOARD_TYPE      "SAMD ARDUINO_SAMD_CIRCUITPLAYGROUND_EXPRESS"
  #elif defined(ADAFRUIT_FEATHER_M0_EXPRESS)
    #define BOARD_TYPE      "SAMD21 ADAFRUIT_FEATHER_M0_EXPRESS"
  #elif defined(ADAFRUIT_METRO_M0_EXPRESS)
    #define BOARD_TYPE      "SAMD21 ADAFRUIT_METRO_M0_EXPRESS"
  #elif defined(ADAFRUIT_CIRCUITPLAYGROUND_M0)
    #define BOARD_TYPE      "SAMD21 ADAFRUIT_CIRCUITPLAYGROUND_M0"
  #elif defined(ADAFRUIT_GEMMA_M0)
    #define BOARD_TYPE      "SAMD21 ADAFRUIT_GEMMA_M0"
  #elif defined(ADAFRUIT_TRINKET_M0)
    #define BOARD_TYPE      "SAMD21 ADAFRUIT_TRINKET_M0"
  #elif defined(ADAFRUIT_ITSYBITSY_M0)
    #define BOARD_TYPE      "SAMD21 ADAFRUIT_ITSYBITSY_M0"
  #elif defined(ARDUINO_SAMD_HALLOWING_M0)
    #define BOARD_TYPE      "SAMD21 ARDUINO_SAMD_HALLOWING_M0"
  #elif defined(ADAFRUIT_METRO_M4_EXPRESS)
    #define BOARD_TYPE      "SAMD51 ADAFRUIT_METRO_M4_EXPRESS"
  #elif defined(ADAFRUIT_GRAND_CENTRAL_M4)
    #define BOARD_TYPE      "SAMD51 ADAFRUIT_GRAND_CENTRAL_M4"
  #elif defined(ADAFRUIT_FEATHER_M4_EXPRESS)
    #define BOARD_TYPE      "SAMD51 ADAFRUIT_FEATHER_M4_EXPRESS"
  #elif defined(ADAFRUIT_ITSYBITSY_M4_EXPRESS)
    #define BOARD_TYPE      "SAMD51 ADAFRUIT_ITSYBITSY_M4_EXPRESS"
  #elif defined(ADAFRUIT_TRELLIS_M4_EXPRESS)
    #define BOARD_TYPE      "SAMD51 ADAFRUIT_TRELLIS_M4_EXPRESS"
  #elif defined(ADAFRUIT_PYPORTAL)
    #define BOARD_TYPE      "SAMD51 ADAFRUIT_PYPORTAL"
  #elif defined(ADAFRUIT_PYPORTAL_M4_TITANO)
    #define BOARD_TYPE      "SAMD51 ADAFRUIT_PYPORTAL_M4_TITANO"
  #elif defined(ADAFRUIT_PYBADGE_M4_EXPRESS)
    #define BOARD_TYPE      "SAMD51 ADAFRUIT_PYBADGE_M4_EXPRESS"
  #elif defined(ADAFRUIT_METRO_M4_AIRLIFT_LITE)
    #define BOARD_TYPE      "SAMD51 ADAFRUIT_METRO_M4_AIRLIFT_LITE"
  #elif defined(ADAFRUIT_PYGAMER_M4_EXPRESS)
    #define BOARD_TYPE      "SAMD51 ADAFRUIT_PYGAMER_M4_EXPRESS"
  #elif defined(ADAFRUIT_PYGAMER_ADVANCE_M4_EXPRESS)
    #define BOARD_TYPE      "SAMD51 ADAFRUIT_PYGAMER_ADVANCE_M4_EXPRESS"
  #elif defined(ADAFRUIT_PYBADGE_AIRLIFT_M4)
    #define BOARD_TYPE      "SAMD51 ADAFRUIT_PYBADGE_AIRLIFT_M4"
  #elif defined(ADAFRUIT_MONSTER_M4SK_EXPRESS)
    #define BOARD_TYPE      "SAMD51 ADAFRUIT_MONSTER_M4SK_EXPRESS"
  #elif defined(ADAFRUIT_HALLOWING_M4_EXPRESS)
    #define BOARD_TYPE      "SAMD51 ADAFRUIT_HALLOWING_M4_EXPRESS"
  #elif defined(SEEED_WIO_TERMINAL)
    #define BOARD_TYPE      "SAMD SEEED_WIO_TERMINAL"
  #elif defined(SEEED_FEMTO_M0)
    #define BOARD_TYPE      "SAMD SEEED_FEMTO_M0"
  #elif defined(SEEED_XIAO_M0)
    #define BOARD_TYPE      "SAMD SEEED_XIAO_M0"
  #elif defined(Wio_Lite_MG126)
    #define BOARD_TYPE      "SAMD SEEED Wio_Lite_MG126"
  #elif defined(WIO_GPS_BOARD)
    #define BOARD_TYPE      "SAMD SEEED WIO_GPS_BOARD"
  #elif defined(SEEEDUINO_ZERO)
    #define BOARD_TYPE      "SAMD SEEEDUINO_ZERO"
  #elif defined(SEEEDUINO_LORAWAN)
    #define BOARD_TYPE      "SAMD SEEEDUINO_LORAWAN"
  #elif defined(SEEED_GROVE_UI_WIRELESS)
    #define BOARD_TYPE      "SAMD SEEED_GROVE_UI_WIRELESS"
  #elif defined(__SAMD21E18A__)
    #define BOARD_TYPE      "SAMD21E18A"
  #elif defined(__SAMD21G18A__)
    #define BOARD_TYPE      "SAMD21G18A"
  #elif defined(__SAMD51G19A__)
    #define BOARD_TYPE      "SAMD51G19A"
  #elif defined(__SAMD51J19A__)
    #define BOARD_TYPE      "SAMD51J19A"
  #elif defined(__SAMD51J20A__)
    #define BOARD_TYPE      "SAMD51J20A"
  #elif defined(__SAM3X8E__)
    #define BOARD_TYPE      "SAM3X8E"
  #elif defined(__CPU_ARC__)
    #define BOARD_TYPE      "CPU_ARC"
  #elif defined(__SAMD51__)
    #define BOARD_TYPE      "SAMD51"
  #else
    #define BOARD_TYPE      "SAMD Unknown"
  #endif

#endif

// Start location in EEPROM to store config data. Default 0
// Config data Size currently is 128 bytes)
#define EEPROM_START              0
#define EEPROM_SIZE               (2 * 1024)

/////////////////////////////////////////////

#define USE_WIFI_NINA             true
#define USE_WIFI101               false
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
#define CONFIG_TIMEOUT                      120000L

#define USE_DYNAMIC_PARAMETERS              true

#include <WiFiManager_Generic_Lite_SAMD.h>

#define HOST_NAME   "SAMD-Master-Controller"

#ifdef LED_BUILTIN
  #define LED_PIN     LED_BUILTIN
#else
  #define LED_PIN     13
#endif

#endif      //defines_h
```
---

#### 3. File [Credentials.h](examples/SAMD_WiFi/Credentials.h)

```cpp
#ifndef Credentials_h
#define Credentials_h

#include "defines.h"

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


#endif    //Credentials_h
```
---

#### 4. File [dynamicParams.h](examples/SAMD_WiFi/dynamicParams.h)

```cpp
#ifndef dynamicParams_h
#define dynamicParams_h

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


#endif      //dynamicParams_h
```
---
---


### Debug Terminal output Samples

This is the terminal output when running [**SAMD_WiFi**](examples/SAMD_WiFi) example on **Nano-33 IoT**:

#### 1. Open Config Portal

```
Start SAMD_WiFi on SAMD_NANO_33_IOT with WiFiNINA using WiFiNINA_Generic Library
WiFiManager_Generic_Lite v1.0.0
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
F
Your stored Credentials :
Blynk Server1 = account.duckdns.org
Token1 = token1
Blynk Server2 = account.ddns.net
Token2 = token2
Port = 8080
MQTT Server = mqtt.duckdns.org
Stop doubleResetDetecting
ClearFlag write = 0xd0d04321
FFFFFFFFF
```

#### 2. Received data from Config Portal

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

#### 3. Got valid Credential from Config Portal, then connected to WiFi

```
Start SAMD_WiFi on SAMD_NANO_33_IOT with WiFiNINA using WiFiNINA_Generic Library
WiFiManager_Generic_Lite v1.0.0
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
[WG] ConMultiWifi
[WG] con2WF:SSID=HueNet1,PW=12345678
[WG] Remaining retry_time=3
[WG] WOK, lastConnectedIndex=0
[WG] con2WF:OK
[WG] SSID=HueNet1,RSSI=-18
[WG] IP=192.168.2.148
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

#### 4. Lost a WiFi and autoconnect to another WiFi AP

```
[WG] r:Check&WLost                      <=== Lost primary WiFi
[WG] r:WLost.ReconW
[WG] ConMultiWifi
[WG] Using index=1, lastConnectedIndex=0
[WG] con2WF:SSID=HueNet2,PW=****        <=== Connect secondary WiFi
[WG] Remaining retry_time=2
WiFi-begin: return1 = 3
WiFi-begin: return2 = 3
[WG] WOK, lastConnectedIndex=1
[WG] con2WF:OK                          <=== Success
[WG] SSID=HueNet2,RSSI=-48
[WG] IP=192.168.2.105
[WG] r:WOK
HHHHHHHHHH HHHHHHHHHH
```

#### 5. Reopen Config Portal if can't connect to any of the 2 WiFi APs

```
Start SAMD_WiFi on SAMD_NANO_33_IOT with WiFiNINA using WiFiNINA_Generic Library
WiFiManager_Generic_Lite v1.0.0
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
F
Your stored Credentials :
Blynk Server1 = new_account.duckdns.org
Token1 = new_token1
Blynk Server2 = new_account.ddns.net
Token2 = new_token2
Port = 8080
MQTT Server = new_mqtt.duckdns.org
FF
```

#### 6. DRD Not Detected:

```
Start SAMD_WiFi on SAMD_NANO_33_IOT with WiFiNINA using WiFiNINA_Generic Library
WiFiManager_Generic_Lite v1.0.0
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
[WG] con2WF:SSID=HueNet1,PW=****
[WG] Remaining retry_time=3
WiFi-begin: return1 = 3
WiFi-begin: return2 = 3
[WG] WOK, lastConnectedIndex=0
[WG] con2WF:OK
[WG] SSID=HueNet1,RSSI=-21
[WG] IP=192.168.2.105
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

#### 7.DRD detected and Config Portal is forcefully opened

```
Start SAMD_WiFi on SAMD_NANO_33_IOT with WiFiNINA using WiFiNINA_Generic Library
WiFiManager_Generic_Lite v1.0.0
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
F
Your stored Credentials :
Blynk Server1 = new_account.duckdns.org
Token1 = new_token1
Blynk Server2 = new_account.ddns.net
Token2 = new_token2
Port = 8080
MQTT Server = new_mqtt.duckdns.org

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

## Troubleshooting

If you get compilation errors, more often than not, you may need to install a newer version of the board's core, `Generic WiFi (WiFiNINA, WINC1500/WiFi101, ESP8266/ESP32-AT, etc.) module/shield` libraries or this library version.

Sometimes, the library will only work if you update the `Generic WiFi module/shield` core to the newer or older version because some function compatibility.

---
---

## Releases
 
### Release v1.0.0

1. Initial release to support many boards and Generic WiFi (WiFiNINA, WINC1500, ESP8266/ESP32-AT, etc.) using WiFiNINA_Generic, WiFi101, WiFiEsp, etc. libraries.

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
 9. Add support to **nRF52, SAMD21/SAMD51, STM32F/L/H/G/WB/MP1, Teensy, SAM-DUE, Mega**
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
20. Use more efficient [FlashStorage_STM32](https://github.com/khoih-prog/FlashStorage_STM32) and [FlashStorage_SAMD](https://github.com/khoih-prog/FlashStorage_SAMD) library versions.

---
---
 
### Contributions and Thanks

Please help contribute to this project and add your name here.

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

Copyright 2021- Khoi Hoang


