#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>
#include <WiFiClient.h>;
#include <ThingSpeak.h>;
String apiKey = "9XAKUKAPT7LXD1D2";  //masukkan apikey pada thingspeak   
#define FIREBASE_HOST "https://tesph-a1a95-default-rtdb.firebaseio.com/"  //=> firebase
#define FIREBASE_AUTH "Wwqe5LTe8WdkMQNy2K7gMhT4YtmMaUJYS2nicFSk"
#define WIFI_SSID "Galaxy A12C872"
#define WIFI_PASSWORD "rkor5371"

WiFiClient client;
const char* server = "api.thingspeak.com";  //server yang digunakan
unsigned long myChannelNumber = 1407205;   //masukkan id chanel
const char * myWriteAPIKey = "9XAKUKAPT7LXD1D2"; //masukkan apikey 

FirebaseData firebaseData;
SoftwareSerial mcu(D5,D6);
static float pHValue;

void setup(){
 mcu.begin(9600);
 Serial.begin(9600);
 WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();
  ThingSpeak.begin(client);
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
}
void loop()
{
  mcu.write("mcu");
  if(mcu.available()>0) 
  {
//    Serial.print("Voltage:");
//        Serial.print(voltage,2);
    pHValue = mcu.read();
    Serial.print("    pH value: ");
    Serial.println(pHValue);
    Firebase.setFloat(firebaseData, "/PhValue",pHValue);
//     ThingSpeak.writeField(myChannelNumber, 1,voltage, myWriteAPIKey);

     ThingSpeak.writeField(myChannelNumber, 2,pHValue, myWriteAPIKey);
    delay(100);
  }
}
