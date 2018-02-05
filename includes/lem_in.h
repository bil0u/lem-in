/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 17:36:05 by upopee            #+#    #+#             */
/*   Updated: 2018/02/05 11:55:17 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft.h"

# define ERROR -1

typedef struct		s_room
{
	char	*name;
	int		coord_x;
	int		coord_y;
	char	busy;
}					t_room;

typedef struct		s_lgraph
{
	t_list	*nodes;
	int		nb_nodes;
	int		**links;
}					t_lgraph;

#endif
