/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/16 12:14:27 by upopee            #+#    #+#             */
/*   Updated: 2018/02/16 16:48:46 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	print_paths(t_lgraph *graph)
{
	int		curr_no;
	int		path_no;
	int		i;

	ft_printf("\n> {yellow}%d{eoc} paths:\n", graph->nb_paths);
	path_no = 0;
	while (path_no < graph->nb_paths)
	{
		ft_printf("{green}Path #%d:{eoc}\n", path_no + 1);
		ft_printf("{cyan}%s{eoc}", graph->nodes[0]->name);
		i = 0;
		while (i < graph->paths_len[path_no] - 1)
		{
			curr_no = graph->paths[path_no][i];
			ft_printf(" --> {yellow}%s{eoc}", graph->nodes[curr_no]->name);
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
}

void	print_error(t_list *input)
{
	int		line;
	t_list	*curr;
	char	*err;

	curr = input;
	err = NULL;
	line = 0;
	while (curr != NULL)
	{
		err = (char *)curr->content;
		curr = curr->next;
		line++;
	}
	if (err)
		ft_printf("ERROR on line {yellow}%d{eoc}: '{red}%s{eoc}'\n", line, err);
}
