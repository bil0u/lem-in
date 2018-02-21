/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 17:36:05 by upopee            #+#    #+#             */
/*   Updated: 2018/02/16 16:46:41 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft.h"

# define ERROR -1
# define SUCCESS 0
# define NONE -1

typedef struct	s_room
{
	char		*name;
	int			coord_x;
	int			coord_y;
}				t_room;

# define NB_PATHS_MAX 100
# define END_FOUND (1)
# define ALLOCATED_MEMORY (1 << 1)
# define PATH_FOUND (1 << 2)

typedef struct	s_lgraph
{
	t_room		**nodes;
	int			**links;
	int			**paths;
	int			**state;
	int			*paths_len;
	int			*ant_no;
	int			*explored;
	int			*distance;
	int			*previous;
	int			ants_start;
	int			ants_end;
	int			nb_nodes;
	int			nb_links;
	int			nb_ants;
	int			nb_loops;
	int			nb_paths;
	int			curr_node;
	int			flags;
}				t_lgraph;

# define START (1)
# define END (1 << 1)
# define INPUT_ERROR (1 << 2)
# define ROOM_DONE (1 << 3)
# define CUSTOM_DIST (1 << 4)
# define ORIENTED_GRAPH (1 << 5)
# define PRINT_PATHS (1 << 6)
# define PRINT_IF_ERROR (1 << 7)
# define PARSING_DONE (1 << 8)

typedef struct	s_pdata
{
	int			tmp_x;
	int			tmp_y;
	int			tmp_dist;
	int			flags;
	char		*buff;
	char		*to_save;
	t_list		*nodes_tmp;
	t_list		*input_tmp;
	t_room		*start;
	t_room		*end;
	t_room		*existing;
	t_list		*duplicate;
}				t_pdata;

#endif
