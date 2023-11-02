#include "minishell.h"

void	sigint_handler(int sig)
{
	(void)sig;
	rl_on_new_line(); //nose pa que sirve
	rl_redisplay();   //nose pa que sirve
	ft_putchar_fd('\n', 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}
