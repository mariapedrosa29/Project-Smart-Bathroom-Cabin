#include <LiquidCrystal.h> // inicia a biblioteca do LCD
LiquidCrystal lcd(22, 24, 26, 28, 30, 32); // define as portas de comunicação do lCD com o 

// Definição das variáveis do LCD e da iluminação
int sensor_infravermelho = 34; // define a porta 34 do Arduino como sendo o sensor infravermelho
int valor_sensor = 1 ; // define uma variável que receberá o valor de leitura do sensor infravermelho
int pino_rele = 36; // define a porta 36 do Arduino como sendo o pino do relé 

// Definição dos contadores
int bloqueio = 0; // define a variável bloqueio 
int contador; // define a variável contador


void setup() {
  Serial.begin(9600); // inicia o monitor serial do Arduino
  
  // Definição das saídas e entradas do LCD e da iluminação
  pinMode(sensor_infravermelho,INPUT); // define o sensor infravermelho como uma entrada
  pinMode(pino_rele, OUTPUT); // define o pino relé como uma saída
  lcd.begin(16, 2); // inicializa o LCD

}

void loop() {

    //Lógica de leitura do sensor de presença
    valor_sensor = digitalRead(sensor_infravermelho); // faz a leitura do sensor infravermelho e atribui a variável valor_sensor
    Serial.print("Sensor: ");  // nforma a leitura do sensor no monitor serial
    Serial.println(valor_sensor); // envia o valor para o monitor serial
    delay(100); // faz uma espera 100 milissegundos

    // Condição para a mudança da informação do LCD
    if (valor_sensor == 1) { // se o valor do sensor for igual a 1
 
      lcd.clear(); // limpa as informações do LCD
      lcd.setCursor(1, 0); // define as linhas e colunas do LCD 
      lcd.print("STATUS CABINE:"); // imprime no LCD o status da cabine
      lcd.setCursor(5, 1); // define as linhas e colunas do LCD
      lcd.print("VAZIA"); // imprime no LCD que a cabine está vazia
    }
   
    // Condições para a mudança da informação do LCD e acionamento da iluminação 
    if (valor_sensor == 0) { // se o valor do sensor for igual a 1
    
      contador = 1;
      bloqueio = 1;
    }

    if (contador == 1) {

        digitalWrite(pino_rele, HIGH); // a lâmpada irá acender
        lcd.clear(); // limpa as informações do LCD
        lcd.setCursor(1, 0); // define as linhas e colunas do LCD
        lcd.print("STATUS CABINE:"); // imprime no LCD o status da cabine
        lcd.setCursor(4, 1); // define as linhas e colunas do LCD
        lcd.print("OCUPADA"); // imprime no LCD que a cabine está ocupada
        valor_sensor = digitalRead(sensor_infravermelho); // faz a leitura do sensor infravermelho e atribui a variável valor sensor
        Serial.print("Sensor: ");  // nforma a leitura do sensor no monitor serial  
        Serial.println(valor_sensor); // envia o valor para o monitor serial 
            
        if (valor_sensor == 0) { // se o valor do sensor for igual a 0 novamente
        
            contador = 0; //a variável contator receberá 0
            bloqueio = 0; //a variável bloqueio receberá 0
        }

        if (contador == 0){
            
            delay(1000); // faz uma espera de 1000 milissegundos
            digitalWrite(pino_rele, LOW); // a lâmpada irá apagar
            lcd.clear(); // limpa as informações do LCD
            lcd.setCursor(1, 0); // define as linhas e colunas do LCD
            lcd.print("STATUS CABINE:"); // imprime no LCD o status da cabine
            lcd.setCursor(5, 1); // define as linhas e colunas do LCD
            lcd.print("VAZIA"); // imprime no LCD que a cabine está vazia 
        }  
    }
}