#include "minishell.h"

/**
 * @brief Convierte la lista enlazada en un array.
 *
 * Esta función convierte la lista enlazada de variables de entorno en un array
 * de cadenas de la forma "nombre=valor", donde cada elemento del array
 * representa una variable de entorno. El último elemento del array es NULL.
 *
 * @param msh Un puntero al contexto del shell.
 * @return Un array de cadenas que representa las variables de entorno en el
 * formato "nombre=valor".
 */
char	**env_to_array(t_shell *msh)
{
	int		len;
	t_env	*tmp;
	char	**ret;
	char	*tmp_str;

	len = 0;
	tmp = msh->env;
	while (tmp)
	{
		len++;
		tmp = tmp->next;
	}
	ret = malloc((sizeof(char *) * len) + 1);
	tmp = msh->env;
	len = 0;
	while (tmp)
	{
		tmp_str = ft_strjoin(tmp->var_name, "=");
		ret[len] = ft_strjoin(tmp_str, tmp->value_var);
		ft_memfree(tmp_str);
		tmp = tmp->next;
		len++;
	}
	ret[len] = NULL;
	return (ret);
}

/**
 * @brief Obtiene la ruta completa de un comando en función del valor de la
 * variable de entorno "PATH".
 *
 * Esta función toma el nombre de un comando y la lista de variables de entorno,
 * busca el valor de la variable de entorno "PATH", y luego busca el comando en
 * cada directorio especificado en "PATH". Devuelve la ruta completa del comando
 * si se encuentra y es ejecutable.
 *
 * @param cmd Una cadena que representa el nombre del comando a buscar.
 * @param env Un puntero a la lista de variables de entorno que puede contener
 * el valor de la variable "PATH".
 * @return Una cadena que representa la ruta completa del comando si se
 * encuentra y es ejecutable; NULL si no se encuentra.
 */
char	*get_cmd_path(char *cmd, t_env *env)
{
	char	**paths;
	int		i;
	char	*tmp_str;
	char	*complete_path;

	while (env && ft_strncmp(env->var_name, "PATH", 4))
		env = env->next;
	if (!env)
		return (NULL);
	paths = ft_split(env->value_var, ':');
	i = -1;
	while (paths[++i])
	{
		tmp_str = ft_strjoin(paths[i], "/");
		complete_path = ft_strjoin(tmp_str, cmd);
		ft_memfree(tmp_str);
		if (!access(complete_path, X_OK))
		{
			ft_memfree_all(paths);
			return (complete_path);
		}
		ft_memfree(complete_path);
	}
	ft_memfree_all(paths);
	return (NULL);
}
