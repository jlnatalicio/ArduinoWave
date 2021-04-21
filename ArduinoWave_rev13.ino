/* 
 * Created:   qua abr 21 2021
 * Processor: Arduino Uno
 * Compiler:  Arduino AVR
 * Name of the project: ArduinoWave - Wave generator using Arduino UNO and R-2R DAC
 * Developer: José L. Natalício
 * Revision: 1.3
 */

/*---------------------- Hardware ------------------------*/

#define ledQuad   8
#define ledSerra  9
#define ledSeno   10
#define select    11

/*--------------------------------------------------------*/

/*--------------- variáveis iniciais ---------------------*/

uint8_t saida = 0,
        selectFlag = 0,
        seno_LUT[256] = { 128,131,134,137,140,143,146,149,152,156,159,162,165,168,171,174,176,179,182,185,188,191,193,196,199,201,204,206,209,211,
                          213,216,218,220,222,224,226,228,230,232,234,235,237,239,240,242,243,244,246,247,248,249,250,251,251,252,253,253,254,254,
                          254,255,255,255,255,255,255,255,254,254,253,253,252,252,251,250,249,248,247,246,245,244,242,241,239,238,236,235,233,231,
                          229,227,225,223,221,219,217,215,212,210,207,205,202,200,197,195,192,189,186,184,181,178,175,172,169,166,163,160,157,154,
                          151,148,145,142,138,135,132,129,126,123,120,117,113,110,107,104,101,98,95,92,89,86,83,80,77,74,71,69,66,63,60,58,55,53,
                          50,48,45,43,40,38,36,34,32,30,28,26,24,22,20,19,17,16,14,13,11,10,9,8,7,6,5,4,3,3,2,2,1,1,0,0,0,0,0,0,0,1,1,1,2,2,3,4,4,
                          5,6,7,8,9,11,12,13,15,16,18,20,21,23,25,27,29,31,33,35,37,39,42,44,46,49,51,54,56,59,62,64,67,70,73,76,79,81,84,87,90,93,
                          96,99,103,106,109,112,115,118,121,124,128 };

/*--------------------------------------------------------*/

/*--------------------- funções --------------------------*/

void gerarOndaQuadrada();
void gerarOndaDenteSerra();
void gerarOndaSenoidal();

/*--------------------------------------------------------*/

void setup()
{
  // put your setup code here, to run once:
    pinMode(ledSerra, OUTPUT);
    pinMode(ledQuad, OUTPUT);
    pinMode(ledSeno, OUTPUT);

    DDRD |= B11111111; // configurando todos os bits do PORTD como saída
    
    pinMode(select, INPUT_PULLUP);

    digitalWrite(ledSerra, HIGH);
    digitalWrite(ledQuad, HIGH);
    digitalWrite(ledSeno, HIGH);
    delay(1000);
    digitalWrite(ledSerra, LOW);
    digitalWrite(ledQuad, LOW);
    digitalWrite(ledSeno, LOW);
    delay(500);
    
    PORTD = 0;
    saida = 0;
}

void loop()
{
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
                PORTD = 0;
            break;
        }
}

void gerarOndaQuadrada()
{
    digitalWrite(ledSerra, LOW);
    digitalWrite(ledQuad, HIGH);
    digitalWrite(ledSeno, LOW);
    PORTD = 255;
    delayMicroseconds(500);
    PORTD = 0;
    delayMicroseconds(500);
}

void gerarOndaDenteSerra()
{
    digitalWrite(ledSerra, HIGH);
    digitalWrite(ledQuad, LOW);
    digitalWrite(ledSeno, LOW);
    PORTD++;
    if (PORTD > 255) PORTD = 0;
    delayMicroseconds(1);
}

void gerarOndaSenoidal()
{
    digitalWrite(ledSerra, LOW);
    digitalWrite(ledQuad, LOW);
    digitalWrite(ledSeno, HIGH);
         
    for (int i = 0; i < 256; i++)
    {
        PORTD = seno_LUT[i];
        delayMicroseconds(5);
    }
}
