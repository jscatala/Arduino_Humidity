int getprob_int()
{
  int i=random(0, 100);
  return i;
}

bool getprob(int lim)
{
  int prob=0;
  prob=getprob_int();
  Serial.println(String(prob));
  if (lim>=prob)
  {
    return true;
  }
  return false;
}

void digestMois()
{
  if (updateMois)
  {
    updateMois=!updateMois;
    Serial.println("mois");
    Serial.println(String(currDMois));
    Serial.println(String(currRMois));
    Serial.println(String(humidity_lim));
    if ((currDMois < humidity_lim) && (currRMois < humidity_lim))
    {
      runMois=true;
    }else if ((currDMois < humidity_lim) || (currRMois < humidity_lim))
    {
      runMois=getprob(75);
    }
    else
    {
      runMois=false;
    }
    Serial.print("runMois");
    Serial.println(String(runMois));
  }
}

void digestDHT()
{
  if (updateDHT)
  {
    Serial.println("DHT");
    Serial.println(String(setDTemp));
    Serial.println(String(setDHum));
    updateDHT=!updateDHT;
    if ((currDTemp > setDTemp) || (currDHum > setDHum))
    {
      Serial.println("probabilidad");
      runDHT=getprob(25);
    }
    else
    {
      runDHT=false;
    }
    Serial.print("runDHT");
    Serial.println(String(runDHT));
  }
}

void do_run_relay()
{
  if (runMois || runDHT)
  {
    working_mode=8;
  }
}


void outputData()
{
  if (updateMois || updateDHT)
  {
    Serial.println("asdf");
    printData("HT1:",1,0,0);
    printData(String(currDMois),0,4,0);
    printData("HT2:",0,8,0);
    printData(String(currRMois),0,12,0);
    printData("HA:%",0,0,1);
    printData(String(currDHum),0,4,1);
    printData("TA:C",0,8,1);
    printData(String(currDTemp),0,12,1);
    digestMois();
    digestDHT();
    updateDHT=0;
    updateMois=0;
  }
}

void digestData()
{
  outputData();
  do_run_relay();
}
