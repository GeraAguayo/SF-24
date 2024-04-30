//SF 24
#include <SoftwareSerial.h>
SoftwareSerial blue(0,1);
char NOMBRE[21] = "AZIEL";
char appData;
char dato;
String inData;


int tiempo;
#define pwm_d  5
#define der_1  6
#define der_2  7
#define pwm_i  11
#define izq_1  9
#define izq_2  10
#define stby   8
char ultimaAccion = 's'; // 'p' significa STOP

void setup()
{
  //Bluetooth config
  Serial.begin(9600);
  Serial.println("Listo");
  blue.begin(9600);
  blue.print("AT+NAME");
  blue.print(NOMBRE);

  pinMode(izq_1, OUTPUT);
  pinMode(izq_2, OUTPUT);
  pinMode(der_1, OUTPUT);
  pinMode(der_2, OUTPUT);
  pinMode(pwm_i, OUTPUT);
  pinMode(pwm_d, OUTPUT);
  pinMode(stby, OUTPUT);
}

void loop()
{
  blue.listen();
  
  while(blue.available() > 0){
    appData = blue.read();
    inData = String(appData);
  }

  if (Serial.available())
  {
    Serial.print("Serial available");
    dato = Serial.read();
    Serial.print("\nEl dato recibido: ");
    Serial.print(dato);
    Serial.print("\n");
    
  }

  if (dato == 'g'){
    //Go forward
    forward();
  }
  else if(dato == 'o'){
    //Overtake mode
    go();
  }
  else if(dato == 'b'){
    //Reverse - Go back
    reverse();
  }
  else if(dato == 'r'){
    //Turn right
    turnRight();
  }
  else if(dato == 'l'){
    //Turn left
    turnLeft();
  }
  else if(dato == 's'){
    //Brake / stop motors
    stopMotors();
  }
  else if(dato == 'd'){
    //Run demo 
    demo();
  }
  else if(dato == 'c'){
    //Dance mode
    escape();
  }

}

void stopMotors(){
  digitalWrite(stby, HIGH);
  digitalWrite(der_1, LOW);
  digitalWrite(der_2, LOW);
  analogWrite(pwm_d, 0);
  digitalWrite(izq_1, LOW);
  digitalWrite(izq_2, LOW);
  analogWrite(pwm_i, 0);
  
}

void go()
{
  digitalWrite(stby, HIGH);

  digitalWrite(der_1, LOW);
  digitalWrite(der_2, HIGH);
  analogWrite(pwm_d, 150);
  
  digitalWrite(izq_1, HIGH);
  digitalWrite(izq_2, LOW);
  analogWrite(pwm_i, 150);
}

void  forward(){
  go();
  delay(75);
  stopMotors();
}



void back(){
  digitalWrite(stby, HIGH);

  digitalWrite(der_1, HIGH);
  digitalWrite(der_2, LOW);
  analogWrite(pwm_d, 100);
  
  digitalWrite(izq_1, LOW);
  digitalWrite(izq_2, HIGH);
  analogWrite(pwm_i, 100);
}

void reverse(){
  back();
  delay(75);
  stopMotors();
  
}

void left(){
  digitalWrite(stby, HIGH);

  digitalWrite(der_1, LOW);
  digitalWrite(der_2, HIGH);
  analogWrite(pwm_d, 100);

  digitalWrite(izq_1, LOW);
  digitalWrite(izq_2, HIGH);
  analogWrite(pwm_i, 0);
}

void turnLeft(){
  left();
  delay(75);
  stopMotors();
  
}

void right(){
  digitalWrite(stby, HIGH);

  digitalWrite(der_1, LOW);
  digitalWrite(der_2, LOW);
  analogWrite(pwm_d, 0);
  
  digitalWrite(izq_1, HIGH);
  digitalWrite(izq_2, LOW);
  analogWrite(pwm_i, 100);
}

void turnRight(){
  right();
  delay(75);
  stopMotors();
}

void escapeAct(){
  digitalWrite(stby, HIGH);

  digitalWrite(der_1, LOW);
  digitalWrite(der_2, LOW);
  analogWrite(pwm_d, 0);
  
  digitalWrite(izq_1, LOW);
  digitalWrite(izq_2, HIGH);
  analogWrite(pwm_i, 100);

}

void escape(){
  escapeAct();
  delay(75);
  stopMotors();
}


void demo(){
  forward();
  delay(125);
  turnLeft();
  delay(125);
  turnRight();
  delay(125);
  reverse();
  delay(125);
  stopMotors();
}
//Gerardo Aguayo  
