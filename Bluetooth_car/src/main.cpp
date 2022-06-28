#include <Arduino.h>
#include <SoftwareSerial.h>

SoftwareSerial bluetooth(2, 3);

byte led = 13;
byte M1 = 4, M2 = 5, M3 = 6, M4 = 7;
char value;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  bluetooth.begin(9600);
  pinMode(led, OUTPUT);

  pinMode(M1,OUTPUT);   //left motors forward
  pinMode(M2,OUTPUT);   //left motors reverse
  pinMode(M3,OUTPUT);   //right motors forward
  pinMode(M4,OUTPUT);   //right motors reverse
}

void loop() {
  // put your main code here, to run repeatedly:
  if (bluetooth.available() > 0){
    value = bluetooth.read();
    Serial.println(value);
  }

  if(value == 'F'){            //move forward(all motors rotate in forward direction)
    digitalWrite(M1, HIGH);
    digitalWrite(M3, HIGH);
    digitalWrite(M2, LOW);
    digitalWrite(M4, LOW);
  }
  
  else if(value == 'B'){      //move reverse (all motors rotate in reverse direction)
    digitalWrite(M2,HIGH);
    digitalWrite(M4,HIGH);
    digitalWrite(M1, LOW);
    digitalWrite(M3, LOW);
  }
  
  else if(value == 'L'){      //turn right (left side motors rotate in forward direction, right side motors doesn't rotate)
    digitalWrite(M3, HIGH);
    digitalWrite(M2, LOW);
    digitalWrite(M4, LOW);
    digitalWrite(M1, LOW);
  }
  
  else if(value == 'R'){      //turn left (right side motors rotate in forward direction, left side motors doesn't rotate)
    digitalWrite(M1, HIGH);
    digitalWrite(M3, LOW);
    digitalWrite(M2, LOW);
    digitalWrite(M4, LOW);
  }
  
  else if(value == 'S'){      //STOP (all motors stop)
    digitalWrite(M1,LOW);
    digitalWrite(M2,LOW);
    digitalWrite(M3,LOW);
    digitalWrite(M4,LOW);
  }
}