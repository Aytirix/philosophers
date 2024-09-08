#include "Philosophers.h"

int	ft_atoi(const char *nptr)
{
	int			i;
	int			sign;
	long long	result;

	result = 0;
	i = 0;
	sign = 1;
	while (((*nptr >= 9 && *nptr <= 13) || *nptr == 32))
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			sign = -sign;
		nptr++;
	}
	while (nptr[i] && (nptr[i] >= '0' && nptr[i] <= '9'))
		result = result * 10 + nptr[i++] - '0';
	if (((i > 10 || result > INT_MAX) && sign == 1) || ((i > 10
				|| result > ((INT_MIN) * -1LL)) && sign == -1))
		return (0);
	return (sign * result);
}