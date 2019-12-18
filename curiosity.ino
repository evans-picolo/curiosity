/*
 * Curisosity 1.0
 * 
 * Controla o robô curiosity
 * 
 * by Evans Picolo
 * Asthor Barden
 * 16/12/2019
 * 
 * Features:
 *   -  Comunicação bluetooth (via porta serial)
 *   -  Simulação de controle básico de motores (parar, frente e tras) com LEDs
 * 
 */

// Pinos
#define PARADO 13   // vermelho
#define FRENTE 12   // verde
#define TRAS 11     // amarelo

// Variéveis
char inChar; 

void setup() {
  // Configura pinos
  pinMode(PARADO, OUTPUT);
  pinMode(FRENTE, OUTPUT);
  pinMode(PARADO, OUTPUT);

  //Inicia comunicação serial em 9600 b/s
  Serial.begin(9600);
  Serial.println("\n\n>>START");
  
}

void loop() {

  // Verifica se chegou algo no serial buffer
  if(Serial.available()){
    // Lê um caracter e escreve ele de volta pro serial monitor
    inChar = Serial.read();
    Serial.println(inChar);

    // Verifica o que deve ser feito com o LED de acordo com o valor da caracter recebido
    if(inChar == 'p'){
      digitalWrite(PARADO, HIGH);
      digitalWrite(FRENTE, LOW);
      digitalWrite(TRAS, LOW);
      Serial.println(">> Parado.");
    }
    else if (inChar == 'f'){
      digitalWrite(PARADO, LOW);
      digitalWrite(FRENTE, HIGH);
      digitalWrite(TRAS, LOW);
      Serial.println(">> Andando para frente.");
    }
    else if (inChar == 't'){
      digitalWrite(PARADO, LOW);
      digitalWrite(FRENTE, LOW);
      digitalWrite(TRAS, HIGH);
      Serial.println(">> Andando para tras.");
    }
    

    // Deelay para estabilização
    delay(500);
  }

}
