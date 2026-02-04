/*********** BLYNK CONFIG ***********/
#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "template_id"
#define BLYNK_TEMPLATE_NAME "template_name"
#define BLYNK_AUTH_TOKEN "auth_token"

/*********** LIBRARIES ***********/
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>
#include <LiquidCrystal_I2C.h>

/*********** WIFI ***********/
char ssid[] = "wifi_name";
char pass[] = "wifi_password";

/*********** PIN DEFINITIONS ***********/
#define DHTPIN 4
#define DHTTYPE DHT22
#define MQ135_PIN 34        // MUST be ADC pin on ESP32

/*********** OBJECTS ***********/
DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2);
BlynkTimer timer;

/*********** MQ135 CALIBRATION ***********/
int baseline = 1900;   // Measure this in clean air

/*********** FUNCTIONS ***********/
float calculateDewPoint(float t, float h) {
  return t - ((100 - h) / 5);
}

String getAirStatus(int mqValue) {
  if (mqValue <= baseline + 200) {
    return "GOOD";
  } 
  else if (mqValue <= baseline + 600) {
    return "MODERATE";
  } 
  else {
    return "POLLUTED";
  }
}

int calculateAQI(int mqValue) {
  int aqi = map(mqValue, baseline, baseline + 1000, 50, 300);
  return constrain(aqi, 0, 500);
}

/*********** MAIN SENSOR TASK ***********/
void sendSensorData() {

  // ---- DHT22 ----
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("DHT read failed");
    return;
  }

  float heatIndex = dht.computeHeatIndex(temperature, humidity, false);
  float dewPoint  = calculateDewPoint(temperature, humidity);

  // ---- MQ135 (Averaged for stability) ----
  int mqSum = 0;
  for (int i = 0; i < 5; i++) {
    mqSum += analogRead(MQ135_PIN);
    delay(50);
  }
  int mqValue = mqSum / 5;

  int aqi = calculateAQI(mqValue);
  String airStatus = getAirStatus(mqValue);

  // ---- SERIAL ----
    // ---- SERIAL ----
  Serial.print("Temp: "); Serial.print(temperature); Serial.print(" °C | ");
  Serial.print("Hum: "); Serial.print(humidity); Serial.print(" % | ");
  Serial.print("DewPt: "); Serial.print(dewPoint); Serial.print(" °C | ");
  Serial.print("HeatIdx: "); Serial.print(heatIndex); Serial.print(" °C | ");
  Serial.print("MQ135: "); Serial.print(mqValue); Serial.print(" | ");
  Serial.print("AQI: "); Serial.print(aqi); Serial.print(" | ");
  Serial.print("Status: "); Serial.println(airStatus);

  


  // ---- LCD ----
  lcd.clear();


  lcd.setCursor(0, 0);
  lcd.print("T:");
  lcd.print(temperature, 1);
  lcd.print("C AQI:");
  lcd.print(aqi);

  
  lcd.setCursor(0, 1);
  lcd.print("H:");
  lcd.print(humidity, 0);
  lcd.print("% ");
  lcd.print(airStatus);


  // ---- BLYNK ----
  Blynk.virtualWrite(V0, temperature);
  Blynk.virtualWrite(V1, humidity);
  Blynk.virtualWrite(V2, airStatus);
  Blynk.virtualWrite(V3, heatIndex);
  Blynk.virtualWrite(V4, dewPoint);
  Blynk.virtualWrite(V5, aqi);

  
}

/*********** SETUP ***********/
void setup() {
  Serial.begin(9600);

  lcd.init();
  lcd.backlight();

  dht.begin();

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  timer.setInterval(3000L, sendSensorData);
}

/*********** LOOP ***********/
void loop() {
  Blynk.run();
  timer.run();
}
