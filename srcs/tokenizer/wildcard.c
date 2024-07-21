#include "../minishell.h"

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
			continue ;
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

/*t_dir	**ft_aaa(t_dir **dirs)
{
	t_dir	**tmp_dirs;

	tmp_dirs = ft_copy_dir(".",  FILE_DIR);
	printf("1-------> tmp : %s\n", (*tmp_dirs)->name);
	dirs = ft_get_all_dirs(dirs, 0, *tmp_dirs);
	return (dirs);
}

t_dir	**ft_get_all_dirs(t_dir **dirs, int i, t_dir *tmpa)
{
	t_dir	**tmp_dir;
	t_dir	**tmp_file;
	t_dir	*tmp1;
	char	*copy;

	sleep(1);
	copy = ft_strdup(tmpa->name);
	printf("2-------> tmpa avant ft_copy_dir: %s\n", copy);
	tmp_dir = ft_copy_dir(".", FILE_DIR);
	tmp_file = ft_copy_dir(".", FILE_FILE);
	ft_show_all_dirs(tmp_file);
	printf("4-------> tmpa après ft_copy_dir: %s\n", copy);

	if (tmpa)
	{
		printf("\n---> tmpa->name : %s\n", copy);
		chdir(copy);
		tmp_dir = ft_copy_dir(".", FILE_DIR);
		tmp1 = *tmp_dir;
		if (tmp1 != NULL)
			ft_get_all_dirs(dirs, i + 1, tmp1);
		chdir("..");
		tmpa = tmpa->next;
		printf("5-------> tmpa avant ft_copy_dir: %s\n", tmpa->name);
		ft_get_all_dirs(dirs, i + 1, tmpa->next);
	}
	return (dirs);
}


void	ft_dirmatch(char *path, char *w, int n)
{
	char			*next_path;
	char			**dirs;
	int				i;

	printf("N : %d\n", n);
	if (n > ft_count_char(w, '*') + 10)
	{
		printf("> %s\n", path);
		return ;
	}
	dirs = ft_copy_dir(".");
	printf("------- DIRS ----------\n");
	printf("GETCWD : %s\n", getcwd(NULL, 0));
	ft_show_all_var(dirs);
	printf("-----------------------\n");
	i = 0;
	while (dirs[i])
	{
		if (ft_match(path, w, n))
		{
			if (path[0] == '.')
				next_path = ft_strdup(dirs[i]);
			else
			{
				next_path = ft_strjoin(path, "/");
				next_path = better_strjoin(next_path, dirs[i]);
			}
			printf(">> %s\n", next_path);
			chdir(dirs[i]);
			ft_dirmatch(next_path, w, n + 1);
			chdir("..");
		}
		i++;
	}
}

abcdef
012345

i <-> 6 - i - 1*/