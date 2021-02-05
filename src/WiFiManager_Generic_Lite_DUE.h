/****************************************************************************************************************************
   WiFiManager_Generic_Lite_DUE.h
   For SAM DUE boards using WIFI_GENERIC modules/shields, using much less code to support boards with smaller memory

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

#ifndef WiFiManager_Generic_Lite_DUE_h
#define WiFiManager_Generic_Lite_DUE_h

#if ( defined(ARDUINO_SAM_DUE) || defined(__SAM3X8E__) )
  #if defined(WIFI_GENERIC_USE_SAM_DUE)
  #undef WIFI_GENERIC_USE_SAM_DUE
  #endif
  #define WIFI_GENERIC_USE_SAM_DUE      true
  #warning Use SAM_DUE architecture from WiFiManager_Generic_Lite_DUE
#else
  #error This code is intended to run on the SAM DUE platform! Please check your Tools->Board setting.  
#endif

#define WIFI_MANAGER_GENERIC_LITE_VERSION        "WiFiManager_Generic_Lite v1.0.1"

#if (USE_WIFI_NINA || USE_WIFI101)
  #include <WiFiWebServer.h>
#else
  #warning You have to include another WiFiWebServer, such as ESP8266_AT_WebServer.
#endif

#include <WiFiManager_Generic_Lite_Debug.h>

//Use DueFlashStorage to simulate EEPROM
#include <DueFlashStorage.h>                 //https://github.com/sebnil/DueFlashStorage

DueFlashStorage dueFlashStorageData;

///////// NEW for DRD /////////////
// These defines must be put before #include <DoubleResetDetector_Generic.h>
// to select where to store DoubleResetDetector_Generic's variable.
// Otherwise, library will use default EEPROM storage
#define  DRD_FLAG_DATA_SIZE     4

#ifndef DRD_GENERIC_DEBUG
#define DRD_GENERIC_DEBUG     false
#endif

#include <DoubleResetDetector_Generic.h>      //https://github.com/khoih-prog/DoubleResetDetector_Generic

// Number of seconds after reset during which a
// subseqent reset will be considered a double reset.
#define DRD_TIMEOUT 10

// RTC Memory Address for the DoubleResetDetector to use
#define DRD_ADDRESS 0

DoubleResetDetector_Generic* drd;

///////// NEW for DRD /////////////

//NEW
#define MAX_ID_LEN                5
#define MAX_DISPLAY_NAME_LEN      16

typedef struct
{
  char id             [MAX_ID_LEN + 1];
  char displayName    [MAX_DISPLAY_NAME_LEN + 1];
  char *pdata;
  uint8_t maxlen;
} MenuItem;
//

#if USE_DYNAMIC_PARAMETERS
  #warning Using Dynamic Parameters
  ///NEW
  extern uint16_t NUM_MENU_ITEMS;
  extern MenuItem myMenuItems [];
  bool *menuItemUpdated = NULL;
#else
  #warning Not using Dynamic Parameters
#endif


#define SSID_MAX_LEN      32
// WPA2 passwords can be up to 63 characters long.
#define PASS_MAX_LEN      64

typedef struct
{
  char wifi_ssid[SSID_MAX_LEN];
  char wifi_pw  [PASS_MAX_LEN];
}  WiFi_Credentials;

#define NUM_WIFI_CREDENTIALS      2

// Configurable items besides fixed Header
#define NUM_CONFIGURABLE_ITEMS    ( ( 2 * NUM_WIFI_CREDENTIALS ) + 1 )
////////////////

#define HEADER_MAX_LEN            16
#define BOARD_NAME_MAX_LEN        24

typedef struct Configuration
{
  char header         [HEADER_MAX_LEN];
  WiFi_Credentials  WiFi_Creds  [NUM_WIFI_CREDENTIALS];
  char board_name     [BOARD_NAME_MAX_LEN];
  int  checkSum;
} WIFI_GENERIC_Configuration;

// Currently CONFIG_DATA_SIZE  =   236  = (16 + 96 * 2 + 4 + 24)
uint16_t CONFIG_DATA_SIZE = sizeof(WIFI_GENERIC_Configuration);

///New from v1.0.4
extern bool LOAD_DEFAULT_CONFIG_DATA;
extern WIFI_GENERIC_Configuration defaultConfig;

// -- HTML page fragments
const char WIFI_GENERIC_HTML_HEAD[]     /*PROGMEM*/ = "<!DOCTYPE html><html><head><title>SAM_DUE_WM_NINA_Lite</title><style>div,input{padding:5px;font-size:1em;}input{width:95%;}body{text-align: center;}button{background-color:#16A1E7;color:#fff;line-height:2.4rem;font-size:1.2rem;width:100%;}fieldset{border-radius:0.3rem;margin:0px;}</style></head><div style=\"text-align:left;display:inline-block;min-width:260px;\">\
<fieldset><div><label>WiFi SSID</label><input value=\"[[id]]\"id=\"id\"><div></div></div>\
<div><label>PWD</label><input value=\"[[pw]]\"id=\"pw\"><div></div></div>\
<div><label>WiFi SSID1</label><input value=\"[[id1]]\"id=\"id1\"><div></div></div>\
<div><label>PWD1</label><input value=\"[[pw1]]\"id=\"pw1\"><div></div></div></fieldset>\
<fieldset><div><label>Board Name</label><input value=\"[[nm]]\"id=\"nm\"><div></div></div></fieldset>";

const char WIFI_GENERIC_FLDSET_START[]  /*PROGMEM*/ = "<fieldset>";
const char WIFI_GENERIC_FLDSET_END[]    /*PROGMEM*/ = "</fieldset>";
const char WIFI_GENERIC_HTML_PARAM[]    /*PROGMEM*/ = "<div><label>{b}</label><input value='[[{v}]]'id='{i}'><div></div></div>";
const char WIFI_GENERIC_HTML_BUTTON[]   /*PROGMEM*/ = "<button onclick=\"sv()\">Save</button></div>";
const char WIFI_GENERIC_HTML_SCRIPT[]   /*PROGMEM*/ = "<script id=\"jsbin-javascript\">\
function udVal(key,val){var request=new XMLHttpRequest();var url='/?key='+key+'&value='+encodeURIComponent(val);\
request.open('GET',url,false);request.send(null);}\
function sv(){udVal('id',document.getElementById('id').value);udVal('pw',document.getElementById('pw').value);\
udVal('id1',document.getElementById('id1').value);udVal('pw1',document.getElementById('pw1').value);\
udVal('nm',document.getElementById('nm').value);";

const char WIFI_GENERIC_HTML_SCRIPT_ITEM[]  /*PROGMEM*/ = "udVal('{d}',document.getElementById('{d}').value);";
const char WIFI_GENERIC_HTML_SCRIPT_END[]   /*PROGMEM*/ = "alert('Updated');}</script>";
const char WIFI_GENERIC_HTML_END[]          /*PROGMEM*/ = "</html>";
///


String IPAddressToString(IPAddress _address)
{
  String str = String(_address[0]);
  str += ".";
  str += String(_address[1]);
  str += ".";
  str += String(_address[2]);
  str += ".";
  str += String(_address[3]);
  return str;
}

class WiFiManager_Generic_Lite
{
    public:
    
    WiFiManager_Generic_Lite()
    {     
      // check for the presence of the shield
#if USE_WIFI101
      if (WiFi.status() == WL_NO_SHIELD)
#else
      if (WiFi.status() == WL_NO_MODULE)
#endif      
      {
        WG_LOGERROR(F("NoWiFi"));
      }     
    }

    ~WiFiManager_Generic_Lite()
    {
      if (server)
        delete server;
    }
        
    bool connectWiFi(const char* ssid, const char* pass)
    {
      WG_LOGERROR1(F("Con2:"), ssid);
      
      setHostname();

      if ( WiFi.begin(ssid, pass) == WL_CONNECTED )  
      {
        displayWiFiData();
      }
      else
      {
        WG_LOGERROR(F("NoW"));
        return false;
      }

      WG_LOGERROR(F("WOK"));

      wifi_connected = true;

      return true;
    }
   
    void begin(const char* ssid,
               const char* pass )
    {
      WG_LOGERROR(F("conW"));
      connectWiFi(ssid, pass);
    }

    void begin(const char *iHostname = "")
    {
      #define RETRY_TIMES_CONNECT_WIFI			3
      
      if (iHostname[0] == 0)
      {
        String randomNum = String(random(0xFFFFFF), HEX);
        randomNum.toUpperCase();
        
        String _hostname = "DUE-WIFI-" + randomNum;
        _hostname.toUpperCase();

        getRFC952_hostname(_hostname.c_str());
      }
      else
      {
        // Prepare and store the hostname only not NULL
        getRFC952_hostname(iHostname);
      }
      
       WG_LOGERROR1(F("Hostname="), RFC952_hostname);
      //////
      
      //// New DRD ////
      drd = new DoubleResetDetector_Generic(DRD_TIMEOUT, DRD_ADDRESS);  
      bool noConfigPortal = true;
   
      if (drd->detectDoubleReset())
      {
        WG_LOGERROR(F("Double Reset Detected"));
     
        noConfigPortal = false;
      }
      //// New DRD ////
      
      if (LOAD_DEFAULT_CONFIG_DATA)
      {
        WG_LOGERROR(F("======= Start Default Config Data ======="));
        displayConfigData(defaultConfig);
      }
      
      hadConfigData = getConfigData();
      
      isForcedConfigPortal = isForcedCP();
        
      //// New DRD/MRD ////
      //  noConfigPortal when getConfigData() OK and no MRD/DRD'ed
      if (hadConfigData && noConfigPortal && (!isForcedConfigPortal) )
      {
        hadConfigData = true;

        if (connectMultiWiFi(RETRY_TIMES_CONNECT_WIFI))
        {
          WG_LOGERROR(F("b:WOK"));
        }
        else
        {
          WG_LOGERROR(F("b:NoW"));
          // failed to connect to WiFi, will start configuration mode
          startConfigurationMode();
        }
      }
      else
      {      
        WG_LOGERROR(isForcedConfigPortal? F("bg: isForcedConfigPortal = true") : F("bg: isForcedConfigPortal = false"));
                     
        // If not persistent => clear the flag so that after reset. no more CP, even CP not entered and saved
        if (persForcedConfigPortal)
        {
          WG_LOGERROR1(F("bg:Stay forever in CP:"), isForcedConfigPortal ? F("Forced-Persistent") : (noConfigPortal ? F("No ConfigDat") : F("DRD/MRD")));
        }
        else
        {
          WG_LOGERROR1(F("bg:Stay forever in CP:"), isForcedConfigPortal ? F("Forced-non-Persistent") : (noConfigPortal ? F("No ConfigDat") : F("DRD/MRD")));
          clearForcedCP();
        }
          
        //To permit autoreset after timeout if DRD/MRD or non-persistent forced-CP 
        hadConfigData = isForcedConfigPortal ? true : (noConfigPortal ? false : true);
        
        // failed to connect to WiFi, will start configuration mode
        startConfigurationMode();
      }
    }

#ifndef RETRY_TIMES_RECONNECT_WIFI
  #define RETRY_TIMES_RECONNECT_WIFI   2
#else
  // Force range of user-defined RETRY_TIMES_RECONNECT_WIFI between 2-5 times
  #if (RETRY_TIMES_RECONNECT_WIFI < 2)
    #warning RETRY_TIMES_RECONNECT_WIFI too low. Reseting to 2
    #undef RETRY_TIMES_RECONNECT_WIFI
    #define RETRY_TIMES_RECONNECT_WIFI   2
  #elif (RETRY_TIMES_RECONNECT_WIFI > 5)
    #warning RETRY_TIMES_RECONNECT_WIFI too high. Reseting to 5
    #undef RETRY_TIMES_RECONNECT_WIFI
    #define RETRY_TIMES_RECONNECT_WIFI   5
  #endif
#endif

#ifndef RESET_IF_CONFIG_TIMEOUT
  #define RESET_IF_CONFIG_TIMEOUT   true
#endif

#ifndef CONFIG_TIMEOUT_RETRYTIMES_BEFORE_RESET
  #define CONFIG_TIMEOUT_RETRYTIMES_BEFORE_RESET          10
#else
  // Force range of user-defined TIMES_BEFORE_RESET between 2-100
  #if (CONFIG_TIMEOUT_RETRYTIMES_BEFORE_RESET < 2)
    #warning CONFIG_TIMEOUT_RETRYTIMES_BEFORE_RESET too low. Reseting to 2
    #undef CONFIG_TIMEOUT_RETRYTIMES_BEFORE_RESET
    #define CONFIG_TIMEOUT_RETRYTIMES_BEFORE_RESET   2
  #elif (CONFIG_TIMEOUT_RETRYTIMES_BEFORE_RESET > 100)
    #warning CONFIG_TIMEOUT_RETRYTIMES_BEFORE_RESET too high. Resetting to 100
    #undef CONFIG_TIMEOUT_RETRYTIMES_BEFORE_RESET
    #define CONFIG_TIMEOUT_RETRYTIMES_BEFORE_RESET   100
  #endif
#endif

    void run()
    {
      static int retryTimes = 0;
      static bool wifiDisconnectedOnce = false;
      
      // Lost connection in running. Give chance to reconfig.
      // Check WiFi status every 5s and update status
      // Check twice to be sure wifi disconnected is real
      static unsigned long checkstatus_timeout = 0;
      #define WIFI_STATUS_CHECK_INTERVAL    5000L
      
      //// New DRD ////
      // Call the double reset detector loop method every so often,
      // so that it can recognise when the timeout expires.
      // You can also call drd.stop() when you wish to no longer
      // consider the next reset as a double reset.
      drd->loop();
      //// New DRD ////
         
      if ( !configuration_mode && (millis() > checkstatus_timeout) )
      {       
        if (WiFi.status() == WL_CONNECTED)
        {
          wifi_connected = true;
        }
        else
        {
          if (wifiDisconnectedOnce)
          {
            wifiDisconnectedOnce = false;
            wifi_connected = false;
            WG_LOGERROR(F("r:Check&WLost"));
          }
          else
          {
            wifiDisconnectedOnce = true;
          }
        }
        
        checkstatus_timeout = millis() + WIFI_STATUS_CHECK_INTERVAL;
      }    

      // Lost connection in running. Give chance to reconfig.
      if ( !wifi_connected )
      {
        // If configTimeout but user hasn't connected to configWeb => try to reconnect WiFi
        // But if user has connected to configWeb, stay there until done, then reset hardware
        if ( configuration_mode && ( configTimeout == 0 ||  millis() < configTimeout ) )
        {
          retryTimes = 0;

          if (server)
          {
            //WG_LOGDEBUG(F("r:handleClient"));
            server->handleClient();
          }
           
          return;
        }
        else
        {
#if RESET_IF_CONFIG_TIMEOUT
          // If we're here but still in configuration_mode, permit running TIMES_BEFORE_RESET times before reset hardware
          // to permit user another chance to config.
          if ( configuration_mode && (configTimeout != 0) )
          {
            if (++retryTimes <= CONFIG_TIMEOUT_RETRYTIMES_BEFORE_RESET)
            {
              WG_LOGERROR1(F("r:WLost&TOut.ConW.Retry#"), retryTimes);
            }
            else
            {
              resetFunc();  //call reset
            }
          }
#endif

          // Not in config mode, try reconnecting before forcing to config mode
          if ( !wifi_connected )
          {
            WG_LOGERROR(F("r:WLost.ReconW"));
            
            if (connectMultiWiFi(RETRY_TIMES_RECONNECT_WIFI))
            {
              WG_LOGERROR(F("r:WOK"));
            }
          }
        }
      }
      else if (configuration_mode)
      {
        configuration_mode = false;
        WG_LOGERROR(F("r:gotWBack"));
      }
    }
    
    //////////////////////////////////////////////
    
    void setHostname()
    {
      if (RFC952_hostname[0] != 0)
      {
#if USE_WIFI101
        WiFi.hostname(RFC952_hostname);
#elif USE_WIFI_NINA    
        WiFi.setHostname(RFC952_hostname);
#endif        
      }
    }
    
    //////////////////////////////////////////////

    void setConfigPortalIP(IPAddress portalIP = IPAddress(192, 168, 4, 1))
    {
      portal_apIP = portalIP;
    }
    
    //////////////////////////////////////////////

    #define MIN_WIFI_CHANNEL      1
    #define MAX_WIFI_CHANNEL      11    // Channel 13 is flaky, because of bad number 13 ;-)

    int setConfigPortalChannel(int channel = 1)
    {
      // If channel < MIN_WIFI_CHANNEL - 1 or channel > MAX_WIFI_CHANNEL => channel = 1
      // If channel == 0 => will use random channel from MIN_WIFI_CHANNEL to MAX_WIFI_CHANNEL
      // If (MIN_WIFI_CHANNEL <= channel <= MAX_WIFI_CHANNEL) => use it
      if ( (channel < MIN_WIFI_CHANNEL - 1) || (channel > MAX_WIFI_CHANNEL) )
        AP_channel = 1;
      else if ( (channel >= MIN_WIFI_CHANNEL - 1) && (channel <= MAX_WIFI_CHANNEL) )
        AP_channel = channel;

      return AP_channel;
    }
    
    //////////////////////////////////////////////
    
    void setConfigPortal(String ssid = "", String pass = "")
    {
      portal_ssid = ssid;
      portal_pass = pass;
    }
    
    //////////////////////////////////////////////

    void setSTAStaticIPConfig(IPAddress ip)
    {
      static_IP = ip;
    }
    
    //////////////////////////////////////////////
    
    String getWiFiSSID(uint8_t index)
    { 
      if (index >= NUM_WIFI_CREDENTIALS)
        return String("");
        
      if (!hadConfigData)
        getConfigData();

      return (String(WIFI_GENERIC_config.WiFi_Creds[index].wifi_ssid));
    }
    
    //////////////////////////////////////////////

    String getWiFiPW(uint8_t index)
    {
      if (index >= NUM_WIFI_CREDENTIALS)
        return String("");
        
      if (!hadConfigData)
        getConfigData();

      return (String(WIFI_GENERIC_config.WiFi_Creds[index].wifi_pw));
    }
    
    //////////////////////////////////////////////

    bool getWiFiStatus()
    {
      return wifi_connected;
    }
    
    //////////////////////////////////////////////
    
    WIFI_GENERIC_Configuration* getFullConfigData(WIFI_GENERIC_Configuration *configData)
    {
      if (!hadConfigData)
        getConfigData();

      // Check if NULL pointer
      if (configData)
        memcpy(configData, &WIFI_GENERIC_config, sizeof(WIFI_GENERIC_Configuration));

      return (configData);
    }
    
    //////////////////////////////////////////////

    String localIP()
    {
      ipAddress = IPAddressToString(WiFi.localIP());

      return ipAddress;
    }
    
    //////////////////////////////////////////////

    void clearConfigData()
    {
      memset(&WIFI_GENERIC_config, 0, sizeof(WIFI_GENERIC_config));
      
#if USE_DYNAMIC_PARAMETERS      
      for (uint16_t i = 0; i < NUM_MENU_ITEMS; i++)
      {
        // Actual size of pdata is [maxlen + 1]
        memset(myMenuItems[i].pdata, 0, myMenuItems[i].maxlen + 1);
      }
#endif

      saveConfigData();
    }
    
    //////////////////////////////////////////////
    
    bool isConfigDataValid()
    {
      return hadConfigData;
    }
    
    //////////////////////////////////////////////
    
    // Forced CP => Flag = 0xBEEFBEEF. Else => No forced CP
    // Flag to be stored at (EEPROM_START + DRD_FLAG_DATA_SIZE + CONFIG_DATA_SIZE) 
    // to avoid corruption to current data
    //#define FORCED_CONFIG_PORTAL_FLAG_DATA              ( (uint32_t) 0xDEADBEEF)
    //#define FORCED_PERS_CONFIG_PORTAL_FLAG_DATA         ( (uint32_t) 0xBEEFDEAD)
    
    const uint32_t FORCED_CONFIG_PORTAL_FLAG_DATA       = 0xDEADBEEF;
    const uint32_t FORCED_PERS_CONFIG_PORTAL_FLAG_DATA  = 0xBEEFDEAD;
    
    #define FORCED_CONFIG_PORTAL_FLAG_DATA_SIZE     4
    
    void resetAndEnterConfigPortal()
    {
      persForcedConfigPortal = false;
      
      setForcedCP(false);
      
      // Delay then reset the ESP8266 after save data
      delay(1000);
      resetFunc();
    }
    
    //////////////////////////////////////////////
    
    // This will keep CP forever, until you successfully enter CP, and Save data to clear the flag.
    void resetAndEnterConfigPortalPersistent()
    {
      persForcedConfigPortal = true;
      
      setForcedCP(true);
      
      // Delay then reset the ESP8266 after save data
      delay(1000);
      resetFunc();
    }
    
    //////////////////////////////////////////////

    void resetFunc()
    {
      rstc_start_software_reset(RSTC);
    }
    
    //////////////////////////////////////////////

  private:
    String ipAddress = "0.0.0.0";

    WiFiWebServer* server = NULL;
    bool configuration_mode = false;

    unsigned long configTimeout;
    bool hadConfigData = false;
    
    bool isForcedConfigPortal   = false;
    bool persForcedConfigPortal = false;

    WIFI_GENERIC_Configuration WIFI_GENERIC_config;
    
    uint16_t totalDataSize = 0;

    String macAddress = "";
    bool wifi_connected = false;

    IPAddress portal_apIP = IPAddress(192, 168, 4, 1);
    int AP_channel = 10;

    String portal_ssid = "";
    String portal_pass = "";

    IPAddress static_IP   = IPAddress(0, 0, 0, 0);

    #define RFC952_HOSTNAME_MAXLEN      24
    char RFC952_hostname[RFC952_HOSTNAME_MAXLEN + 1];

    char* getRFC952_hostname(const char* iHostname)
    {
      memset(RFC952_hostname, 0, sizeof(RFC952_hostname));

      size_t len = ( RFC952_HOSTNAME_MAXLEN < strlen(iHostname) ) ? RFC952_HOSTNAME_MAXLEN : strlen(iHostname);

      size_t j = 0;

      for (size_t i = 0; i < len - 1; i++)
      {
        if ( isalnum(iHostname[i]) || iHostname[i] == '-' )
        {
          RFC952_hostname[j] = iHostname[i];
          j++;
        }
      }
      // no '-' as last char
      if ( isalnum(iHostname[len - 1]) || (iHostname[len - 1] != '-') )
        RFC952_hostname[j] = iHostname[len - 1];

      return RFC952_hostname;
    }
    
    void displayConfigData(WIFI_GENERIC_Configuration configData)
    {
      WG_LOGERROR5(F("Hdr="),   configData.header, F(",SSID="), configData.WiFi_Creds[0].wifi_ssid,
                   F(",PW="),   configData.WiFi_Creds[0].wifi_pw);
      WG_LOGERROR3(F("SSID1="), configData.WiFi_Creds[1].wifi_ssid, F(",PW1="),  configData.WiFi_Creds[1].wifi_pw);     
      WG_LOGERROR1(F("BName="), configData.board_name);     
                 
#if USE_DYNAMIC_PARAMETERS     
      for (uint16_t i = 0; i < NUM_MENU_ITEMS; i++)
      {
        WG_LOGERROR5("i=", i, ",id=", myMenuItems[i].id, ",data=", myMenuItems[i].pdata);
      }
#endif               
    }

    void displayWiFiData()
    {
      WG_LOGERROR3(F("SSID="), WiFi.SSID(), F(",RSSI="), WiFi.RSSI());
      WG_LOGERROR1(F("IP="), localIP() );
    }

#define WIFI_GENERIC_BOARD_TYPE   "WIFI_GENERIC"
#define WM_NO_CONFIG             "blank"

#ifndef EEPROM_START
  #define EEPROM_START     0
  #warning EEPROM_START not defined. Set to 0
#endif

// Stating positon to store Blynk8266_WM_config
#define CONFIG_EEPROM_START    (EEPROM_START + DRD_FLAG_DATA_SIZE)


    int calcChecksum()
    {
      int checkSum = 0;
      for (uint16_t index = 0; index < (sizeof(WIFI_GENERIC_config) - sizeof(WIFI_GENERIC_config.checkSum)); index++)
      {
        checkSum += * ( ( (byte*) &WIFI_GENERIC_config ) + index);
      }

      return checkSum;
    }
    
    //////////////////////////////////////////////
       
    void saveForcedCP(uint32_t value)
    {
      uint32_t readForcedConfigPortalFlag = value;

      uint16_t offset = CONFIG_EEPROM_START + CONFIG_DATA_SIZE;
            
      dueFlashStorageData.write(offset, (byte *) &readForcedConfigPortalFlag, sizeof(readForcedConfigPortalFlag));
           
      //EEPROM.put(CONFIG_EEPROM_START + CONFIG_DATA_SIZE, readForcedConfigPortalFlag); 
    }
    
    void setForcedCP(bool isPersistent)
    {
      uint32_t readForcedConfigPortalFlag = isPersistent? FORCED_PERS_CONFIG_PORTAL_FLAG_DATA : FORCED_CONFIG_PORTAL_FLAG_DATA;
 
      WG_LOGERROR(isPersistent ? F("setForcedCP Persistent") : F("setForcedCP non-Persistent"));

      saveForcedCP(readForcedConfigPortalFlag);
    }
    
    void clearForcedCP()
    {
      uint32_t readForcedConfigPortalFlag = 0;
   
      WG_LOGERROR(F("clearForcedCP"));

      saveForcedCP(readForcedConfigPortalFlag);
    }

    bool isForcedCP()
    {
      uint32_t readForcedConfigPortalFlag;
      
      // Return true if forced CP (0xDEADBEEF read at offset EPROM_START + DRD_FLAG_DATA_SIZE + CONFIG_DATA_SIZE)
      // => set flag noForcedConfigPortal = false
      uint16_t offset = CONFIG_EEPROM_START + CONFIG_DATA_SIZE;
            
      byte* dataPointer = (byte* ) dueFlashStorageData.readAddress(offset);
      
      memcpy(&readForcedConfigPortalFlag, dataPointer, sizeof(readForcedConfigPortalFlag));
      //EEPROM.get(CONFIG_EEPROM_START + CONFIG_DATA_SIZE, readForcedConfigPortalFlag);
      
      // Return true if forced CP (0xDEADBEEF read at offset EPROM_START + DRD_FLAG_DATA_SIZE + CONFIG_DATA_SIZE)
      // => set flag noForcedConfigPortal = false     
      if (readForcedConfigPortalFlag == FORCED_CONFIG_PORTAL_FLAG_DATA)
      {       
        persForcedConfigPortal = false;
        return true;
      }
      else if (readForcedConfigPortalFlag == FORCED_PERS_CONFIG_PORTAL_FLAG_DATA)
      {       
        persForcedConfigPortal = true;
        return true;
      }
      else
      {       
        return false;
      }
    }
    
    //////////////////////////////////////////////

#if USE_DYNAMIC_PARAMETERS
   
    bool checkDynamicData()
    {
      int checkSum = 0;
      int readCheckSum;
      
      uint16_t  byteCount = 0;
      
      //#define BUFFER_LEN            128
      //char readBuffer[BUFFER_LEN + 1];
      
      #define BIG_BUFFER_LEN        768     
      byte bigBuffer[BIG_BUFFER_LEN + 1];      
      
      uint16_t offset = CONFIG_EEPROM_START + sizeof(WIFI_GENERIC_config) + FORCED_CONFIG_PORTAL_FLAG_DATA_SIZE;
           
      // Make address 4-byte aligned
      if ( (offset % 4) != 0 )
      {
        offset += 4 - (offset % 4);
      }
      
      // Find the longest pdata, then dynamically allocate buffer. Remember to free when done
      // This is used to store tempo data to calculate checksum to see of data is valid
      // We dont like to destroy myMenuItems[i].pdata with invalid data
      int totalLength = 0;
            
      for (int i = 0; i < NUM_MENU_ITEMS; i++)
      {       
        totalLength += myMenuItems[i].maxlen;
        
        if ( (totalLength > BIG_BUFFER_LEN) || (myMenuItems[i].maxlen > BIG_BUFFER_LEN) )
        {
          // Size too large, abort and flag false
          WG_LOGERROR(F("ChkCrR: Error Small Buffer."));
          return false;
        }
      }
                         
      // Both Buffers big enough, read all dynamicData to BigBuffer once 
      // as address need to be 4-byte aligned
      byte* dataPointer = (byte* ) dueFlashStorageData.readAddress(offset);
      
      // Prepare buffer, more than enough
      memset(bigBuffer, 0, sizeof(bigBuffer));
      memcpy(bigBuffer, dataPointer, sizeof(bigBuffer));               
         
      // Don't need readBuffer
      // Now to split into individual piece to add to CSum
      for (int i = 0; i < NUM_MENU_ITEMS; i++)
      {       
        char* _pointer = (char*) bigBuffer;
        
        for (uint16_t j = 0; j < myMenuItems[i].maxlen; j++, _pointer++, byteCount++)
        {
          *_pointer = bigBuffer[byteCount];
                  
          checkSum += *_pointer;  
        }    
      }
      
      memcpy(&readCheckSum, &bigBuffer[byteCount], sizeof(readCheckSum));
          
      WG_LOGERROR3(F("ChkCrR:CrCCsum=0x"), String(checkSum, HEX), F(",CrRCsum=0x"), String(readCheckSum, HEX));
           
      if ( checkSum != readCheckSum )
      {
        return false;
      }
      
      return true;    
    }
    
    //////////////////////////////////////////////
    
    bool dueFlashStorage_getDynamicData()
    {      
      uint16_t offset = CONFIG_EEPROM_START + sizeof(WIFI_GENERIC_config) + FORCED_CONFIG_PORTAL_FLAG_DATA_SIZE;
           
      // Make address 4-byte aligned
      if ( (offset % 4) != 0 )
      {
        offset += 4 - (offset % 4);
      }
            
      int checkSum = 0;
      int readCheckSum;
      
      uint16_t  byteCount = 0;
           
      #define BIG_BUFFER_LEN        768     
      byte buffer[BIG_BUFFER_LEN + 1];      
      
      byte* dataPointer = (byte* ) dueFlashStorageData.readAddress(offset);
      
      memcpy(buffer, dataPointer, sizeof(buffer));
      
      totalDataSize = sizeof(WIFI_GENERIC_config) + sizeof(readCheckSum);
   
      for (int i = 0; i < NUM_MENU_ITEMS; i++)
      {       
        char* _pointer = myMenuItems[i].pdata;
        totalDataSize += myMenuItems[i].maxlen;
        
        // Actual size of pdata is [maxlen + 1]
        memset(myMenuItems[i].pdata, 0, myMenuItems[i].maxlen + 1);
                      
        for (uint16_t j = 0; j < myMenuItems[i].maxlen; j++,_pointer++, byteCount++)
        {
          *_pointer = buffer[byteCount];
          
          checkSum += *_pointer;  
        }     
      }
      
      memcpy(&readCheckSum, &buffer[byteCount], sizeof(readCheckSum));
      
      byteCount += sizeof(readCheckSum);      
      
      WG_LOGERROR5(F("CrCCsum=0x"), String(checkSum, HEX), F(",CrRCsum=0x"), String(readCheckSum, HEX), 
                F(",TotalDataSz="), totalDataSize);
      
      if ( checkSum != readCheckSum)
      {
        return false;
      }
      
      return true;
    }
    
    //////////////////////////////////////////////
    
    void dueFlashStorage_putDynamicData()
    {   
      uint16_t offset = CONFIG_EEPROM_START + sizeof(WIFI_GENERIC_config) + FORCED_CONFIG_PORTAL_FLAG_DATA_SIZE;
      
      // Make address 4-byte aligned
      if ( (offset % 4) != 0 )
      {
        offset += 4 - (offset % 4);
      }
      
      int       checkSum = 0;
      uint16_t  byteCount = 0;
           
      // Use 2K buffer, if need more memory, can reduce this
      byte buffer[2048];
         
      for (int i = 0; i < NUM_MENU_ITEMS; i++)
      {       
        char* _pointer = myMenuItems[i].pdata;
 
        WG_LOGDEBUG3(F("pdata="), myMenuItems[i].pdata, F(",len="), myMenuItems[i].maxlen);
                     
        for (uint16_t j = 0; j < myMenuItems[i].maxlen; j++, _pointer++, /*offset++,*/ byteCount++)
        {
          if (byteCount >= sizeof(buffer))
          {
            WG_LOGERROR1(F("Danger:dynamic data too long >"), sizeof(buffer));
          }
          
          buffer[byteCount] = *_pointer;          
          checkSum += *_pointer;     
         }
      }
           
      memcpy(&buffer[byteCount], &checkSum, sizeof(checkSum));
      
      byteCount += sizeof(checkSum);
      
      dueFlashStorageData.write(offset, buffer, byteCount);
      
      WG_LOGERROR3(F("CrCCSum=0x"), String(checkSum, HEX), F(",byteCount="), byteCount);
    }
#endif

    //////////////////////////////////////////////
    
    void NULLTerminateConfig()
    {
      //#define HEADER_MAX_LEN      16
      //#define SERVER_MAX_LEN      32
      //#define TOKEN_MAX_LEN       36
      
      // NULL Terminating to be sure
      WIFI_GENERIC_config.header[HEADER_MAX_LEN - 1] = 0;
      WIFI_GENERIC_config.WiFi_Creds[0].wifi_ssid[SSID_MAX_LEN - 1] = 0;
      WIFI_GENERIC_config.WiFi_Creds[0].wifi_pw  [PASS_MAX_LEN - 1] = 0;
      WIFI_GENERIC_config.WiFi_Creds[1].wifi_ssid[SSID_MAX_LEN - 1] = 0;
      WIFI_GENERIC_config.WiFi_Creds[1].wifi_pw  [PASS_MAX_LEN - 1] = 0;
      WIFI_GENERIC_config.board_name[BOARD_NAME_MAX_LEN - 1]  = 0;
    }
    
    //////////////////////////////////////////////
    
    bool dueFlashStorage_get()
    {
      uint16_t offset = CONFIG_EEPROM_START;
            
      byte* dataPointer = (byte* ) dueFlashStorageData.readAddress(offset);
      
      memcpy(&WIFI_GENERIC_config, dataPointer, sizeof(WIFI_GENERIC_config));
      
      NULLTerminateConfig();
      
      return true;
    }
    
    //////////////////////////////////////////////
   
    void dueFlashStorage_put()
    {
      uint16_t offset = CONFIG_EEPROM_START;
      
      dueFlashStorageData.write(offset, (byte *) &WIFI_GENERIC_config, sizeof(WIFI_GENERIC_config));   
    } 
    
    //////////////////////////////////////////////

    void saveConfigData()
    {
      int calChecksum = calcChecksum();
      WIFI_GENERIC_config.checkSum = calChecksum;
      
      WG_LOGERROR3(F("SaveData,Sz="), totalDataSize, F(",chkSum=0x"), String(calChecksum, HEX));

      dueFlashStorage_put();

#if USE_DYNAMIC_PARAMETERS      
      dueFlashStorage_putDynamicData();
#endif      
    }
    
    //////////////////////////////////////////////
        
    void loadAndSaveDefaultConfigData()
    {
      // Load Default Config Data from Sketch
      memcpy(&WIFI_GENERIC_config, &defaultConfig, sizeof(WIFI_GENERIC_config));
      strcpy(WIFI_GENERIC_config.header, WIFI_GENERIC_BOARD_TYPE);
      
      // Including config and dynamic data, and assume valid
      saveConfigData();
          
      WG_LOGERROR(F("======= Start Loaded Config Data ======="));
      displayConfigData(WIFI_GENERIC_config);    
    }
    
    //////////////////////////////////////////////
 
    bool getConfigData()
    {
      bool dynamicDataValid = true;
      int calChecksum;
      
      hadConfigData = false;    
          
      // For DUE, DATA_LENGTH = ((IFLASH1_PAGE_SIZE/sizeof(byte))*4) = 1KBytes
      WG_LOGERROR1(F("Simulate EEPROM, Sz:"), DATA_LENGTH);

      // Use new LOAD_DEFAULT_CONFIG_DATA logic
      if (LOAD_DEFAULT_CONFIG_DATA)
      {     
        // Load Config Data from Sketch
        loadAndSaveDefaultConfigData();
        
        // Don't need Config Portal anymore
        return true; 
      }
      else
      {   
        // Load stored config / dynamic data from dueFlashStorage
        // Verify ChkSum
        dueFlashStorage_get();
        
            
        calChecksum = calcChecksum();

        WG_LOGERROR3(F("CCSum=0x"), String(calChecksum, HEX),
                   F(",RCSum=0x"), String(WIFI_GENERIC_config.checkSum, HEX));
                   
#if USE_DYNAMIC_PARAMETERS        
        // Load stored dynamic data from dueFlashStorage
        dynamicDataValid = checkDynamicData();
#endif
        // If checksum = 0 => DueFlashStorage has been cleared (by uploading new FW, etc) => force to CP
        // If bad checksum = 0 => force to CP
        if ( (calChecksum != 0) && (calChecksum == WIFI_GENERIC_config.checkSum) )
        {
          if (dynamicDataValid)
          {   
  #if USE_DYNAMIC_PARAMETERS  
            dueFlashStorage_getDynamicData();
            
            WG_LOGERROR(F("Valid Stored Dynamic Data"));
  #endif        
            WG_LOGERROR(F("======= Start Stored Config Data ======="));
            displayConfigData(WIFI_GENERIC_config);
            
            // Don't need Config Portal anymore
            return true;
          }
          else
          {
            // Invalid Stored config data => Config Portal
            WG_LOGERROR(F("Invalid Stored Dynamic Data. Load default from Sketch"));
            
            // Load Default Config Data from Sketch, better than just "blank"
            loadAndSaveDefaultConfigData();
                             
            // Need Config Portal here as data can be just dummy
            // Even if you don't open CP, you're OK on next boot if your default config data is valid 
            return false;
          }
        }   
      }     

      if ( (strncmp(WIFI_GENERIC_config.header, WIFI_GENERIC_BOARD_TYPE, strlen(WIFI_GENERIC_BOARD_TYPE)) != 0) ||
           (calChecksum != WIFI_GENERIC_config.checkSum) || !dynamicDataValid || 
           ( (calChecksum == 0) && (WIFI_GENERIC_config.checkSum == 0) ) )
      {
        // Including Credentials CSum
        WG_LOGERROR1(F("InitCfgFile,sz="), sizeof(WIFI_GENERIC_config));

        // doesn't have any configuration        
        if (LOAD_DEFAULT_CONFIG_DATA)
        {
          memcpy(&WIFI_GENERIC_config, &defaultConfig, sizeof(WIFI_GENERIC_config));
        }
        else
        {
          memset(&WIFI_GENERIC_config, 0, sizeof(WIFI_GENERIC_config));

#if USE_DYNAMIC_PARAMETERS
          for (uint16_t i = 0; i < NUM_MENU_ITEMS; i++)
          {
            // Actual size of pdata is [maxlen + 1]
            memset(myMenuItems[i].pdata, 0, myMenuItems[i].maxlen + 1);
          }
#endif
              
          strcpy(WIFI_GENERIC_config.WiFi_Creds[0].wifi_ssid,   WM_NO_CONFIG);
          strcpy(WIFI_GENERIC_config.WiFi_Creds[0].wifi_pw,     WM_NO_CONFIG);
          strcpy(WIFI_GENERIC_config.WiFi_Creds[1].wifi_ssid,   WM_NO_CONFIG);
          strcpy(WIFI_GENERIC_config.WiFi_Creds[1].wifi_pw,     WM_NO_CONFIG);
          strcpy(WIFI_GENERIC_config.board_name, WM_NO_CONFIG);
          
#if USE_DYNAMIC_PARAMETERS
          for (uint16_t i = 0; i < NUM_MENU_ITEMS; i++)
          {
            strncpy(myMenuItems[i].pdata, WM_NO_CONFIG, myMenuItems[i].maxlen);
          }
#endif          
        }
    
        strcpy(WIFI_GENERIC_config.header, WIFI_GENERIC_BOARD_TYPE);
        
#if USE_DYNAMIC_PARAMETERS
        for (uint16_t i = 0; i < NUM_MENU_ITEMS; i++)
        {
          WG_LOGDEBUG3(F("g:myMenuItems["), i, F("]="), myMenuItems[i].pdata );
        }
#endif
        
        // Don't need
        WIFI_GENERIC_config.checkSum = 0;

        saveConfigData();

        return false;
      }
      else if ( !strncmp(WIFI_GENERIC_config.WiFi_Creds[0].wifi_ssid,       WM_NO_CONFIG, strlen(WM_NO_CONFIG) )  ||
                !strncmp(WIFI_GENERIC_config.WiFi_Creds[0].wifi_pw,         WM_NO_CONFIG, strlen(WM_NO_CONFIG) )  ||
                !strncmp(WIFI_GENERIC_config.WiFi_Creds[1].wifi_ssid,       WM_NO_CONFIG, strlen(WM_NO_CONFIG) )  ||
                !strncmp(WIFI_GENERIC_config.WiFi_Creds[1].wifi_pw,         WM_NO_CONFIG, strlen(WM_NO_CONFIG) )  ||
                !strlen(WIFI_GENERIC_config.WiFi_Creds[0].wifi_ssid) || 
                !strlen(WIFI_GENERIC_config.WiFi_Creds[1].wifi_ssid) ||
                !strlen(WIFI_GENERIC_config.WiFi_Creds[0].wifi_pw)   ||
                !strlen(WIFI_GENERIC_config.WiFi_Creds[1].wifi_pw)  )
      {
        // If SSID, PW ="nothing", stay in config mode forever until having config Data.
        return false;
      }
      else
      {
        displayConfigData(WIFI_GENERIC_config);
      }

      return true;
    }
    
    //////////////////////////////////////////////

    bool connectMultiWiFi(int retry_time)
    {
      int sleep_time  = 250;
      int index       = 0;
      uint8_t status;
                       
      static int lastConnectedIndex = 255;

      WG_LOGDEBUG(F("ConMultiWifi"));

      if (static_IP != IPAddress(0, 0, 0, 0))
      {
        WG_LOGDEBUG(F("UseStatIP"));
        WiFi.config(static_IP);
      }
    
      if (lastConnectedIndex != 255)
      {
        index = (lastConnectedIndex + 1) % NUM_WIFI_CREDENTIALS;                       
        WG_LOGDEBUG3(F("Using index="), index, F(", lastConnectedIndex="), lastConnectedIndex);
      }
      
      WG_LOGDEBUG3(F("con2WF:SSID="), WIFI_GENERIC_config.WiFi_Creds[index].wifi_ssid,
                F(",PW="), WIFI_GENERIC_config.WiFi_Creds[index].wifi_pw);
             
      while ( !wifi_connected && ( 0 < retry_time ) )
      {      
        WG_LOGDEBUG1(F("Remaining retry_time="), retry_time);
        
        status = WiFi.begin(WIFI_GENERIC_config.WiFi_Creds[index].wifi_ssid, WIFI_GENERIC_config.WiFi_Creds[index].wifi_pw); 
            
        // Need restart WiFi at beginning of each cycle 
        if (status == WL_CONNECTED)
        {
          wifi_connected = true;          
          lastConnectedIndex = index;                                     
          WG_LOGDEBUG1(F("WOK, lastConnectedIndex="), lastConnectedIndex);
          
          break;
        }
        else
        {
          delay(sleep_time);
          retry_time--;
        }         
      }
          
      if (retry_time <= 0)
      {      
        WG_LOGERROR3(F("Failed using index="), index, F(", retry_time="), retry_time);             
      }  

      if (wifi_connected)
      {
        WG_LOGERROR(F("con2WF:OK"));
        displayWiFiData();
      }
      else
      {
        WG_LOGERROR(F("con2WF:failed"));  
        // Can't connect, so try another index next time. Faking this index is OK and lost
        lastConnectedIndex = index;  
      }

      return wifi_connected;  
    }

    //////////////////////////////////////////////
    
    void createHTML(String& root_html_template)
    {
      String pitem;
      
      root_html_template = String(WIFI_GENERIC_HTML_HEAD);

#if USE_DYNAMIC_PARAMETERS     
      if (NUM_MENU_ITEMS > 0)
      {
        root_html_template += String(WIFI_GENERIC_FLDSET_START);
           
        for (uint16_t i = 0; i < NUM_MENU_ITEMS; i++)
        {
          pitem = String(WIFI_GENERIC_HTML_PARAM);

          pitem.replace("{b}", myMenuItems[i].displayName);
          pitem.replace("{v}", myMenuItems[i].id);
          pitem.replace("{i}", myMenuItems[i].id);
          
          root_html_template += pitem;      
        }
            
        root_html_template += String(WIFI_GENERIC_FLDSET_END);
      }
#endif
        
      root_html_template += String(WIFI_GENERIC_HTML_BUTTON) + WIFI_GENERIC_HTML_SCRIPT;     

#if USE_DYNAMIC_PARAMETERS           
      if (NUM_MENU_ITEMS > 0)
      {        
        for (uint16_t i = 0; i < NUM_MENU_ITEMS; i++)
        {
          pitem = String(WIFI_GENERIC_HTML_SCRIPT_ITEM);
          
          pitem.replace("{d}", myMenuItems[i].id);
          
          root_html_template += pitem;        
        }
      }
#endif      
      
      root_html_template += String(WIFI_GENERIC_HTML_SCRIPT_END) + WIFI_GENERIC_HTML_END;
      
      return;     
    }
    
    //////////////////////////////////////////////
    
    void handleRequest()
    {
      if (server)
      {
        String key    = server->arg("key");
        String value  = server->arg("value");

        static int number_items_Updated = 0;

        if (key == "" && value == "")
        {
          String result;
          createHTML(result);

          // Reset configTimeout to stay here until finished.
          configTimeout = 0;

          if ( RFC952_hostname[0] != 0 )
          {
            // Replace only if Hostname is valid
            result.replace("SAM_DUE_WM_NINA_Lite", RFC952_hostname);
          }
          else if ( WIFI_GENERIC_config.board_name[0] != 0 )
          {
            // Or replace only if board_name is valid.  Otherwise, keep intact
            result.replace("SAM_DUE_WM_NINA_Lite", WIFI_GENERIC_config.board_name);
          }

          result.replace("[[id]]",     WIFI_GENERIC_config.WiFi_Creds[0].wifi_ssid);
          result.replace("[[pw]]",     WIFI_GENERIC_config.WiFi_Creds[0].wifi_pw);
          result.replace("[[id1]]",    WIFI_GENERIC_config.WiFi_Creds[1].wifi_ssid);
          result.replace("[[pw1]]",    WIFI_GENERIC_config.WiFi_Creds[1].wifi_pw);
          result.replace("[[nm]]",     WIFI_GENERIC_config.board_name);

#if USE_DYNAMIC_PARAMETERS          
          for (int i = 0; i < NUM_MENU_ITEMS; i++)
          {
            String toChange = String("[[") + myMenuItems[i].id + "]]";
            result.replace(toChange, myMenuItems[i].pdata);
          }
#endif

          // Check if HTML size is larger than 2K, warn that WebServer won't work
          // only with notorious ESP8266-AT 2K buffer limitation.          
          WG_LOGDEBUG1(F("h:HTML page size:"), result.length());
          
          server->send(200, "text/html", result);

          return;
        }

        if (number_items_Updated == 0)
        {
          memset(&WIFI_GENERIC_config, 0, sizeof(WIFI_GENERIC_config));
          strcpy(WIFI_GENERIC_config.header, WIFI_GENERIC_BOARD_TYPE);
        }

#if USE_DYNAMIC_PARAMETERS
        if (!menuItemUpdated)
        {
          // Don't need to free
          menuItemUpdated = new bool[NUM_MENU_ITEMS];
          
          if (menuItemUpdated)
          {
            for (uint16_t i = 0; i < NUM_MENU_ITEMS; i++)
            {           
              // To flag item is not yet updated
              menuItemUpdated[i] = false;           
            }
            
            WG_LOGDEBUG(F("h: Init menuItemUpdated" ));                    
          }
          else
          {
            WG_LOGERROR(F("h: Error can't alloc memory for menuItemUpdated" ));
          }
        }  
#endif

        static bool id_Updated  = false;
        static bool pw_Updated  = false;
        static bool id1_Updated = false;
        static bool pw1_Updated = false;
        static bool nm_Updated  = false;
          
        if (!id_Updated && (key == String("id")))
        {   
          WG_LOGDEBUG(F("h:repl id"));
          id_Updated = true;
          
          number_items_Updated++;
          if (strlen(value.c_str()) < sizeof(WIFI_GENERIC_config.WiFi_Creds[0].wifi_ssid) - 1)
            strcpy(WIFI_GENERIC_config.WiFi_Creds[0].wifi_ssid, value.c_str());
          else
            strncpy(WIFI_GENERIC_config.WiFi_Creds[0].wifi_ssid, value.c_str(), sizeof(WIFI_GENERIC_config.WiFi_Creds[0].wifi_ssid) - 1);
        }
        else if (!pw_Updated && (key == String("pw")))
        {    
          WG_LOGDEBUG(F("h:repl pw"));
          pw_Updated = true;
          
          number_items_Updated++;
          if (strlen(value.c_str()) < sizeof(WIFI_GENERIC_config.WiFi_Creds[0].wifi_pw) - 1)
            strcpy(WIFI_GENERIC_config.WiFi_Creds[0].wifi_pw, value.c_str());
          else
            strncpy(WIFI_GENERIC_config.WiFi_Creds[0].wifi_pw, value.c_str(), sizeof(WIFI_GENERIC_config.WiFi_Creds[0].wifi_pw) - 1);
        }
        else if (!id1_Updated && (key == String("id1")))
        {   
          WG_LOGDEBUG(F("h:repl id1"));
          id1_Updated = true;
          
          number_items_Updated++;
          if (strlen(value.c_str()) < sizeof(WIFI_GENERIC_config.WiFi_Creds[1].wifi_ssid) - 1)
            strcpy(WIFI_GENERIC_config.WiFi_Creds[1].wifi_ssid, value.c_str());
          else
            strncpy(WIFI_GENERIC_config.WiFi_Creds[1].wifi_ssid, value.c_str(), sizeof(WIFI_GENERIC_config.WiFi_Creds[1].wifi_ssid) - 1);
        }
        else if (!pw1_Updated && (key == String("pw1")))
        {    
          WG_LOGDEBUG(F("h:repl pw1"));
          pw1_Updated = true;
          
          number_items_Updated++;
          if (strlen(value.c_str()) < sizeof(WIFI_GENERIC_config.WiFi_Creds[1].wifi_pw) - 1)
            strcpy(WIFI_GENERIC_config.WiFi_Creds[1].wifi_pw, value.c_str());
          else
            strncpy(WIFI_GENERIC_config.WiFi_Creds[1].wifi_pw, value.c_str(), sizeof(WIFI_GENERIC_config.WiFi_Creds[1].wifi_pw) - 1);
        }
        else if (!nm_Updated && (key == String("nm")))
        {
          WG_LOGDEBUG(F("h:repl nm"));
          nm_Updated = true;
          
          number_items_Updated++;
          if (strlen(value.c_str()) < sizeof(WIFI_GENERIC_config.board_name) - 1)
            strcpy(WIFI_GENERIC_config.board_name, value.c_str());
          else
            strncpy(WIFI_GENERIC_config.board_name, value.c_str(), sizeof(WIFI_GENERIC_config.board_name) - 1);
        }
        
#if USE_DYNAMIC_PARAMETERS        
        for (uint16_t i = 0; i < NUM_MENU_ITEMS; i++)
        {
          if ( !menuItemUpdated[i] && (key == myMenuItems[i].id) )
          {
            WG_LOGDEBUG3(F("h:"), myMenuItems[i].id, F("="), value.c_str() );
            
            menuItemUpdated[i] = true;
            
            number_items_Updated++;

            // Actual size of pdata is [maxlen + 1]
            memset(myMenuItems[i].pdata, 0, myMenuItems[i].maxlen + 1);

            if ((int) strlen(value.c_str()) < myMenuItems[i].maxlen)
              strcpy(myMenuItems[i].pdata, value.c_str());
            else
              strncpy(myMenuItems[i].pdata, value.c_str(), myMenuItems[i].maxlen);
          }
        }
#endif

        WG_LOGDEBUG1(F("h:items updated ="), number_items_Updated);
        WG_LOGDEBUG3(F("h:key ="), key, ", value =", value);

        server->send(200, "text/html", "OK");

#if USE_DYNAMIC_PARAMETERS        
        if (number_items_Updated == NUM_CONFIGURABLE_ITEMS + NUM_MENU_ITEMS)
#else
        if (number_items_Updated == NUM_CONFIGURABLE_ITEMS)
#endif 
        {
          WG_LOGERROR(F("h:UpdFlash"));

          saveConfigData();
          
          // Done with CP, Clear CP Flag here if forced
          if (isForcedConfigPortal)
            clearForcedCP();

          WG_LOGERROR(F("h:Rst"));

          // TO DO : what command to reset
          // Delay then reset the board after save data
          delay(1000);
          resetFunc();  //call reset
        }
      }   // if (server)
    }
    
    //////////////////////////////////////////////

#ifndef CONFIG_TIMEOUT
  #warning Default CONFIG_TIMEOUT = 60s
  #define CONFIG_TIMEOUT			60000L
#endif

    void startConfigurationMode()
    {
      WiFi.config(portal_apIP);

      if ( (portal_ssid == "") || portal_pass == "" )
      {
        String randomNum = String(random(0xFFFFFF), HEX);
        randomNum.toUpperCase();

        portal_ssid = "WIFI_GENERIC_" + randomNum;
        portal_pass = "MyWIFI_GENERIC_" + randomNum;
      }
      
      // start access point, AP only, channel 10
           
      uint16_t channel;
     
      // Use random channel if  AP_channel == 0     
      if (AP_channel == 0)
        channel = (millis() % MAX_WIFI_CHANNEL) + 1;
      else
        channel = AP_channel;

      WG_LOGERROR3(F("SSID="), portal_ssid, F(",PW="), portal_pass);
      WG_LOGERROR3(F("IP="), portal_apIP, F(",CH="), channel);

#if USE_ESP_AT_SHIELD
      // start access point, AP only,default channel 10
      WiFi.beginAP(portal_ssid.c_str(), channel, portal_pass.c_str(), ENC_TYPE_WPA2_PSK, true);
#else
      // start access point, AP only,default channel 10
      WiFi.beginAP(portal_ssid.c_str(), portal_pass.c_str(), channel);
#endif
      

      if (!server)
      {
        server = new WiFiWebServer;
      }

      //See https://stackoverflow.com/questions/39803135/c-unresolved-overloaded-function-type?rq=1

      if (server)
      {
        server->on("/", [this](){ handleRequest(); });
        server->begin();
      }

      // If there is no saved config Data, stay in config mode forever until having config Data.
      // or SSID, PW, Server,Token ="nothing"
      if (hadConfigData)
      {
        configTimeout = millis() + CONFIG_TIMEOUT;
                      
        WG_LOGDEBUG3(F("s:millis() = "), millis(), F(", configTimeout = "), configTimeout);
      }
      else
      {
        configTimeout = 0;
               
        WG_LOGDEBUG(F("s:configTimeout = 0"));    
      }

      configuration_mode = true;
    }
};


#endif    //WiFiManager_Generic_Lite_DUE_h
