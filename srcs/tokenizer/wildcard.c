#include "../../include/minishell.h"

int	ft_match_one(char *s, char next)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == next || s[i] == '/')
			return (i);
		i++;
	}
	if (s[i] == next)
		return (i);
	return (-1);
}

int	ft_match(char *s, char *w)
{
	int	i;
	int	j;
	int	ok;
	int	w_count;

	w_count = ft_count_char(w, '/');
	if (ft_count_char(s, '/') != w_count)
		return (0);
	i = 0;
	j = 0;
	ok = 0;
	while (w[i])
	{
		ok = -2;
		if (w[i] == '*' && w[i + 1] && w[i + 1] == '*')
		{
			i++;
			continue ;
		}
		if ((w[i] != '*' && w[i] != s[j]))
			return (0);
		if (w[i] == '*')
			ok = ft_match_one(&s[j], w[i + 1]);
		if (ok == -1)
			return (0);
		else if (ok != -2)
			j = j + ok - 1;
		j++;
		i++;
	}

	return (1);
}

int	ft_count_dir(char *path)
{
	DIR				*dir;
	struct dirent	*entry;
	int				count;

	dir = NULL;
	ft_opendir(path, &dir);
	count = 0;
	entry = readdir(dir);
	while (entry != NULL)
	{
		if (entry->d_name[0] == '.')
		{
			entry = readdir(dir);
			continue ;
		}
		entry = readdir(dir);
		count++;
	}
	ft_closedir(&dir);
	return (count);
}

t_dir	**ft_copy_dir(t_dir **dirs, int len_cwd)
{
	DIR				*dir;
	struct dirent	*entry;
	char			cwd[TOKENS_MAX];
	char			*tmp;

	if (getcwd(cwd, TOKENS_MAX) == NULL)
		return (NULL);
	ft_opendir(".", &dir);
	entry = readdir(dir);
	while (entry != NULL)
	{
		usleep(5000);
		if (entry->d_name[0] == '.')
		{
			entry = readdir(dir);
			continue ;
		}
		tmp = ft_strjoin(cwd, "/");
		tmp = better_strjoin(tmp, entry->d_name);
		if (ft_isdir(tmp) == -1)
		{
			printf("COPY DIR\n");
			continue ;
		}
		else if (ft_isdir(tmp) == 1)
		{
			ft_add_dir(dirs, ft_create_dir(ft_strdup(&tmp[len_cwd]), FILE_DIR));
			chdir(entry->d_name);
			ft_copy_dir(dirs, len_cwd);
			chdir("..");
		}
		else if (ft_isdir(tmp) == 0)
			ft_add_dir(dirs, ft_create_dir(ft_strdup(&tmp[len_cwd]), FILE_FILE));
		entry = readdir(dir);
		free(tmp);
	}
	ft_closedir(&dir);
	return (dirs);
}
