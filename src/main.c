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

static void	ft_minishell(t_shell *msh, char **argv, char **envp)
{
	char	*input;
	char	*tmp;

	ft_lst_env_init(&msh->env, envp);
	while (1)
	{
		input = readline(READLINE_MSG);
		tmp = ft_strtrim(input, " \t\n\v\f\r");
		if (!input)
			break ;
		if (tmp[0] != 0)
			add_history(tmp);
		ft_lexer(tmp, &msh->lexer, &msh->exit_status);
		ft_replace(msh);
		ft_parser(&msh->parser, msh->lexer);
		print_select(msh->lexer, msh->parser, argv); //test print
		ft_executer(msh);
		ft_memfree(input);
		ft_memfree(tmp);
		ft_free_tokenlist(&msh->lexer);
		ft_free_parserlist(&msh->parser);
	}
	ft_free_list(&msh->env);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	msh;

	(void)argc; //test
	// atexit(ft_leaks); //test
	/*if (argc != 1 || argv[1])  //cuando el print ya no sea necesario
		return (EXIT_FAILURE);   //ya podremos descomentar */
	//*printf(HEADER);//imprime el header (si queremos claro);
	signal(SIGINT, sigint_handler); //funcion para manejar ctrl+c
	signal(SIGQUIT, SIG_IGN);       // SIG_IGN ignora la señal SIGQUIT (ctrl+\)
	ft_minishell(&msh, argv, envp);
	return (EXIT_SUCCESS);
}
