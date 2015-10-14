int get_perc(int r, int c)
{
  int perc;
  perc=(c*100)/r;
  return perc;
}

void turn_leds(int i, int d, int val, int hum)
{
  if (hum)
  {
    Serial.println(String(val));
    val=val-100;
    Serial.println(String(val));
  }
  if (val <= 25 )
  {
    modeLeds[i]=2; modeLeds[d]=0;
  }else if (val> 25 && val <= 50)
  {
    modeLeds[i]=1; modeLeds[d]=0;
  }else if (val> 50 && val <=75)
  {
    modeLeds[i]=0; modeLeds[d]=1;
  }else
  {
    modeLeds[i]=1; modeLeds[d]=1;
  }
}

void get_hum_leds()
{
  //0,1
  int val=(currDMois+currRMois)/2;
  Serial.println("Get hum leds");
  Serial.println(String(humidity_lim));
  Serial.println(String(val));
  turn_leds(0,1,get_perc(humidity_lim, val),1);
}

void get_dht_leds()
{
  //2,3
  turn_leds(2,3,get_perc(setDTemp, currDTemp),0);
}

void readSensors()
{
  //####### Humidity  #########
  
  currDMois=analogRead(soil1_pin);
  currRMois=analogRead(soil1_pin);
  if (oldDMois != currDMois)
  {
    oldDMois=currDMois;
    updateMois=1;
  }
  if (oldDMois != currDMois)
  {
    oldRMois=currRMois;
    updateMois=1;
  }
  
  //########## DHT ############ 
  DHT.read11(dht_pin);
  currDHum=DHT.humidity;
  currDTemp=DHT.temperature;
  if (oldDHum != currDHum)
  {
    oldDHum=currDHum;
    updateDHT=1;
  }
  if (oldDTemp != currDTemp)
  {
    oldDTemp=currDTemp;
    updateDHT=1;
  }
  
  get_hum_leds();
  get_dht_leds();
}
