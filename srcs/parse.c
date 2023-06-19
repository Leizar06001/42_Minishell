/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdali <mabdali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 17:40:39 by mabdali           #+#    #+#             */
/*   Updated: 2023/06/16 18:25:33 by mabdali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//TOUT ES A LA NORME ET FREE LEAKS

int	odd_number_of_quotes(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (!str)
		return (-1);
	while (str[i])
	{
		if (str[i] == '"')
			count++;
		i++;
	}
	if (count == 0)
		return (-1);
	if (count % 2 == 0)
		return (1);
	return (0);
}

void	join_quotes(char **tmp, int *i, int *l)
{
	char	*tmp2;

	while (odd_number_of_quotes(tmp[*i]) == 0)
	{
		tmp2 = tmp[*i];
		tmp[*i] = ft_strjoin(tmp2, tmp[*i + *l]);
		free(tmp2);
		free(tmp[*i + *l]);
		(*l)++;
	}
}

void	update_tab_quotes(char **tmp, int *i, int *k, int *l)
{
	while (tmp[*i + *k + 1])
	{
		tmp[*i + *k + 1] = tmp[*i + *k + *l];
		(*k)++;
	}
	*i = 0;
	*k = 0;
	*l = 1;
}

void	join_update_quotes(char **tmp)
{
	int	i;
	int	k;
	int	l;

	i = 0;
	k = 0;
	l = 1;
	while (tmp[i])
	{
		if (odd_number_of_quotes(tmp[i]) != -1)
		{
			if (odd_number_of_quotes(tmp[i]) == 0)
			{
				if (tmp[i + 1])
					join_quotes(tmp, &i, &l);
				update_tab_quotes(tmp, &i, &k, &l);
			}
			else
				i++;
		}
		else
			i++;
	}
}

//FREE LEAKS
char	**parse(char *cmd)
{
	char	**tmp;

	//A la sortie de la fonction free(tmp[0],tmp[1],tmp[2])... et free(tmp)
	tmp = ft_split(cmd, ' ');
	join_update_quotes(tmp);
	//une fonction qui va enlever les quote sil y en a
	//GERER LES SIMPLE QUOTE
	//une fonction qui recherche les < > << >> | etc ...
	return (tmp);
}

// MAIN POUR FAIRE DES TESTS
// int main()
// {
//     char **tmp;
//
//     tmp = parse("echo abc \"abc def\" \"aze rty uiop\" \"qwerty\"");
//     int i = -1;
//     while (tmp[++i])
//         free(tmp[i]);
//     free(tmp);
// }
