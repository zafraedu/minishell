#include "minishell.h"

static void	replace_env_variable(char **data, char *prefix, char *sufix,
		char *env_value)
{
	char	*tmp;

	ft_memfree(*data);
	if (env_value)
	{
		tmp = ft_strjoin(prefix, env_value);
		ft_memfree(prefix);
		*data = ft_strjoin(tmp, sufix);
		ft_memfree(tmp);
	}
	else
	{
		if (prefix[0] != '\0' && sufix[0] != '\0')
			*data = ft_strjoin(prefix, sufix);
		else if (prefix[0] != '\0')
			*data = ft_strdup(prefix);
		else if (sufix[0] != '\0')
			*data = ft_strdup(sufix);
		else
			*data = "";
		ft_memfree(prefix);
	}
	if (sufix[0] != '\0')
		ft_memfree(sufix);
}


static void	process_env_variable(char **data, char **dollar_pos, t_shell *msh)
{
	char	*prefix;
	char	*sufix;
	char	*env_value;

	prefix = ft_substr(*data, 0, *dollar_pos - *data);
	if (*((*dollar_pos) + 1) != '?')
	{
		env_value = process_env_substring(dollar_pos, &sufix, msh);
		replace_env_variable(data, prefix, sufix, env_value);
	}
	else
	{
		if (*((*dollar_pos) + 2) != '\0')
			sufix = ft_strdup(*dollar_pos + 2);
		else
			sufix = "";
		env_value = ft_itoa(msh->exit_status);
		replace_env_variable(data, prefix, sufix, env_value);
		ft_memfree(env_value);
	}
	*dollar_pos = ft_strchr(*data, '$');
}

static void	process_quotes(t_shell *msh, t_lexer *tmp)
{
	char	*str;
	int		aux;
	char	*dollar_pos;

	aux = 0;
	if (tmp->data[0] == '\"')
	{
		str = ft_strtrim(tmp->data, "\"");
		ft_memfree(tmp->data);
		tmp->data = ft_strdup(str);
		ft_memfree(str);
		aux = 1;
	}
	dollar_pos = ft_strchr(tmp->data, '$');
	while (tmp->data[0] != '\'' && dollar_pos)
		process_env_variable(&(tmp->data), &dollar_pos, msh);
	if (aux == 1)
	{
		str = ft_strjoin("\"", tmp->data);
		ft_memfree(tmp->data);
		tmp->data = ft_strjoin(str, "\"");
		ft_memfree(str);
	}
}

void	ft_replace(t_shell *msh)
{
	t_lexer	*tmp;

	if (!msh || !msh->lexer)
		return ;
	tmp = msh->lexer;
	while (tmp)
	{
		if (tmp->type == T_CMD || tmp->type == T_INFILE
			|| tmp->type == T_OUTFILE)
		{
			process_quotes(msh, tmp);
		}
		tmp = tmp->next;
	}
	ft_erase_node(&(msh->lexer));
}
