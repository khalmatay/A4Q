#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
#define SCREEN_ADDRESS 0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET, 18, 19);

#define MQ9_PIN 34
#define MQ135_PIN 35

void setup() {
  Serial.begin(9600);
  while (!Serial);

  pinMode(MQ9_PIN, INPUT);
  pinMode(MQ135_PIN, INPUT);

  // Initialize the OLED display
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }
  display.display();
  delay(500);
  display.clearDisplay();
}

void loop() {
  float mq9Value = analogRead(MQ9_PIN);
  float mq135Value = analogRead(MQ135_PIN);

  // Convert analog readings to voltage
  float mq9Voltage = mq9Value * (5.0 / 1023.0);
  float mq135Voltage = mq135Value * (5.0 / 1023.0);

  // Calculate gas concentrations using sensor curves
  float mq9PPM = mq9Value * (10000.0 / 1023.0); // MQ-9 carbon monoxide gas
  float mq135PPM = mq135Value * (10000.0 / 1023.0); // MQ-135 air quality

  // Display data on OLED
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.print("MQ-9 PPM: ");
  display.println(mq9PPM);
  display.print("MQ-135 PPM: ");
  display.println(mq135PPM);
  display.display();

  // Print data to Serial Monitor
  Serial.print("MQ-9 PPM: ");
  Serial.println(mq9PPM);
  Serial.print("MQ-135 PPM: ");
  Serial.println(mq135PPM);

  delay(500); // Adjust as needed
}
