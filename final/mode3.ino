void relay_setup()
{
  if (data_printed)
  {
    data_printed=!data_printed;
    printData("Valor Bomba:",1,0,0);
    if (humidity_lim>9)
    {
      printData(String(t_relay_on),0,5,1);
      printData("min.",0,8,1);
    }else
    {
      printData(String(t_relay_on),0,6,1);
      printData("min.",0,8,1);
    }
  }
  
  countdown();
  if (downcnt>=3000)
  {
    downcnt=0;
    if (t_relay_on>1)
    {
      data_printed=true;
      t_relay_on--;
      t_mode=millis();
      Serial.print("Relay down  ");
      Serial.println(t_relay_on);
    }    
  }
  
  countup();
  if (upcnt>3000)
  {
    upcnt=0;
    if (t_relay_on<61)
    {
      data_printed=true;
      t_relay_on++;                      
      t_mode=millis();
      Serial.print("Relay up  ");
      Serial.println(t_relay_on);
    }          
  }
}
