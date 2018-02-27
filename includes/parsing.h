/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 11:58:26 by upopee            #+#    #+#             */
/*   Updated: 2018/02/27 00:47:53 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

int		set_error(t_pdata *dat, int set_input_err, char *error);
int		cmp_name(t_room *room, t_pdata *data_ref);
int		cmp_coord(t_room *room, t_pdata *data_ref);
void	apply_commands(t_pdata *dat);
void	parse_input(t_pdata *dat, t_lgraph *graph);
int		get_distance(t_pdata *dat, t_lgraph *graph, int len_a, int len_b);

#endif
