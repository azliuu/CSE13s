#include "names.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
  int num_players = 0;
  printf("How many players? ");
  scanf(" %d", &num_players);

  if (num_players < 2 || num_players > 10) {
    fprintf(stderr, "Invalid number of players. Using 2 instead.\n");
    num_players = 2;
  }

  unsigned int seed_num = 0;
  printf("Random seed: ");
  scanf("%d", &seed_num);

  if (seed_num < 0 || seed_num > UINT_MAX) {
    fprintf(stderr, "Invalid random seed. Using 2022 isntead.\n");
    seed_num = 2022;
  }

  srandom(seed_num);

  int player_points[num_players];
  for (int i = 0; i < num_players; i++) {
    player_points[i] = 0;
  }

  for (int i = 0; i < num_players; i++) {
    int roll = 0;
    printf("%s", names[i]);
    printf(" rolls the pig...");
    while (player_points[i] < 100) {
      roll = random() % 7 + 1;
      if (roll == 1 || roll == 2) {
        printf(" pig lands on side");
        if (i == num_players - 1) {
          i = 0;
          printf("\n");
          printf("%s", names[i]);
          printf(" rolls the pig...");
        } else {
            i +=1;
          printf("\n");
          printf("%s", names[i]);
          printf(" rolls the pig...");
        }
      }
      if (roll == 3) {
        printf(" pig lands on back");
        player_points[i] += 10;
      }
      if (roll == 4) {
        printf(" pig lands upright");
        player_points[i] += 10;
      }
      if (roll == 5) {
        printf(" pig lands on snout");
        player_points[i] += 15;
      }
      if (roll == 6 || roll == 7) {
        printf(" pig lands on ear");
        player_points[i] += 5;
      }
    }

    if (player_points[i] >= 100) {
      printf("\n");
      printf("%s wins with %d points!\n", names[i], player_points[i]);
      return 0;
    }
  }
}
