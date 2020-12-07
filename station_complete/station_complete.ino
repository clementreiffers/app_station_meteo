// on defini sbi et cbi avec des directives de pré-processeur
#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif
#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif

//============== notre equivalent de la fonction analogRead =====================

int analogReadNew(uint8_t pin)
{
  uint8_t low, high;
  if (pin >= 14) pin -= 14; // on reprend le bon numero du pin (-14 pour les uno)
  ADMUX = (INTERNAL << 6) | (pin & 0x07); // on met la tension de reference (1.1v) et on lit le pin
  sbi(ADCSRA, ADSC); // on met le 7eme bit (le numero 6) en mode read
  // on renit ADSC quand la conversion a ete faite
  while ((_SFR_BYTE(ADCSRA) & _BV(ADSC))); 
  low  = ADCL;
  high = ADCH;
  // combine the two bytes
  return (high << 8) | low;// on retourne la valeur
}

// ======== fonction qui split les chiffres et les mets dans les bonnes cases, fait appel à la fonction digits ===============

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

// =================== fonction qui affiche le chiffre dans le bon digit ========================================

void digits(int nbr, int pos) {
  // pos : 1 des 3 digits qu'on a besoin
  // nbr : le nombre qu'on veut afficher dans ce digit

  // on met tous les ports en low
  PORTD &= B00000000;
  PORTB &= B00000000;

  // conditions qu'on verifie pour activer telle ou telle pin
  // selon le cas pour afficher le chiffre dans le bon digit

  // les positions (1 des 3 digits)
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

void setup() {
  // on met tous les pins digitaux en output
  DDRD = 0xff;
  DDRB = 0xff;
  // on initialise tout le monde a low
  PORTD &= B00000000;
  PORTB &= B00000000;

}

// on initialise nos variable de temperature et de masse pour pouvoir les utiliser dans la loop
float temp = 0;
float masse = 0;

void loop() {
  // on recupere les entrees puis on fait une conversion pour avoir des degres celcius et des grammes
  temp = analogReadNew(A0);
  temp = temp * (1.1 / 1023.0 * 100.0);
  masse = analogReadNew(A1);
  masse = masse * 780 / 1023;

  // ========================== on affiche les nombres qu'on vient de recuperer ===================================
  
  float temps = millis(); // on récupère le temps courant
  // tant qu'on a pas affiché ce chiffre pendant au moins 500 millisecondes
  while ((millis() - temps) < 500)
    afficher((int)(temp * 10));
  
  temps = millis(); // on récupère le temps courant

  while ((millis() - temps) < 500)
    afficher((int) masse);
}
