/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: pniezen <pniezen@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/12 13:52:41 by pniezen       #+#    #+#                 */
/*   Updated: 2022/11/12 13:54:50 by pniezen       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	env_len(t_env **env)
{
	t_env	*temp;
	int		count;

	temp = *env;
	count = 0;
	while (temp)
	{
		count++;
		temp = temp->next;
	}
	return (count);
}

static bool	ft_cmpswap(const char *s1, const char *s2)
{
	unsigned long long	i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] > s2[i])
			return (true);
		else if (s1[i] < s2[i])
			return (false);
		i++;
	}
	if (s1[i] > s2[i])
		return (true);
	else
		return (false);
}

static t_env	*swap(t_env *p1, t_env *p2)
{
	t_env	*temp;

	temp = p2->next;
	p2->next = p1;
	p1->next = temp;
	return (p2);
}

void	sort_env_list(t_env **begin_list)
{
	t_env	**head;
	t_env	*p1;
	t_env	*p2;
	int		i;
	int		j;
	int		swapped;

	i = 0;
	while (i < env_len(begin_list))
	{
		head = begin_list;
		i++;
		j = 0;
		swapped = 0;
		while (j < (env_len(begin_list) - i) - 1)
		{
			j++;
			p1 = *head;
			p2 = p1->next;
			if (ft_cmpswap(p1->var_name, p2->var_name))
			{
				*head = swap(p1, p2);
				swapped = 1;
			}
			head = &(*head)->next;
		}
		if (!swapped)
			break ;
	}
}
