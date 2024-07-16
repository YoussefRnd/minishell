#ifndef ENV_H
#define ENV_H

typedef struct s_env
{
    char *key;
    char *value;
    struct s_env *next;
} t_env;

char	**split_it(char *str);
void node_init(char *str, t_env *node);
void	append_node(t_env **head, char *data);
void print_list(t_env *head);
#endif