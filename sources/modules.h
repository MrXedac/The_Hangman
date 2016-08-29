#ifndef FONCTIONS_H_INCLUDED
#define FONCTIONS_H_INCLUDED

void comparison(char letter, char word[], char display[], uint32_t length);
void readTyping(char *typing);
void wordSelection(char word[], uint32_t length, uint32_t MIN, uint32_t MAX);
void wannaReplay(uint32_t *i);
void difficultyChoice(char *word, uint32_t *length, uint32_t *MIN, uint32_t *MAX);
void rules();

#endif // FONCTIONS_H_INCLUDED
