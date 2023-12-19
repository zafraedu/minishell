#include "minishell.h"

static void	ft_minishell(t_shell *msh, char **envp);
static void	ft_prev_exec(char *tmp, t_shell *msh);
static void	ft_clean_shell(char *tmp, char *input, t_shell *msh);

// void ft_leaks(void)
// {
// system("leaks -q minishell");
// }
// atexit(ft_leaks); //test

int	main(int argc, char **argv, char **envp)
{
	t_shell	msh;

	if (argc != 1 || argv[1])
		return (EXIT_FAILURE);
	//*printf(HEADER);//imprime el header (si queremos claro);
	signal_init();
	ft_minishell(&msh, envp);
	return (EXIT_SUCCESS);
}

static void	ft_minishell(t_shell *msh, char **envp)
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
