bool led_mode = false;
uint32_t led_timer = 0;


// Flash LED
// Generally, you should use "unsigned long" for variables that hold time
// The value will quickly become too large for an int to store
unsigned long previousMillis = 0;        // will store last time LED was updated

// constants won't change:
const long interval = 1000;     // interval at which to blink (milliseconds)

// Variables will change:
int ledState = LOW;             // ledState used to set the LED

// Fade LED
int value, value2 ;
int periode = 2000;
int displace = 500;

const long interval2 = 30;     // interval at which to blink (milliseconds)

// Init the led(s) for various boards
void initLed() {
  #if defined(ARDUINO_AVR_PROMICRO)  // Needs no pinMode change
    TXLED0;  // Just turn off initially
    RXLED0;  // Both of them
  #elif defined(ARDUINO_AVR_MICRO) || defined(ARDUINO_AVR_LEONARDO)
    #define RXLED 17  // RXLED is on pin 17
    #define TXLED 30  // TXLED is on pin 30

    pinMode(RXLED, OUTPUT);
    pinMode(TXLED, OUTPUT);
    
    digitalWrite(TXLED, LOW);
    digitalWrite(RXLED, LOW);
  #elif defined(ARDUINO_AVR_NANO) || defined(ARDUINO_AVR_UNO) || defined(ARDUINO_AVR_DUEMILANOVE)
    #define LEDPIN 13

    pinMode(LEDPIN, OUTPUT);
    
    digitalWrite(LEDPIN, LOW);
  #elif defined(ARDUINO_AVR_ADK) || defined(ARDUINO_AVR_MEGA) || defined(ARDUINO_AVR_MEGA2560)
    ;  // ToDo - support on MEGA ADK/2560 boards
  #endif
}

// Turns the led(s) on for various boards
void ledOn() {
  #if defined(ARDUINO_AVR_PROMICRO)
    TXLED1;
    RXLED1;
  #elif defined(ARDUINO_AVR_MICRO) || defined(ARDUINO_AVR_LEONARDO)
    digitalWrite(TXLED, HIGH);
    digitalWrite(RXLED, HIGH);
  #elif defined(ARDUINO_AVR_NANO) || defined(ARDUINO_AVR_UNO) || defined(ARDUINO_AVR_DUEMILANOVE)
    digitalWrite(LEDPIN, HIGH);
  #elif defined(ARDUINO_AVR_ADK) || defined(ARDUINO_AVR_MEGA) || defined(ARDUINO_AVR_MEGA2560)
    ;  // ToDo - support on MEGA ADK/2560 boards
  #endif
}

// Turns the led(s) off for various boards
void ledOff() {
  #if defined(ARDUINO_AVR_PROMICRO)
    TXLED0;
    RXLED0;
  #elif defined(ARDUINO_AVR_MICRO) || defined(ARDUINO_AVR_LEONARDO)
    digitalWrite(TXLED, LOW);
    digitalWrite(RXLED, LOW);
  #elif defined(ARDUINO_AVR_NANO) || defined(ARDUINO_AVR_UNO) || defined(ARDUINO_AVR_DUEMILANOVE)
    digitalWrite(LEDPIN, LOW);
  #elif defined(ARDUINO_AVR_ADK) || defined(ARDUINO_AVR_MEGA) || defined(ARDUINO_AVR_MEGA2560)
    ;  // ToDo - support on MEGA ADK/2560 boards
  #endif
}

// Blink the led(s) given times and delay interval (!BLOCKING FUNCTION!)
void blinkLed(uint8_t times, uint8_t dly) {
  for (uint8_t t=0;t<times;t++) {
    #if defined(ARDUINO_AVR_PROMICRO)
      TXLED1;
      RXLED1;
      delay(dly);
      TXLED0;
      RXLED0;
      delay(dly);
    #elif defined(ARDUINO_AVR_MICRO) || defined(ARDUINO_AVR_LEONARDO)
      digitalWrite(TXLED, HIGH);
      digitalWrite(RXLED, HIGH);
      delay(dly);
      digitalWrite(TXLED, LOW);
      digitalWrite(RXLED, LOW);
      delay(dly);
    #elif defined(ARDUINO_AVR_NANO) || defined(ARDUINO_AVR_UNO) || defined(ARDUINO_AVR_DUEMILANOVE)
      digitalWrite(LEDPIN, HIGH);
      delay(dly);
      digitalWrite(LEDPIN, LOW);
      delay(dly);
    #elif defined(ARDUINO_AVR_ADK) || defined(ARDUINO_AVR_MEGA) || defined(ARDUINO_AVR_MEGA2560)
      ;  // ToDo - support on MEGA ADK/2560 boards
    #endif
  }
}

void waveLed(uint16_t dly) {
  uint32_t curtime = millis();
  
  if (curtime - led_timer >= dly) {
    if (!led_mode) {
      #if defined(ARDUINO_AVR_PROMICRO)
          TXLED1;
          RXLED0;
        } else {
          TXLED0;
          RXLED1;
      #elif defined(ARDUINO_AVR_MICRO) || defined(ARDUINO_AVR_LEONARDO)
          digitalWrite(TXLED, led_mode);
          digitalWrite(RXLED, !led_mode);
        } else {
          digitalWrite(TXLED, led_mode);
          digitalWrite(RXLED, !led_mode);
      #elif defined(ARDUINO_AVR_NANO) || defined(ARDUINO_AVR_UNO) || defined(ARDUINO_AVR_DUEMILANOVE)
          digitalWrite(LEDPIN, led_mode);
        } else {
          digitalWrite(LEDPIN, led_mode);
      #endif
    }
    led_mode = !led_mode;
    led_timer = curtime;
  }
}

// Flash the inted at preset rate
void flashLed() {
  // check to see if it's time to blink the LED; that is, if the difference
  // between the current time and last time you blinked the LED is bigger than
  // the interval at which you want to blink the LED.
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;

    // if the LED is off turn it on and vice-versa:
    if (ledState == LOW) {
      ledState = HIGH;
    } else {
      ledState = LOW;
    }

#if defined(ARDUINO_AVR_PROMICRO)
    TXLED1;
    RXLED0;
#elif defined(ARDUINO_AVR_MICRO) || defined(ARDUINO_AVR_LEONARDO)
    digitalWrite(TXLED, ledState);
    digitalWrite(RXLED, !ledState);
#elif defined(ARDUINO_AVR_NANO) || defined(ARDUINO_AVR_UNO) || defined(ARDUINO_AVR_DUEMILANOVE)
    digitalWrite(LEDPIN, ledState);
#endif

  }
}

// Fade led in and out
void fadeLed() {
  // check to see if it's time to blink the LED; that is, if the difference
  // between the current time and last time you blinked the LED is bigger than
  // the interval at which you want to blink the LED.
  unsigned long currentMillis = millis();
//  if (currentMillis - previousMillis >= interval2) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;
    
    value = 128+127*cos(2*PI/periode*currentMillis);
//    value2 = 128+127*cos(2*PI/periode*(displace-currentMillis));
 
    analogWrite(RXLED, value);           // sets the value (range from 0 to 255) 
//    analogWrite(TXLED, value2);           // sets the value (range from 0 to 255) 

//  }
}
