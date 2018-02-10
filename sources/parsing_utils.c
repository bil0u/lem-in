/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 03:33:19 by upopee            #+#    #+#             */
/*   Updated: 2018/02/10 23:45:21 by upopee           ###   ########.fr       */
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

void	apply_commands(t_pdata *dat, t_lgraph *graph)
{
	if (BIS_SET(dat->flags, START))
	{
		graph->start = dat->existing;
		BUNSET(dat->flags, START);
	}
	if (BIS_SET(dat->flags, END))
	{
		graph->end = dat->existing;
		BUNSET(dat->flags, END);
	}
}

int		get_distance(t_pdata *dat, t_lgraph *graph, int len_x, int len_y)
{
	t_list	*curr_node;
	t_room	*room;
	int		i;

	i = 0;
	dat->tmp_x = -1;
	dat->tmp_y = -1;
	curr_node = graph->nodes;
	while (curr_node != NULL && (dat->tmp_x == -1 || dat->tmp_y == -1))
	{
		room = (t_room *)curr_node->content;
		if (ft_strncmp(room->name, dat->buff, len_x) == 0)
			dat->tmp_x = i;
		if (ft_strncmp(room->name, dat->buff + len_x + 1, len_y) == 0)
			dat->tmp_y = i;
		curr_node = curr_node->next;
		i++;
	}
	if (dat->tmp_x != -1 && dat->tmp_y != -1)
	{
		len_x = ft_atoi(dat->buff + len_x + 1);
		dat->tmp_dist = len_x > 0 ? len_x : 1;
		return (TRUE);
	}
	return (FALSE);
}
