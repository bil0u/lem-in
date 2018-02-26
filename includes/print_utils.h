/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/16 12:28:08 by upopee            #+#    #+#             */
/*   Updated: 2018/02/26 16:15:54 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINT_UTILS_H
# define PRINT_UTILS_H

# define ERR_MSG "ERROR"
# define ERR_NOROOM_MSG "ERROR: no room defined"
# define ERR_ONEROOM_MSG "ERROR: only one room defined"
# define ERR_NOSTART_MSG "ERROR: no start defined"
# define ERR_NOEND_MSG "ERROR: no end defined"
# define ERR_SEQE_MSG "ERROR: start & end cannot be the same"
# define ERR_NOLINK_MSG "ERROR: no link defined"
# define ERR_NOPATH_MSG "ERROR: no path beetween start & end rooms"
# define ERR_LINE_MSG "ERROR on line {yellow}%d{eoc}: '{red}%s{eoc}'\n"

# define IGNORED_MSG "Ignored option: '%c'\n"

# define LKS_HEADER_MSG "> {yellow}%d {eoc}links:\n\n      "
# define LKS_FIRSTLINE_MSG "{yellow}%3.3s{eoc} "
# define LKS_NODENAME_MSG "{yellow}%5.5s{eoc} "
# define LKS_USED_MSG "{cyan}%3d{eoc} "
# define LKS_UNUSED_MSG "{blue}%3d{eoc} "
# define LKS_NOLINK_MSG "  0 "

# define PTH_HEADER_MSG "\n> {yellow}%d{eoc} paths:\n"
# define PTH_NO_MSG "(Path no. {yellow}%d{eoc})\t"
# define PTH_START_MSG "{cyan}%s{eoc}"
# define PTH_NODE_MSG " --> {green}%s{eoc}"
# define PTH_END_MSG " --> {magenta}%s{eoc}\n"

# define SLV_PRMPT_MSG "({blue}Round {cyan}%d{eoc})\tPath no. {yellow}%d{eoc}\t"
# define SLV_SNAME_MSG "{cyan}%s{eoc} "
# define SLV_SNBA_MSG "[{yellow}%d{eoc}] "
# define SLV_SNOA_MSG "[{red}0{eoc}] "
# define SLV_BUSY_MSG "--> ({green}%s{eoc} {blue}#%d{eoc}) "
# define SLV_FREE_MSG "--> ({red}%s{eoc}) "
# define SLV_ENBA_MSG "--> [{yellow}%d{eoc}] "
# define SLV_ENOA_MSG "--> [{red}0{eoc}] "
# define SLV_ENAME_MSG "{magenta}%s{eoc}\n"

void	print_links(t_lgraph *graph);
void	print_path_state(t_lgraph *graph, int *pos, int p_no, int round_no);
void	print_paths(t_lgraph *graph);
void	print_input(t_list *input);
void	print_error(t_list *input);

#endif
