#include <Stepper.h> // inicia a biblioteca do motor de passo
const int stepsPerRevolution = 500; // define uma variável e atribui a ela a rotação inicial do motor de passo
Stepper myStepper(stepsPerRevolution, 8,10,9,11); // define as portas de conexão do Arduino com o motor de passo

// Definição das variáveis do acionamento da porta
int trigger_1 = 7; // define a porta 7 do Arduino como sendo o trigger 1 do sensor ultrassônico
int echo_1 = 6; // define a porta 6 do Arduino como sendo o echo 1 do sensor ultrassônico
float distancia_1; // define uma variável que armazenará a distância entre o sensor e o objeto 
float duracao_1; // define uma variável que armazenará a duração do sinal de echo

// Definição dos contadores
int bloqueio = 0; // define a variável bloqueio 

void setup() {
  Serial.begin(9600); // inicia o monitor serial do Arduino
  
  // Definição da velocidade inicial do motor de passo
  myStepper.setSpeed(60); // define a velocidade inicial do motor de passo 

  // Definição das saídas e entradas do acionamento da porta
  pinMode (trigger_1, OUTPUT); // define trigger 1 como uma saída
  pinMode (echo_1,INPUT); // define echo 1 como uma entrada
}

void loop() {
      // Lógica de leitura do sensor ultrassônico da porta
      digitalWrite(trigger_1, HIGH); // envia para o pino trigger 1 um sinal de nível lógico alto
      delayMicroseconds(10); // faz uma espera de 10 milissegundos
      digitalWrite(trigger_1, LOW); // envia para o pino trigger 1 um sinal de nível lógico baixo
      duracao_1 = pulseIn(echo_1, HIGH); // faz a leitura da duração 1 do pulso enviado pelo pino echo 1
      distancia_1 = 0.017 * duracao_1; // faz o cálculo da distância 1 da leitura do sensor em centímetros
      Serial.print("distancia porta: "); // informa a distância 1 no monitor serial
      Serial.print(distancia_1); // lê a variável distância 1 para mostrar no monitor serial
      Serial.println(" cm"); // informa que a distância está em centímetros

   // Condição para ativação do motor
   if(distancia_1 <= 5 && bloqueio == 0) { // quando a distância 1 for menor ou igual a 5 cm e o bloqueio for 1
   
      Serial.println("Porta acionada");
      myStepper.step(500); // a porta irá abrir 
      delay(3000); // tempo de espera para a abertura da porta de 3 segundos
      myStepper.step(-500); // a porta irá fechar
  }  
          
  else { // quando a distância 1 for maior que 5
  
      Serial.println("Porta não acionada");
  } 
}