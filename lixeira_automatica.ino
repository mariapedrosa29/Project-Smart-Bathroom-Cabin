#include <Servo.h> // inicia a biblioteca do servo motor
const int servo_pin = 12; // define a porta 12 do Arduino como entrada do servo 
Servo servo_motor; // inicializa o motor e o nomeia como servo motor
int trigger = 10; // define a porta 10 do Arduino como sendo o trigger
int echo = 8; // define a porta 8 do Arduino como sendo o echo
float duracao; // define uma variável que armazenará a duração do sinal de echo
float distancia; // define uma variável que armazenará a distância entre o objeto e o sensor

void setup(){
  Serial.begin(9600); // inicia o monitor serial do Arduino
  pinMode(trigger, OUTPUT); // define trigger como uma saída
  pinMode(echo, INPUT); // define echo como uma entrada
  servo_motor.attach(servo_pin); // irá passar para o pino definido a rotação do servo motor
  servo_motor.write(0); // manda para o servo motor um valor de rotação igual a zero
}

void loop(){
  digitalWrite(trigger, HIGH); // envia para o pino trigger um sinal de nível lógico alto
  delayMicroseconds(10); // faz uma espera de 0.010 milissegundos
  digitalWrite(trigger, LOW); // envia para o pino trigger um sinal de nível lógico baixo
  duracao = pulseIn(echo, HIGH); // faz a leitura da duração do pulso enviado pelo pino echo
  distancia = 0.017 * duracao; // faz o cálculo da distância da leitura do sensor em centímetros
  Serial.print("distancia"); // informa a distância no monitor serial
  Serial.print(distancia); // lê a variável distância para mostrar no monitor serial
  Serial.println(" cm"); // informa que a distância está em centímetros
  delay(500); // faz uma espera de 0.500 milissegundos

  if (distancia <= 10) { // quando a distância do sensor ultrassônico for menor ou igual a 10 cm
    servo_motor.write(120); // o motor irá rotacionar 120 graus 
    Serial.println(distancia); // envia a distância lida no sensor ultrassônico para o monitor serial
    Serial.println("Motor rotacionado"); // informa no monitor serial que houve rotação no motor
    delay(5000); // faz uma espera de 5 segundos
  }

  else { // quando a distância for maior que 10 cm
    servo_motor.write(0); // o motor não irá rotacionar
    Serial.println(distancia); // envia a distância lida no sensor ultrassônico para o monitor serial
    Serial.println("Motor nao rotacionado"); // informa no monitor serial que não houve rotação no motor    
  } 
}