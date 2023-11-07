//Código do Arduino que ocntém Leds, LDR, Buzzer. 
//#include <DHT.h>
//#define DHTPIN 6
//#define DHTTYPE DHT11

int LDRPin = A4;
int greenLED = 5;
int yellowLED = 2;

int redLED = 3;
int buzzerPin = 4;
int valorLDR;
int valorAEnviar = 42; // Substitua 42 pelo valor que você deseja enviar
//DHT dht(DHTPIN, DHTTYPE);

const int trigPin = 13; // Pino Trigger do sensor ultrassônico
const int echoPin = 12; // Pino Echo do sensor ultrassônico

void setup() {
  pinMode(LDRPin, INPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  
  pinMode(10, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(8, OUTPUT);
  
  pinMode(redLED, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  Serial.begin(9600);
 // dht.begin();
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  int leitura = (Serial.read());
  Serial.println(leitura);
  if(leitura==3){
    digitalWrite(10, HIGH);
    digitalWrite(9, HIGH);
    digitalWrite(8, HIGH);
  }else if (leitura==2){
    digitalWrite(10, HIGH);
    digitalWrite(9, HIGH);
    digitalWrite(8, LOW);
  }else if (leitura==1){
    digitalWrite(10, HIGH);
    digitalWrite(9, LOW);
    digitalWrite(8, LOW);
  }
  valorLDR = analogRead(LDRPin);
  int nivelAlerta = 400;
  int nivelProblema = 700;

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  float duration = pulseIn(echoPin, HIGH);
  float distance = (duration / 2) / 29.1; // Calcula a distância em centímetros

  if (valorLDR < nivelAlerta || distance < 10) {
    digitalWrite(greenLED, HIGH);
    digitalWrite(yellowLED, LOW);
    digitalWrite(redLED, LOW);
    digitalWrite(buzzerPin, LOW);
  } else if (valorLDR > nivelAlerta && valorLDR < nivelProblema && distance >= 10) {
    digitalWrite(greenLED, LOW);
    digitalWrite(yellowLED, HIGH);
    digitalWrite(redLED, LOW);
    tone(buzzerPin, 500, 3000);
    Serial.println("Medio Nv"); // Envie a informação através da comunicação serial
  } else {
    digitalWrite(greenLED, LOW);
    digitalWrite(yellowLED, LOW);
    digitalWrite(redLED, HIGH);
    tone(buzzerPin, 1000, 3000);
    Serial.print("Baixo Nv"); // Envie a informação através da comunicação serial
  }

  delay(500);
}






// Código Arduino que contém Ultrassônico, Ponteciômetro e LCD. 

#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
const int triggerPin = 7; // Pino de gatilho do sensor ultrassônico
const int echoPin = 6;   // Pino de eco do sensor ultrassônico
void setup() {
  lcd.begin(16, 2); // Inicializa o LCD
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);

}

void loop() {
  int point = 0; 

  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  
  long duracao = pulseIn(echoPin, HIGH);
  int distancia_cm = duracao / 58; // Conversão para centímetros

  lcd.clear(); // Limpa o display

  lcd.setCursor(0, 0);
  lcd.print("Estoque");
  if (distancia_cm < 50) {
    lcd.setCursor(0, 1);
    lcd.print("Alto Nv");
    point=3;
  } else if (distancia_cm < 100) {
    lcd.setCursor(0, 1);
    lcd.print("Medio Nv");
    point = 2;
  } else {
    lcd.setCursor(0, 1);
    lcd.print("Baixo Nv");
    point=1;

  }
  
  Serial.write(point);
  Serial.println(point);
  delay(500); // Aguarda 1 segundo
}