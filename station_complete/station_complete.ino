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
  // on met tous les pins digitaux en output
  DDRD = 0xff;
  DDRB = 0xff;
  // on initialise tout le monde a low
  PORTD &= B00000000;
  PORTB &= B00000000;
  Serial.begin(9600);
}

void afficher(int nombre)
{
  String tab = (String) nombre;
  long temps; // variable utilisée pour savoir le temps écoulé...
  int dizaine = (nombre - nombre % 100) / 100;
  int dizieme = nombre % 10; // variable pour chaque afficheur
  int unite = (nombre - dizaine * 100 - dizieme) / 10;
  int freq = 5; // pour pouvoir avoir les 3 afficheurs visibles pour nous
  float t = millis(); // on récupère le temps courant

  // tant qu'on a pas affiché ce chiffre pendant au moins 500 millisecondes
  // permet donc de pouvoir lire le nombre affiché
  while ((millis() - t) < 1000)
  {
    digits(dizaine, 3);
    delay(freq);
    digits(unite, 2);
    delay(freq);
    digits(dizieme, 1);
    delay(freq);
  }
}
void digits(int nbr, int pos) {
  // on met tous les ports en low
  PORTD &= B00000000;
  PORTB &= B00000000;

  // les positions
  pos == 1 ? PORTB |= B00000010 : false;
  pos == 2 ? PORTB |= B00000100 : false;
  pos == 3 ? PORTB |= B00000001 : false;

  // les nombres
  nbr == 1 ? PORTD |= B00000100 : false;
  nbr == 2 ? PORTD |= B00001000 : false;
  nbr == 3 ? PORTD |= B00001100 : false;
  nbr == 4 ? PORTD |= B00100000 : false;
  nbr == 5 ? PORTD |= B00100100 : false;
  nbr == 6 ? PORTD |= B00101000 : false;
  nbr == 7 ? PORTD |= B00101100 : false;
  nbr == 8 ? PORTD |= B00010000 : false;
  nbr == 9 ? PORTD |= B00010100 : false;
}
float temp = 0;
float masse = 0;
void loop() {
  
  float temps = millis(); // on récupère le temps courant

  // tant qu'on a pas affiché ce chiffre pendant au moins 500 millisecondes
  // permet donc de pouvoir lire le nombre affiché
  while ((millis() - temps) < 500)
  {
    temp = analogReadNew(A0);
    temp = temp * (1.1 / 1023.0 * 100.0);
    masse = analogReadNew(A1);
    masse = masse * 780;
    masse = masse / 1023;
    Serial.println((int)(masse * 10));

  }
  
  afficher((int)(temp * 10));
  delay(1000);
  afficher((int) masse * 10);
  delay(1000); 

}
