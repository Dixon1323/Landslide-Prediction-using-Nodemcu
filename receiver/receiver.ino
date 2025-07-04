#include <ESP8266WiFi.h>
#include <espnow.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

int data;
float station;
int rain1, sound1, vib1, rain2, sound2, vib2, rain3, sound3, vib3;
unsigned long previousMillis = 0, currentMillis;
const long interval = 20000;
bool lcdclr = false;
String dataString = "";
// Structure example to receive data
// Must match the sender structure
typedef struct struct_message {
  char a[32];
  int b;
  float c;
  String d;
  bool e;
} struct_message;

// Create a struct_message called myData
struct_message myData;

// Callback function that will be executed when data is received
void OnDataRecv(uint8_t * mac, uint8_t *incomingData, uint8_t len) {
  memcpy(&myData, incomingData, sizeof(myData));
//  Serial.print("Bytes received: ");
//  Serial.println(len);
//  Serial.print("Char: ");
//  Serial.println(myData.a);
//  Serial.print("Int: ");
//  Serial.println(myData.b);
//  Serial.print("Float: ");
//  Serial.println(myData.c);
//  Serial.print("String: ");
//  Serial.println(myData.d);
//  Serial.print("Bool: ");
//  Serial.println(myData.e);
//  Serial.println();
  data = myData.b;
  station = myData.c;
  delay(100);
  assignval();


}

void setup() {
  Serial.begin(115200);
  lcd.begin();
  lcd.setCursor(3, 0);
  lcd.print("LandSlide");
  lcd.setCursor(3, 1);
  lcd.print("Prediction");
  delay(2000);
  Serial.println("adter delay");
  resetAllVariables();
  WiFi.mode(WIFI_STA);

  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  esp_now_set_self_role(ESP_NOW_ROLE_SLAVE);
  esp_now_register_recv_cb(OnDataRecv);
}

  void loop() {


}



void assignval() {
  
  dataString = "";
  if ((data == 10 && station == 1.0) || (data == 0 && station == 1.0)) {
    sound1 = data;
    Serial.print("sound value of station 1:");
    Serial.println(sound1);
    dataString += String(sound1) + ",";
  }
  if ((data == 11 && station == 1.0) || (data == 0 && station == 1.0)) {
    rain1 = data;
    Serial.print("rain value of station 1:");
    Serial.println(rain1);
    }

  if ((data == 12 && station == 1.0) || (data == 0 && station == 1.0)) {
    vib1 = data;
    Serial.print("vibration value of station 1:");
    Serial.println(vib1);
    dataString += String(vib1) + ",";
  }
  //
  //
  if ((data == 13 && station == 2.0) || (data == 0 && station == 2.0)) {
    sound2 = data;
    Serial.print("sound value of station 2:");
    Serial.println(sound2);
    dataString += String(sound2) + ",";
  }
  if ((data == 14 && station == 2.0) || (data == 0 && station == 2.0)) {
    rain2 = data;
    Serial.print("rain value of station 2:");
    Serial.println(rain2);
    dataString += String(rain2) + ",";

  }
  if ((data == 15 && station == 2.0) || (data == 0 && station == 2.0)) {
    vib2 = data;
    Serial.print("vib value of station 2:");
    Serial.println(vib2);
    dataString += String(vib2) + ",";
  }
  //
  //
  if ((data == 16 && station == 3.0) || (data == 0 && station == 3.0)) {
    sound3 = data;
    Serial.print("sound value of station 3:");
    Serial.println(sound3);
    dataString += String(sound3) + ",";
  }
  if ((data == 17 && station == 3.0) || (data == 0 && station == 3.0)) {
    rain3 = data;
    Serial.print("rain value of station 3:");
    Serial.println(rain3);
    dataString += String(rain3) + ",";

  }
  if ((data == 18 && station == 3.0) || (data == 0 && station == 3.0)) {
    vib3 = data;
    Serial.print("vib value of station 3:");
    Serial.println(vib3);
    dataString += String(vib3) + ",";
  }
dataString.trim(); 
}





void resetAllVariables()
{
  rain1 = 0;
  sound1 = 0;
  vib1 = 0;
  rain2 = 0;
  sound2 = 0;
  vib2 = 0;
  rain3 = 0;
  sound3 = 0;
  vib3 = 0;
}
