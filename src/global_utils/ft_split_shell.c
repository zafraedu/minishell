#include "minishell.h"

static int	ft_foundquotes(char *str, int *i)
{
	char	com;

	com = 0;
	if ((str[*i] == '\'' || str[*i] == '"') && str[*i] != 0)
	{
		com = str[*i];
		*i = *i + 1;
		while (str[*i] != 0 && str[*i] != com)
			*i = *i + 1;
		return (1);
	}
	return (0);
}

static int	ft_foundword(char *str, char s, int *i)
{
	if (str[*i] != s && str[*i] != 0)
	{
		while (str[*i] != 0 && str[*i] != s)
		{
			ft_foundquotes(str, i);
			*i = *i + 1;
		}
		return (1);
	}
	return (0);
}

static int	ft_cwords(char *str, char s)
{
	int	i;
	int	nwords;

	i = 0;
	nwords = 0;
	while (str[i])
	{
		while (str[i] == s && str[i] != 0)
			i++;
		if (str[i] != 0)
			nwords += ft_foundword(str, s, &i);
		if (str[i] != 0)
			ft_foundquotes(str, &i);
	}
	return (nwords);
}

char	**ft_split_shell(t_shell *msh, char *str, char s)
{
	int		i;
	int		is;
	int		len;
	char	**split;
	char	*aux;

	i = 0;
	is = 0;
	len = 0;
	split = ft_calloc(sizeof(char *), ft_cwords(str, s) + 1);
	while (str[i])
	{
		while (str[i] == s && str[i++] != 0)
			len++;
		if (ft_foundword(str, s, &i))
		{
			aux = ft_substr(str, len, i - len);
			split[is++] = ft_strtrim(aux, "\"\'");
			ft_memfree(aux);
			len = i;
		}
		msh->count_cmd_args = is;
	}
	return (split);
}
