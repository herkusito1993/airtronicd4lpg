


int motorControl=9;
int voltpin = A4;


int speed = 0;
int volt; 


int voltai;




void setup() {
 pinMode(motorControl, OUTPUT);
  // set up the LCD's number of columns and rows:


}


void loop() {
volt = analogRead(voltpin);


float voltai = volt / 20;

speed=volt / 3.5;
if (voltai>31)speed=volt / 2;
if (voltai<24)speed=30;



if (speed>255)speed=255;



analogWrite(motorControl, speed);
  



}