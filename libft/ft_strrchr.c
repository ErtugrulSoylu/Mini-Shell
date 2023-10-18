/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esoylu <42istanbul.com.tr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 19:59:45 by esoylu            #+#    #+#             */
/*   Updated: 2022/01/10 11:01:12 by arelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strrchr(const char *s, int c)
{
	int	loc;

	loc = 0;
	while (s[loc])
		loc++;
	while (loc >= 0 && s[loc] != (unsigned char)c)
		loc--;
	if (loc == -1)
		return (0);
	return (&((char *)s)[loc]);
}
