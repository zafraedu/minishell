#include "minishell.h"

static void	child_proccess(t_shell *msh);
static void	exec_cmd(t_shell *msh);
static void	ft_next_cmd(t_shell *msh);
static void	handle_status(t_shell *msh);

/**
 * @brief Ejecuta los comandos parseados en el contexto del shell.
 *
 * Esta función ejecuta los comandos parseados en el contexto del shell, ya sea
 * como comandos internos (builtins) o como comandos externos utilizando el
 * sistema de procesos.
 *
 * @param msh Un puntero al contexto del shell.
 */
void	ft_executer(t_shell *msh)
{
	pid_t	pid;

	while (msh->parser)
	{
		if (!ft_isascii(msh->parser->cmd[0]))
		{
			msh->exit_status = 1;
			break ;
		}
		msh->cmd_args = ft_split_shell(msh, msh->parser->cmd, 32);
		if (is_builtin(msh))
			ft_builtin(msh);
		else
		{
			g_signal = S_CMD;
			pid = fork();
			if (pid == 0)
				child_proccess(msh);
			else
				waitpid(-1, &msh->exit_status, 0);
			handle_status(msh);
		}
		ft_next_cmd(msh);
	}
}

/**
 * @brief Función ejecutada por el proceso hijo.
 *
 * @param msh Un puntero al contexto del shell.
 */
static void	child_proccess(t_shell *msh)
{
	if (is_builtin(msh))
		ft_builtin(msh);
	else
		exec_cmd(msh);
}

/**
 * @brief Ejecuta un comando externo en el contexto del proceso hijo.
 *
 * @param msh Un puntero al contexto del shell.
 */
static void	exec_cmd(t_shell *msh)
{
	char	*cmd_path;
	char	**envp;

	envp = env_to_array(msh);
	if (msh->parser->redir_in != 0)
		dup2(msh->parser->redir_in, STDIN_FILENO);
	if (msh->parser->redir_out != 1)
		dup2(msh->parser->redir_out, STDOUT_FILENO);
	cmd_path = get_cmd_path(msh->cmd_args[0], msh->env);
	if (!ft_isalnum(msh->cmd_args[0][0]))
	{
		ft_memfree(cmd_path);
		cmd_path = msh->cmd_args[0];
	}
	execve(cmd_path, msh->cmd_args, envp);
	exit(127);
}

/**
 * @brief Avanza al siguiente comando parseado en la lista.
 *
 * Esta función avanza al siguiente comando parseado en la lista, liberando la
 * memoria asociada al comando actual.
 *
 * @param msh Un puntero al contexto del shell.
 */
static void	ft_next_cmd(t_shell *msh)
{
	t_parser	*tmp;

	ft_memfree(msh->parser->cmd);
	ft_memfree_all(msh->cmd_args);
	if (msh->parser->redir_in != 0)
		close(msh->parser->redir_in);
	if (msh->parser->redir_out != 1)
		close(msh->parser->redir_out);
	tmp = msh->parser;
	msh->parser = msh->parser->next;
	ft_memfree(tmp);
}

/**
 * @brief Maneja el estado de finalización del proceso hijo.
 *
 * Esta función maneja el estado de finalización del proceso hijo después de la
 * ejecución de un comando. Actualiza el código de salida del proceso hijo y
 * realiza acciones específicas dependiendo del estado y las señales recibidas.
 *
 * @param msh Un puntero al contexto del shell.
 */
static void	handle_status(t_shell *msh)
{
	if (WIFEXITED(msh->exit_status))
		msh->exit_status = WEXITSTATUS(msh->exit_status);
	if (msh && msh->exit_status == 127)
		printf("%s: %s\n", msh->cmd_args[0], ERR_CMD);
	if (g_signal == S_SIGINT_CMD)
		msh->exit_status = 130;
	g_signal = S_BASE;
}
