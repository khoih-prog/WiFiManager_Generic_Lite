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

* [Changelog](#changelog)
  * [Release v1.8.0](#release-v180)
  * [Release v1.7.1](#release-v171)
  * [Release v1.7.0](#release-v170)
  * [Release v1.6.0](#release-v160)
  * [Release v1.5.1](#release-v151)
  * [Major Release v1.5.0](#major-release-v150)
  * [Release v1.4.1](#release-v141)
  * [Major Release v1.4.0](#major-release-v140)
  * [Major Release v1.3.0](#major-release-v130)
  * [Release v1.2.0](#release-v120)
  * [Release v1.1.3](#release-v113)
  * [Release v1.1.2](#release-v112)
  * [Major Release v1.1.0](#major-release-v110)
  * [Release v1.0.2](#release-v102)
  * [Release v1.0.1](#release-v101)
  * [Release v1.0.0](#release-v100)

---
---


## Changelog

### Release v1.8.0

1. Add support to Realtek RTL8720DN, RTL8722DM and RTL8722CSM using [AmebaD core](https://github.com/ambiot/ambd_arduino) and [FlashStorage_RTL8720 library](https://github.com/khoih-prog/FlashStorage_RTL8720). RTL8720DN WiFi can use either 2.4GHz or 5GHz band.
2. Restructure library
3. Add and Update examples
4. Update `Packages' Patches`

### Release v1.7.1

1. Optimize code

### Release v1.7.0

1. Use [WiFiMulti_Generic](https://github.com/khoih-prog/WiFiMulti_Generic) library to connect to the best of **multi-WiFi APs**, with **auto-checking / auto-reconnecting** features when WiFi connection is lost.
2. Update `Packages' Patches`

### Release v1.6.0

1. Optimize code by passing by `reference` instead of `value`
2. Optional `Board_Name` in Config Portal. Check [option to remove board name from web page #25](https://github.com/khoih-prog/WiFiManager_Generic_Lite/issues/25)
3. Add optional `CONFIG_MODE_LED` to be `ON` when in Config Portal mode. Check [Knowing when configuration mode is on or off #26](https://github.com/khoih-prog/WiFiManager_Generic_Lite/issues/26)
4. Add function `isConfigMode()` to signal system is in Config Portal mode.
5. Update `Packages' Patches`

### Release v1.5.1

1. Update to be compatible with new `FlashStorage_SAMD`
2. Use better `FlashStorage_STM32` or `FlashStorage_STM32F1` library for STM32
3. Add support to generic SAMD21 boards : `__SAMD21E1xA__`, `__SAMD21G1xA__` and `__SAMD21J1xA__`
4. Update `Packages' Patches`

### Major Release v1.5.0

1. Add support to RP2040-based boards, such as **NANO_RP2040_CONNECT**, using [**Earle Philhower's arduino-pico** core](https://github.com/earlephilhower/arduino-pico)
2. Fix the blocking issue in loop(). Check [retries block the main loop #18](https://github.com/khoih-prog/WiFiManager_Generic_Lite/issues/18)
3. Configurable `WIFI_RECON_INTERVAL`. Check [retries block the main loop #18](https://github.com/khoih-prog/WiFiManager_Generic_Lite/issues/18#issuecomment-1006197561)
4. Update `Packages' Patches`

### Release v1.4.1

1. Update `platform.ini` and `library.json` to use original `khoih-prog` instead of `khoih.prog` after PIO fix
2. Update `Packages' Patches`

### Major Release v1.4.0

1. Add support to RP2040-based boards, such as **RASPBERRY_PI_PICO, ADAFRUIT_FEATHER_RP2040 and GENERIC_RP2040**, using [**Earle Philhower's arduino-pico** core](https://github.com/earlephilhower/arduino-pico).
2. Add support to RP2040-based boards, such as **Nano_RP2040_Connect, RASPBERRY_PI_PICO, ADAFRUIT_FEATHER_RP2040 and GENERIC_RP2040**, using [**Arduino-mbed RP2040** core](https://github.com/arduino/ArduinoCore-mbed).
3. Update `Packages' Patches`
4. Add `LibraryPatches` for [**Adafruit_MQTT_Library**](https://github.com/adafruit/Adafruit_MQTT_Library) to fix compiler error for RP2040-based and many other boards.

### Major Release v1.3.0

1. Enable scan of WiFi networks for selection in Configuration Portal. Check [PR for v1.3.0 - Enable scan of WiFi networks #10](https://github.com/khoih-prog/WiFiManager_Generic_Lite/pull/10). Now you can select optional **SCAN_WIFI_NETWORKS**, **MANUAL_SSID_INPUT_ALLOWED** to be able to manually input SSID, not only from a scanned SSID lists and **MAX_SSID_IN_LIST** (from 2-6 for ESP8266-AT or 2-15 for other)
2. Minor enhancement to not display garbage when data is invalid
3. Tested with new [Arduino Core for STM32 v2.0.0](https://github.com/stm32duino/Arduino_Core_STM32) and add support to new STM32L5 boards.


### Release v1.2.0

1. Permit optionally inputting one set of WiFi SSID/PWD by using `REQUIRE_ONE_SET_SSID_PW == true`
2. Enforce WiFi Password minimum length of 8 chars
3. Enhance MultiWiFi connection logic

### Release v1.1.3

1. Fix invalid "blank" or NULL Config Data treated as Valid. Check [WiFiManager connection attempt to unconfigured ("blank") SSID after restart on SAMD #8](https://github.com/khoih-prog/WiFiManager_Generic_Lite/issues/8)
2. Fix compiler warnings.

### Release v1.1.2

1. Fix MultiWiFi connection bug. Check [SAMD MultiWiFi issues when first WiFi SSID configured in CP is invalid or not available #6](https://github.com/khoih-prog/WiFiManager_Generic_Lite/issues/6)
2. Bump up to version v1.1.2 to sync with [WiFiManager_Generic_Lite](https://github.com/khoih-prog/WiFiManager_Generic_Lite)

### Major Release v1.1.0

1. Configurable **Customs HTML Headers**, including Customs Style, Customs Head Elements, CORS Header.
2. Fix Config Portal Bug. 
3. Add functions to control Config Portal from software or Virtual Switches. Check [How to trigger a Config Portal from code #25](https://github.com/khoih-prog/Blynk_WM/issues/25)
4. Use more efficient [FlashStorage_SAMD v1.1.0](https://github.com/khoih-prog/FlashStorage_SAMD) and [FlashStorage_STM32 v1.0.0](https://github.com/khoih-prog/FlashStorage_STM32)
5. Optimize code. 
6. Update examples


### Release v1.0.2

1. Add support to STM32F/L/H/G/WB/MP1 using ATWINC1500/WiFi101. Thanks to Max Gerhardt in [**attachInterrupt() on wifi101 unidentified**](https://community.platformio.org/t/attachinterrupt-on-wifi101-unidentified/17543)

### Release v1.0.1

1. Fix bug.
2. Drop support to Mega due to marginal memory issue.

### Release v1.0.0

1. Initial release to support many boards and Generic WiFi (WiFiNINA, WINC1500/WiFi101, WiFiEsp, etc.) using WiFiNINA_Generic, WiFi101, WiFiEsp, etc. libraries.



