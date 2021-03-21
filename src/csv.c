#include "csv.h"

char buffer[10];

void time_generate()
{
  time_t current_time;
  struct tm *time_info;

  time(&current_time);
  time_info = localtime(&current_time);

  strftime(buffer, 10, "%H:%M:%S", time_info);
}

void csv_init()
{
  FILE *file = fopen("data.csv", "w");
  if (file == NULL)
  {
    printf("Erro em abrir/criar o arquivo");
  }
  fprintf(file, "DATETIME, TI, TE, TR, TA\n");
  fclose(file);
}

void write_data(Data data)
{
  // Update Datetime
  time_generate();

  // Write file
  FILE *file = fopen("data.csv", "a");
  if (file == NULL)
  {
    printf("Erro em criar o arquivo");
  }
  fprintf(
      file,
      "%s,%4.2f,%4.2f,%4.2f,%4.2f\r\n",
      buffer,
      data.temp_interna,
      data.temp_externa,
      data.temp_referencia,
      data.control);
  fclose(file);
}
