#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

float temp = 0.0, hum = 0.0, pres = 0.0;
bool dataReceived = false;
int displayMode = 0;  // 0: Temp, 1: Hum, 2: Pressure
unsigned long lastSwitchTime = 0;
const unsigned long interval = 5000;

void setup() {
  Serial.begin(115200);
  delay(2000);  // Allow Serial to initialize

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    while (true); // OLED failed
  }

  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("Waiting...");
  display.display();
}

void loop() {
  // Receive serial data from Python
  if (Serial.available()) {
    String line = Serial.readStringUntil('\n');
    line.trim();

    int tIndex = line.indexOf(',');
    int hIndex = line.indexOf(',', tIndex + 1);

    if (tIndex > 0 && hIndex > tIndex) {
      temp = line.substring(0, tIndex).toFloat();
      hum = line.substring(tIndex + 1, hIndex).toFloat();
      pres = line.substring(hIndex + 1).toFloat();
      dataReceived = true;
    }
  }

  // Cycle to display every 5s
  if (dataReceived && millis() - lastSwitchTime >= interval) {
    lastSwitchTime = millis();
    display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(0, 0);

    switch (displayMode) {
      case 0:
        display.println("Forecast Temp (C):");
        display.setTextSize(3);
        display.setCursor(0, 20);
        display.println(temp, 1);
        break;
      case 1:
        display.println("Forecast Humidity (%):");
        display.setTextSize(3);
        display.setCursor(0, 20);
        display.println(hum, 1);
        break;
      case 2:
        display.println("Forecast Pressure:");
        display.setTextSize(2);
        display.setCursor(0, 20);
        display.println(pres, 1);
        break;
    }

    display.display();
    displayMode = (displayMode + 1) % 3;  // 0 → 1 → 2 → 0 ...
  }
}