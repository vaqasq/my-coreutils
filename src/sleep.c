#include <stdio.h>
#include <stdlib.h>

/* Goals
 * Accept number that defaults to second
 * Accept number that ends with either s,m,h, or d for unit
 * Both previous + be able to process infinite && for additional commands
 */

int main(int argc, char* argv[]){

    if (argc == 1){
        char* err = "Sleep requires at least one argument. See man page.";
        fprintf(stderr, "%s\n", err);
    }

    return EXIT_SUCCESS;
}
