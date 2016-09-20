//Swangya Saurav
//1001054908
//CSE 3320-001
//Assignment 1

#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <readline/readline.h>                          //For Autocompleton
#include <readline/history.h>                           //For Autocompetion

char *dirstr[100];
char *filstr[100];

int main(void) {
    pid_t child;
    DIR * d;
    struct dirent * de;
    int i, c, k;
    char s[256], cmd[256];
    char inpt[256];
    time_t t;

    while (1) {
      system("clear");
      t = time( NULL );
      printf( "Time: %s\n", ctime( &t ));
      printf("-----------------------------------------------\n" );

      getcwd(s, 200);
      printf( "\nCurrent Directory: %s \n", s);

      d = opendir( "." );
      c = 0;
      dirstr[0]=NULL;
      while ((de = readdir(d))){
          if ((de->d_type) & DT_DIR){
             //printf( "\t\t%d. %s\n", c++, de->d_name);
             dirstr[c]=de->d_name;                                        //creating string with directory names to implement previous next function as well as to take integer input insted of string from user
             c++;
          }
      }
      closedir( d );
      int end=5;
      int lim=0;
      char in;
      printf("Directories: \n");
      while (lim<=end && lim<c) {                                       //Implementing Next and Previous functions
          printf("\t\t %d. %s \n", lim, dirstr[lim] );
          lim++;
          if(lim == end){
              printf("Press 'N' for next and 'P' for previous and 'C' for Commands \n");
              in=getchar();
          if(in=='N'){                                                  //For next input.
                  lim=end;
                  end= end+5;                                           //displaying 5 files at a time
                  getchar();
              }
              else if(in=='P'){
                  end=lim-5;
                  lim= lim-10;
                  getchar();
              }
              else if(in == 'C'){
                  break;
              }
              else{
                  printf("Invalid Input!");
              }
          }
      }
      printf( "-----------------------------------------\n" );

      d = opendir( "." );
      c = 0;
      filstr[0]=NULL;
      while ((de = readdir(d))){
          if (((de->d_type) & DT_REG)){
              filstr[c]=de->d_name;                                         //creating string with file names to implement previous next function as well as to take integer input insted of string from user
              c++;
          }
      }
      closedir( d );

   end=5;                                                                   //initializing the variables again for file's previous-next function
       lim=0;
       in;
      printf("Files: ");
      while (lim<=end && lim<c) {
          printf("\t\t %d. %s \n", lim, filstr[lim] );
          lim++;
          if(lim == end){
              printf("Press 'N' for next and 'P' for previous and 'C' for Commands \n");
              in=getchar(); getchar();
              if(in=='N'){
                  lim=end;
                  end= end+5;
                  //getchar();
              }
              else if(in=='P'){
                  end=lim-5;
                  lim= lim-10;
                  //getchar();
              }
              else if(in == 'C'){
                  break;
              }
              else{
                  printf("Invalid Input!");
              }
          }
      }
      printf( "-----------------------------------------\n" );

      printf("Operations: \te)\tEdit\n");
      printf("\t\tr)\tRun\n");
      printf("\t\tc)\tChange Directory\n");
      printf("\t\tq)\tQuit\n");

      char str[256];
      int num;

      c = getchar( );                                                           //One getchar() is removed to overcome the bug where the program was not running properly in a loop
      switch (c) {
        case 'q': exit(0); /* quit */
        case 'e': printf( "Edit what?:" );
                  scanf( "%s", s );
                  if(isdigit(s[0])){                                        //This checks if the user has entered a number insted of string
                  num=atoi(s);                                              //converting string to number
                  strcpy(str, filstr[num]);                                 //Extracting srting name associated with the entered number
                  }
                  else
                    strcpy(str, s);
                  strcpy( cmd, "pico ");
                  strcat( cmd, str );
                  system( cmd );
                  break;
        case 'r': printf( "Run what?:" );
                  scanf( "%s", cmd );
                  if(isdigit(cmd[0])){                                      //This checks if the user has entered a number insted of string
                  num=atoi(cmd);                                            //converting string to number
                      strcpy(str, filstr[num]);                             //Extracting srting name associated with the entered number
                  }
                  else
                    strcpy(str, cmd);
                  system( str );
                  break;
        case 'c': printf( "Change To?:" );
                  scanf( "%s", cmd );
                  if(isdigit(cmd[0])){                                      //This checks if the user has entered a number insted of string
                      num=atoi(cmd);                                        //converting string to number
                      strcpy(str, dirstr[num]);                             //Extracting srting name associated with the entered number
                  }
                  else
                    strcpy(str, cmd);
                  chdir( str );
                  break;
        default: break;
      }
      getchar();                                                            //This does not allow the loop to run again without taking an input
    }
}
