/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mucankir < mucankir@student.42kocaeli.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 00:33:41 by mucankir          #+#    #+#             */
/*   Updated: 2024/12/16 18:08:30 by mucankir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>
#include <stdio.h>

char	*ft_unread(char *st_str)
{
	char	*left;
	int		i;
	int		j;

	printf("In UNREAD Func ---> enterance/ char st_str --->   %s \n ˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙\n",st_str);


	i = 0;
	while (st_str[i] && st_str[i] != '\n')
		i++;

	left = malloc(ft_strlen(st_str) - i + 1);
	printf("In UNREAD Func ---> after mallocate/ char left --->    %s \n ˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙\n",left);
	

	if (!left)
	{
		free(st_str);
		return (NULL);
	}

	j = 0;
	while (st_str[i] != '\0')
		left[j++] = st_str[i++];
	left[j] = '\0';
	printf("In UNREAD Func ---> Returned / char left ---> \n %s \n˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙\n\n\n",st_str);

	free(st_str);
	return (left);
}

char	*ft_get_line(char *st_str)
{
	char	*get_line;
	int		i;

	printf("In GET_LINE Func ---> enterance/ char st_str ---> \n %s \n ˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙\n\n",st_str);

	i = 0;
	if (!st_str[i])
		return (NULL);
	while (st_str[i] && st_str[i] != '\n')
		i++;
	get_line = malloc(i + 1 + ft_check_nl(st_str));
	printf("In GET_LINE Func --->  after mallocate/ char get_line ---> \n %s \n\n ˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙\n",get_line);

	if (!get_line)
		return (NULL);
	i = 0;
	while (st_str[i] && st_str[i] != '\n')
	{
		get_line[i] = st_str[i];
		i++;
	}
	if (st_str[i] == '\n')
	{
		get_line[i] = st_str[i];
		i++;
	}
	get_line[i] = '\0';

	printf("In GET_LINE Func ---> returned/ char get_line ---> \n %s \n ˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙\n\n\n",get_line);

	return (get_line);
}

char	*ft_file_reader(char *st_str, int fd)
{
	int		read_byte;
	char	*buffer;

	read_byte = 1;
	
	printf("		In file_reader Func ----> \n			before mallocate/ char buffer--->  |%s|\n			˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙ ̇\n", buffer);
	buffer = malloc(BUFFER_SIZE + 1);
	
	printf("				before read/ char buffer--->   |%s|\n\n				˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙.˙˙˙˙˙˙˙˙˙˙˙˙\n", buffer);
	if (!buffer)
		return (NULL);
	while (!ft_check_nl(st_str) && read_byte != 0)
	{
		read_byte = read(fd, buffer, BUFFER_SIZE);
		printf("					byte read --->     %d\n					  ˙˙˙˙˙˙˙˙˙˙ ̇\n",read_byte);
		if (read_byte == -1)
		{
			printf("				Errored byte read --->     %d\n˙˙˙˙˙˙˙˙˙˙˙˙\n",read_byte);
			free(buffer);
			free(st_str);
			return (NULL);
		}
		buffer[read_byte] = '\0';
		printf("			after read/ char buffer --->   |%s| \n			  ˙˙˙˙˙˙˙˙˙˙˙˙\n",buffer);
		printf("			after read/ char st_str --->   |%s| \n\n\n 			˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙.\n",st_str);

	
		st_str = ft_strjoin(st_str, buffer);
		printf("				after join/ char buffer --->    |%s| \n 				˙˙˙˙˙˙˙˙˙˙˙˙˙˙ ̇˙˙˙˙\n",buffer);
		printf("				after join/ char st_str --->    |%s| \n\n\n",st_str);
		printf("************************************************************************************\n");
	}

	printf("				before free/ char buffer --->    |%s| \n 				˙˙˙˙˙˙˙˙˙˙˙˙˙˙ ̇˙˙˙˙\n",buffer);
	free(buffer);
	printf("				after free/ char buffer --->    |%s| \n########################################################################################\n",buffer);

	return (st_str);
}

char	*get_next_line(int fd)
{
	static char	*st_str;
	char		*current_line;

	printf("In get_next_line Func --->Enterance---static_str --->   %s\n\n\nSending File_reader func\n",st_str);

	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		free(st_str);
		return (NULL);
	}
	st_str = ft_file_reader(st_str, fd);
	printf("  In get_next_line Func --->\n Return frm filereader func/char static_str ---> %s\n˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙\n\n\n",st_str);
	if (!st_str)
	{
		return (NULL);
	}

	printf("  In get next line Func --->  before sending get_line func/ char st_str --->   %s \n\n ˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙\n",st_str);
	current_line = ft_get_line(st_str);
	printf("  In get_next_line Func --->\nReturn frm get_line func/char curren_line --->   %s\n˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙\n",current_line);
	printf("  In get_next_line Func --->\nReturn frm get_line func/char static_str --->    %s\n˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙\n\n\n\n",st_str);

	st_str = ft_unread(st_str);
	printf("  In get_next_line Func --->\nReturn frm unread func/char static_str --->   %s\n˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙\n",st_str);
	printf("  In get_next_line Func --->\nReturn frm unread func/char static_str --->   %s\n˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙\n\n", st_str);
	return (current_line);
}
