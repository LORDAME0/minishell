/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orahmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 21:52:35 by orahmoun          #+#    #+#             */
/*   Updated: 2022/03/12 18:15:02 by orahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_env *remove_variable(t_env *env, char *variable)
{
  t_env *new_env;
  t_env *tmp;

  new_env = NULL;
  while (env)
  {
    tmp = env->next;
    env->next = NULL;
    if (ft_strncmp(env->key, variable, ft_strlen(variable)) == 0
          && (ft_strlen(variable) == ft_strlen(env->key)))
    {
      free(env->key);
      free(env->value);
      free(env);
    }
    else
      add_variable_back(&new_env, env);
    env = tmp;
  }
  return (new_env); 
}

int bunset(char **args, t_env **env)
{
  size_t i;

  i = 0;
  if (args == NULL)
    return (0);
  while (args[i])
  {
    *env = remove_variable(*env, args[i]);
    i++;
  }
  return (0);
}
