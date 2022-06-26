#include <Servo.h>
#include <Keypad.h>

Servo servo_Motor;

const char* senha = "090104";

const byte LINHAS = 4; 
const byte COLUNAS = 4;

char digitos[LINHAS][COLUNAS] = {
{'1','2','3','A'},
{'4','5','6','B'},
{'7','8','9','C'},
{'*','0','#','D'}
}; 

byte pinosLinha[LINHAS] = { 11, 10, 9, 8 }; 
byte pinosColuna[COLUNAS] = { 7, 6, 5, 4 }; 

Keypad keypad = Keypad( makeKeymap(digitos), pinosLinha, pinosColuna, LINHAS, COLUNAS );

int position = 0;
int ledVermelho = 12;
int ledVerde = 13;
int buzzer = 2;
int tempoBuzz = 50;
int alarme = 0;
int contador;

void setup()
{ 
  
estadoPorta(true);

pinMode(ledVermelho,OUTPUT); 
pinMode(ledVerde,OUTPUT);
pinMode(buzzer,OUTPUT);

servo_Motor.attach(3);

}

void loop(){
  
char digito = keypad.getKey();
 if (digito == '*' || digito == '#') { 
  position = 0;
  estadoPorta(true);
 }
if (digito !=0) {
  digitalWrite(buzzer, HIGH);
  delay(tempoBuzz);
  digitalWrite(buzzer, LOW);

if (digito == senha[position]){
position ++;
alarme--;
}
else {
position = 0;
alarme++;
}
if (alarme == 5) {
  for (contador = 1; contador <= 10; contador++) {
  digitalWrite(buzzer, HIGH);
  delay(500);
  digitalWrite(buzzer, LOW);
  delay(500);
  }
 alarme = 0;
 estadoPorta(true);
}
if (position == 6) {
estadoPorta(false);
}
delay(100);
}
}

void estadoPorta(int trancado){  
  
if (trancado){
digitalWrite(ledVermelho, HIGH);
digitalWrite(ledVerde, LOW);
servo_Motor.write(0);
}

else {
digitalWrite(ledVermelho, LOW);
digitalWrite(ledVerde, HIGH);
servo_Motor.write(90);
digitalWrite(buzzer, HIGH);
delay(tempoBuzz*10);
digitalWrite(buzzer, LOW);
}
}
