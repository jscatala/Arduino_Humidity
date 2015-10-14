void humidity_setup()
{
  if (data_printed)
  {
    data_printed=!data_printed;
    printData("Valor Humedad:",1,0,0);
    if (humidity_lim>100)
    {
      printData(String(humidity_lim),0,5,1);
    }else
    {
      printData(String(humidity_lim),0,6,1);
    }
  }
  
  countdown();
  if (downcnt>=3000)
  {
    downcnt=0;
    if (humidity_lim>0)
    {
      data_printed=true;
      humidity_lim= humidity_lim-2;
      setDHum=((humidity_lim*6)/95)+20;
      t_mode=millis();
      Serial.print("Humidity down  ");
      Serial.println(humidity_lim);
      Serial.println(setDHum);
    }    
  }
  
  countup();
  if (upcnt>3000)
  {
    upcnt=0;
    if (humidity_lim<950)
    {
      data_printed=true;
      humidity_lim= humidity_lim+2;                      
      setDHum=((humidity_lim*6)/95)+20;
      t_mode=millis();
      Serial.print("Humidity up  ");
      Serial.println(humidity_lim);
      Serial.println(setDHum);
    }          
  }
}
