#include "cipher.h"

/// IN THIS FILE, IMPLEMENT EVERY FUNCTION THAT'S DECLARED IN cipher.h.
#define LOWER_A_ASCII 97
#define LOWER_Z_ASCII 122
#define UPPER_A_ASCII 65
#define UPPER_Z_ASCII 90
#define NUM_OF_LET 26
#define UPPER_A_MINUSONE 64
#define LOWER_A_MINUSONE 96

// See full documentation in header file
void encode (char s[], int k)
{
    int i = 0; // running index of s
    int converter = 0; // initial boot, converting char-int
    while(s[i] != '\0') // will run until the end of the string
    {
        if (s[i] >= LOWER_A_ASCII && s[i] <= LOWER_Z_ASCII) // if s[i] is a-z
        {
            while (k < 0) {
                k = NUM_OF_LET + k; // makes % on c act like mod on calculator
            }
            // like a field on math, we'll use mod 26 and then add 97
            converter = (k % NUM_OF_LET) + s[i]; // exmp: 27%26+97=98
            while (!(converter >= LOWER_A_ASCII && converter <= LOWER_Z_ASCII))
            {
                converter = ((converter - LOWER_A_ASCII) % NUM_OF_LET) \
                        + LOWER_A_ASCII; // keeps converter between a-z
            }
            char temp  = (char)(converter); // convert back to char
            s[i] = temp; // update appropriate index on s
        }
        if (s[i] >= UPPER_A_ASCII && s[i] <= UPPER_Z_ASCII) // if s[i] is A-Z
        {
            while (k < 0) {
                k = NUM_OF_LET + k; // makes % on c act like mod on calculator
            }
            converter = (k % NUM_OF_LET) + s[i]; // exmp: 27%26+97=98
            while (!(converter >= UPPER_A_ASCII && converter <= UPPER_Z_ASCII))
            {
                converter = ((converter - UPPER_A_ASCII) % NUM_OF_LET) \
                + UPPER_A_ASCII; // keeps converter between A-Z
            }
            char temp  = (char)(converter); // convert back to char
            s[i] = temp; // update appropriate index on s
        }
        i++; // uppers the running index of s
    }
}

// See full documentation in header file
void decode (char s[], int k)
{
    int i = 0; // running index of s
    int converter = 0; // initial boot, converting char-int
    while(s[i] != '\0') // will run until the end of the string
    {
        if (s[i] >= LOWER_A_ASCII && s[i] <= LOWER_Z_ASCII) // if s[i] is a-z
        {
            while (k < 0) {
                k = NUM_OF_LET + k; // makes % on c act like mod on calculator
            }
            converter = s[i] - (k % NUM_OF_LET); // exmp. 98-(27%26)=97
            while (!(converter >= LOWER_A_ASCII && converter <= LOWER_Z_ASCII))
            {
                if(converter < LOWER_A_ASCII) { // keeps conv between a-z
                    converter = LOWER_Z_ASCII - (LOWER_A_MINUSONE-converter);
                }
            }
            char temp  = (char)(converter); // converts back to char
            s[i] = temp; // updates appropriate index of s
        }
        if (s[i] >= UPPER_A_ASCII && s[i] <= UPPER_Z_ASCII) // if s[i] is A-Z
        {
            while (k < 0) {
                k = NUM_OF_LET + k; // makes % on c act like mod on calculator
            }
            converter = s[i] - (k % NUM_OF_LET); // exmp. 98-(27%26)=97
            while (!(converter >= UPPER_A_ASCII && converter <= UPPER_Z_ASCII))
            {
                if(converter < UPPER_A_ASCII) { // keeps conv between A-Z
                    converter = UPPER_Z_ASCII - (UPPER_A_MINUSONE-converter);
                }
            }
            char temp  = (char)(converter); // converts back to char
            s[i] = temp; // updates appropriate index of s
        }
        i++; // uppers the running index of s
    }
}
