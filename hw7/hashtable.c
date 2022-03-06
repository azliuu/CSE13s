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

#define NUM_BUCKETS 10

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

  buckets[which_bucket] =
      add_friend_to_list(email, name, food, shoe_size, buckets[which_bucket]);

  printf("customer [%s] goes in bucket [%lu] \n", email, which_bucket);
}

char *fav_food_for_friend(char *email, FriendNode **buckets,
                          size_t num_buckets) {

  size_t which_bucket = hash(email) % num_buckets;

  char *result = NULL;
  FriendNode *node;
  node = buckets[which_bucket];

  while (node != NULL) {
    if (strcmp(node->email, email) == 0) {
      result = node->fav_food;
    }
    node = node->next;
  }
  return result;
}

char *name_of_friend(char *email, FriendNode **buckets, size_t num_buckets) {
  size_t which_bucket = hash(email) % num_buckets;

  char *result = NULL;
  FriendNode *node;
  node = buckets[which_bucket];

  while (node != NULL) {
    if (strcmp(node->email, email) == 0) {
      result = node->name;
    }
    node = node->next;
  }
  return result;
}

int shoe_size_of_friend(char *email, FriendNode **buckets, size_t num_buckets) {
  size_t which_bucket = hash(email) % num_buckets;

  int result = 0;
  FriendNode *node;
  node = buckets[which_bucket];

  while (node != NULL) {
    if (strcmp(node->email, email) == 0) {
      result = node->shoe_size;
    }
    node = node->next;
  }
  return result;
}

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

  char *fav_food = NULL;
  char *name = NULL;
  int shoe_size = 0;
  fav_food = fav_food_for_friend("h@gmail.com", buckets, NUM_BUCKETS);
  printf("fav food for henrietta: %s\n", fav_food);

  name = name_of_friend("h@gmail.com", buckets, NUM_BUCKETS);
  printf("name for harietta: %s\n", name);

  shoe_size = shoe_size_of_friend("h@gmail.com", buckets, NUM_BUCKETS);
  printf("shoe_size for hariette: %d\n", shoe_size);

  fav_food = fav_food_for_friend("s@gmail.com", buckets, NUM_BUCKETS);
  printf("fav food for sally: %s\n", fav_food);

  name = name_of_friend("s@gmail.com", buckets, NUM_BUCKETS);
  printf("name of sally: %s\n", name);

  fav_food = fav_food_for_friend("h1@gmail.com", buckets, NUM_BUCKETS);
  printf("fav food for hen1: %s\n", fav_food);

  name = name_of_friend("h1@gmail.com", buckets, NUM_BUCKETS);
  printf("name of hen1: %s\n", name);

  return 0;
}
