#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct FriendNode {
  char *email;    // the key
  char *name;     // values
  char *fav_food; // values
  int shoe_size;  // values
  struct FriendNode *next;
} FriendNode;

#define NUM_BUCKETS 15

// Thank you Dan Bernstein.
unsigned long hash(char *str) {
  unsigned long hash = 5381;
  int c;

  while (*str != '\0') {
    c = *str;
    hash = ((hash << 5) + hash) + (unsigned char)c; /* hash * 33 + c */
    str++;
  }
  return hash;
}

FriendNode *add_friend_to_list(char *email, char *name, char *food,
                               int shoe_size, FriendNode *bucket) {
  FriendNode *new_friend;
  new_friend = malloc(sizeof(FriendNode));
  new_friend->email = strdup(email);
  new_friend->name = strdup(name);
  new_friend->fav_food = strdup(food);
  new_friend->shoe_size = shoe_size;
  new_friend->next = bucket;
  return new_friend;
}

void add_friend_to_hashtable(char *email, char *name, char *food, int shoe_size,
                             FriendNode **buckets, size_t num_buckets) {

  size_t which_bucket = hash(email) % num_buckets;
  FriendNode *node;
  int found = 0;
  for (size_t i = 0; i < num_buckets; i++) {
    node = buckets[i];
    while (node != NULL) {
      if (strcmp(node->email, email) == 0) {
        node->name = strdup(name);
        node->fav_food = strdup(food);
        node->shoe_size = shoe_size;
        found = 1;
      }
      node = node->next;
    }
  }
  if (found == 0) {
  buckets[which_bucket] = add_friend_to_list(email, name, food, shoe_size,
                                                   buckets[which_bucket]);
  }

  // debug check for collisions
  printf("customer [%s] goes in bucket [%lu] \n", email, which_bucket);
}

bool delete_friend(char *email, FriendNode **buckets, size_t num_buckets) {
    size_t which_bucket = hash(email) % num_buckets;
    FriendNode *node;
    node = buckets[which_bucket];

    //DELETE FIRST CASE (only one node in the linked list)
    if (node->next == NULL) {
        if (strcmp(node->email, email) == 0) {
            free(node->email);
            free(node->name);
            free(node->fav_food);
            node->shoe_size = 0;
            free(node);
            return true;
        }
    }

    //DELETE SECOND CASE (delete parent from linked list with more than one node).
    else if (strcmp(node->email, email)  == 0) {
        buckets[which_bucket] = node->next;
        free(node->email);
        free(node->name);
        free(node->fav_food);
        node->shoe_size = 0;
        free(node);
        return true;
    }
    // DELETE THIRD CASE (deleting a node in the middle)
    else {
        FriendNode *current = node;
        FriendNode *prev = NULL;
        while (strcmp(current->email, email) != 0) {
            prev = current;
            //maybe *prev = *current
            current = current->next;
        }
        if (current == NULL) {
            printf("user not found!\n");
        } else {
            prev->next = current->next;
            free(current->email);
            free(current->name);
            free(current->fav_food);
            current->shoe_size = 0;
            free(current);
            return true;
        }
    }
    return false;
}


bool lookup_customer_info(char *email, FriendNode **buckets,
                          size_t num_buckets) {
  size_t which_bucket = hash(email) % num_buckets;
  int shoe_size = 0;
  char *name = NULL;
  char *food = NULL;

  FriendNode *node;
  node = buckets[which_bucket];

  while (node != NULL) {
    if (strcmp(node->email, email) == 0) {
      shoe_size = node->shoe_size;
      name = node->name;
      email = node->email;
      food = node->fav_food;
    }
    node = node->next;
  }
  // IF THE NAME WAS REPLACED BY A VALUE FOUND IN HASHTABLE
  if (name != NULL) {
    printf("email: %s\n", email);
    printf("name: %s\n", name);
    printf("shoesize: %d\n", shoe_size);
    printf("food: %s\n", food);
    printf("\n");
    return true;
  } else {
    // the user was not found because default value was not replaced
    printf("user not found!\n");
  }
  return false;
}

void list_customers(FriendNode **buckets, size_t num_buckets) {
  for (size_t i = 0; i < num_buckets; i++) {
    FriendNode *node;
    node = buckets[i];
    while (node != NULL) {
      lookup_customer_info(node->email, buckets, num_buckets);
      node = node->next;
    }
  }
}

// TESTING FOR EACH HASH FUNCTION
/*
int main(void) {

  unsigned long hashed;

  // array of pointers to FriendNode because they might be null.
  FriendNode *buckets[NUM_BUCKETS] = {NULL};

  add_friend_to_hashtable("j@gmail.com", "jimmothy", "gfuel", 10, buckets,
                          NUM_BUCKETS);
  add_friend_to_hashtable("h@gmail.com", "henrietta", "borgar", 11, buckets,
                          NUM_BUCKETS);
  add_friend_to_hashtable("h@gmail.com", "henrietta", "borgar", 11, buckets,
                          NUM_BUCKETS);
  add_friend_to_hashtable("h1@gmail.com", "henrietta1", "borgar", 11, buckets,
                          NUM_BUCKETS);
  add_friend_to_hashtable("a@gmail.com", "alex", "hummus", 12, buckets,
                          NUM_BUCKETS);
  add_friend_to_hashtable("r@gmail.com", "robert", "tacos", 13, buckets,
                          NUM_BUCKETS);
  add_friend_to_hashtable("s@gmail.com", "sally", "roti", 14, buckets,
                          NUM_BUCKETS);

  // LOOKUP FUNCTION TESTS
  printf("LOOKUP FUNCTION TESTS\n");

  printf("bool output expected 1 got:  %d\n",
         lookup_customer_info("h@gmail.com", buckets, NUM_BUCKETS));

  printf("bool output expected user doesn't exist and 0 got: %d\n",
         lookup_customer_info("test", buckets, NUM_BUCKETS));

  // DELETE TESTS
  printf("DELETE TESTS\n");
    printf("delete output expected 1 got: %d\n", delete_friend("h@gmail.com",
    buckets, NUM_BUCKETS));
    //code breaks here.
    printf("lookup after delete expected 0 got: %d\n",
    lookup_customer_info("h@gmail.com", buckets, NUM_BUCKETS));

  // LIST CUSTOMER TESTS
  printf("LIST CUSTOMER TESTS\n");
  list_customers(buckets, NUM_BUCKETS);
  return 0;
}
 */
