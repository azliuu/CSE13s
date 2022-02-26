#Homework 6: Strings, Seraching, Pointers!
We will implement a Wordle solver. The solver will either iteratively suggest guesses to it's user to search for the solution, or have a secret word be specified for testing purposes in order to cut down the search space until the word is found.

## Scoring Letters / Scoring Words

```
int score_letter(char letter, char **vocabulary, size_t num_words) {
        create a count variable that represents the number of words that contain a specific letter
        for every word in vocabulary
                if the word is not null
                        if the letter is in the word
                                increment the count variable
                otherwise, continue the loop
        return the counter variable
}
```
In order to check if the letter is in a word, the vocabulary list must be iterated through. However, we must check if the word is set to NULL beforehand as our filter functions may set vocabulary words to NULL if they do not satisfy search criteria. Each time the letter is found in a word, the counter variable is incremented and then lastly returned.
```
int score_word(char *word, int *letter_scores) {
        create a score variable representing the sum of each letter score in a word.
        for every unique character in the word
                add the letter_score of the corresponding letter to score
        return the score
}
```
In order to ensure that there only unique characters cause an increment to the word score, we can use the `strchr()` function with a separate char array, and each word of the letter. If the function returns NULL, then we know the letter is unique and can add it to the separate chawr array. Then we can simply add the corresponding letter score to score at the position of `letter_scores[unique[i]- 'a']` in order to get the corresponding index.

##Filtering Words
```
size_t filter_vocabulary_gray(char letter, char **vocabulary, size_t num_words) {
        create a variable the counts how many words have been filtered
        for every word in the vocabulary list
                if the word contains the letter
                        increment the number of words filtered
                        free the vocabulary word
                        set the vocabulary location to null
        return the number of words filtered.
}
```
This function takes care of the case in wordle where a letter is grey. This means that every word that contains that letter within the vocabulary list is not a possible answer. In order to filter out the word, `vocabulary[i]` (the specific word at that position) is freed and then set to NULL. After a word is filtered, the variable is incremented and lastly returned once all the words in the vocabulary list have been gone through.
```
size_t filter_vocabulary_yellow(char letter, int position, char** vocabulary, size_t num_words) {
        create a count variable that represents the number of words filtered.
        for every word in the vocabulary list
                if the letter is not in the word
                        free the word in the vocabulary list
                        set the location of the word to null
                        increment the words filtered by 1
                else if the letter is in the word, but not at the specified position
                        free the word in the vocabulary list
                        set the location of the word to null
                        increment the words filtered by 1
        return the increment
}
```
This function handles the case in wordle where a letter is yellow. This signifies that the letter is inside the word, but not at that specific position. This allows us to filter out every word that does not contain the letter, as well as every word that contains the same letter in that position. The first if check can be accomplished with the `strchr()` function with the word and given letter as arguments. If the function returns NULL (signifying the word does not contain the letter), then we free the word and set it's position in the list to NULL. The words filtered is then incremented by 1. An else if statement is used for the second condition to represent that the letter is in the word, but tests if a word contins the letter at the same position in is freed and the locatiocn is set to NULL. The words filtered is then incremented by 1. Lastly the words filtered is returned.
```
size_t filter_vocabulary_green(char letter, int position, char **vocabulary, size_t num_words) {
        create an increment variable that represents the number of words filtered
        for every word in vocabulary
                if the letter at the given position is not equal to the given letter
                        free the vocabulary word
                        set the vocabulary word location to NULL
                        increment the number of words filtered
        return the number of words filtered
}
```
This function handles the case in wordle where a letter is green in a user's guess. This allows us to decrease the search space by eliminating every word in the vocabulary list that does not contain the specified letter in the specific location. Using similar logic to the previous functions we also can increment every time a word is filtered, and then return the same number.
