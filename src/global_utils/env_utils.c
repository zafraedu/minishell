#include "minishell.h"

/**
 * Busca una variable de entorno específica en env.
 *
 * @param var La variable de entorno que busca.
 * @param env Arreglo de variables de entorno.
 *
 * @return Indice de `var` si se encuentra -1 si no se encuentra.
*/
int	ft_foundenv(char *var, char **env)
{
	int		i;
	char	*aux;

	if (!var[0])
		return (-1);
	i = 0;
	while (env[i])
	{
		aux = ft_strchr(env[i], '=') + 1;
		if (ft_strlen(var) == (size_t)(aux - env[i] - 1))
			if (!ft_strncmp(var, env[i], ft_strlen(var)))
				return (i);
		i++;
	}
	return (-1);
}
