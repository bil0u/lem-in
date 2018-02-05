/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_utils.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 11:58:26 by upopee            #+#    #+#             */
/*   Updated: 2018/02/05 12:02:48 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_UTILS_H
# define STRUCT_UTILS_H

int		**init_matrix(int nb_lines);
void	del_matrix(int **tab, int nb_lines);
void	node_cleaner(void *content, size_t size);

#endif
