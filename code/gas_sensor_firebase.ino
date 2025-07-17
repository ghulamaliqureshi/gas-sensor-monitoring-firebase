#include <WiFi.h>
#include <Firebase_ESP_Client.h>

// Wi-Fi credentials
#define WIFI_SSID "Place your"
#define WIFI_PASSWORD "place your"

// Firebase project credentials
#define API_KEY "Place your"
#define DATABASE_URL "Place your"

// MQ2 and Buzzer Pins
#define MQ2_PIN 34
#define BUZZER_PIN 26
#define GAS_THRESHOLD 1500  // Tune this value based on real readings

// Firebase objects
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

bool signupOK = false;

void setup() {
  Serial.begin(115200);

  pinMode(MQ2_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  // Connect to Wi-Fi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("\nWiFi connected!");

  // Setup Firebase
  config.api_key = API_KEY;
  config.database_url = DATABASE_URL;
  auth.user.email = "";
  auth.user.password = "";

  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
}

void loop() {
  if (Firebase.ready() && signupOK) {
    int gasValue = analogRead(MQ2_PIN);
    Serial.print("Gas Reading: ");
    Serial.println(gasValue);

    // Send to Firebase
    if (Firebase.RTDB.setInt(&fbdo, "/gasSensor/value", gasValue)) {
      Serial.println("Gas value sent to Firebase");
    } else {
      Serial.print("Firebase Error: ");
      Serial.println(fbdo.errorReason());
    }

    // Determine status and control buzzer
    String status = (gasValue > GAS_THRESHOLD) ? "ALERT" : "Safe";
    Firebase.RTDB.setString(&fbdo, "/gasSensor/status", status);
    digitalWrite(BUZZER_PIN, (gasValue > GAS_THRESHOLD) ? HIGH : LOW);

    delay(5000); // Wait before next reading
  } else {
    if (!signupOK && Firebase.signUp(&config, &auth, "", "")) {
      Serial.println("Firebase signup OK");
      signupOK = true;
    } else if (!signupOK) {
      Serial.printf("Firebase signup failed: %s\n", config.signer.signupError.message.c_str());
      delay(2000);
    }
  }
}
