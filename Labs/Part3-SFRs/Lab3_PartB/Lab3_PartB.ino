#define TONE_DDR DDRH
#define TONE_PORT PORTH
#define TONE_BIT 5

#define ACTIVE_DDR DDRL
#define ACTIVE_PORT PORTL
#define ACTIVE_BIT 6

#define PB1_DDR DDRE
#define PB1_PORT PORTE
#define PB1_PIN PINE
#define PB1_BIT 4

#define PB2_DDR DDRE
#define PB2_PORT PORTE
#define PB2_PIN PINE
#define PB2_BIT 5

#define PB3_DDR DDRG
#define PB3_PORT PORTG
#define PB3_PIN PING
#define PB3_BIT 5

#define PB4_DDR DDRL
#define PB4_PORT PORTL
#define PB4_PIN PINL
#define PB4_BIT 7



void setup()
{ 
  TONE_DDR |= _BV(TONE_BIT);
  ACTIVE_DDR |= _BV(ACTIVE_BIT);
  PB1_DDR &= ~_BV(PB1_BIT);
  PB2_DDR &= ~_BV(PB2_BIT);
  PB3_DDR &= ~_BV(PB3_BIT);
  PB4_DDR &= ~_BV(PB4_BIT);
  
  PB1_PORT |= _BV(PB1_BIT);
  PB2_PORT |= _BV(PB2_BIT);
  PB3_PORT |= _BV(PB3_BIT);
  PB4_PORT |= _BV(PB4_BIT);
}

void loop()
{
  //if button press on A0 is detected
  if (bit_is_clear(PB1_PIN,PB1_BIT)) {
    tone(8, 523, 100);
  }
  // if button press on A1 is detected
  if (bit_is_clear(PB2_PIN,PB2_BIT)) {
    tone(8, 587, 100);
  }
  // if button press on A2 is detected
  if (bit_is_clear(PB3_PIN,PB3_BIT)) {
    tone(8, 659, 100);
  }
  while (bit_is_clear(PB4_PIN,PB4_BIT)) {
    ACTIVE_PORT |= _BV(ACTIVE_BIT);
  }
  ACTIVE_PORT &= ~_BV(ACTIVE_BIT);
}