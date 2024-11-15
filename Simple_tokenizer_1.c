#include <stdio.h>
#include <ctype.h>
#include <string.h>
void simple_tokenizer(const char *text) {
    const char *ptr = text;
    while (*ptr != '\0') {
        if (isspace(*ptr)) {
            ptr++;
            continue;
        }
        if (isdigit(*ptr)) {
            while (isdigit(*ptr)) {
                putchar(*ptr);
                ptr++;
            }
            putchar('\n');
        }
        else if (isalpha(*ptr)) {
            while (isalpha(*ptr)) {
                putchar(*ptr);
                ptr++;
            }
            putchar('\n');
        }
        else {
            putchar(*ptr);
            putchar('\n');
            ptr++;
        }
    }
}
int main() {
    const char *text = "Hello, world! This is a tokenizer example with numbers 123.";
    simple_tokenizer(text);
    return 0;
}