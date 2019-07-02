#include <ArduinoJson.h>
#include <Ethernet.h>
#include <SPI.h>

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

IPAddress server(192, 167, 1, 2); 

IPAddress ip(192, 167, 1, 3);
IPAddress myDns(192, 167, 1, 1);

EthernetClient client;

// Variables to measure the speed
unsigned long beginMicros, endMicros;
unsigned long byteCount = 0;
bool printWebData = true;  // set to false for better speed measurement
const int rele[4] = {2, 3, 5, 6};
void setup() {
  for(int i = 0; i < 4; i++){
    pinMode(rele[i], OUTPUT);
    digitalWrite(rele[i], HIGH);
  }
  // Initialize Serial port
  Serial.begin(9600);
  // start the Ethernet connection:
  Serial.println("Initialize Ethernet:");
  Ethernet.begin(mac, ip);
    if (Ethernet.hardwareStatus() == EthernetNoHardware) {
      Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");
      while (true) {
        delay(1); // do nothing, no point running without Ethernet hardware
      }
    }
    if (Ethernet.linkStatus() == LinkOFF) {
      Serial.println("Ethernet cable is not connected.");
    }
    // try to congifure using IP address instead of DHCP:
    Ethernet.begin(mac, ip, myDns);
  // give the Ethernet shield a second to initialize:
  delay(1000);
  Serial.print("connecting to ");
  Serial.print(server);
  Serial.println("...");
  
}

unsigned long tempo1=0;
unsigned long tempo2=0;
unsigned long tempo3=0;
unsigned long tempo4=0; 

bool comutar1 = false;
bool comutar2 = false;
bool comutar3 = false;
bool comutar4 = false;

void Rele1(int rele){
  if(comutar1){
    digitalWrite(rele, !digitalRead(rele));
    tempo1=millis();
    comutar1=false;
  }
}
void Rele2(int rele){
  if(comutar2){
    digitalWrite(rele, !digitalRead(rele));
    tempo2=millis();
    comutar2=false;
  }
}
void Rele3(int rele){
  if(comutar3){
    digitalWrite(rele, !digitalRead(rele));
    tempo3=millis();
    comutar3=false;
  }
}
void Rele4(int rele){
  if(comutar4){
    digitalWrite(rele, !digitalRead(rele));
    tempo4=millis();
    comutar4=false;
  }
}

void espera(int tmp0, int tmp1, int tmp2, int tmp3){
  
  if(!comutar1 && millis()-tempo1>=tmp0){
    comutar1 = true;
  }
  
  if(!comutar2 && millis()-tempo2>=tmp1){
    comutar2 = true;
  }
  
  if(!comutar3 && millis()-tempo3>=tmp2){
    comutar3 = true;
  }
  
  if(!comutar4 && millis()-tempo4>=tmp3){
    comutar4 = true;
  }
}


void loop() {

    if (client.connect(server, 80)) {
      Serial.println(F("Connected!"));
    
      // Send HTTP request
      client.println(F("GET /arduino/status.php HTTP/1.0"));
      client.println(F("Host: 192.167.1.2"));
      client.println(F("Connection: close"));
      if (client.println() == 0) {
        Serial.println(F("Failed to send request"));
        return;
      }
    } else {
      // if you didn't get a connection to the server:
      Serial.println("connection failed");
    }
  beginMicros = micros();

  // Check HTTP status
  char status[32] = {0};
  client.readBytesUntil('\r', status, sizeof(status));
  // It should be "HTTP/1.0 200 OK" or "HTTP/1.1 200 OK"
  if (strcmp(status + 9, "200 OK") != 0) {
    Serial.print(F("Unexpected response: "));
    Serial.println(status);
    //return;
  }

  // Skip HTTP headers
  char endOfHeaders[] = "\r\n\r\n";
  if (!client.find(endOfHeaders)) {
    Serial.println(F("Invalid response"));
    //return;
  }

  // Allocate the JSON document
  // Use arduinojson.org/v6/assistant to compute the capacity.
  const size_t capacity = JSON_OBJECT_SIZE(3) + JSON_ARRAY_SIZE(2) + 60;
  DynamicJsonDocument doc(capacity);

  // Parse JSON object
  DeserializationError error = deserializeJson(doc, client);
  if (error) {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.c_str());
    //return;
  }

  // Extract values
  Serial.println(F("Response:"));
  Serial.println(doc["r1"].as<int>());
  Serial.println(doc["r2"].as<int>());
  Serial.println(doc["r3"].as<int>());
  Serial.println(doc["r4"].as<int>());
  Serial.println(doc["btn"].as<int>());
  String data;
  int tmp[4] = {0, 0, 0, 0};


      for(int i = 0; i < 4; i++){
        if(i == 0){
          data = "r1";
        } else if(i == 1){
          data = "r2";
        } else if(i == 2){
          data = "r3";
        } else if(i == 3){
          data = "r4";
        }
    
        if(doc[data].as<int>() == 0){
          digitalWrite(rele[i], HIGH);
        } else if(doc[data].as<int>() == 1) {
          digitalWrite(rele[i], LOW);
        } else {
          tmp[i] = doc[data].as<int>();
          if(i == 0){
            Rele1(rele[i]);
          }
          if(i == 1){
            Rele2(rele[i]);
          }

          if(i == 2){
            Rele3(rele[i]);
          }

          if(i == 3){
            Rele4(rele[i]);
          }
           
        }
      }
      
      espera(tmp[0], tmp[1], tmp[2], tmp[3]);

       /* if(tmp[0] != 0){
          delay(tmp[0]);
           digitalWrite(rele[0], HIGH);
           tmp[0] = 0;
        }
  
        if(tmp[1] != 0){
          delay(tmp[1]);
          digitalWrite(rele[1], HIGH);
          tmp[0] = 0;
        }
  
        if(tmp[2] != 0){
          delay(tmp[2]);
          digitalWrite(rele[2], HIGH);
          tmp[0] = 0;
        }
        if(tmp[3] != 0){
          delay(tmp[3]);
          digitalWrite(rele[3], HIGH);
          tmp[0] = 0;
        }*/
        //10 segundos para fazer outra requisição
        //delay(10000);
  //client.stop();
}
