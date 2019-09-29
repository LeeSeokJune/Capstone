#include <WiFi.h>
#include <OneWire.h>
#include <DallasTemperature.h>


String apiKey = "41GWC7X6NBNAYEPF";
const char* server = "api.thingspeak.com";
const char* ssid = "lsj";  // AP SSID
const char* password = "bembem18"; // AP password
const int oneWireBus = 4;

OneWire oneWire(oneWireBus);
DallasTemperature sensors(&oneWire);
float temp = 0;

void setup() {
  Serial.begin(115200);
  sensors.begin();
  Serial.printf("start start   \r\n");

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("\nConnecting to WiFi : ");
  Serial.print(ssid);
  
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(100);
  }

  Serial.println("WIFI connected");

}
void loop() {

  sensors.requestTemperatures();
  temp = sensors.getTempCByIndex(0);
  Serial.println("\nmy room temperature :");
  Serial.println(temp);
  
  if(client.connect(server, 80)&&temp!=85&&temp!=-127)
  {
    String sendData = apiKey + "&field2=" + temp + "\r\n\r\n";

    client.print("POST /update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("X-THINGSPEAKAPIKEY: " + apiKey + "\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(sendData.length());
    client.print("\n\n");
    client.print(sendData);

    Serial.print("\nTemperature: ");
    Serial.print(temp);

  }

  client.stop();

  Serial.println("Sending...");

  delay(60000);//wait 1 minute
}
