/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakamot <ynakamot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 11:55:34 by ynakamot          #+#    #+#             */
/*   Updated: 2020/11/03 16:03:34 by ynakamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(const char *s)
{
	size_t i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	char	*r;

	if (!s)
		return (NULL);
	r = (char *)s;
	while (*r)
	{
		if (*r == c)
			return (r);
		r++;
	}
	if (c == '\0')
		return (r);
	else
		return (NULL);
}

char	*ft_strdup(const char *src)
{
	char	*str;
	size_t	len;
	size_t	i;

	i = 0;
	len = ft_strlen(src);
	if (!(str = malloc(sizeof(*str) * (len + 1))))
		return (NULL);
	while (i < len)
	{
		str[i] = src[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		i;
	int		len;

	if (s1 == NULL && s2 == NULL)
		return (ft_strdup(""));
	if (s1 == NULL)
		return (ft_strdup(s2));
	if (s2 == NULL)
		return (ft_strdup(s1));
	i = 0;
	len = ft_strlen(s1) + ft_strlen(s2);
	if (!(str = malloc(sizeof(char) * (len + 1))))
		return (NULL);
	while (*s1)
		str[i++] = *s1++;
	while (*s2)
		str[i++] = *s2++;
	str[i] = '\0';
	return (str);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t		i;
	size_t		slen;
	char		*p;

	if (!s)
		return (NULL);
	slen = ft_strlen(s);
	if (slen < start)
		return (ft_strdup(""));
	if (slen < (start + len))
		len = slen - start;
	if (!(p = malloc(sizeof(char) * (len + 1))))
		return (NULL);
	i = 0;
	while (i < len)
	{
		p[i] = s[start + i];
		i++;
	}
	p[i] = '\0';
	return (p);
}
