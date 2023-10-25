#include <IRremote.hpp>

#define IRpin  2

#define IN1 7   // Left  wheel forward
#define IN2 8   // Left  wheel reverse
#define IN3 9   // Right wheel reverse
#define IN4 11  // Right wheel forward
#define ENB 5 // left wheel speed
#define ENA 6 // left wheel speed
#define carSpeed 255  // initial speed of car >=0 to <=255
#define carspeed2 255 // set forward and backward speed

String val;
int value = 0;
unsigned long preMillis;

void forward() {
  digitalWrite(ENA, carspeed2);
  digitalWrite(ENB, carspeed2);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  digitalWrite(3,HIGH);
  digitalWrite(4,HIGH);
  Serial.println("go forward!");
}

void back(){
  digitalWrite(ENA, carspeed2);
  digitalWrite(ENB, carspeed2);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  digitalWrite(12,HIGH);
  digitalWrite(4,HIGH);
  Serial.println("go back!");
}

void left(){
  analogWrite(ENA, carSpeed);
  analogWrite(ENB, carSpeed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  digitalWrite(4,HIGH);
  digitalWrite(12,HIGH);
  digitalWrite(3,HIGH);
  Serial.println("go left!");
}

void right(){
  analogWrite(ENA, carSpeed);
  analogWrite(ENB, carSpeed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  digitalWrite(4,HIGH);
  digitalWrite(12,HIGH);
  digitalWrite(3,HIGH);
  Serial.println("go right!");
}

void stop()
{
  digitalWrite(ENA, LOW);
  digitalWrite(ENB, LOW);
  digitalWrite(4,LOW);
  Serial.println("Stop!");
}

void setup() 
{
  Serial.begin(9600);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(12,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  stop();
  IrReceiver.begin(IRpin, ENABLE_LED_FEEDBACK);
}

void loop() {
  if (IrReceiver.decode()){ 
    preMillis = millis();
    Serial.println(IrReceiver.decodedIRData.decodedRawData, HEX);
    val = String(IrReceiver.decodedIRData.decodedRawData, HEX);
    Serial.println(val);
    IrReceiver.resume();
    
    if(val == "e41b7f80")//for 2 button remote
    {
      value = 1;
      Serial.println("Gaadi aage badh rahi hai");
    }
      
    if(val == "f00f7f80")// for 8 button remote
    {  
      value = 2;
      Serial.println("Gaadi piche ja rahi hai");
    }
    
    if(val == "f10e7f80")
    {
      value = 4;
      Serial.println("Gaadi Daye ja rahi hai");
    }
    
    if(val == "f30c7f80")
    {
      value = 3;
      Serial.println("Gaadi Baye ja rahi hai");
    }
    
    if(val == "ed127f80")
    {
      value = 5;
      Serial.println("Gaadi ruk gayi");
    }
    
    switch(value){
      case 1: forward();  break;
      case 2:    back();  break;
      case 3:    left();  break;
      case 4:   right();  break;
      case 5:    stop();  break;
      default:            break;
    }
  }
  else{
    if(millis() - preMillis > 150){
      stop();
      digitalWrite(12,LOW);
      digitalWrite(3,LOW);
      preMillis = millis();
    }
  }
}
