#include "minishell.h"

// void ft_leaks(void)
// {
// system("leaks -q minishell");
// }

void	print_select(t_lexer *lex, t_parser *par, char **argv) //test
{
	if (argv[1] && (!ft_strcmp(argv[1], "-l") || !ft_strcmp(argv[1], "-lp")))
	{
		int i = 0;
		ft_printf("\033[33;1m----lexer----\033[0m\n\n");
		while (lex)
		{
			ft_printf("%i. %s, token: %i\n", ++i, lex->data, lex->type);
			lex = lex->next;
		}
		ft_printf("\n\033[33;1m----end----\033[0m\n");
	}
	if (argv[1] && (!ft_strcmp(argv[1], "-p") || !ft_strcmp(argv[1], "-lp")))
	{
		int i = 0;
		ft_printf("\033[33;1m----parser----\033[0m\n\n");
		while (par)
		{
			ft_printf("%i. Cmd: %s", i++, par->cmd);
			ft_printf("\n");
			par = par->next;
		}
		ft_printf("\n\033[33;1m----end----\033[0m\n");
	}
}

static char	**get_paths(char **envp) //no va aqui
{
	char *path;

	while (ft_strncmp("PATH=", *envp, 5))
		envp++;
	path = (*envp + 5);
	return (ft_split(path, ':'));
}

// static char	*get_cmd(char **paths, char *cmd) //no va aqui
// {
// 	char *tmp;
// 	char *command;

// 	while (*paths)
// 	{
// 		tmp = ft_strjoin(*paths, "/");
// 		command = ft_strjoin(tmp, cmd);
// 		free(tmp);
// 		if (access(command, X_OK) == 0)
// 			return (command);
// 		free(command);
// 		paths++;
// 	}
// 	return (NULL);
// }

static void	ft_exec(t_shell *d, char *cmd, char **envp) // no va aqui
{
	d->envp = ft_arraydup(envp);
	d->paths = get_paths(envp);
	d->cmd_args = ft_split(cmd, ' ');
	if (is_builting(d))
		return ;
	// d->cmd = get_cmd(d->paths, d->cmd_args[0]);
	// if (!d->cmd)
	// {
	// 	printf("error CMD\n");
	// 	return ;
	// }
	// execve(d->cmd, d->cmd_args, envp);
	// ft_memfree_all(d->paths);
	// ft_memfree_all(d->cmd_args);
	// ft_memfree(cmd);
	// ft_memfree(d);
}

// void	ft_exec(t_shell *msh, char **envp) //no va aqui
// {
// 	t_parser *parser;

// 	parser = msh->parser;
// 	msh->envp = ft_arraydup(envp);
// 	msh->paths = get_paths(envp); //ns si va aqui o dentro del bucle
// 	while (parser)
// 	{
// 		// extend quotes   " $ " (parser->cmd)
// 		msh->cmd_args = ft_split(parser->cmd, ' ');
// 		// ft_execute_process(msh, parser);
// 		parser = parser->next;
// 	}
// }

static void	ft_getinput(t_shell *msh, char **argv, char **envp)
{
	char	*input;
	char	*tmp;

	// pid_t pid;                      //test
	signal(SIGINT, sigint_handler); // funcion para manejar ctrl+c
	signal(SIGQUIT, SIG_IGN);       // SIG_IGN ignora la señal SIGQUIT (ctrl+\)
	while (1)
	{
		input = readline(READLINE_MSG);
		tmp = ft_strtrim(input, " \t\n\v\f\r");
		if (!input)
			break ;
		add_history(tmp);
		ft_lexer(tmp, &msh->lexer);
		ft_parser(&msh->parser, msh->lexer);
		print_select(msh->lexer, msh->parser, argv); //test print
		// ft_exec();   //no existe aun (el real me refiero)
		// pid = fork();
		// if (pid == 0)
		ft_exec(msh, input, envp); //test
		// else
		// waitpid(pid, NULL, 0);
		ft_memfree(input);              //free global
		ft_memfree(tmp);                //free global
		ft_free_tokenlist(&msh->lexer); //free global
		ft_free_parserlist(&msh->parser);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	msh;

	(void)argc; //test
	// atexit(ft_leaks); //test
	// if (argc != 1 || argv[1])	// cuando el print ya no sea necesario
	// 	return (EXIT_FAILURE);		// ya podremos descomentar
	//* printf(HEADER); //imprime el header
	// msh.envp = ft_arraydup(envp); // se puede mejorar y no va aqui
	ft_getinput(&msh, argv, envp); //argv sirve para imprimir (lo quitaremos);
	return (EXIT_SUCCESS);
}
