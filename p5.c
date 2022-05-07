#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

void shift1(char out[], int code, char instruct[], FILE *fp, int times, int y);
void shift2(char out[], int code, char instruct[], FILE *fp, int times, int y);
void caesar(char out[], int code, char instruct[], FILE *fp, int times, int y);
void binary(char out[], int code, char instruct[], FILE *fp, int times, int y);
void reverseArray(int binary[], int size);

int main(int argc, char* argv[]) {
    char out[300] = "";
    int code;
    char instruct[100];
    strcpy(instruct, argv[3]);
    int len = strlen(instruct);
    instruct[len] = '\0';
    int times;
    char* num;

    if(argc != 4) {
        printf("Invalid number of arguments, must be exactly 4\n");
        return 0;
    }

    char* input = argv[1];
    FILE *fp = fopen(input, "r");

    if(!fp) {
        printf("Could not open file '%s'\n", argv[1]);
        return 0;
    }

    if(strcmp(argv[2], "encode") == 0) {
        code = 1;
    }

    else if(strcmp(argv[2], "decode") == 0) {
        code = 0;
    }

    else {
        printf("Invalid option, must be 'encode' or 'decode'!\n");
        return 0;
    }

    int y = 0;

    while(1) {
        fscanf(fp, "%c", &out[y]);

        if(feof(fp)) {
            break;
        }

        y++;
    }

    out[y] = '\0';

    int i = 0;

    while(1) {

        if(isdigit(instruct[i])) {
            i++;
            if(isdigit(instruct[i]) && instruct[i] != '\0') {
                printf("Please enter a valid number for the encryption task '%c'!\n", instruct[i - 2]);
                return 0;
            }
        }

        else if(instruct[i] == 'L') {
            num = &instruct[i + 1];
            instruct[len] = '\0';
            times = atoi(num);
            
            shift1(out, code, instruct, fp, times, y);
            i++;
        }

        else if(instruct[i] == 'R') {
            num = &instruct[i + 1];
            times = atoi(num);

            shift2(out, code, instruct, fp, times, y);
            i++;
        }

        else if(instruct[i] == 'C') {
            num = &instruct[i + 1];
            times = atoi(num);

            caesar(out, code, instruct, fp, times, y);
            i++;
        }

        else if(instruct[i] == 'B') {
            num = &instruct[i + 1];
            times = atoi(num);

            binary(out, code, instruct, fp, times, y);
            i++;
        }

        else {
            if(code == 1) {
                printf("I cannot encrypt the message with task '%c'!\n", instruct[i]);
                return 0;
            }

            else if(code == 0) {
                printf("I cannot decrypt the message with task '%c'!\n", instruct[i]);
                return 0;
            }
        }

        if(i == len) {
            break;
        }
    }

    printf("%s", out);
    
    fclose(fp);
    return 0;
}

void shift1(char out[], int code, char instruct[], FILE *fp, int times, int y){
    char temp;
    char letter;
    char checkLet;
    char build[100] = "";
    int j = 0;
    int letCount = 0;
    int letWord = 0;
    int flag;

    if(code == 1) {
        for(int i = 0; i < times; i++) {
            letCount = 0;
            letWord = 0;
            j = 0;

            while(1) {
                
                letter = out[j];
                checkLet = out[j + 1];
                flag = 0;

                if(checkLet == ' ' || checkLet == '\n') {
                    temp = letter;
                }

                if(letter == '\0') {
                    temp = out[j - 1];
                    build[j - letWord] = temp;
                    break;
                }
                
                if(letter != ' ' && letter != '\n') {
                    build[j] = out[j - 1];
                }

                else if(letter == ' ') {
                    build[j] = '\n';
                    build[j - letWord] = temp;
                    flag = 1;
                }

                else if(letter == '\n') {
                    build[j] = '\n';
                    build[j - letWord] = temp;
                    flag = 1;
                }

                j++;
                letCount++;
                letWord++;

                if(flag == 1) {
                    letWord = 0;
                }
            }

            for(int k = 0; k < letCount; k++) {
                out[k] = build[k];
            }
        }
    }

    if(code == 0) {
        for(int i = 0; i < times; i++) {
            letCount = 0;
            letWord = 0;
            j = 0;

            while(1) {
                
                letter = out[j];
                checkLet = out[j + 1];
                flag = 0;

                if(letWord == 0) {
                    temp = letter;
                }

                if(checkLet == ' ' || checkLet == '\n') {
                    build[j] = temp;
                }
                
                else if(letter != ' ' && letter != '\n') {
                    build[j] = out[j + 1];
                }

                else if(letter == ' ') {
                    build[j] = '\n';
                    flag = 1;
                }

                else if(letter == '\n') {
                    build[j] = '\n';
                    flag = 1;
                }

                if(letter == '\0') {
                    build[j - 1] = temp;
                    break;
                }

                j++;
                letCount++;
                letWord++;

                if(flag == 1) {

                    letWord = 0;
                }
            }
            for(int k = 0; k < letCount; k++) {
                out[k] = build[k];
            }
        }
    }
}


void shift2(char out[], int code, char instruct[], FILE *fp, int times, int y) {
    char temp;
    char letter;
    char checkLet;
    char build[300] = "";
    int j = 1;
    int letCount = 0;
    int letWord = 0;
    int flag;

    if(code == 0) {
        for(int i = 0; i < times; i++) {
            letCount = 0;
            letWord = 0;
            j = 0;

            while(1) {
                
                letter = out[j];
                checkLet = out[j + 1];
                flag = 0;

                if(checkLet == ' ' || checkLet == '\n') {
                    temp = letter;
                }

                if(letter == '\0') {
                    temp = out[j - 1];
                    build[j - letWord] = temp;
                    break;
                }
                
                if(letter != ' ' && letter != '\n') {
                    build[j] = out[j - 1];
                }

                else if(letter == ' ') {
                    build[j] = '\n';
                    build[j - letWord] = temp;
                    flag = 1;
                }

                else if(letter == '\n') {
                    build[j] = '\n';
                    build[j - letWord] = temp;
                    flag = 1;
                }

                j++;
                letCount++;
                letWord++;

                if(flag == 1) {
                    letWord = 0;
                }
            }

            for(int k = 0; k < letCount; k++) {
                out[k] = build[k];
            }
        }
    }

    if(code == 1) {
        for(int i = 0; i < times; i++) {
            letCount = 0;
            letWord = 0;
            j = 0;

            while(1) {
                
                letter = out[j];
                checkLet = out[j + 1];
                flag = 0;

                if(letter == '\0') {
                    break;
                }

                if(letWord == 0) {
                    temp = letter;
                }

                if(checkLet == ' ' || checkLet == '\n') {
                    build[j] = temp;
                }
                
                else if(letter != ' ' && letter != '\n') {
                    build[j] = out[j + 1];
                }

                else if(letter == ' ') {
                    build[j] = '\n';
                    flag = 1;
                }

                else if(letter == '\n') {
                    build[j] = '\n';
                    flag = 1;
                }

                j++;
                letCount++;
                letWord++;

                if(flag == 1) {

                    letWord = 0;
                }
            }
            for(int k = 0; k < letCount; k++) {
                out[k] = build[k];
            }
        }
    }
}

void caesar(char out[], int code, char instruct[], FILE *fp, int times, int y) {
    int i = 0;
    int wrap;
    char build[400] = "";
    
    if(code == 1) {
        while(1) {
            if(out[i] == '\0') {
                break;
            }

            else if(out[i] == '\n') {
                build[i] = '\n';
            }

            else if(out[i] == ' ') {
                build[i] = '\n';
            }

            else if((out[i] - times) < 33) {
                wrap = 127 - (times - (out[i] - 33));
                build[i] = out[i] + (wrap - out[i]);
            }

            else {
                build[i] = out[i] - times;
            }

            i++;
        }
    }

    else if(code == 0) {
        while(1) {
            if(out[i] == '\0') {
                break;
            }

            else if(out[i] == '\n') {
                build[i] = '\n';
            }

            else if(out[i] == ' ') {
                build[i] = '\n';
            }

            else if((out[i] + times) > 126) {
                wrap = (32 + (out[i] + times) - 126);
                build[i] = out[i] + (wrap - out[i]);
            }

            else {
                build[i] = out[i] + times;
            }

            i++;
        }
    }

    for(int k = 0; k < i; k++) {
        out[k] = build[k];
    }
}

void binary(char out[], int code, char instruct[], FILE *fp, int times, int y) {
    int n = times;
    int binary[15];
    int i = 0;
    int j = 0;
    int k = 0;
    char build[400];

    for(i; n > 0; i++) {
        binary[i] = n % 2;
        n = n/2;
    }

    reverseArray(binary, i);

    if(code == 1) {
        while(1) {
            //printf("%d\n", binary[j]);
            if(out[k] == '\0') {
                break;
            }

            else if(out[k] == '\n') {
                out[k] = '\n';
                j = 0;
            }

            else if(out[k] == ' ') {
                out[k] = '\n';
                j = 0;
            }

            else if(out[k] == 125) {
                out[k] = 125;
            }

            else if((out[k] > 47 && out[k] < 58) || (out[k] > 64 && out[k] < 91) || (out[k] > 96 && out[k] < 123)) {
                if(binary[j] == 1) {
                    if(out[k] == 122) {
                        out[k] = 97;
                    }

                    else if(out[k] == 90) {
                        out[k] = 65;
                    }

                    else if(out[k] == 57) {
                        out[k] = 48;
                    }

                    else {
                        out[k] = out[k] + 1;
                    }
                }

                else if(binary[j] == 0) {
                    if(out[k] == 97) {
                        out[k] = 122;
                    }

                    else if(out[k] == 65) {
                        out[k] = 90;
                    }

                    else if(out[k] == 48) {
                        out[k] = 57;
                    }

                    else {
                        out[k] = out[k] - 1;
                    }
                }
            }

            if(out[k] != '\n' && out[k] != ' ') {
                j++;
            }

            k++;

            if(j > i - 1) {
                j = 0;
            }
        }
    }

    else if(code == 0) {
        while(1) {

            if(out[k] == '\n') {
                out[k] = '\n';
                j = 0;
            }

            else if(out[k] == ' ') {
                out[k] = '\n';
                j = 0;
            }

            if(out[k] == '\0') {
                break;
            }

            else if((out[k] > 47 && out[k] < 58) || (out[k] > 64 && out[k] < 91) || (out[k] > 96 && out[k] < 123)) {
                if(binary[j] == 1) {
                    if(out[k] == 97) {
                        out[k] = 122;
                    }

                    else if(out[k] == 65) {
                        out[k] = 90;
                    }

                    else if(out[k] == 48) {
                        out[k] = 57;
                    }

                    else {
                        out[k] = out[k] - 1;
                    }
                }

                else if(binary[j] == 0) {
                    if(out[k] == 122) {
                        out[k] = 97;
                    }

                    else if(out[k] == 90) {
                        out[k] = 65;
                    }

                    else if(out[k] == 57) {
                        out[k] = 48;
                    }

                    else {
                        out[k] = out[k] + 1;
                    }
                }
            }

            if(out[k] != '\n' && out[k] != ' ') {
                j++;
            }

            k++;

            if(j > i - 1) {
                j = 0;
            }
        }

    }
}

void reverseArray(int binary[], int size) {
    int temp[10];

    for(int i = 0; i < size; i++) {
        temp[size - 1 - i] = binary[i];
    }

    for(int i = 0; i < size; i++) {
        binary[i] = temp[i];
    }
}