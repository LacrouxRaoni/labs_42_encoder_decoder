/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_reader.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rruiz-la <rruiz-la@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 10:48:53 by rruiz-la          #+#    #+#             */
/*   Updated: 2023/01/15 10:54:51 by rruiz-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "encoder.h"

int	get_files_qty(char **files)
{
	int i;

	i = 0;
	while (files[i])
		i++;
	return (i);
}

static char *read_files(char *file_in)
{
	FILE *file;
	char *str;
	long numbytes;

	file = fopen(file_in, "r");
	if (!file)
	{
		perror("encoder open file error ");
		exit(2);
	}
	fseek(file, 0L, SEEK_END);
	numbytes = ftell(file);
	fseek(file, 0L, SEEK_SET);
	str = (char *)calloc(numbytes, sizeof(char) + 1);
	if (!str)
	{
		perror("malloc error\n");
		exit(1);
	}
	fread(str, sizeof(char), numbytes, file);
	if (strlen(str) == 0)
	{
		printf("file is empty\n");
		exit(1);
	}
	fclose(file);
	return (str);
}

char *open_files(char **files)
{
	int	qty;
	char **lines;
	char *line;
	
	qty = get_files_qty(files);
	lines = (char **)calloc(qty, sizeof(char *));
	for (int i = 1; files[i]; i++)
		lines[i - 1] = read_files(files[i]);
	line = ft_str_superjoin(lines);
	free_matrix(lines);
	return (line);
}

