
#define BLYNK_TEMPLATE_ID "TMPL3S4kSHAXj"
#define BLYNK_TEMPLATE_NAME "SMART IRRIGATION"
#define BLYNK_AUTH_TOKEN "It72TZOHLLB2oHJjQGGrLjQ_QMQEHpZT"

#include <WiFi.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>

// --- WiFi ---
char ssid[] = "GROUP16";
char pass[] = "987654321";

// Pins
#define DHTPIN 4
#define DHTTYPE DHT22
#define SOIL_PIN 34
#define RELAY_PIN 26
#define LCD_ADDR 0x27

// Blynk Pins
#define VPIN_SOIL   V0
#define VPIN_TEMP   V1
#define VPIN_HUM    V2
#define VPIN_MANUAL V3

// Objects
DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(LCD_ADDR, 16, 2);
BlynkTimer timer;

// Variables
bool manualPumpOn = false;
bool autoPumpOn = false;
int pumpThreshold = 40;
bool pumpState = false;

// Control Pump Function (Active LOW Logic)
void controlPump() {
  if (manualPumpOn || autoPumpOn) {
    digitalWrite(RELAY_PIN, LOW);   // ON (Active LOW)
    pumpState = true;
    Serial.println("Pump ON");
  } else {
    digitalWrite(RELAY_PIN, HIGH);  // OFF
    pumpState = false;
    Serial.println("Pump OFF");
  }
}

// Manual Pump Control from Blynk
BLYNK_WRITE(VPIN_MANUAL) {
  manualPumpOn = param.asInt();
  controlPump();
}

// Sensor Logic and LCD Display
void sensorLogic() {
  float t = dht.readTemperature();
  float h = dht.readHumidity();
  int soilVal = analogRead(SOIL_PIN);
  int soilPercent = map(soilVal, 4095, 0, 0, 100);

  if (!manualPumpOn && soilPercent < pumpThreshold) {
    autoPumpOn = true;
  } else {
    autoPumpOn = false;
  }

  controlPump();

  // Send data to Blynk
  Blynk.virtualWrite(VPIN_TEMP, t);
  Blynk.virtualWrite(VPIN_HUM, h);
  Blynk.virtualWrite(VPIN_SOIL, soilPercent);

  // Update LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("T:");
  lcd.print(t, 1);
  lcd.print((char)223);
  lcd.print("C H:");
  lcd.print((int)h);
  lcd.print("%");

  lcd.setCursor(0, 1);
  lcd.print("Soil:");
  lcd.print(soilPercent);
  lcd.print("% ");

  if (manualPumpOn) {
    lcd.print("P:MAN");
  } else if (autoPumpOn) {
    lcd.print("P:AUTO");
  } else {
    lcd.print("P:OFF");
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, HIGH); // OFF at boot (Active LOW)

  dht.begin();
  lcd.init();
  lcd.backlight();

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  timer.setInterval(5000L, sensorLogic);
}

void loop() {
  Blynk.run();
  timer.run();
}
