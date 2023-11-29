// Created by Ofek Avidan on 10/08/2022.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "markov_chain.h"

#define CASE_OF_THREE_ARGS 4
#define CASE_OF_FOUR_ARGS 5
#define OUR_BASE 10
#define MAX_LEN 1001 // + '\0'
#define MAX_TWEET 20
#define SEED argv[1]
#define NUMBER_OF_TWEETS argv[2]
#define PATH argv[3]
#define NUMBER_OF_WORDS argv[4]
#define NUMBER_OF_ARGS_ERROR "Usage: please enter 3 or 4 arguments"
#define PATH_ERROR "Error: path isn't valid"
#define ALLOCATION_ERROR_MASSAGE "Allocation failure: Failed to allocate"\
            "new memory\n"


/**
 * this function reads the file, and fill the database
 * (markov_chain->database) of the program
 * @param fp - the input file
 * @param words_to_read - number of words to read. 0 if use meant all
 * @param markov_chain - the pointer to the database itself
 * @return 0 if all the allocates succeed, 1 otherwise
 */
int fill_database(FILE *fp, int words_to_read, MarkovChain *markov_chain)
{
    char buffer[MAX_LEN];
    int counter = 0;
    MarkovNode *prev = NULL;
    while (fgets(buffer, MAX_LEN, fp)) {
        char *second_word = strtok(buffer, " \n\r\0");

        while ((second_word != NULL && words_to_read != counter
        && words_to_read != 0) ||
        (second_word != NULL && words_to_read == 0))
        {
//            if (second_word[strlen(second_word)-1] == '\n' ||
//                second_word[strlen(second_word)-1] == '\r') {
//                second_word[strlen(second_word)-1] = '\0';
//            }

            if (counter == words_to_read && words_to_read != 0) {
                break;
            }
            MarkovNode *first = (add_to_database(markov_chain,
                                                 second_word))->data;
            if (first == NULL) {
                return EXIT_FAILURE;
            }
            if (prev != NULL && prev->data[strlen(prev->data) -1] != '.') {
                add_node_to_counter_list(prev,first);
            }
            // if first is last, prev = NULL
            if((first->data)[strlen((first->data))-1] == '.') {
                prev = NULL;
            }
            prev = first;
            second_word = strtok(NULL, " \n\r\0");
            counter++;
        }
    }
    return EXIT_SUCCESS;
}

/**
 * a simple function which checks all 3/4 arguments
 * @param argc - number of arguments
 * @param argv - the arguments themselves
 * @return SUCCESS if 3/4 args, and path is OK, FAILURE otherwise
 */
int initial_argument_tests(int argc, char *argv[])
{
    if (argc != CASE_OF_THREE_ARGS && argc != CASE_OF_FOUR_ARGS)
    {
        fprintf(stdout, NUMBER_OF_ARGS_ERROR);
        return EXIT_FAILURE;
    }
    else
    {
        FILE *input = fopen(argv[3], "r");
        if (input == NULL)
        {
            fprintf(stdout, PATH_ERROR);
            return EXIT_FAILURE;
        }
        fclose(input);
    }
    return EXIT_SUCCESS;
}

/**
 * a simple function which initialize the seed
 * @param seed - the second argument that we got from CommandLine
 */
void initialize_seed(char* seed)
{
    long seed_long = strtol(seed, NULL, OUR_BASE);
    srand(seed_long);
}

/**
 * this function create the tweets (appropriate to number of tweets)
 * it uses get_first_random_node func. to create the beginning of the tweet,
 * then uses generate_random_sequence to complete it.
 * last but not least, it uses number_of_tweets to create the appropriate
 * number of tweets.
 * @param database - pointer to the database itself
 * @param number_of_tweets - number of tweets
 */
void create_tweet(MarkovChain* database, int number_of_tweets)
{
    for (int i = 0; i < number_of_tweets; i++) {
        printf("Tweet %d:", (i+1));
        MarkovNode * first = get_first_random_node(database);
        generate_random_sequence(database,first, MAX_TWEET);
    }
}

/**
 * the main function. first uses initial_argument_tests to make sure we got
 * appropriate arguments.then creates an empty database to send the last
 * to fill_database and make it full. then uses create_tweet as well,
 * and ends the program by close the file and clean the heap.
 * @param argc - number of arguments
 * @param argv - the arguments themselves
 * @return FAILURE if args not OK, or couldn't allocate memory. else, SUCCESS.
 */
int main (int argc, char *argv[]) {
    if (initial_argument_tests(argc, argv) != 0) {
        // first check if 3/4 args. if not, return EXIT_FAILURE
        return EXIT_FAILURE;
    } // arguments are OK
    initialize_seed(SEED);
    FILE *input = fopen(PATH, "r");
    MarkovChain *markov_chain = malloc(sizeof (MarkovChain));
    if(markov_chain == NULL) {
        printf(ALLOCATION_ERROR_MASSAGE);
        return EXIT_FAILURE;
    }
    markov_chain->database = malloc(sizeof (LinkedList));
    if(markov_chain->database == NULL) {
        printf(ALLOCATION_ERROR_MASSAGE);
        free(markov_chain);
        return EXIT_FAILURE;
    }
    markov_chain->database->first = NULL;
    markov_chain->database->last = NULL;
    markov_chain->database->size = 0;
    int filled_succeed = 0;
    if (argc == CASE_OF_FOUR_ARGS) {
        int words_to_read = strtol(NUMBER_OF_WORDS, NULL, OUR_BASE);
        filled_succeed = fill_database(input, words_to_read, markov_chain);
    }
    else {
        // in case of 3 arguments
        filled_succeed = fill_database(input, 0, markov_chain);
    }
    if(filled_succeed) {
        return EXIT_FAILURE;
    }
    int num_of_tweets = strtol(NUMBER_OF_TWEETS, NULL, OUR_BASE);
    create_tweet(markov_chain, num_of_tweets);
    free_markov_chain(&markov_chain);
//    print_chain(markov_chain);
    fclose(input);
    EXIT_SUCCESS;
}