#include <dht.h>
#include <Bounce2.h>

#define INT_BTN 2                             //Side button
#define UP_BTN 3                            //Right button
#define DOWN_BTN 4                             //Left button

//Temperature Leds
#define LED_GREEN 6
#define LED_YELLOW 7

//Humidity Leds
#define LED_BLUE 10
#define LED_RED 12   

#define dht_pin A0

/*
Dry Soil   0 - 300
Humid Soil 300 - 700
In Water   700 - 950
*/


const int pinLeds[]={LED_RED, LED_BLUE, LED_YELLOW, LED_GREEN};
int modeLeds[]={0,0,0,0};                     //0:off, 1:on, 2:blink
unsigned long prevmillisLeds[]={0,0,0,0};
unsigned long currmillisLeds[]={0,0,0,0};

dht DHT;
int setDHum, currDHum, setDTemp, currDTemp;
int oldDHum, oldDTemp;
bool updateVals=0;

volatile int working_mode=0;                  //working mode
volatile unsigned long last_interrupt_time=0; //last time interrupt was called
volatile unsigned long t_mode=0;              //time on current mode
volatile bool check_int=false;                //check if interrupt was called 

bool backlight=true;                          //backlight status
bool relay_on=false;                          //is relay running

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
  
  setLeds();
  
  currDTemp=0;
  currDHum=0;
  oldDTemp=0;
  oldDHum=0;
  setDTemp=30;
  setDHum=450;
  t_relay_on=1;
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
  }
  
  unsigned long t_sensors_curr=millis(); // Current time for sensors
  
  debounceup.update();
  debouncedown.update();
  
  valuedown = debouncedown.read();
  valueup = debounceup.read();
  
  
  //Start the relay
  if (working_mode == 8)
  {
    //Relay Turn ON
    relay_turn_on();
    relay_running_lights();
  }
  else if (working_mode==9)
  {
    //Relay Turn Off
    relay_turn_off();
  }
  else
  {
    setallLeds(0);
    
    if ((t_sensors_curr - t_sensors > 2000) && (working_mode == 0))
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
        dht_lights();
        break;
      case 3:
        relay_setup();
        relay_lights();
        break;
      case 7:
        Serial.println("Turn off backlight");
        working_mode=0;
        break;
      default:
        printData();
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
      Serial.println(interrupt_time - last_interrupt_time);
      if (interrupt_time - last_interrupt_time < 1000)
      {
        working_mode=7;      //backlight
      }else if ((interrupt_time - last_interrupt_time >= 1000) && ((interrupt_time - last_interrupt_time < 5000)))
      {
        working_mode=(working_mode+1)%4;  //move between modes
        t_mode=millis();
      }else
      {
        if (working_mode == 8)
        {
          working_mode=9;
        }else
        {
          working_mode=8;  // change relay
        }
      }
    }
  }
  
}
