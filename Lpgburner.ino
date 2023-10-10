#include <LiquidCrystal.h>
const int rs = 12, en = 13, d4 = 7, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const int buttonPin = 8; 

int start = 0;

int thermistorPin = A1;
int Vo; // Holds the ADC Value
int lpg;
float tCelsius;


int lpgpin=A4;
int fanpin=6;
int airpin=5;
int glowpin=9;
int dujospin = 11; 


int tempsensor;
int fanspeed = 0;
int airspeed = 0;
int glow = 0;
int dujos =0;

unsigned long time;
unsigned long startMillis;  //some global variables available anywhere in the program
unsigned long currentMillis;
const unsigned long period = 10000;  //the value is a number of milliseconds


void setup() {
  Serial.begin(9600);
//TCCR0B = TCCR0B & B11111000 | B00000001;    // set timer 0 divisor to     1 for PWM frequency of 62500.00 Hz
//TCCR0B = TCCR0B & B11111000 | B00000010;    // set timer 0 divisor to     8 for PWM frequency of  7812.50 Hz
  TCCR0B = TCCR0B & B11111000 | B00000001;    // set timer 0 divisor to    64 for PWM frequency of   976.56 Hz (The DEFAULT)
//TCCR0B = TCCR0B & B11111000 | B00000100;    // set timer 0 divisor to   256 for PWM frequency of   244.14 Hz
//TCCR0B = TCCR0B & B11111000 | B00000101;    // set timer 0 divisor to  1024 for PWM frequency of    61.04 Hz
 
   pinMode(buttonPin, INPUT);
 pinMode(fanpin, OUTPUT);
  pinMode(airpin, OUTPUT);
 pinMode(glowpin, OUTPUT);
 pinMode(dujospin, OUTPUT);
startMillis = millis();
}

void loop() {
  Vo = analogRead(thermistorPin);
  lpg = analogRead(lpgpin);
  tCelsius = Vo / 5;
 
currentMillis = millis();

analogWrite(fanpin, fanspeed);
analogWrite(airpin, airspeed);
analogWrite(glowpin, glow);
analogWrite(dujospin, dujos);

start = digitalRead(buttonPin); // Reading input from Button Pin.

  if (start == 0) // Checking if Input from button is HIGH (1/+5V)
   {     

{    
if (currentMillis < 550000)glow = 255;
if (currentMillis > 550000)glow = 0;


}
{   
if (currentMillis < 500000)dujos = 0;
if (currentMillis > 500000)dujos = 170;


if (currentMillis < 2000000)fanspeed =  250;
if (currentMillis > 2000000)fanspeed = lpg * 6.7;


startMillis = currentMillis;

}





 if (fanspeed>255)fanspeed=255;
airspeed = tCelsius * 1.4;
 if (airspeed>255)airspeed=255;

   } 




  lcd.begin(16,2);
   lcd.setCursor(0, 0);
   lcd.print("C:");
   lcd.print(tCelsius);
 lcd.setCursor(9, 0); 
 lcd.print("Fan:");
   lcd.print(fanspeed);
   lcd.setCursor(0, 1); 
lcd.print("LPG:");
   lcd.print(lpg);
   lcd.setCursor(9, 1); 
lcd.print("Air:");
   lcd.print(airspeed);
  delay(14020);
}
