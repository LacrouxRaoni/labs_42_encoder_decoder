/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decoder.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rruiz-la <rruiz-la@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 23:43:51 by rruiz-la          #+#    #+#             */
/*   Updated: 2023/01/15 11:19:40 by rruiz-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "decoder.h"

int main(void)
{
	t_decoder		dec;
	t_dec_return	ret;
	clock_t			start, end;

	start = clock();
	initi_struct(&dec, &ret);
	read_from_shared_memory(&dec);
	if (dec.byte)
	{
		create_list(&dec);
		build_huffman_tree(&dec);
		decompress_data(&dec, &ret);
			end = clock();
		ret.exec_time = (double)(end - start) / CLOCKS_PER_SEC;
		get_log_data(&dec, &ret);
		return_to_encoder(&ret, &dec);
		free_everything(&dec, &ret);
	}
}
