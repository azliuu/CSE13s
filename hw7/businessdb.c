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
        token = strtok(NULL, "\t");
        email = token;
        token = strtok(buf, "\t");
        token = strtok(NULL, "\t");
        name = token;
        token = strtok(buf, "\t");
        token = strtok(NULL, "\t");
        shoe_size = atoi(token);
        token = strtok(buf, "\t");
        token = strtok(NULL, "\t");
        fav_food = token;
        //add a friend node to the hashtable with the given information
        add_friend_to_hashtable(email, name, fav_food, buckets, NUM_BUCKETS);
    }
    fclose(infile);

    while (1){
        char *command = NULL;
        getchar();
        fgets(command, BUFFER, stdin);
        if (strcmp(command, "quit") == 0) {
            break;
        }
        else if (strcmp(command, "save") == 0) {
            FILE *outfile;
            outfile = fopen("customers.tsv", "w");
            // for every customer node, print out it's stuff to the file.
            //borrowing list logic
            for (size_t i = 0; i < NUM_BUCKETS; i++) {
                FriendNode *node;
                node = buckets[i];
                while (node != NULL) {
                    char *line = ("%s\t%s\t%s\t%s", node->email, node->name, atoi(node->shoe_size), node->fav_food);
                    fputs(line, outfile);
                    node = node->next;
                }
            }
            fclose(outfile);
        }
        else if (strcmp(command, "add") == 0) {
            printf("email address? \n");
            getc();
            fgets(email, 1024, stdin);

            printf("name? \n");
            getc();
            fgets(name, 1024, stdin);

            printf("shoe size? \n");
            getc();
            fgets(shoe_size, 1024, stdin);

            printf("favorite food? \n");
            getc();
            fgets(fav_food, 1024, stdin);

            add_friend_to_hashtable(email, name, fav_food, buckets, NUM_BUCKETS);
        }
        else if (strcmp(command, "lookup") == 0) {
            printf("email address? \n");
            getc();
            fgets(email, 1024, stdin);
            lookup_customer_info(email, buckets, NUM_BUCKETS);
        }
        else if (strcmp(command, "delete") == 0) {
            printf("email address? \n");
            getc();
            fgets(email, 1024, stdin);
            delete_friend(email, buckets, NUM_BUCKETS);
        }
        else if (strcmp(command, "list") == 0) {
            list_customers(buckets, NUM_BUCKETS);
        }
        else {
            print("unknown command.\n");
        }
    }
}
