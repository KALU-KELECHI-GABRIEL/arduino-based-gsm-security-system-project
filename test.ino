#include <SoftwareSerial.h>
//#include <DHT11.h>
//int pin=11;
//DHT11 dht11(pin); 
char inchar; // Will hold the incoming character from the GSM shield
SoftwareSerial SIM900(7, 8);
int onoff=0; // 0 = off, 1 = on
const byte PIR = 2;
const byte BUZZER = 12;
const byte LEDLM35 = 18;
const byte LEDPIR = 3 ;
const byte LEDMQ2 = 4 ;
const byte LEDMQ7 = 5 ;
const byte LEDINTERNAL = 13 ;
const byte LEDEXTERNAL = 10 ;
const int MQ2 = A0;
const int MQ7 = A1;
const int LM35 = A2;
byte sensorThres = 200;
byte sensorThres7 = 350;
int mq2SMS,mq7SMS,pirSMS,lm35SMS;
boolean mq2,mq7,pir,temp=0;
float current;
float previous;


void setup()
{
pinMode(MQ2, INPUT); // put your setup code here, to run once
 pinMode(PIR, INPUT);
 pinMode(MQ7, INPUT);
 pinMode(LM35, INPUT);
 pinMode(LEDLM35, OUTPUT);
 pinMode(LEDPIR, OUTPUT);
 pinMode( LEDMQ2, OUTPUT);
 pinMode(LEDMQ7, OUTPUT);
 pinMode(LEDINTERNAL, OUTPUT);
 pinMode(LEDEXTERNAL, OUTPUT);
 pinMode(BUZZER, OUTPUT);
  pinMode(9, OUTPUT);
 pinMode(19, OUTPUT);
Serial.begin(19200);
digitalWrite(19,HIGH);
SIM900power();
SIM900.begin(19200);
delay(2000); // give time to log on to network.
SIM900.print("AT+CLIP=1\r"); // turn on caller ID notification
delay(100);
delay(2000);
digitalWrite(19,LOW);
float previous=10;
} 
void SIM900power()
// software equivalent of pressing the GSM shield "power" button
{
digitalWrite(9, LOW);
delay(1000);
digitalWrite(9, HIGH);
delay(1000);
digitalWrite(9, LOW);
} 

void loop()
{
callMonitor(); 
checkLM35();
checkMQ2();
checkMQ7();
if(onoff==0){
  checkPIR();
  Serial.println("EXTERNAL MODE    EXTERNAL MODE    EXTERNAL MODE    EXTERNAL MODE");
 digitalWrite(LEDEXTERNAL,HIGH);
 digitalWrite(LEDINTERNAL, LOW);
 }
else if(onoff==1){Serial.println("INTERNAL MODE    INTERNAL MODE    INTERNAL MODE    INTERNAL MODE");
 digitalWrite(LEDEXTERNAL,LOW);
 digitalWrite(LEDINTERNAL, HIGH);}

}



void callMonitor()
{
if(SIM900.available() >0)
{
inchar=SIM900.read();
if (inchar=='0')
{
delay(10);
inchar=SIM900.read();
if (inchar=='8')
{
delay(10);
inchar=SIM900.read();
if (inchar=='0')
{
delay(10);
inchar=SIM900.read();
if (inchar=='5')
{
delay(10);
inchar=SIM900.read();
if (inchar=='3')
{
delay(10);
inchar=SIM900.read();
if (inchar=='2')
{
delay(10);
inchar=SIM900.read();
if (inchar=='9')
{
delay(10);
inchar=SIM900.read();
if (inchar=='6')
{
delay(10);
inchar=SIM900.read();
if (inchar=='8')
{
delay(10);
inchar=SIM900.read();
if (inchar=='0')
{
delay(10);
inchar=SIM900.read();
if (inchar=='1')
SIM900.print("AT+HVOIC\r");
tone(BUZZER, 5000, 2000);
 digitalWrite(19,HIGH);
 delay(30000);
{
 Serial.println("do sometehing");
 SIM900.print("ATH\r");
 delay(10);
 dosomething();
 SIM900.print("ATH\r");
 delay(10);
 SIM900.print("ATH\r");
 delay(10);
SIM900.print("ATH\r");
SIM900.print("AT+HVOIC\r");

// now the number is matched, do something
// arbitrary delay so the function isn't called again on the same phone call
delay(5000);
}
}
}
}
}
}
}
}
}
}
}
}
}

void dosomething()
{
  if (onoff ==0){
  onoff = 1;
   digitalWrite(LEDEXTERNAL,HIGH);
 digitalWrite(LEDINTERNAL, LOW);
 tone(BUZZER, 10000, 2000);
 digitalWrite(19,LOW);
  }
  else if(onoff ==1){
    onoff = 0;
    digitalWrite(LEDEXTERNAL,LOW);
 digitalWrite(LEDINTERNAL, HIGH);
 tone(BUZZER, 10000, 2000);
 digitalWrite(19,LOW);
    }
  }

    // CARBON MONOXIDE SENSOR LOOP

void checkMQ7(){
int analogMQ7 = analogRead(MQ7);
  Serial.println("Pin mq7: ");
  Serial.print(analogMQ7);
  // Checks if it has reached the threshold value
  if (analogMQ7 > 400)
  {
    if(SIM900.available() >0){
    callMonitor();
    if(onoff==0){return;}
    return;
    }
    delay(2000);
   int analogMQ7 = analogRead(MQ7);
  Serial.println("Pin mq7: ");
  Serial.print(analogMQ7);
  // Checks if it has reached the threshold value
  if (analogMQ7 > 400){ 
     if(onoff==1){
    if(mq7==0){ 
      digitalWrite(LEDMQ7, HIGH);
    tone(BUZZER, 1000, 3000);
 SIM900.print("AT+CMGF=1\r"); // AT command to send SMS message
 delay(1000);
SIM900.println("AT + CMGS = \"+2348133587431\""); // recipient's mobile number, in international format
delay(1000);
SIM900.println("HELLO UNSAFE CARBON DIOXIDE LEVEL"); // message to send
delay(1000);
SIM900.println((char)26); // End AT command with a ^Z, ASCII code 26
delay(1000);
SIM900.println();
digitalWrite(19, HIGH);
delay(5000); // give module time to send SMS
   mq7==1;
   digitalWrite(19, LOW);
   }
   else if(mq7==1){digitalWrite(LEDMQ7, HIGH);
    tone(BUZZER, 1000, 3000);}
   }
   if(onoff==0){
     digitalWrite(LEDMQ7, HIGH);
      digitalWrite(LEDMQ7, HIGH);
    tone(BUZZER, 1000, 3000);
   }
  }
     delay(10000);
     digitalWrite(LEDMQ7, LOW);
     callMonitor();
}  
  else
  {
    digitalWrite(LEDMQ7, LOW);
    noTone(BUZZER);
    callMonitor();
    mq7==0;
  } 
  }


// PIR SENSOR
//
void checkPIR(){
  /*
PIR sketch
a Passive Infrared motion sensor connected to pin 6
lights the LED on pin 3
*/
int val = digitalRead(PIR); // read input value
if (val == HIGH) // check if the input is HIGH
{
   if(SIM900.available() >0){
    callMonitor();
    if(onoff==1){return;}
    return;
    }
  delay(3000);
  if(SIM900.available() >0){
    callMonitor();
    if(onoff==1){return;}
    return;
    }
    int val = digitalRead(PIR); // read input value
if (val == HIGH) // check if the input is HIGH{
   {
    Serial.println("MOTION ");
 if(onoff==0){
  callMonitor();
  if(onoff==1){return;} 
  if(pir==0){ 
    digitalWrite(LEDPIR, HIGH); // turn LED on if motion detected
 tone(BUZZER, 1000, 3000);
    SIM900.print("AT+CMGF=1\r"); // AT command to send SMS message
delay(1000);
SIM900.println("AT + CMGS = \"+2348133587431\""); // recipient's mobile number, in international format
delay(1000);
SIM900.println(" INTRUDER ALERT"); // message to send
delay(1000);
SIM900.println((char)26); // End AT command with a ^Z, ASCII code 26
delay(1000);
SIM900.println();
digitalWrite(19, HIGH);
delay(5000); // give module time to send SMS
 pir==1;
 digitalWrite(19, LOW);
 }
 else if(pir==0){
   digitalWrite(LEDPIR, HIGH); // turn LED on if motion detected
 tone(BUZZER, 1000, 3000);
 }
 }
   }
    delay(10000);
    digitalWrite(LEDPIR, LOW);
     callMonitor();
}
else{
digitalWrite(LEDPIR, LOW); // turn LED off
noTone(BUZZER);
callMonitor();
}
}

void checkLM35(){
  /*
lm35 internal operation mode sketch
*/ // led on pin 2
int lmvalue = analogRead(LM35);
float millivolts = (lmvalue*500)/1023;
float celsius = -1* millivolts; // sensor output is 10mV per degree Celsius
Serial.println("LM35: ");
Serial.print(celsius);

lmvalue = analogRead(LM35);
millivolts = (lmvalue*500)/1023;
celsius = -1* millivolts; // sensor output is 10mV per degree Celsius
 Serial.println("LM35: ");
 Serial.print(celsius);
    if(celsius >= 45){
  if(onoff==1){
   if(temp==0){ 
    tone(BUZZER, 1000, 3000);
  digitalWrite(LEDLM35, HIGH);
  SIM900.print("AT+CMGF=1\r"); // AT command to send SMS message
delay(1000);
SIM900.println("AT + CMGS = \"+2348133587431\""); // recipient's mobile number, in international format
delay(1000);
SIM900.println("HELLO HIGH TEMPERATURE"); // message to send
delay(1000);
SIM900.println((char)26); // End AT command with a ^Z, ASCII code 26
delay(1000);
SIM900.println();
digitalWrite(19, HIGH);
delay(5000); // give module time to send SMS
digitalWrite(19, LOW);
   temp==1;
   }
   else{
    if(temp==1){ 
    tone(BUZZER, 1000, 3000);
  digitalWrite(LEDLM35, HIGH);
    }
    }
   }
   if(onoff==0){
     digitalWrite(LEDLM35, HIGH); 
    tone(BUZZER, 1000, 3000);
  digitalWrite(LEDLM35, HIGH);
 
     }
else{
  digitalWrite(BUZZER, LOW);
  digitalWrite(LEDLM35, LOW);
  callMonitor();
  temp==0;
  }
}
}


void checkMQ2(){
int analogMQ2 = analogRead(MQ2);
  Serial.println("Pin mq2: ");
  Serial.print(analogMQ2);
  // Checks if it has reached the threshold value
  if (analogMQ2 > 300)
  {
    if(SIM900.available() >0){
    callMonitor();
    if(onoff==0){return;}
    return;
    }
    delay(500);
   int analogMQ2 = analogRead(MQ2);
  Serial.println("Pin mq2: ");
  Serial.print(analogMQ2);
  // Checks if it has reached the threshold value
  if (analogMQ2 > 300){ 
     if(onoff==1){
    if(mq2==0){ 
      digitalWrite(LEDMQ2, HIGH);
     
    tone(BUZZER, 1000, 3000);
 SIM900.print("AT+CMGF=1\r"); // AT command to send SMS message
 delay(1000);
SIM900.println("AT + CMGS = \"+2348133587431\""); // recipient's mobile number, in international format
delay(1000);
SIM900.println("HELLO HIGH SMOKE LEVEL"); // message to send
delay(1000);
SIM900.println((char)26); // End AT command with a ^Z, ASCII code 26
delay(1000);
SIM900.println();
digitalWrite(19, HIGH);
delay(5000); // give module time to send SMS
   mq2==1;
   digitalWrite(19, LOW);
   }
   else if(mq2==1){digitalWrite(LEDMQ2, HIGH);
    tone(BUZZER, 1000, 3000);}
   }
   if(onoff==0){
     digitalWrite(LEDMQ2, HIGH);
      digitalWrite(LEDMQ2, HIGH);
    tone(BUZZER, 1000, 3000);
   }
  }
     delay(10000);
     digitalWrite(LEDMQ2, LOW);
     callMonitor();
}  
  else
  {
    digitalWrite(LEDMQ2, LOW);
    noTone(BUZZER);
    callMonitor();
    mq2==0;
  } 
  }
