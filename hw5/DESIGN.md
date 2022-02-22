
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
                set each character of guess to lower case
                set each character of secret to lower case
                if the guess[j] does not appear in any of the the secret word slots [i]
                        add 'x' to the result[j] position.
                if the letter in the guess appears in the secret word, but is not in the corresponding slot
                        add 'y' to the result[j] position.
                if the letter in the guess matches the corresponding letter in the secret word
                       add 'g' to the result[j] position.
                if guess is an exact match with secret
                        set all the characters in result to 'g'
                        and return true
       return false
}
```
The result has enough memory for a string of length 5 (at least 6 bytes long). So the loop should go until reaching the null character '\0' in the guess/secret chars. In order to handle case issues `tolower() in ctypes.h` can be used to guarantee the words are all lower-case letters ignoring the case of user's input.  Setting/checking each letter can be done by treating the chars as an array `guess[j]` `result[j]` and `secret[i]`. By using two for loops, each letter in guess can be checked with every letter in the secret word in order to satisfy each check.
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
            create a buffer of size 7 to store the line of the file
            set the number of words read to be zero.
            set a variable representing number of memory reallocations
            open the file with read permissions given the filename
            dynamically allocate out as an array of words
            while there are still lines to be read
                    set out at words_read equal to the first 5 characters of buffer
                    increment words_read variable
            if words_read is a multiple of 10 and not equal to zero
                    increment number of times allocated by 10
                    reallocate memory by creating a newOut variable of the same type and pass it out with the number of times reallocated + 10
                    if reallocation did not fail
                            set out equal to newout
            set num_words equal to words_read
            close the file
            return out
```
`char **out` represents the dynamically allocated array of `char *` pointers containing words. A buffer is needed in order to store the line read from each file. The buffer is of length 7 because each line in the file contains a hidden `\0 and newline` character on top of being a 5 letter word. In order to properly reallocate memory, a variable must be used to track how much memory has been used. Once the number of words read is divisable by 10 (each block of memory), then more memory must be allocated. First a variable that tracks the number of times allocated is incremented by 10. Then realloc is used with the number of times allocated + 10 in order to add additional memory. If memory reallocation did not fail, we can set out to the newOut variable. Lastly we set `num_words` equal to the number of words read, close the file, and return out.

```
void free_vocabulary(char **vocabulary, size_t num_words) {
        loop from zero to the number of words
            free the i'th element of `vocabulary`
        free vocabulary
        set vocabulary equal to NULL.
}
```
Frees the words in vocabulary, and the pointer vocabulary itself.
