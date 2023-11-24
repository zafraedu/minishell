#include "minishell.h"

void	restore_std(int incpy, int outcpy)
{
	int	i;

	dup2(incpy, STDIN_FILENO);
	dup2(outcpy, STDOUT_FILENO);
	close(incpy);
	close(outcpy);
	i = 3; // creo que sobra (no estoy seguro)
	while (i < 50)
	{
		close(i);
		i++;
	}
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
		execve(msh->cmd, msh->cmd_args, msh->envp);
		exit(127);
	}
	else
	{
		waitpid(pid, &status, 0);
		// if (WIFEXITED(status))
		// 	msh->exit_status = WEXITSTATUS(status);
		dup2((p->redir_out - 1), STDIN_FILENO);
		close(p->redir_out);
		close(p->redir_out - 1);
	}
}

int	run_node(t_shell *msh, t_parser *p)
{
	if (is_builting(msh, p, msh->stdoutcpy))
		return (0);
	else
		fork_child(msh, p);
	return (0);
}
