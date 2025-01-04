#include <WiFi.h>
#include <WebServer.h>

// Wi-Fi credentials
const char* ssid = "SIT-IIoT";
const char* password = "Sit1To#Down!9";

WebServer server(8010);

const int ONBOARD_LED1 = 18;
const int ONBOARD_LED2 = 19;

bool led1Status = false;
bool led2Status = false;

void setup() {
  Serial.begin(115200);

  pinMode(ONBOARD_LED1, OUTPUT);
  pinMode(ONBOARD_LED2, OUTPUT);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi Connected");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  server.on("/1/on", HTTP_GET, []() {
    digitalWrite(ONBOARD_LED1, HIGH);
    led1Status = true;
    server.send(200, "text/plain", "LED 1 turned ON");
  });

  server.on("/1/off", HTTP_GET, []() {
    digitalWrite(ONBOARD_LED1, LOW);
    led1Status = false;
    server.send(200, "text/plain", "LED 1 turned OFF");
  });

  server.on("/2/on", HTTP_GET, []() {
    digitalWrite(ONBOARD_LED2, HIGH);
    led2Status = true;
    server.send(200, "text/plain", "LED 2 turned ON");
  });

  server.on("/2/off", HTTP_GET, []() {
    digitalWrite(ONBOARD_LED2, LOW);
    led2Status = false;
    server.send(200, "text/plain", "LED 2 turned OFF");
  });

  server.on("/1/status", HTTP_GET, []() {
    char response[50];
    snprintf(response, sizeof(response), "{ \"switch\": \"%s\" }", led1Status ? "on" : "off");
    server.send(200, "application/json", response);
  });

  server.on("/2/status", HTTP_GET, []() {
    char response[50];
    snprintf(response, sizeof(response), "{ \"switch\": \"%s\" }", led2Status ? "on" : "off");
    server.send(200, "application/json", response);
  });

  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}
