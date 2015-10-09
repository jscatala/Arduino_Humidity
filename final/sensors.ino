void readSensors()
{
  DHT.read11(dht_pin);
  currDHum=DHT.humidity;
  currDTemp=DHT.temperature;
  if (oldDHum != currDHum)
  {
    oldDHum=currDHum;
    updateVals=1;
  }
  if (oldDTemp != currDTemp)
  {
    oldDTemp=currDTemp;
    updateVals=1;
  }
}
