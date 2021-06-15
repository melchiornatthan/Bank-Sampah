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
void login(char user_temp[32], char pass_temp[32]);
struct User *user_checker(char user_temp[32], char pass_temp[32], ptr_user database);
void registration(ptr_user *head, char user_temp[32], char pass_temp[32], int *counter);


//Main function section
int main(){
    int counter_user = 0, counter_trash = 0, select = 0;
    char user_temp[32], pass_temp[32];
    //set for the linked list User
    ptr_user head = NULL;
    ptr_user temp = NULL;
    //set for the file
    FILE *file;
    count_create_user(file, &counter_user);

    while (1)
    {
        login(user_temp, pass_temp);
        if(strcmp(user_temp,"admin")==0 && strcmp(pass_temp,"admin")==0){
            switch(menu_admin()){
                case 1:
                    //command
                    break;
                default:
                    break;
            }
        }else{
            temp = user_checker(user_temp, pass_temp ,head);
            if(temp == NULL){
                printf("\nRegister your account Y(1)/N(0) ?\n");
                scanf("%d", &select);
                if(select == 1){
                    registration(&head,user_temp,pass_temp,&counter_user);
                }else{
                    continue;
                }
            }else{
                switch (menu_user()){
                case 1:
                    //command
                    break;
                
                default:
                    break;
                }
            }
        }
    }
    


}

//Function section
void count_create_user(FILE *file, int *counter){
    char ch;
    file = fopen("User.txt","r");
    if(file == NULL){
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
    printf("Selamat datang <nama>\n");
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

void login(char user_temp[32], char pass_temp[32]){
    printf("===========================\n");
    printf("=      Halaman Login      =\n");
    printf("===========================\n");
    printf("\nUsername : ");
    scanf(" %[^\n]",user_temp);
    printf("\npassword : ");
    scanf(" %[^\n]",pass_temp);
}

struct User *user_checker(char user_temp[32], char pass_temp[32], ptr_user database){
    ptr_user current = database;
    if(current == NULL){
        printf("\nThere is no account yet\n");
        return NULL;
    }else{
        while(current != NULL){
            if(strcmp(current->username,user_temp) == 0 && strcmp(current->password,pass_temp) == 0){
                return current;
                break;
            }
            current = current->next_user;
        }
    }
}

void registration(ptr_user *head, char user_temp[32], char pass_temp[32], int *counter){
    ptr_user new;
    ptr_user current;

    new = malloc(sizeof(user));
    if(new != NULL){
        printf("===========================\n");
        printf("=      Halaman Login      =\n");
        printf("===========================\n\n");
        printf("Username : %s\n", user_temp);
        strcpy(new->username,user_temp);
        printf("Password : %s\n", pass_temp);
        strcpy(new->password,pass_temp);
        printf("Name : ");
        scanf(" %[^\n]", new->name);
        new->next_user = NULL;
        new->linked_account = NULL;
        

        if(*head == NULL){
            *head = new;
            *counter++;
        }else{
            current = *head;
            while(current->next_user != NULL){
                current = current->next_user;            
            }
            current->next_user = new;
            *counter++;
        }
    }else{
        printf("\nmemory not allocated");
    }
}
