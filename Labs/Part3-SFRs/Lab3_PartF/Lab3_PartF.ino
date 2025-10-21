#include <LiquidCrystal.h>
LiquidCrystal lcd(13, 12, 11, 10, 9, 8);

#define DDR_GREEN DDRE
#define PORT_GREEN PORTE
#define PIN_GREEN PINE
#define BIT_GREEN 4

#define DDR_YELLOW DDRE
#define PORT_YELLOW PORTE
#define PIN_YELLOW PINE
#define BIT_YELLOW 5

#define DDR_RESTART DDRD
#define PORT_RESTART PORTD
#define PIN_RESTART PIND
#define BIT_RESTART 0

#define DDR_GREEN_L DDRH
#define PORT_GREEN_L PORTH
#define PIN_GREEN_L PINH
#define BIT_GREEN_L 3

#define DDR_YELLOW_L DDRH
#define PORT_YELLOW_L PORTH
#define PIN_YELLOW_L PINH
#define BIT_YELLOW_L 4

/*** Interrupt Flags ***/
volatile uint8_t mainEventFlags = 0;
#define FLAG_PB_GREEN 0x01
#define FLAG_PB_YELLOW 0x02
#define FLAG_PB_RESTART 0x04


volatile uint8_t greenCounter = 0;
volatile uint8_t yellowCounter = 0;


void setup()
{
  DDR_YELLOW &= ~_BV(BIT_YELLOW);
  DDR_GREEN &= ~_BV(BIT_GREEN);
  DDR_RESTART &= ~_BV(BIT_RESTART);
  
  DDR_GREEN_L |= _BV(BIT_GREEN_L);
  DDR_YELLOW_L |= _BV(BIT_YELLOW_L);
  
  PORT_YELLOW |= _BV(BIT_YELLOW);
  PORT_GREEN |= _BV(BIT_GREEN);
  PORT_RESTART |= _BV(BIT_RESTART);
  
  lcd.begin(16, 2);
  lcd.print("Owen Wiesler");
  
  EIMSK |= _BV(INT4);
  EIMSK |= _BV(INT5);
  EIMSK |= _BV(INT0);
  
  EICRA |= _BV(ISC41);
  EICRA |= _BV(ISC51);
  EICRA |= _BV(ISC01);
  
  EICRA &= ~_BV(ISC40);
  EICRA &= ~_BV(ISC50);
  EICRA &= ~_BV(ISC00);
  
  sei();
}

void loop() {
  updateLCD();

  if (mainEventFlags & FLAG_PB_GREEN) {
    delay(30);
    mainEventFlags &= ~FLAG_PB_GREEN;
    if (bit_is_clear(PIN_GREEN, BIT_GREEN)) {
      PORT_YELLOW_L &= ~_BV(BIT_YELLOW_L);
      PORT_GREEN_L |= _BV(BIT_GREEN_L);
      greenCounter++;

      while (bit_is_clear(PIN_GREEN, BIT_GREEN)) {
        // Do nothing, wait till button is released to continue
      }
    }
  }

  if (mainEventFlags & FLAG_PB_YELLOW) {
    delay(30);
    mainEventFlags &= ~FLAG_PB_YELLOW;
    if (bit_is_clear(PIN_YELLOW, BIT_YELLOW)) {
      PORT_GREEN_L &= ~_BV(BIT_GREEN_L);
      PORT_YELLOW_L |= _BV(BIT_YELLOW_L);
      yellowCounter++;

      while (bit_is_clear(PIN_YELLOW, BIT_YELLOW)) {
        // Do nothing, wait till button is released to continue
      }
    }
  }

  if (bit_is_clear(PIN_RESTART, BIT_RESTART)) {
    delay(30);
    PORT_GREEN_L &= ~_BV(BIT_GREEN_L);
    PORT_YELLOW_L &= ~_BV(BIT_YELLOW_L);
    greenCounter = 0;
    yellowCounter = 0;
  }
}

void updateLCD() {
  lcd.setCursor(0, 1);
  lcd.print("G=");
  lcd.print(greenCounter);
  lcd.print("  ");
  
  lcd.setCursor(5,1);
  lcd.print("Y=");
  lcd.print(yellowCounter);
  lcd.print("  ");
  
  lcd.setCursor(10,1);
  lcd.print("T=");
  lcd.print(millis() / 1000);
  lcd.print("  ");
}

ISR(INT4_vect) {
  mainEventFlags |= FLAG_PB_GREEN;
}

ISR(INT5_vect) {
  mainEventFlags |= FLAG_PB_YELLOW;  
}

ISR(INT0_vect) {
  mainEventFlags |= FLAG_PB_RESTART;
}
