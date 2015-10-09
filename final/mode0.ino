int getprob()
{
  return 0;
}

bool getprob(int lim)
{
  int prob=0;
  prob=getprob();
  if (prob>=lim)
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
    if ((currDMois > setMois) && (currRMois > setMois))
    {
      runMois=true;
    }else if ((currDMois > setMois) || (currRMois > setMois))
    {
      runMois=getprob(75);
    }
    else
    {
      runMois=false;
    }
  }
}

void digestDHT()
{
  if (updateDHT)
  {
    updateDHT=!updateDHT;
    if ((currDTemp > setDTemp) || (currDHum > setDHum))
    {
      runDHT=getprob(25);
    }
    else
    {
      runDHT=false;
    }
  }
}

void do_run_relay()
{
  if (runMois || runDHT)
  {
    working_mode=8;
  }
}


void digestData()
{
  printData();
  digestMois();
  digestDHT();
  do_run_relay();
}
