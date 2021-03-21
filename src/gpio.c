#include <gpio.h>

void gpio_init() {
  wiringPiSetup();
}

void toggle(int item, int status) {
  pinMode(item, OUTPUT);
  softPwmCreate(item, 1, ON);
  softPwmWrite(item, status);
}

void gpio_controle(double controle) {
  if (controle > 0) { //Controle resistor
    toggle(VENT, OFF);
    toggle(RESISTOR, controle);
  } else if (controle < -40) { //controle ventoinha
    toggle(RESISTOR, OFF);
    toggle(VENT, controle * -1);
  } else {
    all_off();
  }
}

void all_off() {
  // RESISTOR
  pinMode(RESISTOR, OUTPUT);
  softPwmWrite(RESISTOR, OFF);

  // VENT
  pinMode(VENT, OUTPUT);
  softPwmWrite(VENT, OFF);
}