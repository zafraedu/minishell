#include "minishell.h"

// void ft_leaks(void)
// {
// system("leaks -q minishell");
// }

// void	ft_getpath(t_shell *shell) //no va aqui
// {
// 	int i;

// 	i = 0;
// 	while (shell->envp[i] && ft_strnstr(shell->envp[i], "PATH=", 5) == NULL)
// 		i++;
// 	if (i == ft_arraylen(shell->envp))
// 		shell->paths = 0;
// 	else
// 		shell->paths = ft_split(shell->envp[i] + 5, ':');
// }

static char	*find_path(char **envp)
{
	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	return (*envp + 5);
}

static char	*get_cmd(char **paths, char *cmd)
{
	char	*tmp;
	char	*command;

	while (*paths)
	{
		tmp = ft_strjoin(*paths, "/");
		command = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(command, X_OK) == 0)
			return (command);
		free(command);
		paths++;
	}
	return (NULL);
}

void	ft_exec(t_shell *d, char *cmd, char **envp)
{
	char	*path_var;

	path_var = find_path(envp);
	d->paths = ft_split(path_var, ':');
	d->cmd_args = ft_split(cmd, ' ');
	d->cmd = get_cmd(d->paths, d->cmd_args[0]);
	if (!d->cmd)
	{
		printf("error CMD\n");
		// exit(EXIT_FAILURE);
	}
	execve(d->cmd, d->cmd_args, envp);
}

static void	ft_getinput(t_shell *msh)
{
	char	*input;
	char	*tmp;
	pid_t	pid;

	signal(SIGINT, sigint_handler); //crear funcion para manejar ctrl+c
	signal(SIGQUIT, SIG_IGN);       // SIG_IGN ignora la señal SIGQUIT (ctrl+\)
	while (1)
	{
		// ft_getpath(msh);
		input = readline(READLINE_MSG);
		tmp = ft_strtrim(input, " ");
		if (!input)
			break ;
		add_history(tmp);
		ft_lexer(input, &msh->token_list);    // Creacion de tokens
		if (!check_syntaxis(msh->token_list)) //comprobacion de syntaxis
		{
			printf("syntaxis mal\n"); //test
		}
		else
			printf("syntaxis bien\n"); //test
										//ft_parser(); //no existe aun
		pid = fork();
		if (pid == 0)
		{
			ft_exec(msh, input, msh->envp);
		}
		else
			waitpid(pid, NULL, 0);
		ft_memfree(input);
		ft_memfree(tmp);
		ft_free_tokenlist(&msh->token_list);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	msh;

	// atexit(ft_leaks);
	if (argc != 1 || argv[1])
		return (EXIT_FAILURE);
	//* printf(HEADER); //imprime el header
	msh.envp = ft_arraydup(envp); // se puede mejorar
	ft_getinput(&msh);
	return (EXIT_SUCCESS);
}
