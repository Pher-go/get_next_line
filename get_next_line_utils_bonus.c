/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanuel- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 09:49:10 by fmanuel-          #+#    #+#             */
/*   Updated: 2021/10/29 16:34:37 by fmanuel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	while (str[len])
	{
		len++;
	}
	return (len);
}

char	*ft_strchr(const char *str, int c)
{
	char	ch;

	ch = (char)c;
	while (*str && *str != ch)
	{
		str++;
	}
	if (*str == ch)
		return ((char *)str);
	else
		return (0);
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;

	if (!dest && !src)
		return (NULL);
	d = dest;
	s = src;
	if (d > s)
	{
		d += n;
		s += n;
		while (n--)
			*--d = *--s;
	}
	else
	{
		while (n--)
			*d++ = *s++;
	}
	return (dest);
}

char	*ft_realloc(char *s, int size, int new_size)
{
	char	*new;
	int		i;

	new = NULL;
	new = malloc (new_size);
	if (new)
	{
		i = 0;
		while (i < size)
		{
			new[i] = s[i];
			i++;
		}
	}
	free(s);
	return (new);
}
