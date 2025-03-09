#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

#define DHTPIN 2        // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11   // DHT 11
#define PIR_PIN 5       // Digital pin connected to the PIR sensor
#define BUZZER_PIN 4    // Digital pin connected to the buzzer

/* 1. Define the WiFi credentials */
#define WIFI_SSID "Darasimi"
#define WIFI_PASSWORD "dotun003"

// For the following credentials, see examples/Authentications/SignInAsUser/EmailPassword/EmailPassword.ino

/* 2. Define the API Key */
#define API_KEY "AIzaSyDNgjcUjvwB14Aeex8feCmmswvs6zZ4gfs"

/* 3. Define the RTDB URL */
#define DATABASE_URL "haztech-3041d-default-rtdb.firebaseio.com"

/* 4. Define the user Email and password that already registered or added in your project */
#define USER_EMAIL "Qasim.adebisik@gmail.com"
#define USER_PASSWORD "Qasim9937"

// Define Firebase Data object
FirebaseData fbdo;

FirebaseAuth auth;
FirebaseConfig config;

unsigned long sendDataPrevMillis = 0;

unsigned long count = 0;
DHT dht(DHTPIN, DHTTYPE);

void setup()
{
  Serial.begin(115200);
  dht.begin();
  pinMode(PIR_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);  // Initialize buzzer pin
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  // Explicitly set A0 as an input
  pinMode(A0, INPUT);  // Flame Sensor Pin
  pinMode(16, INPUT);  // Water Sensor Pin

  Serial.printf("Firebase Client v%s\n\n", FIREBASE_CLIENT_VERSION);

  /* Assign the api key (required) */
  config.api_key = API_KEY;

  /* Assign the user sign in credentials */
  auth.user.email = USER_EMAIL;
  auth.user.password = USER_PASSWORD;

  /* Assign the RTDB URL (required) */
  config.database_url = DATABASE_URL;

  /* Assign the callback function for the long running token generation task */
  config.token_status_callback = tokenStatusCallback; // see addons/TokenHelper.h

  Firebase.begin(&config, &auth);

  // Comment or pass false value when WiFi reconnection will control by your code or third-party library
  Firebase.reconnectWiFi(true);

  Firebase.setDoubleDigits(5);
}

void loop()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  // Read the flame sensor value
  int flameSensorValue = analogRead(A0);

  // Read the water sensor value
  int waterSensorValue = digitalRead(16);

  // Read the PIR sensor value
  int pirSensorValue = digitalRead(PIR_PIN);

  if (Firebase.ready() && (millis() - sendDataPrevMillis >= 3000 || sendDataPrevMillis == 0))
  {
    sendDataPrevMillis = millis();

    // Set Water Sensor Data
    Serial.printf("Set Water Sensor Data... %s\n", Firebase.setInt(fbdo, F("/Haztec1/waterSensor"), waterSensorValue) ? "ok" : fbdo.errorReason().c_str());

    // Get Water Sensor Data
    Serial.printf("Get Water Sensor Data... %s\n", Firebase.getInt(fbdo, F("/Haztec1/waterSensor")) ? String(fbdo.to<int>()).c_str() : fbdo.errorReason().c_str());

    // Set Temperature
    Serial.printf("Set Temperature... %s\n", Firebase.setFloat(fbdo, F("/Haztec1/temperature"), t) ? "ok" : fbdo.errorReason().c_str());

    // Get Temperature
    Serial.printf("Get Temperature... %s\n", Firebase.getFloat(fbdo, F("/Haztec1/temperature")) ? String(fbdo.to<float>()).c_str() : fbdo.errorReason().c_str());

    // Set Humidity
    Serial.printf("Set Humidity... %s\n", Firebase.setDouble(fbdo, F("/Haztec1/humidity"), h) ? "ok" : fbdo.errorReason().c_str());

    // Get Humidity
    Serial.printf("Get Humidity... %s\n", Firebase.getDouble(fbdo, F("/Haztec1/humidity")) ? String(fbdo.to<double>()).c_str() : fbdo.errorReason().c_str());

    // Set Flame Sensor Data
    Serial.printf("Set Flame Sensor Data... %s\n", Firebase.setInt(fbdo, F("/Haztec1/flameSensor"), flameSensorValue) ? "ok" : fbdo.errorReason().c_str());

    // Get Flame Sensor Data
    Serial.printf("Get Flame Sensor Data... %s\n", Firebase.getInt(fbdo, F("/Haztec1/flameSensor")) ? String(fbdo.to<int>()).c_str() : fbdo.errorReason().c_str());

    // Set PIR Sensor Data
    Serial.printf("Set PIR Sensor Data... %s\n", Firebase.setInt(fbdo, F("/Haztec1/pirSensor"), pirSensorValue) ? "ok" : fbdo.errorReason().c_str());

    // Get PIR Sensor Data
    Serial.printf("Get PIR Sensor Data... %s\n", Firebase.getInt(fbdo, F("/Haztec1/pirSensor")) ? String(fbdo.to<int>()).c_str() : fbdo.errorReason().c_str());

    // Get the local IP address
    IPAddress localIP = WiFi.localIP();

    // Set Device IP Address
    Serial.printf("Set Device IP Address... %s\n", Firebase.setString(fbdo, F("/Haztec1/deviceIP1"), localIP.toString().c_str()) ? "ok" : fbdo.errorReason().c_str());

    // Get Device IP Address
    Serial.printf("Get Device IP Address... %s\n", Firebase.getString(fbdo, F("/Haztec1/deviceIP1")) ? fbdo.to<String>().c_str() : fbdo.errorReason().c_str());

    // Check flame sensor value and trigger alarm if below 500
    if (flameSensorValue < 400)
    {
      digitalWrite(BUZZER_PIN, HIGH); // Turn on the buzzer
      delay(1000);  // Keep the buzzer on for 1 second
      digitalWrite(BUZZER_PIN, LOW); // Turn off the buzzer
    }

    count++;
  }
}
