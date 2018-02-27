/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_core.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 22:50:30 by upopee            #+#    #+#             */
/*   Updated: 2018/02/27 02:23:07 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "lem_in.h"
#include "parsing.h"
#include "struct_utils.h"
#include "print_utils.h"

static int		is_room(t_pdata *dat)
{
	int		name_len;
	char	*token;
	char	*tmp;

	if (dat->buff[0] == 'L')
		return (set_error(dat, FALSE, ERR_LNAME_MSG));
	if ((token = ft_nextws(dat->buff, FALSE)) == NULL)
		return (set_error(dat, FALSE, ERR_NOCOORD_MSG));
	name_len = token - dat->buff;
	if (ft_strnchr(dat->buff, '-', name_len))
		return (set_error(dat, FALSE, ERR_SEPNAME_MSG));
	if (((tmp = ft_strchr(token, '-')) || (tmp = ft_strchr(token, '+')))
		&& ft_isdigit(tmp[1]) == FALSE)
		return (set_error(dat, FALSE, ERR_BADCOORD_MSG));
	dat->tmp_x = ft_atoi_chr(&token);
	if (!ft_iswhitespace(token[0]))
		return (set_error(dat, FALSE, ERR_ONECOORD_MSG));
	if (((tmp = ft_strchr(token, '-')) || (tmp = ft_strchr(token, '+')))
		&& ft_isdigit(tmp[1]) == FALSE)
		return (set_error(dat, FALSE, ERR_BADCOORD_MSG));
	dat->tmp_y = ft_atoi_chr(&token);
	if (token[0] != '\0')
		return (set_error(dat, FALSE, ERR_OVERCOORD_MSG));
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

	if ((dat->duplicate = ft_lstfind(dat->nodes_tmp, dat, &cmp_name)))
	{
		dat->existing = (t_room *)dat->duplicate->content;
		dat->existing->coord_x = dat->tmp_x;
		dat->existing->coord_y = dat->tmp_y;
		ft_strdel(&(dat->to_save));
	}
	else if ((dat->duplicate = ft_lstfind(dat->nodes_tmp, dat, &cmp_coord)))
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
		ft_lstadd(&(dat->nodes_tmp), ft_lstnew(&new, sizeof(new)));
		graph->nb_nodes++;
		dat->existing = (t_room *)dat->nodes_tmp->content;
	}
	apply_commands(dat);
}

static void		get_linkdata(t_pdata *dat, t_lgraph *graph, char *sep)
{
	int		*i;
	int		*j;
	int		len_x;
	int		len_y;

	i = &(dat->tmp_x);
	j = &(dat->tmp_y);
	if (ft_strchr(sep + 1, '-') == NULL)
	{
		len_x = sep - dat->buff;
		dat->to_save = ft_nextws(sep, TRUE);
		len_y = dat->to_save ? dat->to_save - (sep + 1) : ft_strlen(sep + 1);
		if (get_distance(dat, graph, len_x, len_y) == TRUE)
		{
			graph->nb_links += (*i == *j) ? 0 : 1;
			graph->links[*i][*j] = (*i == *j) ? 0 : dat->tmp_dist;
			if (!BIS_SET(dat->flags, ORIENTED_GRAPH))
				graph->links[*j][*i] = (*i == *j) ? 0 : dat->tmp_dist;
		}
	}
	else
		set_error(dat, TRUE, ERR_MULTSEP_MSG);
}

void			parse_input(t_pdata *d, t_lgraph *g)
{
	if (get_next_line(STDIN_FILENO, &(d->buff)) > 0)
	{
		ft_lstappend(&(d->input_tmp), ft_lstnew_nm(d->buff, 0));
		d->to_save = NULL;
		if (d->buff[0] != '#' && !BIS_SET(d->flags, ROOM_DONE) && !is_room(d))
		{
			BSET(d->flags, ROOM_DONE);
			ft_strdel(&(d->to_save));
			g->nb_nodes > 0 ? init_graph(d, g) : (void)d;
		}
		if (d->buff[0] == '#')
			get_hashdata(d);
		else if (!BIS_SET(d->flags, ROOM_DONE))
			get_roomdata(d, g);
		else if (ft_strchr(d->buff, '-'))
			get_linkdata(d, g, ft_strchr(d->buff, '-'));
		else
			set_error(d, TRUE, NULL);
		d->buff = NULL;
	}
	else
		BSET(d->flags, EOL_REACHED);
}
