/****************************************************************************************************************************
  ESPAsync_WiFiManager_Debug.h
  For ESP8266 / ESP32 boards

  ESPAsync_WiFiManager is a library for the ESP8266/Arduino platform, using (ESP)AsyncWebServer to enable easy
  configuration and reconfiguration of WiFi credentials using a Captive Portal.

  Modified from 
  1. Tzapu               (https://github.com/tzapu/WiFiManager)
  2. Ken Taylor          (https://github.com/kentaylor)
  3. Alan Steremberg     (https://github.com/alanswx/ESPAsyncWiFiManager)
  4. Khoi Hoang          (https://github.com/khoih-prog/ESP_WiFiManager)

  Built by Khoi Hoang https://github.com/khoih-prog/ESPAsync_WiFiManager
  Licensed under MIT license
  
  Version: 1.9.3

  Version Modified By  Date      Comments
  ------- -----------  ---------- -----------
  1.0.11  K Hoang      21/08/2020 Initial coding to use (ESP)AsyncWebServer instead of (ESP8266)WebServer. Bump up to v1.0.11
                                  to sync with ESP_WiFiManager v1.0.11
  1.1.1   K Hoang      29/08/2020 Add MultiWiFi feature to autoconnect to best WiFi at runtime to sync with
                                  ESP_WiFiManager v1.1.1. Add setCORSHeader function to allow flexible CORS
  1.1.2   K Hoang      17/09/2020 Fix bug in examples.
  1.2.0   K Hoang      15/10/2020 Restore cpp code besides Impl.h code to use if linker error. Fix bug.
  1.3.0   K Hoang      04/12/2020 Add LittleFS support to ESP32 using LITTLEFS Library
  1.4.0   K Hoang      18/12/2020 Fix staticIP not saved. Add functions. Add complex examples.
  1.4.1   K Hoang      21/12/2020 Fix bug and compiler warnings.
  1.4.2   K Hoang      21/12/2020 Fix examples' bug not using saved WiFi Credentials after losing all WiFi connections.
  1.4.3   K Hoang      23/12/2020 Fix examples' bug not saving Static IP in certain cases.
  1.5.0   K Hoang      13/02/2021 Add support to new ESP32-S2. Optimize code.
  1.6.0   K Hoang      25/02/2021 Fix WiFi Scanning bug.
  1.6.1   K Hoang      26/03/2021 Modify multiWiFi-related timings to work better with latest esp32 core v1.0.6
  1.6.2   K Hoang      08/04/2021 Fix example misleading messages.
  1.6.3   K Hoang      13/04/2021 Allow captive portal to run more than once by closing dnsServer.
  1.7.0   K Hoang      20/04/2021 Add support to new ESP32-C3 using SPIFFS or EEPROM
  1.7.1   K Hoang      25/04/2021 Fix MultiWiFi bug. Fix captive-portal bug if CP AP address is not default 192.168.4.1
  1.8.0   K Hoang      30/04/2021 Set _timezoneName. Add support to new ESP32-S2 (METRO_ESP32S2, FUNHOUSE_ESP32S2, etc.)
  1.8.1   K Hoang      06/05/2021 Fix bug. Don't display invalid time when not synch yet.
  1.9.0   K Hoang      08/05/2021 Add WiFi /scan page. Fix timezoneName not displayed in Info page. Clean up.
  1.9.1   K Hoang      18/05/2021 Fix warnings with ESP8266 core v3.0.0
  1.9.2   K Hoang      02/08/2021 Fix Mbed TLS compile error and MultiWiFi connection issue with ESP32 core v2.0.0-rc1+
  1.9.3   K Hoang      13/08/2021 Add WiFi scanning of hidden SSIDs
 *****************************************************************************************************************************/

#pragma once

#ifndef ESPAsync_WiFiManager_Debug_H
#define ESPAsync_WiFiManager_Debug_H

#ifdef ESPASYNC_WIFIMGR_DEBUG_PORT
  #define DBG_PORT_ESP_WM      ESPASYNC_WIFIMGR_DEBUG_PORT
#else
  #include <Arduino.h>
  #define DBG_PORT_ESP_WM      Serial
#endif

// Change _ESPASYNC_WIFIMGR_LOGLEVEL_ to set tracing and logging verbosity
// 0: DISABLED: no logging
// 1: ERROR: errors
// 2: WARN: errors and warnings
// 3: INFO: errors, warnings and informational (default)
// 4: DEBUG: errors, warnings, informational and debug

#ifndef _ESPASYNC_WIFIMGR_LOGLEVEL_
  #define _ESPASYNC_WIFIMGR_LOGLEVEL_       4
#endif

/////////////////////////////////////////////////////////

const char ESP_WM_MARK[] = "[WM] ";
const char ESP_WM_SP[]   = " ";

#define ESP_WM_PRINT        DBG_PORT_ESP_WM.print
#define ESP_WM_PRINTLN      DBG_PORT_ESP_WM.println

#define ESP_WM_PRINT_MARK   ESP_WM_PRINT(ESP_WM_MARK)
#define ESP_WM_PRINT_SP     ESP_WM_PRINT(ESP_WM_SP)

/////////////////////////////////////////////////////////

#define LOGERROR(x)         if(_ESPASYNC_WIFIMGR_LOGLEVEL_>0) { ESP_WM_PRINT_MARK; ESP_WM_PRINTLN(x); }
#define LOGERROR0(x)        if(_ESPASYNC_WIFIMGR_LOGLEVEL_>0) { ESP_WM_PRINT(x); }
#define LOGERROR1(x,y)      if(_ESPASYNC_WIFIMGR_LOGLEVEL_>0) { ESP_WM_PRINT_MARK; ESP_WM_PRINT(x); ESP_WM_PRINT_SP; ESP_WM_PRINTLN(y); }
#define LOGERROR2(x,y,z)    if(_ESPASYNC_WIFIMGR_LOGLEVEL_>0) { ESP_WM_PRINT_MARK; ESP_WM_PRINT(x); ESP_WM_PRINT_SP; ESP_WM_PRINT(y); ESP_WM_PRINT_SP;  ESP_WM_PRINTLN(z); }
#define LOGERROR3(x,y,z,w)  if(_ESPASYNC_WIFIMGR_LOGLEVEL_>0) { ESP_WM_PRINT_MARK; ESP_WM_PRINT(x); ESP_WM_PRINT_SP; ESP_WM_PRINT(y); ESP_WM_PRINT_SP; ESP_WM_PRINT(z); ESP_WM_PRINT_SP; ESP_WM_PRINTLN(w); }

/////////////////////////////////////////////////////////

#define LOGWARN(x)          if(_ESPASYNC_WIFIMGR_LOGLEVEL_>1) { ESP_WM_PRINT_MARK; ESP_WM_PRINTLN(x); }
#define LOGWARN0(x)         if(_ESPASYNC_WIFIMGR_LOGLEVEL_>1) { ESP_WM_PRINT(x); }
#define LOGWARN1(x,y)       if(_ESPASYNC_WIFIMGR_LOGLEVEL_>1) { ESP_WM_PRINT_MARK; ESP_WM_PRINT(x); ESP_WM_PRINT_SP; ESP_WM_PRINTLN(y); }
#define LOGWARN2(x,y,z)     if(_ESPASYNC_WIFIMGR_LOGLEVEL_>1) { ESP_WM_PRINT_MARK; ESP_WM_PRINT(x); ESP_WM_PRINT_SP; ESP_WM_PRINT(y); ESP_WM_PRINT_SP;  ESP_WM_PRINTLN(z); }
#define LOGWARN3(x,y,z,w)   if(_ESPASYNC_WIFIMGR_LOGLEVEL_>1) { ESP_WM_PRINT_MARK; ESP_WM_PRINT(x); ESP_WM_PRINT_SP; ESP_WM_PRINT(y); ESP_WM_PRINT_SP; ESP_WM_PRINT(z); ESP_WM_PRINT_SP; ESP_WM_PRINTLN(w); }

/////////////////////////////////////////////////////////

#define LOGINFO(x)          if(_ESPASYNC_WIFIMGR_LOGLEVEL_>2) { ESP_WM_PRINT_MARK; ESP_WM_PRINTLN(x); }
#define LOGINFO0(x)         if(_ESPASYNC_WIFIMGR_LOGLEVEL_>2) { ESP_WM_PRINT(x); }
#define LOGINFO1(x,y)       if(_ESPASYNC_WIFIMGR_LOGLEVEL_>2) { ESP_WM_PRINT_MARK; ESP_WM_PRINT(x); ESP_WM_PRINT_SP; ESP_WM_PRINTLN(y); }
#define LOGINFO2(x,y,z)     if(_ESPASYNC_WIFIMGR_LOGLEVEL_>2) { ESP_WM_PRINT_MARK; ESP_WM_PRINT(x); ESP_WM_PRINT_SP; ESP_WM_PRINT(y); ESP_WM_PRINT_SP; ESP_WM_PRINTLN(z); }
#define LOGINFO3(x,y,z,w)   if(_ESPASYNC_WIFIMGR_LOGLEVEL_>2) { ESP_WM_PRINT_MARK; ESP_WM_PRINT(x); ESP_WM_PRINT_SP; ESP_WM_PRINT(y); ESP_WM_PRINT_SP; ESP_WM_PRINT(z); ESP_WM_PRINT_SP; ESP_WM_PRINTLN(w); }

/////////////////////////////////////////////////////////

#define LOGDEBUG(x)         if(_ESPASYNC_WIFIMGR_LOGLEVEL_>3) { ESP_WM_PRINT_MARK; ESP_WM_PRINTLN(x); }
#define LOGDEBUG0(x)        if(_ESPASYNC_WIFIMGR_LOGLEVEL_>3) { ESP_WM_PRINT(x); }
#define LOGDEBUG1(x,y)      if(_ESPASYNC_WIFIMGR_LOGLEVEL_>3) { ESP_WM_PRINT_MARK; ESP_WM_PRINT(x); ESP_WM_PRINT_SP; ESP_WM_PRINTLN(y); }
#define LOGDEBUG2(x,y,z)    if(_ESPASYNC_WIFIMGR_LOGLEVEL_>3) { ESP_WM_PRINT_MARK; ESP_WM_PRINT(x); ESP_WM_PRINT_SP; ESP_WM_PRINT(y); ESP_WM_PRINT_SP; ESP_WM_PRINTLN(z); }
#define LOGDEBUG3(x,y,z,w)  if(_ESPASYNC_WIFIMGR_LOGLEVEL_>3) { ESP_WM_PRINT_MARK; ESP_WM_PRINT(x); ESP_WM_PRINT_SP; ESP_WM_PRINT(y); ESP_WM_PRINT_SP; ESP_WM_PRINT(z); ESP_WM_PRINT_SP; ESP_WM_PRINTLN(w); }

/////////////////////////////////////////////////////////

#endif    // ESPAsync_WiFiManager_Debug_H

