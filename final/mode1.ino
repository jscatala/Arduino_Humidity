void humidity_setup()
{
//  Serial.println("Setup Humidity Sensor");
  
  countdown();
  if (downcnt>=3000)
  {
    downcnt=0;
    if (humidity_lim>0)
    {
      humidity_lim= humidity_lim-2;
      t_mode=millis();
      Serial.print("Humidity down  ");
      Serial.println(humidity_lim);
    }    
  }
  
  countup();
  if (upcnt>3000)
  {
    upcnt=0;
    if (humidity_lim<950)
    {
      humidity_lim= humidity_lim+2;                      
      t_mode=millis();
      Serial.print("Humidity up  ");
      Serial.println(humidity_lim);
    }          
  }
}
