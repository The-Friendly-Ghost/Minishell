/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export_print.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: pniezen <pniezen@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/13 12:04:07 by pniezen       #+#    #+#                 */
/*   Updated: 2022/11/21 09:18:01 by pniezen       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	env_array_size(char **env_array)
{
	int	i;

	i = 0;
	while (env_array[i])
		i++;
	return (i);
}

static void	swap(char **arr, int str1, int str2)
{
	char	*temp;

	temp = arr[str1];
	arr[str1] = arr[str2];
	arr[str2] = temp;
}

void	sort_env_array(char **env_array, int array_size)
{
	int		i;
	int		j;

	while (array_size-- >= 0)
	{
		i = 0;
		while (env_array[i] && env_array[i + 1])
		{
			j = 0;
			while (env_array[i][j] && env_array[i + 1][j])
			{
				if (env_array[i][j] == '=' || env_array[i + 1][j] == '='
					|| env_array[i][j] < env_array[i + 1][j])
					break ;
				else if (env_array[i][j] > env_array[i + 1][j])
				{
					swap(env_array, i, i + 1);
					break ;
				}
				j++;
			}
			i++;
		}
	}
}

void	print_export_env(void)
{
	char	**env_array;
	char	**split;
	int		i;

	env_array = get_env_array();
	if (!env_array)
		return (set_exit_code(127));
	sort_env_array(env_array, env_array_size(env_array));
	i = 0;
	while (env_array[i])
	{
		split = ft_split(env_array[i], '=');
		if (!split)
			return ;
		if (split[1])
			printf("declare -x %s=\"%s\"\n", split[0], split[1]);
		else
			printf("declare -x %s\n", split[0]);
		destroy_double_array(split);
		split = NULL;
		i++;
	}
	destroy_double_array(env_array);
}
