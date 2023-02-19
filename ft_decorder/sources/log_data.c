/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rruiz-la <rruiz-la@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 11:17:52 by rruiz-la          #+#    #+#             */
/*   Updated: 2023/01/15 11:19:48 by rruiz-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "decoder.h"

void	get_log_data(t_decoder *dec, t_dec_return *ret)
{
	int i;
	i = 0;

	while (ret->dec_message[i])
		i++;
	ret->descmp_size_bits = i;
	ret->cmp_size_bits = dec->bytes_len;
}
