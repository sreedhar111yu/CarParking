#include <WiFi.h>
#include <FirebaseESP32.h>

// Firebase project configuration
#define FIREBASE_HOST "your_firebase_host"
#define FIREBASE_AUTH "your_firebase_auth_token"

// Wi-Fi credentials
#define WIFI_SSID "your_wifi_ssid"
#define WIFI_PASSWORD "your_wifi_password"

// Sensor pins
#define SENSOR1_PIN 32
#define SENSOR2_PIN 33
#define SENSOR3_PIN 34
#define SENSOR4_PIN 35

FirebaseData firebaseData;

void setup() {
  Serial.begin(115200);
  
  pinMode(SENSOR1_PIN, INPUT);
  pinMode(SENSOR2_PIN, INPUT);
  pinMode(SENSOR3_PIN, INPUT);
  pinMode(SENSOR4_PIN, INPUT);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println(" connected");
  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
}

void loop() {
  int sensor1_status = digitalRead(SENSOR1_PIN);
  int sensor2_status = digitalRead(SENSOR2_PIN);
  int sensor3_status = digitalRead(SENSOR3_PIN);
  int sensor4_status = digitalRead(SENSOR4_PIN);

  // Send sensor data to Firebase
  Firebase.setInt(firebaseData, "/parking/spot1", sensor1_status);
  Firebase.setInt(firebaseData, "/parking/spot2", sensor2_status);
  Firebase.setInt(firebaseData, "/parking/spot3", sensor3_status);
  Firebase.setInt(firebaseData, "/parking/spot4", sensor4_status);

  delay(2000); // Update every 2 seconds
}
