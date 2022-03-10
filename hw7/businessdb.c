#include "hashtable.h"
#include "string.h"
#include <stdio.h>
#define BUFFER 1024
int main() {
    char buf[BUFFER];
    char *email = NULL;
    char *name = NULL;
    char *fav_food = NULL;
    int shoe_size;
    FILE *infile;
    FriendNode *buckets[NUM_BUCKETS] = {NULL};
    infile = fopen("customers.tsv", "r");

    while (fgets(buf, BUFFER, infile) != NULL) {
        //split the info given from the line in the file
        char *token = strtok(buf, "\t");
        int count = 0;
        while (token != NULL) {
            printf("%s\n", token);
            count++;
            if (count == 1) {
                strcpy(email, token);
            }
            else if (count == 2) {
                strcpy(name, token);
            }
            else if (count == 3) {
                shoe_size = atoi(token);
            }
            else {
                strcpy(fav_food, token);
            }
            token = strtok(NULL, "\t");
        }
        //add a friend node to the hashtable with the given information
        add_friend_to_hashtable(email, name, fav_food, buckets, NUM_BUCKETS);
    }
    fclose(infile);

    while (1){
        char *command = NULL;
        getchar();
        fgets(command, BUFFER, stdin);

        if (strcmp(command, "add") == 0) {
            printf("email: ?\n");
            printf("name: ?\n");
            printf("testing: ?\n");
            //do the add function
        }
    }
}
