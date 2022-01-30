#include "MonoTransfer.h"

int MonoTransfer::fromBinToDec(String value)
{
    int base = 2;
    int lengh = value.length() +1;
    char valueAsArray[lengh];
    value.toCharArray(valueAsArray, lengh);
    return strtol(valueAsArray, NULL, base);
}

MonoTransfer::MonoTransfer()
{
  pinMode(this->Pin,INPUT);
}

MonoTransfer::MonoTransfer(int Port,int Com_speed,char End_symbol)
{
  this->Pin=Port;
  pinMode(this->Pin,INPUT);
  this->end_symbol = End_symbol;
  this->com_speed = Com_speed;
}


void MonoTransfer::send(String data)
{
  data+=this->end_symbol;
  for(int j=0;j<data.length();++j)
  {
    int count=0;
    int n = data[j];
    for(count=0;n>0;++count)
      n = n/2;

    pinMode(this->Pin,OUTPUT);
    digitalWrite(this->Pin,HIGH);
    delayMicroseconds(this->com_speed);
    digitalWrite(this->Pin,LOW);
    delayMicroseconds(this->com_speed);

    for(int i=0;i<8-count;++i)
      delayMicroseconds(this->com_speed/2);

    n = data[j];
    String temp="";
    while(n>0)
    {
      if(n%2)
        temp+="1";
      else
        temp+="0";
      n = n/2;
    }

    for(int i=temp.length()-1;i>=0;--i)
    {
      if(temp[i]=='1')
        digitalWrite(this->Pin,HIGH);
      else
        digitalWrite(this->Pin,LOW);
      delayMicroseconds(this->com_speed/2);
    }

    delayMicroseconds(this->com_speed/4);
  }


  pinMode(this->Pin,INPUT);
  delay(5);
}


bool MonoTransfer::available()
{
  if(digitalRead(this->Pin))
    return true;
  return false;
}


String MonoTransfer::read()
{
  String data="";
  String temp="";
  if(this->available())
  {
    byte count=0;
    unsigned long timer;
    while(true)
    {
      temp="";
      count++;
      if(count>100)
        break;
      if(digitalRead(this->Pin))
      {
        while(digitalRead(this->Pin))
          continue;
        delayMicroseconds(this->com_speed*1.25);
        for(int i=0;i<8;++i)
        {
          if(digitalRead(this->Pin)){
            temp+='1';
            timer = micros();
            while(((unsigned)(micros()-timer))<(this->com_speed/2)){
              if(!digitalRead(Pin)){
                delayMicroseconds(this->com_speed/4);
                break;
              }
            }
          }
          else{
            temp+='0';
            timer = micros();
            while(((unsigned)(micros()-timer))<(this->com_speed/2)){
              if(digitalRead(this->Pin)){
                delayMicroseconds(this->com_speed/4);
                break;
              }
            }
          }
        }
        if(temp=="00000000")
          continue;
        int tempp=this->fromBinToDec(temp);
        if ((char)tempp == this->end_symbol){
          while(digitalRead(this->Pin))
            continue;
          return data;
        }
        data+=String((char)tempp);
      }
      delayMicroseconds(this->com_speed/2);
    }
    while(digitalRead(this->Pin))
          continue;
    return data;
  }
  return "Error";
}


void MonoTransfer::end(){
  pinMode(this->Pin,INPUT);
}
