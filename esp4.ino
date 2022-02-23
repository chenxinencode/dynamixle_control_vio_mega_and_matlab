#include <ESP8266WiFi.h>
#include <Arduino.h>
#include <Wire.h>


//const char *ssid = "3x513";
//const char *password = "862234463";
//const char *ssid = "iPhone";
//const char *password = "11111111";

const char *ssid = "Cornetto";
const char *password = "qwertyuiop.";

int timeout=20;

boolean DEBUG=false;
WiFiServer server(8888);

void setup()
{
    Serial.begin(115200);
    //Serial.printf("Connecting to %s ", ssid);
    WiFi.begin(ssid, password);

   while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        //Serial.print(".");
    }
    //Serial.println(" connected"); 
    server.begin();
   //Serial.printf("Web server started, open %s in a web browser\n", WiFi.localIP().toString().c_str());
   while(Serial.read()>=0){}//清除串口
}

void loop()
{
 server.begin();  
 while (WiFi.status() == WL_CONNECTED)
 {      
    WiFiClient clientpc = server.available(); //尝试建立客户对象
    clientpc.setTimeout(1);
    while (clientpc.connected()) //如果客户端建立连接
    { 
        String response="";
        long int time=millis();
         while ((time+timeout) > millis())
         {
          while(clientpc.available()) {
            // The esp has data so display its output to the serial window
            char c=clientpc.read(); // read the next character.
            response += c;
            } 
      
          if(response.charAt(response.length()-2)=='，'&&response.charAt(response.length()-1)=='；'){
            time=0;
          }
          }

          
        Serial.print(response);
      
        String serial_to_esp_to_pc = "";
        //String pc_to_esp_to_serial = "";
//        pc_to_esp_to_serial =clientpc.read();
//        Serial.print(pc_to_esp_to_serial);//这里对mega请求数据

        //mega-->esp
        //serial_to_esp_to_pc = Serial.readString();
    
        //esp-->pc
        //clientpc.write(serial_to_esp_to_pc.c_str());
        clientpc.print(response);
      //clientpc.print(pc_to_esp_to_serial);
       //Serial.flush();
       //clientpc.flush();
    }

  
          
}
}
