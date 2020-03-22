bool alarmCheckSituation();
void CheckSituation();
bool getWindowStateAuto();
bool getDoorStateAuto();

#include <iarduino_Pressure_BMP.h>  // термометр барометр                       
#include "WarmSensor.h" 
#include "Alarm.h"
#include <iarduino_HC_SR04.h> //дальномер

#define FIRE_SENSOR_PIN   0       // 1 пусто; 0 пожар //для включения сирены
#define MOTION_SENSOR_PIN 1       // 1 движение, 20 сек задержка //для включения света на улице
#define SOUND_SENSOR_PIN  2       // 560 - тихо  //для включения выключения света в жилой комнате
#define LIGHT_SENSOR_PIN  3       //1 - темно   //для включения света на кухне
#define LEN_SENSOR_DOOR_PIN     4    // 
#define LEN_SENSOR_WINDOW_PIN   5  // 
#define LIGHT_DATA              6  // 
#define LIGHT_ADDRESS           7  // 
#define LEN_SENSOR_TRIG_PIN     8  // 
#define SERVO_DOOR              9  // 
  
#define WARM_SENSOR_PIN     A0      // 0 - сухо
//#define DIRT_WARM_SENSOR  A1      // 0 - сухо
#define SERVO_WINDOW        A1      // 
#define GAS_SENSOR_PIN      A2      // 
#define ALARM_PIN           A3      //

#define OUTSIDE_LIGHT     0  // 
#define KICHEN_LIGHT      1  //
#define BEDROOM_LIGHT     2  //

#define OPEN      true      // 
#define CLOSED           false      //

bool ClapButtonInfo = false;
bool isFire = false;
bool isLight = false;
bool isGas = false;
bool isMovement = false;
bool isRain = false;
bool windowState = false;
bool doorState = false;

iarduino_Pressure_BMP BMPSensor; //i2c   //A4 and A5
iarduino_HC_SR04 DoorSensor(LEN_SENSOR_TRIG_PIN,LEN_SENSOR_DOOR_PIN);          // объявляем переменную для работы с датчиком, указывая номера arduino подключенные к выводам TRIG и ECHO датчика
iarduino_HC_SR04 WindowSensor(LEN_SENSOR_TRIG_PIN,LEN_SENSOR_WINDOW_PIN);          // объявляем переменную для работы с датчиком, указывая номера arduino подключенные к выводам TRIG и ECHO датчика

void updateSensorData(){ //проверка ситуации запись значений с датчиков в переменные на время ближайшего цикла
    isFire = !digitalRead(FIRE_SENSOR_PIN;
    isMovement = digitalRead(MOTION_SENSOR_PIN));
    ClapButtonInfo = getClapButtonInfo();
    isLight = !digitalRead(LIGHT_SENSOR_PIN));
    doorState = DoorSensor.distance()>10?OPEN:CLOSED;  //млжно сделать индикатор взлома - если небыло команды открытия двер но она отурфыта сигналим
    windowState = WindowSensor.distance()>10?OPEN:CLOSED;
    isRain = getWarm()>500?true:false;
    isGas = analogRead(GAS_SENSOR_PIN)>300?true:false;
    curPressure = BMPSensor.pressure;
    curTemperature = BMPSensor.pressure;
}

void setup(){                                               
    Serial.begin(9600);  

    BMPSensor.begin(); 
    
    setClapPin(SOUND_SENSOR_PIN);
    setClapButtonState(SWITCH); //переключатель света в жилом помещении
    
    setWarmSensorPin(WARM_SENSOR_PIN);
    
    setState(SWITCH); 
    
    setAlarm(false); 
    setAlarmPin(ALARM_PIN);  
    
    setStCpPin(0);              //защёлка
    setShCpPin(LIGHT_ADDRESS);  //такт
    setDsCpPin(LIGHT_DATA);     //данные
}                                                          

void loop (){
    updateSensorData(); 
    сlapButtonProsess();
    alarmProcess();
    setAlarm(alarmCheckSituation());

    setRelay(OUTSIDE_LIGHT,getOutsideLightState());
    setRelay(KICHEN_LIGHT,getKichenLightState());
    setRelay(BEDROOM_LIGHT,getBedroomLightState());

  // Пример давления и температуры
    /*
//  Считываем данные и выводим: температуру в °С, давление в мм. рт. ст., изменение высоты относительно указанной в функции begin(по умолчанию 0 метров).
    if(BMPSensor.read(1))       {Serial.println((String)"CEHCOP BMP" + BMPSensor.type + ": \t P = " + BMPSensor.pressure + "\tMM.PT.CT, \t T = " + BMPSensor.temperature + " *C, \t\t B = "+BMPSensor.altitude+" M.");}
    else                     {Serial.println("HET OTBETA OT CEHCOPA");}
//  Считываем данные и выводим: температуру в °С и давление в Па, давление в мм. рт. ст., изменение высоты относительно указанной в функции begin(по умолчанию 0 метров).
    if(BMPSensor.read(2))       {Serial.println((String)"CEHCOP BMP" + BMPSensor.type + ": \t P = " + BMPSensor.pressure + "\tPa, \t\t T = "     + BMPSensor.temperature + " *C, \t\t B = "+BMPSensor.altitude+" M.");}
    else                     {Serial.println("HET OTBETA OT CEHCOPA");}
    delay(3000);
    */
    //Serial.println(digitalRead(FIRE_SENSOR_PIN));
    //Serial.println(digitalRead(SOUND_SENSOR_PIN));
    //Serial.println(analogRead(GAS_SENSOR_PIN));
    //Serial.println("Влажность: "+getWarm());
    //Serial.println(analogRead(GAS_SENSOR_PIN));
    //Serial.println(digitalRead(MOTION_SENSOR_PIN));
}

bool alarmCheckSituation(){
  return isFire || isGas; 
}

bool getWindowState(){
  return isRain || (curTemperature < 20); 
}

bool getDoorState(){
  return isRain || (curTemperature < 20); 
}
bool getOutsideLightState(){
  return isMovement; 
}
bool getBedroomLightState(){
  return getClapButtonInfo(); 
}
bool getKichenLightState(){
  return isLight;
}
