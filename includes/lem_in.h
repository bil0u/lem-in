/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 17:36:05 by upopee            #+#    #+#             */
/*   Updated: 2018/02/08 06:20:46 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft.h"

# define ERROR -1
# define SUCCESS 0

# define START (1)
# define END (1 << 1)
# define DATA_ERROR (1 << 2)
# define ROOM_DONE (1 << 3)

typedef struct	s_room
{
	char		*name;
	int			coord_x;
	int			coord_y;
	char		busy;
}				t_room;

typedef struct	s_lgraph
{
	t_list		*nodes;
	int			nb_nodes;
	int			**links;
	t_room		*start;
	t_room		*end;
}				t_lgraph;

typedef struct	s_lenv
{
	t_lgraph	graph;
	int			ants;
}				t_lenv;

typedef struct	s_pdata
{
	int			tmp_x;
	int			tmp_y;
	char		flags;
	char		*buff;
	char		*to_save;
	t_room		*existing;
	t_list		*duplicate;
}				t_pdata;

#endif
