#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/**
 * @brief Get the File object
 * 
 * @param path relative path to the File
 * @return FILE* if file existed: File, else: Null
 */
FILE* getFile(char* path) {
    FILE* fp = fopen(path, "r");
    if (fp == NULL) {
        printf("Error: Couldnt open file %s", path);
        return NULL;
    }
    return fp;
} 

/**
 * @brief Get the Next Line object
 * 
 * @param fp File with read rights
 * @param MAX_LENGTH Max length of bytes which are read per line
 * @return char* line content with length max_length
 */
char* getNextLine(FILE* fp, const unsigned MAX_LENGTH) {
    char* buffer = malloc(sizeof(char) * MAX_LENGTH);
    if (fgets(buffer, MAX_LENGTH, fp)) {
        return buffer;
    } else {
        return NULL;
    }
}

/**
 * @brief removes blank spaces generated by reading lines by a larger buffer
 * 
 * @param str string which has to be cleaned up
 * @return char* string without unnessesary blank spaces
 */
char* clearString(char* str) {
    return strtok(str, "\n");
}

/**
 * @brief returns the length of a string
 * 
 * @param str string with terminal '\0'
 * @return int length of the string
 */
int getLength(char* str) {
    int i = 0; 
    while (str[i] != '\0') {
        i++;
    }
    return i;
}

char *reverse(const char * __restrict const s) {
    if (s == NULL)
        return NULL;
    size_t i, len = strlen(s);
    char *r = malloc(len + 1);

    for(i = 0; i < len; ++i)
        r[i] = s[len - i - 1];
    r[len] = 0;
    return r;
}

char *rstrstr(char *__restrict s1, char *__restrict s2) {
    size_t  s1len = strlen(s1);
    size_t  s2len = strlen(s2);
    char *s;

    if (s2len > s1len)
        return NULL;
    for (s = s1 + s1len - s2len; s >= s1; --s)
        if (strncmp(s, s2, s2len) == 0)
        return s;
    return NULL;
}


int parseLine(char* str) {
    int n = getLength(str);
    char* num = (char*)(malloc(2));


    int l = -1;
    int r = -1;

    for (int i = 0; i < n; i++) {
        if (str[i] >= 48 && str[i] <= 57) {
            if (l == -1) {
                l = i;
            } else {
                r = i;
            }
        }
    }
    if (r != -1) {
        num[0] = str[l];
        num[1] = str[r];
    } else {
        num[0] = str[l];
        num[1] = str[l];
    }


    int nu = atoi(num);
    free(num);
    return nu;
}

int substring(char* str) {
    int l = -1;
    int r = -1;
    char* lptG = 0;

    char* lPoint = str + 256;
    char* rPoint;

    char* possibleStr[] = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};


    for (int i = 0; i < 10; i++) {
        rPoint = strstr(str, possibleStr[i]);
        if (rPoint != NULL) { 
            // printf("found %s in %s\n", possibleStr[i], str);
            if (rPoint < lPoint) {
                l = i;
                lPoint = rPoint;
            } 
            if (rPoint > lptG) {
                r = i;
                lptG = rPoint;
            }
            
        } else {
            rPoint = 0;
        }
    }

    // printf("found in %s: l: %d | r: %d \n", str, l, r);


    int n = getLength(str);
    for (int i = 0; i < n; i++) {
        if (str[i] >= 48 && str[i] <= 57) {
            if (str + i < lPoint) {
                char tmp = str[i];
                l = atoi(&tmp);
                lPoint = str + i;
                // printf("convert %c to %d\n", tmp, l);
            } else if (str + i > lptG) {
                char tmp = str[i];
                r = atoi(&(str[i]));
                lptG = str + i;
                // printf("convert %c to %d\n", tmp, r);
            }
        }
    }
    // printf("found in %s: l: %d | r: %d \n", str, l, r);

    for (int i = 0; i < 9; i++) {
        rPoint = rstrstr(str, possibleStr[i]);
        if (rPoint != NULL) { 
            // printf("found %s in %s\n", possibleStr[i], str);
            if (rPoint < lPoint) {
                l = i;
                lPoint = rPoint;
            } 
            if (rPoint > lptG) {
                r = i;
                lptG = rPoint;
            }
            
        } else {
            rPoint = 0;
        }
    }


    if (r == -1) r = l;
    return (l * 10) + r;
} 

int main() {
    FILE* input = getFile("input_1_2.txt");
    char* line = getNextLine(input, 256);
    
    int sum = 0;
    int i = 0;;
    while (line != NULL) {   
        
        int tmp = substring(line);
        sum += tmp != -11 ? tmp : 0;
        
        printf("----------------[%d]---------------\n", i);
        printf("%s -> %d\n", line, tmp, sum);
        
        free(line);
        line = getNextLine(input, 256);
    } 
    printf("%d", sum);
    return EXIT_SUCCESS;
}
