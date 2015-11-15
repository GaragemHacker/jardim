#define PIR 2
#define LED 11


class Flasher
{
  int ledPin;                           // port number of the led pin
  long OnTime;                          // ON time in milliseconds; remenber 1000 ms = 1 s
  long OffTime;                         // OFF time in milliseconds

  // these maintain the current state
  int ledState;                         // used to set the led
  unsigned long previousMillis;         // the last time led was updated 
  

  // Constructor: creates a Flasher and initializes the member variables and state
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
    // check to change the state of the led
    unsigned long currentMillis = millis();

    if ((ledState == HIGH) && (currentMillis - previousMillis >= OnTime))
    {
       ledState = LOW; // led OFF
       previousMillis = currentMillis; // save the time
       digitalWrite(ledPin, ledState); // Update led  
    }  
    else if ((ledState == LOW) && (currentMillis - previousMillis >= OffTime))
    {
       ledState = HIGH; // led ON
       previousMillis = currentMillis; // save the time
       digitalWrite(ledPin, ledState); // Update led 
    }
  }

  void Desligar()                     // turn led off
  {
    digitalWrite(ledPin, LOW);
  }
};
  

Flasher led1(LED, 400, 200);

void setup()
{
  pinMode(PIR, INPUT); // Set PIR pin Port
}


unsigned long readSensor() 
{
  // Ler a duração do pulso do sensor em nível alto
  return pulseIn(PIR, HIGH, 3E6); 
}

void loop()
{ 
  unsigned long sensorIn = readSensor();
  
  if (sensorIn > 1E6 && sensorIn < 3E6) // Testar se a largura do pulso está entre 1 e 3 segundos
  {
     led1.Update();    // Acionar o Led
  } 
  else 
  {
     led1.Desligar();  // Desligar o Led
     
  }

}


