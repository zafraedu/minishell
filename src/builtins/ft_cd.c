#include "minishell.h"

static void	ft_change_oldpwd_env(t_shell *info);
static void	ft_change_pwd_env(t_shell *msh);

/**
 * @file ft_cd.c
 * @brief Cambia el directorio de trabajo actual del shell.
 *
 * Esta función maneja el comando "cd" para cambiar el directorio de trabajo
 * actual. Puede recibir un argumento para el nuevo directorio o cambiar al
 * directorio HOME si no se proporciona ninguno. Además, actualiza las variables
 * de entorno PWD y OLDPWD.
 *
 * @param msh Un puntero al contexto del shell.
 */
void	ft_cd(t_shell *msh)
{
	char	*path;

	path = NULL;
	if (msh->count_cmd_args > 2)
		return (printf("cd :too many arguments\n"), (void)NULL);
	ft_change_oldpwd_env(msh);
	if (msh->cmd_args[1])
		path = ft_strdup(msh->cmd_args[1]);
	else if (!path)
		path = ft_strdup(getenv("HOME"));
	if (chdir(path))
		perror("cd");
	else
		ft_pwd(msh); //test
	ft_memfree(path);
	ft_change_pwd_env(msh);
}

/**
 * @brief Actualiza la variable de entorno "OLDPWD".
 *
 * Esta función construye una cadena que representa la variable de entorno
 * "OLDPWD" seguida del directorio de trabajo actual y la agrega al entorno
 * del shell mediante la función `add_arg_to_env`.
 *
 * @param info Un puntero al contexto del shell.
 */
static void	ft_change_oldpwd_env(t_shell *info)
{
	char	*to_send;
	char	*path;

	path = getcwd(NULL, 0);
	to_send = ft_strjoin("OLDPWD=", path);
	add_arg_to_env(to_send, info);
	ft_memfree(to_send);
	ft_memfree(path);
}

/**
 * @brief Actualiza la variable de entorno "PWD".
 *
 * Esta función busca la variable de entorno "PWD" en la lista enlazada de
 * variables de entorno del shell. Luego, actualiza su valor con el directorio
 * de trabajo actual obtenido mediante la función `getcwd`.
 *
 * @param msh Un puntero al contexto del shell.
 */
static void	ft_change_pwd_env(t_shell *msh)
{
	t_env	*tmp;
	char	*pwd;

	tmp = msh->env;
	while (tmp)
	{
		if (ft_strcmp(tmp->var_name, "PWD") == 0)
		{
			pwd = getcwd(NULL, 0);
			ft_memfree(tmp->value_var);
			tmp->value_var = ft_strdup(pwd);
		}
		tmp = tmp->next;
	}
	ft_memfree(pwd);
}
