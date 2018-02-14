/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_utils.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 11:58:26 by upopee            #+#    #+#             */
/*   Updated: 2018/02/14 04:48:36 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_UTILS_H
# define STRUCT_UTILS_H

void	init_graph(t_pdata *dat, t_lgraph *graph);
void	del_graph(t_lgraph *graph);
int		**init_matrix(int nb_x, int nb_y);

#endif
