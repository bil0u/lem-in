/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_lem_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 10:37:59 by upopee            #+#    #+#             */
/*   Updated: 2018/02/16 16:50:21 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include "lem_in.h"
#include "parsing.h"
#include "struct_utils.h"
#include "pathfinding.h"
#include "print_utils.h"

static void		get_ants(t_pdata *dat, t_lgraph *graph)
{
	int		neg;
	int		i;

	get_next_line(STDIN_FILENO, &(dat->buff));
	if (dat->buff)
	{
		ft_lstappend(&(dat->input_tmp), ft_lstnew_nm(dat->buff, 0));
		if (ft_strisnumber(dat->buff, '\0'))
		{
			neg = ft_strchr(dat->buff, '-') ? -1 : 1;
			i = ft_isdigit(dat->buff[0]) ? 0 : 1;
			while (dat->buff[i] == '0')
				i++;
			if (ft_atol(dat->buff + i) <= INT_MAX)
				graph->nb_ants = ft_atoi(dat->buff + i) * neg;
		}
		dat->buff = NULL;
	}
	if (graph->nb_ants < 1)
		BSET(dat->flags, INPUT_ERROR);
}

static void		init_main_data(t_pdata *dat, t_lgraph *graph)
{
	ft_memset(graph, 0, sizeof(*graph));
	ft_memset(dat, 0, sizeof(*dat));
}

static void		exit_error(t_pdata *dat, t_lgraph *graph)
{
	if (BIS_SET(dat->flags, PRINT_IF_ERROR))
	{
		if (!BIS_SET(dat->flags, PARSING_DONE))
			print_error(dat->input_tmp);
		else if (graph->nb_nodes == 0)
			ft_putendl("ERROR: no room defined");
		else if (graph->nb_nodes == 1)
			ft_putendl("ERROR: only one room defined");
		else if (dat->start == NULL)
			ft_putendl("ERROR: no start defined");
		else if (dat->end == NULL)
			ft_putendl("ERROR: no end defined");
		else if (graph->nb_paths == 0)
			ft_putendl("ERROR: no path found");
	}
	else
		ft_putendl("ERROR");
	while (get_next_line(STDIN_FILENO, &(dat->buff)) > 0)
		ft_strdel(&(dat->buff));
	ft_lstdel(&(dat->input_tmp), &ft_delcontent);
	if (BIS_SET(graph->flags, ALLOCATED_MEMORY))
		del_graph(graph);
	exit(ERROR);
}

static void		check_options(int argc, char **argv, t_pdata *dat)
{
	while (argc-- > 1)
	{
		if (argv[argc][0] == '-' && argv[argc][1] == 'o')
			BSET(dat->flags, ORIENTED_GRAPH);
		else if (argv[argc][0] == '-' && argv[argc][1] == 'p')
			BSET(dat->flags, PRINT_PATHS);
		else if (argv[argc][0] == '-' && argv[argc][1] == 'd')
			BSET(dat->flags, PRINT_IF_ERROR);
		else
		{
			ft_printf("Unknown option: '%s'\n", argv[argc]);
			exit(ERROR);
		}
	}
}

int				main(int argc, char **argv)
{
	t_lgraph	graph;
	t_pdata		dat;

	init_main_data(&dat, &graph);
	check_options(argc, argv, &dat);
	get_ants(&dat, &graph);
	while (!BIS_SET(dat.flags, INPUT_ERROR))
		parse_input(&dat, &graph);
	if (pre_check(&dat, &graph) == ERROR)
		exit_error(&dat, &graph);
	get_paths(&graph);
	if (BIS_SET(graph.flags, PATH_FOUND))
		print_input(dat.input_tmp);
	ft_lstdel(&(dat.input_tmp), &ft_delcontent);
	if (BIS_SET(dat.flags, PRINT_PATHS))
		print_paths(&graph);
	if (graph.nb_paths == 0)
		exit_error(&dat, &graph);
	cross_paths(&graph);
	del_graph(&graph);
	return (SUCCESS);
}
