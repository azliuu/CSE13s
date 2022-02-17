
# Homework 5: strings, searching, words
This assignment implements our own version of wordle. There is a secret 5-letter English word and the player tries to guess what the word is. The player is passed information based on their guesses with yellow and green squares.

## Rules of the game
First a secret word is chosen from a list of 5-letter English words. For each turn, a player guesses a word, which must come from the shared list of 5-letter English words. If the player is able to guess the word correctly they win!

The dictionary of 5-letter words is within the code for the game. The game compares a player's guess with the secret word, and then returns a response which is made of 5 colored squares.

Square colors have different meanings:
* grey: The corresponding letter does not appear in the secret word.
* yellow: The corresponding letter appears in the secret word, but in a different slot.
* green: The corresponding letter appears in the secret word at the same slot

A guess is valid if it is a 5-letter string of ASCII characters a-z, and it is one of the words in the word list.

## Implementation
```
bool score_guess(char *secret, char *guess, char *result) {
        Loop through each character in the secret word with increment i.
            Loop through each character in the guess word with increment j.
                if the guess[j] does not appear in any of the the secret word slots [i]
                        add 'x' to the result[j] position.
                if the letter in the guess appears in the secret word, but is not in the corresponding slot
                        add 'y' to the result[j] position.
                if the letter in the guess matches the corresponding letter in the secret word
                       add 'g' to the result[j] position.
}
```
The result has enough memory for a string of length 5 (at least 6 bytes long). So the loop should go until reaching the null character '\0' in the guess char. Setting/checking each letter can be done by treating the chars as an array `guess[j]` `result[j]` and `secret[i]`. By using two for loops, each letter in guess can be checked with every letter in the secret word in order to satisfy each check.
```
bool valid_guess(char *guess, char **vocabulary, size_t num_words) {
            Loop through the list of accepted words.
                if the guess is one of the strings in the list of accepted words, return true. Else return false.
}
```
A Linear search can be used to loop through the vocab words, but for our use-case using a quick sort implementation may be faster. The function returns true if the user's guess is found within the vocabulary word list, false otherwise with a simple for loop.

```
char **load_vocabulary(char *filename, size_t *num_words) {
            char **out = NULL;
            set the number of words read to be zero.
            dynamically allocate an array
            use realloc to increase the size ofthe array over time.
            open the input file
            strdup the line/word from the file into out
            increment the num_words read
            realloc array
            fclose the file after all the lines have been read
```
`char **out` represents the dynamically allocated array of `char *` pointers containing each word read from the infile. In order to handle case issues `strupr()` can be used to guarantee the words are all capital letters ignoring case. As the array stores a word from each line of the infile, the array must be reallocated using `realloc` in order to fit the new word in the array.

```
void free_vocabulary(char **vocabulary, size_t num_words) {
        loop from zero to the number of words
            free the i'th element of `vocabulary`
        free vocabulary
        set vocabulary equal to NULL.
}
```
Frees the strings in vocabulary, and the pointer vocabulary itself.
