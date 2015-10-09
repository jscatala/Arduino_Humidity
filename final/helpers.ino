void printData()
{
  
}

void countup()
{
  if (valueup == LOW)
  {
    upcnt++;
  }
}

void countdown()
{
  if (valuedown == LOW)
  {
    downcnt++;
  }
}

//################# SETTER  ################################
void setLeds()
{
  pinMode(LED_BLUE, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);

  modeLeds[0]=1;
  blinkStatic(600,300,4);
  modeLeds[0]=0; modeLeds[1]=1;
  blinkStatic(600,300,4);
  modeLeds[1]=0; modeLeds[2]=1;
  blinkStatic(600,300,4);
  modeLeds[2]=0; modeLeds[3]=1;
  blinkStatic(600,300,4);
  modeLeds[0]=1; modeLeds[1]=1; modeLeds[2]=1; modeLeds[3]=1;
  blinkStatic(600,300,4);
  setallLeds(0);
}

void setValues()
{
  //######## DHT Data ###########
  currDTemp=0;
  currDHum=0;
  oldDTemp=0;
  oldDHum=0;
  setDTemp=30;
  setDHum=450;
  
  //#######Moisture Data ########
  currDMois=0;
  currRMois=0;
  oldDMois=0;
  oldRMois=0;
  setMois=500;
  
}
