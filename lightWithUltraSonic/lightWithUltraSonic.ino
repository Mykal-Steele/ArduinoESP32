#include <ESP32Servo.h>


const byte trig = 23;
const byte echo = 22;
Servo myServo;

void setup() {
  // put your setup code here, to run once:
  pinMode(18, OUTPUT);
  pinMode(19, OUTPUT);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  myServo.attach(13); 
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(trig, LOW);
  delay(20);  // Allow sensor to reset
  digitalWrite(trig, HIGH);
  delay(10);  // Pulse duration
  digitalWrite(trig, LOW);

  unsigned long duration = pulseIn(echo, HIGH); 
  
  int distance = duration * 0.034 / 2;  
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  if(distance <= 10){
    myServo.write(90); // Add missing semicolon
    digitalWrite(18, HIGH);
    digitalWrite(19, LOW);
  } else {
    myServo.write(0); // Add missing semicolon
    digitalWrite(18, LOW);
    digitalWrite(19, HIGH);
  }

  delay(100);  // Add delay to stabilize servo response
}
