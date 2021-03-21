#include "data.h"

Data dado_anterior;

void data_init()
{
	dado_anterior.temp_interna = -1;
	dado_anterior.temp_externa = -1;
	dado_anterior.temp_referencia = -1;
	dado_anterior.control = -1;
}

Data read_data()
{
	Data data;
	data.temp_externa = bme280_read();
	data.temp_interna = arduino_read_internal();	 //from uart
	data.temp_referencia = arduino_read_reference(); //from uart

	// If `temp_interna` temperature can't be read, use previous value
	if (data.temp_interna < 0 && dado_anterior.temp_interna > 0)
	{
		data.temp_interna = dado_anterior.temp_interna;
	}
	// If `temp_referencia` temperature can't be read, use previous value
	if (data.temp_referencia < 0 && dado_anterior.temp_referencia > 0)
	{
		data.temp_referencia = dado_anterior.temp_referencia;
	}

	dado_anterior = data;

	return data;
}
