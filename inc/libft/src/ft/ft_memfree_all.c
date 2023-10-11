/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memfree_all.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zafraedu <zafraedu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 17:02:51 by zafraedu          #+#    #+#             */
/*   Updated: 2023/10/09 00:19:38 by zafraedu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

/**
 * Libera la memoria asignada para un array de cadenas de caracteres y el propio
 * array.
 *
 * Esta función libera la memoria asignada para cada cadena de caracteres en el
 * array 'ptr', y luego libera la memoria utilizada por el propio array 'ptr'.
 * Finalmente, establece el puntero 'ptr' a NULL para evitar problemas de acceso
 * a memoria liberada.
 *
 * @param ptr Puntero al array de cadenas de caracteres.
 */
void	ft_memfree_all(char **ptr)
{
	int	i;

	if (!ptr)
		return ;
	i = 0;
	while (ptr[i])
		ft_memfree(ptr[i++]);
	free(ptr);
	ptr = NULL;
}
