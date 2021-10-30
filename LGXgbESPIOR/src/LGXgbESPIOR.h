/*
  LGXgbESPIOR.h - Library for Legaxus-Gibbon ESPIOR
  Created by Samuel Lim Sep 2021.
  Released for Elliance System ONLY.
*/

#ifndef LGXgbESPIOR_h
#define LGXgbESPIOR_h
#endif

#include <Arduino.h>
#include <Adafruit_MCP23008.h>
#include <WiFi.h>
#include <ETH.h>
#include <HTTPClient.h>
#include <Wire.h>
#include <ThingsBoard.h>
#include <ModbusRTU.h>
#include <Adafruit_ADS1X15.h>

#define RXD2 16
#define TXD2 17

#define redLED 12
#define ENABLE_ETH 14

#define LGX_HEADER "lgx"
#define LGX_SN "es160921"

bool gbGPSvalid();
float gbLaTconvert();
float gbLoNconvert();
void Error_Flag(int num);
String gbPrint_GpsDATA(int toPrint);
void gbParse_GpsDATA();
String gbModbusGPSdecode(String tempRMC, bool PrintGPSdata, int toPrint);
void gbGPSinit();
String gbDecToAscii(int numArray, uint16_t decNum[]);
String gbDecToHex(int numArray, int decNum);
String gbHexToAscii(String hex);
void gbIOinit();
void gbETHenable(char static_ip[], char static_gw[], char static_sn[], char static_dns[]);
void gbWiFienable(const char* ssid, const char* pwd);
void WiFiEvent(WiFiEvent_t event);
void gbOUT(int rly, bool status);
bool gbIN(int opto);
bool gbTGconnect(char TGmqtt_server[], char TGapi_token[], int TGport);
void gbTGsendTelemetryInt(char TGtopic[], int INTvalue); 
void gbTGsendTelemetryFloat(char TGtopic[], float FLOATvalue);
String getChipId();
String get_device_status(String device_id_status);
bool gbTGconnected();
bool cb(Modbus::ResultCode event, uint16_t transactionId, void* data);
void gbMBinit();
void gbMBreadHreg(uint8_t s_id, uint16_t firstREG, uint16_t* REG, uint16_t REGcount);
bool gbMBslave();
void gbMBtask();
bool gbCheckOnline();
String gbADCgetV(int adcVchannel);
int gbADCgetI(int adcIchannel);
void gbLED(bool status);