/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 10:42:37 by upopee            #+#    #+#             */
/*   Updated: 2018/02/08 06:21:32 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "lem_in.h"

int				**init_matrix(int nb_nodes)
{
	int		**new;
	int		i;

	if ((new = ft_memalloc(nb_nodes * sizeof(*new))) == NULL)
		exit(ERROR);
	i = nb_nodes;
	while (i--)
	{
		if ((new[i] = ft_memalloc(nb_nodes * sizeof(**new))) == NULL)
			exit(ERROR);
	}
	return (new);
}

static void		del_matrix(int **tab, int nb_nodes)
{
	if (tab)
	{
		while (nb_nodes--)
			ft_memdel((void **)&(tab[nb_nodes]));
		ft_memdel((void **)tab);
	}
}

static void		node_cleaner(void *content, size_t size)
{
	t_room	*node;

	node = (t_room *)content;
	ft_strdel(&(node->name));
	ft_memdel(&content);
	(void)size;
}

void			env_cleaner(t_lenv *env)
{
	ft_lstdel(&(env->graph.nodes), &node_cleaner);
	del_matrix(env->graph.links, env->graph.nb_nodes);
	ft_memset(env, 0, sizeof(*env));
}
