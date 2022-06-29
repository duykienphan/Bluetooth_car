#include <Arduino.h>
#include <SoftwareSerial.h>

SoftwareSerial bluetooth(2, 3);

byte led = 13;
byte M1 = 4, M2 = 5, M3 = 6, M4 = 7;
char value;

void motor(byte status1, byte status2, byte status3, byte status4){
  digitalWrite(M1, status1);
  digitalWrite(M2, status2);
  digitalWrite(M3, status3);
  digitalWrite(M4, status4);
}

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
    motor(1, 0, 1, 0);
  }
  
  else if(value == 'B'){      //move reverse (all motors rotate in reverse direction)
    motor(0, 1, 0, 1);
  }
  
  else if(value == 'L'){      //turn right (left side motors rotate in forward direction, right side motors doesn't rotate)
    motor(0, 0, 1, 0);
  }
  
  else if(value == 'R'){      //turn left (right side motors rotate in forward direction, left side motors doesn't rotate)
    motor(1, 0, 0, 0);
  }
  
  else if(value == 'S'){      //STOP (all motors stop)
    motor(0, 0, 0, 0);
  }
}