#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<windows.h>

//Struct section untuk linked list
//Struct data sampah
struct Trash{
    char trash_name[25];
    int value;
    struct Trash *next_trash;
};
typedef struct Trash trash;
typedef trash *ptr_trash;

//Struct data akun  
struct User{
    char name[32];
    char username[32];
    char password[32];
    ptr_trash linked_account;
    struct User *next_user;
};
typedef struct User user;
typedef user *ptr_user;

//Function prototype section
void count_create_user(FILE *file, int *counter);
int menu_user();
int menu_admin();

//Main function section
int main(){
    int counter_user = 0, counter_trash = 0;
    //set for the linked list User
    ptr_user head = NULL;
    ptr_user temp = NULL;
    //set for the file
    FILE *file;
    count_create_user(file, &counter_user);


}

//Function section
void count_create_user(FILE *file, int *counter){
    char ch;
    file = fopen("User.txt","r");
    if(file==NULL){
        printf("making file\n");
        fclose(file);
        fopen("User.txt","w");
        fclose(file);
    }else{
        while(!feof(file)){
            ch = fgetc(file);
            if(ch == '\n'){
                (*counter)++;
            }
        }
        fclose(file);
    }
}

int menu_user(){
    int pilihan;
    system("CLS");
    printf("===========================================\n");
    printf("Selamat datang <username>\n");
    printf("===========================================\n");
    //Tinggal di sesuaikan menu dengan pilihan nanti
    printf("\n1. Menu 1");
    printf("\n2. Menu 2");
    printf("\n3. Menu 3");
    printf("\n\nPilihan: ");
    scanf("%d", &pilihan);
    return pilihan;
}

int menu_admin(){
    int pilihan;
    system("CLS");
    printf("===========================================\n");
    printf("Selamat datang di menu admin\n");
    printf("===========================================\n");
    //Tinggal di sesuaikan menu dengan pilihan nanti
    printf("\n1. Menu 1");
    printf("\n2. Menu 2");
    printf("\n3. Menu 3");
    printf("\n\nPilihan: ");
    scanf("%d", &pilihan);
    return pilihan;
}