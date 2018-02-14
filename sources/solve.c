/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/14 04:39:09 by upopee            #+#    #+#             */
/*   Updated: 2018/02/14 05:13:20 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "struct_utils.h"

static void	print_path_state(t_lgraph *graph, int path_no, int as, int ae)
{
	int		i;
	int		len;
	int		*pos;
	int		*busy;

	pos = graph->paths[path_no];
	len = graph->paths_len[path_no];
	busy = graph->state[path_no];;
	i = 0;
	ft_printf("PATH #%d :\t", (path_no + 1));
	as ? ft_printf("{green}%s{eoc} ", graph->nodes[0]->name)
		: ft_printf("{red}%s{eoc} ", graph->nodes[0]->name);
	ft_printf("[{yellow}%d{eoc}] ", as);
	while (i < len - 1)
	{
		if (busy[pos[i]])
			ft_printf("--> {green}");
		else
			ft_printf("--> {red}");
		ft_printf("%s{eoc} ", graph->nodes[pos[i]]->name);
		i++;
	}
	ft_printf("--> [{blue}%d{eoc}] ", ae);
	ae ? ft_printf("{green}%s{eoc}\n", graph->nodes[pos[i]]->name)
		: ft_printf("{red}%s{eoc}\n", graph->nodes[pos[i]]->name);

}

static void		update_path(t_lgraph *graph, int p_no, int *astart, int *aend)
{
	int		i;
	int		len;
	int		*pos;
	int		*busy;

	if ((len = graph->paths_len[p_no]) == 1)
	{
		(*astart)--;
		(*aend)++;
		return ;
	}
	pos = graph->paths[p_no];
	busy = graph->state[p_no];
	i = len - 2;
	busy[pos[i]] ? (*aend)++ : (void)i;
	busy[pos[i]] ? busy[pos[i]] = FALSE : (void)i;
	while (i > 0)
	{
		ft_swap(&(busy[pos[i]]), &(busy[pos[i - 1]]));
		i--;
	}
	(*astart > 0) ? busy[pos[0]] = TRUE : (void)i;
	busy[pos[0]] ? (*astart)-- : (void)i;
}

void		cross_paths(t_lgraph *graph)
{
	int		curr_path;
	int		ants_start;
	int		ants_end;

	graph->state = init_matrix(graph->nb_paths, graph->nb_nodes);
	ants_start = graph->nb_ants;
	ants_end = 0;
	curr_path = -1;
	while (++curr_path < graph->nb_paths)
		print_path_state(graph, curr_path, ants_start, ants_end);
	ft_printf("\n");
	while (ants_end < graph->nb_ants)
	{
		curr_path = 0;
		while (curr_path < graph->nb_paths)
		{
			update_path(graph, curr_path, &ants_start, &ants_end);
			print_path_state(graph, curr_path, ants_start, ants_end);
			curr_path++;
		}
		ft_printf("\n");
	}
	curr_path = graph->nb_paths;
	while (curr_path--)
		ft_memdel((void **)&(graph->state[curr_path]));
	ft_memdel((void **)&(graph->state));
}
