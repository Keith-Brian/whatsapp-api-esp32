#include<WiFi.h>
#include <HTTPClient.h>
#include <UrlEncode.h>

#include<AHT10.h>
#include<Wire.h>


AHT10 aht;


float temp, humi;


#define WIFI_SSID "Sierra"
#define WIFI_PASS "Sierra@13"

String apiKey = "8408457"; //8408457 //2209090
String mobileNumber = "254113268646";            //254702333332

WiFiClient Client;

void setup() {

  Serial.begin(9600);
  aht.begin();

  WiFi.mode(WIFI_STA);
  
  Serial.print("Connecting...");
  WiFi.begin(WIFI_SSID,WIFI_PASS);

  while(WiFi.status() != WL_CONNECTED){
    Serial.print("...");
    delay(500);
    }

    Serial.println();
    Serial.println("Connected!");

    sendWhatsapp("Hey I'm working:-");

}

void loop() {
  
  temp = aht.readTemperature();
  humi = aht.readHumidity();

  Serial.println("The temperature of the cow is: " +String(temp) +" and humidity is: "+ String(humi));

  sendWhatsapp("The temperature of the cow is: " +String(temp) +" and humidity is: "+ String(humi));
  //delay(10000);
  //sendWhatsapp("The humidity of the cow is: " +String(humi));

  delay(30000);

}


void sendWhatsapp(String message){
  
  String url = "https://api.callmebot.com/whatsapp.php?phone=" + mobileNumber + "&apikey=" + apiKey + "&text=" + urlEncode(message); 
  HTTPClient http;
  http.begin(url);

  http.addHeader("Content-Type", "application/x-www-form-urlencoded");

  int responseCode = http.POST(url);
  if(responseCode ==200){
    Serial.println();
    Serial.println("DM sent successfully!");
    }else{
      Serial.print("Error sending the message: ");
      Serial.println(responseCode);
      }
      
  http.end();
  }
