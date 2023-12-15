#include "minishell.h"

char	*get_env_name(char *fullenv)
{
	int	i;

	i = 0;
	while (fullenv[i] && fullenv[i] != '=' && fullenv[i] != ' ')
		i++;
	return (ft_substr(fullenv, 0, i));
}

char	*get_env_value(char *fullenv)
{
	int	i;

	i = 0;
	while (fullenv[i] && fullenv[i] != '=' && fullenv[i] != ' ')
		i++;
	if (fullenv[i + 1] == '\"')
		return (ft_substr(fullenv, i + 2, ft_strlen(fullenv) - i));
	else
		return (ft_substr(fullenv, i + 1, ft_strlen(fullenv) - i));
}
