#include <string.h> // For strlen(), strcmp(), strcpy()
#include "markov_chain.h"

#define MAX(X, Y) (((X) < (Y)) ? (Y) : (X))

#define EMPTY -1
#define BOARD_SIZE 100
#define MAX_GENERATION_LENGTH 60

#define DICE_MAX 6
#define NUM_OF_TRANSITIONS 20
#define SEED argv[1]
#define NUMBER_OF_PATHS argv[2]
#define WANTED_NUMBER_OF_ARGS 3
#define NUMBER_OF_ARGS_ERROR "Usage: please enter 3 or 4 arguments"
#define OUR_BASE 10


/**
 * this function checks number of arguments.
 * @param argc - number of args
 * @return success if 2 args, failure otherwise
 */
static int initial_argument_tests(int argc) {
    if (argc != WANTED_NUMBER_OF_ARGS) {
        fprintf(stdout, NUMBER_OF_ARGS_ERROR);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

/**
 * represents the transitions by ladders and snakes in the game
 * each tuple (x,y) represents a ladder from x to if x<y or a snake otherwise
 */
static const int transitions[][2] = {{13, 4},
                              {85, 17},
                              {95, 67},
                              {97, 58},
                              {66, 89},
                              {87, 31},
                              {57, 83},
                              {91, 25},
                              {28, 50},
                              {35, 11},
                              {8,  30},
                              {41, 62},
                              {81, 43},
                              {69, 32},
                              {20, 39},
                              {33, 70},
                              {79, 99},
                              {23, 76},
                              {15, 47},
                              {61, 14}};

/**
 * struct represents a Cell in the game board
 */
typedef struct Cell {
    int number; // Cell number 1-100
    int ladder_to;  // ladder_to represents the jump
    // of the ladder in case there is one from this square
    int snake_to;  // snake_to represents the jump
    // of the snake in case there is one from this square
    //both ladder_to and snake_to should be -1 if the Cell doesn't have them
} Cell;

/** Error handler **/
static int handle_error(char *error_msg, MarkovChain **database) {
    printf("%s", error_msg);
    if (database != NULL) {
        free_markov_chain(database);
    }
    return EXIT_FAILURE;
}

/**
 * this function creates the board, and got activated by fill_database
 * it uses malloc to create memory for each cell
 * @param cells - two-dimension array that we must fill
 * @return fail if memory allocate failed,
 */
static int create_board(Cell *cells[BOARD_SIZE]) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        cells[i] = malloc(sizeof(Cell));
        if (cells[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(cells[j]);
            }
            handle_error(ALLOCATION_ERROR_MASSAGE, NULL);
            return EXIT_FAILURE;
        }
        *(cells[i]) = (Cell) {i + 1, EMPTY, EMPTY};
    }

    for (int i = 0; i < NUM_OF_TRANSITIONS; i++) {
        int from = transitions[i][0];
        int to = transitions[i][1];
        if (from < to) {
            cells[from - 1]->ladder_to = to;
        } else {
            cells[from - 1]->snake_to = to;
        }
    }
    return EXIT_SUCCESS;
}

/**
 * fills database
 * @param markov_chain
 * @return EXIT_SUCCESS or EXIT_FAILURE
 */
static int fill_database(MarkovChain *markov_chain) {
    Cell *cells[BOARD_SIZE];
    if (create_board(cells) == EXIT_FAILURE) {
        return EXIT_FAILURE;
    }
    MarkovNode *from_node = NULL, *to_node = NULL;
    size_t index_to;
    for (size_t i = 0; i < BOARD_SIZE; i++) {
        add_to_database(markov_chain, cells[i]);
    }

    for (size_t i = 0; i < BOARD_SIZE; i++) {
        from_node = get_node_from_database(markov_chain,
                                           cells[i])->data;

        if (cells[i]->snake_to != EMPTY || cells[i]->ladder_to != EMPTY) {
            index_to = MAX(cells[i]->snake_to, cells[i]->ladder_to) - 1;
            to_node = get_node_from_database(markov_chain,
                                             cells[index_to])
                    ->data;
            add_node_to_counter_list(from_node,
                                     to_node, markov_chain);
        } else {
            for (int j = 1; j <= DICE_MAX; j++) {
                index_to = ((Cell *) (from_node->data))->number + j - 1;
                if (index_to >= BOARD_SIZE) {
                    break;
                }
                to_node = get_node_from_database(markov_chain,
                                                 cells[index_to])
                        ->data;
                add_node_to_counter_list(from_node,
                                         to_node, markov_chain);
            }
        }
    }
    // free temp arr
    for (size_t i = 0; i < BOARD_SIZE; i++) {
        free(cells[i]);
    }
    return EXIT_SUCCESS;
}

/**
 * this function prints a single cell
 * @param cell - the cell we want to print
 */
static void cell_print(Cell *cell) {
    if (cell->number == BOARD_SIZE)
    {
        printf("[%d]",BOARD_SIZE);
    }
    else if (cell->ladder_to != EMPTY) {
        printf("[%d]-ladder to %d -> ", cell->number, cell->ladder_to);
    } else if (cell->snake_to != EMPTY) {
        printf("[%d]-snake to %d -> ", cell->number, cell->snake_to);
    } else {
        printf("[%d] -> ", cell->number);
    }

}

/**
 * this function compares between two cells
 * @param first_cell - the first cell
 * @param second_cell - the second cell
 * @return 0 if the cells are the same, 1 if the first cell (num) is bigger
 * and -1 if the second cell is bigger
 */
static int cell_compare(Cell *first_cell, Cell *second_cell) {
    if(first_cell->number == second_cell->number)
    {
        return 0;
    }
    else if(first_cell->number > second_cell->number)
    {
        return 1;
    }
    else
    {
        return -1;
    }
}

/**
 * this function allocates memory for the new cell, and returns the new cell
 * the new cell is identify to the parameter
 * @param generic_ptr - the cell we got from the main
 * @return the new self (with the same attributes as the gotten cell)
 */
static Cell *cell_copy(Cell *generic_ptr) {
    Cell *new_cell = malloc(sizeof(Cell));
    if (new_cell == NULL) {
        return NULL;
    }
    *new_cell = (Cell) {generic_ptr->number, generic_ptr->ladder_to,
                        generic_ptr->snake_to};

    return new_cell;
}

/**
 * this function gets the cell and checks if its last cell
 * @param cell_ptr - the cell to check
 * @return true if the cell is last, false otherwise
 */
bool is_last_cell(Cell* cell_ptr)
{
    return (cell_ptr->number == BOARD_SIZE);
}

/**
 * this function gets the markov chain
 * and allocates a memory for every attribute in the struct
 * @param markov_chain - the markov chain we want to edit
 * @return failure if the allocation failed, success otherwise
 */
static int initialize_markov_chain_database(MarkovChain *markov_chain)
{
    markov_chain->database = malloc(sizeof(LinkedList));
    if (markov_chain->database == NULL) {
        printf(ALLOCATION_ERROR_MASSAGE);

        return EXIT_FAILURE;
    }

    markov_chain->print_func_markov_chain =(print_func) cell_print;
    markov_chain->comp_func_markov_chain = (comp_func) cell_compare;
    markov_chain->free_data_markov_chain = free;
    markov_chain->copy_func_markov_chain=(copy_func) cell_copy;
    markov_chain->is_last_markov_chain =(is_last) is_last_cell;
    markov_chain->database->first = NULL;
    markov_chain->database->last = NULL;
    markov_chain->database->size = 0;

    return EXIT_SUCCESS;
}

/**
 * this function prints to the user the path(s).
 * it continue (number_of_paths) times, and uses generate_random_sequence func
 * for each path.
 * @param markovChain - markov chain - holds the database
 * @param number_of_paths - number of paths we want to print
 */
static void create_path(MarkovChain * markovChain, int number_of_paths)
{
    MarkovNode *first = markovChain->database->first->data;
    int counter = 0;
    while(counter != number_of_paths)
    {
        printf("Random Walk %d: ", (counter + 1));
        generate_random_sequence(markovChain,
        first,MAX_GENERATION_LENGTH);
        counter++;
    }

}

/**
 * @param argc num of arguments
 * @param argv 1) Seed
 *             2) Number of sentences to generate
 * @return EXIT_SUCCESS or EXIT_FAILURE
 */
int main(int argc, char *argv[]) {
    if (initial_argument_tests(argc) != 0) {
        // first check if 2 args. if not, return EXIT_FAILURE
        return EXIT_FAILURE;
    } // arguments are OK
    int seed_long = (int) strtol(SEED, NULL, OUR_BASE);
    srand(seed_long);
    MarkovChain *markov_chain = malloc(sizeof(MarkovChain));
    if (markov_chain == NULL) {
        printf(ALLOCATION_ERROR_MASSAGE);
        return EXIT_FAILURE;
    }

    int res_initialize = initialize_markov_chain_database(markov_chain);
    if (res_initialize == EXIT_FAILURE)
    {
        free(markov_chain);
        markov_chain = NULL;
        return EXIT_FAILURE;
    }
    int filled_succeed = 0;
    int converted_number_of_paths
    = (int)strtol(NUMBER_OF_PATHS, NULL, OUR_BASE);
    filled_succeed = fill_database(markov_chain);
    if (filled_succeed) {
        free_markov_chain(&markov_chain);
        free(markov_chain->database);
        markov_chain->database = NULL;
        free(markov_chain);
        markov_chain = NULL;
        return EXIT_FAILURE;
    }
    create_path(markov_chain,
                converted_number_of_paths);

    free_markov_chain(&markov_chain);
    free(markov_chain->database);
    markov_chain->database = NULL;
    free(markov_chain);
    markov_chain = NULL;
    return EXIT_SUCCESS;
}