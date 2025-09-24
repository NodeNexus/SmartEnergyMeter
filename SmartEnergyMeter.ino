#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>

#define CURRENT_SENSOR_PIN 34  // Analog pin for ACS712
#define VOLTAGE_SENSOR_PIN 35  // Analog pin for voltage divider

const char* ssid = "ESP32-AccessPoint";
const char* password = "12345678";

AsyncWebServer server(80);

float readCurrent() {
  int raw = analogRead(CURRENT_SENSOR_PIN);
  float current = (raw - 2048) * (30.0 / 2048.0); // ACS712 30A model
  return current;
}

float readVoltage() {
  int raw = analogRead(VOLTAGE_SENSOR_PIN);
  float voltage = raw * (230.0 / 4095.0); // Adjust depending on voltage divider
  return voltage;
}

void setup() {
  Serial.begin(115200);

  WiFi.softAP(ssid, password);
  Serial.println("Access Point Started");
  Serial.println(WiFi.softAPIP());

  // Serve web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", webpage);
  });

  server.on("/data", HTTP_GET, [](AsyncWebServerRequest *request){
    float current = readCurrent();
    float voltage = readVoltage();
    float power = current * voltage;

    StaticJsonDocument<200> doc;
    doc["current"] = current;
    doc["voltage"] = voltage;
    doc["power"] = power;

    String json;
    serializeJson(doc, json);
    request->send(200, "application/json", json);
  });

  server.begin();
}

void loop() {
  // Nothing here, handled by async server
}

const char webpage[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
<meta name="viewport" content="width=device-width, initial-scale=1">
<title>Smart Energy Meter</title>
<style>
body { font-family: Arial; text-align: center; background-color: #111; color: #0f0; }
h1 { margin-bottom: 20px; }
div.data { font-size: 24px; margin: 15px; }
</style>
</head>
<body>
<h1>Smart Energy Meter Dashboard</h1>
<div class="data">Current: <span id="current">0</span> A</div>
<div class="data">Voltage: <span id="voltage">0</span> V</div>
<div class="data">Power: <span id="power">0</span> W</div>

<script>
function fetchData() {
  fetch('/data')
  .then(response => response.json())
  .then(data => {
    document.getElementById('current').innerText = data.current.toFixed(2);
    document.getElementById('voltage').innerText = data.voltage.toFixed(2);
    document.getElementById('power').innerText = data.power.toFixed(2);
  });
}
setInterval(fetchData, 1000);
fetchData();
</script>
</body>
</html>
)rawliteral";
