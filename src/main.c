#include "../inc/minishell.h"

// void ft_leaks(void)
// {
// system("leaks -q minishell");
// }

static void	ft_getinput(void)
{
	char	*input;
	char	*tmp;
	t_token	*token_list;

	token_list = NULL;
	while (1)
	{
		input = readline(READLINE_MSG);
		tmp = ft_strtrim(input, " ");
		if (!input || !ft_strcmp(tmp, "exit"))
		{
			ft_memfree(tmp);
			ft_memfree(input);
			ft_free_tokenlist(&token_list);
			break ;
		}
		ft_lexer(input, &token_list); // Creacion de tokens
		add_history(input);           //todavia no se usa
		if (input[0] == 0)
			printf("%s", input); // tiene que resetear tools
		ft_memfree(tmp);
		ft_memfree(input);
		ft_free_tokenlist(&token_list);
	}
}

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
	// Pongo esta lista en el main hasta definir si solo se usará dentro de ft_getinput o no
	//? t_tools tools; ?
	//? t_pipe pipe; ?
	signal(SIGINT, sigint_handler); //crear funcion para manejar ctrl+c
	signal(SIGQUIT, SIG_IGN);       // SIG_IGN ignora la señal SIGQUIT (ctrl+\)
	// atexit(ft_leaks);
	(void)envp; //? todavia no se usa
	if (argc != 1 || argv[1])
		return (EXIT_FAILURE);
	//* printf(HEADER); //imprime el header
	//* usar envp para crear la variable de entorno
	ft_getinput(); //funcion para obtener la linea; como parametro va tools
	return (EXIT_SUCCESS);
}
