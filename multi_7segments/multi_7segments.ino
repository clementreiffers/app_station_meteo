// définition des broches du décodeur 7 segments
// (vous pouvez changer les numéros si vous voulez)
const int bit_A = 2;
const int bit_B = 3;
const int bit_C = 4;
const int bit_D = 5;

int pos1 = bit_A, pos2 = bit_B, pos4 = bit_C, pos8 = bit_D;

// définitions des broches des transistors pour chaque afficheur
const int alim_dizaine = 8; // les dizaines
const int alim_unite = 9;   // les unites
const int alim_dizieme = 10;

void setup()
{
  // Les broches sont toutes des sorties
  pinMode(bit_A, OUTPUT);
  pinMode(bit_B, OUTPUT);
  pinMode(bit_C, OUTPUT);
  pinMode(bit_D, OUTPUT);
  pinMode(alim_dizaine, OUTPUT);
  pinMode(alim_unite, OUTPUT);
  pinMode(alim_dizieme, OUTPUT);


  // Les broches sont toutes mises à l'état bas
  digitalWrite(bit_A, LOW);
  digitalWrite(bit_B, LOW);
  digitalWrite(bit_C, LOW);
  digitalWrite(bit_D, LOW);
  digitalWrite(alim_dizaine, LOW);
  digitalWrite(alim_dizieme, LOW);
  digitalWrite(alim_unite, LOW);

  Serial.begin(9600);
}

void loop() // fonction principale
{
  afficher_nombre(531);
  //digits(5, 10);
  //digits(5, 8);
  //digits(5, 9);

}

// fonction permettant d'afficher un nombre sur deux afficheurs
void afficher_nombre(int nombre)
{
  String tab = (String) nombre;

  long temps; // variable utilisée pour savoir le temps écoulé...
  float unite = 0, dizaine = 0, dizieme = 0; // variable pour chaque afficheur

  dizieme = nombre % 10;
  dizaine = (nombre - nombre % 100) / 100;
  unite = (nombre - dizaine * 100 - dizieme) / 10;

  Serial.println(dizieme);

  temps = millis(); // on récupère le temps courant

  // tant qu'on a pas affiché ce chiffre pendant au moins 500 millisecondes
  // permet donc de pouvoir lire le nombre affiché
  while ((millis() - temps) < 10)
  {
    // on affiche le nombre

    // d'abord les dizaines pendant 10 ms

    // le transistor de l'afficheur des dizaines est saturé,
    // donc l'afficheur est allumé
    digitalWrite(alim_dizaine, HIGH);
    // on appel la fonction qui permet d'afficher le chiffre dizaine
    afficher(dizaine);
    //digits(dizaine, 8);
    // l'autre transistor est bloqué et l'afficheur éteint
    digitalWrite(alim_unite, LOW);
    delay(5);

    // puis les unités pendant 10 ms

    // on éteint le transistor allumé
    digitalWrite(alim_dizaine, LOW);
    // on appel la fonction qui permet d'afficher le chiffre unité

    //digits(unite, 9);

    afficher(unite);
    // et on allume l'autre
    digitalWrite(alim_unite, HIGH);
    delay(5);

    // on éteint le transistor allumé
    digitalWrite(alim_unite, LOW);
    // on appel la fonction qui permet d'afficher le chiffre unité
    //digits(dizieme, 10);

    afficher(dizieme);
    // et on allume l'autre
    digitalWrite(alim_dizieme, HIGH);
    delay(5);

  }

}

// fonction écrivant sur un seul afficheur
// on utilise le même principe que vu plus haut
void afficher(char chiffre)
{
  digitalWrite(bit_A, LOW);
  digitalWrite(bit_B, LOW);
  digitalWrite(bit_C, LOW);
  digitalWrite(bit_D, LOW);

  if (chiffre >= 8)
  {
    digitalWrite(bit_D, HIGH);
    chiffre = chiffre - 8;
  }
  if (chiffre >= 4)
  {
    digitalWrite(bit_C, HIGH);
    chiffre = chiffre - 4;
  }
  if (chiffre >= 2)
  {
    digitalWrite(bit_B, HIGH);
    chiffre = chiffre - 2;
  }
  if (chiffre >= 1)
  {
    digitalWrite(bit_A, HIGH);
    chiffre = chiffre - 1;
  }
}


/*
  void setup() {
  pinMode(pos1, OUTPUT);
  pinMode(pos2, OUTPUT);
  pinMode(pos4, OUTPUT);
  pinMode(pos8, OUTPUT);


  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  Serial.begin(9600);

  }

  void loop() {
  afficher(550);
  }*/
void afficher(float nbr) {

  String chaine = (String) nbr;
  int temps = 500;
  int i = 0;
  int pos = 8;
  while ((millis() - temps) < 10000)
  {
    i = i < 10 ? i++ : 0;
    pos = pos < 11 ? i++ : 8;
    digits(chaine[i], i + 8);
  }

  digits(5, 8);
}

void digits(float nbr, int pos) {
  digitalWrite(8, LOW);
  digitalWrite(9, LOW);
  digitalWrite(10, LOW);
  if (nbr == 1) {
    digitalWrite(pos, HIGH);
    digitalWrite(pos1, HIGH);
  }
  if (nbr == 2) {
    digitalWrite(pos, HIGH);
    digitalWrite(pos2, HIGH);
  }
  if (nbr == 3) {
    digitalWrite(pos, HIGH);
    digitalWrite(pos1, HIGH);
    digitalWrite(pos2, HIGH);
  }
  if (nbr == 4) {
    digitalWrite(pos, HIGH);
    digitalWrite(pos4, HIGH);
  }
  if (nbr == 5) {
    digitalWrite(pos, HIGH);
    digitalWrite(pos4, HIGH);
    digitalWrite(pos1, HIGH);
  }
  if (nbr == 6) {
    digitalWrite(pos, HIGH);
    digitalWrite(pos2, HIGH);
    digitalWrite(pos4, HIGH);
  }
  if (nbr == 7) {
    digitalWrite(pos, HIGH);
    digitalWrite(pos1, HIGH);
    digitalWrite(pos2, HIGH);
    digitalWrite(pos4, HIGH);
  }
  if (nbr == 8) {
    digitalWrite(pos, HIGH);
    digitalWrite(pos8, HIGH);
  }
  if (nbr == 9) {
    digitalWrite(pos, HIGH);
    digitalWrite(pos1, HIGH);
    digitalWrite(pos8, HIGH);
  }
}
