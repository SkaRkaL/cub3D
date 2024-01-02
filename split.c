#include "cub3D.h"

int	counter(char *s, char c)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c && s[i])
			i++;
		if (s[i] != c && s[i] != '\0')
			counter++;
		while (s[i] != c && s[i])
			i++;
	}
	return (counter);
}

void	*check_isfree(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free (str[i]);
		i++;
	}
	free (str);
	return (NULL);
}

void	ft_skip(char *str, int *start, int *end, char c)
{
	while (str[*start] == c)
		*start = *start + 1;
	*end = *start;
	while (str[*end] != c && str[*end] != 0)
		*end = *end + 1;
}

char	**ft_split(char *str, char c)
{
	char	**str_split;
	int		start;
	int		end;
	int		i;

	if (!str)
		return (NULL);
	str_split = malloc(counter(str, c) + 1);
	if (!str_split)
		return (0);
	start = 0;
	i = -1;
	while (++i < counter(str, c))
	{
		ft_skip(str, &start, &end, c);
		str_split[i] = ft_substr(str, start, end - start);
		if (!str_split[i])
			return (check_isfree(str_split));
		start = end;
	}
	str_split[i] = NULL;
	return (str_split);
}