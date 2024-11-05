#include "assign6.h"

void pf(const char* format, ...)
{
    va_list arguments;
    va_start(arguments, format);
    vprintf(format, arguments);
    va_end(arguments);
    printf("\n");

}

void pef(const char* format, ...)
{
    printf("ERROR: ");
    va_list arguments;
    va_start(arguments, format);
    vprintf(format, arguments);
    va_end(arguments);
    printf("\n");
}


int main() {
    redirect(0);

    FILE* ip; // Inventory Pointer

    if (!(ip = fopen(inventory, "r")))
    {
        ip = fopen(inventory, "wb");

        if (!ip)
        {
            pef("File creation failed");
            return 1;
        }

        fclose(ip);
    }

    char buffer[10];

    printMenu;

    while (fgets(buffer, sizeof(buffer), stdin) != NULL)
    {
        buffer[strlen(buffer) - 1] = '\0';
        if (strlen(buffer) >= 2) buffer[0] = 'z';

        switch (buffer[0])
        {
        case 'c':
        case 'C':
            create(ip);
            break;
        case 'r':
        case 'R':
            read(ip);
            break;
        case 'u':
        case 'U':
            update(ip);
            break;
        case 'd':
        case 'D':
            delete(ip);
            break;
        default:
            pef("Invalid option");
            break;

        }


        printMenu;

        fclose(ip);

    }
    return 0;
}

void create(FILE* ip)
{
    byteCheck;
    openInv;
    if (exists)
    {
        pef("Item already exists");
        return;
    }
    Item create;

    char buffer[128];

    uString("Enter a simple name: ", create.simpleName);
    uString("Enter a item name: ", create.itemName);
    uString("Enter the current quantity: ", buffer);
    create.currentQuantity = strlen(buffer) == 0 ? 0 : atoi(buffer);
    uString("Enter the max quantity: ", buffer);
    create.maxQuantity = strlen(buffer) == 0 ? 1 : atoi(buffer);
    uString("Enter a description: ", create.body);


    fseek(ip, byte, SEEK_SET);
    fwrite(&create, itemSize, 1, ip);
    fflush(ip);

}

void read(FILE* ip)
{
    byteCheck;
    ip = fopen(inventory, "r");

    Item readFrom;
    getItem(readFrom);
    if (readFrom.maxQuantity == 0 )
    {
        pef("No item found");
        return;
    }

    pf("Item name: %s", readFrom.itemName);
    pf("Simple name: %s", readFrom.simpleName);
    pf("Current Quantity: %d", readFrom.currentQuantity);
    pf("Max Quantity: %d", readFrom.maxQuantity);
    pf("Body: %s\n", readFrom.body);

}
void update(FILE* ip)
{
    byteCheck;
    openInv;

    if (!exists)
    {
        pef("Item not found");
        return;
    }

    Item data;
    getItem(data);

    Item update;

    char buffer[128];

    uString("Enter a simple name: ", buffer);
    strcpy(update.simpleName, strlen(buffer) == 0 ? data.simpleName : buffer);
    uString("Enter a item name: ", buffer);
    strcpy(update.itemName, strlen(buffer) == 0 ? data.itemName : buffer);
    uString("Enter the current quantity: ", buffer);
    update.currentQuantity = strlen(buffer) == 0 ? data.currentQuantity : atoi(buffer);
    uString("Enter the max quantity: ", buffer);
    update.maxQuantity = strlen(buffer) == 0 ? data.maxQuantity : atoi(buffer);
    uString("Enter a description: ", buffer);
    strcpy(update.body, strlen(buffer) == 0 ? data.body : buffer);

    fseek(ip, byte, SEEK_SET);
    fwrite(&update, itemSize, 1, ip);
    fflush(ip);



}
void delete(FILE* ip)
{
    int i;
    byteCheck;
    openInv;


    Item item;
    getItem(item);

    if (!exists)
    {
        pef("Item not found");
        return;
    }

    for ( i = 0; i < itemSize; i++)
    {
        fseek(ip, i + byte, SEEK_SET);
        fwrite("\0", 1, 1, ip);
    }

    pf("%s was successfully deleted", item.simpleName);

}

int byteOffset()
{
    char num[10]; //9999
    char* numPtr;
    int retNum;

    pf("Enter an item number: ");
    fs(num);

    if (strlen(num) == 0) return -1;

    retNum = strtol(num, &numPtr, 10);

    if (retNum < 1 || retNum > 9999)
    {
        pef("Invalid number");
        return -1;
    }

    return retNum * itemSize;
}

int itemExists(int byte, FILE* ip)
{
    Item check;
    fseek(ip, byte, SEEK_SET);

    if (fread(&check, itemSize, 1, ip) != 1 || check.maxQuantity == 0)
    {
        return 0;
    }

    return 1;
}

void getString(const char* message, char variable[], int len)
{
    int i;
    char buffer[128];
    for (i = 0; i < len; i++) buffer[i] = '\0';
    pf("%s", message);
    fs(buffer);
    strcpy(variable, buffer);

}
