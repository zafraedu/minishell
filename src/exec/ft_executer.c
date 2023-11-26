#include "minishell.h"

void	restore_std(int incpy, int outcpy)
{
	dup2(incpy, STDIN_FILENO);
	dup2(outcpy, STDOUT_FILENO);
	close(incpy);
	close(outcpy);
}

void	fork_child(t_shell *msh, t_parser *p)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		msh->cmd = get_cmd(msh->paths, msh->cmd_args[0]);
		dup2(p->redir_out, STDOUT_FILENO);
		if (execve(msh->cmd, msh->cmd_args, msh->envp) < 0)
		{
			//! aquí está un leak de memoria
		}
		exit(127); // exit_status
	}
	else
	{
		waitpid(pid, &status, 0);
		// if (WIFEXITED(status))
		// 	msh->exit_status = WEXITSTATUS(status);
		dup2((p->redir_in), STDIN_FILENO); // ns si es necesario
		close(p->redir_out);
		close(p->redir_in);
	}
}

int	run_node(t_shell *msh, t_parser *p)
{
	int fd[2];   //test
	if (p->next) //test
	{
		pipe(fd);
		// if fd < 0 error;
		p->pipe_out = fd[1];
		p->next->pipe_in = fd[0];
	}
	if (is_builting(msh, p, msh->stdoutcpy))
		return (0);
	else
		fork_child(msh, p);
	return (0);
}

void	ft_executer(t_shell *msh, char **envp)
{
	t_parser	*parser;

	parser = msh->parser;
	msh->stdincpy = dup(STDIN_FILENO);
	msh->stdoutcpy = dup(STDOUT_FILENO);
	dup2(parser->redir_in, STDIN_FILENO);
	msh->envp = ft_arraydup(envp);
	msh->paths = get_paths(envp); //ns si va aqui o dentro del bucle
	while (parser)
	{
		// extend quotes " $ " (parser->cmd)
		//? if (error) break ;
		// if no hay parser->cmd ?
		msh->cmd_args = ft_split_shell(parser->cmd, ' ');
		run_node(msh, parser);
		ft_memfree_all(msh->cmd_args);
		parser = parser->next;
	}
	ft_memfree_all(msh->envp);
	ft_memfree_all(msh->paths);
	restore_std(msh->stdincpy, msh->stdoutcpy);
}
