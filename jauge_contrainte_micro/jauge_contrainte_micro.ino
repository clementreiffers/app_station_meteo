#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif
#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif

int analogReadNew(uint8_t pin)
{
  uint8_t low, high;
  if (pin >= 14) pin -= 14; // allow for channel or pin numbers
  ADMUX = (INTERNAL << 6) | (pin & 0x07);
  sbi(ADCSRA, ADSC);
  // ADSC is cleared when the conversion finishes
  while ((_SFR_BYTE(ADCSRA) & _BV(ADSC))); // bit is set
  low  = ADCL;
  high = ADCH;
  // combine the two bytes
  return (high << 8) | low;
}


void setup() {
  Serial.begin(9600);
}
void loop() {
  // ne pas toucher à ces calculs !!!
  float valeur = analogReadNew(A0);
  valeur = valeur * 780;
  valeur = valeur / 1023;
  Serial.println(valeur);
}
