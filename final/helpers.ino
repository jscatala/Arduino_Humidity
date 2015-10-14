void printData(String data, int cCursor, int lCursor, int rCursor)
{
  if(cCursor)
  {
    lcd.clear();
    Serial.println();
    Serial.println();
  }

  lcd.setCursor(lCursor,rCursor); //Start at character 4 on line 0
  lcd.print(data);
  Serial.println(data);
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
  //#######Moisture Data ########
  currDMois=0;
  currRMois=0;
  oldDMois=0;
  oldRMois=0;
  humidity_lim=500;
  
  //######## DHT Data ###########
  currDTemp=0;
  currDHum=0;
  oldDTemp=0;
  oldDHum=0;
  setDTemp=30; //0-50
  setDHum=52;  //20-80 . 
}
