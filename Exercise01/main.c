#include "cipher.h"
#include "tests.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"

#define MAX_LEN 1028
#define OURBASE 10
#define FIRST_CASE 5
#define SECOND_CASE 2

/**
 * a func. which checks command, k, and both paths we got
 * @param argv - command, k, and both paths we got
 * @return success if passed all the test, failure otherwise
 */
int checks_the_four_case(char *argv[])
{
    if(strcmp(argv[1], "decode") != 0 && \
    strcmp(argv[1], "encode") != 0) { // first, check the command
        // the command isn't valid
        fprintf(stderr, "The given command is invalid.\n");
        return EXIT_FAILURE;
    }
    else { // the command is OK
        // now we want to check k
        char* end_pnt;
        long str_to_long = strtol(argv[2], &end_pnt,OURBASE);
        // conditions: if k include non-digits, if k isn't integer, if k empty
        if (strcmp(end_pnt, "") != 0 || \
        str_to_long != (int)str_to_long || strcmp(argv[2], "") == 0)
        {
            fprintf(stderr, "The given shift value is invalid.\n");
            return EXIT_FAILURE;
        }
        else { // the k is OK
            // check if the paths are appropriate
            FILE *input = fopen(argv[3], "r");
            FILE *output = fopen(argv[4], "w");
            // if one of them not, we should close the good one
            if (input == NULL || output == NULL) {
                if (input != NULL) {
                    fclose(input);
                }
                if (output != NULL) {
                    fclose(output);
                }
                fprintf(stderr, "The given file is invalid.\n");
                return EXIT_FAILURE; // appropriate message and exit
            }
            else { // if paths are ok, then everything is ok
                fclose(input);
                fclose(output);
                return EXIT_SUCCESS;
            }
        }
    }
}

/**
 * when we got one parameter, we check all the tests we made earlier
 * @return failure if one of the tests didn't pass, success otherwise
 */
int output_for_second_case()
{
    if (test_encode_non_cyclic_lower_case_positive_k() != 0 \
        || test_encode_cyclic_lower_case_special_char_positive_k() != 0 \
        || test_encode_non_cyclic_lower_case_special_char_negative_k() != 0 \
        || test_encode_cyclic_lower_case_negative_k() != 0 \
        || test_encode_cyclic_upper_case_positive_k() != 0 \
        || test_decode_non_cyclic_lower_case_positive_k() != 0 \
        || test_decode_cyclic_lower_case_special_char_positive_k() != 0 \
        || test_decode_non_cyclic_lower_case_special_char_negative_k() != 0 \
        || test_decode_cyclic_lower_case_negative_k() != 0 \
        || test_decode_cyclic_upper_case_positive_k() != 0)

    {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

/**
 * uses all side-functions to finally encode/decode the input
 * @param argc - number of parameters we got
 * @param argv - the parameters themselves
 * @return failure if one of the tests didn't pass, success otherwise
 */
int main (int argc, char *argv[])
{
    if (argc == FIRST_CASE) {
        if(checks_the_four_case(argv) == 0) { // if all four conditions are OK
            FILE *input = fopen(argv[3], "r");
            FILE *output = fopen(argv[4], "w");
            char buffer[MAX_LEN];
            char* end_pnt;
            long str_to_long = strtol(argv[2], &end_pnt,OURBASE);
            // divide to cases, then just like on TA, write into the output
            if (strcmp(argv[1], "encode") == 0) {
                while (fgets(buffer, MAX_LEN, input)) {
                    encode(buffer, (int)str_to_long);
                    fputs(buffer, output);
                }
            }
            else {
                while (fgets(buffer, MAX_LEN, input)) {
                    decode(buffer, (int)str_to_long);
                    fputs(buffer, output);
                }
            }
        }
        else { // if one of our condition isn't OK
            return EXIT_FAILURE;
        }

    }
    else if (argc == SECOND_CASE) { // case two, only one parameter ("test")
        if (strcmp(argv[1], "test") != 0) {
            fprintf(stderr, "Usage: cipher test\n");
            return EXIT_FAILURE;
        }
        else {
            return output_for_second_case();
        }
    }
    else { // if we got k parameter s.t k isn't 1 or 4
        fprintf(stderr, "The program receives 1 or 4 arguments only.\n");
        return EXIT_FAILURE;
    }
}
