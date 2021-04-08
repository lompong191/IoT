#include <TridentTD_LineNotify.h>
#include "DHT.h"

#define DHTPIN D2
#define DHTTYPE DHT11
#define SSID        "Tokyo-2.4G"
#define PASSWORD    "1234567890"
#define LINE_TOKEN  "QKBiOILAfVJNQ029TkvA0A5wuj6j2O2crOCtKELvjhw"

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200); Serial.println();
  Serial.println(LINE.getVersion());
  
  WiFi.begin(SSID, PASSWORD);
  Serial.printf("WiFi connecting to %s\n",  SSID);
  while(WiFi.status() != WL_CONNECTED) { Serial.print("."); delay(400); }
  Serial.printf("\nWiFi connected\nIP : ");
  Serial.println(WiFi.localIP());  

  // กำหนด Line Token
  LINE.setToken(LINE_TOKEN);
  
  LINE.notify("เชื่อมต่อ Line สำเร็จ");
}

void loop() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  if (t >= 31) {
    LINE.notify("ร้อนมาก " + String(t) + " องศา");
  }
  Serial.println("อุณหภูมิ : " + String(t) + ", ความชื้น : " + String(h));
  delay(10000);
}
