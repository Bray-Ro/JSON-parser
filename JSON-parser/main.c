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

int main(int argc, const char * argv[]) {
    // insert code here...
    char * buffer = 0;
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

    // start to process your data / extract strings here...
    if (buffer)
    {
        int i = 0;
        while (i <= length) {
            switch (buffer[i]) {
                case '{':
                    current_state = STATE_OBJECT;
                    printf("STATE_OBJECT\n");
                    break;
                case '}':
                    current_state = STATE_DEFAULT;
                    printf("STATE_DEFAULT\n");
                    break;
                case '"':
                    
                    if (current_state == STATE_STRING) {
                        current_state = STATE_OBJECT;
                        printf("STATE_OBJECT\n");
                    } else {
                        current_state = STATE_STRING;
                        printf("STATE_STRING\n");

                    }
                    break;
                default:
                    break;
                    
                    
            }
            
            i++;
        }
    }
    
    return 0;
}
