


//los pine 10 y 11 son de l motor derecha
//los pines 9 y 12 son del motor izquierda
#include <SoftwareSerial.h>
#define IN1  8
#define IN2  7
#define IN3  3
#define IN4  2

int Paso [ 4 ][ 4 ] =
   {  {1, 1, 0, 0},
      {0, 1, 1, 0},
      {0, 0, 1, 1},
      {1, 0, 0, 1},
 
   };
   int velDerecha=200;
    int Steps = 0; 
   int moveCamera=0;
   int limiteGiro=10;
   int velGiro=5;
   int zeroCamera=0;
   int pasoDerecha=0;
   int pasoIzquierda=0;
   int tempPasoReturnToZero=0;

int bluetoothTx = 5;//blutoth module terminal TX
int bluetoothRx = 6;//blutoth module terminal RX


SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);



char ch;



void setup() {

  // set the data rate for the SoftwareSerial port
  bluetooth.begin(9600);
 //pinMode(13,OUTPUT);
  pinMode(4,OUTPUT);
 pinMode(9,OUTPUT);
pinMode(10,OUTPUT);
pinMode(11,OUTPUT);
pinMode(12,OUTPUT);
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);

Serial.begin(9600);
 
  

}

void loop() {
  if(bluetooth.available()>0){
   ch=bluetooth.read();
   Serial.println(ch);
   
    if(ch=='A'){

   ad();
 
  
  
 } if(ch=='B'){
  
   iz();
  
  
 }if(ch=='C'){
   
   dch();
   
  
 }
 if(ch=='D'){
   
   st();
   
  
 }
  if(ch=='E'){
 
   at();
   
   
  
 }  if(ch=='F'){
   //Move camera to left
   //MoveCamera valor es 0;
   moveCamera=0;
   while(moveCamera<limiteGiro){
     //Hacemos un paso a la izquierda
      stepperIzquierda();
      //Calculamos cunto nos alejamos del origen zero
     calcularZeroCamera(false);
     //Esperamos 
      delay(velGiro);
      //incrementamos valor moveCamera cuando llege a 10 para. este valor es para salir del bucle infinito asi nos 
      //asiguramos de que cada 10 pasos podemos recibir datos entrantes
      moveCamera++;
    
   }
   //Al acabar el ciclo paramos el motor papo a paso
  lowAllPaso();
 //cam move izquierda
   
   
  
 }
 if(ch=='Q'){
   //Move camera to right
   moveCamera=0;
   while(moveCamera<limiteGiro){
 stepperDerecha();
 calcularZeroCamera(true);
  
 delay(velGiro);
 moveCamera++;

 //cam move derecha
   }
     lowAllPaso();
 }
   if(ch=='H'){
    moveCamera=10;
    lowAllPaso();
   
   
 }
  if(ch=='Y'){
   
 volverToZero();
//Return camera to zero

   
  
 }
  if(ch=='V'){
 
 volverToMarchaAtras();
//Return camera to marcha atras

}
 
 
 
 
 
 }
 }


  
 
   
    
    

 void ad(){
    digitalWrite(4,HIGH);
    //  digitalWrite(13,HIGH);
    digitalWrite(9,HIGH);
    digitalWrite(10,LOW);
    //digitalWrite(11,velDerecha);
    analogWrite(11,velDerecha);
    digitalWrite(12,LOW);


 
  
  } 
  void at(){
  digitalWrite(4,HIGH);
      // digitalWrite(13,HIGH);
  digitalWrite(9,LOW);
  analogWrite(10,velDerecha);
  //digitalWrite(10,velDerecha);
  digitalWrite(11,LOW);
  digitalWrite(12,HIGH);


} 
  void st(){
   digitalWrite(4,LOW);
    //  digitalWrite(13,LOW);
   digitalWrite(9,LOW);
   digitalWrite(10,LOW);
   digitalWrite(11,LOW);
   digitalWrite(12,LOW);


} 
void dch(){
   digitalWrite(4,HIGH);
  //digitalWrite(13,HIGH);
   digitalWrite(9,velDerecha);
   analogWrite(10,LOW);
   digitalWrite(11,LOW);

  // digitalWrite(10,velDerecha);

   digitalWrite(12,HIGH);
}



 
 void iz(){
   digitalWrite(4,HIGH);
    // digitalWrite(13,HIGH);
   digitalWrite(9,LOW);
   digitalWrite(10,HIGH);
 //  digitalWrite(11,velDerecha);

   analogWrite(11,velDerecha);
   digitalWrite(12,LOW);

 
  
  }  
  void stepperIzquierda()            //Avanza un paso
   {  digitalWrite( IN1, Paso[Steps][ 0] );
      digitalWrite( IN2, Paso[Steps][ 1] );
      digitalWrite( IN3, Paso[Steps][ 2] );
      digitalWrite( IN4, Paso[Steps][ 3] );
   
      Steps++;
          Steps = ( Steps + 4) % 4 ;

          Serial.println(Steps);
   }
     void stepperDerecha()            //Avanza un paso
   {  digitalWrite( IN4, Paso[Steps][ 0] );
      digitalWrite( IN3, Paso[Steps][ 1] );
      digitalWrite( IN2, Paso[Steps][ 2] );
      digitalWrite( IN1, Paso[Steps][ 3] );
      Steps++;
      
    
      
          Steps = ( Steps + 4) % 4 ;
          Serial.println(Steps);
   }
   void lowAllPaso(){
      digitalWrite(4,HIGH);
    //  digitalWrite(13,HIGH);
      digitalWrite( IN4, LOW);
      digitalWrite( IN3,LOW);
      digitalWrite( IN2, LOW );
      digitalWrite( IN1, LOW);
    }  
     void calcularZeroCamera(boolean vaDerecha){
      if(vaDerecha){
       
      
    if(pasoDerecha==2048){
          pasoDerecha=0;
        }
        
        if(pasoIzquierda>0){
          pasoIzquierda--;
        }
        else{
        pasoDerecha++;
        }
        
         Serial.println(pasoDerecha);
      }else{
          
         if(pasoIzquierda==2048){
          pasoIzquierda=0;
        }
        if(pasoDerecha>0){
          pasoDerecha--;
        }else{
          pasoIzquierda++;
        }

        Serial.println(pasoDerecha);
      }
      
 }
  
    
   void volverToZero(){
     //Si paso izquierda superior de paso derecha 
if(pasoIzquierda>pasoDerecha){
    //Si paso Izquierda menor de 1024 volvemos por la derecha
    if(pasoIzquierda<1024){
for(int i=0;i<pasoIzquierda;i++){
    stepperDerecha();
    delay(velGiro);
  }
   pasoDerecha=0;
  pasoIzquierda=0;
}


else{
   //Si paso Izquierda mayor que 1024 volvemos por la Izquierda
  for(int i=0;i<2048-pasoIzquierda;i++){
    stepperIzquierda();
    delay(velGiro);
  }
   pasoDerecha=0;
  pasoIzquierda=0;
}
  }
  
  
 else{
    //Si pasoIzquierda menor que pasoDerecha
    if(pasoDerecha<1024){
      //Si paso derecha menor que 1024 volviemos por la izquierda
     for(int i=0;i<pasoDerecha;i++){
    stepperIzquierda();
    delay(velGiro);
  }
  pasoDerecha=0;
  pasoIzquierda=0;
  }
  else{
     //Si paso derecha mayor que 1024 volviemos por la derecha
    
     for(int i=0;i<2048-pasoDerecha;i++){
    stepperDerecha();
    delay(velGiro);
  }
  pasoDerecha=0;
  pasoIzquierda=0;
  }
}
}
   void volverToMarchaAtras(){
   //Si paso izquierda superior de paso derecha 
  if(pasoIzquierda>pasoDerecha){
    //Si paso Izquierda menor de 1024 volvemos por la derecha
    if(pasoIzquierda<1024){
for(int i=0;i<1024-pasoIzquierda;i++){
    stepperIzquierda();
    delay(velGiro);
  }
   pasoDerecha=0;
  pasoIzquierda=1024;
}else{
   //Si paso Izquierda mayor que 1024 volvemos por la Izquierda
  for(int i=0;i<pasoIzquierda-1024;i++){
    stepperDerecha();
    delay(velGiro);
  }
   pasoDerecha=0;
  pasoIzquierda=1024;
}
  }else{
    //Si pasoIzquierda menor que pasoDerecha
    if(pasoDerecha<1024){
      //Si paso derecha menor que 1024 volviemos por la izquierda
     for(int i=0;i<1024-pasoDerecha;i++){
    stepperDerecha();
    delay(velGiro);
  }
  pasoDerecha=1024;
  pasoIzquierda=0;
  }else{
     //Si paso derecha mayor que 1024 volviemos por la derecha
    
     for(int i=0;i<pasoDerecha-1024;i++){
    stepperIzquierda();
    delay(velGiro);
  }
  pasoDerecha=1024;
  pasoIzquierda=0;
  }
}
    }  
