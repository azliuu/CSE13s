# homework 7: Hash tables, I/O and strings
Design and implement a simple database that will keep track of our customers, and the information about them. With a simple interface, we can read a database file from the disk, add customers, and save the database back to the file.

## Big Picture Program Structure
This describes each file and how they relate to one another.

businessdb.c -- contains the main I/O for the project, handling prompting the user for commands. This will include hashtable.h in order to use it's functions. It will mainly feed in the user's input into hashtable.h's functions in order to implement the command.

Run the program with
```
make businessdb.c
./businessdb
```
hashtable.c -- contains all the logic for hash tables adding users, hashing using their email address, as well as contains all the functions needed in order to perform the commands specified by the user input.

hashtable.h -- contains the struct for a customer, as well as all the function headers defined in hashtable.c

Makefile -- this is a simple Makefile that correctly builds the businessdb program into an executable. It also contains CFLAGS for error checking, can format files, and cleans any .o files or executables.

```
make all -- compiles all the programs
make clean -- removes all .o and executables
make format -- correctly formats all files
make businessdb.c -- compiles businessdb.c and creates an executable named businessdb
```

## Storing the information from a customer
Create a Customer struct that contains an email address (string type), name (string type), shoe size (int type), and favorite food (a string). The following struct will be in a .h file
```
create a struct named Customer that contains
create a char email var
create a char name var
create a int shoe_size var
create a char food var
```
## The main interaction loop I/O
This is the main interaction loop that forms the interface for users. This will have the ability to read a file from the disk, add customers, delete customers, and save the database back to the file. Below is a close translation of the given python example code. In reality my program plan differs slightly, instead of having all the logic inside this file, the file will handle mainly user input to use functions that are defined in the `hashtable.h` file. There the logic will be implemented for the different hash functions.
```
while True:
    ask the user for a command
        if the command is quit
            break
        else if the command is save
         open the file with write permissions to outfile
                for every customer
                       create a variable line that stores the current customers email, name, shoesize, and food
                     print line to the outfile
              close the outfile
        else if the command is add
            ask the user for an email address
            store the user input into a char var called email
            ask the user for a name
            store the user input into a char var called name
            ask the user for a shoe size
            store the user input into a int var called shoe_size
            ask the user for a favorite food
            store the user input into a char var called food
            Create a new customer with the above email, name, shoe_size, and food
            store the customer in the customers hash table at the position of their email
        else if the command is lookup
            ask the user for an email address
            store the user input into a char variable called email
            if the email is in the customers hash table
                    print the current customer at email position in the customers hash table
            else, print the user is not found!
        else if the command is delete
            ask the user for an email address
            store the user input into a char variable called email
            if the email is in customers
                    free the customer at email position in the customers hash table
                    set the location in the customers hash table to NULL
            else, print the user is not found
        else if the command is list
            for every customer in customers
                    print the customer
        else
            print unknown command
```
Quit -- frees all the memory used by the program and then exits
Save -- writes the current state of the hash table to the file line by line
Add -- This adds a user to the hashtable. If the key specified by the user already exists, it overwrites the old key with the new specified data given by the user.
Lookup -- Searches the hashtable and returns the data in the hashtable associated with the given key. If there is no key in the hashtable that matches the specified one, the customer doesn't exist. Print an error message that tells the user the customer doesn't exist.
Delete -- Iterates through the hashtable, and each linked list element in the hashtable. If the key matches the specified one, free the node and set the next value to the previous value.
List -- Iteratres through the hastable and executes a lookup for each customer.
Else -- otherwise the command is not known and print an error message.

## Loading customer information from the file
This section opens the customers.tsv file, and creates customers with the provided data in the database.
```
set infile tp customers.tsv
create a buffer
open the infile
   for every line in the file
           set buffer equal to the line without the newline character
           set a fields array equal to each part of the line in the file, separatedd by the tab character
           set email equal to the 0th field
           set name equal to the 1st field
           set shoe_size equal to the 2nd field as an int
           set food equal to the third field
           create a customer with the above data

           add the customer to the customers array at email position
```
We can accomplish the split behavior needed using the function `strtok()`.

## storing customer data into a hash table
This logic is heavily inspired by the class demo given on Feb 28th. These functions and logic are used in order to store the customer data into buckets in the hash table.
```
create a Customers struct that contains
the email key
the values for name, fav_food, shoe_size, and Customers *next
```
This is a struct that represents a Customer node that contains the email key and values
```
define the number of buckets to be 100

unsigned long hash(char *str) {
        create a hash variable and set it to 5381
        create an var c that equals the given char str pointer
        while the pointer to string is not the null character
                set hash equal to hash * 33 + c
                increment string
        return the hash
}
```
This is the hash function originally created by Dan Bernstein. It takes a string and returns the hash using the djb2 hashing algorithm.
```
Customers *add_customer_to_list(char *email, char *name, char *food, int shoe_size, Customers *bucket) {
        create a new customer node called new_customer
        dynamically allocate memory to new_customer of customers size
        set each part of new_customer equal to the provided info
        set the next value of new_customer to bucket
        return the new customer
}
```
This function adds a customer to the given bucket with the given attributes.
```
void add_customer_to_hashtable(char *email, char *name, char *food, int shoe_size, Customers **buckets, size_t num_buckets) {
        create a variable which_bucket of size_t type that contains the hash of email % num_buckets
        set buckets at which bucket equal to the output of add_customer_to_list function with the given email, name, food, shoe_size, buckets at which bucket
}
```
This function adds the customer to the hashtable with the email being used as a key value. The `which_bucket` variable contains the value after the email has been hashed % the number of buckets. Then `which_bucket` is used as in index in the buckets array where the customer is added to the list.
```
char *fav_food_of_customer(char *email, Customers **buckets, size_t num_buckets) {
        create a which bucket variable that contains the hash of email mod num_buckets
        create a char pointer result and set it equal to NULL
        Create a new Customers *node
        set node equal to the customer in the buckets array at which_bucket

        while the node does not equal NULL
                if the email of the current node is the same as the given email
                        set result equal to the current node's favorite food
                set node equal to the next node
        return the result
}
```
This function returns the favorite food of a given customer provided their email. This function can be used in the `lookup` and `list` commands of the main file. The same logic can be used to return any of the customers data: name, email, shoe size, and favorite food.

## saving the customer database file
```
Open the outfile with write permissions
dump the current state of the hash table into the file with the same format
close the outfile
```
By using the `fprintf()` function, we can write to a given customers.tsv outfile with the specified tab-separated value format and order above.
