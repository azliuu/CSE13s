#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NUM_BUCKETS 10

typedef struct FriendNode {
  char *email;
  char *name;
  char *fav_food;
  int shoe_size;
  struct FriendNode *next;
} FriendNode;

unsigned long hash(char *str);

FriendNode *add_friend_to_list(char *email, char *name, char *food,
                               FriendNode *bucket);

void add_friend_to_hashtable(char *email, char *name, char *food,
                             FriendNode **buckets, size_t num_buckets);

char *fav_food_for_friend(char *email, FriendNode **buckets,
                          size_t num_buckets);
