//#include <avr/wdt.h>

//SERVO
#include <Servo.h>
Servo servoIC;
int angulo = 90;
const byte angbase = 30;
const byte angmax = 180;

//ULTRASSOM
#include <EEPROM.h>
//Leitura de distância com o sensor HC-SR04
#include <Ultrasonic.h>
Ultrasonic ultrassom(A3, A2); // define o nome do sensor(ultrassom)
//e onde esta ligado o trig(A0) e o echo(A1) respectivamente
//https://portal.vidadesilicio.com.br/hc-sr04-sensor-ultrassonico/
long distancia;
int endereco = 0;

//MOTOR
#include <AFMotor.h>
// Define o motor1 ligado a conexao 1
AF_DCMotor motor1(1);
// Define o motor2 ligado a conexao 4
AF_DCMotor motor2(4);


// Esta função "setup" roda uma vez quando a placa e ligada ou resetada
void setup() {
  servoIC.attach(9);
  servoIC.write(0); //INICIA O MOTOR NA POSIÇÃO 0º
  Serial.begin(9600); //Habilita Comunicação Serial a uma taxa de 9600 bauds.
  Serial.print(distancia); //imprime o valor da variável distancia
  Serial.println("cm");
  EEPROM.write(endereco, distancia);
  delay(10);

  //Leitura
  Serial.print("Lendo numero da memoria EEPROM : ");
  Serial.println(EEPROM.read(endereco));
  distancia = ultrassom.Ranging(CM);// ultrassom.Ranging(CM) retorna a distancia em centímetros(CM)

  motor1.setSpeed(100);
  motor2.setSpeed(100);

  //wdt_enable(WDTO_1S);  //habilita WDT

}
//PRECISA COLOCAR O IF ELSE DO MOTOR
// Função que se repete infinitamente quando a placa é ligada
void loop()
{
  for (angulo; angulo <= angmax; angulo += 45)
  {
    servoIC.write(angulo);
    delay(15);
    distancia = ultrassom.Ranging(CM);// ultrassom.Ranging(CM) retorna a distancia em
    // centímetros(CM) ou polegadas(INC)
    Serial.print(distancia); //imprime o valor da variável distancia
    Serial.println("cm");
    EEPROM.write(endereco, distancia);
    delay(15);
    //Leitura
    Serial.print("Lendo numero da memoria EEPROM : ");
    Serial.println(EEPROM.read(endereco));

    if (distancia >= 30 && angulo > 90 && angulo < 90)
    {
      // Aciona os motores 1 e 2 no sentido anti-horario
      motor1.run(FORWARD);
      motor2.run(FORWARD);
      delay(1000);
    }



    else if (distancia == 10 && angulo > 90 && angulo < 90)
    {
      // Aciona os motores 1 e 2 no sentido anti-horario
      motor1.run(BACKWARD);
      motor2.run(BACKWARD);
      delay(1000);
    }



    else if (distancia < 30 && angulo > 90)
    {
      // Aciona o motor 1 no sentido anti-horario
      motor1.run(BACKWARD);
      // Aciona o motor 2 no sentido horario
      motor2.run(FORWARD);
      delay(1000);
    }



    else if (distancia < 30 && angulo < 90)
    {
      // Aciona o motor 1 no sentido anti-horario
      motor1.run(FORWARD);
      // Aciona o motor 2 no sentido horario
      motor2.run(BACKWARD);
      delay(1000);

    }
  }
  for (angulo = 90; angulo >= angbase; angulo -= 45)
  {
    servoIC.write(angulo);
    delay(15);
    distancia = ultrassom.Ranging(CM);// ultrassom.Ranging(CM) retorna a distancia em
    // centímetros(CM) ou polegadas(INC)
    Serial.print(distancia); //imprime o valor da variável distancia
    Serial.println("cm");
    EEPROM.write(endereco, distancia);
    delay(15);
    //Leitura
    Serial.print("Lendo numero da memoria EEPROM : ");
    Serial.println(EEPROM.read(endereco));


  }

}
