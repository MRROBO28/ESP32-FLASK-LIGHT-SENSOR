#include <WiFi.h>
#include <HTTPClient.h>

// Ganti dengan SSID dan Password WiFi Anda
const char* ssid = "Infinix NOTE 30";
const char* password = "irshadfaqih";

// Ganti dengan URL server Flask Anda
const char* serverName = "http://192.168.35.68:5000/sensor";


void setup() {
  Serial.begin(115200);
  pinMode(34, INPUT); // Pin sensor cahaya
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  
  Serial.println("Connected to WiFi");
}

void loop() {
    int sensorValue = analogRead(34);
    int newval = map(sensorValue,4095,0,0,100);
    Serial.println(newval);delay(100);

    if (WiFi.status() == WL_CONNECTED) {
      HTTPClient http;
      http.begin(serverName);
      http.addHeader("Content-Type", "application/x-www-form-urlencoded");

      String httpRequestData = "type=light&value=" + String(newval);
      int httpResponseCode = http.POST(httpRequestData);

      if (httpResponseCode > 0) {
        String response = http.getString();
        Serial.println(httpResponseCode);
        Serial.println(response);
      } else {
        Serial.print("Error on sending POST: ");
        Serial.println(httpResponseCode);
      }

      http.end();
    } else {
      Serial.println("Error in WiFi connection");
    }
}
