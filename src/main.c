#include "../inc/minishell.h"

// void ft_leaks(void)
// {
// 	system("leaks -q minishell");
// }
//atexit(ft_leaks);

int	main(int argc, char **argv, char **envp)
{
	char	*input;

	//* signal(SIGINT, sigint_handler); //crear funcion para manejar ctrl+c
	//* signal(SIGQUIT, SIG_IGN); // SIG_IGN ignora la señal SIGQUIT (ctrl+\)
	(void)envp; //? todavia no se usa
	if (argc != 1 || argv[1])
		exit(1);
	//? printf(HEADER); //imprime el header
	//* usar envp para crear la variable de entorno
	//* ft_getinput(); //funcion para obtener la linea
	while (1)                                        //test
	{                                                //test
		input = readline("\033[32;1mmsh$> \033[0m"); //test
		ft_printf("%s\n", input);                    //test
	}                                                //test
	return (0);
}
