#include <IRremote.h>
#include <Servo.h>

const int RECV_PIN = 3;
IRrecv irrecv(RECV_PIN);
decode_results results;
unsigned long key_value = 0;
int yes = 5;

Servo servo1;

void setup(){
  Serial.begin(9600);
  irrecv.enableIRIn();
  irrecv.blink13(true);
  servo1.attach(yes);
}

void loop(){
  if (irrecv.decode(&results)){
 
        if (results.value == 0XFFFFFFFF)
          results.value = key_value;

        switch(results.value){
          case 0xFFA25D:
            Serial.println("OFF");
            servo1.write(70);
            delay(2000);
            servo1.write(90);
            break;
          case 0xFF629D:
            Serial.println("ON");
            servo1.write(110);
            delay(2000);
            servo1.write(90);
            break;
        }
        key_value = results.value;
        irrecv.resume(); 
  }
}
