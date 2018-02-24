/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_lem_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 10:37:59 by upopee            #+#    #+#             */
/*   Updated: 2018/02/24 18:17:23 by upopee           ###   ########.fr       */
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

static void		errors_details(t_pdata *dat, t_lgraph *graph, int step)
{
	if (graph->nb_nodes == 0)
		ft_putendl("ERROR: no room defined");
	else if (graph->nb_nodes == 1)
		ft_putendl("ERROR: only one room defined");
	else if (dat->start == NULL)
		ft_putendl("ERROR: no start defined");
	else if (dat->end == NULL)
		ft_putendl("ERROR: no end defined");
	else if (dat->end && dat->start == dat->end)
		ft_putendl("ERROR: start & end cannot be the same");
	else if (!BIS_SET(dat->flags, PARSE_OK) && BIS_SET(dat->flags, INPUT_ERROR))
		print_error(dat->input_tmp);
	else if (BIS_SET(dat->flags, PARSE_OK) && graph->nb_links == 0)
		ft_putendl("ERROR: no links defined");
	else if (step == 2)
		ft_putendl("ERROR: no path found");
}

static int		end_error(t_pdata *dat, t_lgraph *graph, int step)
{
	if (BIS_SET(dat->flags, PRINT_ERRORS))
		errors_details(dat, graph, step);
	else
		ft_putendl("ERROR");
	while (get_next_line(STDIN_FILENO, &(dat->buff)) > 0)
		ft_strdel(&(dat->buff));
	ft_lstdel(&(dat->input_tmp), &ft_delcontent);
	if (BIS_SET(graph->flags, ALLOCATED_MEMORY))
		del_graph(graph);
	return (ERROR);
}

static void		check_options(int ac, char **av, t_pdata *dat)
{
	int		i;
	int		err;

	while (ac-- > 1)
	{
		if (av[ac][0] == '-')
		{
			i = 0;
			while (av[ac][++i] && (err = 0) == 0)
			{
				av[ac][i] == 'o' ? BSET(dat->flags, ORIENTED_GRAPH): err++;
				av[ac][i] == 'l' ? BSET(dat->flags, PRINT_LINKS) : err++;
				av[ac][i] == 'p' ? BSET(dat->flags, PRINT_PATHS) : err++;
				av[ac][i] == 'd' ? BSET(dat->flags, PRINT_ERRORS) : err++;
				av[ac][i] == 'v' ? BSET(dat->flags, VERBOSE) : err++;
				av[ac][i] == 'v' ? BSET(dat->flags, PRINT_PATHS) : (void)err;
				av[ac][i] == 'i' ? BSET(dat->flags, NO_INPUT_PRINT) : err++;
				av[ac][i] == 's' ? BSET(dat->flags, NO_SOLVE) : err++;
				if (err == NB_OPTIONS)
					ft_printf("Ignored option: '%c'\n", av[ac][i]);
			}
		}
		else
			ft_printf("Ignored option: '%s'\n", av[ac]);
	}
}

int				main(int argc, char **argv)
{
	t_lgraph	graph;
	t_pdata		dat;

	ft_bzero(&graph, sizeof(graph));
	ft_bzero(&dat, sizeof(dat));
	check_options(argc, argv, &dat);
	get_ants(&dat, &graph);
	while (!BIS_SET(dat.flags, INPUT_ERROR) && !BIS_SET(dat.flags, PARSE_OK))
		parse_input(&dat, &graph);
	if (pre_check(&dat, &graph) == ERROR)
		return (end_error(&dat, &graph, 1));
	get_paths(&graph);
	if (BIS_SET(graph.flags, PATH_FOUND) && !BIS_SET(dat.flags, NO_INPUT_PRINT))
		print_input(dat.input_tmp);
	if (!BIS_SET(graph.flags, PATH_FOUND))
		return (end_error(&dat, &graph, 2));
	if (BIS_SET(dat.flags, PRINT_LINKS))
		print_links(&graph);
	if (BIS_SET(dat.flags, PRINT_PATHS))
		print_paths(&graph);
	if (!BIS_SET(dat.flags, NO_SOLVE))
		cross_paths(&graph, &dat);
	del_graph(&graph);
	return (SUCCESS);
}
