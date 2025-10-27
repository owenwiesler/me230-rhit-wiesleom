#include <LiquidCrystal.h>

LiquidCrystal lcd(13, 12, 11, 10, 9, 8);

void setup() {
  lcd.begin(16, 2);
  
  // Clear
  ADMUX = 0;
  ADCSRA = 0;
  
  // AVCC w/ external capacitor at AREF
  ADMUX &= ~_BV(7);
  ADMUX |= _BV(6);
  
  // Enable ADC
  ADCSRA |= _BV(7);
  
  // Prescaler with ADCSRA
  ADCSRA |= _BV(0);
  ADCSRA |= _BV(1);
  ADCSRA |= _BV(2);

}

void loop() {  
  lcd.setCursor(0, 0);
  lcd.print("ADC 0 = ");
  lcd.print(getADC0());
  lcd.print("   ");
  
  lcd.setCursor(0, 1);
  lcd.print("ADC 15 = ");
  lcd.print(getADC3());
  lcd.print("   ");  
}

uint16_t getADC0() {
  // return analogRead(0);
  
  // Select A0 Pin
  ADMUX &= ~_BV(MUX0);
  ADMUX &= ~_BV(MUX1);
  ADMUX &= ~_BV(MUX2);
  ADMUX &= ~_BV(MUX3);
  ADMUX &= ~_BV(MUX4);
  ADCSRB &= ~_BV(MUX5);

  
  // Start conversion
  ADCSRA |= _BV(ADSC);
  
  // Do nothing in a while loop until the ADC convert is complete
  while (bit_is_set(ADCSRA, ADSC)) {
    // Do nothing
  }
  
  // Read the result
  return ADC;
}

uint16_t getADC3() {
  // return analogRead(3);  // Comment out this line
  
  // Select A3 Pin
  ADMUX |= _BV(MUX0);
  ADMUX |= _BV(MUX1);
  ADMUX |= _BV(MUX2);
  ADMUX &= ~_BV(MUX3);
  ADMUX &= ~_BV(MUX4);
  ADCSRB |= _BV(MUX5);
  
  // Start conversion
  ADCSRA |= _BV(ADSC);
  
  // Do nothing in a while loop until the ADC convert is complete
  while (bit_is_set(ADCSRA, ADSC)) {
    // Do nothing
  }
  
  // Read the result
  return ADC;
}