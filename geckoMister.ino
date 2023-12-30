#include <Servo.h>

Servo servo;

int times = 0;

void setup() {
  // put your setup code here, to run once:

  servo.attach(3);

  Serial.begin(9600);
}

void loop() {
  mist();
  mist();
  mist();
  delay(3600000);

  times++;
  Serial.println(times);
}

void mist(){
  // put your main code here, to run repeatedly:
  servo.write(0);

  delay(1000);

  servo.write(180);

  delay(1000);
  
  servo.write(0);
}
