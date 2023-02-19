/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   encoder.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rruiz-la <rruiz-la@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 10:48:58 by rruiz-la          #+#    #+#             */
/*   Updated: 2023/01/15 10:49:02 by rruiz-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "encoder.h"

int main(int argc, char* argv[]){

	t_encoder		enc;
	t_decoder_log	log;
	char			*str;

	if (argc >= 2){
		init_structs(&enc, &log);
		str = open_files(argv);
		create_frequency_table(&enc, str);
		create_list(&enc);
		build_huffman_tree(&enc);
		build_dctionary(&enc);
		convert_to_bin(&enc, str);
		memory_share(&enc, &log);
		print_log(&log);
		free(str);
		free_everything(&enc, &log);
	}
	else if (argc > 2)
		printf("Too many files to be compressed\n");
	else
		printf("Please send a file to be compressed\n");
}