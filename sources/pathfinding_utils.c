/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinding_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 23:37:08 by upopee            #+#    #+#             */
/*   Updated: 2018/02/16 16:47:06 by upopee           ###   ########.fr       */
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

int			pre_check(t_pdata *dat, t_lgraph *graph)
{
	if (graph->nb_ants < 1 || graph->nb_nodes < 2 || graph->nb_links < 1)
		return (ERROR);
	else if (dat->start == NULL || dat->end == NULL || dat->start == dat->end)
		return (ERROR);
	BSET(dat->flags, PARSING_DONE);
	return (SUCCESS);
}

int			last_path_len(t_lgraph *graph)
{
	int		path_len;
	int		i;
	int		*path;

	path = graph->previous;
	path_len = 1;
	i = graph->nb_nodes - 1;
	while (path[i] != 0)
	{
		i = path[i];
		path_len++;
	}
	return (path_len);
}

void		save_path(t_lgraph *graph, int path_len)
{
	int		curr_node;
	int		prev_node;

	curr_node = graph->nb_nodes - 1;
	graph->paths_len[graph->nb_paths] = path_len;
	while (curr_node != 0)
	{
		prev_node = graph->previous[curr_node];
		graph->paths[graph->nb_paths][path_len - 1] = curr_node;
		graph->links[prev_node][curr_node] = -1;
		graph->nb_links--;
		path_len--;
		curr_node = prev_node;
	}
	graph->nb_paths++;
}
