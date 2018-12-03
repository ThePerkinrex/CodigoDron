
// REMOTE INPUT
#define CH1 2 // Left/Right
#define CH2 3 // Forward/Backward
#define CH3 4 // Throttle
#define CH4 5 // Rotate
#define CH5 6 // SWA
#define CH6 7 // VRA
//                    /\
// MOTOR OUTPUT       ||
#define M1 8  //    M1  M2  //
#define M2 9  //      \/    //
#define M3 10 //      /\    //
#define M4 11 //    M3  M4  //

#define DECREMENT 4

#define DEBUG true


void setup() {
  if(DEBUG){
    Serial.begin(9600);
  }
  
  pinMode(CH1, INPUT);
  pinMode(CH2, INPUT);
  pinMode(CH3, INPUT);
  pinMode(CH4, INPUT);
  pinMode(CH5, INPUT);
  pinMode(CH6, INPUT);

  pinMode(M1, OUTPUT);
  pinMode(M2, OUTPUT);
  pinMode(M3, OUTPUT);
  pinMode(M4, OUTPUT);
}

void loop() {
  unsigned long ch1 = map(pulseIn(CH1, HIGH),980, 1940, 1000, 1800); //R <>
  unsigned long ch2 = map(pulseIn(CH1, HIGH),980, 1940, 1000, 1800); //R /\ \/
  unsigned long ch3 = map(pulseIn(CH3, HIGH),980, 1940, 1000, 1800); //THROTTLE
  unsigned long ch4 = map(pulseIn(CH4, HIGH),980, 1940, 1000, 1800); //L <>
  
  // AUX
  unsigned long ch5 = map(pulseIn(CH5, HIGH),980, 1940, 1000, 1800); //SWA
  unsigned long ch6 = map(pulseIn(CH6, HIGH),980, 1940, 1000, 1800); //VRA
  if(DEBUG){
    Serial.print("CH1:\t");
    Serial.print(ch1);
    Serial.print("; CH2:\t");
    Serial.print(ch2);
    Serial.print("; CH3:\t");
    Serial.print(ch3);
    Serial.print("; CH4:\t");
    Serial.print(ch4);
    Serial.print("; CH5:\t");
    Serial.print(ch5);
    Serial.print("; CH6:\t");
    Serial.print(ch6);
  }
  unsigned long throttle = ch3;
  Serial.print("; THR:\t");
  Serial.print(throttle);
  unsigned long change1  = (ch1-900)/DECREMENT - (ch2 - 900)/DECREMENT + ch3 - (ch4 - 900)/DECREMENT; // LF
  unsigned long change2  = - (ch1-900)/DECREMENT - (ch2 - 900)/DECREMENT + ch3 + (ch4 - 900)/DECREMENT; // RF
  unsigned long change3  = 0; // LB
  unsigned long change4  = 0; // RB
  Serial.print("; M1:\t");
  Serial.println(change1     );
  /*
   * base -> thottle -> CH3
   * 
   * CH1 ++ -> LB+LF++ && RB+RF--
   * CH2 ++ -> LB+RB++ && RF+LF--
   * CH3 ++ -> LB+LF+RB+RF++
   * CH4 ++ -> LB+RF++ && RB+LF--
   * 
   * 
   */
  pulseOut(M1, throttle);
  //pulseOut(M2, throttle);
  
}

void pulseOut(int pin, unsigned long pwm){
  digitalWrite(pin, HIGH);
  delayMicroseconds(pwm);
  digitalWrite(pin, LOW);
}

