//------------------------------------------------------------------------------
// ass2.c
//
// Enigma - encrypt a string
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


//-----------------------------------------------------------------------------
///
/// Print the rollers as a nice table
///
/// @param roller The rollers to print
//
void printRollers(char roller[][NUMBER_OF_ROLLER_ELEMENTS])
{
  printf("    | 1 | 2 | 3 | 4 | 5\n----+---+---+---+---+---\n");
  for (int index = 0; index < NUMBER_OF_ROLLER_ELEMENTS; index++) {
    printf("%3d | %c | %c | %c | %c | %c\n", index+1, roller[0][index], 
           roller[1][index], roller[2][index], roller[3][index], 
           roller[4][index]);
  }

}

//-----------------------------------------------------------------------------
///
/// Updates the offsets and rotates the rollers accordingly
///
/// @param roller The rollers
/// @param offsets The offsets
//
void updateRollers(char roller[][NUMBER_OF_ROLLER_ELEMENTS], int offsets[])
{
  // the 2nd roller has to be rotated everytime
  rotateRoller(roller[1]);

  offsets[0]++;

  // check the offsets and after a complete turn, rotate the next one also
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

//-----------------------------------------------------------------------------
///
/// Rotates a single roller by shifting the elements right
///
/// @param roller The roller to rotate
//
void rotateRoller(char roller[]) {
  char tmp;

  tmp = roller[NUMBER_OF_ROLLER_ELEMENTS - 1];
  for (int counter = NUMBER_OF_ROLLER_ELEMENTS - 1; counter > 0; counter--) {
    roller[counter] = roller[counter - 1];
  }
  roller[0] = tmp;
}


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
  int index;
  char ukw;
  char egw;
  char tmp;

  do 
  {
    input = fgetc(stdin);

    // ignore input, which is not [A-Z]
    if ('A' <= input && input <= 'Z')
    {
      // encipher, print character and update rollers
      
      // convert characters to indices
      index=input - 'A';
      for (int counter = 0; counter < 4; counter++)
      {
        index = roller[counter][index] - 'A';
      }
      ukw = roller[4][index];

      // convert indices to chars
      tmp = ukw;
      for (int counter = 3; counter >= 0; counter--) 
      {
        // strchr returns a pointer to the first found char, therefore 
        // the start position (which is the array pointer itself) has to be 
        // subtracted to get the zero based position of the char in the string
        tmp = (strchr(roller[counter], tmp) - roller[counter]) + 'A';
      }
      egw = tmp;

      // print a single encrypted char
      printf("%c", egw);
      updateRollers(roller, offsets);
    }
  } 
  while(input != '\n' && input != EOF);

  printf("\n--\n\n");
  printf("Rollers after encryption:\n\n");
  printRollers(roller);

  return 0;
}
