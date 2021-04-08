#include <DHT.h>
#include <ESP8266WiFi.h>

String apiKey = "OG0QXO0CT2CSZJ6Q"; // thingspeak API key ที่ได้จากการสร้างของผู้ใช้
const char* ssid = "Tokyo-2.4G"; // กรอก ssid ที่ปล่อยสัญญาณ Wi-Fi
const char* password = "1234567890"; //กรอก รหัสผ่านสัญญาณ Wi-Fi
const char* server = "api.thingspeak.com";
#define DHTPIN D2
#define DHTTYPE DHT11 // DHT11 if useDHT11
DHT dht(DHTPIN, DHTTYPE);
WiFiClient client;

void setup() {
  Serial.begin(115200);
  delay(10);
  dht.begin();
  WiFi.begin(ssid, password);
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
}
void loop() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  if (client.connect(server,80)) {
    String url = "/update?api_key="+ apiKey;
    url += "&field1=" + (String)t;
    url += "&field2=" + (String)h;
    client.print(String("GET ") + url + " HTTP/1.1\r\n" +
    "Host: " + server + "\r\n" +
    "Connection: close\r\n\r\n");
    Serial.print("Temp: ");
    Serial.print(t);
    Serial.print(" *C and Humidity: ");
    Serial.print(h);
    Serial.println("% ");
  }
  client.stop();
  Serial.print("Waiting...");
  delay(15000); // thingspeak needs minimum 15 sec delay between updates
}
