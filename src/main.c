#include "../inc/minishell.h"

// void ft_leaks(void)
// {
// 	system("leaks -q minishell");
// }
//atexit(ft_leaks);

int	main(int argc, char **argv, char **envp)
{
	// signal(SIGINT, sigint_handler); //crear funcion para manejar ctrl+c
	signal(SIGQUIT, SIG_IGN); // SIG_IGN ignora la señal SIGQUIT (ctrl+\)
	if (argc != 1 || argv[1])
		exit(1);
	(void)envp; //todavia no se usa
	// usar envp para crear la variable de entorno
	// printf(HEADER); //imprime el header
	//ft_getinput(); //funcion para obtener la linea
	return (0);
}
