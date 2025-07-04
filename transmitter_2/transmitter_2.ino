#include <ESP8266WiFi.h>
#include <espnow.h>

uint8_t broadcastAddress[] = {0x08, 0xF9, 0xE0, 0x6B, 0x7D, 0x9D};
unsigned long previousMillis = 0, currentMillis;
const long interval = 1000;
const int LED13 = 13;
typedef struct struct_message {
  char a[32];
  int sensorValue;
  float floatValue;
  int rainValue;
  int vibrationValue;
  int soundValue;
} struct_message;

struct_message myData;

int previousVibrationState = HIGH; // Initial state of vibration sensor
int previousRainState = HIGH;      // Initial state of rain sensor
int previousSoundState = HIGH;     // Initial state of sound sensor

// Callback when data is sent
void OnDataSent(uint8_t *mac_addr, uint8_t sendStatus) {
  Serial.print("Last Packet Send Status: ");
  if (sendStatus == 0) {
    Serial.println("Delivery success");
    digitalWrite(LED_BUILTIN, HIGH);
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(D2, INPUT);
  pinMode(D1, INPUT);
  pinMode(A0, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);

  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Once ESPNow is successfully Init, we will register for Send CB to
  // get the status of Transmitted packet
  esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);
  esp_now_register_send_cb(OnDataSent);

  // Register peer
  esp_now_add_peer(broadcastAddress, ESP_NOW_ROLE_SLAVE, 1, NULL, 0);
}

void loop() {
  int vibrationState = analogRead(A0);
  int rainState = digitalRead(D1);
  int soundState = digitalRead(D2);

  if (vibrationState != previousVibrationState || rainState != previousRainState || soundState != previousSoundState) {
    Serial.println("Change detected. Sending data...");

    strcpy(myData.a, "Sensor data from station 1");
    myData.floatValue = 1.0;
    myData.rainValue = rainState == LOW ? 11 : 0;
    myData.vibrationValue = vibrationState < 700 ? 12 : 0;
    myData.soundValue = soundState == LOW ? 10 : 0;

    // Combine sensor values
    myData.sensorValue = myData.rainValue + myData.vibrationValue + myData.soundValue;

    esp_now_send(broadcastAddress, (uint8_t *)&myData, sizeof(myData));
    delay(2000);

    previousVibrationState = vibrationState;
    previousRainState = rainState;
    previousSoundState = soundState;
  }

  currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    digitalWrite(LED_BUILTIN, LOW);
  }
}
