#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SYMBOLS 100
#define MAX_NAME_LENGTH 50

struct Symbol {
    char name[MAX_NAME_LENGTH];
    int address;
};

struct SymbolTable {
    struct Symbol symbols[MAX_SYMBOLS];
    int size;
};

void initSymbolTable(struct SymbolTable *table) {
    table->size = 0;
}

int searchSymbol(struct SymbolTable *table, const char *name) {
    int i;
    for (i = 0; i < table->size; i++) {
        if (strcmp(table->symbols[i].name, name) == 0) {
            return i;
        }
    }
    return -1;
}

void insertSymbol(struct SymbolTable *table, const char *name, int address) {
    if (table->size >= MAX_SYMBOLS) {
        printf("Symbol table is full.\n");
        return;
    }

    if (searchSymbol(table, name) != -1) {
        printf("Duplicate symbol.\n");
        return;
    }

    strcpy(table->symbols[table->size].name, name);
    table->symbols[table->size].address = address;
    table->size++;
    printf("Symbol inserted successfully.\n");
}

void displaySymbolTable(struct SymbolTable *table) {
    int i;
    printf("\nSymbol Table:\n");
    printf("Name\tAddress\n");
    for (i = 0; i < table->size; i++) {
        printf("%s\t%d\n", table->symbols[i].name, table->symbols[i].address);
    }
}

void deleteSymbol(struct SymbolTable *table, const char *name) {
    int index = searchSymbol(table, name);
    if (index == -1) {
        printf("Symbol not found.\n");
        return;
    }

    int i; 
    for (i = index; i < table->size - 1; i++) {
        table->symbols[i] = table->symbols[i + 1];
    }
    table->size--;
    printf("Symbol deleted successfully.\n");
}

void modifySymbol(struct SymbolTable *table, const char *name, int newAddress) {
    int index = searchSymbol(table, name);
    if (index == -1) {
        printf("Symbol not found.\n");
        return;
    }

    table->symbols[index].address = newAddress;
    printf("Symbol modified successfully.\n");
}

int main() {
    struct SymbolTable table;
    initSymbolTable(&table);
    int choice, address;
    char name[MAX_NAME_LENGTH];
    int index; 

    while (1) {
        printf("\n1. Insert\n2. Display\n3. Delete\n4. Search\n5. Modify\n6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter symbol name: ");
                scanf("%s", name);
                printf("Enter address: ");
                scanf("%d", &address);
                insertSymbol(&table, name, address);
                break;
            case 2:
                displaySymbolTable(&table);
                break;
            case 3:
                printf("Enter symbol name to delete: ");
                scanf("%s", name);
                deleteSymbol(&table, name);
                break;
            case 4:
                printf("Enter symbol name to search: ");
                scanf("%s", name);
                index = searchSymbol(&table, name); 
                if (index != -1) {
                    printf("Symbol found at index %d, address: %d\n", index, table.symbols[index].address);
                } else {
                    printf("Symbol not found.\n");
                }
                break;
            case 5:
                printf("Enter symbol name to modify: ");
                scanf("%s", name);
                printf("Enter new address: ");
                scanf("%d", &address);
                modifySymbol(&table, name, address);
                break;
            case 6:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

