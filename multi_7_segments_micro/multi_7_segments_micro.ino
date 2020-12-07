void setup() {
  // on met tous les pins digitaux en output
  DDRD = 0xff;
  DDRB = 0xff;
  // on initialise tout le monde a low
  PORTD &= B00000000;
  PORTB &= B00000000;
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
void loop() {
  afficher(123);
}
