#include <dht.h>
#include <Bounce2.h>
#include <Wire.h>  
#include <LiquidCrystal_I2C.h>



#define INT_BTN 2                             //Side button
#define UP_BTN 3                            //Right button
#define DOWN_BTN 4                             //Left button

//Temperature Leds
#define LED_GREEN 6
#define LED_YELLOW 7

#define RELAY 9

//Humidity Leds
#define LED_BLUE 10
#define LED_RED 12   

#define dht_pin A0
/*
Dry Soil   0 - 300
Humid Soil 300 - 700
In Water   700 - 950
*/
#define soil1_pin A1
#define soil2_pin A2


LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address

const int pinLeds[]={LED_RED, LED_BLUE, LED_YELLOW, LED_GREEN};
int modeLeds[]={0,0,0,0};                     //0:off, 1:on, 2:blink
unsigned long prevmillisLeds[]={0,0,0,0};
unsigned long currmillisLeds[]={0,0,0,0};

dht DHT;
int setDHum, currDHum, setDTemp, currDTemp;
int oldDHum, oldDTemp;
bool updateDHT=0;
bool runDHT=false;

int currDMois, currRMois;
int oldDMois, oldRMois;
bool updateMois=0;
bool runMois=false;

volatile int working_mode=0;                  //working mode
volatile int old_mode=0;
volatile unsigned long last_interrupt_time=0; //last time interrupt was called
volatile unsigned long t_mode=0;              //time on current mode
volatile bool check_int=false;                //check if interrupt was called 

bool backlight=true;                          //backlight status
bool relay_on=false;                          //is relay running
volatile bool data_printed=false;
volatile bool clean_leds=false;

bool lights_relay_on=false;

unsigned long t_sensors=0;                    //time sensors 
unsigned long t_relay=0;                      //time relays 

int t_relay_on=5;                             //set up minutes relay on
int humidity_lim=500;                         //set up for humidity sensors 

Bounce debounceup=Bounce();
Bounce debouncedown=Bounce();
int upcnt=0;                                  //count occurrences of click
int downcnt=0;

int valueup, valuedown;

int last_min=61;
int curr_led_on=0;
unsigned long tmp_lights_on=0;
int tmp=0;                                    

void setup() {
  Serial.begin(9600);
  
  lcd.begin(16,2);   // initialize the lcd for 16 chars 2 lines, turn on backlight

// ------- Quick 3 blinks of backlight  -------------
  for(int i = 0; i< 3; i++) {
    lcd.backlight();
    delay(250);
    lcd.noBacklight();
    delay(250);
  }
  lcd.backlight(); // finish with backlight on  

//-------- Write characters on the display ------------------
// NOTE: Cursor Position: (CHAR, LINE) start at 0  
  printData("Hola Panchita!",0,0,0);
  delay(300);
  printData("Configurando!",0,1,1);
  delay(1000);//Let system settle
  
  //############# Interruption ###################
  pinMode(INT_BTN, INPUT);
  digitalWrite(INT_BTN, HIGH);
  attachInterrupt(0, changeMode, RISING);
  //##############################################
  
  //##################BUTTON #####################
  pinMode(UP_BTN,INPUT_PULLUP);
  debounceup.attach(UP_BTN);
  debounceup.interval(10); // interval in ms
  pinMode(DOWN_BTN,INPUT_PULLUP);
  debouncedown.attach(DOWN_BTN);
  debouncedown.interval(10); // interval in ms
  //##############################################
  
  pinMode(RELAY,OUTPUT);
  digitalWrite(RELAY,LOW);
 
  setLeds();
  setValues();
  
  t_sensors=millis();

}

void loop()   
{
  //Get all the timers
  if (check_int && (millis()-last_interrupt_time > 10000)) //reset check_int if has not any input
  {
    Serial.println("Reset check_int");
    check_int=!check_int;
  }
  
  if(millis() - t_mode > 10000 && working_mode != 0 && working_mode != 8 && working_mode != 9)
  {
    Serial.println("Reset working_mode");
    working_mode=0;
    updateDHT=1;
    updateMois=1;
    clean_leds=true;
    if (relay_on)
    {
      working_mode=9;
    }
  }
  
  unsigned long t_sensors_curr=millis(); // Current time for sensors
  
  randomSeed(analogRead(A6));
  debounceup.update();
  debouncedown.update();
  
  valuedown = debouncedown.read();
  valueup = debounceup.read();
  
  //Start the relay
  if (clean_leds)
  {
    clean_leds=!clean_leds;
    setallLeds(0);
  }
  
  if (working_mode == 8)
  {
    //Relay Turn ON
    relay_turn_on();
  }
  else if (working_mode==9)
  {
    //Relay Turn Off
    relay_turn_off();
  }
  else
  {
   // setallLeds(0);
    
    if ((t_sensors_curr - t_sensors > 15000) && (working_mode == 0))
    {
      Serial.println("readSensors");
      readSensors();
      t_sensors=t_sensors_curr;
    }
    
    switch(working_mode)
    {
      case 1:
        humidity_setup();
        humidity_lights();
        break;
      case 2:
        dht_setup();
        dht_lights();
        break;
      case 3:
        relay_setup();
        relay_lights();
        break;
      case 7:
        working_mode=old_mode;
        old_mode=0;
        if (backlight)
        {
          Serial.println("Turn off backlight");
          lcd.noBacklight(); // finish with backlight on   
          backlight=!backlight;
        }else
        {
          Serial.println("Turn on backlight");
          lcd.backlight();
          backlight=!backlight;
        }
        break;
      default:
        digestData();
    } 
  }
  doLeds();
}

void changeMode()
{
  unsigned long interrupt_time = millis();
  // If interrupts come faster than 200ms, turn backlight on or off
  if (interrupt_time - last_interrupt_time > 700)
  {
    check_int=!check_int;
  }
  if (check_int)
  {
    last_interrupt_time = interrupt_time;
  }
  else
  {
    if(interrupt_time!=0)
    {
      if (interrupt_time - last_interrupt_time < 1500)
      {
        old_mode=working_mode;
        data_printed = true;
        clean_leds=true;
        working_mode=7;      //backlight
        t_mode=millis();
      }else if ((interrupt_time - last_interrupt_time >= 1500) && ((interrupt_time - last_interrupt_time < 5000)))
      {
        data_printed = true;
        clean_leds=true;
        working_mode=(working_mode+1)%4;  //move between modes
        if (working_mode == 0)
        {
          working_mode++;
        }
        t_mode=millis();
      }else
      {
        clean_leds=true;
        if (working_mode == 8)
        {
          data_printed = true;
          working_mode=9;
        }else
        {
          data_printed = true;
          working_mode=8;  // change relay
        }
      }
    }
  }
  
}
