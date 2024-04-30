int n;
int blanco;
int negro;
int r1, r2, r3;
void setup() {
  // put your setup code here, to run once:
  // put your setup code here, to run once:
pinMode(A1,INPUT);//Establecemos los pines del A0 al A2 como entradas a las que estan conectados los sensores
pinMode(A2,INPUT);
pinMode(A3,INPUT);
pinMode(5,OUTPUT);//EN1
pinMode(2,OUTPUT);//IN1
pinMode(4,OUTPUT);//IN2
pinMode(6,OUTPUT);//EN2
pinMode(7,OUTPUT);//IN3
pinMode(8,OUTPUT);//IN4
pinMode(13,INPUT);//boton
   int r1 =analogRead(A1);//Creamos una variable r donde se guarda la lectura del pin A
  int r2 =analogRead(A2);//Creamos una variable r donde se guarda la lectura del pin A
  int r3 =analogRead(A3);//Creamos una variable r donde se guarda la lectura del pin A
  blanco=r2-10;
  negro=r2+10;
 
Serial.begin(9600);//Iniciamos la terminal virtual
}
void adelante(){// Creamos una funcion que haga que los motores giren en el sentido del reloj
digitalWrite(2,HIGH);
digitalWrite(4,LOW);//motor izquierda
analogWrite(5,182);

digitalWrite(7,LOW);
digitalWrite(8,HIGH);//motor derecha
analogWrite(6,181);
}
void atras(){// Creamos una funcion que haga que los motores giren en el sentido contrario del reloj
digitalWrite(2,LOW);
digitalWrite(4,HIGH);//motor izquierda
analogWrite(5,167);

digitalWrite(7,HIGH);
digitalWrite(8,LOW);//motor derecha
analogWrite(6,166);
}  
void giro_d1(){// Creamos una funcion que haga que uno de los motores gire en el sentido del reloj y otro al contrario resultando en un giro a la derecha en su propio eje
digitalWrite(2,HIGH);
digitalWrite(4,LOW);//motor izquierda
analogWrite(5,177);

digitalWrite(7,LOW);
digitalWrite(8,HIGH);//motor derecha
analogWrite(6,66);
}
void giro_i8(){// Creamos una funcion que haga que uno de los motores gire en el sentido del reloj y otro al contrario resultando en un giro a la izquierda en su propio eje
digitalWrite(2,HIGH);
digitalWrite(4,LOW);//motor izquierda
analogWrite(5,67);

digitalWrite(7,LOW);
digitalWrite(8,HIGH);//motor derecha
analogWrite(6,176 );
}

void apagado(){// Creamos una funcion que haga que los dos motores se detengan
digitalWrite(2,LOW);
digitalWrite(4,HIGH);//motor izquierda
digitalWrite(5,0);

digitalWrite(7,LOW);
digitalWrite(8,HIGH);//motor derecha
digitalWrite(6,0);
}
void loop() {
  // put your main code here, to run repeatedly:
int r1 =analogRead(A1);//Creamos una variable r donde se guarda la lectura del pin A
int r2 =analogRead(A2);//Creamos una variable r donde se guarda la lectura del pin A
int r3 =analogRead(A3);//Creamos una variable r donde se guarda la lectura del pin A
int b=digitalRead(13);
Serial.println(r1);
Serial.println(r2);
Serial.println(r3);
Serial.println(blanco);
Serial.println(negro);
Serial.println("  ");
//delay(3000);

 if(r1>=0 && r1<=negro && r2>=blanco && r2<=1023 && r3>=0 && r3<=negro  ){//Creamos un if que se ejecuta si los sensores estan en sensor0:negro, sensor1:blanco y sensor2:negro siendo blanco una distancia de 0mm a 2 mm y negor de 7mm a 10mm
adelante();//Se ejecuta la funcion que hace que los motores se activen y giren en direccion del reloj
Serial.println("adelante");
  }
  if(r1>=0 && r1<=negro && r2>=0 && r2<=negro && r3>=blanco && r3<=1023  ){//Creamos un if que se ejecuta si los sensores estan en sensor0:blanco, sensor1:negro y sensor2:negro siendo blanco una distancia de 0mm a 2 mm y negor de 7mm a 10mm
giro_d1();//Se ejecuta la funcion que hace que los motores se activen y giren el primero en direccion del reloj y el segundo al contrario
Serial.println("derecha");
  }
  if(r1>=blanco && r1<=1023 && r2>=0 && r2<=negro && r3>=0 && r3<=negro  ){//Creamos un if que se ejecuta si los sensores estan en sensor0:negro, sensor1:negro y sensor2:blanco siendo blanco una distancia de 0mm a 2 mm y negor de 7mm a 10mm
giro_i8();//Se ejecuta la funcion que hace que los motores se activen y giren el segundo en direccion del reloj y el primero al contrario
Serial.println("izquierda");
  }
 // if(r1>=0 && r1<=negro && r2>=0 && r2<=negro && r3>=0 && r3<=negro  ){//Creamos un if que se ejecuta si los sensores estan en sensor0:blanco, sensor1:blanco y sensor2:blanco siendo blanco una distancia de 0mm a 2 mm y negor de 7mm a 10mm
//atras();//Se ejecuta la funcion que hace que los motores se activen y giren en direccion contraria del reloj
 // }
 
}
