#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

int main() {
    int n;
    char ch, buffer[1000];
    FILE *fp;
    int i = 0, push_count = 0, pop_count = 0;
    int brace_count = 0;
    int inside_main = 0;
    int total = 0;

    fp = fopen("program.txt", "r");

    if(fp == NULL) {
        printf("Error while opening the file\n");
        exit(0);
    }
    printf("Let the potential function be the number of elements in the stack\nphi(0) = 0");
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
                        printf("phi(D_k-1) = %d\n", n);
                        n++;
                        printf("phi(D_k) = %d\n", n);
                        printf("Amortized cost = 1 + 1 = 2\n");

                        total+=2;
                    } else if(strcmp(buffer, "pop") == 0) {
                        printf("phi(D_k-1) = %d\n", n);
                        n--;
                        printf("phi(D_k) = %d\n", n);
                        printf("Amortized cost = 1 + (- 1) = 0\n");
                        
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

    
    
    
    printf("Total cost is O(%d)\n", total);
    

    return 0;
}