/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 10:42:37 by upopee            #+#    #+#             */
/*   Updated: 2018/02/13 01:03:27 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "lem_in.h"

static int		**init_matrix(int nb_nodes)
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

static void		init_buffers(t_lgraph *g)
{
	int		n;
	int		i;

	n = g->nb_nodes;
	g->links = init_matrix(n);
	g->paths = init_matrix(n);
	i = n;
	while (i--)
		ft_memset(g->paths[i], NONE, sizeof(**(g->paths)) * n);
	if ((g->nodes = ft_memalloc(n * sizeof(*(g->nodes)))) == NULL)
		exit(ERROR);
	if ((g->explored = ft_memalloc(n * sizeof(*(g->explored)))) == NULL)
		exit(ERROR);
	if ((g->distance = ft_memalloc(n * sizeof(*(g->distance)))) == NULL)
		exit(ERROR);
	if ((g->previous = ft_memalloc(n * sizeof(*(g->previous)))) == NULL)
		exit(ERROR);
}

void			init_graph(t_pdata *dat, t_lgraph *graph)
{
	t_list	*tmp;
	t_list	*leak;
	t_room	*curr_room;
	int		i;

	init_buffers(graph);
	i = dat->end ? graph->nb_nodes - 2 : graph->nb_nodes - 1;
	graph->nodes[0] = dat->start;
	graph->nodes[graph->nb_nodes - 1] = dat->end;
	tmp = dat->nodes_tmp;
	while (tmp != NULL)
	{
		curr_room = (t_room *)tmp->content;
		if (curr_room != dat->start && curr_room != dat->end)
		{
			graph->nodes[i] = curr_room;
			i--;
		}
		leak = tmp;
		tmp = tmp->next;
		ft_memdel((void **)&leak);
	}
	dat->nodes_tmp = NULL;
}

void			del_graph(t_lgraph *graph)
{
	int		i;

	i = graph->nb_nodes;
	while (i--)
	{
		ft_strdel(&(graph->nodes[i]->name));
		ft_memdel((void **)&(graph->nodes[i]));
		ft_memdel((void **)&(graph->links[i]));
		ft_memdel((void **)&(graph->paths[i]));
	}
	ft_memdel((void **)&(graph->nodes));
	ft_memdel((void **)&(graph->links));
	ft_memdel((void **)&(graph->paths));
	ft_memdel((void **)&(graph->explored));
	ft_memdel((void **)&(graph->distance));
	ft_memdel((void **)&(graph->previous));
}
