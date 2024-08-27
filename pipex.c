/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarin-j <rmarin-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 20:07:48 by rmarin-j          #+#    #+#             */
/*   Updated: 2024/08/27 20:01:43 by rmarin-j         ###   ########.fr       */
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

char	*read_env(char **env)
{
	int i;

	i = 0;
	while (env[i])
	{
		if (env[i][0] == 'P' && env[i][1] == 'A' &&env[i][2] == 'T' && env[i][3] == 'H')
			return(env[i]);
		i++;
	}
	return (0);
}


char	*find_com(char *cm, char **env)
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
		com_p = ft_strjoin2(paths[i], cm);
		if (access(com_p, X_OK) == 0)
			return(com_p);
		i++;
	}
	return(cm);
}

void	exe_com1(char **argv, char **env, int *pipe)
{
	char	*com_p;
	char	**com_args;
	int		fd1;
	close(pipe[0]);
	fd1 = open(argv[1], O_RDONLY);
	com_args = ft_split_com(argv[2], ' ');
	com_p = find_com(com_args[0], env);
	dup2(fd1, STDIN_FILENO);
	close(fd1);
	dup2(pipe[1], STDOUT_FILENO);
	close(pipe[1]);
	execve(com_p, com_args, env);
	exit(1);
}
void	exe_com2(char **argv, char **env, int *pipe)
{
	char	*com_p;
	char	**com_args;
	int		fd2;

	close(pipe[1]);
	fd2 = open(argv[4], O_WRONLY | O_TRUNC | O_CREAT, 0777);
	com_args = ft_split_com(argv[3], ' ');
	com_p = find_com(com_args[0], env);
	dup2(pipe[0], STDIN_FILENO);
	close(pipe[0]);
	dup2(fd2, STDOUT_FILENO);
	close(fd2);
	execve(com_p, com_args, env);
	exit(1);
}



int	main(int argc, char **argv, char **env)
{
	int tube[2];
	int pid1;
	int pid2;
/* 	int fd1;
	int fd2; */

	if (argc  != 5)
		ft_error("no son 4 argumentos\n"); 
/* 	fd1 = open(argv[1], O_RDONLY);
	if(fd1 < 0)
		ft_error("mal fd1");
	close(fd1);
	fd2 = open(argv[4], O_WRONLY | O_TRUNC | O_CREAT, 0777);
	if (fd2 < 0)
	{
		close(fd1);
		ft_error("mal open");
	}
	close(fd2); */
	//----------------------------
	pid1 = fork();
	pipe(tube);
	if (pid1 == 0)
		exe_com1(argv, env, tube);
	 else
	{
		pid2 = fork();
		if(pid2 == 0)
			exe_com2(argv, env, tube);
	}
	close(tube[1]);
	close(tube[0]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (0);
}
