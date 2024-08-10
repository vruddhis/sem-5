#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#define MAX_BUFFER 1024

typedef struct {
    char *numIterations;
    char *iterator;
    char *start_var;
    char *end_var;
    char *constant;
    char *operation;
} ParseResult;


int findClosingBracket(char *code, int openBracketIndex) {
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


int is_integer(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isdigit(str[i])) return 0;
    }
    return 1;
}
ParseResult* parse_for_loop(char *line) {
    ParseResult *result = (ParseResult *)malloc(sizeof(ParseResult));
    if (result == NULL) {
        return NULL;
    }
    result->numIterations = NULL;
    result->iterator = NULL;
    result->start_var = NULL;
    result->end_var = NULL;
    result->constant = NULL;
    result->operation = NULL;

    char start_var[50], end_var[50], something[4], constant[50], iterator[50];
    char condition[4];
    int i = 0;

    if (line == NULL) {
        free(result);
        return NULL;
    }
    while (line[i] != '(' && line[i] != '\0') {
        i++;
    }
    if (line[i] == '\0') {
        free(result);
        return NULL;
    }
    i++;

    int j = 0;
    while (line[i] != '=' && line[i] != '\0') {
        if (!isspace(line[i])) {
            iterator[j++] = line[i];
        }
        i++;
    }
    iterator[j] = '\0';
    if (strncmp(iterator, "int", 3) == 0) {
        memmove(iterator, iterator + 3, strlen(iterator) - 2);
    }

    result->iterator = strdup(iterator);

    while (line[i] == ' ' || line[i] == '\t') {
        i++;
    }

    if (line[i] == '\0' || line[i] != '=') {
        free(result->iterator);
        free(result);
        return NULL;
    }
    i++;

    j = 0;
    while (line[i] != ';' && line[i] != '\0' && !isspace(line[i])) {
        start_var[j++] = line[i++];
    }
    start_var[j] = '\0';
    result->start_var = strdup(start_var);

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

    while (line[i] == ' ' || line[i] == '\t') {
        i++;
    }

    j = 0;
    while (line[i] != ';' && line[i] != '\0' && !isspace(line[i])) {
        end_var[j++] = line[i++];
    }
    end_var[j] = '\0';
    result->end_var = strdup(end_var);

    while (line[i] == ' ' || line[i] == '\t') {
        i++;
    }

    j = 0;
    if (line[i] == '+' && line[i+1] == '+') {
        strcpy(something, "+=");
        strcpy(constant, "1");
        i += 2;
    } else if (line[i] == '-' && line[i+1] == '-') {
        strcpy(something, "-=");
        strcpy(constant, "1");
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
            strcpy(constant, "1");
        } else {
            while (line[i] == ' ' || line[i] == '\t') {
                i++;
            }

            j = 0;
            while (line[i] != ')' && line[i] != '\0' && !isspace(line[i])) {
                 constant[j++] = line[i++];
            }
            constant[j] = '\0';

            if (strlen(constant) == 0) {
                strcpy(constant, "1");
            }
        }
    }

    if (strcmp(something, "+") == 0 && strcmp(constant, "+") == 0) {
        strcpy(something, "+=");
        strcpy(constant, "1");
    } else if (strcmp(something, "-") == 0 && strcmp(constant, "-") == 0) {
        strcpy(something, "-=");
        strcpy(constant, "1");
    }

    result->operation = strdup(something);
    result->constant = strdup(constant);

    result->numIterations = (char *)malloc(100 * sizeof(char));
    if (result->numIterations == NULL) {
        free(result->iterator);
        free(result->start_var);
        free(result->end_var);
        free(result->constant);
        free(result->operation);
        free(result);
        return NULL;
    }

    if (strcmp(something, "*=") == 0) {
        if (is_integer(constant)) {
            if (is_integer(start_var) && is_integer(end_var)) {
                snprintf(result->numIterations, 100, "1");
            } else if (is_integer(start_var)) {
                snprintf(result->numIterations, 100, "log(%s)", end_var);
            } else if (is_integer(end_var)) {
                snprintf(result->numIterations, 100, "log(1/%s)", start_var);
            } else {
                snprintf(result->numIterations, 100, "log(%s / %s)", end_var, start_var);
            }
        } else {
            if (is_integer(start_var) && is_integer(end_var)) {
                snprintf(result->numIterations, 100, "log(%s / %s) / log(%s)", end_var, start_var, constant);
            } else if (is_integer(start_var)) {
                snprintf(result->numIterations, 100, "log(%s) / log(%s)", end_var, constant);
            } else if (is_integer(end_var)) {
                snprintf(result->numIterations, 100, "log(%s) / log(%s)", constant, start_var);
            } else {
                snprintf(result->numIterations, 100, "log(%s / %s) / log(%s)", end_var, start_var, constant);
            }
        }
    } else if (strcmp(something, "/=") == 0) {
        if (is_integer(constant)) {
            if (is_integer(start_var) && is_integer(end_var)) {
                snprintf(result->numIterations, 100, "1");
            } else if (is_integer(start_var)) {
                snprintf(result->numIterations, 100, "log(%s)", start_var);
            } else if (is_integer(end_var)) {
                snprintf(result->numIterations, 100, "log(%s)", end_var);
            } else {
                snprintf(result->numIterations, 100, "log(%s / %s)", start_var, end_var);
            }
        } else {
            if (is_integer(start_var) && is_integer(end_var)) {
                snprintf(result->numIterations, 100, "log(%s / %s) / log(%s)", start_var, end_var, constant);
            } else if (is_integer(start_var)) {
                snprintf(result->numIterations, 100, "log(%s) / log(%s)", start_var, constant);
            } else if (is_integer(end_var)) {
                snprintf(result->numIterations, 100, "log(%s) / log(%s)", end_var, constant);
            } else {
                snprintf(result->numIterations, 100, "log(%s / %s) / log(%s)", start_var, end_var, constant);
            }
        }
    } else if (strcmp(something, "+=") == 0 || strcmp(something, "-=") == 0) {
        if (is_integer(constant)) {
            if (is_integer(start_var) && is_integer(end_var)) {
                snprintf(result->numIterations, 100, "1");
            } else if (is_integer(start_var)) {
                snprintf(result->numIterations, 100, "%s", end_var);
            } else if (is_integer(end_var)) {
                snprintf(result->numIterations, 100, "1/%s", start_var);
            } else {
                snprintf(result->numIterations, 100, "%s - %s", end_var, start_var);
            }
        } else {
            if (is_integer(start_var) && is_integer(end_var)) {
                snprintf(result->numIterations, 100, "%s", end_var);
            } else if (is_integer(start_var)) {
                snprintf(result->numIterations, 100, "%s", end_var);
            } else if (is_integer(end_var)) {
                snprintf(result->numIterations, 100, "%s", start_var);
            } else {
                snprintf(result->numIterations, 100, "%s - %s", end_var, start_var);
            }
        }
    } else {
        snprintf(result->numIterations, 100, "Unknown operation: %s", something);
    }

    return result;
}
char* timeComplexity(  char *code) {
    char *result = (char *)malloc(100 * sizeof(char));
    if (result == NULL) {
        perror("Memory allocation failed");
        exit(0);
    }
    strcpy(result, "1");

      char *ptr = code;

    while (*ptr != '\0') {
        if (strncmp(ptr, "for", 3) == 0) {
              char *startOfForLoop = ptr;
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
                exit(0);
            }
            strncpy(for_loop_line, startOfForLoop, ptr - startOfForLoop);
            for_loop_line[ptr - startOfForLoop] = '\0';
            ParseResult *parseResult = parse_for_loop(for_loop_line);
            
            char *numIterations = parseResult->numIterations;
            char *iterator = parseResult->iterator;
            char *innerComplexity = timeComplexity(code + startBracketIndex + 1);
            

            char tempResult[200];
            if (strcmp(result, "1") == 0) {
                snprintf(tempResult, sizeof(tempResult), "%s * %s", numIterations, innerComplexity);
                strcpy(result, tempResult);
            } else {
                snprintf(tempResult, sizeof(tempResult), "%s + %s * %s", result, numIterations, innerComplexity);
                strcpy(result, tempResult);
            }

            free(innerComplexity);
            free(numIterations);
            free(iterator);
            free(parseResult);
            free(for_loop_line);
            ptr = code + endBracketIndex + 1;
            
        } else {
            ptr++;
        }
    }

    return result;
}


int main() {
    char *result;
    char *testCode1 = "for (int i = 1; i < n; i += 2) { for (int j = 0; j < m; j++) { /* code */ } }";
    char *testCode2 = "for (int i = 0; i < n; i*=k) { /* code */ }";
    char *testCode3 = "for (int i = 1; i < n; i++) { for (int j = 0; j < i; j++) { /* code */ } }";
    
    result = timeComplexity(testCode1);
    printf("Test 1 Result: O(%s)\n", result);
    free(result);
    result = timeComplexity(testCode2);
    printf("Test 2 Result: O(%s)\n", result);
    free(result);
    result = timeComplexity(testCode3);
    printf("Test 3 Result: O(%s)\n", result);
    free(result);

    return 0;
}