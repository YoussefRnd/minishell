#include "../../inc/minishell.h"
#include "../inc/env.h"

/**
 * create_env_dict - it will create(allocate)!!! a sort of a match of a python dictionary/list
 * that contains in each node in it an enviroment variable with as a pair of 
 * key value and return it to work with it while the whole running of the program
 * @env: the 2d array of enviroment variables inherited from the previous shell
 * Return : on succes the linked list, on failure NULL
 */
t_env *create_env_dict(char **env)
{
    if (!env)
        return (NULL);
    while(*env)
    {
        // it's fucking midnight and i can't think of shit
    }
}

/**
 * node_init - it will fill the right
 * formations of each env var in a node
 */