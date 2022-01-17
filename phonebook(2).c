#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

// Typedef for person datatype.
typedef struct per{
    char name[100];
    long int phone_no;
    char email[100];
    char address[100];
} person;

void insertRecord(){
    // Function to insert a new contact.
    system("cls");
    person temp;
    char name[100], email[100], address[100];
    long int phone_no;

    printf("Enter name: ");
    gets(temp.name);
    printf("Enter phone number: ");
    scanf("%ld", &temp.phone_no);
    fflush(stdin);
    printf("Enter email: ");
    gets(temp.email);
    printf("Enter address: ");
    gets(temp.address);

    FILE *f;
    f = fopen("record", "ab+");
    if(!f){
        printf("Failed to open file!");
        sleep(3);
        return;
    }
    fwrite(&temp, sizeof(person), 1, f);    // inserting the struct to the binary file
    fflush(stdin);
    printf("Record saved!\n");

    fclose(f);

    printf("Enter any key to continue...");

    _getch();
}
void deleteRecord(){
    // Function to delete a contact
    system("cls");
    person temp;
    FILE *f;
    f = fopen("record", "rb");
    if(!f){
        printf("Failed to open records!");
        sleep(3);
        return;
    }
    FILE *f2;
    f2 = fopen("temp", "wb+");
    if(!f2){
        printf("File error...");
        sleep(3);
        return;
    }
    char name[100];
    int flag = 0;

    printf("Enter the name of the contact to remove: ");
    scanf("%s", &name);

    fflush(stdin);
    while(fread(&temp, sizeof(person), 1, f) == 1){         // loop to search for contact
        if(strcmp(temp.name, name) != 0)
            fwrite(&temp, sizeof(person), 1, f2);
        if(strcmp(temp.name, name) == 0){
            flag = 1;
        }
    }
    fclose(f2);
    fclose(f);
    if(flag){
        if(remove("record") == -1)
            printf("%d\n", errno);
        if(rename("temp", "record") == -1)
            printf("%s\n", strerror(errno));
        printf("Record deleted successfully.\n");
    }
    else{
        remove("temp");
        printf("Record not found.\n");
    }
    printf("Enter any key to continue...");
    _getch();
}
void modifyRecord(){
    // Function to modify a record.
    FILE *f;
    f = fopen("record", "rb+");
    if(!f){
        printf("Failed to open records.");
        sleep(3);
        return;
    }
    person temp1, temp2;
    char name[100];
    int flag = 0;
    system("cls");

    printf("Enter the name of the contact to modify: ");
    scanf("%s", &name);
    while (fread(&temp1, sizeof(person), 1, f) == 1){       // loop to find and enter new details for the contact.
        if(strcmp(temp1.name, name) == 0){
            printf("Enter name: ");
            gets(temp2.name);
            printf("Enter phone number: ");
            scanf("%ld", &temp2.phone_no);
            printf("Enter email: ");
            gets(temp2.email);
            printf("Enter address: ");
            gets(temp2.address);
            fseek(f, -sizeof(person), SEEK_CUR);
            fwrite(&temp2, sizeof(person), 1, f);
            flag = 1;
            break;
        }
        fflush(stdin);
    }
    if(flag)
        printf("Data modified successfully.\n");
    else
        printf("Data not found.\n");
    fclose(f);

    printf("Enter any key to continue...");
    _getch();
}
void findRecord(){
    // Function to find and display a record.
    person temp;
    char name[100];
    FILE *f = fopen("record", "rb");
    if(!f){
        printf("Failed to open records.");
        sleep(3);
        return;
    }
    printf("Enter the name of the contact to search: ");
    scanf("%s", &name);

    while(fread(&temp, sizeof(person), 1, f) == 1){
        if(strcmp(temp.name, name) == 0){
            printf("Information of %s:\n", name);
            printf("Name: %s\n", name);
            printf("Phone number: %ld\n", temp.phone_no);
            printf("Email: %s\n", temp.email);
            printf("Address: %s\n", temp.address);
        }
        else
            printf("Record not found.\n");
    }
    printf("Enter any key to continue...");
    fclose(f);
    _getch();
}
int main(){
    system("color 0a");
    while(1){
        system("cls");

        fflush(stdin);
        char x;
        printf("Enter [1] to insert new contact, [2] to modify contact, [3] to delete contact, [4] to find record, [5] to exit.");
        x = _getch();
        system("cls");

        switch (x)
        {
        case '1':
            insertRecord();
            break;
        case '2':
            modifyRecord();
            break;
        case '3':
            deleteRecord();
            break;
        case '4':
            findRecord();
            break;
        case '5':
            printf("Adios...");
            return 0;
        default:
            printf("Invalid choice.");
            break;
        }
    }
}