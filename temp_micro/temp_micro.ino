void setup() {
  Serial.begin(9600);  
// Désactivons l'ADC pour l'instant
  ADCSRA &= B01111111; 
  ADCSRB=0x00;
  ADMUX|=0&0x07;
  ADMUX|= (1<< REFS0);
  ADMUX|= (1<< REFS1);
  ADCSRA &= B11111011;
  ADCSRA |= B00000010;
  ADCSRA |= B00000001;
  ADCSRA |= B00100000;
  ADCSRA |= B00001000;
  ADCSRA |= B10000000;
  ADCSRA |= B01000000;
  sei();
}

void loop(){
//Code à exécuter lors d'une mesure analogique
//analogReference(INTERNAL);
  int valeur_brute = (ADCH<<8) | ADCL;
  float temperature_celcius = valeur_brute * (1.1 / 1023.0 * 100.0);
//Serial.println(temperature_celcius);
  delay(200);
}

ISR(ADC_vect){
  // Code à exécuter lors d'une mesure analogique3
  int valeur_brute= (ADCH<<8) | ADCL;
  float temperature_celcius = valeur_brute * (1.1 / 1023.0 * 100.0);
  Serial.println(temperature_celcius);
  delay(200);
}
