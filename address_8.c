#include <stdio.h>
#include <stdlib.h>
#define PAGE_SIZE 1024
int PAGE_TABLE[] = {5, 3, 7, 1};
int PAGE_TABLE_SIZE = sizeof(PAGE_TABLE) / sizeof(PAGE_TABLE[0]);

int translate_address(int virtual_address) {
    int page_number = virtual_address / PAGE_SIZE;
    int offset = virtual_address % PAGE_SIZE;
    if (page_number >= PAGE_TABLE_SIZE) return -1;
    return PAGE_TABLE[page_number] * PAGE_SIZE + offset;
}

int main() {
    int virtual_address;
    printf("Enter the virtual address: ");
    scanf("%d", &virtual_address);
    int physical_address = translate_address(virtual_address);
    if (physical_address != -1)
        printf("Virtual address %d translates to physical address %d\n", virtual_address, physical_address);
    else
        printf("Page fault! Virtual address %d is not in the page table.\n", virtual_address);
    return 0;
}
