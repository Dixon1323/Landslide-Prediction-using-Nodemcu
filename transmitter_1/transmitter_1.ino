#include <ESP8266WiFi.h>
#include <espnow.h>


uint8_t broadcastAddress[] = {0x08,0xF9,0xE0,0x6B,0x7D,0x9D};
unsigned long previousMillis = 0,currentMillis;
const long interval = 1000; 
const int LED13 = 13;  
typedef struct struct_message {
  char a[32];
  int b;
  float c;
  String d;
  bool e;
} struct_message;

struct_message myData;


// Callback when data is sent
void OnDataSent(uint8_t *mac_addr, uint8_t sendStatus) {
  Serial.print("Last Packet Send Status: ");
  if (sendStatus == 0){
    Serial.println("Delivery success");
    digitalWrite(LED_BUILTIN,HIGH);
  }
}
 
void setup() {
  Serial.begin(115200);
  pinMode(D2,INPUT);
  pinMode(D1,INPUT);
  pinMode(A0,INPUT);
  pinMode(LED_BUILTIN,OUTPUT);
 
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Once ESPNow is successfully Init, we will register for Send CB to
  // get the status of Trasnmitted packet
  esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);
  esp_now_register_send_cb(OnDataSent);
  
  // Register peer
  esp_now_add_peer(broadcastAddress, ESP_NOW_ROLE_SLAVE, 1, NULL, 0);
}
 
void loop() {
  Serial.println(analogRead(A0));
    if(analogRead(A0)<=700)
    {
    strcpy(myData.a, "VIbration Detected on station 1");
    myData.b = 12;
    myData.c = 1.0;
    myData.d = "Hello";
    myData.e = false;
    esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData)); 
    delay(2000);
    }
    if(digitalRead(D1)==0)
    {
    strcpy(myData.a, "rain Detected on station 1");
    myData.b = 11;
    myData.c = 1.0;
    myData.d = "Hello";
    myData.e = false;
    esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData)); 
    delay(2000);
    }
    
    if(digitalRead(D2)==0)
    {
    strcpy(myData.a, "Sound Detected on station 1");
    myData.b = 10;
    myData.c = 1.0;
    myData.d = "Hello";
    myData.e = false;
    esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData)); 
    delay(2000);
    }
    currentMillis = millis();
    if (currentMillis - previousMillis >= interval) 
    {
      previousMillis = currentMillis;
      digitalWrite(LED_BUILTIN,LOW);
    }
    
}
