/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 11:58:26 by upopee            #+#    #+#             */
/*   Updated: 2018/02/08 05:15:57 by Bilou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

int		atoi_chr(char **str);
int		cmp_name(t_room *room, t_pdata *data_ref);
int		cmp_coord(t_room *room, t_pdata *data_ref);
void	apply_commands(t_pdata *dat, t_lgraph *graph);
void	get_input(t_pdata *dat, t_lenv *env);

#endif