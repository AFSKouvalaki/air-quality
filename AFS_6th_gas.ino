#include <DHT.h>
#include <DHT_U.h>

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Fonts/FreeSerif9pt7b.h>

#define DHT11_PIN 4
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
DHT dht11(DHT11_PIN, DHT11);

int sensorValue;
int digitalValue;
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup()
{
  dht11.begin();

  Serial.begin(9600); // sets the serial port to 9600
  Serial.begin(115200);

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println("SSD1306 allocation failed");
    for(;;);
  }
  delay(2000);

 
  
  delay(2000); 
  pinMode(13, OUTPUT);
}

void loop()
{
  float humi  = dht11.readHumidity();
  
  float tempC = dht11.readTemperature();
  

  sensorValue = analogRead(0); // read analog input pin 0
  //digitalValue = digitalRead(2);
  if (sensorValue > 150)
  {
    digitalWrite(13, HIGH);
    

  }
  else
    digitalWrite(13, LOW);

  if (isnan(humi) || isnan(tempC)) {
    Serial.println("Failed to read from DHT11 sensor!");
    } else {
    Serial.print("Temperature: ");
    Serial.print(tempC);
    Serial.print("°C ~ ");
    Serial.print("DHT11# Humidity: ");
    Serial.print(humi);
    Serial.print("%");

    Serial.print("  |  "); 

   
  }
  
  
  Serial.println(sensorValue, DEC); // prints the value read
  Serial.println(digitalValue, DEC);
  display.setFont(&FreeSerif9pt7b);
  display.clearDisplay();
  display.setTextSize(1);             
  display.setTextColor(WHITE);        
  display.setCursor(0,20);             
  display.print("CO2 value: ");
  display.println(sensorValue, DEC);
  display.print("Temp:");
  display.print(tempC);
  display.print("°C ~ ");
  display.println("  |  "); 
  display.print("Hum: ");
  display.print(humi);
  display.print("%");
  display.display();
  delay(2000);
}
