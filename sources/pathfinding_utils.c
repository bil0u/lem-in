/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinding_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 23:37:08 by upopee            #+#    #+#             */
/*   Updated: 2018/02/27 01:40:04 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <unistd.h>

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
	BUNSET(g->flags, END_FOUND);
}

int			pre_check(t_pdata *dat, t_lgraph *graph)
{
	if (!BIS_SET(dat->flags, EOL_REACHED))
		gnl_end(STDIN_FILENO);
	if (graph->nb_ants < 1 || graph->nb_nodes < 2 || graph->nb_links < 1)
		return (ERROR);
	else if (dat->start == NULL || dat->end == NULL || dat->start == dat->end)
		return (ERROR);
	BSET(dat->flags, PARSE_OK);
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

static int	check_overlap(t_lgraph *g)
{
	int		curr_node;
	int		prev_node;

	curr_node = g->nb_nodes - 1;
	while (curr_node != 0)
	{
		prev_node = g->previous[curr_node];
		if (g->used[curr_node] == TRUE && curr_node < g->nb_nodes - 1)
			return (FALSE);
		curr_node = prev_node;
	}
	return (TRUE);
}

void		save_path(t_lgraph *g, int path_len, int *optimal)
{
	int		curr_node;
	int		prev_node;

	if ((*optimal = check_overlap(g)) == FALSE)
		return ;
	curr_node = g->nb_nodes - 1;
	g->paths_len[g->nb_paths] = path_len;
	while (curr_node != 0)
	{
		prev_node = g->previous[curr_node];
		g->paths[g->nb_paths][path_len - 1] = curr_node;
		g->used[curr_node] = TRUE;
		g->links[prev_node][curr_node] = -g->links[prev_node][curr_node];
		g->links[curr_node][prev_node] = -g->links[curr_node][prev_node];
		g->nb_links--;
		path_len--;
		curr_node = prev_node;
	}
	g->nb_paths++;
}
