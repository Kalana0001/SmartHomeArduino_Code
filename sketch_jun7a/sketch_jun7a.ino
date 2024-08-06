#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

// Replace with your Firebase and WiFi credentials
#define FIREBASE_HOST "iotproject-9cf99-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "wfogCpqXSEgRqPPBdlj8Tj3mvSqxpiPCOhthL6Uh"
#define WIFI_SSID "Dialog 4G"
#define WIFI_PASSWORD "N5FN8TARLD4"

const int BULB1_PIN = D2;  // Define the pin where the first bulb is connected
const int BULB2_PIN = D3;  // Define the pin where the second bulb is connected
const int BULB3_PIN = D4;  // Define the pin where the third bulb is connected
const int FAN_PIN = D5;    // Define the pin where the fan is connected

void setup() {
  pinMode(BULB1_PIN, OUTPUT);
  pinMode(BULB2_PIN, OUTPUT);
  pinMode(BULB3_PIN, OUTPUT);
  pinMode(FAN_PIN, OUTPUT);
  
  Serial.begin(9600);
  
  // Connect to WiFi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.println("Connected to WiFi.");
  Serial.println(WiFi.localIP());
  
  // Connect to Firebase
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void loop() {
  // Read the values from Firebase
  bool bulb1 = Firebase.getBool("devices/bulb_01");
  bool bulb2 = Firebase.getBool("devices/bulb_02");
  bool bulb3 = Firebase.getBool("devices/bulb_03");
  bool fan = Firebase.getBool("devices/fan");
  
  // Check for errors in fetching data from Firebase
  if (Firebase.failed()) {
    Serial.print("Failed to read from Firebase: ");
    Serial.println(Firebase.error());
    delay(500); // Retry after a short delay
    return;
  }

  // Control the bulbs and fan based on Firebase values using if-else
  if (bulb1) {
    digitalWrite(BULB1_PIN, LOW);
  } else {
    digitalWrite(BULB1_PIN, HIGH);
  }

  if (bulb2) {
    digitalWrite(BULB2_PIN, LOW);
  } else {
    digitalWrite(BULB2_PIN, HIGH);
  }

  if (bulb3) {
    digitalWrite(BULB3_PIN, LOW);
  } else {
    digitalWrite(BULB3_PIN, HIGH);
  }

  if (fan) {
    digitalWrite(FAN_PIN, LOW);
  } else {
    digitalWrite(FAN_PIN, HIGH);
  }

  // Add a delay to avoid rapid toggling and to allow time for Firebase to update
  delay(50);
}
