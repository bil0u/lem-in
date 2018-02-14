/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinding_core.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 19:27:38 by upopee            #+#    #+#             */
/*   Updated: 2018/02/14 04:39:29 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "pathfinding.h"

static void		mark_visited(t_lgraph *graph)
{
	int		i;
	int		nearest;

	i = graph->nb_nodes;
	nearest = NONE;
	while (i--)
	{
		if (graph->explored[i] == FALSE && graph->distance[i] != NONE)
		{
			if (nearest == NONE)
				nearest = i;
			else if (graph->distance[i] < graph->distance[nearest])
				nearest = i;
		}
	}
	if (nearest != NONE)
	{
		graph->curr_node = nearest;
		graph->explored[nearest] = TRUE;
		if (nearest == graph->nb_nodes - 1)
			BSET(graph->flags, END_FOUND);
	}
}

static void		find_shortest_path(t_lgraph *g)
{
	int		i;
	int		f;
	int		c;

	i = g->nb_loops;
	while (i-- && !BIS_SET(g->flags, END_FOUND))
	{
		mark_visited(g);
		f = g->curr_node;
		c = 0;
		while (c < g->nb_nodes)
		{
			if (g->links[f][c] != 0
				&& ((g->distance[f] + g->links[f][c]) < g->distance[c]
				||	g->distance[c] == NONE))
			{
				g->distance[c] = g->distance[f] + g->links[f][c];
				g->previous[c] = f;
			}
			c++;
		}
	}
}

void			get_paths(t_lgraph *graph)
{
	int		tmp;
	int		still_optimal;
	int		cumul;
	int		curr;

	tmp = graph->nb_links;
	cumul = 0;
	still_optimal = TRUE;
	while (still_optimal)
	{
		load_input(graph);
		find_shortest_path(graph);
		if (!BIS_SET(graph->flags, END_FOUND))
			break;
		curr = last_path_len(graph);
		still_optimal = graph->nb_ants - cumul > cumul - curr ? TRUE : FALSE;
		still_optimal = graph->nb_paths < NB_PATHS_MAX ? still_optimal : FALSE;
		if (still_optimal)
		{
			save_path(graph, curr);
			cumul += curr;
		}
	}
	graph->nb_links = tmp;
}