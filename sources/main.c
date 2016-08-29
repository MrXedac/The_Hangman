#include <stdio.h>
#include <stdlib.h>
#include <stdint.h> //uint32_t
#include <inttypes.h>
#include <string.h> //strcmp()
#include "modules.h"

int main(int argc, char *argv[])
{
    uint32_t remainingAttempts = 10, attemptsCount = 0, remainingAttempsCount = 10, length = 0, i = 0, choice = 0, MIN = 0, MAX = 0;
    char letter = 0;
    char *display = NULL;
    char *word = NULL;

    printf("Welcome on 'The Hangman' by Tartine !\n");
    printf("Loading game...\n");
    printf("V1.0 Release.\n\n");

    while(i == 0) //Replay loop
    {
        printf("***Menu***\n\n"); //Simple menu
        printf("1. Rules of the game.\n");
        printf("2. Start game.\n");
        printf("3. Exit.\n");
        printf("\nYou choice : ");
        scanf("%d", &choice);

        switch(choice)
        {
        case 1:
            rules();
            i = 0;
            break;
        case 2:

            difficultyChoice(word, &length, &MIN, &MAX);

            word = malloc((length + 1) * sizeof(char)); //Dyn allocation of memory on word string

            if(word == NULL) //Routine success check
            {
                printf("Error : memory attribution failed.\n Exiting...\n");
                exit(0);
            }

            wordSelection(word, length, MIN, MAX); //Picking a random word from words.hangman

            display = malloc((length + 1) * sizeof(char)); //Dyn allocation of memory on display string

            if(display == NULL) //Routine success check
            {
                printf("Error : memory attribution failed.\n Exiting...\n");
                exit(0);
            }

            for(i = 0; i < length; i++) //Hidding displayed word
            {
                display[i] = '*';
            }

            display[length] = '\0';

            while(attemptsCount <= remainingAttempts) //Core code
            {
                printf("\nYou have %d attempts remaining !\n", remainingAttempsCount);
                printf("Guess the secret word : %s\n", display);
                printf("Enter a letter ! ");
                readTyping(&letter);

                comparison(letter, word, display, length);

                remainingAttempsCount--; //Decreasing remaining attempts
                attemptsCount++; //Increasing attempts count

                printf("You have tried %d times to find the word yet\n", attemptsCount);

                if(strcmp(word, display) == 0) //Success
                {
                    printf("\n***** Good job ! You have guessed the word ! It was %s. *****\n", word);
                    attemptsCount = 100;
                    wannaReplay(&i);

                }
                else if(remainingAttempsCount == 0) //Failure
                {
                    printf("\n***** You are dead, hung by the neck... *****");
                    printf("\n***** The word was %s... *****\n", word);
                    attemptsCount = 100;
                    wannaReplay(&i);
                }
            }

            free(display); //Clearing display memory
            free(word); //Clearing word memory

//------------------------------------------------------------------------------

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
