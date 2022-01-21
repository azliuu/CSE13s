# Assignment 1 - Pass the Pigs

## The Task

Implement a version of the game Pass the Pigs using the following rules:
- 2<=k<=10players
- Players take turns rolling an asymmetrical die with the following possibilities:
- side (2/7)
- razorback (1/7)
- trotter (1/7)
- snouter (1/7)
- jowler (2/7)

## Each possible roll has a different point value:
- side = 0 pts
- razorback/trotter = 10 pts
- snouter = 15 pts
-  jowler = 5 pts
-  The side roll has a special property: If a player rolls and gets a SIDE value, their turn ends and the next player gets to begin rolling the dice.
- The game ends when any player has earned 100 or more points.

## User Input

- Ask user for number of players
- If the user input is now between 2 and 10 inclusive, print an error message and use default value of 2. Else, the number of players is equal to the user input.
- Prompt user to input random seed
- if the user inputs anything other than a valid seed, print error message
- valid seeds are from 0 to UINT_MAX inclusive

## The rules of the game

- Set the random seed based on the valid user input. Each player begins with 0 points.
- Proceed arounbd in a circle from player 0. For each player:
- print out the name of the player currently rolling the pig
- roll the pig / dice, increasing the player's points until they either win or the pig/dice lands on a side
- If the game continues and hte current player rolls a side
- If the current player rolls a side and is at location n-1 in names.h then move to the next player's turn.
the next player's turn begins.
- If the player rolls anything other than a side and their point value <100 pts, increase their individual point value and roll again.
- If a player has >= 100 pts, then the win and congrats message is printed to stdout.
- If the rolled pig lands on one of its two sides, then the player's turn ends and the next player gets to begin rolling.

## Pseudocode
```
player_num = input("How many players?")
if player_num < 2 or player_num > 10 or player_num is not int:
        print("Invalid number of players. Using 2 instead.\n")
        player_num = 2

seed_num = input("Random seed:")
if seed_num < 0 or seed_num > 4294967295 or seednum is not int: // UINT_MAX value
        print("Invalid random seed. Using 2021 instead.\n")
        seed_num = 2022

random.seed(seed_num)
player_points = [0] * player_num

for i in player_num: int roll = 0
        while player_points[i] < 100:
                print(names[i] + "rolls the pig...")
                roll = random.randint(1,7)
                if roll == 1 or roll == 2: // Side
                        print("pig lands on side")
                        if i == player_num-1:
                            i=0
                        else:
                            i += 1
                if roll == 3: // Razorback
                        print("pig lands on back")
                        player_points[i] += 1
                if roll == 4: // Trotter
                        print("pig lands upright")
                        player_points[i] += 10
                if roll == 5: // Snouter
                        print("pig lands on snout")
                        player_points[i] += 15
                if roll == 6 or roll == 7: // Jowler
                        print("pig lands on ear")
                        player_points[i] += 5
                if (player_points[i] >= 100):
                        print(names[i], "wins with", player_points[i], "points!")
                        return 0
```
