/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_lem_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 10:37:59 by upopee            #+#    #+#             */
/*   Updated: 2018/02/27 01:59:00 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
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

static void		errors_details(t_pdata *d, t_lgraph *g)
{
	if (BIS_SET(d->flags, PARSE_OK))
		ft_putendl(ERR_NOPATH_MSG);
	else
	{
		!BIS_SET(d->flags, EOL_REACHED) ? print_error(d) : (void)d;
		g->nb_nodes == 0 ? ft_putendl(ERR_NOROOM_MSG) : (void)d;
		g->nb_nodes == 1 ? ft_putendl(ERR_ONEROOM_MSG) : (void)d;
		d->start == NULL ? ft_putendl(ERR_NOSTART_MSG) : (void)d;
		d->end == NULL ? ft_putendl(ERR_NOEND_MSG) : (void)d;
		d->end && d->start == d->end ? ft_putendl(ERR_SEQE_MSG) : (void)d;
		g->nb_links == 0 ? ft_putendl(ERR_NOLINK_MSG) : (void)d;
	}
}

static int		end_error(t_pdata *dat, t_lgraph *graph)
{
	if (BIS_SET(dat->flags, PRINT_ERRORS))
		errors_details(dat, graph);
	else
		ft_putendl(ERR_MSG);
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
		i = (av[ac][0] == '-') ? 0 : -1;
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
			av[ac][i] == 'u' ? BSET(dat->flags, UNIQ_PATH) : err++;
			err == NB_OPTIONS ? ft_printf(IGNORED_MSG, av[ac][i]) : (void)err;
		}
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
	while (!BIS_SET(dat.flags, INPUT_ERROR) && !BIS_SET(dat.flags, EOL_REACHED))
		parse_input(&dat, &graph);
	if (pre_check(&dat, &graph) == ERROR)
		return (end_error(&dat, &graph));
	get_paths(&dat, &graph);
	if (!BIS_SET(graph.flags, PATH_FOUND))
		return (end_error(&dat, &graph));
	if (BIS_SET(graph.flags, PATH_FOUND) && !BIS_SET(dat.flags, NO_INPUT_PRINT))
		print_input(dat.input_tmp);
	if (BIS_SET(dat.flags, PRINT_LINKS))
		print_links(&graph);
	if (BIS_SET(dat.flags, PRINT_PATHS))
		print_paths(&graph);
	if (!BIS_SET(dat.flags, NO_SOLVE))
		cross_paths(&graph, &dat);
	del_graph(&graph);
	return (SUCCESS);
}
