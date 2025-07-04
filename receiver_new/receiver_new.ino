#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <espnow.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define BLYNK_TEMPLATE_ID "TMPL3dtyr5QRw"
#define BLYNK_TEMPLATE_NAME "LandSlide"
#define BLYNK_AUTH_TOKEN "JNSYenUo5F4fel-gqSRUgQetyzLMZsNa"
#define BLYNK_PRINT Serial

LiquidCrystal_I2C lcd(0x27, 16, 2);
WidgetLED led(V1);

char ssid[] = "VERDANT PW 4G";
char pass[] = "Verdant@123456";

uint8_t broadcastAddress[] = {0x08, 0xF9, 0xE0, 0x6B, 0x7D, 0x9D};

typedef struct struct_message {
  char a[32];
  int sensorValue;
  float floatValue;
  int rainValue;
  int vibrationValue;
  int soundValue;
} struct_message;

struct_message myData;

int sound1, rain1, vib1,sound2, rain2, vib2,sound3, rain3, vib3;
 int i=0,temp,tempv;

// Callback when data is received
void OnDataRecv(uint8_t *mac_addr, uint8_t *data, uint8_t len) {
  memcpy(&myData, data, sizeof(myData));

  Serial.print("Received data: ");
  Serial.print("Sensor: ");
  Serial.print(myData.floatValue);
  Serial.print(", Rain: ");
  Serial.print(myData.rainValue);
  Serial.print(", Vibration: ");
  Serial.print(myData.vibrationValue);
  Serial.print(", Sound: ");
  Serial.println(myData.soundValue);

  // Check if floatValue is 1.0
  if (myData.floatValue == 1.0) {
    sound1 = myData.soundValue;
    rain1 = myData.rainValue;
    vib1 = myData.vibrationValue;
  }
  if (myData.floatValue == 2.0) {
    sound2 = myData.soundValue;
    rain2 = myData.rainValue;
    vib2 = myData.vibrationValue;
  }
  if (myData.floatValue == 3.0) {
    sound3 = myData.soundValue;
    rain3 = myData.rainValue;
    vib3 = myData.vibrationValue;
  }
}

void setup() {
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  Serial.begin(115200);
  pinMode(D5,OUTPUT);
  digitalWrite(D5,HIGH);
  lcd.begin();
  lcd.setCursor(3, 0);
  lcd.print("LandSlide");
  lcd.setCursor(3, 1);
  lcd.print("Prediction");
  delay(2000);
  lcd.clear();

  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Register peer
  esp_now_add_peer(broadcastAddress, ESP_NOW_ROLE_CONTROLLER, 1, NULL, 0);

  // Register callback for data reception
  esp_now_register_recv_cb(OnDataRecv);
}

  void loop() {
  // Do other tasks if needed
  Serial.println("******************* Vibration Status ******************");

  bool isVib1 = (vib1 == 12);
  bool isVib2 = (vib2 == 15);
  bool isVib3 = (vib3 == 18);
  bool isRain1 = (rain1 == 11);
  bool isRain2 = (rain2 == 14);
  bool isRain3 = (rain3 == 17);

  if ((isVib1 || isVib2 || isVib3)&&((isRain1 && isRain2) || (isRain1 && isRain3) || (isRain2 && isRain3))) {
    Serial.println("Landslide");
  lcd.setCursor(0, 0);
  lcd.print("    LANDSLIDE    ");
  lcd.setCursor(0, 1);
  lcd.print("           ");
  tempv=100;
  Blynk.virtualWrite(V1, tempv);
  Blynk.run();
  for(i=0;i<15;i++)
  {
    digitalWrite(D5,LOW);
    delay(1000);
    digitalWrite(D5,HIGH);
    delay(500);
  }
  } else {
    Serial.println("No Landslide Detected");
  }
  Serial.println("******************* sound Status ******************");

  bool issound1 = (sound1 == 10);
  bool issound2 = (sound2 == 13);
  bool issound3 = (sound3 == 16);

  if (issound1 || issound2 || issound3) {
    Serial.println("SOUND");
  lcd.setCursor(0, 0);
  lcd.print("      SOUND     ");
  lcd.setCursor(0, 1);
  lcd.print("    WARNING     ");
  for(i=0;i<6;i++)
  {
    digitalWrite(D5,LOW);
    delay(100);
    digitalWrite(D5,HIGH);
    delay(100);
  }
  } else {
    Serial.println("No Landslide Detected");
  }
  Serial.println("******************* Rain Status ******************");
  
  

  if (isRain1 && isRain2 && isRain3) {
    Serial.println("Heavy Rain");
    lcd.setCursor(0, 0);
  lcd.print("RAINFALL: HIGH  ");
  lcd.setCursor(0,1);
  lcd.print("             ");
  temp=100;
  Blynk.virtualWrite(V0, temp);
  Blynk.run();
  for(i=0;i<6;i++)
  {
    digitalWrite(D5,LOW);
    delay(100);
    digitalWrite(D5,HIGH);
    delay(100);
  }
  } else if ((isRain1 && isRain2) || (isRain1 && isRain3) || (isRain2 && isRain3)) {
    Serial.println("Moderate Rain");
    lcd.setCursor(0, 0);
  lcd.print("RAINFALL: MEDIUM");
  lcd.setCursor(0, 1);
  lcd.print("             ");
  temp=75;
  Blynk.virtualWrite(V0, temp);
  Blynk.run();
  } else if (isRain1 || isRain2 || isRain3) {
    Serial.println("Low Rain");
    lcd.setCursor(0, 0);
    lcd.print("RAINFALL: LOW   ");
    lcd.setCursor(0, 1);
    lcd.print("             ");
    temp=50;
    Blynk.virtualWrite(V0, temp);
    Blynk.run();
  } else {
  Serial.println("No Rain Detected");
  lcd.setCursor(0, 0);
  lcd.print("     NORMAL     ");
  lcd.setCursor(0, 1);
  lcd.print("             ");
  temp=0;
  Blynk.virtualWrite(V0, temp);
  Blynk.run();
  }

  delay(1000);
}
