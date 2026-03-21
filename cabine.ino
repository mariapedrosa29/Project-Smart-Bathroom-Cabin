
#include <LiquidCrystal.h> // inicia a biblioteca do LCD
LiquidCrystal lcd(22, 24, 26, 28, 30, 32); // define as portas de comunicação do LCD com o Arduino
#include <Stepper.h> // inicia a biblioteca do motor de passo
const int stepsPerRevolution = 500; // define uma variável e atribui a ela a rotação inicial do motor de passo
Stepper myStepper(stepsPerRevolution, 8,10,9,11); // define as portas de conexão do Arduino com o motor de passo

// Definição das variáveis do acionamento da porta
int trigger_1 = 7; // define a porta 7 do Arduino como sendo o trigger 1 do sensor ultrassônico
int echo_1 = 6; // define a porta 6 do Arduino como sendo o echo 1 do sensor ultrassônico
float distancia_1; // define uma variável que armazenará a distância entre o sensor e o objeto 
float duracao_1; // define uma variável que armazenará a duração do sinal de echo

// Definição das variáveis do acionamento da pia
int trigger_2 = 4; // define a porta 4 do Arduino como sendo o trigger 2 do sensor ultrassônico
int echo_2 = 3; // define a porta 3 do Arduino como sendo o echo 2 do sensor ultrassônico
float distancia_2; // define uma variável que armazenará a distância entre o sensor e o objeto 
float duracao_2; // define uma variável que armazenará a duração do sinal de echo
int led_pia = 2; // define a porta 5 do Arduino como sendo o led que representa a pia

// Definição das variáveis do acionamento da descarga
int trigger_3 = 14; // define a porta 14 do Arduino como sendo o trigger 3 do sensor ultrassônico
int echo_3 = 15; // define a porta 15 do Arduino como sendo o echo 3 do sensor ultrassônico
float distancia_3; // define uma variável que armazenará a distância entre o sensor e o objeto 
float duracao_3; // define uma variável que armazenará a duração do sinal de echo
int led_descarga = 16 ; // define a porta 7 do Arduino como sendo o led que representa a descarga

// Definição das variáveis do LCD e da iluminação
int sensor_infravermelho = 34; // define a porta 34 do Arduino como sendo o sensor infravermelho
int valor_sensor = 1 ; // define uma variável que receberá o valor de leitura do sensor infravermelho
int pino_rele = 36; // define a porta 36 do Arduino como sendo o pino do relé 

// Definição dos contadores
int bloqueio = 0; // define a variável bloqueio 
int contador; // define a variável contador  

void setup() {
  Serial.begin(9600); // inicia o monitor serial do Arduino
  
  // Definição da velocidade inicial do motor de passo
  myStepper.setSpeed(60); // define a velocidade inicial do motor de passo 

  // Definição das saídas e entradas do acionamento da porta
  pinMode (trigger_1, OUTPUT); // define trigger 1 como uma saída
  pinMode (echo_1,INPUT); // define echo 1 como uma entrada

  // Definição das saídas e entradas do acionamento da pia
  pinMode (trigger_2, OUTPUT); // define trigger 2 como uma saída
  pinMode (echo_2,INPUT); // define echo 2 como uma entrada
  pinMode (led_pia, OUTPUT); // define o led da pia como uma saída

  // Definição das saídas e entradas do acionamento da descarga
  pinMode (trigger_3, OUTPUT); // define trigger 3 como uma saída
  pinMode (echo_3,INPUT); // define echo 3 como uma entrada
  pinMode (led_descarga, OUTPUT); // define o led da descarga com uma saída

  // Definição das saídas e entradas do LCD e da iluminação
  pinMode(sensor_infravermelho,INPUT); // define o sensor infravermelho como uma entrada
  pinMode(pino_rele, OUTPUT); // define o pino rele como uma saída
  lcd.begin(16, 2); // inicializa o LCD
}

// Criação da função void para leitura do sensor de presença e acionamento do lCd e da iluminação    
void lcd_iluminacao() {

    // Lógica de leitura do sensor de presença
    valor_sensor = digitalRead(sensor_infravermelho); // faz a leitura do sensor infravermelho e atribui a variável valor_sensor
    Serial.print("Sensor: ");  // informa a leitura do sensor no monitor serial
    Serial.println(valor_sensor); // envia o valor para o monitor serial
    delay(100); // faz uma espera 0.100 milissegundos

    // Condição para a mudança da informação do LCD
    if (valor_sensor == 1) { // se o valor do sensor for igual a 1
    
      lcd.clear(); // limpa as informações do LCD
      lcd.setCursor(1, 0); // define as linhas e colunas do LCD 
      lcd.print("STATUS CABINE:"); // imprime no LCD o status da cabine
      lcd.setCursor(5, 1); // define as linhas e colunas do LCD
      lcd.print("VAZIA"); // imprime no LCD que a cabine está vazia
    }
   
    //Condições para a mudança da informação do LCD e acionamento da iluminação 
    if (valor_sensor == 0) { // se o valor do sensor for igual a 1

      contador = 1;
      bloqueio = 1;
    }

      if (contador == 1){

        digitalWrite(pino_rele, HIGH); // a lâmpada irá acender
        lcd.clear(); // limpa as informações do LCD
        lcd.setCursor(1, 0); // define as linhas e colunas do LCD
        lcd.print("STATUS CABINE:"); // imprime no LCD o status da cabine
        lcd.setCursor(4, 1); // define as linhas e colunas do LCD
        lcd.print("OCUPADA"); // imprime no LCD que a cabine está ocupada
        delay(1000); // faz uma espera de 1 segundo 
        valor_sensor = digitalRead(sensor_infravermelho); // faz a leitura do sensor infravermelho e atribui a variável valor_sensor
        Serial.print("Sensor: ");  // informa a leitura do sensor no monitor serial  
        Serial.println(valor_sensor); // envia o valor para o monitor serial 
         
        if (valor_sensor == 0) { // se o valor do sensor for igual a 0 novamente
        
          contador = 0; // a variável contador receberá 0
          bloqueio = 0; // a variável bloqueio receberá 0
        }

        if (contador == 0){

          delay(1000); // faz uma espera de 1 segundo
          digitalWrite(pino_rele, LOW); // a lâmpâda irá apagar
          lcd.clear(); // limpa as informações do LCD
          lcd.setCursor(1, 0); // define as linhas e colunas do LCD
          lcd.print("STATUS CABINE:"); // imprime no LCD o status da cabine
          lcd.setCursor(5, 1); // define as linhas e colunas do LCD
          lcd.print("VAZIA"); // imprime no LCD que a cabine está vazia 
        }  
    }
}
    
// Criação da função void para leitura do sensores ultrassônicos da porta, pia e descarga, respectivamente
void sensores_ultrassonicos() {

    // Lógica de leitura do sensor ultrassônico da porta
    digitalWrite(trigger_1, HIGH); // envia para o pino trigger 1 um sinal de nível lógico alto
    delayMicroseconds(10); // faz uma espera de 0.010 milissegundos
    digitalWrite(trigger_1, LOW); // envia para o pino trigger 1 um sinal de nível lógico baixo
    duracao_1 = pulseIn(echo_1, HIGH); // faz a leitura da duração 1 do pulso enviado pelo pino echo 1
    distancia_1 = 0.017 * duracao_1; // faz o cálculo da distância 1 da leitura do sensor em centímetros
    Serial.print("distancia porta: "); // informa a distancia 1 no monitor serial
    Serial.print(distancia_1); // lê a variável distância 1 para mostrar no monitor serial
    Serial.println(" cm"); // informa que a distância está em centímetros
      
    // Lógica de leitura do sensor ultrassônico da pia
    digitalWrite(trigger_2, HIGH); // envia para o pino trigger 2 um sinal de nível lógico alto
    delayMicroseconds(10); // faz uma espera de 0.010 milissegundos
    digitalWrite(trigger_2, LOW); // envia para o pino trigger 2 um sinal de nível lógico baixo
    duracao_2 = pulseIn(echo_2, HIGH); // faz a leitura da duração 2 do pulso enviado pelo pino echo 2
    distancia_2 = 0.017 * duracao_2; // faz o cálculo da distância 2 da leitura do sensor em centímetros
    Serial.print("distancia pia: "); // informa a distancia 2 no monitor serial
    Serial.print(distancia_2); // lê a variável distância 2 para mostrar no monitor serial
    Serial.println(" cm"); // informa que a distância está em centímetros

    // Lógica de leitura do sensor ultrassônico da descarga
    digitalWrite(trigger_3, HIGH); // envia para o pino trigger 3 um sinal de nível lógico alto
    delayMicroseconds(10); // faz uma espera de 0.010 milissegundos
    digitalWrite(trigger_3, LOW); // envia para o pino trigger 3 um sinal de nível lógico baixo
    duracao_3 = pulseIn(echo_3, HIGH); // faz a leitura da duração 3 do pulso enviado pelo pino echo 3
    distancia_3 = 0.017 * duracao_3; // faz o cálculo da distância 3 da leitura do sensor em centímetros
    Serial.print("distancia descarga: "); // informa a distancia 3 no monitor serial
    Serial.print(distancia_3); // lê a variável distância 3 para mostrar no monitor serial
    Serial.println(" cm"); // informa que a distância está em centímetros
}

void loop() {

  lcd_iluminacao(); // chama a função criada para a leitura e acionamento
  sensores_ultrassonicos(); // chama a função criada para fazer a leitura dos sensores ultrassônicos

  // Condição para ativação do motor
  if(distancia_1 <= 5 && bloqueio == 0) { // quando a distância 1 for menor ou igual a 5 cm e o bloqueio for 1
  
    Serial.println("Porta acionada");
    myStepper.step(500); // a porta irá abrir 
    delay(3000); // tempo de espera para a abertura da porta de 3 segundos
    myStepper.step(-500); // a porta irá fechar
    lcd_iluminacao(); // chama a função criada para a leitura e acionamento
    sensores_ultrassonicos(); // chama a função criada para fazer a leitura dos sensores ultrassônicos
  }  
          
  else { // quando a distância 1 for maior que 5
  
    Serial.println("Porta não acionada");
  } 

  lcd_iluminacao(); // chama a função criada para a leitura e acionamento
  sensores_ultrassonicos(); // chama a função criada para fazer a leitura dos sensores ultrassônicos

  // Condição de ativação do led da pia
  if(distancia_2 <= 5) { // quando a distância 2 for menor ou igual a 5 cm
  
    digitalWrite(led_pia, HIGH); // o led irá acender
    Serial.println("Led pia ligado"); //envia o monitor serial a informação que o led está ligado
    delay(3000); //espera de 3 segundos
    lcd_iluminacao(); //chama a função criada para a leitura e acionamento
    sensores_ultrassonicos(); //chama a função criada para fazer a leitura dos sensores ultrassônicos
  }
              
  else { // quando a distância 2 for maior que 5
  
    digitalWrite(led_pia, LOW); // o led não irá acender
    Serial.println("Led pia desligado"); // envia o monitor serial a informação que o led está desligado 
  } 

  lcd_iluminacao(); // chama a função criada para a leitura e acionamento
  sensores_ultrassonicos(); // chama a função criada para fazer a leitura dos sensores ultrassônicos

  // Condição de ativação do led da descarga
  if(distancia_3 <= 5) { // quando a distância 3 for menor ou igual a 5 cm
  
    digitalWrite(led_descarga, HIGH); // o led irá acender
    Serial.println("Led descarga ligado"); // envia o monitor serial a informação que o led está ligado
    delay(3000);  // espera de 3 segundos
    lcd_iluminacao(); // chama a função criada para a leitura e acionamento
    sensores_ultrassonicos(); // chama a função criada para fazer a leitura dos sensores ultrassônicos
  } 
             
  else { // quando a distância 3 for maior que 5
  
    digitalWrite(led_descarga, LOW); // o led não irá acender
    Serial.println("Led descarga desligado"); // envia o monitor serial a informação que o led está desligado
  } 

  lcd_iluminacao(); // chama a função criada para a leitura e acionamento
  sensores_ultrassonicos(); // chama a função criada para fazer a leitura dos sensores ultrassônicos
}