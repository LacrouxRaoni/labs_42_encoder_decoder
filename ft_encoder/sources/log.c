/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rruiz-la <rruiz-la@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 10:48:09 by rruiz-la          #+#    #+#             */
/*   Updated: 2023/01/15 11:13:25 by rruiz-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "encoder.h"

void	print_log(t_decoder_log *log)
{
	printf("********** EXECUTION LOG **********\n\n");
	printf("message: %s\n\n", log->data);
	printf("decompressed file size: %d\n", log->decmp_file_size);
	printf("compressed file size: %d\n", log->cmp_file_size);
	printf("execution time: %f\n", log->exec_time);
}