void dht_setup()
{
  if (data_printed)
  {
    data_printed=!data_printed;
    printData("Temperatura:",1,0,0);
    if (setDTemp>9)
    {
      printData(String(setDTemp),0,4,1);
    }else
    {
      printData(String(setDTemp),0,4,1);
    }
      printData(String("Grad C"),0,9,1);
  }
  
  countdown();
  if (downcnt>=3000)
  {
    downcnt=0;
    if (setDTemp>0)
    {
      data_printed=true;
      setDTemp=setDTemp-1;
      t_mode=millis();
      Serial.print("Temp down  ");
      Serial.println(setDTemp);
    }    
  }
  
  countup();
  if (upcnt>3000)
  {
    upcnt=0;
    if (setDTemp<51)
    {
      data_printed=true;
      setDTemp=setDTemp+1;                      
      t_mode=millis();
      Serial.print("Temp up  ");
      Serial.println(setDTemp);
    }          
  }
}

