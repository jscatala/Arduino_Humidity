void relay_turn_on()
{ 
  int curr_min;
  if (!relay_on)
  {
    lights_relay_on=true;
    t_relay=millis();
    relay_on=!relay_on;
    digitalWrite(RELAY,HIGH);
  }else
  {
    unsigned long t_relay_curr=millis();
    if (t_relay_curr - t_relay > (t_relay_on *60000))
    {
      last_min=61;
      working_mode=9;
    }else
    {
      curr_min=(t_relay_curr - t_relay)/(60000);
      if (last_min!=curr_min)
      {
        last_min=curr_min;
        lcd.clear();
        lcd.setCursor(0,0); //Start at character 4 on line 0
        lcd.print("Bomba Activa");
        lcd.setCursor(0,1); //Start at character 4 on line 0
        lcd.print("Faltan");
        lcd.setCursor(7,1); //Start at character 4 on line 0
        lcd.print(String(curr_min));
        lcd.setCursor(9,1); //Start at character 4 on line 0
        lcd.print("/");
        lcd.setCursor(10,1); //Start at character 4 on line 0
        lcd.print(String(t_relay_on));
        Serial.print("Faltan: ");
        Serial.print(curr_min);
        Serial.print("/");
        Serial.println(t_relay_on);
        if(lights_relay_on)
        {
          lights_relay_on=false;
          setallLeds(1);
        }
        else
        {
          lights_relay_on=true;
          setallLeds(0);
        }
       
      }
    }
  }
}
