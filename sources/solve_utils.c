/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 23:37:08 by upopee            #+#    #+#             */
/*   Updated: 2018/02/13 01:57:55 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		load_input(t_lgraph *g)
{
	int		n;

	n = g->nb_nodes;
	ft_memset(g->explored, FALSE, sizeof(*(g->explored)) * n);
	ft_memset(g->distance, NONE, sizeof(*(g->distance)) * n);
	ft_memset(g->previous, NONE, sizeof(*(g->previous)) * n);
	g->distance[0] = 0;
	g->nb_loops = g->nb_nodes;
	g->nb_links < g->nb_nodes ? g->nb_loops = g->nb_links + 1 : (void)g;
	g->curr_node = 0;
	g->flags = 0;
}

void		pre_check(t_pdata *dat, t_lgraph *graph)
{
	if (graph->nb_ants < 1 || graph->nb_nodes < 2 || graph->nb_links < 1)
		BSET(dat->flags, DATA_ERROR);
	else if (dat->start == NULL || dat->end == NULL || dat->start == dat->end)
		BSET(dat->flags, DATA_ERROR);
}

int			shortest_path_len(int *prev, int nb_nodes)
{
	int		len;
	int		i;

	len = 1;
	i = nb_nodes - 1;
	while (prev[i] != 0)
	{
		i = prev[i];
		len++;
	}
	return (len);
}

void		save_path(t_lgraph *graph)
{
	int		curr;
	int		prev;
	int		i;

	curr = graph->nb_nodes - 1;
	i = shortest_path_len(graph->previous, graph->nb_nodes) - 1;
	while (curr != 0)
	{
		prev = graph->previous[curr];
		graph->paths[graph->nb_paths][i] = curr;
		graph->links[prev][curr] = -1;
		graph->nb_links--;
		i--;
		curr = prev;
	}
	graph->nb_paths++;
}
