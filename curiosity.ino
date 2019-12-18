/*
 * Curisosity 1.1
 * 
 * Controla o robô curiosity
 * 
 * by Evans Picolo
 * Asthor Barden
 * 18/12/2019
 * 
 * Features:
 *   -  Controle básico servo (frente, direita e esquerda)
 *   -  Controle básico do motor (frente, tras e parado)
 * 
 */

// Bibliotecas
#include <Servo.h>


// Definição dos pinos dos motores
#define MOTOR_DIREITO_RE              02    
#define MOTOR_DIREITO_FRENTE          03    
#define MOTOR_ESQUERDO_RE             04    
#define MOTOR_ESQUERDO_FRENTE         05
#define MOTOR_CENTRAL_DIREITO_RE      13    
#define MOTOR_CENTRAL_DIREITO_FRENTE  11    
#define MOTOR_CENTRAL_ESQUERDO_RE     12     
#define MOTOR_CENTRAL_ESQUERDO_FRENTE 10      // NOTE QUE ESSES ÚLTIMOS ESTÃO CRUZADOS DEVIDO À DISPOSIÇÃO DOS PINOS PWM   


// Declaração dos servos
Servo servoFrente;  
Servo servoTras;


// Variéveis
char inChar;   // para ler o BT


// Funções de controle dos motores

void para(){
  // Para todos o motores
  digitalWrite(MOTOR_DIREITO_RE,LOW);
  digitalWrite(MOTOR_DIREITO_FRENTE,LOW);
  digitalWrite(MOTOR_ESQUERDO_RE,LOW);
  digitalWrite(MOTOR_ESQUERDO_FRENTE,LOW);
  digitalWrite(MOTOR_CENTRAL_DIREITO_RE,LOW);
  digitalWrite(MOTOR_CENTRAL_DIREITO_FRENTE,LOW);
  digitalWrite(MOTOR_CENTRAL_ESQUERDO_RE,LOW);
  digitalWrite(MOTOR_CENTRAL_ESQUERDO_FRENTE,LOW);
}

void re(){
  // More carrinho para trás
  digitalWrite(MOTOR_DIREITO_RE,HIGH);
  digitalWrite(MOTOR_DIREITO_FRENTE,LOW);
  digitalWrite(MOTOR_ESQUERDO_RE,HIGH);
  digitalWrite(MOTOR_ESQUERDO_FRENTE,LOW);
  digitalWrite(MOTOR_CENTRAL_DIREITO_RE,HIGH);
  digitalWrite(MOTOR_CENTRAL_DIREITO_FRENTE,LOW);
  digitalWrite(MOTOR_CENTRAL_ESQUERDO_RE,HIGH);
  digitalWrite(MOTOR_CENTRAL_ESQUERDO_FRENTE,LOW);
}

void frente(){
  // Move carrinho para frente
  digitalWrite(MOTOR_DIREITO_RE,LOW);
  digitalWrite(MOTOR_DIREITO_FRENTE,HIGH);
  digitalWrite(MOTOR_ESQUERDO_RE,LOW);
  digitalWrite(MOTOR_ESQUERDO_FRENTE,HIGH);
  digitalWrite(MOTOR_CENTRAL_DIREITO_RE,LOW);
  digitalWrite(MOTOR_CENTRAL_DIREITO_FRENTE,HIGH);
  digitalWrite(MOTOR_CENTRAL_ESQUERDO_RE,LOW);
  digitalWrite(MOTOR_CENTRAL_ESQUERDO_FRENTE,HIGH);
}


// Funções de controle do servo

void viraFrente(){
  servoFrente.write(90);
  servoTras.write(90);
}


void viraDireita(){
  servoFrente.write(135);
  servoTras.write(45);
}


void viraEsquerda(){
  servoFrente.write(45);
  servoTras.write(135);
}


// Setup
void setup() {

  // Configura pinos dos motores
  pinMode(MOTOR_DIREITO_RE,OUTPUT);
  pinMode(MOTOR_DIREITO_FRENTE,OUTPUT);
  pinMode(MOTOR_ESQUERDO_RE,OUTPUT);
  pinMode(MOTOR_ESQUERDO_FRENTE,OUTPUT);
  pinMode(MOTOR_CENTRAL_DIREITO_RE,OUTPUT);
  pinMode(MOTOR_CENTRAL_DIREITO_FRENTE,OUTPUT);
  pinMode(MOTOR_CENTRAL_ESQUERDO_RE,OUTPUT);
  pinMode(MOTOR_CENTRAL_ESQUERDO_FRENTE,OUTPUT);
  
  // Define pinos dos servos
  servoFrente.attach(6); 
  servoTras.attach(7);

  //Inicia comunicação serial em 9600 b/s
  Serial.begin(9600);
  Serial.println("\n\n>>START");

  // Inicia com servos para frente
  viraFrente();

  // Espera um tempo antes de começar
  delay(2000);
  
}

// Loop
void loop() {

  // Verifica se chegou algo no serial buffer
  if(Serial.available()){
    // Lê um caracter e escreve ele de volta pro serial monitor
    inChar = Serial.read();
    Serial.println(inChar);

    // Verifica o que deve ser feito com o LED de acordo com o valor da caracter recebido
    if(inChar == 'p'){
      // Para motores
      para();
      Serial.println(">> Parado.");
    }
    else if (inChar == 'f'){
      // Motores para frente
      frente();
      Serial.println(">> Andando para frente.");
    }
    else if (inChar == 't'){
      // Motores para trás
      re();
      Serial.println(">> Andando para tras.");
    }
    else if (inChar == 'x'){
      // Servos para frente
      viraFrente();
      Serial.println(">> Virando a frente");
    }
    else if (inChar == 'd'){
      // Servos para direita
      viraDireita();
      Serial.println(">> Virando a direita.");
    }
    else if (inChar == 'e'){
      // Servos para esquerda
      viraEsquerda();
      Serial.println(">> Virando a esquerda.");
    }
    

    // Delay para estabilização
    delay(500);
  }

}
