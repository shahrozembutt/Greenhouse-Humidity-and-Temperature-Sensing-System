//Libraries
#include <DHT.h>
#include <Servo.h>

//Constants
#define DHTPIN 4     // what pin we're connected to
#define DHTTYPE DHT11   // DHT 11  (AM2302)
// Initialize DHT sensor for normal 16mhz Arduino
DHT dht(DHTPIN, DHTTYPE);
Servo s;


int chk;
float humidity;  //humidity 
float temperature; //temperature 

void setup()
{
  Serial.begin(9600);
  dht.begin();
  s.attach(9);
  s.write(90);
    
}

void motor(){
  for (int i=0; i<=180; i+=1){
    s.write(i);
    delay(15);
  }
}

void functions(){
  if (temperature > 26 && temperature <= 28){
    Serial.println("Greenhouse is running at optimal temperature and humidity levels!");
    Serial.println("Ventilation system paused.....");
  }
  
  else if (temperature > 28){
    Serial.println("Overheat Alert!!!");
    Serial.println("Ventilation system triggered.....");
    Serial.println("");
    while(temperature > 28){
      motor();
      temperature = dht.readTemperature();
      Serial.println(temperature);
    }

    Serial.println("Optimum temperature reached. Ventilation system paused!");
  }

  else if (temperature < 24){
    Serial.println("Temperature Drop Alert!!!");
    Serial.println("Please make sure that all the doors and ventilation outlets are closed.");
  }
}

void loop()
{
    //Read data and store to humidity and temperature
    humidity = dht.readHumidity();
    temperature = dht.readTemperature();

    //Print readings
    Serial.print("");
    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.print("%");
    Serial.println("");
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.print(" Celsius");
    Serial.println("");

    functions();

    delay(4000); //Delay by 4 seconds
}



   
