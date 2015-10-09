void readSensors()
{
  //####### Humidity  #########
  
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
}
