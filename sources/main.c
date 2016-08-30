#include <stdio.h>
#include <stdlib.h>
#include <stdint.h> /* uint32_t */
#include <inttypes.h> /* macros */
#include <string.h> /* strcmp() */
#include "modules.h"

/* The Hangman is a popular game and well known game. I created this code for training purpose.
I you have any idea on how to make it more efficient, or any fun feature I could add, you can email me at 'ritotartine@gmail.com'.
This code is not licensed or whatever. */


int main(int argc, char *argv[])
{
    uint32_t i = 0;

    printf("Welcome on 'The Hangman' by Tartine !\n");
    printf("Loading game...\n");

    while(i == 0) /* Replay loop */
    {
        uint32_t remainingAttempsCount = 10, length = 0, choice = 0, MIN = 0, MAX = 0, failedAttempts = 0, c = 0;
        char letter = 0;
        char *display = NULL;
        char *word = NULL;

        printf("***Menu***\n\n"); /* Simple menu */
        printf("1. Rules of the game.\n");
        printf("2. Start game.\n");
        printf("3. Exit.\n");
        printf("\nYou choice : ");
        scanf("%" SCNu32, &choice);

        switch(choice)
        {
        case 1:
            rules();
            i = 0;
            break;
        case 2:

            difficultyChoice(&length, &MIN, &MAX);

/*------------------------------------------------------------------------------*/
/* Shit is getting real -> core code */

            word = malloc((length + 1) * sizeof(char)); /* Dyn allocation of memory on word string */

            if(word == NULL) /* Routine success check */
            {
                printf("Error : memory attribution failed.\n Exiting...\n");
                exit(0);
            }

            wordSelection(word, length, MIN, MAX); /* Picking a random word from words.hangman */

            display = malloc((length + 1) * sizeof(char)); /* Dyn allocation of memory on display string */

            if(display == NULL) /* Routine success check */
            {
                printf("Error : memory attribution failed.\n Exiting...\n");
                exit(0);
            }

            for(i = 0; i < length; i++) /* Hidding displayed word */
            {
                display[i] = '*';
            }

            display[length] = '\0';
            failedAttempts = 0;

/*------------------------------------------------------------------------------*/

            while(remainingAttempsCount != 0) /* Core loop */
            {
                printf("\nYou have %d attempts remaining !\n", remainingAttempsCount);
                printf("Guess the secret word : %s\n", display);
                printf("Enter a letter ! ");
                readTyping(&letter);

                comparison(letter, word, display, length, &failedAttempts, &remainingAttempsCount);

                while((c = getchar()) != '\n' && c != EOF);
                c = 0;

                hanged(failedAttempts);

                if(strcmp(word, display) == 0) /* Success */
                {
                    printf("\n***** Good job ! You have guessed the word ! It was %s. *****\n", word);
                    wannaReplay(&i);
                    while((c = getchar()) != '\n' && c != EOF); /* I don't exactly why this is necessary, and at this point i'm too afraid to ask */
                    c = 0;

                }
                else if(remainingAttempsCount == 0) /* Failure */
                {
                    printf("\n\t***** You end up hung by the neck... *****");
                    printf("\n\t\t***** The word was %s... *****\n", word);
                    wannaReplay(&i);
                    while((c = getchar()) != '\n' && c != EOF);
                    c = 0;
                }
            }

            free(display); /* Clearing display memory */
            free(word); /* Clearing word memory */

/*------------------------------------------------------------------------------*/

            break;
        case 3:
            printf("\nThanks for playing !\n");
            exit(0);
        default:
            printf("\nThis option is not in the menu...Retry !\n\n");
            i = 0;
        }
    }

    printf("\nThanks for playing !\n");

    return 0;
}
