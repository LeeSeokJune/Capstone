#include <WiFi.h>


String apiKey = "41GWC7X6NBNAYEPF";
const char* server = "api.thingspeak.com";
const char* ssid = "lsj";  // AP SSID
const char* password = "bembem18"; // AP password

const int httpPort = 80;
// Mapo Gu
//www.kma.go.kr/wid/queryDFSRSS.jsp?zone=11440506000
const String KMA_url = "/wid/queryDFSRSS.jsp?zone=1144060000";

const char* SERVER = "www.kma.go.kr";


void setup() {
  Serial.begin(115200);
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
  int i = 0;
  String tmp_str;
  String wt_temp;

  Serial.println("connecting to");
  Serial.println(SERVER);

  WiFiClient client;
  
  if (!client.connect(SERVER, 80)) {
    Serial.println("connection failed");
    return;
  }
  client.print(String("GET ") + KMA_url + " HTTP/1.1\r\n" +
                 "Host: " + SERVER + "\r\n" +
                 "Connection: close\r\n\r\n");
    delay(100);
    while (client.available()) {
      i++;
      String line = client.readStringUntil('\n');
      int temp = line.indexOf("</temp>");
      
      if(temp>0)
      {
        String tmp_str="<temp>";
        wt_temp = line.substring(line.indexOf(tmp_str) + tmp_str.length(),temp);
        Serial.println("\nvalue is : ");
        Serial.println(wt_temp);
        break;
      }
      
      
    }
  
  if(client.connect(server, 80))
  {
    String sendData = apiKey + "&field1=" + wt_temp + "\r\n\r\n";

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
    Serial.print(wt_temp);
    Serial.println("deg C. Connecting to Thingspeak..");

  }

  client.stop();

  Serial.println("Sending...");

  delay(60000);//wait 1 minute
}
