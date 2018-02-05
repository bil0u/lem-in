/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 10:42:37 by upopee            #+#    #+#             */
/*   Updated: 2018/02/05 11:58:11 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int		**init_matrix(int nb_lines)
{
	int		**new;
	int		i;

	if ((new = ft_memalloc(nb_lines * sizeof(*new)) == NULL)
		exit(ERROR);
	i = 0;
	while (i < nb_lines)
	{
		if ((new[i] = ft_memalloc(nb_lines * sizeof(**new)) == NULL)
			exit(ERROR);
		i++;
	}
	return (new);
}

void	del_matrix(int **tab, int nb_lines)
{
	while (nb_lines--)
		ft_memdel(&(tab[nb_lines]));
	ft_memdel(&(tab));
}

void	node_cleaner(void *content, size_t size)
{
	t_room	*node;

	node = (t_room *)content;
	ft_strdel(&(node->name));
	(void)size;
}
