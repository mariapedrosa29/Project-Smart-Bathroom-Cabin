// Definição das variáveis do acionamento da pia
int trigger_2 = 4; // define a porta 4 do Arduino como sendo o trigger 2 do sensor ultrassônico
int echo_2 = 3; // define a porta 3 do Arduino como sendo o echo 2 do sensor ultrassônico
float distancia_2; // define uma variável que armazenará a distância entre o sensor e o objeto 
float duracao_2; // define uma variável que armazenará a duração do sinal de echo
int led_pia = 2; // define a porta 5 do Arduino como sendo o led que representa a pia


void setup () {
  Serial.begin(9600); // inicia o monitor serial do Arduino

  // Definição das saídas e entradas do acionamento da pia
  pinMode (trigger_2, OUTPUT); // define trigger 2 como uma saída
  pinMode (echo_2,INPUT); // define echo 2 como uma entrada
  pinMode (led_pia, OUTPUT); // define o led da pia como uma saída

  // Lógica de leitura do sensor ultrassônico da pia
  digitalWrite(trigger_2, HIGH); // envia para o pino trigger 2 um sinal de nível lógico alto
  delayMicroseconds(10); // faz uma espera de 10 milissegundos
  digitalWrite(trigger_2, LOW); // envia para o pino trigger 2 um sinal de nível lógico baixo
  duracao_2 = pulseIn(echo_2, HIGH); // faz a leitura da duração 2 do pulso enviado pelo pino echo 2
  distancia_2 = 0.017 * duracao_2; // faz o cálculo da distância 2 da leitura do sensor em centímetros
  Serial.print("distancia pia: "); // informa a distância 2 no monitor serial
  Serial.print(distancia_2); // lê a variável distância 2 para mostrar no monitor serial
  Serial.println(" cm"); // informa que a distância está em centímetros
}

void loop() {
  
   // Condição de ativação do led da pia
  if(distancia_2 <= 5) { //quando a distância 2 for menor ou igual a 5 cm
  
    digitalWrite(led_pia, HIGH); // o led irá acender
    Serial.println("Led pia ligado"); // envia o monitor serial a informação que o led está ligado
    delay(1000); // faz uma espera de 1000 segundos
  }
              
  else {// quando a distância 2 for maior que 5
  
    digitalWrite(led_pia, LOW); // o led não irá acender
    Serial.println("Led pia desligado"); // envia o monitor serial a informação que o led está desligado 
  } 
}
