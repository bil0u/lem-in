/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 03:33:19 by upopee            #+#    #+#             */
/*   Updated: 2018/02/27 02:29:49 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "libft.h"
#include "print_utils.h"

int		set_error(t_pdata *dat, int set_input_err, char *error)
{
	if (set_input_err == TRUE)
		BSET(dat->flags, INPUT_ERROR);
	if (error != NULL)
		dat->err_msg = error;
	return (FALSE);
}

int		cmp_name(t_room *room, t_pdata *data_ref)
{
	return (ft_strcmp(room->name, data_ref->to_save));
}

int		cmp_coord(t_room *room, t_pdata *data_ref)
{
	if (room->coord_x == data_ref->tmp_x && room->coord_y == data_ref->tmp_y)
		return (0);
	return (1);
}

void	apply_commands(t_pdata *dat)
{
	if (BIS_SET(dat->flags, START))
	{
		dat->start = dat->existing;
		BUNSET(dat->flags, START);
	}
	if (BIS_SET(dat->flags, END))
	{
		dat->end = dat->existing;
		BUNSET(dat->flags, END);
	}
}

int		get_distance(t_pdata *dat, t_lgraph *graph, int x, int y)
{
	int		i;
	int		name_len;
	char	*node_name;

	if (((i = -1) == -1) && (graph->nb_nodes == 0 || (x <= 0 || y <= 0)))
		return (set_error(dat, TRUE, ERR_NOLINKNAME_MSG));
	dat->tmp_x = -1;
	dat->tmp_y = -1;
	while (++i < graph->nb_nodes && (dat->tmp_x == -1 || dat->tmp_y == -1))
	{
		node_name = graph->nodes[i]->name;
		name_len = ft_strlen(node_name);
		if (name_len == x && ft_strncmp(node_name, dat->buff, x) == 0)
			dat->tmp_x = i;
		if (name_len == y && ft_strncmp(node_name, dat->buff + x + 1, y) == 0)
			dat->tmp_y = i;
	}
	if ((dat->tmp_dist = 1) == 1 && (dat->tmp_x == -1 || dat->tmp_y == -1))
		return (set_error(dat, TRUE, ERR_BADLINKNAME_MSG));
	if (dat->buff[x + y + 1] != '\0'
		&& (dat->tmp_dist = ft_atoi(dat->buff + x + y + 1)) < 1)
		return (set_error(dat, TRUE, ERR_BADLINKVAL_MSG));
	dat->tmp_dist > 1 ? BSET(dat->flags, CUSTOM_DIST) : (void)x;
	return (TRUE);
}
