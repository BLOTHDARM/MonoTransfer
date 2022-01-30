#include <SimpleTransmition.h>

// SimpleTransmition(arduino digital pin, speed (recommend 1000 and higher for atmega328 with 16 mhz crystal oscillator ), packet ending symbol)
SimpleTransmition Seriall(5,1000,'-');

void setup()
{
  Serial.begin(9600);
}


void loop()
{
  if(Seriall.available())
  {
    String data = Seriall.read();
    Serial.print("data: ");
    Serial.println(data);
  }
}
