#include <wiringPi.h>
#include <stdio.h>    
#include <softPwm.h>

#define ON 100
#define OFF 0

#define RESISTOR 4
#define VENT 5

#ifndef GPIO_H_
#define GPIO_H_

void gpio_init();
void toggle(int item, int status);
void all_off();

#endif /* GPIO_H_ */