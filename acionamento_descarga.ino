// Definição das variáveis do acionamento da descarga
int trigger_3 = 14; // define a porta 14 do Arduiino como sendo o trigger 3 do sensor ultrassônico 
int echo_3 = 15; // define a porta 15 do Arduino como sendo o echo 3 do sensor ultrâssonico
float distancia_3; // define uma variável que armazenará a distância entre o sensor e o objeto
float duracao_3; // define uma variável que armazenará a duração do sinal de echo
int led_descarga = 16; // define a porta 7 do Arduino como sendo o led que representa a descarga

void setup () {
    Serial.begin(9600); // incia o monitor serial do Arduino

    // Definição das saídas e entradas do acionamento da descarga
    pinMode(trigger_3, OUTPUT); // define o trigger 3 como uma saída
    pinMode(echo_3, INPUT); // define o echo 3 como uma entrada
    pinMode(led_descarga, OUTPUT); // define o led da descarga como uma saída

    // Lógica de leitura do sensor ultrassônico da descarga
    digitalWrite(trigger_3, HIGH); // envia para o pino trigger 3 um sinal de nível lógico alto
    delayMicroseconds(10); //faz uma espera de 10 milissegundos
    digitalWrite(trigger_3, LOW); //envia para o pino trigger 3 um sinal de nível lógico baixo
    duracao_3 = pulseIn(echo_3, HIGH); //faz a leitura da duração 3 do pulso enviado pelo pino echo 3
    distancia_3 = 0.017 * duracao_3; //faz o cálculo da distância 3 da leitura do sensor em centímetros
    Serial.print("distancia descarga: "); //informa a distância 3 no monitor serial
    Serial.print(distancia_3); //lê a variável distância 3 para mostrar no monitor serial
    Serial.println(" cm"); //informa que a distância está em centímetros
}

void loop() {
  
    //Condição de ativação do led da descarga
  if(distancia_3 <= 5) { //quando a distância 3 for menor ou igual a 5 cm

    digitalWrite(led_descarga, HIGH); // o led irá acender
    Serial.println("Led descarga ligado"); //envia o monitor serial a informação que o led está ligado
    delay(1000);
  } 
             
  else { //quando a distância 3 for maior que 5
   
    digitalWrite(led_descarga, LOW); //o led não irá acender
    Serial.println("Led descarga desligado"); //envia o monitor serial a informação que o led está desligado
  } 
}
