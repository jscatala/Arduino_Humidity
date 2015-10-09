void doLeds()
{
  int i;
  char sync=-1;
  for (i=0;i<4;i++)
  {

    switch (modeLeds[i]) {
        case 0:
           digitalWrite(pinLeds[i], LOW);
           break;
        case 1:
            digitalWrite(pinLeds[i], HIGH);
          break;
        case 2:
          if(sync!=HIGH && sync!=LOW)
          {
            sync=digitalRead(pinLeds[i]);
          }
          currmillisLeds[i]=millis();
          if(currmillisLeds[i] - prevmillisLeds[i] > 300)
          {
            prevmillisLeds[i] = currmillisLeds[i];
            if(digitalRead(pinLeds[i])==LOW && sync==LOW)
            {
              digitalWrite(pinLeds[i], HIGH);
            }else
            {
              digitalWrite(pinLeds[i], LOW);
            }
          }
          break;
        default:
          continue;
    }
  }
}

void humidity_lights()
{
  //pinLeds[0]->RED  pinLeds[1]->BLUE
  modeLeds[0]=2;
  modeLeds[1]=2;
}

void dht_lights()
{
  //pinLeds[2]->YELLOW  pinLeds[3]->GREEN
  modeLeds[2]=2;
  modeLeds[3]=2;
}

void relay_lights()
{
  setallLeds(2);
}

void relay_running_lights()
{
  modeLeds[curr_led_on]=1;
  unsigned long tmp_lights_on_curr=millis();
  if (tmp_lights_on_curr - tmp_lights_on > 3000)
  {
    curr_led_on=(curr_led_on+1)%5;
    if (curr_led_on==0)
    {
      setallLeds(0);
      doLeds();
    }
    tmp_lights_on=tmp_lights_on_curr;
  }
}

void setallLeds(int mode)
{
  for (int i=0; i<4;i++)
  {
    modeLeds[i]=mode;
  }
}

void blinkStatic(int timeOn, int timeOff, int times)
{
  for(int i=0; i<times; i++)
  {
    for (i=0; i<4; i++ )
    {
      if (modeLeds[i] != 0 )
      {
        digitalWrite(pinLeds[i], HIGH);
      }
    }
    delay(timeOn);
    for (i=0; i<4; i++ )
    {
      if (modeLeds[i] != 0 )
      {
        digitalWrite(pinLeds[i], LOW);
      }
    }
    delay(timeOff);
  }
}
