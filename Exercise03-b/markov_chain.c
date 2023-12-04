// Created by Ofek Avidan on 10/08/2022.
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "markov_chain.h"


/**
* Get random number between 0 and max_number [0, max_number).
* @param max_number maximal number to return (not including)
* @return Random number
*/
int get_random_number(int max_number) {
    return rand() % max_number;
}

// See full documentation in header file
MarkovNode *get_first_random_node(MarkovChain *markov_chain) {
    int random_num =
            get_random_number(markov_chain->database->size);
    int counter = 0;
    Node *tmp = markov_chain->database->first;
    while (counter != random_num) {
        tmp = tmp->next;
        counter++;
    }
    if (markov_chain->is_last_markov_chain(tmp->data->data)) {
        return get_first_random_node(markov_chain);
    } else {
        return tmp->data;
    }

}

// See full documentation in header file
MarkovNode *get_next_random_node(MarkovNode *state_struct_ptr) {
    int len_of_lst = state_struct_ptr->size_of_counter_list;
    int sum_of_frequencies = 0;
    for (int i = 0; i < len_of_lst; ++i) {
        sum_of_frequencies += state_struct_ptr->counter_list[i].frequency;
    }
    int random = get_random_number(sum_of_frequencies);
    int i = 0;

    while (0 < random) {
        random = random - state_struct_ptr->counter_list[i].frequency;
        i++;
    }
    if (random < 0)
    {
        i--;
    }
    return state_struct_ptr->counter_list[i].markov_node;
}

// See full documentation in header file
void generate_random_sequence(MarkovChain *markov_chain,
                              MarkovNode *first_node, int max_length) {
    if (first_node == NULL) {
        first_node = get_first_random_node(markov_chain);
    }
    bool not_last = true;
    if (markov_chain->is_last_markov_chain(first_node->data)) {
        not_last = false;
    }

    int counter = 1;
    markov_chain->print_func_markov_chain(first_node->data);
    while (not_last && counter != max_length) {
        if (markov_chain->is_last_markov_chain(first_node->data)) {
            break;
        }
        MarkovNode *tmp_markov_node =
                get_next_random_node(first_node);

        counter++;
        markov_chain->print_func_markov_chain(tmp_markov_node->data);
        first_node = tmp_markov_node;
        fflush(stdout);
    }
    printf("\n");
}

// See full documentation in header file
bool
add_node_to_counter_list(MarkovNode *first_node, MarkovNode *second_node,
                         MarkovChain *markov_chain) {
    // first we'll check if already exist
    for (int i = 0; i < first_node->size_of_counter_list; ++i) {
        if (markov_chain->comp_func_markov_chain
        (first_node->counter_list[i].markov_node->data,
                                                 second_node->data) == 0) {
            first_node->counter_list[i].frequency++;
            return EXIT_SUCCESS;
        }
    }

    // second case, add the second node to the first one

    NextNodeCounter *tmp = realloc(first_node->counter_list,
                                   (first_node->size_of_counter_list + 1) *
                                   sizeof(NextNodeCounter));

    if (tmp == NULL) {
        printf(ALLOCATION_ERROR_MASSAGE);
        free(first_node->counter_list);
        first_node->counter_list = NULL;
        return EXIT_FAILURE;
    }

    first_node->counter_list = tmp;
    first_node->size_of_counter_list++;
    first_node->counter_list[first_node->size_of_counter_list-1].markov_node
            = second_node;
    first_node->counter_list[first_node->size_of_counter_list-1].frequency
            = 1;

    return EXIT_SUCCESS;
}

// See full documentation in header file
Node *get_node_from_database(MarkovChain *markov_chain, void *data_ptr) {

    if (markov_chain == NULL || markov_chain->database == NULL) {
        return NULL;
    }
    Node *runner = markov_chain->database->first;
    if (runner == NULL || runner->data == NULL) {
        return NULL;
    }

    for (int i = 0; i < markov_chain->database->size; ++i) {
        if (markov_chain->comp_func_markov_chain(runner->data->data, data_ptr)
        == 0) {
            return runner;
        }
        runner = runner->next;
    }
    return NULL;
}

// See full documentation in header file
Node *add_to_database(MarkovChain *markov_chain, void *data_ptr) {
    Node *to_add = get_node_from_database(markov_chain, data_ptr);
    if (to_add == NULL) {
        MarkovNode *markov_node = malloc(sizeof(MarkovNode));
        if (markov_node == NULL) {
            printf(ALLOCATION_ERROR_MASSAGE);
            return NULL;
        } else {
            markov_node->data = markov_chain->copy_func_markov_chain(data_ptr);
            if(markov_node->data == NULL)
            {
                printf(ALLOCATION_ERROR_MASSAGE);
                free(markov_node);
                markov_node = NULL;
                return NULL;
            }
//            markov_node->counter_list = calloc(sizeof(NextNodeCounter));

            markov_node->size_of_counter_list = 0;
            markov_node->counter_list = malloc(sizeof(NextNodeCounter));

            if(markov_node->counter_list == NULL) {
                printf(ALLOCATION_ERROR_MASSAGE);
                free(markov_node->data);
                markov_node->data = NULL;
                free(markov_node);
                markov_node = NULL;
                return NULL;
            }
            markov_node->counter_list->frequency = 0;
            markov_node->counter_list->markov_node = NULL;
            int is_failed = add(markov_chain->database,
                                markov_node);
            if (is_failed) {
                printf(ALLOCATION_ERROR_MASSAGE);
                free(markov_node->data);
                markov_node->data = NULL;
                free(markov_node->counter_list);
                markov_node->counter_list = NULL;
                free(markov_node);
                markov_node = NULL;
                return NULL;
            }
        }
        return markov_chain->database->last;
    }
    return to_add;
}

// See full documentation in header file
void free_markov_chain(MarkovChain **markov_chain) {
    if((markov_chain == NULL) || (*markov_chain == NULL)
    || ((*markov_chain)->database == NULL))
    {
        return;
    }

    Node *temp = (*markov_chain)->database->first;
    for (int i = 0; i < (*markov_chain)->database->size; ++i) {
        Node *next = temp->next;

        free(temp->data->counter_list);
        temp->data->counter_list = NULL;
        (*markov_chain)->free_data_markov_chain(temp->data->data);
        temp->data->data = NULL;
        free(temp->data);
        temp->data = NULL;
        free(temp);
        // temp = NULL;
        temp = next;
    }
    (*markov_chain)->database->first = NULL;
    (*markov_chain)->database->last = NULL;
}
