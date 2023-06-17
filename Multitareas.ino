#include "AsyncTaskLib.h"
#include "DHTStable.h"

#define DEBUG(a) Serial.print(millis()); Serial.print(": "); Serial.println(a);
#define DHT11_PIN       5

DHTStable DHT;



void leerFotoresistor(void);
void leerTemperatura(void);
AsyncTask asyncTask(2000, true, leerFotoresistor);
AsyncTask asyncTask1(4000, true, leerTemperatura);


const int photocellPin = A0;
int outputValue = 0;

void setup()
{
  Serial.begin(9600);
  Serial.println("Starting");

  asyncTask.Start();
  asyncTask1.Start();
}

void loop()
{
  asyncTask.Update();
  asyncTask1.Update();
}

void leerFotoresistor(void)
{
  outputValue = analogRead(photocellPin);
  Serial.println(outputValue);
}

void leerTemperatura(void)
{
    Serial.print("DHT11, \t");
  int chk = DHT.read11(DHT11_PIN);
  switch (chk)
  {
    case DHTLIB_OK:  
      Serial.print("OK,\t"); 
      break;
    case DHTLIB_ERROR_CHECKSUM: 
      Serial.print("Checksum error,\t"); 
      break;
    case DHTLIB_ERROR_TIMEOUT: 
      Serial.print("Time out error,\t"); 
      break;
    default: 
      Serial.print("Unknown error,\t"); 
      break;
  }
  Serial.print(DHT.getHumidity(), 1);
  Serial.print(",\t");
  Serial.println(DHT.getTemperature(), 1);
}