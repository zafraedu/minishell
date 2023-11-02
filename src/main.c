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
		int j;
		while (par)
		{
			j = -1;
			ft_printf("%i. Cmd: %s", i++, par->cmd);
			while (par->args[0] != NULL && par->args[++j])
				ft_printf(" %s", par->args[j]);
			ft_printf("\n");
			par = par->next;
		}
		ft_printf("\n\033[33;1m----end----\033[0m\n");
	}
}

// static char	*find_path(char **envp) //no va aqui
// {
// 	while (ft_strncmp("PATH", *envp, 4))
// 		envp++;
// 	return (*envp + 5);
// }

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

// static void	ft_exec(t_shell *d, char *cmd, char **envp) // no va aqui
// {
// 	char *path_var;

// 	path_var = find_path(envp);
// 	d->paths = ft_split(path_var, ':');
// 	d->cmd_args = ft_split(cmd, ' ');
// 	if (is_builting(d))
// 		return ;
// 	d->cmd = get_cmd(d->paths, d->cmd_args[0]);
// 	if (!d->cmd)
// 	{
// 		printf("error CMD\n");
// 		return ;
// 	}
// 	execve(d->cmd, d->cmd_args, envp);
// 	ft_memfree_all(d->paths);
// 	ft_memfree_all(d->cmd_args);
// 	ft_memfree(cmd);
// 	ft_memfree(d);
// }

static void	ft_getinput(t_shell *msh, char **argv)
{
	char	*input;
	char	*tmp;

	// pid_t pid;                      //test
	signal(SIGINT, sigint_handler); // funcion para manejar ctrl+c
	signal(SIGQUIT, SIG_IGN);       // SIG_IGN ignora la señal SIGQUIT (ctrl+\)
	while (1)
	{
		input = readline(READLINE_MSG);
		tmp = ft_strtrim(input, " ");
		if (!input)
			break ;
		add_history(tmp);
		ft_lexer(tmp, &msh->lexer);
		ft_parser(&msh->parser, msh->lexer);
		print_select(msh->lexer, msh->parser, argv); //test print
		//ft_exec();   //no existe aun (el real me refiero)
		// pid = fork();                       //test
		// if (pid == 0)                       //test
		// 	ft_exec(msh, input, msh->envp); //test
		// else                                //test
		// 	waitpid(pid, NULL, 0);          //test
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
	msh.envp = ft_arraydup(envp); // se puede mejorar y no va aqui
	ft_getinput(&msh, argv);      //argv sirve para imprimir (lo quitaremos);
	return (EXIT_SUCCESS);
}
