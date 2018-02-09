/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_core.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 22:50:30 by upopee            #+#    #+#             */
/*   Updated: 2018/02/09 14:50:54 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "lem_in.h"
#include "parsing.h"
#include "struct_utils.h"

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

static void		get_linkdata(t_pdata *dat, t_lgraph *graph)
{
	char	*separator;
	int		len;

	if ((separator = ft_strchr(dat->buff, '-')) != NULL)
	{
		len = separator - dat->buff;
		if (get_index(dat, graph, len, separator) == TRUE)
			graph->links[dat->tmp_x][dat->tmp_y] = 1;
		else
			BSET(dat->flags, DATA_ERROR);
	}
	else
		BSET(dat->flags, DATA_ERROR);
}

void			get_input(t_pdata *dat, t_lenv *env)
{
	ft_putendl(dat->buff);
	dat->to_save = NULL;
	if (dat->buff[0] != '#' && !BIS_SET(dat->flags, ROOM_DONE) && !is_room(dat))
	{
		BSET(dat->flags, ROOM_DONE);
		env->graph.links = init_matrix(env->graph.nb_nodes);
		ft_strdel(&(dat->to_save));
	}
	if (dat->buff[0] == '#')
		get_hashdata(dat);
	else if (!BIS_SET(dat->flags, ROOM_DONE))
	{
		get_roomdata(dat, &(env->graph));
		apply_commands(dat, &(env->graph));
	}
	else if (ft_strchr(dat->buff, '-'))
		get_linkdata(dat, &(env->graph));
	else
		BSET(dat->flags, DATA_ERROR);
	ft_strdel(&(dat->buff));
}
