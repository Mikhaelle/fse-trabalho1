#include "control.h"
#include <data.h>
#include <csv.h>

// A second minus UART usleep
#define SECOND 800000

// Time state
int should_log = 0;
int choice;
float reference;

void menu_handler()
{
	do
	{
		printf("----------------Bem Vindo ao Menu----------------\n\n");
		printf("1. Caso deseje setar a temperatura tecle 1\n");
		printf("2. Para usar a temperatura de referencia tecle 2\n");
		printf("3. Para sair tecle 3\n");
		printf("-------------------------------------------------\n");
		scanf("%d", &choice);

		switch (choice)
		{
		case 1:
			printf("Entre com a temperatura desejada: \n");
			scanf("%f", &reference);
			pid_referencia_usuario(reference);
			break;
		case 2:
			pid_limpa_referencia_usuario();
			break;
		case 3:
			quit_handler();
			break;
		default:
			quit_handler();
			break;
		}

	} while (choice != 3);
}

void temperature_handler()
{
	while (1)
	{
		Data data = read_data();

		pid_atualiza_referencia(data.temp_referencia);
		double controle = pid_controle(data.temp_interna);
		gpio_controle(controle);
		data.control = controle;

		data.temp_referencia = pid_le_referencia();

		lcd_loc_first_line();
		typeLn("TI:");
		typeFloat(data.temp_interna);
		typeLn(" ");
		typeLn("TE:");
		typeFloat(data.temp_externa);
		lcd_loc_second_line();
		typeLn("TR:");
		typeFloat(data.temp_referencia);

		//print_data(data);

		if (should_log == 0)
		{
			should_log += 1;
		}
		else if (should_log == 1)
		{
			write_data(data);
			should_log = 0;
		}

		usleep(SECOND);
	}
}
