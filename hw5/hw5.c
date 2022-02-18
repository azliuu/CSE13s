#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
// extra include
#include <ctype.h>

// Returns true if the guess is an exact match with the secret word, but
// more importantly, fills in the result with the following:
// - 'x' goes in a slot if the corresponding letter in the guess does not appear
//   anywhere in the secret word
// - 'y' goes in a slot if the corresponding letter in the guess appears in the
//   secret word, but not in the corresponding slot
// - 'g' goes in a slot if the corresponding letter in the guess appears in the
//   corresponding slot in the secret word.
//   You can assume that result points at enough memory for a string of length
//   5. (ie, at least 6 bytes long)
bool score_guess(char *secret, char *guess, char *result) {
  // TODO(you): finish this function
  /*
  char low_secret = strdup(secret);
  for (int k = 0; k < low_secret; k++) {
      low_secret[k] = tolower(secret[k]);
  }
  char low_guess = strdup(guess);
  for (int l = 0; l < low_guess; l++) {
      low_guess[l] = tolower(guess[l]);
  }
  */
  for (int i = 0; secret[i] != '\0'; i++) {
      for (int j = 0; guess[j] != '\0'; j++) {
          guess[j] = tolower(guess[j]);
          secret[i] = tolower(secret[i]);
        if ((secret[i] != guess[i]) && (secret[i] != guess[j])) {
          result[i] = 'x';
        }
        if ((secret[i] != guess[i]) && (guess[j] == secret[i])) {
          result[i] = 'y';
        }
        if (secret[i] == guess[j])
          result[i] = 'g';
        }
        if (strcmp(secret, guess) == 0) {
            return true;
        }
  }
  return false;
}

// Returns true if the specified guess is one of the strings in the vocabulary,
// and false otherwise. num_words is the length of the vocabulary.
// A simple linear scan over the strings in vocabulary is fine for our purposes,
// but consider: could you do this search more quickly?
bool valid_guess(char *guess, char **vocabulary, size_t num_words) {
  // TODO(you): finish this function
  for (int i = 0; i != '\0'; i++) {
      guess[i] = tolower(guess[i]);
  }
  for (unsigned long i = 0; i < num_words; i++) {
      if (strcmp(guess, vocabulary[i]) == 0) {
          return true;
      }
  }
  return false;
}

// Returns an array of strings (so, char **), where each string contains a word
// from the specified file. The file is assumed to contain 5-letter words, one
// per line.
// Also, this function sets the value pointed at by *num_words to be the number
// of words read.
// This will need to allocate enough memory to hold all of the char* pointers --
// so you will keep track of the size of your char** array and then use realloc
// to make the array larger over time, so that you have enough space for the
// dynamically-growing array of char *.
// Use fopen to open the input file for reading,
// strdup (or strndup) to make copies of each word read from that file, and
// fclose to close the file when you are done reading from it.
// Each element of the array should be a single five-letter word,
// null-terminated.
char **load_vocabulary(char *filename, size_t *num_words) {
  char **out = NULL;
  //TODO(you): finish this function
  char buf[1024];
  FILE* infile;
  int c;
  infile = fopen(filename, "r");
  out = (char**)malloc(sizeof(char*)*(unsigned long)num_words);
  while(fgets(buf, 1024, infile) != NULL) {
      num_words++;
      out = (char **) realloc(out, (unsigned long )num_words);
      char *temp = strdup(buf);
      out[num_words-(unsigned long)1] = temp;
  }
  fclose(infile);
  return out;
}

// Free each of the strings in the vocabulary, as well as the pointer vocabulary
// itself (which points to an array of char *).
void free_vocabulary(char **vocabulary, size_t num_words) {
  // TODO(you): finish this function
}

// Once your other functions are working, please revert your main() to its
// initial state, but please feel free to change it, during development. You'll
// want to test out each individual function!
int main(void) {
  char **vocabulary;
  size_t num_words;
  int num_guesses = 0;

  srand(time(NULL));

  // load up the vocabulary and store the number of words in it.
  vocabulary = load_vocabulary("vocabulary.txt", &num_words);

  // Randomly select one of the words from the file to be today's SECRET WORD.
  int word_index = rand() % num_words;
  char *secret = vocabulary[word_index];

  // input buffer -- we'll use this to get a guess from the user.
  char guess[80];

  // buffer for scoring each guess.
  char result[6] = {0};
  bool success = false;

  printf("time to guess a 5-letter word! (press ctrl-D to exit)\n");
  while (!success) {
    printf("guess: ");
    if (fgets(guess, 80, stdin) == NULL) {
      break;
    }
    // Whatever the user input, cut it off at 5 characters.
    guess[5] = '\0';

    if (!valid_guess(guess, vocabulary, num_words)) {
      printf("not a valid guess\n");
      continue;
    } else {
      num_guesses++;
    }
    success = score_guess(secret, guess, result);
    printf("%s\n", guess);
    printf("%s\n", result);
  }

  if (success) {
    printf("you win, in %d guesses!\n", num_guesses);
  }
  free_vocabulary(vocabulary, num_words);

  return 0;
}
