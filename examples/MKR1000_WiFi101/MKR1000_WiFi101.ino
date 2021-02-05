/****************************************************************************************************************************
  MKR1000_WiFi101.ino
  For SAMD 21 MKR1000 boards using WiFi101 Modules/Shields
  
  WiFiManager_Generic_WM_Lite is a library for the Mega, Teensy, SAM DUE, SAMD and STM32 boards 
  (https://github.com/khoih-prog/WiFiManager_Generic_Lite) to enable store Credentials in EEPROM/LittleFS for easy 
  configuration/reconfiguration and autoconnect/autoreconnect of WiFi and other services without Hardcoding.
  
  Built by Khoi Hoang https://github.com/khoih-prog/WiFiManager_Generic_Lite
  Licensed under MIT license
  Version: 1.0.1
   
   Version Modified By   Date        Comments
   ------- -----------  ----------   -----------
   1.0.0   K Hoang      04/02/2021  Initial coding for generic boards using generic WiFi.
   1.0.1   K Hoang      05/02/2021  Fix bug. Drop Mega support due to marginal memory.                     
  *****************************************************************************************************************************/
  
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

  Serial.print(F("\nStart MKR1000_WiFi101 on ")); Serial.print(BOARD_NAME);
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
