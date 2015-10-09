void relay_setup()
{
  //Serial.println("Setup Relay timer");
  
  countdown();
  if (downcnt>=3000)
  {
    downcnt=0;
    if (t_relay_on>=1)
    {
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
      t_relay_on++;                      
      t_mode=millis();
      Serial.print("Relay up  ");
      Serial.println(t_relay_on);
    }          
  }
}
