#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

struct ConstFold {
    char New_Str[10];
    char str[10];
} Opt_Data[20];

void ReadInput(char Buffer[], FILE *Out_file);
int Gen_Token(char str[], char Tokens[][10]);

int New_Index = 0;

int main() {
    FILE *In_file, *Out_file;
    char Buffer[100], temp[100], Token[20][10];
    int i, n, j, flag;

    In_file = fopen("Code_7.txt", "r");
    if (In_file == NULL) {
        printf("Error: Cannot open input file.\n");
        return 1;
    }

    Out_file = fopen("output.txt", "w");
    if (Out_file == NULL) {
        printf("Error: Cannot open output file.\n");
        fclose(In_file);
        return 1;
    }

    while (fgets(Buffer, sizeof(Buffer), In_file) != NULL) {
        strcpy(temp, Buffer);
        n = Gen_Token(temp, Token);

        flag = 0;
        for (i = 0; i < n; i++) {
            if (strcmp(Token[i], "=") == 0) {
                if (isdigit(Token[i + 1][0]) || Token[i + 1][0] == '.') {
                    flag = 1;
                    strcpy(Opt_Data[New_Index].New_Str, Token[i - 1]);
                    strcpy(Opt_Data[New_Index++].str, Token[i + 1]);
                }
            }
        }

        if (!flag) {
            for (i = 0; i < New_Index; i++) {
                for (j = 0; j < n; j++) {
                    if (strcmp(Opt_Data[i].New_Str, Token[j]) == 0) {
                        strcpy(Token[j], Opt_Data[i].str);
                    }
                }
            }
        }

        strcpy(temp, "");
        for (i = 0; i < n; i++) {
            strcat(temp, Token[i]);
            if (i < n - 1) strcat(temp, " ");
        }
        strcat(temp, "\n");

        fwrite(temp, strlen(temp), 1, Out_file);
    }

    fclose(In_file);
    fclose(Out_file);

    return 0;
}

int Gen_Token(char str[], char Token[][10]) {
    int i = 0, j = 0, k = 0;

    while (str[k] != '\0') {
        j = 0;

        while (str[k] == ' ' || str[k] == '\t') k++;

        while (str[k] != ' ' && str[k] != '\0' && str[k] != '=' && str[k] != '/' &&
               str[k] != '+' && str[k] != '-' && str[k] != '*' && str[k] != ',' && str[k] != ';') {
            Token[i][j++] = str[k++];
        }
        Token[i++][j] = '\0';

        if (str[k] == '=' || str[k] == '/' || str[k] == '+' ||
            str[k] == '-' || str[k] == '*' || str[k] == ',' || str[k] == ';') {
            Token[i][0] = str[k++];
            Token[i++][1] = '\0';
        }

        if (str[k] == '\0') break;
    }

    return i;
}
/* Input 
int main()  
{  
    float pi = 3.14, r = 5.0, a;  
    a = pi * r * r;  
    printf("a = %f", a);  
    return 0;  
}
*/
/* Expected output 
int main() 

{ 

float pi  = 3.14 , r  = 5.0 , a ; 

a 3.14 = pi 3.14 * r 3.14 * r ; 

printf("a 3.14 = %f" , a) ; 

return 0 ; 

}

*/