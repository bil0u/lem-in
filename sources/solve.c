/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/14 04:39:09 by upopee            #+#    #+#             */
/*   Updated: 2018/02/24 16:32:16 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "struct_utils.h"
#include "print_utils.h"

static int		handle_directmap(t_lgraph *graph, t_pdata *dat, int path_no)
{
	int		len;
	char	*room_name;
	int		*pos;

	pos = graph->paths[path_no];
	len = graph->paths_len[path_no];
	if (len == 1)
	{
		graph->ants_start--;
		graph->ants_end++;
		room_name = graph->nodes[pos[0]]->name;
		if (!BIS_SET(dat->flags, VERBOSE))
			ft_printf("L%d-%s ", graph->nb_ants - graph->ants_start, room_name);
		return (SUCCESS);
	}
	return (len);
}

static void		update_path(t_lgraph *g, t_pdata *d, int p_no, int i)
{
	int		*pos;
	int		*busy;

	pos = g->paths[p_no];
	busy = g->state[p_no];
	if (busy[pos[i - 1]] && !BIS_SET(d->flags, VERBOSE))
		ft_printf("L%d-%s ", g->ant_no[pos[i - 1]], g->nodes[pos[i]]->name);
	busy[pos[i - 1]] ? g->ants_end++ : (void)i;
	busy[pos[i - 1]] ? g->ant_no[pos[i - 1]] = 0 : (void)i;
	busy[pos[i - 1]] ? busy[pos[i - 1]] = FALSE : (void)i;
	while (--i > 0)
	{
		ft_swap(&(busy[pos[i]]), &(busy[pos[i - 1]]));
		ft_swap(&(g->ant_no[pos[i]]), &(g->ant_no[pos[i - 1]]));
		if (busy[pos[i]] && !BIS_SET(d->flags, VERBOSE))
			ft_printf("L%d-%s ", g->ant_no[pos[i]], g->nodes[pos[i]]->name);
	}
	g->ants_start > 0 ? busy[pos[0]] = TRUE : (void)i;
	busy[pos[0]] ? g->ants_start-- : (void)i;
	busy[pos[0]] ? (g->ant_no[pos[0]] = g->nb_ants - g->ants_start) : (void)i;
	if (busy[pos[0]] && !BIS_SET(d->flags, VERBOSE))
		ft_printf("L%d-%s ", g->ant_no[pos[0]], g->nodes[pos[0]]->name);
}

void			cross_paths(t_lgraph *graph, t_pdata *dat)
{
	int		i;
	int		curr_path;
	int		path_len;

	ft_putchar('\n');
	graph->ants_start = graph->nb_ants;
	i = 1;
	while (graph->ants_end < graph->nb_ants)
	{
		curr_path = -1;
		while (++curr_path < graph->nb_paths)
		{
			if ((path_len = handle_directmap(graph, dat, curr_path)) > 0)
				update_path(graph, dat, curr_path, path_len - 1);
			if (BIS_SET(dat->flags, VERBOSE))
				print_path_state(graph, graph->paths[curr_path], curr_path, i);
		}
		!BIS_SET(dat->flags, VERBOSE) ? ft_putchar('\n') : (void)i;
		i++;
	}
}
