#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<windows.h>

//Struct section untuk linked list
//Struct data sampah
struct Trash{
    char trash_name[25];
    int value;
    int jumlah;
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
void count_create(FILE *file, int *counter, char file_name[30]);
int menu_user(ptr_user nama);
int menu_admin();
void login(char user_temp[32], char pass_temp[32]);
struct User *user_checker(char user_temp[32], char pass_temp[32], ptr_user database);
void registration(ptr_user *head, char user_temp[32], char pass_temp[32], int *counter);
void tambahSampah(FILE *dataSampah, int *counter_sampah);
void list_sampah(FILE *dataSampah, int counter_sampah);


//Main function section
int main(){
    int counter_user = 0, counter_trash = 0, select = 0, sentinelMenu = 0;
    char user_temp[32], pass_temp[32];
    //set for the linked list User
    ptr_user head = NULL;
    ptr_user temp = NULL;
    //set for the file
    FILE *file;
    count_create(file, &counter_user, "User.txt");
    count_create(file, &counter_trash, "List Sampah.txt");


    while (1)
    {
        login(user_temp, pass_temp);
        if(strcmp(user_temp,"admin")==0 && strcmp(pass_temp,"admin")==0){
            do{
                switch(menu_admin()){
                    case 0:
                        sentinelMenu = 99;
                        break;
                    case 1:
                        list_sampah(file,counter_trash);
                        system("pause");
                        continue;
                    case 2:
                        tambahSampah(file,&counter_trash);
                        system("pause");
                        continue;
                    default:
                        printf("\nPilihan tidak diketahui, mohon coba lagi\n\n");
                        system("pause");
                        continue;
                }
            }while(sentinelMenu != 99);
            
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
                do{
                    switch (menu_user(temp)){
                        case 0:
                            sentinelMenu = 99;
                            break;
                        case 1:
                            list_sampah(file,counter_trash);
                            system("pause");
                            continue;
                        default:
                            printf("\nPilihan tidak diketahui, mohon coba lagi\n\n");
                            system("pause");
                            continue;
                    }
                }while(sentinelMenu != 99);
            }
        }
    }
}

//Function section
void count_create(FILE *file, int *counter, char file_name[30]){
    char ch;
    file = fopen(file_name,"r");
    if(file == NULL){
        printf("making file\n");
        fclose(file);
        fopen(file_name,"w");
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

int menu_user(ptr_user nama){
    int pilihan;
    //system("CLS");
    printf("===========================================\n");
    printf("Selamat datang %s\n",nama->name);
    printf("===========================================\n");
    //Tinggal di sesuaikan menu dengan pilihan nanti
    printf("\n1. List Jenis Sampah");
    printf("\n2. Penyetoran Sampah");
    printf("\n3. Saldo Akun");
    printf("\n\n0. Keluar");
    printf("\n\nPilihan: ");
    scanf("%d", &pilihan);
    return pilihan;
}

int menu_admin(){
    int pilihan;
    //system("CLS");
    printf("===========================================\n");
    printf("Selamat datang di menu admin\n");
    printf("===========================================\n");
    //Tinggal di sesuaikan menu dengan pilihan nanti
    printf("\n1. List Jenis Sampah");
    printf("\n2. Tambah Jenis Sampah");
    printf("\n3. Ubah Nilai Sampah");
    printf("\n4. List Akun");
    printf("\n5. Hapus Akun");
    printf("\n\n0. Keluar");
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
            (*counter)++;
        }else{
            current = *head;
            while(current->next_user != NULL){
                current = current->next_user;            
            }
            current->next_user = new;
            (*counter)++;
        }
    }else{
        printf("\nmemory not allocated");
    }
}

void tambahSampah(FILE *dataSampah,int *counter_sampah){
    char namaSampah[32];
    char temp_nama_sampah[32];
    int hargaSampah, flag, temp_harga_sampah;
    int sentinel = 0;
    dataSampah = fopen("List Sampah.txt", "a+");
    printf("============================\n");
    printf("=    Input Jenis Sampah    =\n");
    printf("============================\n");
    do{
        flag = 0;
        printf("\nSilahkan Masukkan Nama Sampah : ");
        scanf(" %[^\n]", namaSampah);
        do{
            fscanf(dataSampah,"%s\t%d",temp_nama_sampah,&temp_harga_sampah);
            if(strcmpi(temp_nama_sampah, namaSampah) == 0){
                flag = 1;
            }        
        }while(!feof(dataSampah));
        if(flag == 1){
            printf("\nJenis sampah sudah ada, silahkan coba lagi\n\n");
            //system("pause");
        }
        //system("CLS");
    }while(flag == 1);
        
    printf("Silahkan Masukkan Harga Sampah : ");
    scanf("%d", &hargaSampah);
    fprintf(dataSampah, "%s\t%d\n", namaSampah,hargaSampah);
    (*counter_sampah)++;
    fclose(dataSampah);
}

void list_sampah(FILE *dataSampah, int counter_sampah){
    int i, temp_harga_sampah;
    char temp_nama_sampah[32];
    dataSampah = fopen("List Sampah.txt", "r");
    printf("=============================\n");
    printf("=     List Jenis Sampah     =\n");
    printf("=============================\n\n");
    for(i = 0; i < counter_sampah; i++){
        fscanf(dataSampah,"%s\t%d",temp_nama_sampah,&temp_harga_sampah);
        printf("%s\t%d\n", temp_nama_sampah, temp_harga_sampah);
    }
    fclose(dataSampah);
}