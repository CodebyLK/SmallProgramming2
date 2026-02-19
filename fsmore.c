#include <stdio.h>
#include <stdlib.h>



int main(const int argc, char *argv[]) {
    int count = 0;

    //
    for (int i = 1; i < argc; i++) {
        FILE *fp = fopen(argv[i], "r");
        if (fp == NULL) {
            printf("fsmore: cannot open file\n");
            exit(1);
        }

        const char *line_env = getenv("LINES");
        int max_lines = 24; // Default

        if (line_env != NULL) {
            char *endptr;
            //Three arguments of strtol:
                //1. Pointer to a character array (Destination where read string is stored)
                //2. Maximum number of characters (Max buffer size - the safety net for char container
                //(cannot exceed char line[24] in this example))
                //3. Input stream (Source where you are reading characters from)


            const long val = strtol(line_env, &endptr, 10);

            // Check if the string was actually a number
            if (endptr != line_env) {
                max_lines = (int)val;
            }
        }

        char line[200];  //Container - Physical size of memory block

        //Three arguments of fgets:
            //1. Pointer to a character array (Destination where read string is stored)
            //2. Maximum number of characters (Max buffer size - the safety net for char container
                //(cannot exceed char line[24] in this example))
            //3. Input stream (Source where you are reading characters from)
        //int *count = 0;
        while (fgets(line, sizeof(line), fp)) {
            //printf("%s", line);
            count++;
            if (count >= max_lines) {
                printf("%s", line);
                char *temp[2];
                fgets(temp, sizeof(temp), stdin);
                FILE *tty = fopen("/dev/tty", "r");
                printf("--More--");
                getc(tty);
                fclose(tty);
                count = 0;
            }



        }
        fclose(fp);
    }

    exit(0);
}