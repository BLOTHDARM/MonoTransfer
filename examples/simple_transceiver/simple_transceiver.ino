#include <MonoTransfer.h>

// SimpleTransmition(arduino digital pin, speed (recommend 1000 and higher for atmega328 with 16 mhz crystal oscillator ), packet ending symbol)
MonoTransfer Seriall(5,1000,'-');

void setup()
{
  Serial.begin(9600);
}


void loop()
{
  Seriall.send("Test message");
  Serial.println("Test message");
  delay(500);
}
