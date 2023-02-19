/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rruiz-la <rruiz-la@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 10:48:30 by rruiz-la          #+#    #+#             */
/*   Updated: 2023/01/15 10:48:31 by rruiz-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "encoder.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	size;

	if (s == NULL)
		return (NULL);
	if (start > strlen(s))
		return (strdup(""));
	if ((strlen(s) - start) < len)
		size = (strlen(s) - start) + 1;
	else
		size = len + 1;
	substr = (char *)malloc(size * sizeof(char));
	if (!substr)
	{
		return (NULL);
	}
	strncpy(substr, &s[start], size);
	return (substr);
}
