/*
 * Curisosity 1.2
 * 
 * Controla o robô curiosity
 * 
 * by Evans Picolo
 * Asthor Barden
 * 
 * 
 * Features:
 *   -  Limitação da velocidade 
 *   -  Diminuição do delay de estabilização (para diminui o tempo de resposta)
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


// Definição da velocidade
#define VELOCIDADE 150   // na verdade, é o duty cicle (0 a 255)


// Definição do delay entre um loop e outro (estabilização)
#define TEMPO_ESTABILIZACAO 100    // ms


// Declaração dos servos
Servo servoFrente;  
Servo servoTras;


// Variéveis
char inChar;   // para ler o BT


// Funções de controle dos motores

void para(){
  // Para todos o motores
  digitalWrite( MOTOR_DIREITO_RE              , LOW        );
  analogWrite ( MOTOR_DIREITO_FRENTE          , 0          );
  digitalWrite( MOTOR_ESQUERDO_RE             , LOW        );
  analogWrite ( MOTOR_ESQUERDO_FRENTE         , 0          );
  digitalWrite( MOTOR_CENTRAL_DIREITO_RE      , LOW        );
  analogWrite ( MOTOR_CENTRAL_DIREITO_FRENTE  , 0          );
  digitalWrite( MOTOR_CENTRAL_ESQUERDO_RE     , LOW        );
  analogWrite ( MOTOR_CENTRAL_ESQUERDO_FRENTE , 0          );
}

void re(){
  // More carrinho para trás
  // Usando complemento do duty cicle pois os pinos PWM agora são o bit negativo
  digitalWrite( MOTOR_DIREITO_RE              , HIGH             );
  analogWrite ( MOTOR_DIREITO_FRENTE          , 255 - VELOCIDADE );
  digitalWrite( MOTOR_ESQUERDO_RE             , HIGH             );
  analogWrite ( MOTOR_ESQUERDO_FRENTE         , 255 - VELOCIDADE );
  digitalWrite( MOTOR_CENTRAL_DIREITO_RE      , HIGH             );
  analogWrite ( MOTOR_CENTRAL_DIREITO_FRENTE  , 255 - VELOCIDADE );
  digitalWrite( MOTOR_CENTRAL_ESQUERDO_RE     , HIGH             );
  analogWrite ( MOTOR_CENTRAL_ESQUERDO_FRENTE , 255 - VELOCIDADE );
}

void frente(){
  // Move carrinho para frente
  digitalWrite( MOTOR_DIREITO_RE              , LOW        );
  analogWrite ( MOTOR_DIREITO_FRENTE          , VELOCIDADE );
  digitalWrite( MOTOR_ESQUERDO_RE             , LOW        );
  analogWrite ( MOTOR_ESQUERDO_FRENTE         , VELOCIDADE );
  digitalWrite( MOTOR_CENTRAL_DIREITO_RE      , LOW        );
  analogWrite ( MOTOR_CENTRAL_DIREITO_FRENTE  , VELOCIDADE );
  digitalWrite( MOTOR_CENTRAL_ESQUERDO_RE     , LOW        );
  analogWrite ( MOTOR_CENTRAL_ESQUERDO_FRENTE , VELOCIDADE );
}


// Funções de controle do servo

void viraFrente(){
  // Alinha os dois servos
  servoFrente.write(90);
  servoTras.write(90);
}


void viraDireita(){
  // Gira motores dianteiros para direita e traseiros para esquerda
  servoFrente.write(135);
  servoTras.write(45);
}


void viraEsquerda(){
  // Gira motores dianteiros para esquerda e traseiros para direita
  servoFrente.write(45);
  servoTras.write(135);
}


// Setup
void setup() {

  // Configura pinos dos motores
  pinMode(MOTOR_DIREITO_RE, OUTPUT);
  pinMode(MOTOR_DIREITO_FRENTE, OUTPUT);
  pinMode(MOTOR_ESQUERDO_RE, OUTPUT);
  pinMode(MOTOR_ESQUERDO_FRENTE, OUTPUT);
  pinMode(MOTOR_CENTRAL_DIREITO_RE, OUTPUT);
  pinMode(MOTOR_CENTRAL_DIREITO_FRENTE, OUTPUT);
  pinMode(MOTOR_CENTRAL_ESQUERDO_RE, OUTPUT);
  pinMode(MOTOR_CENTRAL_ESQUERDO_FRENTE, OUTPUT);
  
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
    delay(TEMPO_ESTABILIZACAO);
  }

}
