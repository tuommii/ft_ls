/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftoa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 15:55:27 by mtuomine          #+#    #+#             */
/*   Updated: 2019/11/27 11:51:33 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	init_rounders(t_printf *p)
{
	p->rounders[0] = 0.5;
	p->rounders[1] = 0.05;
	p->rounders[2] = 0.005;
	p->rounders[3] = 0.0005;
	p->rounders[4] = 0.00005;
	p->rounders[5] = 0.000005;
	p->rounders[6] = 0.0000005;
	p->rounders[7] = 0.00000005;
	p->rounders[8] = 0.000000005;
	p->rounders[9] = 0.0000000005;
	p->rounders[10] = 0.00000000005;
	p->rounders[11] = 0.000000000005;
	p->rounders[12] = 0.0000000000005;
	p->rounders[13] = 0.00000000000005;
	p->rounders[14] = 0.000000000000005;
	p->rounders[15] = 0.0000000000000005;
	p->rounders[16] = 0.00000000000000005;
	p->rounders[17] = 0.000000000000000005;
	p->rounders[18] = 0.0000000000000000005;
	p->rounders[19] = 0.00000000000000000005;
	p->rounders[20] = 0.000000000000000000005;
}

static void	ftoa_checks(long double f, int precision, char **ptr)
{
	if (precision > MAX_PRECISION)
		precision = MAX_PRECISION;
	if (f < 0)
	{
		f = -f;
		**ptr++ = '-';
	}
	if (precision < 0)
	{
		if (f < 1.0)
			precision = 6;
		else if (f < 10.0)
			precision = 5;
		else if (f < 100.0)
			precision = 4;
		else if (f < 1000.0)
			precision = 3;
		else if (f < 10000.0)
			precision = 2;
		else if (f < 100000.0)
			precision = 1;
		else
			precision = 0;
	}
}

static void	handle_prec(int precision, char **ptr, char c, long double *f)
{
	if (precision)
	{
		**ptr = '.';
		*ptr += 1;
		while (precision--)
		{
			*f *= 10.0;
			c = *f;
			**ptr = '0' + c;
			*ptr += 1;
			*f -= c;
		}
	}
	**ptr = 0;
}

static void	handle_intpart(long *intpart, char **ptr, char **p, char *c)
{
	char *p1;

	if (!*intpart)
		*(*ptr)++ = '0';
	else
	{
		*p = *ptr;
		while (*intpart)
		{
			**p = '0' + *intpart % 10;
			*p += 1;
			*intpart /= 10;
		}
		p1 = *p;
		while (*p > *ptr)
		{
			c[0] = *(--*p);
			**p = **ptr;
			**ptr = c[0];
			*ptr += 1;
		}
		*ptr = p1;
	}
}

void		pf_ftoa(t_printf *pf, long double f, char *buf, int precision)
{
	char *ptr;
	char *p;
	char c;
	long intpart;

	ptr = buf;
	p = ptr;
	c = 0;
	init_rounders(pf);
	ftoa_checks(f, precision, &ptr);
	if (precision)
		f += pf->rounders[precision];
	intpart = f;
	f -= intpart;
	handle_intpart(&intpart, &ptr, &p, &c);
	handle_prec(precision, &ptr, c, &f);
}
