/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 03:33:19 by upopee            #+#    #+#             */
/*   Updated: 2018/02/15 18:26:07 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "libft.h"

int		atoi_chr(char **str)
{
	int			sign;
	int			res;

	res = 0;
	while (ft_iswhitespace((int)**str))
		(*str)++;
	sign = (**str == '-' ? -1 : 1);
	if (**str == '-' || **str == '+')
		(*str)++;
	while (ft_isdigit((int)**str))
	{
		res = res * 10 + (int)**str - '0';
		(*str)++;
	}
	return (res * sign);
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

	if (x > 0 && y > 0)
	{
		i = 0;
		dat->tmp_x = -1;
		dat->tmp_y = -1;
		while (i < graph->nb_nodes && (dat->tmp_x == -1 || dat->tmp_y == -1))
		{
			if (ft_strncmp(graph->nodes[i]->name, dat->buff, x) == 0)
				dat->tmp_x = i;
			if (ft_strncmp(graph->nodes[i]->name, dat->buff + x + 1, y) == 0)
				dat->tmp_y = i;
			i++;
		}
		if (dat->tmp_x != -1 && dat->tmp_y != -1)
		{
			x = ft_atoi(dat->buff + x + y + 1);
			dat->tmp_dist = x > 0 ? x : 1;
			dat->tmp_dist > 1 ? BSET(dat->flags, CUSTOM_DIST) : (void)x;
			return (TRUE);
		}
	}
	return (FALSE);
}
