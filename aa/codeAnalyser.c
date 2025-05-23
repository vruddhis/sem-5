#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

int main() {
    char ch, buffer[15];
    FILE *fp;
    int i = 0, push_count = 0, pop_count = 0;
    int brace_count = 0;
    int inside_main = 0;

    fp = fopen("program.txt", "r");

    if(fp == NULL) {
        printf("Error while opening the file\n");
        exit(0);
    }

    while((ch = fgetc(fp)) != EOF) {
        if(ch == '{') {
            if(inside_main) {
                brace_count++;
            }
            i = 0;  
        } else if(ch == '}') {
            if(inside_main) {
                brace_count--;
                if(brace_count == 0) {
                    inside_main = 0;
                }
            }
            i = 0;  
        } else if(inside_main) {
            if(isalnum(ch)) {
                buffer[i++] = ch;
            } else {
                if(i != 0) {
                    buffer[i] = '\0';
                    i = 0;

                    if(strcmp(buffer, "push") == 0) {
                        push_count++;
                    } else if(strcmp(buffer, "pop") == 0) {
                        pop_count++;
                    }
                }
            }
        } else {
            if(isalnum(ch)) {
                buffer[i++] = ch;
            } else {
                buffer[i] = '\0';

                if(strcmp(buffer, "main") == 0 && ch == '(') {
                    inside_main = 1;
                    brace_count = 0;
                }
                
                i = 0;
            }
        }
    }

    fclose(fp);

    printf("Number of 'push' occurrences: %d\n", push_count);
    printf("Number of 'pop' occurrences: %d\n", pop_count);

    return 0;
}

