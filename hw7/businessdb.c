#include "businessdb.h"
#include <stdio.h>

char create_customer() {}

int main(int argc, char **argv) {
  char buf[512];
  FILE *infile;

  if (argc != 2) {
    fprintf(stderr, "usage: ./businessdb <command>");
    exit(1);
  }
  // if the user specifies the "add" command
  if (argv[1] == "add") {
    char email;
    char name;
    char food;
    int shoe_size;
    // asks user for their info, stores it in these variables.
    printf("Email Address?: ");
    fgets("%s", % email);

    printf("Display Name?: ");
    fgets("%s", % name);

    printf("Shoe Size?: ");
    fgets("%d", % shoe_size);

    printf("Favorite Food?: ");
    fgets("%s", &food);
  }
  infile = fopen("customers.tsv", "w");

  fclose(infile);
}
