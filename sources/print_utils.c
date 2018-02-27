/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/16 12:14:27 by upopee            #+#    #+#             */
/*   Updated: 2018/02/27 01:14:39 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "print_utils.h"

void	print_links(t_lgraph *g)
{
	int		i;
	int		j;

	ft_printf(LKS_HEADER_MSG, g->nb_links);
	i = 0;
	while (i < g->nb_nodes)
		ft_printf(LKS_FIRSTLINE_MSG, g->nodes[i++]->name);
	ft_putchar('\n');
	i = -1;
	while (++i < g->nb_nodes)
	{
		ft_printf(LKS_NODENAME_MSG,g->nodes[i]->name);
		j = -1;
		while (++j < g->nb_nodes)
		{
			if (g->links[i][j] == 0)
				ft_printf(LKS_NOLINK_MSG);
			else if (g->links[i][j] < 0)
				ft_printf(LKS_USED_MSG, -g->links[i][j]);
			else
				ft_printf(LKS_UNUSED_MSG, g->links[i][j]);
		}
		ft_putchar('\n');
	}
	ft_putchar('\n');
}

void	print_path_state(t_lgraph *g, int *p, int p_no, int round_no)
{
	int		i;
	int		p_len;
	int		*busy;

	busy = g->state[p_no];
	p_len = g->paths_len[p_no];
	ft_printf(SLV_PRMPT_MSG, round_no, (p_no + 1));
	ft_printf(SLV_SNAME_MSG, g->nodes[0]->name);
	g->ants_start ? ft_printf(SLV_SNBA_MSG, g->ants_start)
					: ft_printf(SLV_SNOA_MSG);
	i = -1;
	while (++i < p_len - 1)
	{
		if (busy[p[i]])
			ft_printf(SLV_BUSY_MSG, g->nodes[p[i]]->name, g->ant_no[p[i]]);
		else
			ft_printf(SLV_FREE_MSG, g->nodes[p[i]]->name);
	}
	g->ants_end ? ft_printf(SLV_ENBA_MSG, g->ants_end)
				: ft_printf(SLV_ENOA_MSG);
	ft_printf(SLV_ENAME_MSG, g->nodes[p[i]]->name);
}

void	print_paths(t_lgraph *g)
{
	int		curr_no;
	int		path_no;
	int		i;

	ft_printf(PTH_HEADER_MSG, g->nb_paths);
	path_no = 0;
	while (path_no < g->nb_paths)
	{
		ft_printf(PTH_NO_MSG, path_no + 1);
		ft_printf(PTH_START_MSG, g->nodes[0]->name);
		i = 0;
		while (i < g->paths_len[path_no] - 1)
		{
			curr_no = g->paths[path_no][i];
			ft_printf(PTH_NODE_MSG, g->nodes[curr_no]->name);
			i++;
		}
		curr_no = g->paths[path_no][i];
		ft_printf(PTH_END_MSG, g->nodes[curr_no]->name);
		path_no++;
	}
}

void	print_input(t_list *input)
{
	t_list	*curr;

	curr = input;
	while (curr != NULL)
	{
		ft_putendl((char *)curr->content);
		curr = curr->next;
	}
	ft_lstdel(&input, &ft_delcontent);
}

void	print_error(t_pdata *dat)
{
	int		line;
	t_list	*curr;
	char	*err;

	curr = dat->input_tmp;
	line = 1;
	while (curr->next != NULL)
	{
		curr = curr->next;
		line++;
	}
	if ((err = (char *)curr->content) != NULL)
		ft_printf(ERR_LINE_MSG, line, err);
	if (dat->err_msg != NULL)
		ft_printf(" --> %s\n", dat->err_msg);
	else
		ft_putchar('\n');
}
