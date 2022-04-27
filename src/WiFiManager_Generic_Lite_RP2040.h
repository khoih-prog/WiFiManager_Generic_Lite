/*******************************************************************************************************************************
  WiFiManager_Generic_Lite_RP2040.h
  For RP2040 boards using WIFI_GENERIC modules/shields, using much less code to support boards with smaller memory

  WiFiManager_Generic_WM_Lite is a library for the Mega, Teensy, SAM DUE, SAMD and STM32 boards 
  (https://github.com/khoih-prog/WiFiManager_Generic_Lite) to enable store Credentials in EEPROM/LittleFS for easy 
  configuration/reconfiguration and autoconnect/autoreconnect of WiFi and other services without Hardcoding.

  Built by Khoi Hoang https://github.com/khoih-prog/WiFiManager_Generic_Lite
  Licensed under MIT license
  
  Version: 1.7.0

  Version Modified By   Date        Comments
  ------- -----------  ----------   -----------
  1.0.0   K Hoang      04/02/2021  Initial coding for generic boards using generic WiFi.
  ....
  1.5.0   K Hoang      07/01/2022  Configurable WIFI_RECON_INTERVAL. Add support to RP2040 using arduino-pico core
  1.5.1   K Hoang      26/01/2022  Update to be compatible with new FlashStorage libraries. Add support to more SAMD/STM32 boards
  1.6.0   K Hoang      26/01/2022  Optional Board_Name in Menu. Optimize code by using passing by reference
                                   Add optional CONFIG_MODE_LED. Add function isConfigMode()
  1.7.0   K Hoang      27/04/2022  Use WiFiMulti_Generic library for auto-checking / auto-reconnecting MultiWiFi                            
 ********************************************************************************************************************************/

#ifndef WiFiManager_Generic_Lite_RP2040_h
#define WiFiManager_Generic_Lite_RP2040_h

#if ( defined(NANO_RP2040_CONNECT)    || defined(ARDUINO_ARCH_RP2040) || defined(ARDUINO_RASPBERRY_PI_PICO) || \
      defined(ARDUINO_GENERIC_RP2040) || defined(ARDUINO_ADAFRUIT_FEATHER_RP2040) )
  #if defined(WIFI_GENERIC_USE_RP2040)
    #undef WIFI_GENERIC_USE_RP2040
  #endif
  #define WIFI_GENERIC_USE_RP2040      true
#else
  #error This code is intended to run on the RP2040 platform! Please check your Tools->Board setting.  
#endif

#ifndef WIFI_MANAGER_GENERIC_LITE_VERSION
  #define WIFI_MANAGER_GENERIC_LITE_VERSION            "WiFiManager_Generic_Lite v1.7.0"

  #define WIFI_MANAGER_GENERIC_LITE_VERSION_MAJOR      1
  #define WIFI_MANAGER_GENERIC_LITE_VERSION_MINOR      7
  #define WIFI_MANAGER_GENERIC_LITE_VERSION_PATCH      0

#define WIFI_MANAGER_GENERIC_LITE_VERSION_INT          1007000

#endif

#if (USE_WIFI_NINA || USE_WIFI101)
  #include <WiFiMulti_Generic.h>
  #include <WiFiWebServer.h>

  WiFiMulti_Generic wifiMulti;
#else
  #warning You have to include another WiFiWebServer, such as ESP8266_AT_WebServer.
#endif

//////////////////////////////////////////

#warning Using LittleFS in WiFiManager_Generic_Lite_RP2040.h

//////////////////////////////////////////

#include <WiFiManager_Generic_Lite_Debug.h>

#ifndef USING_CUSTOMS_STYLE
  #define USING_CUSTOMS_STYLE     false
#endif

#ifndef USING_CUSTOMS_HEAD_ELEMENT
  #define USING_CUSTOMS_HEAD_ELEMENT     false
#endif

#ifndef USING_CORS_FEATURE
  #define USING_CORS_FEATURE     false
#endif

//////////////////////////////////////////////

// New from v1.3.0
// KH, Some minor simplification
#if !defined(SCAN_WIFI_NETWORKS)
  #define SCAN_WIFI_NETWORKS     true     //false
#endif
	
#if SCAN_WIFI_NETWORKS
  #if !defined(MANUAL_SSID_INPUT_ALLOWED)
    #define MANUAL_SSID_INPUT_ALLOWED     true
  #endif

  #if !defined(MAX_SSID_IN_LIST)
    #define MAX_SSID_IN_LIST     6
  #elif (MAX_SSID_IN_LIST < 2)
    #warning Parameter MAX_SSID_IN_LIST defined must be >= 2 - Reset to 6
    #undef MAX_SSID_IN_LIST
    #define MAX_SSID_IN_LIST      6
  #elif (MAX_SSID_IN_LIST > 15)
    #warning Parameter MAX_SSID_IN_LIST defined must be <= 15 - Reset to 6
    #undef MAX_SSID_IN_LIST
    #define MAX_SSID_IN_LIST      6
  #endif
#else
  #warning SCAN_WIFI_NETWORKS disabled	
#endif

///////// NEW for DRD /////////////
// These defines must be put before #include <DoubleResetDetector_Generic.h>
// to select where to store DoubleResetDetector_Generic's variable.
// Otherwise, library will use default EEPROM storage
#define  DRD_FLAG_DATA_SIZE     4

#ifndef DOUBLERESETDETECTOR_DEBUG
#define DOUBLERESETDETECTOR_DEBUG     false
#endif

#include <DoubleResetDetector_Generic.h>      //https://github.com/khoih-prog/DoubleResetDetector_Generic

// Number of seconds after reset during which a
// subseqent reset will be considered a double reset.
#define DRD_TIMEOUT 10

// RTC Memory Address for the DoubleResetDetector_Generic to use
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

#if USING_BOARD_NAME
  // Configurable items besides fixed Header, just add board_name 
  #define NUM_CONFIGURABLE_ITEMS    ( ( 2 * NUM_WIFI_CREDENTIALS ) + 1 )
#else
  // Configurable items besides fixed Header, just add board_name 
  #define NUM_CONFIGURABLE_ITEMS    ( ( 2 * NUM_WIFI_CREDENTIALS ))
#endif

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

const char WIFI_GENERIC_HTML_HEAD_START[] /*PROGMEM*/ = "<!DOCTYPE html><html><head><title>RP2040_WM_Lite</title>";

const char WIFI_GENERIC_HTML_HEAD_STYLE[] /*PROGMEM*/ = "<style>div,input{padding:5px;font-size:1em;}input{width:95%;}body{text-align: center;}button{background-color:#16A1E7;color:#fff;line-height:2.4rem;font-size:1.2rem;width:100%;}fieldset{border-radius:0.3rem;margin:0px;}</style>";

#if USING_BOARD_NAME
const char WIFI_GENERIC_HTML_HEAD_END[]   /*PROGMEM*/ = "</head><div style='text-align:left;display:inline-block;min-width:260px;'>\
<fieldset><div><label>*WiFi SSID</label><div>[[input_id]]</div></div>\
<div><label>*PWD (8+ chars)</label><input value='[[pw]]' id='pw'><div></div></div>\
<div><label>*WiFi SSID1</label><div>[[input_id1]]</div></div>\
<div><label>*PWD1 (8+ chars)</label><input value='[[pw1]]' id='pw1'><div></div></div></fieldset>\
<fieldset><div><label>Board Name</label><input value='[[nm]]' id='nm'><div></div></div></fieldset>";	// DO NOT CHANGE THIS STRING EVER!!!!
#else
const char WIFI_GENERIC_HTML_HEAD_END[]   /*PROGMEM*/ = "</head><div style='text-align:left;display:inline-block;min-width:260px;'>\
<fieldset><div><label>*WiFi SSID</label><div>[[input_id]]</div></div>\
<div><label>*PWD (8+ chars)</label><input value='[[pw]]' id='pw'><div></div></div>\
<div><label>*WiFi SSID1</label><div>[[input_id1]]</div></div>\
<div><label>*PWD1 (8+ chars)</label><input value='[[pw1]]' id='pw1'><div></div></div></fieldset>";	// DO NOT CHANGE THIS STRING EVER!!!!
#endif

const char WIFI_GENERIC_HTML_INPUT_ID[]   /*PROGMEM*/ = "<input value='[[id]]' id='id'>";
const char WIFI_GENERIC_HTML_INPUT_ID1[]  /*PROGMEM*/ = "<input value='[[id1]]' id='id1'>";

const char WIFI_GENERIC_FLDSET_START[]  /*PROGMEM*/ = "<fieldset>";
const char WIFI_GENERIC_FLDSET_END[]    /*PROGMEM*/ = "</fieldset>";
const char WIFI_GENERIC_HTML_PARAM[]    /*PROGMEM*/ = "<div><label>{b}</label><input value='[[{v}]]'id='{i}'><div></div></div>";
const char WIFI_GENERIC_HTML_BUTTON[]   /*PROGMEM*/ = "<button onclick=\"sv()\">Save</button></div>";

#if USING_BOARD_NAME
const char WIFI_GENERIC_HTML_SCRIPT[]   /*PROGMEM*/ = "<script id=\"jsbin-javascript\">\
function udVal(key,val){var request=new XMLHttpRequest();var url='/?key='+key+'&value='+encodeURIComponent(val);\
request.open('GET',url,false);request.send(null);}\
function sv(){udVal('id',document.getElementById('id').value);udVal('pw',document.getElementById('pw').value);\
udVal('id1',document.getElementById('id1').value);udVal('pw1',document.getElementById('pw1').value);\
udVal('nm',document.getElementById('nm').value);";
#else
const char WIFI_GENERIC_HTML_SCRIPT[]   /*PROGMEM*/ = "<script id=\"jsbin-javascript\">\
function udVal(key,val){var request=new XMLHttpRequest();var url='/?key='+key+'&value='+encodeURIComponent(val);\
request.open('GET',url,false);request.send(null);}\
function sv(){udVal('id',document.getElementById('id').value);udVal('pw',document.getElementById('pw').value);\
udVal('id1',document.getElementById('id1').value);udVal('pw1',document.getElementById('pw1').value);";
#endif

const char WIFI_GENERIC_HTML_SCRIPT_ITEM[]  /*PROGMEM*/ = "udVal('{d}',document.getElementById('{d}').value);";
const char WIFI_GENERIC_HTML_SCRIPT_END[]   /*PROGMEM*/ = "alert('Updated');}</script>";
const char WIFI_GENERIC_HTML_END[]          /*PROGMEM*/ = "</html>";

#if SCAN_WIFI_NETWORKS
const char WIFI_GENERIC_SELECT_START[]      /*PROGMEM*/ = "<select id=";
const char WIFI_GENERIC_SELECT_END[]        /*PROGMEM*/ = "</select>";
const char WIFI_GENERIC_DATALIST_START[]    /*PROGMEM*/ = "<datalist id=";
const char WIFI_GENERIC_DATALIST_END[]      /*PROGMEM*/ = "</datalist>";
const char WIFI_GENERIC_OPTION_START[]      /*PROGMEM*/ = "<option>";
const char WIFI_GENERIC_OPTION_END[]        /*PROGMEM*/ = "";			// "</option>"; is not required
const char WIFI_GENERIC_NO_NETWORKS_FOUND[] /*PROGMEM*/ = "No suitable WiFi networks available!";
#endif

//////////////////////////////////////////

//KH Add repeatedly used const
//KH, from v1.1.0
const char WM_HTTP_HEAD_CL[]         PROGMEM = "Content-Length";
const char WM_HTTP_HEAD_TEXT_HTML[]  PROGMEM = "text/html";
const char WM_HTTP_HEAD_TEXT_PLAIN[] PROGMEM = "text/plain";

const char WM_HTTP_CACHE_CONTROL[]   PROGMEM = "Cache-Control";
const char WM_HTTP_NO_STORE[]        PROGMEM = "no-cache, no-store, must-revalidate";
const char WM_HTTP_PRAGMA[]          PROGMEM = "Pragma";
const char WM_HTTP_NO_CACHE[]        PROGMEM = "no-cache";
const char WM_HTTP_EXPIRES[]         PROGMEM = "Expires";

const char WM_HTTP_CORS[]            PROGMEM = "Access-Control-Allow-Origin";
const char WM_HTTP_CORS_ALLOW_ALL[]  PROGMEM = "*";

//////////////////////////////////////////////

// New from v1.2.0
#if !defined(REQUIRE_ONE_SET_SSID_PW)
  #define REQUIRE_ONE_SET_SSID_PW     false
#endif

#define PASSWORD_MIN_LEN        8

//////////////////////////////////////////////

String IPAddressToString(const IPAddress& _address)
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
#if ( USE_WIFI101 || USE_ESP_AT_SHIELD )
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
      {
        delete server;

#if SCAN_WIFI_NETWORKS
        if (indices)
        {
          free(indices); //indices array no longer required so free memory
        }
#endif
      }
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
 
#if USING_CONFIG_MODE_LED  
      //Turn OFF
      pinMode(LED_BUILTIN, OUTPUT);
      digitalWrite(LED_BUILTIN, LED_OFF);
#endif 
      
      if (iHostname[0] == 0)
      {
        String randomNum = String(random(0xFFFFFF), HEX);
        randomNum.toUpperCase();
        
        String _hostname = "RP2040-WIFI-" + randomNum;
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

#if (USE_WIFI_NINA || USE_WIFI101)        
        wifiMulti.addAP(WIFI_GENERIC_config.WiFi_Creds[0].wifi_ssid, WIFI_GENERIC_config.WiFi_Creds[0].wifi_pw);
  			wifiMulti.addAP(WIFI_GENERIC_config.WiFi_Creds[1].wifi_ssid, WIFI_GENERIC_config.WiFi_Creds[1].wifi_pw);
#endif

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

#if !defined(WIFI_RECON_INTERVAL)      
  #define WIFI_RECON_INTERVAL       0         // default 0s between reconnecting WiFi
#else
  #if (WIFI_RECON_INTERVAL < 0)
    #define WIFI_RECON_INTERVAL     0
  #elif  (WIFI_RECON_INTERVAL > 600000)
    #define WIFI_RECON_INTERVAL     600000    // Max 10min
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
      
      static uint32_t curMillis;
      
      curMillis = millis();
      
      //// New DRD ////
      // Call the double reset detector loop method every so often,
      // so that it can recognise when the timeout expires.
      // You can also call drd.stop() when you wish to no longer
      // consider the next reset as a double reset.
      drd->loop();
      //// New DRD ////
         
      if ( !configuration_mode && (curMillis > checkstatus_timeout) )
      {       
        if (WiFi.status() == WL_CONNECTED)
        {
          wifi_connected = true;
          
#if USING_CONFIG_MODE_LED
          // turn the LED_BUILTIN OFF to tell us we exit configuration mode.
          digitalWrite(CONFIG_MODE_LED, LED_OFF);
#endif
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
        
        checkstatus_timeout = curMillis + WIFI_STATUS_CHECK_INTERVAL;
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
            
 
#if (WIFI_RECON_INTERVAL > 0)

            static uint32_t lastMillis = 0;
            
            if ( (lastMillis == 0) || (curMillis - lastMillis) > WIFI_RECON_INTERVAL )
            {
              lastMillis = curMillis;
              
              WG_LOGERROR(F("r:WLost.ReconW"));
               
              if (connectMultiWiFi(RETRY_TIMES_RECONNECT_WIFI))
              {
                WG_LOGERROR(F("r:WOK"));
              }
            }
#else
            WG_LOGERROR(F("r:WLost.ReconW"));
            
            if (connectMultiWiFi(RETRY_TIMES_RECONNECT_WIFI))
            {
              WG_LOGERROR(F("r:WOK"));
            }
#endif            
          }
        }
      }
      else if (configuration_mode)
      {
        configuration_mode = false;
        WG_LOGERROR(F("r:gotWBack"));
        
#if USING_CONFIG_MODE_LED
        // turn the LED_BUILTIN OFF to tell us we exit configuration mode.
        digitalWrite(CONFIG_MODE_LED, LED_OFF);
#endif 
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

    void setConfigPortalIP(const IPAddress& portalIP = IPAddress(192, 168, 4, 1))
    {
      portal_apIP = portalIP;
    }
    
    //////////////////////////////////////////////

    #define MIN_WIFI_CHANNEL      1
    #define MAX_WIFI_CHANNEL      11    // Channel 13 is flaky, because of bad number 13 ;-)

    int setConfigPortalChannel(const int& channel = 1)
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
    
    void setConfigPortal(const String& ssid = "", const String& pass = "")
    {
      portal_ssid = ssid;
      portal_pass = pass;
    }
    
    //////////////////////////////////////////////

    void setSTAStaticIPConfig(const IPAddress& ip)
    {
      static_IP = ip;
    }
    
    //////////////////////////////////////////////
    
    String getWiFiSSID(const uint8_t& index)
    { 
      if (index >= NUM_WIFI_CREDENTIALS)
        return String("");
        
      if (!hadConfigData)
        getConfigData();

      return (String(WIFI_GENERIC_config.WiFi_Creds[index].wifi_ssid));
    }
    
    //////////////////////////////////////////////

    String getWiFiPW(const uint8_t& index)
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
    
    bool isConfigMode()
    {
      return configuration_mode;
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
        
    typedef struct
    {
      uint32_t CPUID;                  /*!< Offset: 0x000 (R/ )  CPUID Base Register */
      uint32_t ICSR;                   /*!< Offset: 0x004 (R/W)  Interrupt Control and State Register */
      uint32_t RESERVED0;
      uint32_t AIRCR;                  /*!< Offset: 0x00C (R/W)  Application Interrupt and Reset Control Register */
      uint32_t SCR;                    /*!< Offset: 0x010 (R/W)  System Control Register */
      uint32_t CCR;                    /*!< Offset: 0x014 (R/W)  Configuration Control Register */
      uint32_t RESERVED1;
      uint32_t SHP[2U];                /*!< Offset: 0x01C (R/W)  System Handlers Priority Registers. [0] is RESERVED */
      uint32_t SHCSR;                  /*!< Offset: 0x024 (R/W)  System Handler Control and State Register */
    } SCB_Type;
    
    //////////////////////////////////////////////

    void NVIC_SystemReset()
    {                  
    /* SCB Application Interrupt and Reset Control Register Definitions */
    #define SCB_AIRCR_VECTKEY_Pos              16U                                      /*!< SCB AIRCR: VECTKEY Position */
    #define SCB_AIRCR_VECTKEY_Msk              (0xFFFFUL << SCB_AIRCR_VECTKEY_Pos)      /*!< SCB AIRCR: VECTKEY Mask */
        
    #define SCB_AIRCR_SYSRESETREQ_Pos           2U                                      /*!< SCB AIRCR: SYSRESETREQ Position */
    #define SCB_AIRCR_SYSRESETREQ_Msk          (1UL << SCB_AIRCR_SYSRESETREQ_Pos)       /*!< SCB AIRCR: SYSRESETREQ Mask */    

    #define SCS_BASE            (0xE000E000UL)                            /*!< System Control Space Base Address */
    #define SysTick_BASE        (SCS_BASE +  0x0010UL)                    /*!< SysTick Base Address */
    #define NVIC_BASE           (SCS_BASE +  0x0100UL)                    /*!< NVIC Base Address */
    #define SCB_BASE            (SCS_BASE +  0x0D00UL)                    /*!< System Control Block Base Address */

    #define SCB                 ((SCB_Type       *)     SCB_BASE      )   /*!< SCB configuration struct */
    #define SysTick             ((SysTick_Type   *)     SysTick_BASE  )   /*!< SysTick configuration struct */
    #define NVIC                ((NVIC_Type      *)     NVIC_BASE     )   /*!< NVIC configuration struct */

                                  
      SCB->AIRCR  = ((0x5FAUL << SCB_AIRCR_VECTKEY_Pos) | SCB_AIRCR_SYSRESETREQ_Msk);

      while(true);
    }

    //////////////////////////////////////////////
    
    void resetFunc()
    {
      delay(1000);
      // Restart for RPi_Pico
      NVIC_SystemReset();
    }

    //////////////////////////////////////
    
    // Add customs headers from v1.1.0
    
    // New from v1.1.0, for configure CORS Header, default to WM_HTTP_CORS_ALLOW_ALL = "*"

#if USING_CUSTOMS_STYLE
    //sets a custom style, such as color
    // "<style>div,input{padding:5px;font-size:1em;}
    // input{width:95%;}body{text-align: center;}
    // button{background-color:#16A1E7;color:#fff;line-height:2.4rem;font-size:1.2rem;width:100%;}
    // fieldset{border-radius:0.3rem;margin:0px;}</style>";
    void setCustomsStyle(const char* CustomsStyle = WIFI_GENERIC_HTML_HEAD_STYLE) 
    {
      WIFI_GENERIC_HTML_HEAD_CUSTOMS_STYLE = CustomsStyle;
      WG_LOGDEBUG1(F("Set CustomsStyle to : "), WIFI_GENERIC_HTML_HEAD_CUSTOMS_STYLE);
    }
    
    const char* getCustomsStyle()
    {
      WG_LOGDEBUG1(F("Get CustomsStyle = "), WIFI_GENERIC_HTML_HEAD_CUSTOMS_STYLE);
      return WIFI_GENERIC_HTML_HEAD_CUSTOMS_STYLE;
    }
#endif

#if USING_CUSTOMS_HEAD_ELEMENT    
    //sets a custom element to add to head, like a new style tag
    void setCustomsHeadElement(const char* CustomsHeadElement = NULL) 
    {
      _CustomsHeadElement = CustomsHeadElement;
      WG_LOGDEBUG1(F("Set CustomsHeadElement to : "), _CustomsHeadElement);
    }
    
    const char* getCustomsHeadElement()
    {
      WG_LOGDEBUG1(F("Get CustomsHeadElement = "), _CustomsHeadElement);
      return _CustomsHeadElement;
    }
#endif
    
#if USING_CORS_FEATURE   
    void setCORSHeader(const char* CORSHeaders = NULL)
    {     
      _CORS_Header = CORSHeaders;

      WG_LOGDEBUG1(F("Set CORS Header to : "), _CORS_Header);
    }
    
    const char* getCORSHeader()
    {      
      WG_LOGDEBUG1(F("Get CORS Header = "), _CORS_Header);
      return _CORS_Header;
    }
#endif
          
    //////////////////////////////////////


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

    /////////////////////////////////////
    
    // Add customs headers from v1.1.0
    
#if USING_CUSTOMS_STYLE
    const char* WIFI_GENERIC_HTML_HEAD_CUSTOMS_STYLE = NULL;
#endif
    
#if USING_CUSTOMS_HEAD_ELEMENT
    const char* _CustomsHeadElement = NULL;
#endif
    
#if USING_CORS_FEATURE    
    const char* _CORS_Header        = WM_HTTP_CORS_ALLOW_ALL;   //"*";
#endif
       
    /////////////////////////////////////
    // Add WiFi Scan from v1.3.0
    
#if SCAN_WIFI_NETWORKS
  int WiFiNetworksFound = 0;		// Number of SSIDs found by WiFi scan, including low quality and duplicates
  int *indices;					        // WiFi network data, filled by scan (SSID, BSSID)
  String ListOfSSIDs = "";		  // List of SSIDs found by scan, in HTML <option> format
#endif

    //////////////////////////////////////
    
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
    
    void displayConfigData(const WIFI_GENERIC_Configuration& configData)
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
#define WM_NO_CONFIG              "blank"

    int calcChecksum()
    {
      int checkSum = 0;
      for (uint16_t index = 0; index < (sizeof(WIFI_GENERIC_config) - sizeof(WIFI_GENERIC_config.checkSum)); index++)
      {
        checkSum += * ( ( (byte*) &WIFI_GENERIC_config ) + index);
      }

      return checkSum;
    }
    
// Use LittleFS/InternalFS for RP2040
#define  CONFIG_FILENAME                  ("/fs/wm_config.dat")
#define  CONFIG_FILENAME_BACKUP           ("/fs/wm_config.bak")

#define  CREDENTIALS_FILENAME             ("/fs/wm_cred.dat")
#define  CREDENTIALS_FILENAME_BACKUP      ("/fs/wm_cred.bak")

#define  CONFIG_PORTAL_FILENAME           ("/fs/wm_cp.dat")
#define  CONFIG_PORTAL_FILENAME_BACKUP    ("/fs/wm_cp.bak")

    //////////////////////////////////////////////

#if defined(ARDUINO_ARCH_MBED)
    #warning Using Arduino-mbed core
    // For boards using Arduino-mbed core
        
    void saveForcedCP(const uint32_t& value)
    {
      // Mbed RP2040 code
      FILE *file = fopen(CONFIG_PORTAL_FILENAME, "w");
      
      WG_LOGERROR(F("SaveCPFile "));

      if (file)
      {
        fseek(file, 0, SEEK_SET);
        fwrite((uint8_t *) &value, 1, sizeof(value), file);        
        fclose(file);
        
        WG_LOGERROR(F("OK"));
      }
      else
      {
        WG_LOGERROR(F("failed"));
      }

      // Trying open redundant CP file
      file = fopen(CONFIG_PORTAL_FILENAME_BACKUP, "w");
      
      WG_LOGERROR(F("SaveBkUpCPFile "));

      if (file)
      {
        fseek(file, 0, SEEK_SET);
        fwrite((uint8_t *) &value, 1, sizeof(value), file);        
        fclose(file);
        
        WG_LOGERROR(F("OK"));
      }
      else
      {
        WG_LOGERROR(F("failed"));
      }
    }
    
    //////////////////////////////////////////////
    
    void setForcedCP(const bool& isPersistent)
    {
      uint32_t readForcedConfigPortalFlag = isPersistent? FORCED_PERS_CONFIG_PORTAL_FLAG_DATA : FORCED_CONFIG_PORTAL_FLAG_DATA;
  
      WG_LOGERROR(isPersistent ? F("setForcedCP Persistent") : F("setForcedCP non-Persistent"));
      
      saveForcedCP(readForcedConfigPortalFlag);
    }
    
    //////////////////////////////////////////////
    
    void clearForcedCP()
    {
      uint32_t readForcedConfigPortalFlag = 0;
   
      WG_LOGERROR(F("clearForcedCP"));
      
      saveForcedCP(readForcedConfigPortalFlag);
    }
    
    //////////////////////////////////////////////

    bool isForcedCP()
    {
      uint32_t readForcedConfigPortalFlag;
    
      WG_LOGDEBUG(F("Check if isForcedCP"));
      
      FILE *file = fopen(CONFIG_PORTAL_FILENAME, "r");
      
      WG_LOGDEBUG(F("LoadCPFile "));

      if (!file)
      {
        WG_LOGDEBUG(F("failed"));

        // Trying open redundant config file
        file = fopen(CONFIG_PORTAL_FILENAME_BACKUP, "r");
        
        WG_LOGDEBUG(F("LoadBkUpCPFile "));

        if (!file)
        {
          WG_LOGDEBUG(F("failed"));
          return false;
        }
      }
           
      fseek(file, 0, SEEK_SET);
      fread((uint8_t *) &readForcedConfigPortalFlag, 1, sizeof(readForcedConfigPortalFlag), file);        
      fclose(file);
      WG_LOGDEBUG(F("OK"));
      
      
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
      char* readBuffer = nullptr;
           
      FILE *file = fopen(CREDENTIALS_FILENAME, "r");
      
      WG_LOGDEBUG(F("LoadCredFile "));

      if (!file)
      {
        WG_LOGDEBUG(F("failed"));

        // Trying open redundant config file
        file = fopen(CREDENTIALS_FILENAME_BACKUP, "r");
        
        WG_LOGDEBUG(F("LoadBkUpCredFile "));

        if (!file)
        {
          WG_LOGDEBUG(F("failed"));
          return false;
        }
      }
      
      // Find the longest pdata, then dynamically allocate buffer. Remember to free when done
      // This is used to store tempo data to calculate checksum to see of data is valid
      // We dont like to destroy myMenuItems[i].pdata with invalid data
      
      uint16_t maxBufferLength = 0;
      
      for (uint16_t i = 0; i < NUM_MENU_ITEMS; i++)
      {       
        if (myMenuItems[i].maxlen > maxBufferLength)
          maxBufferLength = myMenuItems[i].maxlen;
      }
      
      if (maxBufferLength > 0)
      {
        readBuffer = new char[ maxBufferLength + 1 ];
        
        // check to see NULL => stop and return false
        if (readBuffer == NULL)
        {
          WG_LOGERROR(F("ChkCrR: Error can't allocate buffer."));
          return false;
        }     
        else
        {
          WG_LOGDEBUG1(F("ChkCrR: Buffer allocated, Sz="), maxBufferLength + 1);
        }  
          
        uint16_t offset = 0;
        
        for (uint16_t i = 0; i < NUM_MENU_ITEMS; i++)
        {       
          uint8_t * _pointer = (uint8_t *) readBuffer;

          // Actual size of pdata is [maxlen + 1]
          memset(readBuffer, 0, myMenuItems[i].maxlen + 1);
          
          // Redundant, but to be sure correct position         
          fseek(file, offset, SEEK_SET);
          fread(_pointer, 1, myMenuItems[i].maxlen, file);  
           
          offset += myMenuItems[i].maxlen;
       
          WG_LOGDEBUG3(F("ChkCrR:pdata="), readBuffer, F(",len="), myMenuItems[i].maxlen);         
                 
          for (uint16_t j = 0; j < myMenuItems[i].maxlen; j++,_pointer++)
          {         
            checkSum += *_pointer;  
          }       
        }

        fread((uint8_t *) &readCheckSum, 1, sizeof(readCheckSum), file);
        
        WG_LOGDEBUG(F("OK"));
        
        fclose(file);
        
        WG_LOGERROR3(F("CrCCsum=0x"), String(checkSum, HEX), F(",CrRCsum=0x"), String(readCheckSum, HEX));
        
        if (readBuffer != nullptr)
        {
          // Free buffer
          delete [] readBuffer;
          WG_LOGDEBUG(F("Buffer freed"));
        }
        
        if ( checkSum == readCheckSum)
        {
          return true;
        }
      }
      
      return false;
    }
    
    //////////////////////////////////////////////

    bool loadDynamicData()
    {
      int checkSum = 0;
      int readCheckSum;
      totalDataSize = sizeof(WIFI_GENERIC_config) + sizeof(readCheckSum);
      
      FILE *file = fopen(CREDENTIALS_FILENAME, "r");
      
      WG_LOGDEBUG(F("LoadCredFile "));

      if (!file)
      {
        WG_LOGDEBUG(F("failed"));

        // Trying open redundant config file
        file = fopen(CREDENTIALS_FILENAME_BACKUP, "r");
        
        WG_LOGDEBUG(F("LoadBkUpCredFile "));

        if (!file)
        {
          WG_LOGDEBUG(F("failed"));
          return false;
        }
      }
     
      uint16_t offset = 0;
      
      for (uint16_t i = 0; i < NUM_MENU_ITEMS; i++)
      {       
        uint8_t * _pointer = (uint8_t *) myMenuItems[i].pdata;
        totalDataSize += myMenuItems[i].maxlen;

        // Actual size of pdata is [maxlen + 1]
        memset(myMenuItems[i].pdata, 0, myMenuItems[i].maxlen + 1);
        
        // Redundant, but to be sure correct position
        fseek(file, offset, SEEK_SET);
        fread(_pointer, 1, myMenuItems[i].maxlen, file);
        
        offset += myMenuItems[i].maxlen;        
    
        WG_LOGDEBUG3(F("CrR:pdata="), myMenuItems[i].pdata, F(",len="), myMenuItems[i].maxlen);         
               
        for (uint16_t j = 0; j < myMenuItems[i].maxlen; j++,_pointer++)
        {         
          checkSum += *_pointer;  
        }       
      }

      fread((uint8_t *) &readCheckSum, 1, sizeof(readCheckSum), file);
      
      WG_LOGDEBUG(F("OK"));
      
      fclose(file);
      
      WG_LOGDEBUG3(F("CrCCsum=0x"), String(checkSum, HEX), F(",CrRCsum=0x"), String(readCheckSum, HEX));
      
      if ( checkSum != readCheckSum)
      {
        return false;
      }
      
      return true;    
    }
    
    //////////////////////////////////////////////

    void saveDynamicData()
    {
      int checkSum = 0;
    
      FILE *file = fopen(CREDENTIALS_FILENAME, "w");
      
      WG_LOGDEBUG(F("SaveCredFile "));

      uint16_t offset = 0;
      
      for (uint16_t i = 0; i < NUM_MENU_ITEMS; i++)
      {       
        uint8_t* _pointer = (uint8_t *) myMenuItems[i].pdata;
       
        WG_LOGDEBUG3(F("CW1:pdata="), myMenuItems[i].pdata, F(",len="), myMenuItems[i].maxlen);
        
        if (file)
        {
          // Redundant, but to be sure correct position
          fseek(file, offset, SEEK_SET);
          fwrite(_pointer, 1, myMenuItems[i].maxlen, file); 
          
          offset += myMenuItems[i].maxlen;      
        }
        else
        {
          WG_LOGDEBUG(F("failed"));
        }        
                     
        for (uint16_t j = 0; j < myMenuItems[i].maxlen; j++,_pointer++)
        {         
          checkSum += *_pointer;     
         }
      }
      
      if (file)
      {
        fwrite((uint8_t *) &checkSum, 1, sizeof(checkSum), file);        
        fclose(file);
        
        WG_LOGDEBUG(F("OK"));    
      }
      else
      {
        WG_LOGDEBUG(F("failed"));
      }   
           
      WG_LOGDEBUG1(F("CrWCSum=0x"), String(checkSum, HEX));
      
      // Trying open redundant Auth file
      file = fopen(CREDENTIALS_FILENAME_BACKUP, "w");
      
      WG_LOGDEBUG(F("SaveBkUpCredFile "));

      offset = 0;
      
      for (uint16_t i = 0; i < NUM_MENU_ITEMS; i++)
      {       
        uint8_t* _pointer = (uint8_t *) myMenuItems[i].pdata;
     
        WG_LOGDEBUG3(F("CW2:pdata="), myMenuItems[i].pdata, F(",len="), myMenuItems[i].maxlen);
        
        if (file)
        {
          fseek(file, offset, SEEK_SET);
          fwrite(_pointer, 1, myMenuItems[i].maxlen, file); 
          
          // Redundant, but to be sure correct position
          offset += myMenuItems[i].maxlen; 
        }
        else
        {
          WG_LOGDEBUG(F("failed"));
        }        
                     
        for (uint16_t j = 0; j < myMenuItems[i].maxlen; j++,_pointer++)
        {         
          checkSum += *_pointer;     
         }
      }
      
      if (file)
      {
        fwrite((uint8_t *) &checkSum, 1, sizeof(checkSum), file);        
        fclose(file);
        
        WG_LOGDEBUG(F("OK"));    
      }
      else
      {
        WG_LOGDEBUG(F("failed"));
      }   
    }
#endif

    //////////////////////////////////////////////

    bool loadConfigData()
    {
      WG_LOGDEBUG(F("LoadCfgFile "));
      
      // file existed
      FILE *file = fopen(CONFIG_FILENAME, "r");
      
      if (!file)
      {
        WG_LOGDEBUG(F("failed"));

        // Trying open redundant config file
        file = fopen(CONFIG_FILENAME_BACKUP, "r");
        
        WG_LOGDEBUG(F("LoadBkUpCfgFile "));

        if (!file)
        {
          WG_LOGDEBUG(F("failed"));
          return false;
        }
      }
     
      fseek(file, 0, SEEK_SET);
      fread((uint8_t *) &WIFI_GENERIC_config, 1, sizeof(WIFI_GENERIC_config), file);
      fclose(file);

      WG_LOGDEBUG(F("OK"));
      
      return isWiFiConfigValid();
    }
    
    //////////////////////////////////////////////

    void saveConfigData()
    {
      WG_LOGDEBUG(F("SaveCfgFile "));

      int calChecksum = calcChecksum();
      WIFI_GENERIC_config.checkSum = calChecksum;
      WG_LOGDEBUG1(F("WCSum=0x"), String(calChecksum, HEX));
      
      FILE *file = fopen(CONFIG_FILENAME, "w");

      if (file)
      {
        fseek(file, 0, SEEK_SET);
        fwrite((uint8_t *) &WIFI_GENERIC_config, 1, sizeof(WIFI_GENERIC_config), file);
        fclose(file);
        
        WG_LOGDEBUG(F("OK"));
      }
      else
      {
        WG_LOGDEBUG(F("failed"));
      }
      
      WG_LOGDEBUG(F("SaveBkUpCfgFile "));
      
      // Trying open redundant Auth file
      file = fopen(CONFIG_FILENAME_BACKUP, "w");

      if (file)
      {
        fseek(file, 0, SEEK_SET);
        fwrite((uint8_t *) &WIFI_GENERIC_config, 1, sizeof(WIFI_GENERIC_config), file);
        fclose(file);
        
        WG_LOGDEBUG(F("OK"));
      }
      else
      {
        WG_LOGDEBUG(F("failed"));
      }
      
#if USE_DYNAMIC_PARAMETERS      
      saveDynamicData();
#endif

#if (USE_WIFI_NINA || USE_WIFI101)        
        wifiMulti.addAP(WIFI_GENERIC_config.WiFi_Creds[0].wifi_ssid, WIFI_GENERIC_config.WiFi_Creds[0].wifi_pw);
  			wifiMulti.addAP(WIFI_GENERIC_config.WiFi_Creds[1].wifi_ssid, WIFI_GENERIC_config.WiFi_Creds[1].wifi_pw);
#endif
    }

//////////////////////////////////////////////

#else   // #if defined(ARDUINO_ARCH_MBED)

//////////////////////////////////////////////

    #warning Using arduino-pico core
    // For boards using arduino-pico core
    // Already defined in DoubleResetDetector_Generic.h
    // FS* filesystem =      &LittleFS;
    // #define FileFS        LittleFS
    
    //#define SEEK_SET        SeekSet     
    
    void saveForcedCP(const uint32_t& value)
    {
      // Mbed RP2040 code
      File file = filesystem->open(CONFIG_PORTAL_FILENAME, "w");
      
      WG_LOGERROR(F("SaveCPFile "));

      if (file)
      {
        file.seek(0, SeekSet);
        file.write((uint8_t *) &value, sizeof(value));        
        file.close();
        
        WG_LOGERROR(F("OK"));
      }
      else
      {
        WG_LOGERROR(F("failed"));
      }

      // Trying open redundant CP file
      file = filesystem->open(CONFIG_PORTAL_FILENAME_BACKUP, "w");
      
      WG_LOGERROR(F("SaveBkUpCPFile "));

      if (file)
      {
        file.seek(0, SeekSet);
        file.write((uint8_t *) &value, sizeof(value));        
        file.close();
        
        WG_LOGERROR(F("OK"));
      }
      else
      {
        WG_LOGERROR(F("failed"));
      }
    }
    
    //////////////////////////////////////////////
    
    void setForcedCP(const bool& isPersistent)
    {
      uint32_t readForcedConfigPortalFlag = isPersistent? FORCED_PERS_CONFIG_PORTAL_FLAG_DATA : FORCED_CONFIG_PORTAL_FLAG_DATA;
  
      WG_LOGERROR(isPersistent ? F("setForcedCP Persistent") : F("setForcedCP non-Persistent"));
      
      saveForcedCP(readForcedConfigPortalFlag);
    }
    
    //////////////////////////////////////////////
    
    void clearForcedCP()
    {
      uint32_t readForcedConfigPortalFlag = 0;
   
      WG_LOGERROR(F("clearForcedCP"));
      
      saveForcedCP(readForcedConfigPortalFlag);
    }
    
    //////////////////////////////////////////////

    bool isForcedCP()
    {
      uint32_t readForcedConfigPortalFlag;
    
      WG_LOGDEBUG(F("Check if isForcedCP"));
      
      File file = filesystem->open(CONFIG_PORTAL_FILENAME, "r");
      
      WG_LOGDEBUG(F("LoadCPFile "));

      if (!file)
      {
        WG_LOGDEBUG(F("failed"));

        // Trying open redundant config file
        file = filesystem->open(CONFIG_PORTAL_FILENAME_BACKUP, "r");
        
        WG_LOGDEBUG(F("LoadBkUpCPFile "));

        if (!file)
        {
          WG_LOGDEBUG(F("failed"));
          return false;
        }
      }
           
      file.seek(0, SeekSet);
      file.read((uint8_t *) &readForcedConfigPortalFlag, sizeof(readForcedConfigPortalFlag));        
      file.close();
      WG_LOGDEBUG(F("OK"));
      
      
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
      char* readBuffer = nullptr;
           
      File file = filesystem->open(CREDENTIALS_FILENAME, "r");
      
      WG_LOGDEBUG(F("LoadCredFile "));

      if (!file)
      {
        WG_LOGDEBUG(F("failed"));

        // Trying open redundant config file
        file = filesystem->open(CREDENTIALS_FILENAME_BACKUP, "r");
        
        WG_LOGDEBUG(F("LoadBkUpCredFile "));

        if (!file)
        {
          WG_LOGDEBUG(F("failed"));
          return false;
        }
      }
      
      // Find the longest pdata, then dynamically allocate buffer. Remember to free when done
      // This is used to store tempo data to calculate checksum to see of data is valid
      // We dont like to destroy myMenuItems[i].pdata with invalid data
      
      uint16_t maxBufferLength = 0;
      
      for (uint16_t i = 0; i < NUM_MENU_ITEMS; i++)
      {       
        if (myMenuItems[i].maxlen > maxBufferLength)
          maxBufferLength = myMenuItems[i].maxlen;
      }
      
      if (maxBufferLength > 0)
      {
        readBuffer = new char[ maxBufferLength + 1 ];
        
        // check to see NULL => stop and return false
        if (readBuffer == NULL)
        {
          WG_LOGERROR(F("ChkCrR: Error can't allocate buffer."));
          return false;
        }     
        else
        {
          WG_LOGDEBUG1(F("ChkCrR: Buffer allocated, Sz="), maxBufferLength + 1);
        }  
          
        uint16_t offset = 0;
        
        for (uint16_t i = 0; i < NUM_MENU_ITEMS; i++)
        {       
          uint8_t * _pointer = (uint8_t *) readBuffer;

          // Actual size of pdata is [maxlen + 1]
          memset(readBuffer, 0, myMenuItems[i].maxlen + 1);
          
          // Redundant, but to be sure correct position         
          file.seek(offset, SeekSet);
          file.read(_pointer, myMenuItems[i].maxlen);  
           
          offset += myMenuItems[i].maxlen;
       
          WG_LOGDEBUG3(F("ChkCrR:pdata="), readBuffer, F(",len="), myMenuItems[i].maxlen);         
                 
          for (uint16_t j = 0; j < myMenuItems[i].maxlen; j++,_pointer++)
          {         
            checkSum += *_pointer;  
          }       
        }

        file.read((uint8_t *) &readCheckSum, sizeof(readCheckSum));
        
        WG_LOGDEBUG(F("OK"));
        
        file.close();
        
        WG_LOGERROR3(F("CrCCsum=0x"), String(checkSum, HEX), F(",CrRCsum=0x"), String(readCheckSum, HEX));
        
        if (readBuffer != nullptr)
        {
          // Free buffer
          delete [] readBuffer;
          WG_LOGDEBUG(F("Buffer freed"));
        }
        
        if ( checkSum == readCheckSum)
        {
          return true;
        }
      }
      
      return false;
    }
    
    //////////////////////////////////////////////

    bool loadDynamicData()
    {
      int checkSum = 0;
      int readCheckSum;
      totalDataSize = sizeof(WIFI_GENERIC_config) + sizeof(readCheckSum);
      
      File file = filesystem->open(CREDENTIALS_FILENAME, "r");
      
      WG_LOGDEBUG(F("LoadCredFile "));

      if (!file)
      {
        WG_LOGDEBUG(F("failed"));

        // Trying open redundant config file
        file = filesystem->open(CREDENTIALS_FILENAME_BACKUP, "r");
        
        WG_LOGDEBUG(F("LoadBkUpCredFile "));

        if (!file)
        {
          WG_LOGDEBUG(F("failed"));
          return false;
        }
      }
     
      uint16_t offset = 0;
      
      for (uint16_t i = 0; i < NUM_MENU_ITEMS; i++)
      {       
        uint8_t * _pointer = (uint8_t *) myMenuItems[i].pdata;
        totalDataSize += myMenuItems[i].maxlen;

        // Actual size of pdata is [maxlen + 1]
        memset(myMenuItems[i].pdata, 0, myMenuItems[i].maxlen + 1);
        
        // Redundant, but to be sure correct position
        file.seek(offset, SeekSet);
        file.read(_pointer, myMenuItems[i].maxlen);
        
        offset += myMenuItems[i].maxlen;        
    
        WG_LOGDEBUG3(F("CrR:pdata="), myMenuItems[i].pdata, F(",len="), myMenuItems[i].maxlen);         
               
        for (uint16_t j = 0; j < myMenuItems[i].maxlen; j++,_pointer++)
        {         
          checkSum += *_pointer;  
        }       
      }

      file.read((uint8_t *) &readCheckSum, sizeof(readCheckSum));
      
      WG_LOGDEBUG(F("OK"));
      
      file.close();
      
      WG_LOGDEBUG3(F("CrCCsum=0x"), String(checkSum, HEX), F(",CrRCsum=0x"), String(readCheckSum, HEX));
      
      if ( checkSum != readCheckSum)
      {
        return false;
      }
      
      return true;    
    }
    
    //////////////////////////////////////////////

    void saveDynamicData()
    {
      int checkSum = 0;
    
      File file = filesystem->open(CREDENTIALS_FILENAME, "w");
      
      WG_LOGDEBUG(F("SaveCredFile "));

      uint16_t offset = 0;
      
      for (uint16_t i = 0; i < NUM_MENU_ITEMS; i++)
      {       
        uint8_t* _pointer = (uint8_t *) myMenuItems[i].pdata;
       
        WG_LOGDEBUG3(F("CW1:pdata="), myMenuItems[i].pdata, F(",len="), myMenuItems[i].maxlen);
        
        if (file)
        {
          // Redundant, but to be sure correct position
          file.seek(offset, SeekSet);
          file.write(_pointer, myMenuItems[i].maxlen); 
          
          offset += myMenuItems[i].maxlen;      
        }
        else
        {
          WG_LOGDEBUG(F("failed"));
        }        
                     
        for (uint16_t j = 0; j < myMenuItems[i].maxlen; j++,_pointer++)
        {         
          checkSum += *_pointer;     
         }
      }
      
      if (file)
      {
        file.write((uint8_t *) &checkSum, sizeof(checkSum));        
        file.close();
        
        WG_LOGDEBUG(F("OK"));    
      }
      else
      {
        WG_LOGDEBUG(F("failed"));
      }   
           
      WG_LOGDEBUG1(F("CrWCSum=0x"), String(checkSum, HEX));
      
      // Trying open redundant Auth file
      file = filesystem->open(CREDENTIALS_FILENAME_BACKUP, "w");
      
      WG_LOGDEBUG(F("SaveBkUpCredFile "));

      offset = 0;
      
      for (uint16_t i = 0; i < NUM_MENU_ITEMS; i++)
      {       
        uint8_t* _pointer = (uint8_t *) myMenuItems[i].pdata;
     
        WG_LOGDEBUG3(F("CW2:pdata="), myMenuItems[i].pdata, F(",len="), myMenuItems[i].maxlen);
        
        if (file)
        {
          file.seek(offset, SeekSet);
          file.write(_pointer, myMenuItems[i].maxlen); 
          
          // Redundant, but to be sure correct position
          offset += myMenuItems[i].maxlen; 
        }
        else
        {
          WG_LOGDEBUG(F("failed"));
        }        
                     
        for (uint16_t j = 0; j < myMenuItems[i].maxlen; j++,_pointer++)
        {         
          checkSum += *_pointer;     
         }
      }
      
      if (file)
      {
        file.write((uint8_t *) &checkSum, sizeof(checkSum));        
        file.close();
        
        WG_LOGDEBUG(F("OK"));    
      }
      else
      {
        WG_LOGDEBUG(F("failed"));
      }   
    }
#endif

    //////////////////////////////////////////////

    bool loadConfigData()
    {
      WG_LOGDEBUG(F("LoadCfgFile "));
      
      // file existed
      File file = filesystem->open(CONFIG_FILENAME, "r");
      
      if (!file)
      {
        WG_LOGDEBUG(F("failed"));

        // Trying open redundant config file
        file = filesystem->open(CONFIG_FILENAME_BACKUP, "r");
        
        WG_LOGDEBUG(F("LoadBkUpCfgFile "));

        if (!file)
        {
          WG_LOGDEBUG(F("failed"));
          return false;
        }
      }
     
      file.seek(0, SeekSet);
      file.read((uint8_t *) &WIFI_GENERIC_config, sizeof(WIFI_GENERIC_config));
      file.close();

      WG_LOGDEBUG(F("OK"));
      
      return isWiFiConfigValid();
    }
    
    //////////////////////////////////////////////

    void saveConfigData()
    {
      WG_LOGDEBUG(F("SaveCfgFile "));

      int calChecksum = calcChecksum();
      WIFI_GENERIC_config.checkSum = calChecksum;
      WG_LOGDEBUG1(F("WCSum=0x"), String(calChecksum, HEX));
      
      File file = filesystem->open(CONFIG_FILENAME, "w");

      if (file)
      {
        file.seek(0, SeekSet);
        file.write((uint8_t *) &WIFI_GENERIC_config, sizeof(WIFI_GENERIC_config));
        file.close();
        
        WG_LOGDEBUG(F("OK"));
      }
      else
      {
        WG_LOGDEBUG(F("failed"));
      }
      
      WG_LOGDEBUG(F("SaveBkUpCfgFile "));
      
      // Trying open redundant Auth file
      file = filesystem->open(CONFIG_FILENAME_BACKUP, "w");

      if (file)
      {
        file.seek(0, SeekSet);
        file.write((uint8_t *) &WIFI_GENERIC_config, sizeof(WIFI_GENERIC_config));
        file.close();
        
        WG_LOGDEBUG(F("OK"));
      }
      else
      {
        WG_LOGDEBUG(F("failed"));
      }
      
#if USE_DYNAMIC_PARAMETERS      
      saveDynamicData();
#endif

#if (USE_WIFI_NINA || USE_WIFI101)        
        wifiMulti.addAP(WIFI_GENERIC_config.WiFi_Creds[0].wifi_ssid, WIFI_GENERIC_config.WiFi_Creds[0].wifi_pw);
  			wifiMulti.addAP(WIFI_GENERIC_config.WiFi_Creds[1].wifi_ssid, WIFI_GENERIC_config.WiFi_Creds[1].wifi_pw);
#endif
    }

//////////////////////////////////////////////

#endif    // #if defined(ARDUINO_ARCH_MBED)

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
    
    bool isWiFiConfigValid()
    {
      #if REQUIRE_ONE_SET_SSID_PW
      // If SSID ="blank" or NULL, or PWD length < 8 (as required by standard) => return false
      // Only need 1 set of valid SSID/PWD
      if (!( ( ( strncmp(WIFI_GENERIC_config.WiFi_Creds[0].wifi_ssid, WM_NO_CONFIG, strlen(WM_NO_CONFIG)) && 
                 strlen(WIFI_GENERIC_config.WiFi_Creds[0].wifi_ssid) >  0 )  &&
             (   strlen(WIFI_GENERIC_config.WiFi_Creds[0].wifi_pw) >= PASSWORD_MIN_LEN ) ) ||
             ( ( strncmp(WIFI_GENERIC_config.WiFi_Creds[1].wifi_ssid, WM_NO_CONFIG, strlen(WM_NO_CONFIG)) && 
                 strlen(WIFI_GENERIC_config.WiFi_Creds[1].wifi_ssid) >  0 )  &&
               ( strlen(WIFI_GENERIC_config.WiFi_Creds[1].wifi_pw) >= PASSWORD_MIN_LEN ) ) ))
      #else
      // If SSID ="blank" or NULL, or PWD length < 8 (as required by standard) => invalid set
      // Need both sets of valid SSID/PWD
      if ( !strncmp(WIFI_GENERIC_config.WiFi_Creds[0].wifi_ssid,   WM_NO_CONFIG, strlen(WM_NO_CONFIG) )  ||
           !strncmp(WIFI_GENERIC_config.WiFi_Creds[0].wifi_pw,     WM_NO_CONFIG, strlen(WM_NO_CONFIG) )  ||
           !strncmp(WIFI_GENERIC_config.WiFi_Creds[1].wifi_ssid,   WM_NO_CONFIG, strlen(WM_NO_CONFIG) )  ||
           !strncmp(WIFI_GENERIC_config.WiFi_Creds[1].wifi_pw,     WM_NO_CONFIG, strlen(WM_NO_CONFIG) )  ||
           ( strlen(WIFI_GENERIC_config.WiFi_Creds[0].wifi_ssid) == 0 ) || 
           ( strlen(WIFI_GENERIC_config.WiFi_Creds[1].wifi_ssid) == 0 ) ||
           ( strlen(WIFI_GENERIC_config.WiFi_Creds[0].wifi_pw)   < PASSWORD_MIN_LEN ) ||
           ( strlen(WIFI_GENERIC_config.WiFi_Creds[1].wifi_pw)   < PASSWORD_MIN_LEN ) )
      #endif     
      {
        // If SSID, PW ="blank" or NULL, set the flag
        WG_LOGERROR(F("Invalid Stored WiFi Config Data"));
        
        // Nullify the invalid data to avoid displaying garbage
        memset(&WIFI_GENERIC_config, 0, sizeof(WIFI_GENERIC_config));
        
        hadConfigData = false;
        
        return false;
      }
      
      return true;
    }
    
    //////////////////////////////////////////////  

    
    //////////////////////////////////////////////
    
    void loadAndSaveDefaultConfigData()
    {
      // Load Default Config Data from Sketch
      memcpy(&WIFI_GENERIC_config, &defaultConfig, sizeof(WIFI_GENERIC_config));
      strcpy(WIFI_GENERIC_config.header, WIFI_GENERIC_BOARD_TYPE);
      
      // Including config and dynamic data, and assume valid
      saveConfigData();
          
      WG_LOGDEBUG(F("======= Start Loaded Config Data ======="));
      displayConfigData(WIFI_GENERIC_config);    
    }
    
    //////////////////////////////////////////////
    
    // Return false if init new EEPROM or SPIFFS. No more need trying to connect. Go directly to config mode
    bool getConfigData()
    {
      bool dynamicDataValid = true; 
      int calChecksum; 
      
      hadConfigData = false;
      
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
        // Load stored config data from LittleFS
        // Get config data. If "blank" or NULL, set false flag and exit
        if (!loadConfigData())
        {
          return false;
        }
        
        // Verify ChkSum        
        calChecksum = calcChecksum();

        WG_LOGERROR3(F("CCSum=0x"), String(calChecksum, HEX),
                   F(",RCSum=0x"), String(WIFI_GENERIC_config.checkSum, HEX));
        
#if USE_DYNAMIC_PARAMETERS        
        // Load stored dynamic data from LittleFS
        dynamicDataValid = checkDynamicData();
#endif
        
        // If checksum = 0 => LittleFS has been cleared (by uploading new FW, etc) => force to CP
        // If bad checksum = 0 => force to CP
        if ( (calChecksum != 0) && (calChecksum == WIFI_GENERIC_config.checkSum) )
        {       
          if (dynamicDataValid)
          {
  #if USE_DYNAMIC_PARAMETERS        
            loadDynamicData();
             
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
      else if ( !isWiFiConfigValid() )
      {
        // If SSID, PW ="blank" or NULL, stay in config mode forever until having config Data.
        return false;
      }
      else
      {
        displayConfigData(WIFI_GENERIC_config);
      }

      return true;
    }
        
    //////////////////////////////////////////////
    
#if (USE_WIFI_NINA || USE_WIFI101)  
    
    bool connectMultiWiFi(int retry_time)
    {
			// For general board, this better be 1000 to enable connect the 1st time
			#define WIFI_MULTI_1ST_CONNECT_WAITING_MS             1000L

			#define WIFI_MULTI_CONNECT_WAITING_MS                   500L

			WG_LOGDEBUG("No WiFi. Trying to scan and reconnect");

			WiFi.disconnect();

			int i = 0;

			uint8_t status = wifiMulti.run();

			delay(WIFI_MULTI_1ST_CONNECT_WAITING_MS);

			while ( ( i++ < (retry_time * 5) ) && ( status != WL_CONNECTED ) )
			{
				status = WiFi.status();

				if ( status == WL_CONNECTED )
				  break;
				else
				  delay(WIFI_MULTI_CONNECT_WAITING_MS);
			}

			if ( status == WL_CONNECTED )
			{
				WG_LOGERROR1(F("WiFi connected after time: "), i);
				WG_LOGERROR3(F("SSID:"), WiFi.SSID(), F(",RSSI="), WiFi.RSSI());

		#if (defined(ESP32) || defined(ESP8266))
				WG_LOGERROR3(F("Channel:"), WiFi.channel(), F(",IP address:"), WiFi.localIP() );
		#else
				WG_LOGERROR1(F("IP address:"), WiFi.localIP() );
		#endif
			}
			else
			{
				WG_LOGERROR(F("WiFi not connected"));

				if (wifiMulti.run() != WL_CONNECTED)
				{
				  Serial.println("WiFi not connected!");
				  delay(1000);
				}
			}

			return (status == WL_CONNECTED);
    }

#else
    
    //////////////////////////////////////////////

// Max times to try WiFi per loop() iteration. To avoid blocking issue in loop()
// Default 1 and minimum 1.
#if !defined(MAX_NUM_WIFI_RECON_TRIES_PER_LOOP)      
  #define MAX_NUM_WIFI_RECON_TRIES_PER_LOOP     1
#else
  #if (MAX_NUM_WIFI_RECON_TRIES_PER_LOOP < 1)  
    #define MAX_NUM_WIFI_RECON_TRIES_PER_LOOP     1
  #endif
#endif

    // New connection logic from v1.2.0
    bool connectMultiWiFi(int retry_time)
    {
      int sleep_time  = 250;
      int index       = 0;
      int new_index   = 0;
      uint8_t status  = WL_IDLE_STATUS;
                       
      static int lastConnectedIndex = 255;

      WG_LOGDEBUG(F("ConMultiWifi"));
      
      if (static_IP != IPAddress(0, 0, 0, 0))
      {
        WG_LOGDEBUG(F("UseStatIP"));
        WiFi.config(static_IP);
      }
      
      if (lastConnectedIndex != 255)
      {
        //  Successive connection, index = ??
        // Checking if new_index is OK
        new_index = (lastConnectedIndex + 1) % NUM_WIFI_CREDENTIALS;
        
        if ( strlen(WIFI_GENERIC_config.WiFi_Creds[new_index].wifi_pw) >= PASSWORD_MIN_LEN )
        {    
          index = new_index;
          WG_LOGDEBUG3(F("Using index="), index, F(", lastConnectedIndex="), lastConnectedIndex);
        }
        else
        {
          WG_LOGERROR3(F("Ignore invalid WiFi PW : index="), new_index, F(", PW="), WIFI_GENERIC_config.WiFi_Creds[new_index].wifi_pw);
          
          // Using the previous valid index
          index = lastConnectedIndex;
        }
      }
      else
      {
        //  First connection ever, index = 0
        if ( strlen(WIFI_GENERIC_config.WiFi_Creds[0].wifi_pw) >= PASSWORD_MIN_LEN )
        {    
          WG_LOGDEBUG(F("First connection, Using index=0"));
        }
        else
        {
          WG_LOGERROR3(F("Ignore invalid WiFi PW : index=0, SSID="), WIFI_GENERIC_config.WiFi_Creds[0].wifi_ssid,
                       F(", PWD="), WIFI_GENERIC_config.WiFi_Creds[0].wifi_pw);
          
          // Using the next valid index
          index = 1;
        }
      } 
         
      WG_LOGERROR3(F("con2WF:SSID="), WIFI_GENERIC_config.WiFi_Creds[index].wifi_ssid,
                   F(",PW="), WIFI_GENERIC_config.WiFi_Creds[index].wifi_pw);
      
      uint8_t numIndexTried = 0;
      
      uint8_t numWiFiReconTries = 0;
     
      while ( !wifi_connected && (numIndexTried++ < NUM_WIFI_CREDENTIALS) && (numWiFiReconTries++ < MAX_NUM_WIFI_RECON_TRIES_PER_LOOP) )
      {         
        while ( 0 < retry_time )
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
        
        if (status == WL_CONNECTED)
        {         
          break;
        }
        else
        {        
          if (retry_time <= 0)
          {      
            WG_LOGERROR3(F("Failed using index="), index, F(", retry_time="), retry_time);
            retry_time = RETRY_TIMES_CONNECT_WIFI;  
          }
          
          new_index = (index + 1) % NUM_WIFI_CREDENTIALS;
          
          // only use new index if valid (len >= PASSWORD_MIN_LEN = 8)
          if ( strlen(WIFI_GENERIC_config.WiFi_Creds[new_index].wifi_pw) >= PASSWORD_MIN_LEN )
          {
            index = new_index;
          }
          
          //WiFi.end();
        }
      }

      if (wifi_connected)
      {
        WG_LOGERROR(F("con2WF:OK"));
        
        WG_LOGERROR1(F("IP="), WiFi.localIP() );
        
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

#endif
   
    //////////////////////////////////////////////
    
    // NEW
    void createHTML(String& root_html_template)
    {
      String pitem;
      
      root_html_template  = WIFI_GENERIC_HTML_HEAD_START;
      
  #if USING_CUSTOMS_STYLE
      // Using Customs style when not NULL
      if (WIFI_GENERIC_HTML_HEAD_CUSTOMS_STYLE)
        root_html_template  += WIFI_GENERIC_HTML_HEAD_CUSTOMS_STYLE;
      else
        root_html_template  += WIFI_GENERIC_HTML_HEAD_STYLE;
  #else     
      root_html_template  += WIFI_GENERIC_HTML_HEAD_STYLE;
  #endif
      
  #if USING_CUSTOMS_HEAD_ELEMENT
      if (_CustomsHeadElement)
        root_html_template += _CustomsHeadElement;
  #endif          
      
#if SCAN_WIFI_NETWORKS
      WG_LOGDEBUG1(WiFiNetworksFound, F(" SSIDs found, generating HTML now"));
      // Replace HTML <input...> with <select...>, based on WiFi network scan in startConfigurationMode()

      ListOfSSIDs = "";

      for (int i = 0, list_items = 0; (i < WiFiNetworksFound) && (list_items < MAX_SSID_IN_LIST); i++)
      {
        if (indices[i] == -1) 
          continue; 		// skip duplicates and those that are below the required quality
          
        ListOfSSIDs += WIFI_GENERIC_OPTION_START + String(WiFi.SSID(indices[i])) + WIFI_GENERIC_OPTION_END;	
        list_items++;		// Count number of suitable, distinct SSIDs to be included in list
      }

      WG_LOGDEBUG(ListOfSSIDs);

      if (ListOfSSIDs == "")		// No SSID found or none was good enough
        ListOfSSIDs = WIFI_GENERIC_OPTION_START + String(WIFI_GENERIC_NO_NETWORKS_FOUND) + WIFI_GENERIC_OPTION_END;

      pitem = String(WIFI_GENERIC_HTML_HEAD_END);

#if MANUAL_SSID_INPUT_ALLOWED
      pitem.replace("[[input_id]]",  "<input id='id' list='SSIDs'>"  + String(WIFI_GENERIC_DATALIST_START) + "'SSIDs'>" + ListOfSSIDs + WIFI_GENERIC_DATALIST_END);
      WG_LOGDEBUG1(F("pitem:"), pitem);
      pitem.replace("[[input_id1]]", "<input id='id1' list='SSIDs'>" + String(WIFI_GENERIC_DATALIST_START) + "'SSIDs'>" + ListOfSSIDs + WIFI_GENERIC_DATALIST_END);
      
      WG_LOGDEBUG1(F("pitem:"), pitem);

#else
      pitem.replace("[[input_id]]",  "<select id='id'>"  + ListOfSSIDs + WIFI_GENERIC_SELECT_END);
      pitem.replace("[[input_id1]]", "<select id='id1'>" + ListOfSSIDs + WIFI_GENERIC_SELECT_END);
#endif

      root_html_template += pitem + WIFI_GENERIC_FLDSET_START;

#else

      pitem = String(WIFI_GENERIC_HTML_HEAD_END);
      pitem.replace("[[input_id]]",  WIFI_GENERIC_HTML_INPUT_ID);
      pitem.replace("[[input_id1]]", WIFI_GENERIC_HTML_INPUT_ID1);
      root_html_template += pitem + WIFI_GENERIC_FLDSET_START;

#endif    // SCAN_WIFI_NETWORKS

#if USE_DYNAMIC_PARAMETERS      
      for (uint16_t i = 0; i < NUM_MENU_ITEMS; i++)
      {
        pitem = String(WIFI_GENERIC_HTML_PARAM);

        pitem.replace("{b}", myMenuItems[i].displayName);
        pitem.replace("{v}", myMenuItems[i].id);
        pitem.replace("{i}", myMenuItems[i].id);
        
        root_html_template += pitem;
      }
#endif
      
      root_html_template += String(WIFI_GENERIC_FLDSET_END) + WIFI_GENERIC_HTML_BUTTON + WIFI_GENERIC_HTML_SCRIPT;     

#if USE_DYNAMIC_PARAMETERS      
      for (uint16_t i = 0; i < NUM_MENU_ITEMS; i++)
      {
        pitem = String(WIFI_GENERIC_HTML_SCRIPT_ITEM);
        
        pitem.replace("{d}", myMenuItems[i].id);
        
        root_html_template += pitem;
      }
#endif
      
      root_html_template += String(WIFI_GENERIC_HTML_SCRIPT_END) + WIFI_GENERIC_HTML_END;
      
      return;     
    }
       
    //////////////////////////////////////////////

    void serverSendHeaders()
    {
      WG_LOGDEBUG3(F("serverSendHeaders:WM_HTTP_CACHE_CONTROL:"), WM_HTTP_CACHE_CONTROL, "=", WM_HTTP_NO_STORE);
      server->sendHeader(WM_HTTP_CACHE_CONTROL, WM_HTTP_NO_STORE);
      
#if USING_CORS_FEATURE
      // New from v1.1.0, for configure CORS Header, default to WM_HTTP_CORS_ALLOW_ALL = "*"
      WG_LOGDEBUG3(F("serverSendHeaders:WM_HTTP_CORS:"), WM_HTTP_CORS, " : ", _CORS_Header);
      server->sendHeader(WM_HTTP_CORS, _CORS_Header);
#endif
     
      WG_LOGDEBUG3(F("serverSendHeaders:WM_HTTP_PRAGMA:"), WM_HTTP_PRAGMA, " : ", WM_HTTP_NO_CACHE);
      server->sendHeader(WM_HTTP_PRAGMA, WM_HTTP_NO_CACHE);
      
      WG_LOGDEBUG3(F("serverSendHeaders:WM_HTTP_EXPIRES:"), WM_HTTP_EXPIRES, " : ", "-1");
      server->sendHeader(WM_HTTP_EXPIRES, "-1");
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
          // New from v1.1.0         
          serverSendHeaders();        
          //////
          
          String result;
          createHTML(result);

          // Reset configTimeout to stay here until finished.
          configTimeout = 0;

          if ( RFC952_hostname[0] != 0 )
          {
            // Replace only if Hostname is valid
            result.replace("RP2040_WM_Lite", RFC952_hostname);
          }
          else if ( WIFI_GENERIC_config.board_name[0] != 0 )
          {
            // Or replace only if board_name is valid.  Otherwise, keep intact
            result.replace("RP2040_WM_Lite", WIFI_GENERIC_config.board_name);
          }

          if (hadConfigData)
          {
            result.replace("[[id]]",     WIFI_GENERIC_config.WiFi_Creds[0].wifi_ssid);
            result.replace("[[pw]]",     WIFI_GENERIC_config.WiFi_Creds[0].wifi_pw);
            result.replace("[[id1]]",    WIFI_GENERIC_config.WiFi_Creds[1].wifi_ssid);
            result.replace("[[pw1]]",    WIFI_GENERIC_config.WiFi_Creds[1].wifi_pw);
            
#if USING_BOARD_NAME            
            result.replace("[[nm]]",     WIFI_GENERIC_config.board_name);
#endif            
          }
          else
          {
            result.replace("[[id]]",  "");
            result.replace("[[pw]]",  "");
            result.replace("[[id1]]", "");
            result.replace("[[pw1]]", "");
            
#if USING_BOARD_NAME            
            result.replace("[[nm]]",  "");
#endif            
          }
          
#if USE_DYNAMIC_PARAMETERS          
          for (uint16_t i = 0; i < NUM_MENU_ITEMS; i++)
          {
            String toChange = String("[[") + myMenuItems[i].id + "]]";
            result.replace(toChange, myMenuItems[i].pdata);
          }
#endif


          WG_LOGDEBUG1(F("h:HTML page size:"), result.length());
          WG_LOGDEBUG1(F("h:HTML="), result);
          
          server->send(200, WM_HTTP_HEAD_TEXT_HTML, result);

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
            
            WG_LOGDEBUG1(F("h: Init menuItemUpdated :" ), NUM_MENU_ITEMS);                    
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
       
#if USING_BOARD_NAME         
        static bool nm_Updated  = false;
#endif
          
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
#if USING_BOARD_NAME        
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
#endif

        
#if USE_DYNAMIC_PARAMETERS 
        else
        {       
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
                
              break;  
            }
          }
        }
#endif
        
        WG_LOGDEBUG1(F("h:items updated ="), number_items_Updated);
        WG_LOGDEBUG3(F("h:key ="), key, ", value =", value);

        server->send(200, WM_HTTP_HEAD_TEXT_HTML, "OK");

#if USE_DYNAMIC_PARAMETERS        
        if (number_items_Updated == NUM_CONFIGURABLE_ITEMS + NUM_MENU_ITEMS)
#else
        if (number_items_Updated == NUM_CONFIGURABLE_ITEMS)
#endif 
        {
          WG_LOGERROR(F("h:UpdLittleFS"));

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
#if SCAN_WIFI_NETWORKS
	    configTimeout = 0;  // To allow user input in CP
	    
	    WiFiNetworksFound = scanWifiNetworks(&indices);	
#endif    
    
#if USING_CONFIG_MODE_LED
      // turn the LED_BUILTIN ON to tell us we enter configuration mode.
      digitalWrite(CONFIG_MODE_LED, LED_ON);
#endif
    
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
    
#if SCAN_WIFI_NETWORKS

	  // Source code adapted from https://github.com/khoih-prog/ESP_WiFiManager/blob/master/src/ESP_WiFiManager-Impl.h

    int           _paramsCount            = 0;
    int           _minimumQuality         = -1;
    bool          _removeDuplicateAPs     = true;
	
	  //////////////////////////////////////////
    
    void swap(int *thisOne, int *thatOne)
    {
       int tempo;

       tempo    = *thatOne;
       *thatOne = *thisOne;
       *thisOne = tempo;
    }

    //////////////////////////////////////////
	
	  void setMinimumSignalQuality(const int& quality)
	  {
	    _minimumQuality = quality;
	  }

	  //////////////////////////////////////////

	  //if this is true, remove duplicate Access Points - default true
	  void setRemoveDuplicateAPs(const bool& removeDuplicates)
	  {
	    _removeDuplicateAPs = removeDuplicates;
	  }

	  //////////////////////////////////////////

	  //Scan for WiFiNetworks in range and sort by signal strength
	  //space for indices array allocated on the heap and should be freed when no longer required  
	  int scanWifiNetworks(int **indicesptr)
	  {
	    WG_LOGDEBUG(F("Scanning Network"));

	    int n = WiFi.scanNetworks();

	    WG_LOGDEBUG1(F("scanWifiNetworks: Done, Scanned Networks n = "), n); 

	    //KH, Terrible bug here. WiFi.scanNetworks() returns n < 0 => malloc( negative == very big ) => crash!!!
	    //In .../esp32/libraries/WiFi/src/WiFiType.h
	    //#define WIFI_SCAN_RUNNING   (-1)
	    //#define WIFI_SCAN_FAILED    (-2)
	    //if (n == 0)
	    if (n <= 0)
	    {
		    WG_LOGDEBUG(F("No network found"));
		    return (0);
	    }
	    else
	    {
		    // Allocate space off the heap for indices array.
		    // This space should be freed when no longer required.
		    int* indices = (int *)malloc(n * sizeof(int));

		    if (indices == NULL)
		    {
		      WG_LOGDEBUG(F("ERROR: Out of memory"));
		      *indicesptr = NULL;
		      return (0);
		    }

		    *indicesptr = indices;
	       
		    //sort networks
		    for (int i = 0; i < n; i++)
		    {
		      indices[i] = i;
		    }

		    WG_LOGDEBUG(F("Sorting"));

		    // RSSI SORT
		    // old sort
		    for (int i = 0; i < n; i++)
		    {
		      for (int j = i + 1; j < n; j++)
		      {
			      if (WiFi.RSSI(indices[j]) > WiFi.RSSI(indices[i]))
			      {
                    //std::swap(indices[i], indices[j]);
                    // Using locally defined swap()
                    swap(&indices[i], &indices[j]);
       			}
		      }
		    }

		    WG_LOGDEBUG(F("Removing Dup"));

		    // remove duplicates ( must be RSSI sorted )
		    if (_removeDuplicateAPs)
		    {
		      String cssid;
		      
		      for (int i = 0; i < n; i++)
		      {
			      if (indices[i] == -1)
			        continue;

			      cssid = WiFi.SSID(indices[i]);
			      
			      for (int j = i + 1; j < n; j++)
			      {
			        if (cssid == WiFi.SSID(indices[j]))
			        {
				        WG_LOGDEBUG1("DUP AP:", WiFi.SSID(indices[j]));
				        indices[j] = -1; // set dup aps to index -1
			        }
			      }
		      }
		    }

		    for (int i = 0; i < n; i++)
		    {
		      if (indices[i] == -1)
			      continue; // skip dups

		      int quality = getRSSIasQuality(WiFi.RSSI(indices[i]));

		      if (!(_minimumQuality == -1 || _minimumQuality < quality))
		      {
			      indices[i] = -1;
			      WG_LOGDEBUG(F("Skipping low quality"));
		      }
		    }

		    WG_LOGDEBUG(F("WiFi networks found:"));
		    
		    for (int i = 0; i < n; i++)
		    {
		      if (indices[i] == -1)
			      continue; // skip dups
		      else
			      WG_LOGDEBUG5(i+1,": ",WiFi.SSID(indices[i]), ", ", WiFi.RSSI(i), "dB");
		    }

		    return (n);
	    }
	  }

	  //////////////////////////////////////////

	  int getRSSIasQuality(const int& RSSI)
	  {
	    int quality = 0;

	    if (RSSI <= -100)
	    {
		    quality = 0;
	    }
	    else if (RSSI >= -50)
	    {
		    quality = 100;
	    }
	    else
	    {
		    quality = 2 * (RSSI + 100);
	    }

	    return quality;
	  }

  //////////////////////////////////////////

#endif	       
};


#endif    //WiFiManager_Generic_Lite_RP2040_h
