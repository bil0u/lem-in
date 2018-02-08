/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_core.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 22:50:30 by upopee            #+#    #+#             */
/*   Updated: 2018/02/08 06:21:39 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "lem_in.h"
#include "parsing.h"

static int		is_room(t_pdata *dat)
{
	char	*tmp;
	int		name_len;

	if ((tmp = ft_strchr(dat->buff, ' ')) == NULL)
		return (FALSE);
	name_len = tmp - dat->buff;
	if (ft_strnstr(dat->buff, "-", name_len) || dat->buff[0] == 'L')
		return (FALSE);
	dat->tmp_x = atoi_chr(&tmp);
	if (tmp[0] != ' ')
	{
		dat->tmp_x = 0;
		return (FALSE);
	}
	dat->tmp_y = atoi_chr(&tmp);
	if (tmp[0] != '\0')
	{
		dat->tmp_y = 0;
		return (FALSE);
	}
	dat->to_save = ft_strndup(dat->buff, name_len);
	return (TRUE);
}

static void		get_hashdata(t_pdata *dat)
{
	if (ft_strcmp(dat->buff, "##start") == 0)
		BSET(dat->flags, START);
	else if (ft_strcmp(dat->buff, "##end") == 0)
		BSET(dat->flags, END);
}

static void		get_roomdata(t_pdata *dat, t_lgraph *graph)
{
	t_room	new;

	if ((dat->duplicate = ft_lstfind(graph->nodes, dat, &cmp_name)))
	{
		dat->existing = (t_room *)dat->duplicate->content;
		dat->existing->coord_x = dat->tmp_x;
		dat->existing->coord_y = dat->tmp_y;
		ft_strdel(&(dat->to_save));
	}
	else if ((dat->duplicate = ft_lstfind(graph->nodes, dat, &cmp_coord)))
	{
		dat->existing = (t_room *)dat->duplicate->content;
		ft_strdel(&(dat->existing->name));
		dat->existing->name = dat->to_save;
	}
	else
	{
		new.name = dat->to_save;
		new.coord_x = dat->tmp_x;
		new.coord_y = dat->tmp_y;
		new.busy = FALSE;
		ft_lstadd(&(graph->nodes), ft_lstnew(&new, sizeof(new)));
		graph->nb_nodes++;
		dat->existing = (t_room *)graph->nodes->content;
	}
}

static void		get_linkdata()
{

}

void			get_input(t_pdata *dat, t_lenv *env)
{
	ft_putendl(dat->buff);
	if (dat->buff[0] != '#' && !BIS_SET(dat->flags, ROOM_DONE) && !is_room(dat))
	{
		BSET(dat->flags, ROOM_DONE);
		env->graph.links = init_matrix(env->graph.nb_nodes);
	}
	if (dat->buff[0] == '#')
		get_hashdata(dat);
	else if (!BIS_SET(dat->flags, ROOM_DONE))
	{
		get_roomdata(dat, &(env->graph));
		apply_commands(dat, &(env->graph));
	}
	else if (ft_strchr(dat->buff, '-'))
		get_linkdata();
	else
		BSET(dat->flags, DATA_ERROR);
	ft_strdel(&(dat->buff));
}
