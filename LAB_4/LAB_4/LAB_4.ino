int P1L0 = PD_0;
int P1L1 = PD_1;
int P1L2 = PD_2;
int P1L3 = PD_3;
int P1L4 = PE_1;
int P1L5 = PE_2;
int P1L6 = PE_3;
int P1L7 = PB_5;

int P2L0 = PB_0;
int P2L1 = PB_1;
int P2L2 = PE_4;
int P2L3 = PE_5;
int P2L4 = PB_4;
int P2L5 = PA_5;
int P2L6 = PA_6;
int P2L7 = PA_7;

int ROJO = RED_LED;
int VERDE = GREEN_LED;

const int P1 = PUSH1;
const int P2 = PUSH2;

int Pl1 = 0;
int Pl2 = 0;

int anti1 = 0;
int anti2 = 0;

int CP1 = 0;
int CP2 = 0;

int sflag = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(P1L0,OUTPUT);
  pinMode(P1L1,OUTPUT);
  pinMode(P1L2,OUTPUT);
  pinMode(P1L3,OUTPUT);
  pinMode(P1L4,OUTPUT);
  pinMode(P1L5,OUTPUT);
  pinMode(P1L6,OUTPUT);
  pinMode(P1L7,OUTPUT);

  pinMode(P2L0,OUTPUT);
  pinMode(P2L1,OUTPUT);
  pinMode(P2L2,OUTPUT);
  pinMode(P2L3,OUTPUT);
  pinMode(P2L4,OUTPUT);
  pinMode(P2L5,OUTPUT);
  pinMode(P2L6,OUTPUT);
  pinMode(P2L7,OUTPUT);

  pinMode(P1,INPUT_PULLUP);
  pinMode(P2,INPUT_PULLUP);

  pinMode(ROJO,OUTPUT);
  pinMode(VERDE,OUTPUT);

 
  delay(5000);
  semaforo();
}

void loop() {
  // put your main code here, to run repeatedly: 
  
  Pl1 = digitalRead(P1);
  delay (100);
  Pl2 = digitalRead(P2);
  delay (100);
  

  S
  Player1();
  Player2();
  win();
  
  //if (Pl1 == 0 or Pl2 == 0){
    //semaforo();
  //}
  
}

void semaforo(void){
   digitalWrite(ROJO, HIGH); 
   digitalWrite(VERDE, LOW); 
   delay(1000);

   digitalWrite(ROJO, HIGH); 
   digitalWrite(VERDE, HIGH); 
   delay(1000);

   digitalWrite(ROJO, LOW); 
   digitalWrite(VERDE, HIGH); 
   delay(1000);

   digitalWrite(ROJO, LOW); 
   digitalWrite(VERDE, LOW); 
      
}

void win (void){
    if (CP2 == 8 && CP1 < 8){
     digitalWrite(ROJO, HIGH); 
     digitalWrite(VERDE, LOW);
    }
    if (CP1 == 8 && CP2 < 8){
     digitalWrite(ROJO, LOW); 
     digitalWrite(VERDE, HIGH);
    }
}

void Player1(void){
  if (Pl1 == 0){
    anti1 = 1;
  }
  
  if (Pl1 == 1 && anti1 == 1){
   anti1 = 0;
   delay(50);
   CP1++;
    }
    switch (CP1){
  case 0:
    digitalWrite(P1L0, LOW);  
    digitalWrite(P1L1, LOW); 
    digitalWrite(P1L2, LOW); 
    digitalWrite(P1L3, LOW); 
    digitalWrite(P1L4, LOW); 
    digitalWrite(P1L5, LOW); 
    digitalWrite(P1L6, LOW);
    digitalWrite(P1L7, LOW);
    break;
    
  case 1:
    digitalWrite(P1L0, HIGH);  
    digitalWrite(P1L1, LOW); 
    digitalWrite(P1L2, LOW); 
    digitalWrite(P1L3, LOW); 
    digitalWrite(P1L4, LOW); 
    digitalWrite(P1L5, LOW); 
    digitalWrite(P1L6, LOW);
    digitalWrite(P1L7, LOW);
    break;
    
  case 2:
    digitalWrite(P1L0, LOW);  
    digitalWrite(P1L1, HIGH); 
    digitalWrite(P1L2, LOW); 
    digitalWrite(P1L3, LOW); 
    digitalWrite(P1L4, LOW); 
    digitalWrite(P1L5, LOW); 
    digitalWrite(P1L6, LOW);
    digitalWrite(P1L7, LOW);
    break;
    
  case 3:
    digitalWrite(P1L0, LOW);  
    digitalWrite(P1L1, LOW); 
    digitalWrite(P1L2, HIGH); 
    digitalWrite(P1L3, LOW); 
    digitalWrite(P1L4, LOW); 
    digitalWrite(P1L5, LOW); 
    digitalWrite(P1L6, LOW);
    digitalWrite(P1L7, LOW);
    break;
    
  case 4:
    digitalWrite(P1L0, LOW);  
    digitalWrite(P1L1, LOW); 
    digitalWrite(P1L2, LOW); 
    digitalWrite(P1L3, HIGH); 
    digitalWrite(P1L4, LOW); 
    digitalWrite(P1L5, LOW); 
    digitalWrite(P1L6, LOW);
    digitalWrite(P1L7, LOW);
    break;
    
  case 5:
    digitalWrite(P1L0, LOW);  
    digitalWrite(P1L1, LOW); 
    digitalWrite(P1L2, LOW); 
    digitalWrite(P1L3, LOW); 
    digitalWrite(P1L4, HIGH); 
    digitalWrite(P1L5, LOW); 
    digitalWrite(P1L6, LOW);
    digitalWrite(P1L7, LOW);
    break;
    
  case 6:
    digitalWrite(P1L0, LOW);  
    digitalWrite(P1L1, LOW); 
    digitalWrite(P1L2, LOW); 
    digitalWrite(P1L3, LOW); 
    digitalWrite(P1L4, LOW); 
    digitalWrite(P1L5, HIGH); 
    digitalWrite(P1L6, LOW);
    digitalWrite(P1L7, LOW);
    break;
    
  case 7:
    digitalWrite(P1L0, LOW);  
    digitalWrite(P1L1, LOW); 
    digitalWrite(P1L2, LOW); 
    digitalWrite(P1L3, LOW); 
    digitalWrite(P1L4, LOW); 
    digitalWrite(P1L5, LOW); 
    digitalWrite(P1L6, HIGH);
    digitalWrite(P1L7, LOW);
    break;
    
  case 8:
    digitalWrite(P1L0, LOW);  
    digitalWrite(P1L1, LOW); 
    digitalWrite(P1L2, LOW); 
    digitalWrite(P1L3, LOW); 
    digitalWrite(P1L4, LOW); 
    digitalWrite(P1L5, LOW); 
    digitalWrite(P1L6, LOW);
    digitalWrite(P1L7, HIGH);
    break;

  }
}

void Player2 (void){
  if (Pl2 == 0){
    anti2 = 1;
  }
  
  if (Pl2 == 1 && anti2 == 1){
   anti2 = 0;
   delay(50);
   CP2++;
    }
    
switch (CP2){
  case 0:
    digitalWrite(P2L0, LOW);  
    digitalWrite(P2L1, LOW); 
    digitalWrite(P2L2, LOW); 
    digitalWrite(P2L3, LOW); 
    digitalWrite(P2L4, LOW); 
    digitalWrite(P2L5, LOW); 
    digitalWrite(P2L6, LOW);
    digitalWrite(P2L7, LOW);
    break;
    
  case 1:
    digitalWrite(P2L0, HIGH);  
    digitalWrite(P2L1, LOW); 
    digitalWrite(P2L2, LOW); 
    digitalWrite(P2L3, LOW); 
    digitalWrite(P2L4, LOW); 
    digitalWrite(P2L5, LOW); 
    digitalWrite(P2L6, LOW);
    digitalWrite(P2L7, LOW);
    break;
    
  case 2:
    digitalWrite(P2L0, LOW);  
    digitalWrite(P2L1, HIGH); 
    digitalWrite(P2L2, LOW); 
    digitalWrite(P2L3, LOW); 
    digitalWrite(P2L4, LOW); 
    digitalWrite(P2L5, LOW); 
    digitalWrite(P2L6, LOW);
    digitalWrite(P2L7, LOW);
    break;
    
  case 3:
    digitalWrite(P2L0, LOW);  
    digitalWrite(P2L1, LOW); 
    digitalWrite(P2L2, HIGH); 
    digitalWrite(P2L3, LOW); 
    digitalWrite(P2L4, LOW); 
    digitalWrite(P2L5, LOW); 
    digitalWrite(P2L6, LOW);
    digitalWrite(P2L7, LOW);
    break;

    
  case 4:
    digitalWrite(P2L0, LOW);  
    digitalWrite(P2L1, LOW); 
    digitalWrite(P2L2, LOW); 
    digitalWrite(P2L3, HIGH); 
    digitalWrite(P2L4, LOW); 
    digitalWrite(P2L5, LOW); 
    digitalWrite(P2L6, LOW);
    digitalWrite(P2L7, LOW);
    break;
    
  case 5:
    digitalWrite(P2L0, LOW);  
    digitalWrite(P2L1, LOW); 
    digitalWrite(P2L2, LOW); 
    digitalWrite(P2L3, LOW); 
    digitalWrite(P2L4, HIGH); 
    digitalWrite(P2L5, LOW); 
    digitalWrite(P2L6, LOW);
    digitalWrite(P2L7, LOW);
    break;
    
  case 6:
    digitalWrite(P2L0, LOW);  
    digitalWrite(P2L1, LOW); 
    digitalWrite(P2L2, LOW); 
    digitalWrite(P2L3, LOW); 
    digitalWrite(P2L4, LOW); 
    digitalWrite(P2L5, HIGH); 
    digitalWrite(P2L6, LOW);
    digitalWrite(P2L7, LOW);
     break;
       
  case 7:
    digitalWrite(P2L0, LOW);  
    digitalWrite(P2L1, LOW); 
    digitalWrite(P2L2, LOW); 
    digitalWrite(P2L3, LOW); 
    digitalWrite(P2L4, LOW); 
    digitalWrite(P2L5, LOW); 
    digitalWrite(P2L6, HIGH);
    digitalWrite(P2L7, LOW);
    break;
       
  case 8:
    digitalWrite(P2L0, LOW);  
    digitalWrite(P2L1, LOW); 
    digitalWrite(P2L2, LOW); 
    digitalWrite(P2L3, LOW); 
    digitalWrite(P2L4, LOW); 
    digitalWrite(P2L5, LOW); 
    digitalWrite(P2L6, LOW);
    digitalWrite(P2L7, HIGH);
    break;  

  }
}
