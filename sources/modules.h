#ifndef FONCTIONS_H_INCLUDED
#define FONCTIONS_H_INCLUDED

void comparison(char letter, char word[], char display[], uint32_t length, uint32_t *failed, uint32_t *remaining);
void readTyping(char *typing);
void wordSelection(char word[], uint32_t length, uint32_t MIN, uint32_t MAX);
void wannaReplay(uint32_t *i);
void difficultyChoice(uint32_t *length, uint32_t *MIN, uint32_t *MAX);
void rules();
void hanged(uint32_t i);

#endif /* FONCTIONS_H_INCLUDED */
