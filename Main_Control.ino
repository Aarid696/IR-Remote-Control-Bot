#include <IRremote.hpp> //This was the updated library

#define IRpin  12 // In some cases pin 12 does not work, try to change pin. Better to use PWM signal pins

#define IN1 7   // Left  wheel forward
#define IN2 8   // Left  wheel reverse
#define IN3 9   // Right wheel reverse
#define IN4 11  // Right wheel forward
#define ENB 5 // left wheel speed
#define ENA 6 // left wheel speed
#define carSpeed 100  // initial speed of car >=0 to <=255, you may change the speed while turning
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
  digitalWrite(2,HIGH);
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
  pinMode(2,OUTPUT); //This pin is for LED, to check for back command
  pinMode(3,OUTPUT); //This pin is for LED, to check for back command
  pinMode(4,OUTPUT); //This pin is for LED, to check for any command
  stop();
  IrReceiver.begin(IRpin, ENABLE_LED_FEEDBACK);
}

void loop() {
  if (IrReceiver.decode()){ 
    preMillis = millis();
    Serial.println(IrReceiver.decodedIRData.decodedRawData, HEX);
    val = String(IrReceiver.decodedIRData.decodedRawData, HEX); // command for receiving the values
    Serial.println(val); // for printing the values in serail monitor
    IrReceiver.resume();

    /* These if statements were written for the indirect comparisons of the data recieved from IR
    remote because in case were getting alphanumeric values, it may so happen that you might get 'long int' values. 
    In that case you can directly compare the results in 'switch' command*/
    
    if(val == "ee11bf00") // the code may change in your case, check it by running decoder program
      value = 1;
    if(val == "e619bf00") // the code may change in your case, check it by running decoder program
      value = 2;
    if(val == "eb14bf00") // the code may change in your case, check it by running decoder program
      value = 3; 
    if(val == "e916bf00") // the code may change in your case, check it by running decoder program
      value = 4;
    if(val == "ff00bf00") // the code may change in your case, check it by running decoder program
      value = 5; // No need of this command you can skip it
    
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
      digitalWrite(2,LOW);
      digitalWrite(3,LOW);
      preMillis = millis();
    }
  }
}
