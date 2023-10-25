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
