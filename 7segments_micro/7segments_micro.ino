/* 
correspondance pour le cablâge :
A = pin 5;
B = pin 6;
C = pin 7;
D = pin 3;
E = pin 2;
F = pin 4;
G = pin 9;
DP = pin 8;
*/
void setup()
{
  DDRD = 0xff;
  DDRB |= B00000011;
  PORTD |= B11111111;
  PORTB |= B11111111;
}

int i = 0;
void loop()
{
    i>9 ? i = 0 :  i++, afficher(i), delay(1000);
}
void eteindre() {
  PORTD |= B11111111;
  PORTB |= B11111111;
}
void afficher(int c) {
  eteindre();
  c == 0 ? PORTD &= B00000011 : false;
  c == 1 ? PORTD &= B00111111 : false;
  c == 2 ? PORTD &= B10010000, PORTB &= B11111101 : false;
  c == 3 ? PORTD &= B00010101, PORTB &= B11111101 : false;
  c == 4 ? PORTD &= B00101111, PORTB &= B11111101 : false;
  c == 5 ? PORTD &= B01000111, PORTB &= B11111101 : false;
  c == 6 ? PORTD &= B01000011, PORTB &= B11111101 : false;
  c == 7 ? PORTD &= B00011111 : false;
  c == 8 ? PORTD &= B00000001, PORTB &= B11111101 : false;
  c == 9 ? PORTD &= B00000101, PORTB &= B11111101 : false;
  c == 10 ? PORTB &= B00000010 : false;
}
