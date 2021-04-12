/****************************************************************************************************************************
  STM32_WiFi.ino
  For STM32 boards using WIFI_GENERIC Modules/Shields, using much less code to support boards with smaller memory

  WiFiManager_Generic_WM_Lite is a library for the Mega, Teensy, SAM DUE, SAMD and STM32 boards 
  (https://github.com/khoih-prog/WiFiManager_Generic_Lite) to enable store Credentials in EEPROM/LittleFS for easy 
  configuration/reconfiguration and autoconnect/autoreconnect of WiFi and other services without Hardcoding.
  
  Built by Khoi Hoang https://github.com/khoih-prog/WiFiManager_Generic_Lite
  Licensed under MIT license
  Version: 1.1.3

  Version Modified By   Date        Comments
  ------- -----------  ----------   -----------
  1.0.0   K Hoang      04/02/2021  Initial coding for generic boards using generic WiFi.
  1.0.1   K Hoang      05/02/2021  Fix bug. Drop Mega support due to marginal memory. 
  1.0.2   K Hoang      06/02/2021  Add support to STM32F/L/H/G/WB/MP1 using ATWINC1500/WiFi101
  1.1.0   K Hoang      21/02/2021  Optimize code and use better FlashStorage_SAMD and FlashStorage_STM32. 
                                   Add customs HTML header feature. Fix bug.
  1.1.2   K Hoang      30/03/2021  Fix MultiWiFi connection bug.
  1.1.3   K Hoang      12/04/2021  Fix invalid "blank" Config Data treated as Valid.
 *****************************************************************************************************************************/
#include "defines.h"
#include "Credentials.h"
#include "dynamicParams.h"

#if USE_WIFI101
  // Fix only for STM32 using WiFi101, thanks to Max Gerhardt in
  // https://community.platformio.org/t/attachinterrupt-on-wifi101-unidentified/17543
  extern "C" void attachInterruptMultiArch(uint32_t pin, void *chip_isr, uint32_t mode)
  {
    void (*_c)(void) = (void(*)(void))(chip_isr);
    attachInterrupt(pin, _c, mode);
  }
  
  extern "C" void detachInterruptMultiArch(uint32_t pin)
  {
    detachInterrupt(pin);
  }
#endif

void heartBeatPrint()
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
#define HEARTBEAT_INTERVAL    600000L
  // Print hearbeat every HEARTBEAT_INTERVAL (600) seconds.
  if ((millis() > checkstatus_timeout) || (checkstatus_timeout == 0))
  {
    heartBeatPrint();
    checkstatus_timeout = millis() + HEARTBEAT_INTERVAL;
  }
}

WiFiManager_Generic_Lite* WiFiManager_Generic;

#if USING_CUSTOMS_STYLE
const char NewCustomsStyle[] /*PROGMEM*/ = "<style>div,input{padding:5px;font-size:1em;}input{width:95%;}body{text-align: center;}\
button{background-color:blue;color:white;line-height:2.4rem;font-size:1.2rem;width:100%;}fieldset{border-radius:0.3rem;margin:0px;}</style>";
#endif

void setup()
{
  // Debug console
  Serial.begin(115200);
  while (!Serial);

  delay(200);

  Serial.print(F("\nStart STM32_WiFi on ")); Serial.print(BOARD_NAME);
  Serial.print(F(" with ")); Serial.println(SHIELD_TYPE);
  Serial.println(WIFI_MANAGER_GENERIC_LITE_VERSION);

#if ( USE_WIFI_CUSTOM && USE_ESP_AT_SHIELD )
    // initialize serial for ESP module
  EspSerial.begin(115200);
  // initialize ESP module
  WiFi.init(&EspSerial);

  Serial.println(F("WiFi shield init done"));

  // check for the presence of the shield
  if (WiFi.status() == WL_NO_SHIELD)
  {
    Serial.println(F("WiFi shield not present"));
    // don't continue
    while (true);
  }
#endif

  WiFiManager_Generic = new WiFiManager_Generic_Lite();

  // Optional to change default AP IP(192.168.4.1) and channel(10)
  //WiFiManager_Generic->setConfigPortalIP(IPAddress(192, 168, 120, 1));
  WiFiManager_Generic->setConfigPortalChannel(0);

#if USING_CUSTOMS_STYLE
  WiFiManager_Generic->setCustomsStyle(NewCustomsStyle);
#endif

#if USING_CUSTOMS_HEAD_ELEMENT
  WiFiManager_Generic->setCustomsHeadElement("<style>html{filter: invert(10%);}</style>");
#endif

#if USING_CORS_FEATURE  
  WiFiManager_Generic->setCORSHeader("Your Access-Control-Allow-Origin");
#endif

  // Set customized DHCP HostName
  WiFiManager_Generic->begin(HOST_NAME);
  //Or use default Hostname "STM32-WiFi-XXXXXX"
  //WiFiManager_Generic->begin();
}

#if USE_DYNAMIC_PARAMETERS
void displayCredentials()
{
  Serial.println(F("\nYour stored Credentials :"));

  for (uint16_t i = 0; i < NUM_MENU_ITEMS; i++)
  {
    Serial.print(myMenuItems[i].displayName);
    Serial.print(F(" = "));
    Serial.println(myMenuItems[i].pdata);
  }
}

void displayCredentialsInLoop()
{
  static bool displayedCredentials = false;

  if (!displayedCredentials)
  {
    for (int i = 0; i < NUM_MENU_ITEMS; i++)
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
}

#endif

void loop()
{
  WiFiManager_Generic->run();
  check_status();

#if USE_DYNAMIC_PARAMETERS
  displayCredentialsInLoop();
#endif  
}
