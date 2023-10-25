#include <IRremote.hpp>
int IRpin = 2;
void setup()
{
  Serial.begin(9600);
  IrReceiver.begin(IRpin, ENABLE_LED_FEEDBACK);
}
void loop() 
{   
  if (IrReceiver.decode()) 
    {
     Serial.println(IrReceiver.decodedIRData.decodedRawData, HEX);
     IrReceiver.printIRResultShort(&Serial);
     IrReceiver.resume();
    }
}

//E41B7F80 for 2
//F30C7F80 for 4
//F00F7F80 for 8
//F10E7F80 for 6
//ED127F80 for power stop
