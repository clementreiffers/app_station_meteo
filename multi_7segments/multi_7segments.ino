// définition des broches du décodeur 7 segments
// (vous pouvez changer les numéros si vous voulez)
const int bit_A = 2;
const int bit_B = 3;
const int bit_C = 4;
const int bit_D = 5;

const int temp_pin = 6 ;
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
  pinMode(temp_pin, INPUT);
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
  /*
    Serial.println(lire_masse());
    afficher_nombre(lire_temp());
  */
  //digits(1,9);
  Serial.println(lire_temp());
  afficher_nombre(lire_temp());
}

int lire_masse() {
  return (int)analogRead(A1) * 10;
}

int lire_temp() {
  return (int) (analogRead(A0) * ( 5.0 / 1023.0 * 100.0) * 10);
}

// fonction permettant d'afficher un nombre sur deux afficheurs
void afficher_nombre(int nombre)
{
  String tab = (String) nombre;

  long temps; // variable utilisée pour savoir le temps écoulé...
  int unite = 0, dizaine = 0, dizieme = 0; // variable pour chaque afficheur

  dizieme = nombre % 10;
  dizaine = (nombre - nombre % 100) / 100;
  unite = (nombre - dizaine * 100 - dizieme) / 10;
  //int myArray[10]={9,3,2,4,3,2,7,8,9,11};
  //int ordrechiffre[3] = {dizaine, unite, dizieme};//= new int[3];
  temps = millis(); // on récupère le temps courant

  // tant qu'on a pas affiché ce chiffre pendant au moins 500 millisecondes
  // permet donc de pouvoir lire le nombre affiché
  while ((millis() - temps) < 1000)
  {
    digits(dizaine, 8);
    delay(1);
    digits(unite, 9);
    delay(1);
    digits(dizieme, 10);
    delay(1);


  }

}
// fonction écrivant sur un seul afficheur
// on utilise le même principe que vu plus haut

void afficher(char nbr)
{
  digitalWrite(pos1, LOW);
  digitalWrite(pos2, LOW);
  digitalWrite(pos4, LOW);
  digitalWrite(pos8, LOW);
  if (nbr == 0) {
    digitalWrite(pos1, HIGH);
    digitalWrite(pos2, HIGH); 
    digitalWrite(pos4, HIGH); 
    digitalWrite(pos8, HIGH);
  }

  if (nbr == 1) {
    digitalWrite(pos1, HIGH);
    digitalWrite(pos2, LOW);
    digitalWrite(pos4, LOW);
    digitalWrite(pos8, LOW);
  }
  if (nbr == 2) {
    digitalWrite(pos1, LOW);
    digitalWrite(pos2, HIGH);
    digitalWrite(pos4, LOW);
    digitalWrite(pos8, LOW);
  }
  if (nbr == 3) {
    digitalWrite(pos1, HIGH);
    digitalWrite(pos2, HIGH);
    digitalWrite(pos4, LOW);
    digitalWrite(pos8, LOW);
  }
  if (nbr == 4) {
    digitalWrite(pos4, HIGH);
    digitalWrite(pos1, LOW);
    digitalWrite(pos2, LOW);
    digitalWrite(pos8, LOW);

  }
  if (nbr == 5) {
    digitalWrite(pos4, HIGH);
    digitalWrite(pos1, HIGH);
    digitalWrite(pos2, LOW);
    digitalWrite(pos8, LOW);
  }
  if (nbr == 6) {
    digitalWrite(pos2, HIGH);
    digitalWrite(pos4, HIGH);
    digitalWrite(pos1, LOW);
    digitalWrite(pos8, LOW);

  }
  if (nbr == 7) {
    digitalWrite(pos1, HIGH);
    digitalWrite(pos2, HIGH);
    digitalWrite(pos4, HIGH);
    digitalWrite(pos8, LOW);

  }
  if (nbr == 8) {
    digitalWrite(pos1, LOW);
    digitalWrite(pos2, LOW);
    digitalWrite(pos4, LOW);
    digitalWrite(pos8, HIGH);
  }
  if (nbr == 9) {
    digitalWrite(pos2, LOW);
    digitalWrite(pos4, LOW);
    digitalWrite(pos1, HIGH);
    digitalWrite(pos8, HIGH);
  }
}


void digits(float nbr, int pos) {
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);

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
