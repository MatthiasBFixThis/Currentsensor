/*
ESP-DASH is a Blazing Fast Library to Create Great Looking Dashboards to Manage your ESP's

To Use this Library - (Step 1 and Step 2 Required only for First time Upload)
Step1: Download and install ESP8266 SPIFFS Tool
        http://esp8266.github.io/Arduino/versions/2.0.0/doc/filesystem.html#uploading-files-to-file-system
Step2: Now Connect your ESP8266 and Select Tools > ESP8266 Sketch Data Upload.
        (This Uploads the UI for your Dashboard)
Step3: After SPIFFS Upload is Completed, Upload the Arduino Sketch to ESP8266.
Step4: Restart ESP8266 and Access your Dashboard at it's IP Address.

Library Author: Ayush Sharma
Created on: 11/10/2017
*/

#include <EspDash.h>
#define FEATURE_ADC_VCC true // Enable FEATURE_ADC_VCC to measure supply voltage using the analog pin

const char* ssid = "";
const char* password = "";
const int currentsense = analogRead(A0);

int voltage = 5;
int watt = 0;
int watthours = 0;
int mah = 0;
int number = 0;   // Number of Artificial Visitors
int current = 0;
void setup() {
Serial.begin(115200);

EspDash.debug(true);              // Print Debug Info Like Wifi Connection etc. on Serial.
EspDash.begin(ssid, password);    // Setup First Time SSID and Password. (STA Only)
EspDash.addTab("Visitors", number);   // Add 'Visitors' Tab


EspDash.addTab("Voltage", voltage);
EspDash.addTab("Current", current);
EspDash.addTab("Power", watt);
EspDash.addTab("Watt Hours", watthours);
}

void loop() {
  number++;   // Increase Number of Artifical Visitors
  current = currentsense *50 /1023;
  watt = current * voltage;
  mah = mah + current /60 /60 /1000;
  watthours = mah * voltage /1000;
  EspDash.updateTab("Current", current);
  EspDash.updateTab("Power", watt);
  EspDash.updateTab("Watt Hours", watthours);
  EspDash.updateTab("Visitors", number);  // Update 'Visitors' Tab
  delay(1000); // delay in miliseconds (There are 1000 milliseconds in a second)
  
  
  EspDash.loop(); // Required for Proper Functioning.
}




/*
Measuring AC Current Using ACS712
*/

/*
const int sensorIn = A0;
int mVperAmp = 185; // use 100 for 20A Module and 66 for 30A Module


double Voltage = 0;
double VRMS = 0;
double AmpsRMS = 0;



void setup(){ 
 Serial.begin(9600);
}

void loop(){
 
 
 Voltage = getVPP();
 VRMS = (Voltage/2.0) *0.707; 
 AmpsRMS = (VRMS * 1000)/mVperAmp;
 Serial.print(AmpsRMS);
 Serial.println(" Amps RMS");

}

float getVPP()
{
  float result;
  
  int readValue;             //value read from the sensor
  int maxValue = 0;          // store max value here
  int minValue = 1024;          // store min value here
  
   uint32_t start_time = millis();
   while((millis()-start_time) < 1000) //sample for 1 Sec
   {
       readValue = analogRead(sensorIn);
       // see if you have a new maxValue
       if (readValue > maxValue) 
       {
           /*record the maximum sensor value*//*
           maxValue = readValue;
       }
       if (readValue < minValue) 
       {
           *//*record the maximum sensor value*//*
           minValue = readValue;
       }
   }
   
   // Subtract min from max
   result = ((maxValue - minValue) * 5.0)/1024.0;
      
   return result;
 }
*/








/*
You need to compile the source code yourself with the FEATURE_ADC_VCC set to true.

You will see this part in the main body of the source at around line 113 to 119
// Enable FEATURE_ADC_VCC to measure supply voltage using the analog pin
// Please note that the TOUT pin has to be disconnected in this mode
// Use the "System Info" device to read the VCC value
#define FEATURE_ADC_VCC false

You must change the false to true save it and compile and flash your ESP with the new code than your system_info_Vcc will give the approximate Voltage.
*/
