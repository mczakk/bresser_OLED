
#include "globals.h"
// include ssd1306 display
#define SSD1306_DISPLAY
#include <Wire.h>
#include <iostream>
#include <string>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "WeatherSensorCfg.h" // needed for interface description of sensor data structure
#include <WeatherSensor.h> // needed for interface description of sensor data structure
#include "RainGauge.h" // needed for interface description of rain gauge
#include  "DisplayWeatherData.h"




#define SSD1306_DISPLAY
#define SCREEN_WIDTH 128  // OLED display width, in pixels
#define SCREEN_HEIGHT 64  // OLED display height, in pixels
#define OLED_SDA 21
#define OLED_SCL 22
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire);
extern void printDateTime(void);

// create instance of display class here
void setup(){
	Serial.begin(115200);
	#ifdef SSD1306_DISPLAY
		Wire.begin(OLED_SDA, OLED_SCL);
        if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3c, false, false)) { // Address 0x3C for 128x32
          log_d("SSD1306 Display not found");
        }
        else{
          display.clearDisplay();
          display.setTextColor(WHITE);
          display.setTextSize(1);
          display.setCursor(0,0);
          display.print("LORA WEATHER SENSOR ");
          log_d("Display should work");
			}
	#endif
	} 	
void displayWeatherData(sensor_t sensor) {
    printDateTime();

      
    display.setCursor(0,0);
    display.print("LORA WEATHER SENSOR ");
    display.setCursor(0,10);
    display.print("Getting Weather data.. ");
    display.setCursor(0,20);
    display.print("Time is:");
    display.setCursor(0,30);
    display.print(tbuf);
    display.setCursor(0,40);
    //get battery status flag
    if (WeatherSensor.sensor[i].battery_ok == true){
		display.print ("Battery OK");
    }else if (WeatherSensor.sensor[i].battery_ok == false){
		display.print("Change Battery");
	}	
    //if flag is bad print "Change Battery"
    //Serial.print(tbuf2);        
    display.display();
    delay(10000);
    display.clearDisplay();
    //display.setTextColor(WHITE);
    //display.setTextSize(1);
    //display.setCursor(0, 0);
    //display.print("LORA WEATHER SENDER ");
    //display.display();
    display.setCursor(0,0);
    display.print("Rain Data:");
    
    
    display.setCursor(0,10);
    display.print("Hourly rain:");
    display.setCursor(80, 10);
    display.print(RainGauge.pastHour());display.print(" mm");

    

    display.setCursor(0,20);
    display.print("Weekly rain:");
    display.setCursor(80,20);
    display.print(RainGauge.currentWeek());display.print(" mm");

    display.setCursor(0,30);
    display.print("Monthly rain:");
    display.setCursor(80,30);
    display.print(RainGauge.currentMonth());display.print(" mm");
    
    display.setCursor(0, 40);
    display.print("Total Rain");
    display.setCursor(0, 50);
    display.print(WeatherSensor.sensor[idx].w.rain_mm);
    
    display.display();
    delay(15000);
    display.clearDisplay();

    display.setCursor(0,0);
    display.print("Llanellen Weather"); //enter your gauge name here

    display.setCursor(0,10);
    display.print("Rain today:");
    display.setCursor(70,10);
    display.print(RainGauge.currentDay());display.print(" mm");    
    
    
    
    display.setCursor(0,20);
    display.print("Hum:");
    display.setCursor(40, 20);
    display.print(WeatherSensor.sensor[idx].w.humidity);display.print("%");

    display.setCursor(60, 20);
    display.print("T:");display.print(WeatherSensor.sensor[idx].w.temp_c);
    display.setCursor(80, 20);
    display.print((char)247);display.print("C");

    display.setCursor(0, 30);
    display.print("W/S (avg.m/s)");
    display.setCursor(100, 30);
    display.print(WeatherSensor.sensor[idx].w.wind_avg_meter_sec_fp1 / 10.0);

    display.setCursor(0, 40);
    display.print("W/S (max.m/s)");
    display.setCursor(100, 40);
    display.print(WeatherSensor.sensor[idx].w.wind_gust_meter_sec_fp1 / 10.0);
    
    display.setCursor(0,50);
    display.print("Wind Dir.");
    display.setCursor(85, 50);
    display.print(WeatherSensor.sensor[idx].w.wind_direction_deg_fp1 / 10.0);display.print((char)247);
    display.display();
  }			
