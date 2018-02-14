/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_lem_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 10:37:59 by upopee            #+#    #+#             */
/*   Updated: 2018/02/14 18:40:16 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "lem_in.h"
#include "parsing.h"
#include "struct_utils.h"
#include "pathfinding.h"

/*
** --------------------------------- DEBUG -------------------------------------
*/

void			print_nodes(t_lgraph *graph, t_pdata *dat)
{
	t_room	**curr;
	int		i;

	ft_printf("\n");
	ft_printf("{yellow}%d{eoc} nodes | start = {green}%s{eoc} | end = {blue}%s{eoc}\n", graph->nb_nodes, graph->nodes[0]->name, graph->nodes[graph->nb_nodes -1]->name);
	ft_printf("custom distances : {yellow}%s{eoc}\n\n-->   ", BIS_SET(dat->flags, CUSTOM_DIST) ? "YES" : "NO");
	i = 0;
	curr = graph->nodes;
	while (i < graph->nb_nodes)
	{
		ft_printf("[%d - '{magenta}%s{eoc}']   ", i, curr[i]->name);
		i++;
	}
	ft_putchar('\n');
	ft_putchar('\n');
}

void			print_links(t_lgraph *graph)
{
	int		i;
	int		j;
	int		cell;

	ft_printf("-- {yellow}%d{eoc} {red}LINKS{eoc} --\n", graph->nb_links);
	if (graph->links != NULL)
	{
		i = 0;
		while (i < graph->nb_nodes)
		{
			j = 0;
			while (j < graph->nb_nodes)
			{
				cell = graph->links[i][j];
				if (cell == 0)
					ft_printf("0 ");
				else if (cell == -1)
					ft_printf("{red}1{eoc} ", graph->links[i][j]);
				else
					ft_printf("{green}%d{eoc} ", graph->links[i][j]);
				j++;
			}
			ft_putchar('\n');
			i++;
		}
	}
	ft_putchar('\n');
}

void			print_path(t_lgraph *graph, int path_no)
{
	int		curr_node;
	int		i;

	if (path_no >= 0 && path_no < graph->nb_paths)
	{
		ft_printf("{green}Path #%d:{eoc}\n", path_no + 1);
		ft_printf("{yellow}%s{eoc}", graph->nodes[0]->name);
		i = 0;
		while ((curr_node = graph->paths[path_no][i]) != NONE)
		{
			ft_printf(" --> {yellow}%s{eoc}", graph->nodes[curr_node]->name);
			i++;
		}
		ft_putchar('\n');
	}
}

void			print_paths(t_lgraph *graph)
{
	int		i;

	i = 0;
	ft_printf("> {yellow}%d{eoc} paths:\n", graph->nb_paths);
	while (i < graph->nb_paths)
	{
		print_path(graph, i);
		i++;
	}
	ft_putchar('\n');
}

/*
** -----------------------------------------------------------------------------
*/

static void		get_ants(t_pdata *dat, t_lgraph *graph)
{
	get_next_line(STDIN_FILENO, &(dat->buff));
	if (dat->buff)
	{
		ft_putendl(dat->buff);
		if (ft_strisnumber(dat->buff, '\0'))
			graph->nb_ants = ft_atoi(dat->buff);
		ft_strdel(&(dat->buff));
	}
	if (graph->nb_ants < 1)
		BSET(dat->flags, INPUT_ERROR);
}

static void		init_main_data(t_pdata *dat, t_lgraph *graph)
{
	ft_memset(graph, 0, sizeof(*graph));
	ft_memset(dat, 0, sizeof(*dat));
	get_ants(dat, graph);
}

static void		exit_error(t_lgraph *graph)
{
	ft_putendl("ERROR");
	del_graph(graph);
	exit(ERROR);
}

int				main(void)
{
	t_lgraph	graph;
	t_pdata		dat;

	init_main_data(&dat, &graph);
	while (!BIS_SET(dat.flags, INPUT_ERROR))
		parse_input(&dat, &graph);
	pre_check(&dat, &graph);
	if (BIS_SET(dat.flags, DATA_ERROR))
		exit_error(&graph);

	print_nodes(&graph, &dat);
	print_links(&graph);

	get_paths(&graph);
	if (graph.nb_paths == 0)
		exit_error(&graph);

	print_paths(&graph);
	print_links(&graph);

	cross_paths(&graph);

	del_graph(&graph);
	return (SUCCESS);
}
