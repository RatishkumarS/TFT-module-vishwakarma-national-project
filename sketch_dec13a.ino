int IR = A0;
float voltage;
String A = "GET /update?api_key=VX5AUWKZI5ICVYMU&field1=";
String Z = " HTTP/1.1 \nHOST: api.thingspeak.com \r\n\r\n";   //web link
void setup() 
{                
Serial.begin(115200); 
}
void loop() 
{
/* VOLTAGE */
voltage =analogRead(IR);
voltage = (voltage / 1024.0) * 5.0;
char voltage_buff[16];
String voltageX = dtostrf(voltage, 4, 1, voltage_buff);
String postStr = A + voltageX + Z;
/*********   Uploading to ThinkSpeak Cloud    ***********/
/*********  Sending AT Commands to ESP8266    ***********/
Serial.println("AT");
delay(2000);
Serial.print("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",80\r\n");
delay(3000);
String ciplength = "AT+CIPSEND=" + String(postStr.length()) + "\r\n";
Serial.print(ciplength);
delay(3000);
Serial.print(postStr);
delay(3000);
Serial.print("AT+RST\r\n");
delay(3000);   
}
