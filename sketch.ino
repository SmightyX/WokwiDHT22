#include <DHT.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define DHTPIN 15
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  Serial.begin(115200);
    if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
    }

  dht.begin();
}

void loop() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();
      
  if (isnan(h) || isnan(t)) 
   {
    Serial.println("Failed to read from DHT sensor!");
   return;
   }
  Serial.print("Temperature: ");
  Serial.println(String(t).c_str());
    Serial.print("Humidity: ");
  Serial.println(String(h).c_str());

  display.setCursor(0,0);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.print("DHT22");
  display.startscrollright(0x00, 0x00);

  display.setCursor(0, 20);
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.print("S:");
  display.print(t);
  display.setCursor(115, 28);
  display.setTextSize(1);
  display.print("C");
  display.display();

  display.setCursor(0, 45);
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.print("K:");
  display.print(h);
  display.setCursor(115, 53);
  display.setTextSize(1);
  display.print("rH");
  display.display();

  display.clearDisplay();
  delay(5000); // this speeds up the simulation
}
