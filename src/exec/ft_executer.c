#include "minishell.h"

// ns pq se me sale del programa

void	ft_exec_cmd(t_shell *msh)
{
	pid_t	pid;

	if (is_builting(msh)) // pipe_config ?
		return ;
	pid = fork();
	if (pid < 0)
		exit(0);       //err_msh;
	else if (pid == 0) // children
	{
		msh->cmd = get_cmd(msh->paths, msh->cmd_args[0]);
		if (!msh->cmd)
		{
			//err_msh();
			return ;
		}
		// if (parser->redir_in > 0)
		// {
		// 	dup2(parser->redir_in, STDIN_FILENO);
		// 	close(parser->redir_in);
		// }
		// if (parser->redir_out > 0)
		// {
		// 	dup2(parser->redir_out, STDOUT_FILENO);
		// 	close(parser->redir_out);
		// }
		if (execve(msh->cmd, msh->cmd_args, msh->envp) < 0)
		{
			perror("execve");
			ft_memfree_all(msh->paths);
			ft_memfree_all(msh->cmd_args);
			ft_memfree(msh->cmd);
			ft_memfree(msh);
		}
	}
	else // &msh->exit_status (donde va NULL);
		waitpid(pid, NULL, 0);
}

void	ft_executer(t_shell *msh, char **envp)
{
	t_parser	*parser;

	parser = msh->parser;
	msh->envp = ft_arraydup(envp);
	msh->paths = get_paths(envp); //ns si va aqui o dentro del bucle
	while (parser)
	{
		// extend quotes " $ " (parser->cmd)
		// if (error) break ;
		msh->cmd_args = ft_split(parser->cmd, ' '); // if no hay parser->cmd ?
		ft_exec_cmd(msh);
		ft_memfree_all(msh->cmd_args);
		parser = parser->next;
	}
	ft_memfree_all(msh->envp);
	ft_memfree_all(msh->paths);
}
