/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarin-j <rmarin-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 20:07:48 by rmarin-j          #+#    #+#             */
/*   Updated: 2024/08/28 21:45:37 by rmarin-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "pipex.h"

void	ft_error(char *text)
{
	perror(text);
	exit(EXIT_FAILURE);
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

	fd1 = open(argv[1], O_RDONLY);
	if(fd1 == -1)
		ft_error("falla in file\n");
	com_args = ft_split_com(argv[2], ' ');
	com_p = find_com(com_args[0], env);
	dup2(fd1, STDIN_FILENO);
	dup2(pipe[1], STDOUT_FILENO);
	close(pipe[0]);
	close(fd1);
	close(pipe[1]);
	if(execve(com_p, com_args, env) == -1)
		ft_error("fallo exe child\n");
	free(com_p);
	free_array(com_args);
}
void	exe_com2(char **argv, char **env, int *pipe)
{
	char	*com_p;
	char	**com_args;
	int		fd2;

	fd2 = open(argv[4], O_WRONLY | O_TRUNC | O_CREAT, 0777);
	com_args = ft_split_com(argv[3], ' ');
	com_p = find_com(com_args[0], env);
	dup2(pipe[0], STDIN_FILENO);
	dup2(fd2, STDOUT_FILENO);
	close(pipe[1]);
	close(fd2);
	close(pipe[0]);
	if(execve(com_p, com_args, env) == -1)
		ft_error("fallo exe father\n");
	free(com_p);
	free_array(com_args);
}



int	main(int argc, char **argv, char **env)
{
	int tube[2];
	int pid;

	if (argc  != 5)
		ft_error("no son 4 argumentos\n"); 
	if(pipe(tube) == -1)
		ft_error("salio mal el pipe");
	pid = fork();
	if (pid == -1)
		ft_error("fallo el pid");
	if (pid == 0)
		exe_com1(argv, env, tube);
	waitpid(pid, NULL, 0);
	exe_com2(argv, env, tube);
	return (0);
}
