#include <stdio.h> 
#include <string.h> 
#include <stdlib.h>

int print_record(char * filename) {

    char buffer[800];
    int len = strlen(filename);

    if (len != 36)
        return -1;

    FILE * file;
    file = fopen(filename, "r");
    if (file == NULL) {
        return -1;
    }

    printf("\nXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX");
    printf("\nXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n\n");
    
    fread(buffer, 780, 1, file);
    printf("%s", buffer);
    printf("\n\nXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX");
    printf("\nXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX");
    fclose(file);
    return 0;
}

int main() {
    char password[16];
    printf("Enter password to authentic yourself : ");
    fflush(stdout);
    scanf("%s", password);
    if (strncmp(password, "kaiokenx20", 10) != 0) {
        printf("Incorrect password. Closing connection.\n");
        exit(0);
    }

    printf("Enter case number: \n");
    printf("\n\t 1) Application_1");
    printf("\n\t 2) Application_2");
    printf("\n\t 3) Application_3");
    printf("\n\t 4) Application_4");
    printf("\n\t 5) Application_5");
    printf("\n\t 6) Application_6");
    printf("\n\n\t Enter choice :- ");
    fflush(stdout);
    
    int choice;
    char name[40];
    scanf("%d", &choice);

    switch (choice) {
    case 1:
        strcpy(name, "2a5880700ae8e5f51ca9df9c5a44356d.dat");
        break;
    case 2:
        strcpy(name, "c85ade1c47bcbbe2ac64214919491b18.dat");
        break;
    case 3:
        strcpy(name, "829c1a326223afb33c34c16bba47472d.dat");
        break;
    case 4:
        strcpy(name, "a54df28db8b4d80f706611da99819460.dat");
        break;
    case 5:
        strcpy(name, "453be7bc0f23d90c0e33cd5b510382c0.dat");
        break;
    case 6:
        strcpy(name, "3133efc692a75d5bd56a6e7af726127c.dat");
        break;
    }

    int ret_code = print_record(name);

    if (ret_code == -1) {
        printf("\nNo such record exists. Please verify your choice.");
    }
    fflush(stdout);
    printf("\n\n");

}
