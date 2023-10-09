
#include <Servo.h>
Servo myservo;  

int lpg = 10;
int spark = 6;
int combustion_air = 5;
int fan = 11;
int time = 0;
int button = 8;
int button_state;
int sensor = A1;
int temp_sensor = A5;
int sensor_data;
int temp;
int temp_val;
int comb_speed;
int movee;
int hasrun = 0;
int hasrun2 = 0;
int startup_mixture = 10;
int runin_mixture = 45;
int startrun = 0;

unsigned long myTime;


void setup() {
Serial.begin(9600);
TCCR2B = TCCR2B & B11111000 | B00000001; // for PWM frequency of 31372.55 Hz
pinMode(button, INPUT);
pinMode(spark, OUTPUT);
pinMode(combustion_air, OUTPUT); 
pinMode(fan, OUTPUT); 
pinMode(sensor, INPUT); 
pinMode(temp_sensor, INPUT);
pinMode(lpg, OUTPUT); 
myservo.attach(9);

}

void loop() {
myTime = millis();
time = myTime / 1000;





float button_state = digitalRead(button);
float sensor_data = analogRead(sensor);
float temp = analogRead(temp_sensor);
float temp_val = temp / 3.5;

comb_speed = sensor_data + 43;
movee =  sensor_data / 8 ;


if (comb_speed >= 255)comb_speed = 255; 
if (comb_speed >= 255)comb_speed = 255;  
if (comb_speed <= 88)comb_speed = 88;  
if (sensor_data > 260)myservo.write(43); 
if (button_state == 1)hasrun = 0; 

if ((button_state == 1) && (hasrun2 == 0))
{
analogWrite(lpg, 255);
analogWrite(spark, 255);
analogWrite(combustion_air, 160);
myservo.write(startup_mixture);  
hasrun2 = 1;
delay(8000);
startrun = 1;

}
else if ((startrun = 1) && (button_state == 1))
{
analogWrite(spark, 0);
analogWrite(fan, temp_val);
analogWrite(combustion_air, comb_speed);
myservo.write(movee); 
}



else if (button_state == 0)//cooldown state//
{
analogWrite(spark, 0);
analogWrite(lpg, 0);
analogWrite(fan, 120);
analogWrite(combustion_air, 155);
hasrun2 = 0;
startrun = 0;
}
else
{
analogWrite(spark, 0);
analogWrite(combustion_air, 0);
analogWrite(fan, 0);
analogWrite(lpg, 0);
myservo.write(0);

}

Serial.println(button_state);
Serial.println(time);
Serial.print("sensor_data: ");
Serial.println(sensor_data);
Serial.print("servo: ");
Serial.println(movee);
Serial.print("comb_air: ");
Serial.println(comb_speed);
Serial.print("raw_temp: ");
Serial.println(temp);
Serial.print("fan_duty: ");
Serial.println(temp_val);
delay(400);

}
