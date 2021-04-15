/* 
 * Created:   qua abr 14 2021
 * Processor: Arduino Uno
 * Compiler:  Arduino AVR
 * Name of the project: ArduinoWave - Wave generator using Arduino UNO and R-2R DAC
 * Developer: José L. Natalício
 * Revision: 2.0
 */

/*---------------------- Hardware ------------------------*/

#define ledQuad   4
#define ledSerra  5
#define ledSeno   6
#define select    7

/*--------------------------------------------------------*/

/*--------------- variáveis iniciais ---------------------*/

int saida = 0,
    selectFlag = 0,
    ton = 940,
    toff = 60;

char seno_LUT[256] = { 32,32,33,34,35,35,36,37,38,38,39,40,41,41,42,43,44,44,45,46,46,47,48,48,49,50,50,51,52,52,
                       53,53,54,54,55,55,56,56,57,57,58,58,59,59,59,60,60,60,61,61,61,61,62,62,62,62,62,63,63,63,
                       63,63,63,63,63,63,63,63,63,63,63,62,62,62,62,62,62,61,61,61,61,60,60,60,59,59,58,58,58,57,
                       57,56,56,55,55,54,54,53,52,52,51,51,50,49,49,48,47,47,46,45,45,44,43,43,42,41,40,40,39,38,
                       37,37,36,35,34,33,33,32,31,30,30,29,28,27,26,26,25,24,23,23,22,21,20,20,19,18,18,17,16,16,
                       15,14,14,13,12,12,11,11,10,9,9,8,8,7,7,6,6,5,5,5,4,4,3,3,3,2,2,2,2,1,1,1,1,1,1,0,0,0,0,0,
		                   0,0,0,0,0,0,0,0,0,1,1,1,1,1,2,2,2,2,3,3,3,4,4,4,5,5,6,6,7,7,8,8,9,9,10,10,11,11,12,13,13,
		                   14,15,15,16,17,17,18,19,19,20,21,22,22,23,24,25,25,26,27,28,28,29,30,31,32 };

/*--------------------------------------------------------*/

/*--------------------- funções --------------------------*/

void gerarOndaQuadrada();
void gerarOndaDenteSerra();
void gerarOndaSenoidal();

/*--------------------------------------------------------*/

void setup() {
  // put your setup code here, to run once:
    pinMode(ledSerra, OUTPUT);
    pinMode(ledQuad, OUTPUT);
    pinMode(ledSeno, OUTPUT);

    DDRB |= B00111111;
    
    pinMode(select, INPUT_PULLUP);

    digitalWrite(ledSerra, HIGH);
    digitalWrite(ledQuad, HIGH);
    digitalWrite(ledSeno, HIGH);
    delay(1000);
    digitalWrite(ledSerra, LOW);
    digitalWrite(ledQuad, LOW);
    digitalWrite(ledSeno, LOW);
    delay(500);
    
    PORTB = 0;
    saida = 0;
}

void loop() {
  // put your main code here, to run repeatedly:
      
      if (!digitalRead(select))
      {
          selectFlag = 1;
          delay(10);
      }
          if (digitalRead(select) && selectFlag)
          {
              selectFlag = 0;
              saida++;
              if (saida > 3) saida = 0;
          }

      switch (saida)
      {
           case 1:
                 gerarOndaQuadrada();
           break;

           case 2:
                 gerarOndaDenteSerra();
           break;

           case 3:
                 gerarOndaSenoidal();
           break;

           default:
                 digitalWrite(ledSerra, LOW);
                 digitalWrite(ledQuad, LOW);
                 digitalWrite(ledSeno, LOW);
                 PORTB = 0;
           break;
      }
}

void gerarOndaQuadrada()
{
      digitalWrite(ledSerra, LOW);
      digitalWrite(ledQuad, HIGH);
      digitalWrite(ledSeno, LOW);
      PORTB = 63;
      delayMicroseconds(500);
      PORTB = 0;
      delayMicroseconds(500);
}

void gerarOndaDenteSerra()
{
      digitalWrite(ledSerra, HIGH);
      digitalWrite(ledQuad, LOW);
      digitalWrite(ledSeno, LOW);
      PORTB++;
      if (PORTB > 64) PORTB = 0;
      delayMicroseconds(1);
}

void gerarOndaSenoidal()
{
      digitalWrite(ledSerra, LOW);
      digitalWrite(ledQuad, LOW);
      digitalWrite(ledSeno, HIGH);
	       
      for (int i = 0; i < 256; i++)
      {
          PORTB = seno_LUT[i];
          delayMicroseconds(3);
      }
}
