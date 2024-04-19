/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daviles- <daviles-@student.madrid42.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 14:09:15 by daviles-          #+#    #+#             */
/*   Updated: 2024/04/17 14:09:17 by daviles-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/philo.h"

/*@brief Used to return error message and free everything before exit*/
void    ft_perror(char *msj)
{
        ft_putstr_fd(msj, 2);
        ft_putstr_fd("\n", 2);
        // ft_clearenv((**sack));
}
void    ft_putstr_fd(char *s, int fd)
{
        int     i;

        i = 0;
        while (s[i] != '\0')
        {
                if(write (fd, &s[i], 1) == -1)
                        return ;
                i++;
        }
}

// void    perror_free_exit(char *msj, t_shell_sack ***sack)
// {
//         int     exitcode;

//         perror(msj);
//         exitcode = (**sack)->last_exit;
//         ft_clearenv((**sack));
//         free_sack(&(**sack));
//         exit(exitcode);
// }