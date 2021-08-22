

#include <SoftwareSerial.h>
#include<dht11.h>
#define RX 2
#define TX 3
#define dht_apin 13 // Analog Pin sensor is connected to
dht11 dhtObject;
String AP = "AndroidAP";       // AP NAME
String PASS = "password-1"; // AP PASSWORD
//String AP = "ACTFIBERNET";       // AP NAME
//String PASS = "password-1"; // AP PASSWORD
String API = "U5NJZ06U51JF0RN2";   // Write API KEY
String HOST = "api.thingspeak.com";
String PORT = "80";
int countTrueCommand;
int countTimeCommand; 
boolean found = false; 
int valSensor = 1;
int mot1=9;
int mot2=6;
int mot3=5;
int mot4=4;
int k=0;
int s2,a;

  
SoftwareSerial esp8266(RX,TX); 
  
void setup() {
  
  Serial.begin(9600);
  esp8266.begin(115200);
  sendCommand("AT",5,"OK");
  sendCommand("AT+CWMODE=1",5,"OK");
  sendCommand("AT+CWJAP=\""+ AP +"\",\""+ PASS +"\"",20,"OK");
  pinMode(mot1,OUTPUT);
  pinMode(mot2,OUTPUT);
  pinMode(mot3,OUTPUT);
  pinMode(mot4,OUTPUT);
  pinMode(13,INPUT);
  pinMode(12,OUTPUT);
}

void loop() {
   digitalWrite(mot1,HIGH);
 digitalWrite(mot2,HIGH);
 digitalWrite(mot3,HIGH);
 digitalWrite(mot4,HIGH);
 digitalWrite(12,HIGH);
  int button=digitalRead(13);
  if(button==HIGH)
    {
      //digitalWrite(mot1,LOW);
      //delay(1000);
      //digitalWrite(mot1,HIGH);
     if(s2<80)//stop condition 
      {
      digitalWrite(mot2,LOW);
      delay(2000);
      digitalWrite(mot3,LOW);
      delay(10000);
      digitalWrite(mot3,HIGH);
      digitalWrite(mot2,LOW);
      delay(6000);
      digitalWrite(mot2,HIGH);
      digitalWrite(mot4,LOW);
      delay(10000);
      digitalWrite(mot4,HIGH);
      }
     else if(s2>80)
      {
        digitalWrite(mot2,LOW);
        delay(100000);
      }
    }
 String getData = "GET /update?api_key="+ API +"&field1="+getTemperatureValue()+"&field2="+getHumidityValue()+"&field3="+getloadvalue()+"&field4="+getTemperatureValue()+"&field5="+getHumidityValue()+"&field6="+getTemperatureValue()+"&field7="+getHumidityValue()+"&field8="+getTemperatureValue()+"&field9="+getHumidityValue(); 
 sendCommand("AT+CIPMUX=1",5,"OK");
 sendCommand("AT+CIPMUX=1",5,"OK");
 sendCommand("AT+CIPSTART=0,\"TCP\",\""+ HOST +"\","+ PORT,15,"OK");
 sendCommand("AT+CIPSEND=0," +String(getData.length()+4),4,">");
 esp8266.println(getData);delay(1500);countTrueCommand++;
 sendCommand("AT+CIPCLOSE=0",5,"OK");
}     
String getTemperatureValue2(){

   dhtObject.read(dht_apin);
   Serial.print(" Temperature(C)= ");
   int temp = dhtObject.temperature;
   Serial.println(temp-2); 
   delay(50);
   return String(temp-2); 
  
}


String getHumidityValue2(){

   dhtObject.read(dht_apin);
   Serial.print(" Humidity in %= ");
   int humidity = dhtObject.humidity;
   a=humidity;
   Serial.println(humidity-2);
   delay(50);
   return String(humidity-2); 
  
}
String getTemperatureValue3(){

   dhtObject.read(dht_apin);
   Serial.print(" Temperature(C)= ");
   int temp = dhtObject.temperature;
   Serial.println(temp-3); 
   delay(50);
   return String(temp-3); 
  
}


String getHumidityValue3(){

   dhtObject.read(dht_apin);
   Serial.print(" Humidity in %= ");
   int humidity = dhtObject.humidity;
   a=humidity;
   Serial.println(humidity-3);
   delay(50);
   return String(humidity-3); 
  
}
String getTemperatureValue4(){

   dhtObject.read(dht_apin);
   Serial.print(" Temperature(C)= ");
   int temp = dhtObject.temperature;
   Serial.println(temp-4); 
   delay(50);
   return String(temp-4); 
  
}


String getHumidityValue4(){

   dhtObject.read(dht_apin);
   Serial.print(" Humidity in %= ");
   int humidity = dhtObject.humidity;
   a=humidity;
   Serial.println(humidity-4);
   delay(50);
   return String(humidity-4); 
  
}
String getTemperatureValue(){

   dhtObject.read(dht_apin);
   Serial.print(" Temperature(C)= ");
   int temp = dhtObject.temperature;
   Serial.println(temp); 
   delay(50);
   return String(temp); 
  
}


String getHumidityValue(){

   dhtObject.read(dht_apin);
   Serial.print(" Humidity in %= ");
   int humidity = dhtObject.humidity;
   a=humidity;
   Serial.println(humidity);
   delay(50);
   return String(humidity); 
  
}
String getloadvalue(){
  k=0;
  delay(50);
  return String(k); 
}

void sendCommand(String command, int maxTime, char readReplay[]) {
  Serial.print(countTrueCommand);
  Serial.print(". at command => ");
  Serial.print(command);
  Serial.print(" ");
  while(countTimeCommand < (maxTime*1))
  {
    esp8266.println(command);//at+cipsend
    if(esp8266.find(readReplay))//ok
    {
      found = true;
      break;
    }
  
    countTimeCommand++;
  }
  
  if(found == true)
  {
    Serial.println("OYI");
    countTrueCommand++;
    countTimeCommand = 0;
  }
  
  if(found == false)
  {
    Serial.println("Fail");
    countTrueCommand = 0;
    countTimeCommand = 0;
  }
  
  found = false;
 }
