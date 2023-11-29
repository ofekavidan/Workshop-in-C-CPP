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
    int random_num = get_random_number(markov_chain->database->size);
    int counter = 0;
    Node *tmp = markov_chain->database->first;
    while (counter != random_num) {
        tmp = tmp->next;
        counter++;
    }
    if (tmp->data->data[strlen(tmp->data->data) - 1] == '.') {
        return get_first_random_node(markov_chain);
    } else {
        return tmp->data;
    }

}

// See full documentation in header file
MarkovNode *get_next_random_node(MarkovNode *state_struct_ptr) {
    int len_of_lst = state_struct_ptr->size_of_counter_list;
    int sum_of_freq = 0;
    for (int i = 0; i < len_of_lst; ++i) {
        sum_of_freq += state_struct_ptr->counter_list[i].frequency;
    }
    int random = get_random_number(sum_of_freq);
    int i = 0;

    while (0 < random) {
        random = random - state_struct_ptr->counter_list[i].frequency;
        i++;
    }
    if (random < 0)
    {
        i--;
    }

//    while (i < random) {
//        if (random > state_struct_ptr->counter_list[i].frequency) {
//            random = random - state_struct_ptr->counter_list[i].frequency;
//        } else {
//            break;
//        }
//        i++;
//    }
    return state_struct_ptr->counter_list[i].markov_node;

}

// See full documentation in header file
void generate_random_sequence(MarkovChain *markov_chain,
                              MarkovNode *first_node, int max_length) {
    if (first_node == NULL) {
        first_node = get_first_random_node(markov_chain);
    }
    bool not_last = true;
    if (first_node->data[strlen(first_node->data)-1] == '.') {
        not_last = false;
    }

    int counter = 1;
    printf(" %s", first_node->data);
    while (not_last && counter != max_length) {
        MarkovNode *tmp_markov_node = get_next_random_node(first_node);
        if (tmp_markov_node->data[strlen(tmp_markov_node->data)-1] == '.') {
            not_last = false;
        }
        counter++;
        printf(" %s", tmp_markov_node->data);
        first_node = tmp_markov_node;
    }
    printf("\n");
}

// See full documentation in header file
bool
add_node_to_counter_list(MarkovNode *first_node, MarkovNode *second_node) {
    // first we'll check if already exist
    for (int i = 0; i < first_node->size_of_counter_list; ++i) {
        if (strcmp(first_node->counter_list[i].markov_node->data,
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
    first_node->counter_list[first_node->size_of_counter_list -1].markov_node
    = second_node;
    first_node->counter_list[first_node->size_of_counter_list -1 ].frequency
    = 1;

    return EXIT_SUCCESS;
}

// See full documentation in header file
Node *get_node_from_database(MarkovChain *markov_chain, char *data_ptr) {

    if (markov_chain == NULL || markov_chain->database == NULL) {
        return NULL;
    }
    Node *runner = markov_chain->database->first;
    if (runner == NULL || runner->data == NULL) {
        return NULL;
    }

    for (int i = 0; i < markov_chain->database->size; ++i) {
        if (strcmp(runner->data->data, data_ptr) == 0) {
            return runner;
        }
        runner = runner->next;
    }
    return NULL;
}

// See full documentation in header file
Node *add_to_database(MarkovChain *markov_chain, char *data_ptr) {

    Node *to_add = get_node_from_database(markov_chain, data_ptr);
    if (to_add == NULL) {
        MarkovNode *markov_node = malloc(sizeof(MarkovNode));

        if (markov_node == NULL) {
            printf(ALLOCATION_ERROR_MASSAGE);
            return NULL;
        } else {
            markov_node->data = malloc(strlen(data_ptr) + 1);
            if(markov_node->data == NULL)
            {
                printf(ALLOCATION_ERROR_MASSAGE);
                free(markov_node);
                markov_node = NULL;
                return NULL;
            }
            strcpy(markov_node->data,data_ptr);

            markov_node->size_of_counter_list = 0;
            markov_node->counter_list = malloc(sizeof(NextNodeCounter));

            if(markov_node->counter_list == NULL)
            {
                printf(ALLOCATION_ERROR_MASSAGE);
                free(markov_node->data);
                markov_node->data = NULL;
                free(markov_node);
                markov_node = NULL;
                return NULL;
            }

            int if_succeed = add(markov_chain->database, markov_node);
            if (if_succeed) {
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
    Node *temp = (*markov_chain)->database->first;
    for (int i = 0; i < (*markov_chain)->database->size; ++i) {
        Node *next = temp->next;

        free(temp->data->counter_list);
        temp->data->counter_list = NULL;
        free(temp->data->data);
        temp->data->data = NULL;
        free(temp->data);
        temp->data = NULL;
        free(temp);
        // temp = NULL;
        temp = next;
    }
    (*markov_chain)->database->first = NULL;
    (*markov_chain)->database->last = NULL;


    free((*markov_chain)->database);
    (*markov_chain)->database = NULL;


    free((*markov_chain));
    (*markov_chain) = NULL;
}

