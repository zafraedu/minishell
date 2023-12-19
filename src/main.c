#include "minishell.h"

static void	ft_minishell(t_shell *msh, char **argv, char **envp);
static void	ft_prev_exec(char *tmp, t_shell *msh);
static void	ft_clean_shell(char *tmp, char *input, t_shell *msh);

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

int	main(int argc, char **argv, char **envp)
{
	t_shell	msh;

	(void)argc;
	// atexit(ft_leaks); //test
	// if (argc != 1 || argv[1])
	// 	return (EXIT_FAILURE);
	//*printf(HEADER);//imprime el header (si queremos claro);
	signal_init();
	ft_minishell(&msh, argv, envp);
	return (EXIT_SUCCESS);
}

static void	ft_minishell(t_shell *msh, char **argv, char **envp)
{
	char	*input;
	char	*tmp;

	ft_lst_env_init(&msh->env, envp);
	while (1)
	{
		if (g_signal == S_SIGINT)
			msh->exit_status = 1;
		input = readline(READLINE_MSG);
		tmp = ft_strtrim(input, " \t\n\v\f\r");
		if (!input)
			break ;
		if (tmp[0] != 0)
			add_history(tmp);
		ft_prev_exec(tmp, msh);
		print_select(msh->lexer, msh->parser, argv); //test print
		if (g_signal != S_CANCEL_EXEC)
			ft_executer(msh);
		ft_clean_shell(tmp, input, msh);
		g_signal = S_BASE;
	}
	ft_free_list(&msh->env);
}

static void	ft_prev_exec(char *tmp, t_shell *msh)
{
	ft_lexer(tmp, &msh->lexer, &msh->exit_status);
	ft_replace(msh);
	ft_parser(&msh->parser, msh->lexer);
}

static void	ft_clean_shell(char *tmp, char *input, t_shell *msh)
{
	ft_memfree(input);
	ft_memfree(tmp);
	ft_free_tokenlist(&msh->lexer);
	ft_free_parserlist(&msh->parser);
}
