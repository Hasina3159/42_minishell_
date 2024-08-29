#include "../../include/minishell.h"

void	ft_show_all_dirs(t_dir **dirs)
{
	t_dir	*tmp;

	printf("------------------- ALL DIRS -------------------\n");
	tmp = *dirs;
	while (tmp)
	{
		usleep(5000);
		printf("> start : %p - end : %p, FILE : %s > TYPE : ", tmp, tmp + sizeof(tmp),tmp->name);
		if (tmp->type == FILE_DIR)
			printf("_DIRECTORY_\n");
		else
			printf("_FILE_\n");
		tmp = tmp->next;
	}
	printf("------------------------------------------------\n");

}

t_dir	**ft_init_dirs(void)
{
	t_dir	**dir;

	dir = ft_calloc(1, sizeof(t_dir **));
	if (dir == NULL)
		return (NULL);
	return (dir);
}
