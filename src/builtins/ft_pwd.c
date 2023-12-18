#include "minishell.h"

/**
 * @brief Imprime el directorio de trabajo actual en la salida estándar.
 *
 * Esta función obtiene el directorio de trabajo actual mediante la función
 * `getcwd` y lo imprime en la salida estándar.
 *
 * @param msh Un puntero al contexto del shell.
 */
void	ft_pwd(t_shell *msh)
{
	char	*pwd;

	msh->exit_status = 0;
	pwd = getcwd(NULL, 0);
	ft_putendl_fd(pwd, 1);
	ft_memfree(pwd);
}
