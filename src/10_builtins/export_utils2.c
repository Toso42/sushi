/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdi-leo <tcorax42@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 13:22:10 by kzak              #+#    #+#             */
/*   Updated: 2023/01/03 17:27:00 by tdi-leo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	error_no_name(char **name_value, int *wrong_names)
{
	char	*error_string;

	if (name_value[1])
		error_string = ft_strjoinfree(ft_strdup("sushi: export: `="), \
					ft_strdup(name_value[1]));
	else
		error_string = ft_strjoinfree(ft_strdup("sushi: export: `"), \
					ft_strdup(""));
	error_string = ft_strjoinfree(error_string, \
				ft_strdup("': not a valid identifier"));
	++(*wrong_names);
	error_handler(1, error_string, RESET_PRINT);
}
