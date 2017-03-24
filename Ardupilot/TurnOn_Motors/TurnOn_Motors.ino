
#include <AP_Common.h>
#include <AP_Math.h>
#include <AP_Param.h>
#include <AP_Progmem.h>
#include <AP_ADC.h>
#include <AP_InertialSensor.h>
#include <AP_HAL.h>
#include <AP_HAL_AVR.h>

const AP_HAL::HAL& hal = AP_HAL_AVR_APM2;  // Hardware abstraction layer
void setup()
{
    hal.rcout->set_freq(0xF, 490);
    hal.rcout->enable_mask(0xFF);
}
/*
Tabla de entradas
0 - > 1500 ApagarS
150 -> 1200 Incremento
222 -> 1777 Encender
254 -> 2040 Decremento
*/
void loop()
{
  int16_t x;
  uint16_t rcthroff = 900;
  uint16_t rcthr = 1100;

  x = hal.rcin->read(6);
  hal.console->printf_P(PSTR("%d \r\n"),x);
//*********Off*********
  if(x > 1470 && x < 1520)
  {
      hal.console->printf_P(PSTR("OFF\n"),"");
      hal.rcout->write(0, rcthroff);
      hal.rcout->write(1, rcthroff);
      hal.rcout->write(2, rcthroff);
      hal.rcout->write(3, rcthroff);
      rcthr = 1100;
  }
  //*****Incremento****
 if (x > 2000 && x < 2100)
 {
      hal.console->printf_P(PSTR("INCREMENTO\n"),"");
      hal.rcout->write(0, rcthr);
    	hal.rcout->write(1, rcthr);
    	hal.rcout->write(2, rcthr);
    	hal.rcout->write(3, rcthr);
          if(rcthr<1800){
            rcthr = rcthr + 10;
          }
          else{rcthr = 1100;}
      
  }
  //*******ON************
   if (x > 1600 && x < 1800)
   {
      hal.console->printf_P(PSTR("ENCENDIDO\n"),"");
      hal.rcout->write(0, rcthr);
    	hal.rcout->write(1, rcthr);
    	hal.rcout->write(2, rcthr);
    	hal.rcout->write(3, rcthr);
  }
  //******DECREMENTO********
     if (x > 1190 && x < 1250)
   {
      hal.console->printf_P(PSTR("DECREMENTO\n"),"");
      hal.rcout->write(0, rcthr);
    	hal.rcout->write(1, rcthr);
    	hal.rcout->write(2, rcthr);
    	hal.rcout->write(3, rcthr);
       rcthr = rcthr - 10 ;
  }

}
AP_HAL_MAIN();  
