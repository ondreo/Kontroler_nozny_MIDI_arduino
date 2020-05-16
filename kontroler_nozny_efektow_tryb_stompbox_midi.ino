void midi_message(int cmd, int pitch, int velocity)
{
  Serial.write(cmd);
  Serial.write(pitch);
  Serial.write(velocity);
}

bool buttonPushed[55];
bool ef[55];
int cc[55];

void setup()
{
  //Serial.begin(115200);//for usb_midi
  Serial.begin(31250);//for midi
  for(int i=30;i<40;++i)
  {
    pinMode(i, INPUT_PULLUP);
    buttonPushed[i]=ef[i]=0;
    pinMode(i+10, OUTPUT);
    digitalWrite(i+10,LOW);
    
  }
  //cc[30]
  cc[31]=22;//stompbox
  cc[32]=65;//chorus/mod
  cc[33]=73;//delay
  cc[34]=89;//reverb
  cc[35]=16;//whammy/IPS on/off
  cc[36]=17;//whammy/IPS type
  //cc[37]
  //cc[38]
  //cc[39]
}

void loop()
{
  for(int i=30;i<40;++i)
  {
    if (digitalRead(i)==HIGH)
    {
      if(buttonPushed[i]==0)
      {
        if(ef[i]==false)
        {
          if(i==36)
          {
            midi_message(0xB1,cc[i],40);
            midi_message(0xB1,19,33);//param1 -12 semitones
          }
          else if(i!=30&&i!=37&&i!=38&&i!=39)midi_message(0xB1,cc[i],127);
          digitalWrite(i+10,HIGH);
        }
        else 
        {
          if(i==36)
          {
            midi_message(0xB1,19,45);//param1 -5??
          }
          else if(i!=30&&i!=37&&i!=38&&i!=39)midi_message(0xB1,cc[i],0);
          digitalWrite(i+10,LOW);
        }
        ef[i]=!ef[i];
      }
      delay(50);
      buttonPushed[i]=1;
    }
    else 
      buttonPushed[i]=0;
  }
}
