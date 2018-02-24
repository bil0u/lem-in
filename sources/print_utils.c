/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/16 12:14:27 by upopee            #+#    #+#             */
/*   Updated: 2018/02/24 16:42:08 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	print_links(t_lgraph *graph)
{
	int		i;
	int		j;

	ft_printf("> {yellow}%d {eoc}links:\n\n      ", graph->nb_links);
	i = 0;
	while (i < graph->nb_nodes)
		ft_printf("{yellow}%3.3s{eoc} ",graph->nodes[i++]->name);
	ft_putchar('\n');
	i = -1;
	while (++i < graph->nb_nodes)
	{
		ft_printf("{yellow}%5.5s{eoc} ",graph->nodes[i]->name);
		j = -1;
		while (++j < graph->nb_nodes)
		{
			if (graph->links[i][j] == 0)
				ft_printf("  0 ");
			else if (graph->links[i][j] < 0)
				ft_printf("{cyan}%3d{eoc} ", -graph->links[i][j]);
			else
				ft_printf("{blue}%3d{eoc} ", graph->links[i][j]);
		}
		ft_putchar('\n');
	}
	ft_putchar('\n');
}

void	print_path_state(t_lgraph *graph, int *path, int p_no, int round_no)
{
	int		i;
	int		p_len;
	int		*busy;

	busy = graph->state[p_no];
	p_len = graph->paths_len[p_no];
	ft_printf("({blue}Round {cyan}%d{eoc})\tPath no. {yellow}%d{eoc}\t",
		round_no, (p_no + 1));
	ft_printf("{cyan}%s{eoc} [", graph->nodes[0]->name);
	graph->ants_start ? ft_printf("{yellow}%d{eoc}] ", graph->ants_start)
		: ft_printf("{red}%d{eoc}] ", graph->ants_start);
	i = -1;
	while (++i < p_len - 1)
	{
		ft_printf("--> (");
		busy[path[i]] ? ft_printf("{green}") : ft_printf("{red}");
		ft_printf("%s{eoc}", graph->nodes[path[i]]->name);
		if (busy[path[i]])
			ft_printf(" {blue}#%d{eoc}", graph->ant_no[path[i]]);
		ft_printf(") ");
	}
	ft_printf("--> [");
	graph->ants_end ? ft_printf("{yellow}%d{eoc}] ", graph->ants_end)
		: ft_printf("{red}%d{eoc}] ", graph->ants_end);
	ft_printf("{magenta}%s{eoc}\n", graph->nodes[path[i]]->name);
}

void	print_paths(t_lgraph *graph)
{
	int		curr_no;
	int		path_no;
	int		i;

	ft_printf("\n> {yellow}%d{eoc} paths:\n", graph->nb_paths);
	path_no = 0;
	while (path_no < graph->nb_paths)
	{
		ft_printf("{yellow}Path #%d:{eoc}\n", path_no + 1);
		ft_printf("{cyan}%s{eoc}", graph->nodes[0]->name);
		i = 0;
		while (i < graph->paths_len[path_no] - 1)
		{
			curr_no = graph->paths[path_no][i];
			ft_printf(" --> {green}%s{eoc}", graph->nodes[curr_no]->name);
			i++;
		}
		curr_no = graph->paths[path_no][i];
		ft_printf(" --> {magenta}%s{eoc}", graph->nodes[curr_no]->name);
		ft_putchar('\n');
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

void	print_error(t_list *input)
{
	int		line;
	t_list	*curr;
	char	*err;

	curr = input;
	line = 1;
	while (curr->next != NULL)
	{
		curr = curr->next;
		line++;
	}
	if ((err = (char *)curr->content) != NULL)
		ft_printf("ERROR on line {yellow}%d{eoc}: '{red}%s{eoc}'\n", line, err);
}
