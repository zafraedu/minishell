#include "minishell.h"

void	replace_env_variable(char **data, char *prefix, char *sufix,
		char *env_value)
{
	ft_memfree(*data);
	if (env_value)
	{
		*data = ft_strjoin(prefix, env_value);
		ft_memfree(prefix);
		*data = ft_strjoin(*data, sufix);
	}
	else
	{
		*data = ft_strjoin(prefix, sufix);
		ft_memfree(prefix);
	}
	if (sufix[0] != '\0')
		ft_memfree(sufix);
}

void	process_env_substring(char **dollar_pos, char **str, char **sufix,
		char **env_value)
{
	char	*next_dollar_pos;
	char	*next_space_pos;

	next_dollar_pos = ft_strchr(*dollar_pos + 1, '$');
	next_space_pos = ft_strchr(*dollar_pos + 1, ' ');
	if (next_dollar_pos)
	{
		if (next_space_pos && (next_dollar_pos > next_space_pos))
		{
			*str = ft_substr(*dollar_pos, 1, next_space_pos - *dollar_pos - 1);
			*sufix = ft_strdup(next_space_pos);
		}
		else
		{
			*str = ft_substr(*dollar_pos, 1, next_dollar_pos - *dollar_pos - 1);
			*sufix = ft_strdup(next_dollar_pos);
		}
	}
	else
	{
		if (next_space_pos)
		{
			*str = ft_substr(*dollar_pos, 1, next_space_pos - *dollar_pos - 1);
			*sufix = ft_strdup(next_space_pos);
		}
		else
		{
			*str = ft_substr(*dollar_pos, 1, ft_strlen(*dollar_pos + 1));
			*sufix = "";
		}
	}
	*env_value = getenv(*str);
	ft_memfree(*str);
}


void	process_env_variable(char **data, char **dollar_pos)
{
	char	*prefix;
	char	*sufix;
	char	*env_value;
	char	*str;
	char	*next_dollar_pos;

	next_dollar_pos = ft_strchr(*dollar_pos + 1, '$');
	if (*((*dollar_pos) + 1) != '?')  //Esto deberiamos incluirlo al momento de ejecutar el comando
		process_env_substring(dollar_pos, &str, &sufix, &env_value);
	else
	{
		env_value = ft_itoa(42); // Deberia ser el exit status
		sufix = ft_strdup(*dollar_pos + 2);
		printf("sufix: %s\n", sufix);
	}
	prefix = ft_substr(*data, 0, *dollar_pos - *data);
	replace_env_variable(data, prefix, sufix, env_value);
	if (!next_dollar_pos)
		*dollar_pos = NULL;
	else
		*dollar_pos = ft_strchr(*data, '$');
}

/* void	process_quoted_data(t_lexer **tmp)
{
	char	**array;
	char	*dollar_pos;
	int		i;

	(*tmp)->data = ft_strtrim((*tmp)->data, "\"");
	array = ft_split((*tmp)->data, ' ');
	ft_memfree((*tmp)->data);
	(*tmp)->data = NULL;
	i = -1;
	while (array[++i])
	{
		dollar_pos = ft_strchr(array[i], '$');
		while (dollar_pos)
		{
			process_env_variable(&(array[i]), &dollar_pos);
			if (!dollar_pos)
				break ;
		}
	}
	i = -1;
	while (array[++i])
		append_to_tmp_data(tmp, array[i]);
	ft_free_array(array);
} */

void	ft_replace(t_lexer **lexer)
{
	t_lexer	*tmp;
	char	*dollar_pos;
	int		aux;

	aux = 0;
	tmp = *lexer;
	while (tmp)
	{
		if (tmp->type == T_CMD || tmp->type == T_INFILE
			|| tmp->type == T_OUTFILE)
		{
			if (tmp->data[0] == '\"')
				tmp->data = ft_strtrim(tmp->data, "\"");
				//process_quoted_data(&tmp);
			dollar_pos = ft_strchr(tmp->data, '$');
			while (tmp->data[0] != '\'' && dollar_pos)
				process_env_variable(&(tmp->data), &dollar_pos);
			if (tmp->data[0] == '\'')
				tmp->data = ft_strtrim(tmp->data, "\'");
		}
		tmp = tmp->next;
	}
	ft_erase_node(lexer);
}
