#include <LiquidCrystal.h>
#include <Servo.h>
Servo myservo;
LiquidCrystal lcd(12,11,5,4,3,2);
const int trigPin = 9;
const int echoPin = 10;
const int trigPin1 = A2;
const int echoPin1= A3;
// defines variables
long Duration;
int distance;
long Duration1;
int distance1;
void setup() {
  // put your setup code here, to run once:
lcd.begin(16,2);
pinMode(6,INPUT);//IR 1(hand sensor)
pinMode(7,INPUT);//IR 2(gate sensor)
pinMode(13,OUTPUT);//Relay
myservo.attach(A1);
 pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  Serial.begin(9600); // Starts the serial communication
pinMode(A0,OUTPUT);
pinMode(trigPin1, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin1, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
analogWrite(A0,73);
//sonar inside
digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  Duration = pulseIn(echoPin1, HIGH);
  // Calculating the distance
  distance = Duration * 0.034 / 2;
  // Prints the distance on the Serial Monitor

  //sonar hands
digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  Duration1 = pulseIn(echoPin1, HIGH);
  // Calculating the distance
  distance1 = Duration1 * 0.034 / 2;
  // Prints the distance on the Serial Monitor
Serial.print("Distance: ");
Serial.println(distance1);

lcd.clear();
lcd.setCursor(0,0);
lcd.print("Sanitization");
  if(distance<=15){delay(100);
 lcd.setCursor(0,1);
    lcd.print("Opening ");   
    int a=0;
  for(a;a<=90;a++){
     myservo.write(a);
    }
      }
if(distance < 30){
    delay(5000);
    int i=90;
  for(i;i>=0;i--){
        myservo.write(i);
 digitalWrite(13,HIGH);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Sanitization");
     lcd.setCursor(0,1);
    lcd.print("In Progress");
    delay(5000);
  digitalWrite(13,LOW);
  int a=0;
  for(a;a<=90;a++){
     myservo.write(a);
    }
     lcd.setCursor(0,1);
    lcd.print("Completed");
    delay(2000);
    lcd.clear();
}}}
