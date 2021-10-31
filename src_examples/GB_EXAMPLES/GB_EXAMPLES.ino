#include <LGXgbESPIOR.h>

// Modbus parameter defination
#define SLAVE_ID 1
#define FIRST_REG 5
#define REG_COUNT 35

//define your default values here
char mqtt_server[40] = "iot.technogine.com";
int mqtt_port = 1883;
char api_token[32] = "zQQ7wv2CNVKN3uoYxmLT";

//default custom WiFi credential
const char* WIFI_SSID = "ESPIOR";
const char* WIFI_PASSWORD = "1234567890";

//default custom static IP
char static_ip[16] = "192.168.100.242";
char static_gw[16] = "192.168.100.1";
char static_sn[16] = "255.255.255.0";
char static_dns[16] = "192.168.100.1";

bool output_test = false;

void setup() 
{
  Serial.begin(9600);
  gbIOinit();
  gbMBinit();
  gbGPSinit();
  //delay(3000);
  gbWiFienable(WIFI_SSID, WIFI_PASSWORD);
  //gbETHenable(static_ip, static_gw, static_sn, static_dns); 
}

void loop() 
{
  if (!output_test)
  {
    for (int x = 1;x < 9;x++)
    {
      gbOUT(x,1);  // gbOUT(Relay number, status)
      delay(1000);
    }
    
   output_test = true;
  }
  
  Serial.println(gbIN(1));
    
    while (!gbTGconnected()) 
    {
      Serial.print("Connecting to Technogine node ...");
      Serial.println();
      //Serial.println(mqtt_server);
      //Serial.print(api_token);
      //Serial.println();
    
      // Attempt to connect (clientId, username, password)
      if ( gbTGconnect(mqtt_server, api_token, mqtt_port) ) 
      {
        Serial.println( "[DONE]" );
      }  
      else 
      {
        Serial.print( "[FAILED]" );
        Serial.println( " : retrying in 5 seconds" );
        // Wait 5 seconds before retrying
        delay( 5000 );
      }
    }
  
  // ------ MODBUS ------
  uint16_t res[REG_COUNT];
  float s_temp;
  float s_humi;
  
  if (!gbMBslave())
  {
    gbLED(true);
    gbMBreadHreg(SLAVE_ID, FIRST_REG, res, REG_COUNT);
    while (gbMBslave())
    {
      gbMBtask();
      delay(10);
    }
    Serial.println();

    //Serial.println(gbDecToAscii(REG_COUNT,res));
    Serial.println(gbModbusGPSdecode(gbDecToAscii(REG_COUNT,res),0,0));
    if (gbGPSvalid())
    {
      Serial.println(gbLaTconvert(),5);
      Serial.println(gbLoNconvert(),5);
    }
    else
    {
      Serial.println("No GPS!");
    }
    
    /*s_temp = (float)res[0]/10;
    s_humi = (float)res[1]/10;
    Serial.print("Soil Moisture-> ");
    Serial.print(res[0]);
    Serial.println(" ");

    Serial.print("Soil Temperature-> ");
    Serial.print(res[1]);
    Serial.println(" ");

    Serial.print("EC-> ");
    Serial.print(res[2]);
    Serial.println(" ");

    Serial.print("PH-> ");
    Serial.print(res[3]);
    Serial.println(" ");

    Serial.print("N-> ");
    Serial.print(res[4]);
    Serial.println(" ");

    Serial.print("P-> ");
    Serial.print(res[5]);
    Serial.println(" ");

    Serial.print("K-> ");
    Serial.print(res[6]);
    Serial.println(" ");*/

    //gbTGsendTelemetryInt("Data 0", res[0]);
    //gbTGsendTelemetryFloat("Soil temperature", res[0]/10);
    //Serial.println(s_temp);
    //Serial.println(s_humi);
    //gbTGsendTelemetryInt("Data 1", res[1]);
    //gbTGsendTelemetryFloat("Soil humidity", res[1]/10);
    gbLED(false);
  }
  delay(1000);
}
