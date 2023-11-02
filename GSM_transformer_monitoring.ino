
 //MINOR PROJECT WORK

#include <Wire.h>
#include <LiquidCrystal.h>
#include<SoftwareSerial.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
SoftwareSerial SIM900(9, 10);


const int trigPin = 8; // Trigger Pin of Ultrasonic Sensor
const int echoPin = 7; // Echo Pin of Ultrasonic Sensor
long duration;
int OilLevel;
float currentValue;


int delayTime = 700;

int temp;
float TempSensorPin = A0;
float vout;



void setup() {
  // put your setup code here, to run once:
pinMode(TempSensorPin,INPUT);
pinMode(trigPin, OUTPUT);
pinMode(echoPin, INPUT);


 Serial.begin(9600);
 SIM900.begin(9600);
 delay(100);

Serial.println(" REMOTE TRANSFORMER MONITORING");  
lcd.begin(20,4);
lcd.print("PROJECT WORK");
lcd.setCursor(2,1);
lcd.print("REMOTE");
lcd.setCursor(9,1);
lcd.print("MONITORING");
lcd.setCursor(4,2);
lcd.print("TRANSFORMER");
delay (delayTime);
lcd.clear();

}

void loop() {



//temperature//
vout = analogRead(TempSensorPin);
vout = (vout * 500) / 1023;
temp = vout;


//CURRENT//
const int currentPin = A1;
int sensitivity = 185;
int adcValue= 0;
int offsetVoltage = 2500;
float adcVoltage = 0;
adcValue = analogRead(currentPin);
currentValue = analogRead(currentPin);
adcVoltage = (adcValue / 1024.0) * 5000;
currentValue = ((adcVoltage - offsetVoltage) / sensitivity);


// SENSING OIL LEVEL//
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
duration = pulseIn(echoPin, HIGH);
OilLevel = duration * 0.034 / 2;


//LCD PRINTING//
  
lcd.setCursor(0,0);
lcd.print("Temperature:");
lcd.setCursor(12,0);
lcd.print(temp);
lcd.setCursor(15,0);
lcd.print("C");

lcd.setCursor(0,1);
lcd.print("Oil Level:");
lcd.setCursor(10,1);
lcd.print(OilLevel);
lcd.setCursor(14,1);
lcd.print("CM");

lcd.setCursor(0, 2);
lcd.print("Current:");
lcd.setCursor(8, 2);
lcd.print(currentValue,2);
lcd.setCursor(13, 2);
lcd.print("A");
delay(300);

condition();

}

void sms()

{
SIM900.print("AT+CMGF=1\r"); 
SIM900.println("AT + CMGS = \"+918112304546\"");// recipient's mobile number
Serial.println("AT + CMGS = \"+918112304546\"");// recipient's mobile number
SIM900.println("HIGH TRANSFORMER TEMPERATURE"); // message to send
Serial.println("HIGH TRANSFORMER TEMPERATURE");
SIM900.println((char)26); // End AT command with a ^Z, ASCII code 26
Serial.println((char)26);
SIM900.println();
}

void sms1(){
SIM900.print("AT+CMGF=1\r"); 
SIM900.println("AT + CMGS = \"+918112304546\"");// recipient's mobile number
Serial.println("AT + CMGS = \"+918112304546\"");// recipient's mobile number
SIM900.println("OIL TANK FULL"); // message to send
Serial.println("OIL TANK FULL");
SIM900.println((char)26); // End AT command with a ^Z, ASCII code 26
Serial.println((char)26);
SIM900.println();

}

void sms2(){
SIM900.print("AT+CMGF=1\r"); 
SIM900.println("AT + CMGS = \"+918112304546\"");// recipient's mobile number
Serial.println("AT + CMGS = \"+918112304546\"");// recipient's mobile number
SIM900.println("LOW OIL LEVEL"); // message to send
Serial.println("LOW OIL LEVEL");
SIM900.println((char)26); // End AT command with a ^Z, ASCII code 26
Serial.println((char)26);
SIM900.println();
}

void sms3(){
SIM900.print("AT+CMGF=1\r"); 
SIM900.println("AT + CMGS = \"+918112304546\"");// recipient's mobile number
Serial.println("AT + CMGS = \"+918112304546\"");// recipient's mobile number
SIM900.println("FAULT Detected"); // message to send
Serial.println("FAULT Detected");
SIM900.println((char)26); // End AT command with a ^Z, ASCII code 26
Serial.println((char)26);
SIM900.println();

}

//CONDITIONS
void condition()
{
  if (temp > 75)
{
lcd_tempPrint();
sms();
 delay(300);
  
  }
  if (currentValue > 8.0)
{
lcd_faultPrint();
sms3();
 delay(1000);
  
  }
if (OilLevel > 800)
{
 lcd_oilLevelFULLPrint();
 sms1();
 
 delay(1000);
  }else if (OilLevel < 300)
{lcd_oilLevelLOWPrint();
 sms2();
 delay(300);
  }

   
}


// LCD PRINTING CONDITION//

void lcd_oilLevelFULLPrint()
{
lcd.clear();
lcd.setCursor(1,1);
lcd.clear();                                  //if condition temp for it to print.
lcd.print("OIL TANK FULL");  
 
}

void lcd_oilLevelLOWPrint()
{
lcd.clear();
lcd.setCursor(0,2);
lcd.clear();                                  //if condition temp for it to print.
lcd.print("OIL LEVEL LOW");  

}



void lcd_tempPrint()
{
lcd.clear();
lcd.setCursor(0,0);
lcd.clear();                                  //if condition temp for it to print.
lcd.print("HIGH TEMPERATURE");   
  
}


void lcd_faultPrint()
{
lcd.clear();
lcd.setCursor(0,0);
lcd.clear();                                  //if condition fault for it to print.
lcd.print("Fault detected");   
  
}




 
