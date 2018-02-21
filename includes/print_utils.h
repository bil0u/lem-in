/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/16 12:28:08 by upopee            #+#    #+#             */
/*   Updated: 2018/02/21 19:07:05 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINT_UTILS_H
# define PRINT_UTILS_H

void	print_path_state(t_lgraph *graph, int *pos, int p_no);
void	print_paths(t_lgraph *graph);
void	print_input(t_list *input);
void	print_error(t_list *input);

#endif
