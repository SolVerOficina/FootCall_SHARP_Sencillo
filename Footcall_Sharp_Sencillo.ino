/*#include <NewPing.h>

//#define TRIGGER_PIN1  6     //Sensor del medio, para cuando es solo una direccion
//#define ECHO_PIN1     7     
#define TRIGGER_PIN2  5  // 5 Sensor de subida, cercano al arduino
#define ECHO_PIN2     4  // 4
#define TRIGGER_PIN3  8  // 8 Sensor de bajada, alejado del arduino
#define ECHO_PIN3     9  // 9 */
#define RELAYS        2 
#define RELAYB        3
//#define MAX_DISTANCE 200
#define LED           10

//NewPing sonar1(TRIGGER_PIN2, ECHO_PIN2, MAX_DISTANCE);
// NewPing sonar2(TRIGGER_PIN2, ECHO_PIN2, MAX_DISTANCE);
// NewPing sonar3(TRIGGER_PIN3, ECHO_PIN3, MAX_DISTANCE);

int contador1 = 0;
int contadorloop = 0;
int contador2 = 0;
int contador3 = 0;
int contador4 = 0;
float dist_set_subida;
float dist_set_bajada;
float distancia2;
float distancia3;
unsigned long s = 0;
unsigned long b = 0;
unsigned long resta_subida = 0;
unsigned long resta_bajada = 0;
unsigned long tiempo = 10000UL;
bool band;
void setup() {
  
  Serial.begin(115200);
  pinMode(RELAYS,OUTPUT);
  pinMode(RELAYB,OUTPUT);
  pinMode(LED,OUTPUT);
  digitalWrite(RELAYS,LOW);
  digitalWrite(RELAYB,LOW);
 // Serial.println("-------------------------FOOTCALL-------------------------------");
 // Serial.println("----------------------V. BETA 1.4.0-------------------------------");  
      digitalWrite(LED,HIGH);
    delay(500);
    digitalWrite(LED,LOW);
    delay(500);
    digitalWrite(LED,HIGH);
    delay(500);
    digitalWrite(LED,LOW);

 SetDistance();
}

void(* resetFunc) (void) = 0; //declare reset function @ address 0

 void SetDistance(){
  Serial.println("-------------------------FOOTCALL-------------------------------");
  Serial.println("----------------------V. BETA 1.4.0-------------------------------");  
  float dist_subida = ADC0_promedio(50);
 Serial.println("DISTANCIA INICIAL:: ");
 Serial.print("SUBIDA: ");
 Serial.println(dist_subida);
  dist_set_subida = dist_subida + 11;
  Serial.println("EL BOTON ACTIVA A ESTA DISTANCIA: ");
  Serial.print("SUBIDA: ");
  Serial.println(dist_set_subida);
 // Serial.println("--------------------------------------------------------------");
 // Serial.println("--------------------------------------------------------------");
}

void loop() {

  contador1++;
  delay(300);
  contadorloop++;
  delay(300);
   Serial.println(contador4);
  // Serial.println(contadorloop);

  if(contador1 > 300){
 Serial.println("RESETEANDO SOFTWARE");
     digitalWrite(LED,HIGH);
    delay(500);
    digitalWrite(LED,LOW);
    delay(500);
    digitalWrite(LED,HIGH);
    delay(500);
    digitalWrite(LED,LOW);
    resetFunc();
  }

  if(contadorloop > 100){
 Serial.println("RESETEANDO DISTANCIA");
     digitalWrite(LED,HIGH);
    delay(500);
    digitalWrite(LED,LOW);
    delay(500);
    digitalWrite(LED,HIGH);
        delay(500);
    digitalWrite(LED,LOW);
    SetDistance();
    contadorloop = 0;
  }
  
  

  if(resta_subida>tiempo){
    if(band){
      delay(5000);
       digitalWrite(LED,LOW);
    }else{
      Serial.println("SE HABILIT?? EL SENSOR DE SUBIDA");
      digitalWrite(LED,LOW);
    }
   }

    float ADC_SHARP = ADC0_promedio(50);


    if (ADC_SHARP < dist_set_subida){
      //prende el LED
       Serial.print("NADA SUBIDA: ");
       Serial.println(ADC_SHARP);
       digitalWrite(LED,LOW);
       digitalWrite(RELAYS,LOW);
       contador2 = 0;
    }
    if(resta_subida < tiempo){
      Serial.println("SENSOR SUBIDA DESHABILITADO");   
      digitalWrite(LED,HIGH);
      digitalWrite(RELAYS,LOW);
    }    

// SENSOR DE SUBIDA-------------------------------------------------------------------------------------------
    resta_subida=millis()-s;
//     Serial.print("nmillis:");
  //  Serial.println(millis());
    Serial.print("Resta subida:");
    Serial.println(resta_subida);
    
 if (resta_subida > tiempo && ADC_SHARP > dist_set_subida && contador2 < 24){
    Serial.println("ACTIVADO SENSOR DE SUBIDA");
    Serial.println(ADC_SHARP);
    s = millis();
    resta_subida=millis()-s;
    Serial.println(s);
    digitalWrite(RELAYS,HIGH);
    digitalWrite(LED,HIGH);
    //digitalWrite(2,HIGH);
    contador4++;
    contador2++;
    delay(250);
  }

  /* if (millis() < tiempo && ADC_SHARP > 107 && contador2 < 24){
    Serial.println("ACTIVADO SENSOR DE SUBIDA POR PRIMERA VEZ EN LA VIDA");
    Serial.println(ADC_SHARP);
    s = millis();
    resta_subida=millis()-s;
    Serial.println(s);
    digitalWrite(RELAYS,HIGH);
    digitalWrite(LED,HIGH);
    //digitalWrite(2,HIGH);
    contador2++;
    delay(600);
  }*/

  if ( ADC_SHARP > dist_set_subida && contador2 >= 24) {
       Serial.println("BOTON DE SUBIDA TRABADO");
       //resetFunc();  //call reset
       digitalWrite(RELAYS,LOW);
       digitalWrite(LED, HIGH);
       delay(50);
       contador2++;
       delay(250);       
  }

// Si lleva mas de 1 minuto, se resetea el modulo
  if ( contador2 > 60 ){
    digitalWrite(LED,HIGH);
    delay(500);
    digitalWrite(LED,LOW);
    delay(500);
    digitalWrite(LED,HIGH);
    delay(500);
    digitalWrite(LED,LOW);
    Serial.println("Reseteando");
    delay(500);
    resetFunc();  //call reset
  } 
 

//  delay(300);
}


int ADC0_promedio(int n)
{
  long suma=0;
  for(int v=0;v<n;v++)
  {
    suma=suma+analogRead(A0);
  }  
  return(suma/n);
}

