/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarin-j <rmarin-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 20:07:48 by rmarin-j          #+#    #+#             */
/*   Updated: 2024/08/06 21:27:56 by rmarin-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "pipex.h"

void	ft_error(char *text)
{
	int i;

	i = 0;
	while(text[i])
	{
		write(1, &text[i], 1);
		i++;
	}
	exit(2);
}

void	read_env(char **env)
{
	int i;

	i = 0;
	while (env[i])
	{
		if (env[i][0] == 'P' && env[i][1] == 'A' &&env[i][2] == 'T' && env[i][3] == 'H')
			return(env[i]);
		i++;
	}
}


void	find_com(char *cm1, char **env)
{
	char	*abs_path;
	char	**paths;
	char	*com_p;
	int		i;

	i = 0;
	abs_path = read_env(env);
	paths = ft_split(abs_path, ':');
	while(paths[i])
	{
		com_p = ft_strjoin2(path[i], cm1);
		if (access(com_p, X_OK) == -1)
			ft_error("no hay comando")
		i++;
	}
}

void	check_imput(char **argv)
{
	if (open(argv[1], O_RDONLY) == -1)
		ft_error("archivo 1 mal");
	if(open(argv[4], O_RDWR) == -1)
		ft_error("archivo 2 mal");
	//check_com(argv[2], argv[3]);
	

}

int	main(int argc, char **argv, char **env)
{
	int fd[2];
	int pid;

	if (argc  != 5)
		//error
	fd = pipe();
	//check argvs
	pid = fork();
	if (pid == 0)
		//exe coman 1
	else
	{
		pid = fork();
		if(pid == 0)
			//exe coman 2
	}
	//free;
}
