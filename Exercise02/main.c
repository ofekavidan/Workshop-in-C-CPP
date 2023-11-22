#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sort_bus_lines.h"
#include "test_bus_lines.h"

#define BUFFER_SIZE 63 // 20*3 + 2 commas + /0
#define WANTED_NUMBER_OF_ARGS 2
#define MIN_OF_LINES 1
#define LINE_NUMBER_MIN 1
#define LINE_NUMBER_MAX 999
#define DISTANCE_MIN 0
#define DISTANCE_MAX 1000
#define DURATION_MIN 10
#define DURATION_MAX 100

#define INITIAL_ARGS_ERROR "USAGE: Program arguments are 'bubble','test' or \
'quick'. Please enter one argument\n"
#define NUMBER_OF_LINES_ERROR "ERROR: Number of lines should \
be a positive integer\n"
#define LINE_NUMBER_ERROR "ERROR: line_number should be an\
 integer between 1 and 999 (includes)\n"
#define DISTANCE_ERROR "ERROR: distance should be an\
 integer between 0 and 1000 (includes)\n"
#define DURATION_ERROR "ERROR: duration should be an integer\
 between 10 and 100 (includes)\n"
#define NUMBER_OF_LINES_REQUEST "Enter number of lines. Then enter\n"
#define LINE_INFO_REQUEST "Enter line info. Then enter\n"
#define TEST_1_PASSED "TEST 1 PASSED: The array is sorted by distance\n"
#define TEST_1_FAILED "TEST 1 FAILED: The array is NOT sorted by distance\n"
#define TEST_2_PASSED "TEST 2 PASSED:\
 The array has the same items after sorting\n"
#define TEST_2_FAILED "TEST 2 FAILED:\
 The array has NOT the same items after sorting\n"
#define TEST_3_PASSED "TEST 3 PASSED: The array is sorted by duration\n"
#define TEST_3_FAILED "TEST 3 FAILED: The array is NOT sorted by duration\n"
#define TEST_4_PASSED "TEST 4 PASSED: \
The array has the same items after sorting\n"
#define TEST_4_FAILED "TEST 4 FAILED:\
 The array has NOT the same items after sorting\n"

/**
 * a function which checks if the initial arguments are bubble/quick/test
 * @param argc - the number of the initial arguments (given)
 * @param argv - the initial argument itself
 * @return success if we got one argument (bubble/quick/test),
 * failure otherwise
 */
int initial_argument_tests(int argc, char *argv[])
{
    if(argc != WANTED_NUMBER_OF_ARGS || \
    (strcmp(argv[1], "bubble") != 0 && \
    strcmp(argv[1], "quick") != 0 && \
    strcmp(argv[1], "test") != 0))
    {
        fprintf(stdout, INITIAL_ARGS_ERROR);
        return EXIT_FAILURE;
    }
    else
    {
        return EXIT_SUCCESS;
    }
}

/**
 * a function which checks if we got a positive number-of-lines
 * @param number_of_lines - the appropriate parameter
 * @return success if number-of-lines is positive, failure otherwise
 */
int valid_number_of_lines(int number_of_lines)
{
    if (number_of_lines < MIN_OF_LINES)
    {
        fprintf(stdout,NUMBER_OF_LINES_ERROR);
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

/**
 * a function which checks every one of the three-input that
 * were given is valid
 * @param line_number - line number
 * @param distance - distance
 * @param duration - duration
 * @return success if:
 * line-number is between 1-999, AND distance between 0-1000,
 * AND duration between 10-100.
 * failure otherwise.
 */
int valid_inputs(int line_number, int distance, int duration)
{
    if (line_number < LINE_NUMBER_MIN || line_number > LINE_NUMBER_MAX)
    {
        fprintf(stdout,LINE_NUMBER_ERROR);
        return EXIT_FAILURE;
    }
    if (distance < DISTANCE_MIN || distance > DISTANCE_MAX)
    {
        fprintf(stdout,DISTANCE_ERROR);
        return EXIT_FAILURE;
    }
    if (duration < DURATION_MIN || duration > DURATION_MAX)
    {
        fprintf(stdout,DURATION_ERROR);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;

}

/**
 * a function which gets from standard input the number of lines
 * it keeps asking for a valid number of lines if we got a non-valid one
 * @return number of lines (valid)
 */
int input_number_of_lines()
{
    int number_of_lines = 0;
    char first_buffer[BUFFER_SIZE]; //
    fprintf(stdout,NUMBER_OF_LINES_REQUEST);
    fgets(first_buffer, BUFFER_SIZE, stdin);
    sscanf(first_buffer,"%d",&number_of_lines);
    while (valid_number_of_lines(number_of_lines) != 0)
    {
        fprintf(stdout, NUMBER_OF_LINES_REQUEST);
        fgets(first_buffer, BUFFER_SIZE, stdin);
        sscanf(first_buffer,"%d",&number_of_lines);
    }

    return number_of_lines;
}

/**
 * a function which actually build the bus array
 * it uses input_number_of_lines function above to get a valid one
 * then creates a dynamic array of BusLine
 * at the end, it continue asking for an N valid BusLines,
 * for the crated array.
 * @return the array itself, if we succeeded to find memory for him
 * pointer to NULL otherwise
 */
BusLine * build_bus_array(int number_of_lines)
{
    int line_number = 0, distance = 0, duration = 0;
    BusLine* bus_array = calloc(number_of_lines, sizeof(BusLine));
    if(bus_array == NULL)
    {
        return NULL;
    }
    else
    {
        int counter = 0; // initial boot
        char second_buffer[BUFFER_SIZE];
        while (counter != number_of_lines)
        {
            fprintf(stdout, LINE_INFO_REQUEST);
            fgets(second_buffer, BUFFER_SIZE, stdin);
            sscanf(second_buffer,"%d,%d,%d",
                   &line_number,&distance,&duration);
            if(valid_inputs(line_number, distance, duration) == 0)
            {
                BusLine new_bus = {line_number, distance, duration};
                bus_array[counter] = new_bus;
                counter++;
            }
        }
    }
    return bus_array;
}

/**
 * this function gets the number of lines
 * creates an array of N BusLines (uses build_bus_array func.)
 * then uses bubble sort and print the sorted bus array,
 * as said, sorted by distance
 * @param number_of_lines - number of lines
 * @return success if the function found enough memory for the array,
 * failure otherwise
 */
int bubble_run(int number_of_lines)
{
    BusLine* bus_array = build_bus_array(number_of_lines);
    if (bus_array == NULL)
    {
        return EXIT_FAILURE;
    }
    else
    {
        bubble_sort(bus_array, bus_array + number_of_lines);

        for (int i = 0; i < number_of_lines; ++i) {
            fprintf(stdout, "%d,%d,%d\n",
                    (bus_array)[i].line_number,
                    (bus_array)[i].distance, (bus_array)[i].duration);
        }
        free(bus_array);
        return EXIT_SUCCESS;
    }
}


/**
 * this function gets the number of lines
 * creates an array of N BusLines (uses build_bus_array func.)
 * then uses quick sort and print the sorted bus array,
 * as said, sorted by duration
 * @param number_of_lines - number of lines
 * @return success if the function found enough memory for the array,
 * failure otherwise
 */
int quick_run(int number_of_lines)
{
    BusLine* bus_array = build_bus_array(number_of_lines);
    if (bus_array == NULL)
    {
        return EXIT_FAILURE;
    }
    else
    {
        quick_sort(bus_array, bus_array + number_of_lines);

        for (int i = 0; i < number_of_lines; ++i) {
            fprintf(stdout, "%d,%d,%d\n",
                    (bus_array)[i].line_number,
                    (bus_array)[i].distance, (bus_array)[i].duration);
        }
        free(bus_array);
        return EXIT_SUCCESS;
    }
}

/**
 * this function uses is_sorted_by_distance func from test_bus_lines
 * it prints PASSED if the array is sorted (non-decreasing) by distance
 * it prints FAILED otherwise
 * @param number_of_lines - number of lines
 * @param source - the array we want to check
 */
void test_run1(int number_of_lines, BusLine* source) {
    if(is_sorted_by_distance(source, source+number_of_lines) == 1) {
        fprintf(stdout, TEST_1_PASSED);
    }
    else {
        fprintf(stdout, TEST_1_FAILED);
    }
}

/**
 * this function runs is_equal func. from test_bus_lines
 * prints PASSED if two arrays are equal except order
 * prints FAILED otherwise
 * @param number_of_lines - number of lines
 * @param dest - the copy of the original array
 * @param source - the array that we sorted by bubble-sort
 */
void test_run2(int number_of_lines, BusLine* source, BusLine* dest) {
    if(is_equal(source, source+number_of_lines,
                dest, dest+number_of_lines) == 1) {
        fprintf(stdout, TEST_2_PASSED);
    }
    else {
        fprintf(stdout, TEST_2_FAILED);
    }
}

/**
 * this function uses is_sorted_by_duration func from test_bus_lines
 * it prints PASSED if the array is sorted (non-decreasing) by duration
 * it prints FAILED otherwise
 * @param number_of_lines - number of lines
 * @param source - the array we want to check
 */
void test_run3(int number_of_lines, BusLine* source) {
    if(is_sorted_by_duration(source, source+number_of_lines) == 1) {
        fprintf(stdout, TEST_3_PASSED);
    }
    else {
        fprintf(stdout, TEST_3_FAILED);
    }
}

/**
 * this function runs is_equal func. from test_bus_lines
 * prints PASSED if two arrays are equal except order
 * prints FAILED otherwise
 * @param number_of_lines - number of lines
 * @param dest - the copy of the original array
 * @param source - the array that we sorted by quick-sort
 */
void test_run4(int number_of_lines, BusLine* source, BusLine* dest) {
    if(is_equal(source, source+number_of_lines,
                dest, dest+number_of_lines) == 1){
        fprintf(stdout, TEST_4_PASSED);
    }
    else {
        fprintf(stdout, TEST_4_FAILED);
    }
}


/**
 * @param number_of_lines - number of lines
 * @return success if the function found enough memory for the array,
 * failure otherwise
 */
int test_run(int number_of_lines)
{
    BusLine* source = build_bus_array(number_of_lines);
    if (source == NULL) {
        return EXIT_FAILURE;
    }
    else {
        BusLine* dest = calloc(number_of_lines, sizeof(BusLine));

        if (dest == NULL)
        {
            return EXIT_FAILURE;
        }
        for (int i = 0; i < number_of_lines; i++)
        {
            memcpy(dest+i, source+i, sizeof(BusLine));
        }

        bubble_sort(source, source+number_of_lines);
        test_run1(number_of_lines, source);
        test_run2(number_of_lines, source, dest);

        quick_sort(source, source+number_of_lines);
        test_run3(number_of_lines, source);
        test_run4(number_of_lines, source, dest);

        free(dest);
        free(source);
    }
    return EXIT_SUCCESS;
}



/**
 * the main function of the program.
 * first checks (uses initial_argument_tests func.) if the
 * initial args are valid.
 * then, gets the number of lines from standard input (uses
 * input_number_of_lines func.)
 * at the end, decide by the appropriate value from the only argument,
 * which program to run (bubble/quick/test)
 */
int main (int argc, char *argv[]) {
    if (initial_argument_tests(argc, argv) != 0)
    {
        return EXIT_FAILURE;
    }
    else
    {
        int number_of_lines = input_number_of_lines();
        if(strcmp(argv[1], "bubble") == 0)
        {
            return bubble_run(number_of_lines);
        }
        else if(strcmp(argv[1], "quick") == 0)
        {
            return quick_run(number_of_lines);
        }
        else if(strcmp(argv[1], "test") == 0)
        {
            return test_run(number_of_lines);
        }
        return EXIT_SUCCESS;
    }

}