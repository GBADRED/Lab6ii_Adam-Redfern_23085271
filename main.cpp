/*
Filename: main.cpp
Description: Reports alarm state on the LCD every 5 seconds
Author: A Redfern
Date: 06/03/2025
Input/Output: 
Version: 01.00
Change log: 01.00 - Initial issue
*/
 
#include "mbed.h"
#include "display.h"

float TempReading;
float GasReading;
int GasAlarm;
int TempAlarm;
AnalogIn GasSensor(A2);
AnalogIn TempSensor(A1);

#define TIME_INCREMENT_MS                       10
int Tick =0;

void Init();
void LCDUpdate();
void alarmActivationUpdate();                          
 
int main()
{
    while( true ) {
        LCDUpdate();
        alarmActivationUpdate();
        thread_sleep_for(TIME_INCREMENT_MS);
    }
}

void LCDUpdate()
{ 

    if (Tick % 500 == 0){ // update LCD every 5 seconds
        if(GasAlarm == true && TempAlarm == true){
            displayInit( DISPLAY_CONNECTION_I2C_PCF8574_IO_EXPANDER );
            displayCharPositionWrite ( 0,0 );
            displayStringWrite( "Gas Alarm Active    " );
            displayCharPositionWrite ( 0,1 );
            displayStringWrite( "Temp Alarm Active   " );
        }

        if(GasAlarm == true && TempAlarm == false){
            displayInit( DISPLAY_CONNECTION_I2C_PCF8574_IO_EXPANDER );
            displayCharPositionWrite ( 0,0 );
            displayStringWrite( "Gas Alarm Active    " );
        }
        
        if(TempAlarm == true && GasAlarm == false){
            displayInit( DISPLAY_CONNECTION_I2C_PCF8574_IO_EXPANDER );
            displayCharPositionWrite ( 0,0 );
            displayStringWrite( "Temp Alarm Active   " );
        }

        if(TempAlarm == false && GasAlarm == false){
            displayInit( DISPLAY_CONNECTION_I2C_PCF8574_IO_EXPANDER );
            displayCharPositionWrite ( 0,0 );
            displayStringWrite( "No Active Alarms    " );
        }
  
    }
    Tick = Tick+1;

}

void alarmActivationUpdate()
{
    TempReading = TempSensor.read()*330;
    if(TempReading >= 28){
        TempAlarm = true;
    }else{
        TempAlarm = false;
    }

    GasReading = GasSensor.read()*3.3;
    if(GasReading >= 1.2){
        GasAlarm = true;
    }else{
        GasAlarm = false;
    }

}
