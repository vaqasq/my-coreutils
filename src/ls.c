// Implement the following flags: -R for recursive, -l for listing info, -A for all (not . and ..), as well as many folders as listed. 
// While ls takes files and simply returns them, I think I will choose to error if given a file.

#include <sys/resource.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>


int main(int argc, char *argv[]){

    // Flags, R, l, A
    bool recursiveFlag, longInfoFlag, allFlag; 
    char* flag_str = "RlA";

    int opt;
    while ((opt = getopt(argc, argv, flag_str)) != -1){
        switch (opt){
            case 'R':
                recursiveFlag = true;
                break;
            case 'l':
                longInfoFlag = true;
                break;
            case 'A':
                allFlag = true;
                break;
        }
    }

    // global var optind, an index into argv, is now the directories;
    if (optind >= argc) {
        fprintf(stderr, "Expected argument after options\n");
        return EXIT_FAILURE; 
    }
    
    // Type should problably be what opendir returns instead;
    DIR **directoriesArr = malloc((argc-1) * sizeof(DIR *));
    int numDirectoriesEntries = 0;

    DIR *currDirFlag;

    for (int i = optind; i < argc; ++i){

        currDirFlag = opendir(argv[i]);

        if (NULL == currDirFlag){
            perror("");
            return EXIT_FAILURE;
        }

        directoriesArr[numDirectoriesEntries++] = currDirFlag;
        
    }

    // work with dirs, using flags;

    // closing open directories
    for (int i = 0; i < numDirectoriesEntries; ++i){
        closedir(directoriesArr[i]);
    }

    return EXIT_SUCCESS;
}
