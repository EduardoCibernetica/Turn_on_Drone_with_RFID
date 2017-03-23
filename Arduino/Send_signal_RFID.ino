
#include <AP_Common.h>
#include <AP_Math.h>
#include <AP_Param.h>
#include <AP_Progmem.h>
#include <AP_ADC.h>
#include <AP_InertialSensor.h>

#include <AP_HAL.h>
#include <AP_HAL_AVR.h>

//set auxiliary servo ranges
   


const AP_HAL::HAL& hal = AP_HAL_AVR_APM2;  // Hardware abstraction layer

    
    
void setup() 
{
hal.rcout->set_freq(0xF, 490);
hal.rcout->enable_mask(0xFF);
}

void loop() 
{
  int16_t control_in;
  //control_in = hal.rcin->read(6);
 // set_pwm(control_in)
  //x=hal.rcin->read(6);
  //uint16_t rcthr;
  //rcthr.set_pwm(hal.rcin->read(x));
  
  
        hal.rcout->write(0, rcthr);
	hal.rcout->write(1, rcthr);
	hal.rcout->write(2, rcthr);
	hal.rcout->write(3, rcthr);
}
AP_HAL_MAIN();    // special macro that replace's one of Arduino's to setup the code (e.g. ensure loop() is called in a loop)
