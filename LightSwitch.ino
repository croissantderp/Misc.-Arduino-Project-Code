#include <Servo.h>

Servo servo;
int isOn = LOW;

int On = 130;
int Off = 50;

bool overrideHeld = false;
bool manual = false;
bool manualHeld;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  pinMode(4, INPUT);
  pinMode(3, INPUT);
  pinMode(2, INPUT);

  pinMode(6, OUTPUT);
  
  servo.attach(5);
}

void loop() {
  // put your main code here, to run repeatedly:

  if (digitalRead(2) == HIGH && !manualHeld) {
    if (manual == true){
      manual = false;
      digitalWrite(6, LOW);
      Serial.println("manual pressed OFF");

      manualHeld = true;
      
      if (isOn == HIGH){
        autoShutOff();
      }
    }
    else {
      manual = true;
      digitalWrite(6, HIGH);
      Serial.println("manual pressed ON");
    }
    
    manualHeld = true;
  }
  else if (digitalRead(2) == LOW) {
    delay(50);
    manualHeld = false;
  }

  
  if (digitalRead(4) == HIGH && !overrideHeld && isOn == LOW) {
    Serial.println("override pressed ON");
    servo.write(On);
    isOn = HIGH;
    overrideHeld = true;

    if (!manual){
      autoShutOff();
    }
  }
  else if (digitalRead(4) == LOW){
    delay(50);
    overrideHeld = false;
  }

  if (!manual){
    if (digitalRead(3) == HIGH){
      Serial.println("movement detected");
      servo.write(On);
      isOn = HIGH;
      autoShutOff();
    }
  }

  if (digitalRead(4) == HIGH && !overrideHeld && isOn == HIGH){
    Serial.println("override pressed OFF");
    servo.write(Off);
    isOn = LOW;
    overrideHeld = true;
  }
}

void autoShutOff() {
  for (int i = 0; i < 600; i++){
    delay(100);
    if (digitalRead(3) == HIGH) {
      Serial.println("movement detected again");
      i = 0;
    }
    else {
      Serial.println("still no movement detected");
    }
    
    if (digitalRead(4) == HIGH && !overrideHeld) {
      Serial.println("override pressed OFF");
      servo.write(Off);
      isOn = LOW;
      overrideHeld = true;
      return;
    }
    else if (digitalRead(4) == LOW){
      delay(50);
      overrideHeld = false;
    }
    
    if (digitalRead(2) == HIGH && !manualHeld) {
      Serial.println("manual pressed ON");
      manual = true;
      digitalWrite(6, HIGH);
      manualHeld = true;
      return;
    }
    else if (digitalRead(2) == LOW){
      delay(50);
      manualHeld = false;
    }
  }
  
  Serial.println("no movement detected for a minute, shutting off");
  servo.write(Off);
  isOn = LOW;
}
