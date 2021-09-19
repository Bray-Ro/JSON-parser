//
//  main.c
//  JSON-parser
//
//  Created by Home on 11/08/2021.
//

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

// DEFINE STATES
#define STATE_DEFAULT 0
#define STATE_OBJECT 1
#define STATE_STRING 2
#define STATE_KEY    3
#define STATE_VALUE  4




int main(int argc, const char * argv[]) {
    
    
    // Read JSON file
    char * buffer = 0;
    char current_token[255];
    char key[255] = "";
    long length = 0;
    int current_state = STATE_DEFAULT;
    
    FILE * f = fopen (argv[1], "rb");

    if (f)
    {
      fseek (f, 0, SEEK_END);
      length = ftell (f);
      fseek (f, 0, SEEK_SET);
      buffer = malloc (length);
      if (buffer)
      {
        fread (buffer, 1, length, f);
      }
      fclose (f);
    }

    if (buffer)
    {
        int i = 0;
        //Iterate through file
        while (i <= length) {
            switch (buffer[i]) {
                case '{':
                    current_state = STATE_OBJECT;
                  //  printf("\nSTATE_OBJECT\n");
                  //  printf("\nOBJECT:\n");

                    break;
                case '}':
                    current_state = STATE_DEFAULT;
                  //  printf("\nSTATE_DEFAULT\n");
                    break;
                case '"':
                    
                    if (current_state == STATE_STRING || current_state == STATE_KEY) {
                        if (current_state == STATE_STRING) {
                      //  printf("key:%s, Argv:%s", key, argv[2]);
                           if (strcmp(key, argv[2]) == 0) {
                              //  printf("\n  VALUE:");
                               printf("\n\"%s\"\n", current_token);
                               strcpy(current_token, "");
                               strcpy(key, "");

                           } else {
                               strcpy(current_token, "");
                               strcpy(key, "");
                           }

                        }
                        current_state = STATE_OBJECT;
                      //  strcpy(current_token, "");
                      //  printf("\nSTATE_OBJECT\n");
                    } else if (current_state == STATE_VALUE){
                        current_state = STATE_STRING;
                        
                        //printf("\n          STRING:");

                    } else if (current_state == STATE_OBJECT) {
                        current_state = STATE_KEY;
                      //  printf("\nSTATE_KEY\n");

                        
                    }
                    break;
                case ':':
                    current_state = STATE_VALUE;
                  // printf("\n      KEY:%s", current_token);
           
                    strcpy(key, current_token);
                    strcpy(current_token, "");

                    break;
                case ',':
                    break;
                default:
                    if (buffer[i] != '\n') {
                        sprintf(current_token, "%s%c", current_token, buffer[i]);
                    }
                    break;
                    
                    
            }
            
            i++;
        }
    }
    
    return 0;
}
