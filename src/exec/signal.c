#include "minishell.h"

int			g_signal;

static void	sigint_handler(int sig);
static void	sigint_handler_aux(void);

/**
 * @brief Inicializa la gestión de señales en el shell.
 *
 * Esta función inicializa la gestión de señales en el shell, estableciendo los
 * manejadores de señales para SIGINT y SIGQUIT. Además, inicializa la variable
 * global `g_signal` en el estado base.
 */
void	signal_init(void)
{
	g_signal = S_BASE;
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

/**
 * @brief Manejador de señales para SIGINT y SIGQUIT.
 *
 * Esta función maneja las señales SIGINT y SIGQUIT. Dependiendo del estado
 * actual de la señal global `g_signal`, realiza acciones específicas, como
 * interrumpir la ejecución de un comando, cancelar un comando en ejecución
 * o finalizar un here document.
 *
 * @param sig El número de la señal recibida.
 */
static void	sigint_handler(int sig)
{
	(void)sig;
	if (g_signal == S_BASE || g_signal == S_SIGINT)
	{
		rl_on_new_line();
		rl_redisplay();
		ft_putstr_fd("\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (g_signal == S_CMD)
	{
		g_signal = S_SIGINT_CMD;
		ft_putstr_fd("\n", 1);
		rl_on_new_line();
	}
	else if (g_signal == S_HEREDOC)
	{
		ioctl(0, TIOCSTI, '\n');
		exit(0);
	}
	sigint_handler_aux();
}

/**
 * @brief Función auxiliar para manejar situaciones adicionales de SIGINT.
 *
 * Esta función maneja situaciones adicionales de SIGINT que no están cubiertas
 * directamente en el manejador principal. Por ejemplo, cancela la ejecución de
 * un here document o establece la señal `S_SIGINT` en estado base o heredoc.
 */
static void	sigint_handler_aux(void)
{
	if (g_signal == S_HEREDOC_END)
	{
		ft_putstr_fd("\n", 1);
		g_signal = S_CANCEL_EXEC;
	}
	else if (g_signal == S_BASE || g_signal == S_HEREDOC)
		g_signal = S_SIGINT;
}
