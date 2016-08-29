#include <stdio.h>
#include <stdlib.h>
#include <stdint.h> //uint32_t
#include <time.h> //srand
#include <ctype.h> //toupper()
#include "modules.h"


// -----------------------------------------------------------------------------------------------------------------


void comparison(char letter, char word[], char display[], uint32_t length)  //Rolling function comparing the proposed letter to the hidden word
{
    uint32_t i = 0, j = 0;

    for(i = 0; i < length; i++)
    {
        if(letter == word[i])
        {
            display[i] = letter; //
            j++;
        }
    }

    if(j == 1)
    {
        printf("Good job, you just guessed the letter %c !\n", letter);
    }
}


// -----------------------------------------------------------------------------------------------------------------


void wordSelection(char word[], uint32_t length, uint32_t MIN, uint32_t MAX) //Randomized word picking function from words.hangman
{
    uint32_t wordNumber = 0, b = 0, close = 1;
    FILE* wordsList = NULL;

    srand(time(NULL));
    wordNumber = (rand() % (MAX - MIN + 1)) + MIN;

    wordsList = fopen("ressources/words.hangman", "r");

    if(wordsList == NULL) //Routine file opening check
    {
        printf("\n*** Unable to open word list...Exiting. ***\n");
        exit(0);
    }

    rewind(wordsList);

    for(b = 0; b < (wordNumber - 1); b++) //Moving to next '\n'
    {
        while (fgetc(wordsList) != '\n')
        ;
    }
    length++;
    fgets(word, length, wordsList); //Printing picked word to 'word'

    close = fclose(wordsList);

    if (close != 0) //Routine file closure check
    {
        printf("\nFailure in dictionary closure...Exiting.\n");
    }

}


// -----------------------------------------------------------------------------------------------------------------


void readTyping(char *typing) //Replace scanf to avoid fails of repetitive use
{
    fflush(stdin); //Emptying buffer
    *typing = getchar();
    *typing = toupper(*typing); // UPPERCASING


    while (getchar() != '\n'); // Emptying buffer

}


// -----------------------------------------------------------------------------------------------------------------


void wannaReplay(uint32_t *i) //Simple replay function
{
    char replay = 0;

    printf("\nPlay again ? Y/N\n");
    readTyping(&replay);

    if(replay == 'Y')
    {
        *i = 0;
        printf("\nSignal received, reloading game...\n\n");
    }
    else
    {
        *i = 10;
        printf("\nSignal received, closing game...\n");
    }
}


// -----------------------------------------------------------------------------------------------------------------


void difficultyChoice(char *word, uint32_t *length, uint32_t *MIN, uint32_t *MAX) //Function to display difficulty menu
{

    uint32_t difficulty = 0, a = 0;

    while(a == 0)
    {
        printf("\nChoose your difficulty !\n");
        printf("1. Easy.\n");
        printf("2. Medium.\n");
        printf("3. Difficult.\n");
        printf("\nYour choice : ");

        scanf("%d", &difficulty); //Demande du choix de difficulte

        switch (difficulty) //Pré-requis à la randomisation du npmbre en fonction de la difficulte
        {
        case 1:
            *MAX = 10;
            *MIN = 1;
            *length = 4;
            a++;
            break;
        case 2:
            *MAX = 20;
            *MIN = 11;
            *length = 5;
            a++;
            break;
        case 3:
            *MAX = 30;
            *MIN = 21;
            *length = 6;
            a++;
            break;
        default:
            printf("This option is not in the menu...\n");
            printf("Retry !\n");
            a = 0;
            break;
        }
    }
}


// -----------------------------------------------------------------------------------------------------------------


void rules() //Do I even need to comment this?
{
    printf("\nHere are the rules of this popular and simple game :\n");
    printf("The program will chose a word between 4 and 6 characters in uppercase.\n");
    printf("This word will be hidden with the * star symbol.\n");
    printf("You will have to guess the word letter by letter.\n");
    printf("Still, attention ! You only have ten attempts before being hung by the neck !\n");
    printf("Back to menu...\n\n");
}
