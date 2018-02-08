/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_lem_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 10:37:59 by upopee            #+#    #+#             */
/*   Updated: 2018/02/08 21:31:48 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "lem_in.h"
#include "parsing.h"
#include "struct_utils.h"

/*
** --------------------------------- DEBUG -------------------------------------
*/

void	print_graph(t_lgraph *graph)
{
	t_list	*tmp;
	t_room	*curr;
	int		i;
	int		j;

	ft_printf("---- {red}GRAPH{eoc} ----\n");
	ft_printf("{yellow}%d{eoc} nodes | start = {green}%p{eoc} | end = {blue}%p{eoc}\n", graph->nb_nodes, graph->start, graph->end);
	tmp = graph->nodes;
	ft_printf("+->  ");
	i = 0;
	while (tmp != NULL)
	{
		curr = (t_room *)tmp->content;
		ft_printf("{[%d]'{magenta}%s{eoc}' ({cyan}%d{eoc},{cyan}%d{eoc})}  -->  ", i, curr->name, curr->coord_x, curr->coord_y);
		tmp = tmp->next;
		i++;
	}
	ft_printf("{red}NULL{eoc}\n");
	if (graph->links != NULL)
	{
		i = 0;
		while (i < graph->nb_nodes)
		{
			j = 0;
			while (j < graph->nb_nodes)
			{
				ft_printf("%d ", graph->links[i][j]);
				j++;
			}
			ft_putchar('\n');
			i++;
		}
	}
	ft_printf("---------------\n");
}

/*
** -----------------------------------------------------------------------------
*/

static void		init_main_data(t_lenv *env, t_pdata *dat)
{
	ft_memset(env, 0, sizeof(*env));
	ft_memset(dat, 0, sizeof(*dat));
}

static void		get_ants(t_pdata *dat, t_lenv *env)
{
	get_next_line(STDIN_FILENO, &(dat->buff));
	if (dat->buff)
	{
		ft_putendl(dat->buff);
		if (ft_strisnumber(dat->buff, '\0'))
			env->ants = ft_atoi(dat->buff);
		ft_strdel(&(dat->buff));
	}
	if (env->ants < 1)
		BSET(dat->flags, DATA_ERROR);
}

int				main(void)
{
	t_lenv	env;
	t_pdata	dat;

	init_main_data(&env, &dat);
	get_ants(&dat, &env);
	while (!BIS_SET(dat.flags, DATA_ERROR))
	{
		get_next_line(STDIN_FILENO, &(dat.buff));
		if (dat.buff)
			get_input(&dat, &env);
		else
			BSET(dat.flags, DATA_ERROR);
	}
	print_graph(&(env.graph));
	env_cleaner(&env);
	return (SUCCESS);
}
