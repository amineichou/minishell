/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moichou <moichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 12:32:10 by moichou           #+#    #+#             */
/*   Updated: 2024/05/14 12:32:29 by moichou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_set_status(int new_status, int type)
{
	static int	old_status;

	if (type)
		old_status = new_status;
	return (old_status);
}
