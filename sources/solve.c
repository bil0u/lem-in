/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/14 04:39:09 by upopee            #+#    #+#             */
/*   Updated: 2018/02/14 18:40:57 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "struct_utils.h"

/*
static void	print_path_state(t_lgraph *graph, int path_no)
{
	int		i;
	int		len;
	int		*pos;
	int		*busy;

	pos = graph->paths[path_no];
	len = graph->paths_len[path_no];
	busy = graph->state[path_no];;
	i = 0;
	ft_printf("\nPATH #%d :\t", (path_no + 1));
	ft_printf("{magenta}%s{eoc} [", graph->nodes[0]->name);
	graph->ants_start ? ft_printf("{yellow}%d{eoc}] ", graph->ants_start)
		: ft_printf("{red}%d{eoc}] ", graph->ants_start);
	while (i < len - 1)
	{
		ft_printf("--> (");
		busy[pos[i]] ? ft_printf("{green}") : ft_printf("{red}");
		ft_printf("%s{eoc}", graph->nodes[pos[i]]->name);
		if (busy[pos[i]])
			ft_printf(": {blue}%d{eoc}", graph->ant_no[pos[i]]);
		ft_printf(") ");
		i++;
	}
	ft_printf("--> [");
	graph->ants_end ? ft_printf("{yellow}%d{eoc}] ", graph->ants_end)
		: ft_printf("{red}%d{eoc}] ", graph->ants_end);
	ft_printf("{magenta}%s{eoc}\n", graph->nodes[pos[i]]->name);
}
*/

static int		handle_directmap(t_lgraph *graph, int path_no, int *i)
{
	int		len;
	char	*room_name;
	int		*pos;

	pos = graph->paths[path_no];
	len = graph->paths_len[path_no];
	*i = len - 1;
	if (len == 1)
	{
		graph->ants_start--;
		graph->ants_end++;
		room_name = graph->nodes[pos[*i]]->name;
		ft_printf("L%d-%s ", graph->nb_ants - graph->ants_start, room_name);
		return (SUCCESS);
	}
	return (len);
}
static void		update_path(t_lgraph *g, int p_no)
{
	int		i;
	int		len;
	int		*pos;
	int		*busy;

	if (!(len = handle_directmap(g, p_no, &i)))
		return ;
	pos = g->paths[p_no];
	busy = g->state[p_no];
	if (busy[pos[i - 1]])
		ft_printf("L%d-%s ", g->ant_no[pos[i - 1]], g->nodes[pos[i]]->name);
	busy[pos[i - 1]] ? g->ants_end++ : (void)i;
	busy[pos[i - 1]] ? g->ant_no[pos[i - 1]] = 0 : (void)i;
	busy[pos[i - 1]] ? busy[pos[i - 1]] = FALSE : (void)i;
	while (--i > 0)
	{
		ft_swap(&(busy[pos[i]]), &(busy[pos[i - 1]]));
		ft_swap(&(g->ant_no[pos[i]]), &(g->ant_no[pos[i - 1]]));
		if (busy[pos[i]])
			ft_printf("L%d-%s ", g->ant_no[pos[i]], g->nodes[pos[i]]->name);
	}
	g->ants_start > 0 ? busy[pos[0]] = TRUE : (void)i;
	busy[pos[0]] ? g->ants_start-- : (void)i;
	if (busy[pos[0]])
		g->ant_no[pos[0]] = g->nb_ants - g->ants_start;
	if (busy[pos[0]])
		ft_printf("L%d-%s ", g->ant_no[pos[0]], g->nodes[pos[0]]->name);
}

void		cross_paths(t_lgraph *graph)
{
	int		curr_path;

	graph->state = init_matrix(graph->nb_paths, graph->nb_nodes);
	graph->ants_start = graph->nb_ants;
	curr_path = -1;
//	while (++curr_path < graph->nb_paths)
//		print_path_state(graph, curr_path);
//	ft_printf("\n");
	while (graph->ants_end < graph->nb_ants)
	{
		curr_path = 0;
		while (curr_path < graph->nb_paths)
		{
			update_path(graph, curr_path);
//			print_path_state(graph, curr_path);
			curr_path++;
		}
		ft_printf("\n");
	}
	curr_path = graph->nb_paths;
	while (curr_path--)
		ft_memdel((void **)&(graph->state[curr_path]));
	ft_memdel((void **)&(graph->state));
}
