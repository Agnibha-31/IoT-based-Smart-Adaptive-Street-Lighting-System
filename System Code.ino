// Replace with your own credentials and apis in place of '**********' in the code.
#define BLYNK_TEMPLATE_ID "**********"
#define BLYNK_TEMPLATE_NAME "**********"
#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>

// Define Blynk Authentication Token, WiFi credentials
char auth[] = "**********"; // Replace with your Blynk auth token
char ssid[] = "**********";        // Replace with your WiFi SSID
char pass[] = "**********";    // Replace with your WiFi Password

// Define pin numbers
#define IR1 13  // IR Sensor 2
#define IR2 12  // IR Sensor 1
#define LDR 35  // LDR Sensor
#define LED1 25 // LED 1
#define LED2 26 // LED 2
#define DHTPIN 4 // DHT22 Sensor connected to GPIO 4
#define DHTTYPE DHT22 // Define DHT22 sensor type

DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;

int ir1, ir2, ldr;
float humidity, temperature;

void sendSensorDataToBlynk() 
{
    // Read sensor values
    ir1 = digitalRead(IR1);
    ir2 = digitalRead(IR2);
    ldr = digitalRead(LDR);
    
    // Read temperature and humidity
    humidity = dht.readHumidity();
    temperature = dht.readTemperature();

    // Send values to Blynk
    Blynk.virtualWrite(V0, temperature);
    Blynk.virtualWrite(V1, humidity);

    // Print values in Serial Monitor
    Serial.println("IR1: " + String(ir2) + " | IR2: " + String(ir1) + " | LDR: " + String(ldr) + " | Temperature: " + String(temperature) + "°C | Humidity: " + String(humidity) + "% ");

    // Send messages to Blynk Terminal widget
    String message;



// When vehicle or object is present the IR Sensor always is in LOW STATE (0) & when vehicle or not object is present IR Sensor always is in HIGH STATE (1)
// When light is present the LDR Sensor always is in LOW STATE (0) & when light is not present LDR Sensor always is in HIGH STATE (1)

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
if (humidity > 95)  // highly foggy weather, values are high for great visibility
{
    if (ir1 == 1 && ldr == 1 && ir2 == 1) // No motion, dark environment
    { 
        ledcWrite(25, 1500);   // LED 1: Dim when high fog & no motion at night
        ledcWrite(26, 1500);  // LED 2: Dim when high fog & no motion at night
        Serial.println("Both LEDs ON but DIM due to high foggy weather at night with no vehicles.");
        message = ("Both LEDs ON but DIM, high foggy weather at night, no vehicles.");
        Blynk.virtualWrite(V2, "IR Sensor 1 : " + String(ir2) + " | IR Sensor 2 : " + String(ir1) + " | LDR Sensor : " + String(ldr));
        Blynk.virtualWrite(V4, message);
    } 
        else if (ir1 == 1 && ldr == 0 && ir2 == 1) // No motion, bright environment             
    { 
        ledcWrite(25, 2500);  // LED 1: Semi-bright when high fog & no motion during day
        ledcWrite(26, 2500);  // LED 2: Semi-bright when high fog & no motion during day
        Serial.println("Both LEDs ON but SEMI-BRIGHT due to high foggy weather during day with no vehicles.");
        message = ("Both LEDs ON but SEMI-BRIGHT, high foggy weather during day, no vehicles.");
        Blynk.virtualWrite(V2, "IR Sensor 1 : " + String(ir2) + " | IR Sensor 2 : " + String(ir1) + " | LDR Sensor : " + String(ldr));
        Blynk.virtualWrite(V4, message);
    } 

        else if (ir1 == 0 && ldr == 1 && ir2 == 1)  // Motion detected near LED1, dark environment
    {
        ledcWrite(25, 2500); // LED 1: Brighter when high fog & motion at night
        ledcWrite(26, 1500); // LED 2: Dim when high fog & no motion at night
        Serial.println("LED2 ON and BRIGHT due to high foggy weather at night with vehicles near LED2, LED1 DIM.");
        message = ("LED2 ON & BRIGHT, high foggy weather at night, vehicles at LED2, LED1 DIM.");
        Blynk.virtualWrite(V2, "IR Sensor 1 : " + String(ir2) + " | IR Sensor 2 : " + String(ir1) + " | LDR Sensor : " + String(ldr));
        Blynk.virtualWrite(V4, message);
    } 

    else if (ir1 == 1 && ldr == 1 && ir2 == 0) // Motion detected near LED2, dark environment
    { 
        ledcWrite(25, 1500);   // LED 1: Dim when high fog & no motion at night
        ledcWrite(26, 2500); // LED 2: Brighter when high fog & motion at night
        Serial.println("LED1 ON and BRIGHT due to high foggy weather at night with vehicles near LED1, LED2 DIM.");
        message = ("LED1 ON & BRIGHT, high foggy weather at night, vehicles at LED1, LED2 DIM.");
        Blynk.virtualWrite(V2, "IR Sensor 1 : " + String(ir2) + " | IR Sensor 2 : " + String(ir1) + " | LDR Sensor : " + String(ldr));
        Blynk.virtualWrite(V4, message);
    }

    else if (ir1 == 0 && ldr == 1 && ir2 == 0) // Motion detected near both LED1 & LED2, dark environment
    { 
        ledcWrite(25, 2500);    // LED 1: Brighter when high fog and motion at night
        ledcWrite(26, 2500); // LED 2: Brighter when high fog and motion at night
        Serial.println("Both LED1 and LED2, ON and BRIGHT due to high foggy weather at night with vehicles near both LED1 and LED2.");
         message = ("LED1 & LED2 ON & BRIGHT, high foggy weather at night, vehicles at LED1 & LED2.");
         Blynk.virtualWrite(V2, "IR Sensor 1 : " + String(ir2) + " | IR Sensor 2 : " + String(ir1) + " | LDR Sensor : " + String(ldr));
         Blynk.virtualWrite(V4, message);
    }

    else if (ir1 == 0 && ldr == 0 && ir2 == 1) // Motion detected near LED1, bright environment
    { 
        ledcWrite(25, 4000); // LED 1: Brighter when high fog & motion during day
        ledcWrite(26, 2500); // LED 2: Dim when high fog & no motion during day
        Serial.println("LED2 ON and BRIGHT due to high foggy weather during day with vehicles near LED2, LED1 DIM.");
        message = ("LED2 ON & BRIGHT, high foggy weather during day, vehicles at LED2, LED1 DIM.");
        Blynk.virtualWrite(V2, "IR Sensor 1 : " + String(ir2) + " | IR Sensor 2 : " + String(ir1) + " | LDR Sensor : " + String(ldr));
        Blynk.virtualWrite(V4, message);
    } 

    else if (ir1 == 1 && ldr == 0 && ir2 == 0) // Motion detected near LED2, bright environment
    { 
        ledcWrite(25, 2500);   // LED 1: Dim when high fog & no motion during day
        ledcWrite(26, 4000); // LED 2: Brighter when high fog & motion during day
        Serial.println("LED1 ON and BRIGHT due to high foggy weather during day with vehicles near LED1, LED2 DIM.");
         message = ("LED1 ON & BRIGHT, high foggy weather during day, vehicles at LED1, LED2 DIM.");
         Blynk.virtualWrite(V2, "IR Sensor 1 : " + String(ir2) + " | IR Sensor 2 : " + String(ir1) + " | LDR Sensor : " + String(ldr));
         Blynk.virtualWrite(V4, message);
    }

    else if (ir1 == 0 && ldr == 0 && ir2 == 0) // Motion detected near both LED1 & LED2, bright environment
    { 
        ledcWrite(25, 4000);    // LED 1: Brighter when high fog and motion during day
        ledcWrite(26, 4000); // LED 2: Brighter when high fog and motion during day
        Serial.println("Both LED1 and LED2, ON and BRIGHT due to high foggy weather during day with vehicles near both LED1 and LED2.");
         message = ("LED1 & LED2 ON & BRIGHT, high foggy weather at day, vehicles at LED1 & LED2.");
         Blynk.virtualWrite(V2, "IR Sensor 1 : " + String(ir2) + " | IR Sensor 2 : " + String(ir1) + " | LDR Sensor : " + String(ldr));
         Blynk.virtualWrite(V4, message);
    }
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

else if (80 < humidity && humidity <= 95)  // medium foggy weather, values are relatively more for better visibility
{
    if (ir1 == 1 && ldr == 1 && ir2 == 1) // No motion, dark environment
    { 
        ledcWrite(25, 300);   // LED 1: Dim when medium fog & no motion at night
        ledcWrite(26, 300);  // LED 2: Dim when medium fog & no motion at night
        Serial.println("Both LEDs ON but DIM due to medium foggy weather at night with no vehicles.");
        message = ("Both LEDs ON but DIM, medium foggy weather at night, no vehicles.");
        Blynk.virtualWrite(V2, "IR Sensor 1 : " + String(ir2) + " | IR Sensor 2 : " + String(ir1) + " | LDR Sensor : " + String(ldr));
        Blynk.virtualWrite(V4, message);
    } 
        else if (ir1 == 1 && ldr == 0 && ir2 == 1) // No motion, bright environment
    { 
        ledcWrite(25, 1200);  // LED 1: Semi-bright when medium fog & no motion during day
        ledcWrite(26, 1200);  // LED 2: Semi-bright when medium fog & no motion during day
        Serial.println("Both LEDs ON but SEMI-BRIGHT due to medium foggy weather during day with no vehicles.");
        message = ("Both LEDs ON but SEMI-BRIGHT, medium foggy weather during day, no vehicles.");
        Blynk.virtualWrite(V2, "IR Sensor 1 : " + String(ir2) + " | IR Sensor 2 : " + String(ir1) + " | LDR Sensor : " + String(ldr));
        Blynk.virtualWrite(V4, message);
    } 

        else if (ir1 == 0 && ldr == 1 && ir2 == 1)  // Motion detected near LED1, dark environment
    {
        ledcWrite(25, 1200); // LED 1: Brighter when medium fog & motion at night
        ledcWrite(26, 300); // LED 2: Dim when medium fog & no motion at night
        Serial.println("LED2 ON and BRIGHT due to medium foggy weather at night with vehicles near LED2, LED1 DIM.");
        message = ("LED2 ON & BRIGHT, medium foggy weather at night, vehicles at LED2, LED1 DIM.");
        Blynk.virtualWrite(V2, "IR Sensor 1 : " + String(ir2) + " | IR Sensor 2 : " + String(ir1) + " | LDR Sensor : " + String(ldr));
        Blynk.virtualWrite(V4, message);
    } 

    else if (ir1 == 1 && ldr == 1 && ir2 == 0) // Motion detected near LED2, dark environment
    { 
        ledcWrite(25, 300);   // LED 1: Dim when medium fog & no motion at night
        ledcWrite(26, 1200); // LED 2: Brighter when medium fog & motion at night
        Serial.println("LED1 ON and BRIGHT due to medium foggy weather at night with vehicles near LED1, LED2 DIM.");
        message = ("LED1 ON & BRIGHT, medium foggy weather at night, vehicles at LED1, LED2 DIM.");
        Blynk.virtualWrite(V2, "IR Sensor 1 : " + String(ir2) + " | IR Sensor 2 : " + String(ir1) + " | LDR Sensor : " + String(ldr));
        Blynk.virtualWrite(V4, message);
    }

    else if (ir1 == 0 && ldr == 1 && ir2 == 0) // Motion detected near both LED1 & LED2, dark environment
    { 
        ledcWrite(25, 1200);    // LED 1: Brighter when medium fog and motion at night
        ledcWrite(26, 1200); // LED 2: Brighter when medium fog and motion at night
        Serial.println("Both LED1 and LED2, ON and BRIGHT due to medium foggy weather at night with vehicles near both LED1 and LED2.");
         message = ("LED1 & LED2 ON & BRIGHT, medium foggy weather at night, vehicles at LED1 & LED2.");
         Blynk.virtualWrite(V2, "IR Sensor 1 : " + String(ir2) + " | IR Sensor 2 : " + String(ir1) + " | LDR Sensor : " + String(ldr));
         Blynk.virtualWrite(V4, message);
    }

    else if (ir1 == 0 && ldr == 0 && ir2 == 1) // Motion detected near LED1, bright environment
    { 
        ledcWrite(25, 2800); // LED 1: Brighter when medium fog & motion during day
        ledcWrite(26, 1200); // LED 2: Dim when medium fog & no motion during day
        Serial.println("LED2 ON and BRIGHT due to medium foggy weather during day with vehicles near LED2, LED1 DIM.");
        message = ("LED2 ON & BRIGHT, medium foggy weather during day, vehicles at LED2, LED1 DIM.");
        Blynk.virtualWrite(V2, "IR Sensor 1 : " + String(ir2) + " | IR Sensor 2 : " + String(ir1) + " | LDR Sensor : " + String(ldr));
        Blynk.virtualWrite(V4, message);
    } 

    else if (ir1 == 1 && ldr == 0 && ir2 == 0) // Motion detected near LED2, bright environment
    { 
        ledcWrite(25, 1200);   // LED 1: Dim when medium fog & no motion during day
        ledcWrite(26, 2800); // LED 2: Brighter when medium fog & motion during day
        Serial.println("LED1 ON and BRIGHT due to medium foggy weather during day with vehicles near LED1, LED2 DIM.");
         message = ("LED1 ON & BRIGHT, medium foggy weather during day, vehicles at LED1, LED2 DIM.");
         Blynk.virtualWrite(V2, "IR Sensor 1 : " + String(ir2) + " | IR Sensor 2 : " + String(ir1) + " | LDR Sensor : " + String(ldr));
         Blynk.virtualWrite(V4, message);
    }

    else if (ir1 == 0 && ldr == 0 && ir2 == 0) // Motion detected near both LED1 & LED2, bright environment
    { 
        ledcWrite(25, 2800);    // LED 1: Brighter when medium fog and motion during day
        ledcWrite(26, 2800); // LED 2: Brighter when medium fog and motion during day
        Serial.println("Both LED1 and LED2, ON and BRIGHT due to medium foggy weather during day with vehicles near both LED1 and LED2.");
         message = ("LED1 & LED2 ON & BRIGHT, medium foggy weather at day, vehicles at LED1 & LED2.");
         Blynk.virtualWrite(V2, "IR Sensor 1 : " + String(ir2) + " | IR Sensor 2 : " + String(ir1) + " | LDR Sensor : " + String(ldr));
         Blynk.virtualWrite(V4, message);
    }
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

else if (humidity <= 80) // not foggy weather, values are optimum for visibility
{
    if (ir1 == 1 && ldr == 1 && ir2 == 1) // No motion, dark environment
    { 
        ledcWrite(25, 50);   // LED 1: Dim when no fog & motion at night
        ledcWrite(26, 50);   // LED 2: Dim when no fog & motion at night
        Serial.println("Both LEDs ON but DIM due to no foggy weather at night with no vehicles.");
        message = ("Both LEDs ON but DIM, no foggy weather at night, no vehicles.");
        Blynk.virtualWrite(V2, "IR Sensor 1 : " + String(ir2) + " | IR Sensor 2 : " + String(ir1) + " | LDR Sensor : " + String(ldr));
        Blynk.virtualWrite(V4, message);
    } 

    else if (ir1 == 1 && ldr == 0 && ir2 == 1) // No motion, bright environment
    { 
        ledcWrite(25, 0);  // LED 1: Off when no fog & motion during day
        ledcWrite(26, 0);  // LED 2: Off when no fog & motion during day
        Serial.println("Both LEDs OFF due to no foggy weather during day with no vehicles.");
        message = ("Both LEDs OFF, no foggy weather during day, no vehicles.");
        Blynk.virtualWrite(V2, "IR Sensor 1 : " + String(ir2) + " | IR Sensor 2 : " + String(ir1) + " | LDR Sensor : " + String(ldr));
        Blynk.virtualWrite(V4, message);
    } 

    else if (ir1 == 0 && ldr == 1 && ir2 == 1) // Motion detected near LED1, dark environment
    { 
        ledcWrite(25, 1200); // LED 1: Brighter when no fog but motion at night
        ledcWrite(26, 50);  // LED 2: Dim when no fog & motion at night
        Serial.println("LED2 ON and BRIGHT due to no foggy weather at night with vehicles near LED2, LED1 DIM.");
        message = ("LED2 ON & BRIGHT, no foggy weather at night, vehicles at LED2, LED1 DIM.");
        Blynk.virtualWrite(V2, "IR Sensor 1 : " + String(ir2) + " | IR Sensor 2 : " + String(ir1) + " | LDR Sensor : " + String(ldr));
        Blynk.virtualWrite(V4, message);
    } 

    else if (ir1 == 1 && ldr == 1 && ir2 == 0) // Motion detected near LED2, dark environment
        { 
        ledcWrite(25, 50);   // LED 1: Dim when no fog & motion at night
        ledcWrite(26, 1200); // LED 2: Brighter when no fog but motion at night
        Serial.println("LED1 ON and BRIGHT due to no foggy weather at night with vehicles near LED1, LED2 DIM.");
        message = ("LED1 ON & BRIGHT, no foggy weather at night, vehicles at LED1, LED2 DIM.");
        Blynk.virtualWrite(V2, "IR Sensor 1 : " + String(ir2) + " | IR Sensor 2 : " + String(ir1) + " | LDR Sensor : " + String(ldr));
        Blynk.virtualWrite(V4, message);
    }

    else if (ir1 == 0 && ldr == 1 && ir2 == 0) // Motion detected near both LED1 & LED2, dark environment
    { 
        ledcWrite(25, 1200);    // LED 1: Brighter when no fog but motion at night
        ledcWrite(26, 1200); // LED 2: Brighter when no fog but motion during at night
        Serial.println("Both LED1 and LED2, ON and BRIGHT due to no foggy weather at night with vehicles near both LED1 and LED2.");
         message = ("LED1 & LED2 ON & BRIGHT, no foggy weather at night, vehicles at LED1 & LED2.");
         Blynk.virtualWrite(V2, "IR Sensor 1 : " + String(ir2) + " | IR Sensor 2 : " + String(ir1) + " | LDR Sensor : " + String(ldr));
         Blynk.virtualWrite(V4, message);
    }

    else if (ir1 == 0 && ldr == 0 && ir2 == 1) // Motion detected near LED1, bright environment
    { 
        ledcWrite(25, 0); // LED 1: Brighter when no fog but motion during day
        ledcWrite(26, 0);  // LED 2: Off
        Serial.println("LED2 OFF due to no foggy weather during day with vehicles near LED2, LED1 OFF.");
        message = ("LED2 OFF, no foggy weather during day, vehicles at LED2, LED1 OFF.");
        Blynk.virtualWrite(V2, "IR Sensor 1 : " + String(ir2) + " | IR Sensor 2 : " + String(ir1) + " | LDR Sensor : " + String(ldr));
        Blynk.virtualWrite(V4, message);
    } 

    else if (ir1 == 1 && ldr == 0 && ir2 == 0) // Motion detected near LED2, bright environment
    { 
        ledcWrite(25, 0);    // LED 1: Off
        ledcWrite(26, 0); // LED 2: Off when no fog but motion during day
        Serial.println("LED1 OFF due to no foggy weather during day with vehicles near LED1, LED2 OFF.");
         message = ("LED1 OFF, no foggy weather during day, vehicles at LED1, LED2 OFF.");
         Blynk.virtualWrite(V2, "IR Sensor 1 : " + String(ir2) + " | IR Sensor 2 : " + String(ir1) + " | LDR Sensor : " + String(ldr));
         Blynk.virtualWrite(V4, message);
    }

    else if (ir1 == 0 && ldr == 0 && ir2 == 0) // Motion detected near both LED1 & LED2, bright environment
    { 
        ledcWrite(25, 0);    // LED 1: Brighter when no fog but motion during day
        ledcWrite(26, 0); // LED 2: Brighter when no fog but motion during day
        Serial.println("Both LED1 and LED2, OFF due to no foggy weather during day with vehicles near both LED1 and LED2.");
         message = ("LED1 & LED2 OFF, no foggy weather at day, vehicles at LED1 & LED2.");
         Blynk.virtualWrite(V2, "IR Sensor 1 : " + String(ir2) + " | IR Sensor 2 : " + String(ir1) + " | LDR Sensor : " + String(ldr));
         Blynk.virtualWrite(V4, message);
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

else 
{
    message = "Default state: Adjusting brightness";
    Serial.println(message);
    Blynk.virtualWrite(V4, message);  // Send message to Terminal Widget
}
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


// OpenWeatherMap API
String city = "**********"; // Replace with your city
String apiKey = "**********";
String serverPath = "http://api.openweathermap.org/data/2.5/weather?q=" + city + "&appid=" + apiKey + "&units=metric";

// Function to fetch weather data
void getWeatherData() {
    HTTPClient http;
    http.begin(serverPath.c_str());  
    int httpResponseCode = http.GET();

    if (httpResponseCode > 0) {
        String response = http.getString();
      //Serial.println(response);
        
        // Parse JSON data
        DynamicJsonDocument doc(1024);
        deserializeJson(doc, response);

        float temperature = doc["main"]["temp"]; 
        float humidity = doc["main"]["humidity"];
        String weatherDesc = doc["weather"][0]["description"];

        
        Serial.print("Temperature by Weather API: "); Serial.print(temperature); Serial.print("°C | ");
        Serial.print("Humidity by Weather API: "); Serial.print(humidity); Serial.println("% ");
        Serial.print("Weather Description by Weather API: "); Serial.println(weatherDesc);
        Serial.println();
        Serial.println();
        Serial.println();

        // Send data to Blynk
        Blynk.virtualWrite(V3, "Weather API Temp. : " + String(temperature) + "°C " + " | Weather API Humid. : " + String(humidity) + "% " + " | " + String(weatherDesc));

    } 
    else {
        Serial.println("Error in HTTP request");
    }
    http.end();
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void setup() 
{
    Serial.begin(115200);
    
  //------------------------------------------------------------------------  
    WiFi.begin(ssid, pass);
    
    while (WiFi.status() != WL_CONNECTED) {
        delay(3000);
        Serial.println("Connecting to WiFi...");
    }
    Serial.println("Connected to WiFi");
  //------------------------------------------------------------------------

    Blynk.begin(auth, ssid, pass); // Connect to Blynk
    dht.begin();

    pinMode(IR1, INPUT);
    pinMode(IR2, INPUT);
    pinMode(LDR, INPUT);

    ledcAttachChannel(LED1, 19000, 12, 0);
    ledcAttachChannel(LED2, 19000, 12, 1);

    // Run getWeatherData every 4 secs
    timer.setInterval(3000L, getWeatherData);  

    // Timer to send data every 4 seconds
    timer.setInterval(3000L, sendSensorDataToBlynk);
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void loop() 
{
    Blynk.run();  // Run Blynk
    timer.run();  // Run Timer
}
