/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frequency_table.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rruiz-la <rruiz-la@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 10:54:30 by rruiz-la          #+#    #+#             */
/*   Updated: 2023/01/15 15:42:06 by rruiz-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "encoder.h"

static void check_table_size(int *vec, char *str)
{
	int i; 
	int j;

	j = 0;
	for (i = 0; i < 128; i++)
	{
		if (vec[i] > 0)
			j++;
	}
	if (j < 2)
	{
		printf("Encoder does not work with byte size less than 2\n");
		free (str);
		exit (1);
	}
}

void create_frequency_table(t_encoder *enc, char *str)
{
	int i;
	int j;

  	j = 0;
	i = 0;
	while(str[i])
	{
		if (isascii(str[i]) == 0)
		{
			printf("ascii error : the file must containt only charecter from ascii\n");
			exit(1);
		}	
		j = str[i];
		enc->vec[j] += 1;
		i++;
		j = 0;
	}
	check_table_size(enc->vec, str);
}
