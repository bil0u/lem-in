/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinding.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 19:42:29 by upopee            #+#    #+#             */
/*   Updated: 2018/02/21 18:57:01 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PATHFINDING_H
# define PATHFINDING_H

int		pre_check(t_pdata *dat, t_lgraph *graph);
void	load_input(t_lgraph *graph);
void	save_path(t_lgraph *graph, int path_len);
int		last_path_len(t_lgraph *graph);
void	get_paths(t_lgraph *graph);
void	cross_paths(t_lgraph *graph, t_pdata *dat);

#endif
