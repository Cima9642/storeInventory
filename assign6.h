#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#ifndef ASSIGN6_ASSIGN6_H
#define ASSIGN6_ASSIGN6_H

#define redirect(v) if(v == 1) freopen("a6Input.txt", "r", stdin)

#define inventory "inventory.dat"

#define itemSize sizeof(Item)

#define openInv ip = fopen(inventory, "r+b")

#define exists itemExists(byte, ip)

#define printMenu	pf("Enter one of the following actions or press CTRL-D to exit"); \
					pf("C - create a new item"); \
					pf("R - read an existing item"); \
					pf("U - update an existing item"); \
					pf("D - delete an existing item")

#define fs(s) fgets(s, sizeof(s),stdin); \
        s[strlen(s) - 1] = '\0'

#define byteCheck	int byte = byteOffset();\
					if(byte == -1) return

#define getItem(item)	fseek(ip,byte,SEEK_SET);\
						fread(&item,itemSize,1,ip)

#define uString(msg,var)	getString(msg,var,sizeof(var))	

typedef struct {
	char itemName[64];
	char simpleName[16];
	int currentQuantity;
	int maxQuantity;
	char body[128];
} Item;

void create(FILE* ip);
void read(FILE* ip);
void update(FILE* ip);
void delete(FILE* ip);

int byteOffset();
int itemExists(int byte, FILE* ip);
void getString(const char* message, char variable[], int len);
void pf(const char* format, ...);


#define getItem(item) fseek(ip,byte,SEEK_SET);\
        fread(&item,itemSize,1,ip)



#endif // ASSIGN6_ASSIGN6_H

