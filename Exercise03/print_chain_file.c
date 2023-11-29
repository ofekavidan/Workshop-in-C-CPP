#include "markov_chain.h"
#include "linked_list.h"
#include <stdio.h>

void print_chain(MarkovChain *chain)
{
    if(!chain || !chain->database || !chain->database->first || !chain->database->first->data)
    {
        return;
    }
    Node *p_node = chain->database->first;
    for(int i = 0; i < chain->database->size; i++)
    {
        printf("%s:\n", p_node->data->data);
        for(int j = 0; j < p_node->data->size_of_counter_list; j++)
        {
            printf("%s %d\n", p_node->data->counter_list[j].markov_node->data, p_node->data->counter_list[j].frequency);
        }
        p_node = p_node->next;
    }
}
