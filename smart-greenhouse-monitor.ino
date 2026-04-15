#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SHT21.h>

// =====================================================
// LCD & SENSOR INITIALIZATION
// =====================================================
LiquidCrystal_I2C lcd(0x27, 16, 2);
SHT21 sht;

// =====================================================
// CALIBRATION VALUES (SOIL MOISTURE)
// =====================================================
const int soilMoistLevelLow = 2610;   // Dry soil value
const int soilMoistLevelHigh = 930;   // Wet soil value

// =====================================================
// GLOBAL VARIABLES
// =====================================================
float temp;
float humidity;

// =====================================================
// SETUP FUNCTION
// =====================================================
void setup() {
  int tasterPin = 15;

  // Initialize LCD
  lcd.init();
  lcd.backlight();

  // Initialize I2C communication
  Wire.begin();

  // Configure pins
  pinMode(32, INPUT);   // Soil moisture sensor
  pinMode(15, INPUT);   // Button
 

  // Start serial communication
  Serial.begin(115200);
}

// =====================================================
// MAIN LOOP
// =====================================================
void loop() {

  // -----------------------------------------------------
  // SENSOR READINGS
  // -----------------------------------------------------
  int soilMoist = analogRead(32);
  temp = sht.getTemperature();
  humidity = sht.getHumidity();

  // -----------------------------------------------------
  // SERIAL OUTPUT (DEBUGGING)
  // -----------------------------------------------------
  Serial.print("Analog Value: ");
  Serial.print(soilMoist);
  Serial.print("Temp: ");
  Serial.print(temp);
  Serial.print("\t Humidity: ");
  Serial.println(humidity);

  // Convert soil moisture to percentage
  int percentSoilMoist = map(soilMoist, soilMoistLevelHigh, soilMoistLevelLow, 100, 0);

  Serial.print("\t");
  Serial.print(percentSoilMoist);
  Serial.println(" %");

  delay(100);

  // -----------------------------------------------------
  // LCD DISPLAY OUTPUT
  // -----------------------------------------------------

  // Soil moisture
  lcd.setCursor(0, 0);
  lcd.print("Bodenfeuchte:  ");
  lcd.setCursor(14, 0);
  lcd.print(percentSoilMoist);
  lcd.setCursor(17, 0);
  lcd.print("%");

  // Air humidity
  lcd.setCursor(0, 1);
  lcd.print("Luftfeuchte:  ");
  lcd.setCursor(14, 1);
  lcd.print(humidity);
  lcd.setCursor(19, 1);
  lcd.print("%");

  // Temperature
  lcd.setCursor(0, 2);
  lcd.print("Temperatur:  ");
  lcd.setCursor(14, 2);
  lcd.print(temp);
  lcd.setCursor(19, 2);

  // -----------------------------------------------------
  // BUTTON CONTROL (LCD BACKLIGHT)
  // -----------------------------------------------------
  if (digitalRead(15) == HIGH) {
    lcd.backlight();
    Serial.print("HIGH");
  } else {
    lcd.noBacklight();
  }

  delay(1000);
}
