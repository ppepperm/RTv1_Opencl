/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahusk <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 16:13:07 by ahusk             #+#    #+#             */
/*   Updated: 2020/07/22 16:13:11 by ahusk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cl_rt.h"

void	check_name(char *l, int *i, char *name)
{
    char tmp[21];

    while (l[++(*i)] != ';' && *i != 21)
        tmp[*i] = l[*i];
    tmp[*i] = '\0';
    if (ft_strcmp(tmp, name))
        ft_error(l);
}

void	check_arg(char *l, int *i, int num)
{
    int tz;

    tz = 0;
    while (tz != num && l[++(*i)])
    {
        if (l[*i] == ';')
            tz++;
        else if ((l[*i] < '0' || l[*i] > '9') && l[*i] != '-' && l[*i] != ' ')
            ft_error(l);
    }
    if (tz < num)
        ft_error(l);
}

void	check_line(char *l, char *name, int num)
{
    int i;

    i = -1;
    check_name(l, &i, name);
    check_arg(l, &i, num);
}

void	parser(char *l)
{
    if (l[0] == 's')
        check_line(l, "sphere", 8);
    else if (l[0] == 'c' && l[1] == 'o')
        check_line(l, "cone", 9);
    else if (l[0] == 'c' && l[1] == 'y')
        check_line(l, "cylinder", 8);
    else if (l[0] == 'd')
        check_line(l, "dot_source", 4);
    else if (l[0] == 'p')
        check_line(l, "plane", 8);
    else
        ft_error(l);
}

void	validation(char *fname)
{
    char	*l;
    int		fd;

    l = NULL;
    fd = open(fname, O_RDWR);
    if (fd < 0)
        ft_error(l);
    while (get_next_line(fd, &l))
    {
        parser(l);
        free(l);
    }
    close(fd);
}
