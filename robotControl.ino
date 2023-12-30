#include <Servo.h>

int thrPin = 9;
int strPin = 10;
int auxPin = 6;
int weaponSpeed = 1000;

Servo motorL;
Servo motorR;
Servo motorW;

void setup() {
  // put your setup code here, to run once:
  pinMode(thrPin, INPUT);
  pinMode(strPin, INPUT);
  pinMode(auxPin, INPUT);

  motorL.attach(11);
  motorR.attach(12);
  motorW.attach(5);
  
  Serial.begin(9600);
  Serial.write("initialized...\n");
}

void loop() {
  int throttle = pulseIn(thrPin, HIGH);
  int steering = pulseIn(strPin, HIGH);

  int leftSpeed = map(throttle, 1000, 1950, 1000, 2000);
  int rightSpeed = map(throttle, 1000, 1950, 1000, 2000);

  leftSpeed = constrain(leftSpeed + map(steering, 1000, 2000, -200, 200), 1000, 2000);
  rightSpeed = constrain(rightSpeed - map(steering, 1000, 2000, -200, 200), 1000, 2000);

  leftSpeed = ((leftSpeed + 5) / 10) * 10;
  rightSpeed = ((rightSpeed + 5) / 10) * 10;


  motorL.writeMicroseconds(leftSpeed);
  motorR.writeMicroseconds(rightSpeed);

  int weaponIn = pulseIn(auxPin, HIGH);

  if (weaponIn < 1100){
    weaponSpeed += 20;
  }
  else if (weaponIn < 1800) {
    weaponSpeed -= 20;
  }

  weaponSpeed = constrain(weaponSpeed, 1000, 2000);

  motorW.writeMicroseconds(weaponSpeed);

  Serial.print("leftSpeed: ");
  Serial.print(leftSpeed); 
  Serial.print(" rightSpeed: ");
  Serial.print(rightSpeed);
  Serial.print(" weaponSpeed: ");
  Serial.print(weaponSpeed);
  Serial.print("\n");

  delay(20);
}
