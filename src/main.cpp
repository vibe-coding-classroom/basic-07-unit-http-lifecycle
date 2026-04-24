#include <Arduino.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>

// --- Configuration ---
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";

AsyncWebServer server(80);

void setup() {
    Serial.begin(115200);

    // WiFi Connection
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Connecting to WiFi...");
    }
    Serial.println("Connected to WiFi");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());

    // --- API Routes ---

    // Task 2: RESTful API - GET /api/status
    server.on("/api/status", HTTP_GET, [](AsyncWebServerRequest *request) {
        StaticJsonDocument<200> doc;
        doc["free_heap"] = ESP.getFreeHeap();
        doc["uptime"] = millis() / 1000;
        doc["status"] = "running";

        String response;
        serializeJson(doc, response);
        
        // Task 3: Connection Header Control (Default is Keep-Alive in AsyncWebServer)
        // You can manually set headers to test "Connection: close"
        AsyncWebServerResponse *res = request->beginResponse(200, "application/json", response);
        // res->addHeader("Connection", "close"); 
        request->send(res);
    });

    // Task 2: RESTful API - POST /api/command
    server.on("/api/command", HTTP_POST, [](AsyncWebServerRequest *request) {
        // Body parsing is handled via onBody if needed, 
        // but for simple commands we can use request->getParam or similar.
    }, NULL, [](AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total) {
        // Handle POST body
        StaticJsonDocument<200> doc;
        DeserializationError error = deserializeJson(doc, data, len);

        if (error) {
            request->send(400, "application/json", "{\"error\":\"Invalid JSON\"}");
            return;
        }

        const char* command = doc["command"];
        Serial.printf("Received command: %s\n", command);
        
        request->send(200, "application/json", "{\"status\":\"success\"}");
    });

    server.begin();
}

void loop() {
    // AsyncWebServer handles requests in the background
}
