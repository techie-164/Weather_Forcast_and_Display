#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define DHTPIN 4
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Pressure array (example forecasted values)
float pressureVals[] = {1002, 1001, 1003, 1004, 1002};
int pressureIndex = 0;

unsigned long lastSwitch = 0;
const long interval = 5000;
int displayMode = 0; // 0: Temp, 1: Humidity, 2: Pressure
unsigned long timestamp = 0;

void setup() {
  Serial.begin(115200);
  dht.begin();

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("OLED init failed"));
    while (true);
  }

  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("Starting...");
  display.display();
  delay(2000);

  Serial.println("Time(s),Temperature(C),Humidity(%),Pressure(hPa)");
}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - lastSwitch >= interval) {
    lastSwitch = currentMillis;
    timestamp += 5;

    float temp = dht.readTemperature();
    float hum = dht.readHumidity();
    float pressure = pressureVals[pressureIndex];

    display.clearDisplay();
    display.setCursor(0, 0);
    display.setTextSize(2);

    switch (displayMode) {
      case 0:
        if (isnan(temp)) {
          display.println("Temp Err");
        } else {
          display.print("Temp: ");
          display.print(temp);
          display.println(" C");
        }
        break;

      case 1:
        if (isnan(hum)) {
          display.println("Hum Err");
        } else {
          display.print("Hum: ");
          display.print(hum);
          display.println(" %");
        }
        break;

      case 2:
        display.print("Pres: ");
        display.print(pressure);
        display.println(" hPa");
        pressureIndex = (pressureIndex + 1) % (sizeof(pressureVals) / sizeof(pressureVals[0]));
        break;
    }

    display.display();
    displayMode = (displayMode + 1) % 3;

    // Print to Serial Monitor with timestamp
    Serial.print(timestamp);
    Serial.print(",");
    Serial.print(isnan(temp) ? -1 : temp);
    Serial.print(",");
    Serial.print(isnan(hum) ? -1 : hum);
    Serial.print(",");
    Serial.println(pressure);
  }
}