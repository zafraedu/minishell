#include "../inc/minishell.h"

static void	ft_getinput(void);

// void ft_leaks(void)
// {
// 	system("leaks -q minishell");
// }
//atexit(ft_leaks);

void	sigint_handler(int sig) //! no va aqui
{
	(void)sig;
	ft_putchar_fd('\n', 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

int	main(int argc, char **argv, char **envp)
{
	//? t_tools tools; ?
	//? t_pipe pipe; ?
	*signal(SIGINT, sigint_handler); //crear funcion para manejar ctrl+c
	*signal(SIGQUIT, SIG_IGN);       // SIG_IGN ignora la señal SIGQUIT (ctrl+\)
	(void)envp;                      //? todavia no se usa
	if (argc != 1 || argv[1])
		return (EXIT_FAILURE);
	//* printf(HEADER); //imprime el header
	//* usar envp para crear la variable de entorno
	ft_getinput(); //funcion para obtener la linea; como parametro va tools
	return (EXIT_SUCCESS);
}

static void	ft_getinput(void) // aqui va tools como parametro
{
	char *input;
	char *tmp;

	while (1)
	{
		input = readline(READLINE_MSG);
		tmp = ft_strtrim(input, " ");
		if (!input || !ft_strcmp(tmp, "exit"))
		{
			ft_memfree(tmp);
			ft_memfree(input);
			break ;
		}
		add_history(input);
		if (input[0] == 0)
			printf("%s", input);   // tiene que resetear tools
		else                       //test
			printf("%s\n", input); //test
		ft_memfree(tmp);
		ft_memfree(input);
	}
}
