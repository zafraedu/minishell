#include "minishell.h"

t_lexer *remove_node(t_lexer **lexer, t_lexer *tmp, t_lexer *prev)
{
    t_lexer *next = NULL;

    if (prev == NULL) 
    {
        *lexer = tmp->next;
        next = *lexer;
        ft_memfree(tmp);
    } 
    else 
    {
        prev->next = tmp->next;
        next = prev->next;
        ft_memfree(tmp);
    }
    return (next);
}

void    ft_erase_node(t_lexer **lexer) 
{
    t_lexer *tmp = *lexer;
    t_lexer *prev = NULL;

    while (tmp) 
    {
        if (tmp->data == NULL || tmp->data[0] == '\0') 
            tmp = remove_node(lexer, tmp, prev);
        else 
        {
            prev = tmp;
            tmp = tmp->next;
        }
    }
}

void    ft_free_array(char **array)
{
    int i;

    i = 0;
    while (array[i])
    {
        ft_memfree(array[i]);
        i++;
    }
    ft_memfree(array);
}

void    append_to_tmp_data(t_lexer **tmp, char *value)
{
    if ((*tmp)->data == NULL)
        (*tmp)->data = ft_strdup(value);
    else
    {
        (*tmp)->data = ft_strjoin((*tmp)->data, " ");
        (*tmp)->data = ft_strjoin((*tmp)->data, value);
    }

}