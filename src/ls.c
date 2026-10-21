// Implement the following flags: -R for recursive, -l for listing info, as well as many folders as listed. 
// While ls takes files and simply returns them, I think I will choose to error if given a file.

#include <sys/resource.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

void printDir(DIR *dir, char *dirName);

int main(int argc, char *argv[]){

    // Hardcode just ./ls

    if (argc == 1){
        DIR* currDir = opendir(".");

        printDir(currDir, "Current Dir");
        return EXIT_SUCCESS;
    }

    // Flags, R, l
    bool recursiveFlag, longInfoFlag; 
    char* flag_str = "Rl";

    int opt;
    while ((opt = getopt(argc, argv, flag_str)) != -1){
        switch (opt){
            case 'R':
                recursiveFlag = true;
                break;
            case 'l':
                longInfoFlag = true;
                break;
            case '?':
                fprintf(stderr, "Improper flag. See man page.\n");
                return EXIT_FAILURE;
        }
    }

    // global var optind, an index into argv, is now the directories;

    // Assume size 1 for now, otherwise realloc
    DIR **directoriesArr = malloc(sizeof(DIR*));
    char **directoriesNameArr = malloc(sizeof(char*));
    // The number of directory entries will be the same for both their DIR* and their names
    int numDirectoryEntries;

    // If no specific folders were provided, assume it is just the current folder
    if (optind >= argc) {

        numDirectoryEntries = 1;
        directoriesArr[0] = opendir(".");
        directoriesNameArr[0] = malloc((strlen("Current Dir") + 1) * sizeof(char));
        strcpy(directoriesNameArr[0], "Current Dir");

    }
    // Else, there are other options that need to be acted upon;
    else {

        directoriesArr = realloc(directoriesArr, (argc-1) * sizeof(DIR *));
        numDirectoryEntries = 0;

        DIR *currDirFlag;
        for (int i = optind; i < argc; ++i){

            currDirFlag = opendir(argv[i]);

            if (NULL == currDirFlag){
                fprintf(stderr, "Error opening file '%s': %s\n", argv[i], strerror(errno));
                return EXIT_FAILURE;
            }

            directoriesArr[numDirectoryEntries] = currDirFlag;

            // Add name aswell

            directoriesNameArr[numDirectoryEntries] = malloc((strlen(argv[i]) + 1) * sizeof(char));
            strcpy(directoriesNameArr[numDirectoryEntries], argv[i]);

            numDirectoryEntries++;

        }

    }

    // work with dirs, using flags: l, R. Make reusable functions so recursive search is easy as well as long


    // closing open directories
    for (int i = 0; i < numDirectoryEntries; ++i){
        closedir(directoriesArr[i]);
    }

    return EXIT_SUCCESS;
}

void printDir(DIR *dir, char *dirName){

    printf("%s:\n", dirName);

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL){
        if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, ".."))
            printf("%s   ", entry->d_name);
    }
    printf("\n");
}

