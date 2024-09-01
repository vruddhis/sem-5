#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

int main() {
    char ch, buffer[1000];
    FILE *fp;
    int i = 0, push_count = 0, pop_count = 0;
    int brace_count = 0;
    int inside_main = 0;

    fp = fopen("program.txt", "r");

    if(fp == NULL) {
        printf("Error while opening the file\n");
        exit(0);
    }
    printf("let cost of push be 2 and pop be 1\n");
    int credit = 0;
    printf("Initial credit is 0\n");
    printf("We claim amortized cost can be 1\nCost of push - amortised cost = 1\n Amortised cost - pop cost = 1\n");
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
                        credit += 1;
                        printf("Pop operation done. 1 added to credit. Credit is %d\n", credit);
                    } else if(strcmp(buffer, "pop") == 0) {
                        pop_count++;
                        printf("Credit is %d. It can be used to pay for pop.\n", credit);
                        credit--;
                        printf("After paying for pop, credit is %d\n",credit);
                        if (credit < 0){printf("Wow it went into negative sad"); return 0;}
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

    
    printf("The credit never went into negative. So we can use 1 as the amortised cost.");
    

    return 0;
}