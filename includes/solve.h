/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 19:42:29 by upopee            #+#    #+#             */
/*   Updated: 2018/02/13 00:31:23 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOLVE_H
# define SOLVE_H

void	pre_check(t_pdata *dat, t_lgraph *graph);
void	load_input(t_lgraph *graph);
void	save_path(t_lgraph *graph);
void	find_other_paths(t_lgraph *graph);
void	find_shortest_path(t_lgraph *graph);

#endif
