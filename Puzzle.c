#include <stdio.h>
#include <string.h> // for strlen, strcmp, strcspn
#include <ctype.h>  // for isdigit
#include "funcs.h"

const int key_code_1 = 2;
const int key_code_2 = 6;
const int key_code_3 = 4;
const int key_code_4 = 5;

int key1_obtained = 0;
int key2_obtained = 0;
int key3_obtained = 0;
int key4_obtained = 0;

void menu_item_1(void) {
    const char correct_code[] = "1407"; 
    char input[32]; // buffer to store the input
    int attempts = 0; // count how many tries the player made.
    const int max_attempts = 3; // maximum tries for the player.
    int unlocked = 0; // becomes 1 when the player succeeds.
    

    printf("\n=== Puzzle 1: Keypad Lock ===\n");
    printf("A glowing keypad guards the first door.\n"); // just to give a visual to the game and make it fun.
    printf("Above it, a dusty chalkboard shows four scribbled maths clues:\n\n");
    printf("  Digit 1: \"I'm the smallest natural number.\"\n");
    printf("  Digit 2: \"I'm the number of sides on a square.\"\n");
    printf("  Digit 3: \"I'm the only solution of x^2 = 0.\"\n");
    printf("  Digit 4: \"I'm the largest one-digit prime number.\"\n\n");
    printf("Work out each digit, then enter the 4-digit code to unlock the door.\n");
    printf("You have %d attempts.\n\n", max_attempts);

    while (attempts < max_attempts && !unlocked) // Player can keep playing until they run out of attempts or until they unlock it.
    {
        printf("Enter 4-digit code: ");

        if (!fgets(input, sizeof(input), stdin)) { 
            printf("\nInput error.\n");
            return;  // 
        }

        input[strcspn(input, "\r\n")] = '\0'; // 
        if (strlen(input) != 4) {
            printf("The code must be exactly 4 digits.\n\n");
            continue; // restart the loop, ask again
        }

        int all_digits = 1;
        for (size_t i = 0; i < 4; i++) {
            if (!isdigit((unsigned char)input[i])) {
                all_digits = 0;
                break;
            } // validate inputs contains digits only
        }

        if (!all_digits) {
            printf("The code must contain digits only.\n\n");
            continue;
        }

        attempts++; // increase attempt counter

        if (strcmp(input, correct_code) == 0) // compare input with correct code.
        {
            printf("\nYou hear a soft click... The lock flashes green!\n");
            printf("The door swings open. You solved Puzzle 1 in %d attempt(s).\n", attempts);
            printf("A small metal token slides out of a compartment marked: KEY #1.\n\n");
            printf("On the token, a single digit is engraved: %d. Remember this.\n\n", key_code_1);
            unlocked = 1;
            key1_obtained = 1; // Save progress
        } 
        else 
        {
            printf("\n(Incorrect code.) The keypad beeps in disappointment.\n");

            if (attempts < max_attempts) {

                
                int correct_position = 0;
                for (int i = 0; i < 4; i++) {
                    if (input[i] == correct_code[i]) {
                        correct_position++;
                    }
                }
                printf("Hint: %d of the digits are in the correct position.\n", correct_position);
                printf("Attempts remaining: %d\n\n", max_attempts - attempts);

                
                char choice[8];
                printf("What would you like to do next?\n");
                printf("  1. Get an extra hint\n");
                printf("  2. Show answer\n");
                printf("  3. Keep trying\n");
                printf("Enter choice: ");

                if (fgets(choice, sizeof(choice), stdin)) {
                    choice[strcspn(choice, "\r\n")] = '\0';

                    if (choice[0] == '1') {
                        
                        printf("\nThe last digit is 7.\n\n");
                    } 
                    else if (choice[0] == '2') {
                        // Show answer but DO NOT auto unlock
                        printf("\nThe correct code is: 1407.\n\n");
                    } 
                    else {
                        printf("\nYou decide to keep trying...\n\n");
                    }
                }
            }
        }
    }

    if (!unlocked) {
        printf("\nThe keypad locks itself temporarily, You'll have to try again later...\n");
    }
}

void menu_item_2(void)
{
    char answer[32];
    int attempts = 0;
    int solved = 0;
    

    printf("\n=== Puzzle 2: The Whispering Riddle Door ===\n");
    printf("A soft voice whispers around you:\n\n");
     printf("\"I speak without a mouth and hear without ears.\n");
    printf(" I have no body, but I come alive with wind.\n");
    printf(" What am I?\"\n\n");
   
    while (!solved) 
    {
        printf("Your answer: ");

        if (!fgets(answer, sizeof(answer), stdin)) {
            printf("\nInput error.\n");
            return;
        }

        answer[strcspn(answer, "\r\n")] = '\0'; 

        if (answer[0] == '\0') {
            printf("The door stays unlocked, Try typing an actual word.\n\n");
            continue;
        }

        for (size_t i = 0; answer[i] != '\0'; i++) {
            answer[i] = (char)tolower((unsigned char)answer[i]);
        }

        attempts++;

        if (strcmp(answer, "echo") == 0) {
            printf("The whisper repeats your word... \"echo\" ...and then laughs.\n");
            printf("Stone grinds as the door slowly opens.\n");
            printf("You have solved Puzzle 2 in %d attempt(s).\n", attempts);
            printf("A second metal token floats towards you, engraved: KEY #2.\n\n");
            printf("You notice a digit etched into the metal: %d. Remember it.\n\n", key_code_2);

            key2_obtained = 1;  // remember that this puzzle is solved
            solved = 1;
        } else {
            printf("\nThe whisper speak again: \"That is not my name. Try again.\"\n");

            
            if (attempts == 3) {
                printf("[Hint] The sound of your own voice bouncing back to you...\n\n");
            } else if (attempts == 5) {
                printf("[Hint] Caves, canyons, empty rooms... your voice repeats itself.\n\n");
            } else {
                printf("\n");
            }
        }
    }
}

void menu_item_3(void)

{
    int grid[4][4] = {
        {1, 2, 3, 4},
        {3, 4, 1, 2},
        {2, 1, 4, 0},   // missing cell = 0
        {4, 3, 2, 1}
    };

    const int correct_value = 3; // what belongs in the ? cell
    char input[32];
    int attempts = 0;
    int solved = 0;

    printf("\n=== Puzzle 3: Sudoku Vault (Array Version) ===\n");
    printf("A 4x4 Sudoku grid is carved into the vault door.\n");
    printf("One number is missing. Fill it in to unlock the vault.\n\n");

    while (!solved)
    {
        
        printf("Current grid:\n\n");
        printf("+---+---+---+---+\n");
        for (int r = 0; r < 4; r++) {
            printf("|");
            for (int c = 0; c < 4; c++) {
                if (grid[r][c] == 0) {
                    printf(" ? |");
                } else {
                    printf(" %d |", grid[r][c]);
                }
            }
            printf("\n+---+---+---+---+\n");
        }

        printf("\nEnter the number that belongs in place of '?': ");

        if (!fgets(input, sizeof(input), stdin)) {
            printf("Input error.\n");
            return;
        }

        input[strcspn(input, "\r\n")] = '\0';

        if (input[0] == '\0') {
            printf("Please enter a digit between 1 and 4.\n\n");
            continue;
        }

        if (!isdigit((unsigned char)input[0]) || input[1] != '\0') {
            printf("Use only ONE digit between 1 and 4.\n\n");
            continue;
        }

        int guess = input[0] - '0';
        attempts++;

        if (guess == correct_value) {
            printf("\nThe number %d fits perfectly.\n", guess);
            printf("The vault glows and unlocks.\n");
            printf("You solved Puzzle 3 in %d attempts.\n", attempts);
            printf("A third metal token emerges from the vault, labeled: KEY #3 .\n\n");
            printf("Carved into its surface is the digit: %d. Remember this one too.\n\n", key_code_3);

            key3_obtained = 1;
            solved = 1;
        } else {
            printf("Incorrect. The door remains sealed.\n");

            
            if (attempts == 2) {
                printf("[Hint] Look at the row: 2, 1, 4, ?\n");
            }
            if (attempts == 4) {
                printf("[Hint] Which number from {1,2,3,4} is missing?\n");
            }

            printf("\n");
        }
    }
}



void menu_item_4(void)
{
    char answer[32];      
    int attempts = 0;     
    int solved = 0;       

    printf("\n=== Puzzle 4: Crossword Chamber ===\n");
    printf("You step into a circular room with walls covered in carved letters.\n");
    printf("In the center of the floor, a tiny 4-letter crossword glows faintly.\n\n");

    printf("   +---+---+---+---+\n");
    printf("1A |   |   |   |   |\n");
    printf("   +---+---+---+---+\n\n");

    printf("Clue 1A (4 letters):\n");
    printf("\"Earth's natural satellite, often seen in phases.\"\n\n");

    printf("Type the word that fits into 1A.\n");
    printf("(You can try as many times as you like.)\n\n");

    while (!solved) {
        printf("Your answer for 1A: ");

        if (!fgets(answer, sizeof(answer), stdin)) {
            printf("\nInput error.\n");
            return;
        }

        
        answer[strcspn(answer, "\r\n")] = '\0';

        
        if (answer[0] == '\0') {
            printf("The letters fade slightly. Try typing an actual word.\n\n");
            continue;
        }

        // convert to uppercase so we accept moon / MOON / Moon etc.
        for (size_t i = 0; answer[i] != '\0'; i++) {
            answer[i] = (char)toupper((unsigned char)answer[i]);
        }

        attempts++;

        if (strcmp(answer, "MOON") == 0) {
            printf("\nThe letters M O O N lock into place on the glowing grid.\n");
            printf("Light explodes from the floor and races up the walls.\n");
            printf("You solved Puzzle 4 in %d attempt(s).\n", attempts);
            printf("A final metal token drops from a hidden slot: KEY #4 is.\n\n");
            printf("In the centre of the token, the digit %d is engraved.\n\n", key_code_4);

            key4_obtained = 1;  // remember that this puzzle is solved
            solved = 1;
        } else {
            printf("\nThe carved letters rearrange themselves, then go dim again.\n");
            printf("That word doesn't seem to fit.\n");

            
            if (attempts == 2) {
                printf("[Hint] You see it in the night sky, not the Sun.\n\n");
            } else if (attempts == 4) {
                printf("[Hint] The pattern appears faintly on the grid: M _ _ N\n\n");
            } else {
                printf("\n");
            }
        }
    }
}


void menu_item_5(void)
{
    char input[64];

    printf("\n=== Puzzle 5: The Guardian ===\n");

    // First: check if the player actually has all four keys
    if (!key1_obtained || !key2_obtained || !key3_obtained || !key4_obtained) {
        printf("A towering stone Guardian blocks your path.\n");
        printf("\"You are not yet ready,\" it rumbles.\n");
        printf("\"Return only when you carry all four keys from the trials.\"\n\n");

        printf("Current key check:\n");
        printf("  KEY #1 (Puzzle 1): %s\n", key1_obtained ? "OBTAINED" : "missing");
        printf("  KEY #2 (Puzzle 2): %s\n", key2_obtained ? "OBTAINED" : "missing");
        printf("  KEY #3 (Puzzle 3): %s\n", key3_obtained ? "OBTAINED" : "missing");
        printf("  KEY #4 (Puzzle 4): %s\n\n", key4_obtained ? "OBTAINED" : "missing");

        printf("The Guardian gestures back towards the earlier chambers.\n");
        printf("You quietly step away. (Solve all puzzles, then return here.)\n");
        return; // don't let them continue without all keys
    }

    // If we reach here, the player HAS all four keys
    printf("The four keys glow in your hands.\n");
printf("\"You carry the keys,\" the Guardian says, \"but do you remember them?\"\n\n");


/* --- Challenge 1: Key #1 digit --- */
while (1) {
    printf("1) What digit was engraved on KEY #1? ");

    if (!fgets(input, sizeof(input), stdin)) {
        printf("\nInput error.\n");
        return;
    }

    input[strcspn(input, "\r\n")] = '\0';

    if (strlen(input) != 1 || !isdigit((unsigned char)input[0])) {
        printf("Answer with a single digit.\n\n");
        continue;
    }

    if ((input[0] - '0') == key_code_1) {
        printf("The first key flares with light.\n\n");
        break;
    } else {
        printf("The Guardian shakes its head. \"That was not the digit on the first key.\"\n\n");
    }
}

/* --- Challenge 2: Key #2 digit --- */
while (1) {
    printf("2) What digit was engraved on KEY #2? ");

    if (!fgets(input, sizeof(input), stdin)) {
        printf("\nInput error.\n");
        return;
    }

    input[strcspn(input, "\r\n")] = '\0';

    if (strlen(input) != 1 || !isdigit((unsigned char)input[0])) {
        printf("Answer with a single digit.\n\n");
        continue;
    }

    if ((input[0] - '0') == key_code_2) {
        printf("The second key shines brightly.\n\n");
        break;
    } else {
        printf("\"Think back to the riddle door,\" the Guardian whispers.\n\n");
    }
}

/* --- Challenge 3: Key #3 digit --- */
while (1) {
    printf("3) What digit was engraved on KEY #3? ");

    if (!fgets(input, sizeof(input), stdin)) {
        printf("\nInput error.\n");
        return;
    }

    input[strcspn(input, "\r\n")] = '\0';

    if (strlen(input) != 1 || !isdigit((unsigned char)input[0])) {
        printf("Answer with a single digit.\n\n");
        continue;
    }

    if ((input[0] - '0') == key_code_3) {
        printf("The third key responds with a soft hum.\n\n");
        break;
    } else {
        printf("\"Remember the missing number in the Sudoku row,\" the Guardian hints.\n\n");
    }
}

/* --- Challenge 4: Key #4 digit --- */
while (1) {
    printf("4) What digit was engraved on KEY #4? ");

    if (!fgets(input, sizeof(input), stdin)) {
        printf("\nInput error.\n");
        return;
    }

    input[strcspn(input, "\r\n")] = '\0';

    if (strlen(input) != 1 || !isdigit((unsigned char)input[0])) {
        printf("Answer with a single digit.\n\n");
        continue;
    }

    if ((input[0] - '0') == key_code_4) {
        printf("The fourth key blazes with light.\n\n");
        break;
    } else {
        printf("\"Think of the word you placed in the crossword,\" the Guardian says quietly.\n\n");
    }
}

printf("All four keys resonate together, merging into a single symbol.\n\n");
printf("              %d%d%d%d\n\n", key_code_1, key_code_2, key_code_3, key_code_4);
printf("The Guardian steps aside.\n");
printf(">>> You have truly escaped the room. Congratulations! <<<\n\n");
printf("(You may still return to the main menu to replay any puzzle.)\n");
}


void show_key_status(void)
{
    printf("\n=== Key Status ===\n");
    printf("Puzzle 1 - KEY #1: %s\n", key1_obtained ? "OBTAINED" : "missing");
    printf("Puzzle 2 - KEY #2: %s\n", key2_obtained ? "OBTAINED" : "missing");
    printf("Puzzle 3 - KEY #3: %s\n", key3_obtained ? "OBTAINED" : "missing");
    printf("Puzzle 4 - KEY #4: %s\n", key4_obtained ? "OBTAINED" : "missing");
    printf("----------------------\n");
}

