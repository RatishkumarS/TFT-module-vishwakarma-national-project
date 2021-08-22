#include <SoftwareSerial.h>
SoftwareSerial SUART(8,11);//Rx-0Tx-1
#include <HX711.h>
#include <SimpleDHT.h>//temp and humidity
#define DOUT 3//weight scale
#define CLK 2
HX711 scale(DOUT,CLK);
int mot1=9;
int mot2=6;
int pinDHT11 = 10;//temp and humidity
int pinDHT11a = 7;
//int pinDHT11b=8;
//int pinDHT11c=11;
//PINS AVAILABLE 7 8 11 
int s=0;//for sum of weight 
int f=0;
SimpleDHT11 dht11(pinDHT11);
int mot3=5;
int mot4=4;
int a,b;
int s2=0;
String weight;
void setup()
{
  Serial.begin(9600);
  SUART.begin(9600);
  Serial.println("System Ready..");
  Serial.println("Press T to tare");
  scale.set_scale(-96650); //Calibration Factor obtained from first sketch
  scale.tare(); //Reset the scale to 0 
  Serial.begin(9600);
  pinMode(mot1,OUTPUT);
  pinMode(mot2,OUTPUT);
  pinMode(mot3,OUTPUT);
  pinMode(13,INPUT);
  pinMode(pinDHT11,INPUT);
  pinMode(pinDHT11a,INPUT);
  //pinMode(pinDHT11b,INPUT);
  //pinMode(pinDHT11c,INPUT);
  pinMode(12,OUTPUT);
  pinMode(4,OUTPUT);
}
void loop() 
{  
  digitalWrite(mot1,HIGH);
  digitalWrite(mot2,HIGH);
  digitalWrite(mot3,HIGH);
  digitalWrite(mot4,HIGH);
  Serial.print("WEIGHT PROCESSED:");
  int k=scale.get_units();
  s=s+k;
  //weight=weight + s + "kg"; 
  //Serial.println(weight);
  //SUART.println(weight);
  if(Serial.available())
    {
       char temp = Serial.read();
      if(temp == 't' || temp == 'T')
      scale.tare(); //Reset the scale to zero 
    }
  //BTserial.println("MAXIMUM WEIGHT LOAD = 100kgs");
  byte temperature = 0;
  byte humidity = 0;
  int err = SimpleDHTErrSuccess;
  if ((err = dht11.read(&temperature, &humidity, NULL)) != SimpleDHTErrSuccess) {
    Serial.print("Read DHT11 failed, err="); Serial.println(err);delay(1000);
    return;
  }
  a=digitalRead(pinDHT11a);
//  b=digitalRead(pinDHT11b); 
  a=(int)humidity;
  weight=weight + a;
  Serial.println(a);
  Serial.println(weight);
  SUART.println(weight);
  delay(2000);
  weight= " ";
  b=(int)humidity;
  Serial.print((int)temperature); Serial.print(" *C, "); 
  Serial.print((int)humidity); Serial.println(" H");
  delay(1500);       
  digitalWrite(12,HIGH);
  int button=digitalRead(13);
  if(button==HIGH)
    {
      digitalWrite(mot1,LOW);
      delay(1000);
      digitalWrite(mot1,HIGH);
    }
  int s1=digitalRead(10);
  Serial.println(10);
  s1=(int)humidity;
  s2=(a+b+s1)/3;
  if(s2<80)//stop condition 
    {
      digitalWrite(mot2,HIGH);
      digitalWrite(mot3,LOW);
      delay(10000);
      digitalWrite(mot3,HIGH);
      digitalWrite(mot2,LOW);
      delay(60000);
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
  Serial.println(s2);
  SUART.print(s2);
}
