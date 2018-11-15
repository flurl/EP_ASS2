//------------------------------------------------------------------------------
// ass2.c
//
// Template program for EP Assignment 2 WS18
//
// Group: Group C, study assistant Thomas Schwar
//
// Authors: Florian Klug 09830971
// Robin Edlinger 11804235
//------------------------------------------------------------------------------
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUMBER_OF_ROLLER_ELEMENTS 26

void printRollers(char roller[][NUMBER_OF_ROLLER_ELEMENTS]);
char encipher(char roller[][NUMBER_OF_ROLLER_ELEMENTS], char to_encipher);
void updateRollers(char roller[][NUMBER_OF_ROLLER_ELEMENTS], int offsets[]);
void rotateRoller(char roller[]);
char rollForward(char roller[], char to_roll);
char rollBackward(char roller[], char to_roll);


/*
void printRollers(char roller[][NUMBER_OF_ROLLER_ELEMENTS])
{
  // print table
}

char encipher(char roller[][NUMBER_OF_ROLLER_ELEMENTS], char to_encipher)
{
  // encipher single character and return it
}

char rollForward(char roller[], char to_roll)
{
  // get character via index (convert to_roll to index)
}

char rollBackward(char roller[], char to_roll)
{
  // get index via character and convert index to character
}
*/

void updateRollers(char roller[][NUMBER_OF_ROLLER_ELEMENTS], int offsets[])
{
  // calculate offsets and rotate roller-arrays if necessary
  
  rotateRoller(roller[1]);
  
  offsets[0]++;
  
  if (offsets[0] > 25) {
    offsets[0] = 0;
    rotateRoller(roller[2]);
    offsets[1]++;
    if (offsets[1] > 25) {
      offsets[1] = 0;
      rotateRoller(roller[3]);
      offsets[2]++;
      if (offsets[2] > 25) { offsets[2] = 0;}
    }
  }
  
}

void rotateRoller(char roller[]) {
  char tmp[NUMBER_OF_ROLLER_ELEMENTS];
  /*for (int i=0; i<NUMBER_OF_ROLLER_ELEMENTS; i++) printf("%c", roller[i]);
  printf("\n");*/
  
  memcpy(tmp+1, roller, sizeof(char)*NUMBER_OF_ROLLER_ELEMENTS-sizeof(char));
  tmp[0] = roller[NUMBER_OF_ROLLER_ELEMENTS-1];
  memcpy(roller, tmp, sizeof(char)*NUMBER_OF_ROLLER_ELEMENTS);
  /*for (int i=0; i<NUMBER_OF_ROLLER_ELEMENTS; i++) printf("%c", roller[i]);
  printf("\n");*/
}

/*void rotateRoller(char roller[])
{
  // rotate array
}*/


int main(int argc, char** argv)
{
  char roller[5][NUMBER_OF_ROLLER_ELEMENTS] = 
  {
    "QWERTZUIOASDFGHJKPYXCVBNML",
    "JGDQOXUSCAMIFRVTPNEWKBLZYH",
    "NTZPSFBOKMWRCJDIVLAEYUXHGQ",
    "JVIUBHTCDYAKEQZPOSGXNRMWFL",
    "QYHOGNECVPUZTFDJAXWMKISRBL"
  };
  
  int offsets[3] = 
  {
    0, 0, 0
  };

  int input;
  char ukw;
  char egw;

  do 
  {
    input = fgetc(stdin);
    
    // ignore input, which is not [A-Z]
    if ('A' <= input && input <= 'Z')
    {
      // encipher, print character and update rollers
//      printf("%d", inputed_char);
      ukw = roller[4][roller[3][roller[2][roller[1][roller[0][input - 'A'] - 
'A'] -  
'A']- 'A'] - 'A'];

      egw = (strchr(roller[0], (strchr(roller[1], 
(strchr(roller[2], (strchr(roller[3], ukw) - roller[3]) + 'A') - roller[2]) +  
'A') - roller[1]) + 'A') - roller[0]) + 'A';

    printf("%c", egw);
    //printf("%02d %02d %02d\n", offsets[0], offsets[1], offsets[2]);
    
    updateRollers(roller, offsets);

    }
  } 
  while(input != '\n' && input != EOF);
  
  // print rollers

  return 0;
}
