/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyamli <zakariayamli00@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 18:26:15 by zyamli            #+#    #+#             */
/*   Updated: 2024/03/30 00:43:37 by zyamli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<unistd.h>
#include<stdio.h>
#include<string.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>


// char* basename(const char* path) {
//     // Find the last occurrence of '/' or '\'
//     const char* last_slash = strrchr(path, '/');
//     if (!last_slash)
//         last_slash = strrchr(path, '\\'); // Windows path separator
    
//     // If no slash found, return the entire path
//     if (!last_slash)
//         return strdup(path);
    
//     // Return the substring after the last slash
//     return strdup(last_slash + 1);
// }

// int main() {
//     const char* path = "/path";
//     printf("Basename: %s\n", basename(path));
//     return 0;
// }

int main(int ac, char **av, char **env)
{
    // struct dirent *entry;
	// DIR *dir = opendir("/");
	// if (dir) {
    //     printf("is a directory");
	//     closedir(dir);	
	// 	return 1;
	// }
// while ((entry = readdir(dir)) != NULL)
// 	{
// 		printf("%s\n", entry->d_name);
	// char *arg[] = ;
    execve("/bin/bash", (char **){"bash", NULL}, NULL);
     perror("MKHDAMCH");
// 	}
//     closedir(dir);
}