/*

   Som de Grilos e Fita de Leds ativados por um sensor de presença (PIR) 

   Cricket sound's and LED ribbon controlled by a PIR. 

   https://github.com/Garagem-Hacker/jardim

*/

#define PIR       02                    // PIR input pin
#define LED       12                    // LED output pin
#define BUZZER    05                    // Buzzer output pin

class Grilo
{
  #define PULSOS 7
  #define DURACAO_PULSO 17
  #define PAUSA 720
  #define FREQUENCIA 3920


  int pinoFalante;
    
  int griloState;
  unsigned long previousMillis;

  public:
  
  Grilo(int pin)
  {
     pinoFalante = pin;
     pinMode(pinoFalante, OUTPUT);

     previousMillis = 0;
     
  }

  void Cantar()
  {
    unsigned long currentMillis = millis();

    if (currentMillis - previousMillis >= PAUSA) 
    {
       for (int i = 0; i < PULSOS; i++) {
           tone(pinoFalante, FREQUENCIA, DURACAO_PULSO);
        delay(DURACAO_PULSO*2);
    }
    previousMillis = currentMillis;
    }
  }
};

class Flasher
{
  // Class Member Variables
  // These are initialized at startup
  int ledPin;      // the number of the LED pin
  long OnTime;     // milliseconds of on-time
  long OffTime;    // milliseconds of off-time

  // These maintain the current state
  int ledState;                 // ledState used to set the LED
  unsigned long previousMillis;   // will store last time LED was updated

  // Constructor - creates a Flasher 
  // and initializes the member variables and state
  public:
  Flasher(int pin, long on, long off)
  {
  ledPin = pin;
  pinMode(ledPin, OUTPUT);     
    
  OnTime = on;
  OffTime = off;
  
  ledState = LOW; 
  previousMillis = 0;
  }

  void Update()
  {
    // check to see if it's time to change the state of the LED
    unsigned long currentMillis = millis();
     
    if((ledState == HIGH) && (currentMillis - previousMillis >= OnTime))
    {
      ledState = LOW;  // Turn it off
      previousMillis = currentMillis;  // Remember the time
      digitalWrite(ledPin, ledState);  // Update the actual LED
    }
    else if ((ledState == LOW) && (currentMillis - previousMillis >= OffTime))
    {
      ledState = HIGH;  // turn it on
      previousMillis = currentMillis;   // Remember the time
      digitalWrite(ledPin, ledState);   // Update the actual LED
    }
  }

  void Desligar()
  {
    digitalWrite(ledPin, LOW);
  }
};


Grilo   grilo1(BUZZER);
Flasher led1(LED, 300, 300);

void setup()
{
  //Serial.begin(9600);
  pinMode(PIR, INPUT); // Set PIR pin input port
}

void loop()
{
  if (digitalRead(PIR) == HIGH)
  {
     int n = random(15000);   // alterar para aumentar ou diminuir o número de grilos cantantes.
     if (n == 437)            // grilos cantam apenas quando for sorteado esse número. 
     {
      grilo1.Cantar();
      //Serial.println(n);      
     }
     led1.Update();    
  }
  else
  {
    led1.Desligar();
  }
}

