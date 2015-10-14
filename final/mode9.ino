void relay_turn_off()
{
  relay_on=false;
  last_min=61;
  curr_led_on=0;
  working_mode=0;
  lights_relay_on=false;
  lcd.clear();
  setallLeds(0);
  updateDHT=1;
  updateMois=1;
  digitalWrite(RELAY,LOW);
}
