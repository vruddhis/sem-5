#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#define MAX_BUFFER 1024
int isForLoop(const char *line) {
    return strstr(line, "for") != NULL;
}



int findClosingBracket(const char *code, int openBracketIndex) {
    int count = 0;
    for (int i = openBracketIndex; code[i] != '\0'; i++) {
        if (code[i] == '{') {
            count++;
        } else if (code[i] == '}') {
            count--;
            if (count == 0) {
                return i;
            }
        }
    }
    return -1;  
}


bool is_integer(const char *str) {
    if (*str == '\0') return false;
    if (*str == '-' || *str == '+') str++;  
    if (*str == '\0') return false;
    while (*str) {
        if (!isdigit(*str)) return false;
        str++;
    }
    return true;
}

char* parse_for_loop(const char *line) {
    char start_var[50], end_var[50], constant_var[50];
    char condition[4];
    char something[4];
    int i = 0;

    if (line == NULL) {
        return NULL;
    }

    while (line[i] != '=' && line[i] != '\0') {
        i++;
    }
    if (line[i] == '\0') {
        return NULL;
    }
    i++;

    int j = 0;
    while (line[i] != ';' && line[i] != '\0' && !isspace(line[i])) {
        start_var[j++] = line[i++];
    }
    start_var[j] = '\0';
    printf("Start: %s\n", start_var);

    j = 0;
    while (line[i] != '\0') {
        if (line[i] == '>' || line[i] == '<') {
            condition[j++] = line[i++];
            if (line[i] == '=') {
                condition[j++] = line[i++];
            }
            condition[j] = '\0';
            break;
        }
        i++;
    }

    if (j > 0) {
        printf("Condition: %s\n", condition);
    }

    while (line[i] == ' ' || line[i] == '\t') {
        i++;
    }

    j = 0;
    while (line[i] != ';' && line[i] != '\0' && !isspace(line[i])) {
        end_var[j++] = line[i++];
    }
    end_var[j] = '\0';
    printf("End: %s\n", end_var);

    while (line[i] == ' ' || line[i] == '\t') {
        i++;
    }

    j = 0;
    if (line[i] == '+' && line[i+1] == '+') {
        strcpy(something, "+=");
        strcpy(constant_var, "1");
        i += 2;
    } else if (line[i] == '-' && line[i+1] == '-') {
        strcpy(something, "-=");
        strcpy(constant_var, "1");
        i += 2;
    } else {
        while (line[i] != '\0' && line[i] != ')') {
            if (line[i] == '+' || line[i] == '-' || line[i] == '*' || line[i] == '/') {
                something[j++] = line[i++];
                if (line[i] == '=') {
                    something[j++] = line[i++];
                }
                something[j] = '\0';
                break;
            }
            i++;
        }

        if (j == 0) {
            strcpy(something, "");
            strcpy(constant_var, "1");
        } else {
            while (line[i] == ' ' || line[i] == '\t') {
                i++;
            }

            j = 0;
            while (line[i] != ')' && line[i] != '\0' && !isspace(line[i])) {
                constant_var[j++] = line[i++];
            }
            constant_var[j] = '\0';

            if (strlen(constant_var) == 0) {
                strcpy(constant_var, "1");
            }
        }
    }

    if (strcmp(something, "+") == 0 && strcmp(constant_var, "+") == 0) {
        strcpy(something, "+=");
        strcpy(constant_var, "1");
    } else if (strcmp(something, "-") == 0 && strcmp(constant_var, "-") == 0) {
        strcpy(something, "-=");
        strcpy(constant_var, "1");
    }

    printf("Something: %s\n", something);
    printf("Constant: %s\n", constant_var);

    char *numIterations = (char *)malloc(100 * sizeof(char));
    if (numIterations == NULL) {
        return NULL;
    }

    if (strcmp(something, "*=") == 0) {
        if (is_integer(constant_var)) {
            if (is_integer(start_var) && is_integer(end_var)) {
                snprintf(numIterations, 100, "1");
            } else if (is_integer(start_var)) {
                snprintf(numIterations, 100, "log(%s)", end_var);
            } else if (is_integer(end_var)) {
                snprintf(numIterations, 100, "log(1/%s)", start_var);
            } else {
                snprintf(numIterations, 100, "log(%s / %s)", end_var, start_var);
            }
        } else {
            if (is_integer(start_var) && is_integer(end_var)) {
                snprintf(numIterations, 100, "log(%s / %s) / log(%s)", end_var, start_var, constant_var);
            } else if (is_integer(start_var)) {
                snprintf(numIterations, 100, "log(%s) / log(%s)", end_var, constant_var);
            } else if (is_integer(end_var)) {
                snprintf(numIterations, 100, "log(%s) / log(%s)", constant_var, start_var);
            } else {
                snprintf(numIterations, 100, "log(%s / %s) / log(%s)", end_var, start_var, constant_var);
            }
        }
    } else if (strcmp(something, "/=") == 0) {
        if (is_integer(constant_var)) {
            if (is_integer(start_var) && is_integer(end_var)) {
                snprintf(numIterations, 100, "1");
            } else if (is_integer(start_var)) {
                snprintf(numIterations, 100, "log(%s)", start_var);
            } else if (is_integer(end_var)) {
                snprintf(numIterations, 100, "log(%s)", end_var);
            } else {
                snprintf(numIterations, 100, "log(%s / %s)", start_var, end_var);
            }
        } else {
            if (is_integer(start_var) && is_integer(end_var)) {
                snprintf(numIterations, 100, "log(%s / %s) / log(%s)", start_var, end_var, constant_var);
            } else if (is_integer(start_var)) {
                snprintf(numIterations, 100, "log(%s) / log(%s)", start_var, constant_var);
            } else if (is_integer(end_var)) {
                snprintf(numIterations, 100, "log(%s) / log(%s)", end_var, constant_var);
            } else {
                snprintf(numIterations, 100, "log(%s / %s) / log(%s)", start_var, end_var, constant_var);
            }
        }
    } else if (strcmp(something, "+=") == 0 || strcmp(something, "-=") == 0) {
        if (is_integer(constant_var)) {
            if (is_integer(start_var) && is_integer(end_var)) {
                snprintf(numIterations, 100, "1");
            } else if (is_integer(start_var)) {
                snprintf(numIterations, 100, "%s", end_var);
            } else if (is_integer(end_var)) {
                snprintf(numIterations, 100, "1/%s", start_var);
            } else {
                snprintf(numIterations, 100, "%s - %s", end_var, start_var);
            }
        } else {
            if (is_integer(start_var) && is_integer(end_var)) {
                snprintf(numIterations, 100, "%s", end_var);
            } else if (is_integer(start_var)) {
                snprintf(numIterations, 100, "%s", end_var);
            } else if (is_integer(end_var)) {
                snprintf(numIterations, 100, "%s", start_var);
            } else {
                snprintf(numIterations, 100, "%s - %s", end_var, start_var);
            }
        }
    } else {
        snprintf(numIterations, 100, "Unknown operation: %s", something);
    }
    return numIterations;
}


char* timeComplexity(const char *code) {
    char *result = (char *)malloc(100 * sizeof(char));
    if (result == NULL) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    strcpy(result, "1");

    const char *ptr = code;

    while (*ptr != '\0') {
        
        if (strncmp(ptr, "for", 3) == 0) {

            const char *startOfForLoop = ptr;
            while (*ptr != '{' && *ptr != '\0') {
                ptr++;
            }
            if (*ptr == '\0') {
                break;
            }

            int startBracketIndex = ptr - code;  
            int endBracketIndex = findClosingBracket(code, startBracketIndex);
            if (endBracketIndex == -1) {
                break;
            }
           

            char *for_loop_line = (char *)malloc((ptr - startOfForLoop + 1) * sizeof(char));
            if (for_loop_line == NULL) {
                perror("Memory allocation failed");
                exit(EXIT_FAILURE);
            }
            strncpy(for_loop_line, startOfForLoop, ptr - startOfForLoop);
            for_loop_line[ptr - startOfForLoop] = '\0';

            

            char *numIterations = parse_for_loop(for_loop_line);
            if (numIterations == NULL) {
                
                free(for_loop_line);
                break;
            }
            
            char *innerComplexity = timeComplexity(code + startBracketIndex + 1);
            if (innerComplexity == NULL) {
               
                free(numIterations);
                free(for_loop_line);
                break;
            }
          

            if (strcmp(result, "1") == 0) {
                strcpy(result, numIterations);
                strcat(result, " * ");
                strcat(result, innerComplexity);
            } else {
                strcat(result, "+ ");
                strcat(result, numIterations);
                strcat(result, " * ");
                strcat(result, innerComplexity);
            }

            free(innerComplexity);
            free(numIterations);
            free(for_loop_line);
            ptr = code + endBracketIndex + 1;
            
        } else {
            ptr++;
        }
    }
    return result;
}

 
int main() {
   
    char *testCode = 
    "for (int i=0; i<n; i*=2){for (int j=0; j<m; j++) {count++;}}}";

    char *complexity = timeComplexity(testCode);
    printf("Time Complexity: %s\n", complexity);

    free(complexity);
    return 0;
}