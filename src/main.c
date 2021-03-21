#include <curses.h>
#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

#include <lcd.h>
#include <bme280.h>
#include <gpio.h>
#include <data.h>
#include <control.h>
#include <csv.h>

//-------quit-----
void quit_handler()
{
  refresh();
  endwin();
  all_off();
  exit(0);
}

void quit_init()
{
  signal(SIGINT, quit_handler);
}
//--------------

int main(int argc, char const *argv[])
{

  lcd_init();
  bme280_init(); // setup BME280
  gpio_init();   // setup GPIO
  data_init();   // setup Data
  quit_init();   // setup QUIT
  csv_init();    // setup CSV
  pthread_t tid[2];
  pthread_create(&tid[0], NULL, (void *)temperature_handler, (void *)NULL);
  pthread_create(&tid[1], NULL, (void *)menu_handler, (void *)NULL);
  pthread_join(tid[0], NULL);
  pthread_join(tid[1], NULL);

  return 0;
}
