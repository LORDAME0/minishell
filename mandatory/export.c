/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orahmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 15:45:05 by orahmoun          #+#    #+#             */
/*   Updated: 2022/03/12 20:39:03 by orahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

bool  is_valid_key(char *key)
{
  size_t  i;

  i = 1;
  panic(key == NULL, "key is NULL", __func__);
  if (key[0] == '\0'
      || (ft_isalpha(key[0]) == 0
      && key[0] != '_'))
    return (false);
  while (key[i])
  {
    if (ft_isalnum(key[i]) == 0 && key[i] != '_')
      return (false);
    i++;
  }
  return (true);
}

void  add_key(t_env **env, char *key, char *value)
{
  t_env *tmp;

  tmp = find_key(*env, key);
  if (tmp)
  {
    free(tmp->value);
    tmp->value = ft_strdup(value);
  }
  else
    add_variable_back(env,
      create_variable(ft_strdup(key), ft_strdup(value)));
}

int bexport(char **args, t_env **env, int fd)
{
  size_t  i;
  size_t  ret;
  char    *tmp;

  i = 0;
  ret = 0;
  if (*args == NULL)
  {
	  printf ("I'm here\n");
	  benv(*env, fd);
  }
  while (args[i])
  {
    if (ft_strchr(args[i], '=') == NULL)
    {
      if (is_valid_key(args[i]) == false)
        ret = printf ("export: not an identifier: %s\n", args[i]);
    }
    else
    {
      tmp = ft_strchr(args[i], '=');
      tmp[0] = '\0';
      if (is_valid_key(args[i]))
        add_key(env, args[i], tmp + 1);
      else
        ret = printf ("export: not an identifier: %s\n", args[i]);
      tmp[0] = '=';
    }
    i++;
  }
	if (ret)
	  g_global.last_return = 1;
  return (ret && true);
}
