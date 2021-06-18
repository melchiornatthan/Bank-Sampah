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
void hapusAkun(ptr_user database);
void listAkun(ptr_user database);
int hapusSampah(int *counter_sampah);
void store_sampah(ptr_user logged_in, FILE *dataSampah, int counter_sampah);
struct Trash *trash_checker(char sampah_temp[32], ptr_trash database);
int add_trash(ptr_trash *add,FILE *dataSampah, char sampah[32]);

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

    //Switch case baik untuk user maupun admin 
    while (1)
    {
        login(user_temp, pass_temp);
        if(strcmp(user_temp,"admin")==0 && strcmp(pass_temp,"admin")==0){
            do{
            	system("CLS");
                //Switch menu admin
                switch(menu_admin()){
                    case 99:
                        sentinelMenu = 99;
                        break;
                    case 1:
                    	system("CLS");
                        list_sampah(file,counter_trash);
                        system("pause");
                        continue;
                    case 2:
                    	system("CLS");
                        tambahSampah(file,&counter_trash);
                        system("pause");
                        continue;
                    case 4:
                    	system("CLS");
                        listAkun(head);
                        system("pause");
                        continue;
                    case 5:
                    	system("CLS");
                        hapusAkun(head);
                        system("pause");
                        continue;
                    case 6:
                    	system("CLS");
                		list_sampah(file,counter_trash);
                    	hapusSampah(&counter_trash);
                    	system("pause");
                    	continue;
                    default:
                    	system("CLS");
                        printf("\n\nPilihan tidak diketahui, mohon coba lagi\n\n");
                        system("pause");
                        continue;
                }
            }while(sentinelMenu != 99);
            
        }else{
            temp = user_checker(user_temp, pass_temp ,head);
            if(temp == NULL){
                //Jika akun tidak terdaftar
                printf("\nRegister your account Y(1)/N(0) ?\n");
                scanf("%d", &select);
                if(select == 1){
                    registration(&head,user_temp,pass_temp,&counter_user);
                }else{
                    continue;
                }
            }else{
                do{
                	system("CLS");
                    //Switch menu user
                    switch (menu_user(temp)){
                        case 99:
                            sentinelMenu = 99;
                            break;
                        case 1:
                        	system("CLS");
                            list_sampah(file,counter_trash);
                            system("pause");
                            continue;
                        case 2:
                            system("CLS");
                            store_sampah(temp,file,counter_trash);
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

//Funtion untuk membuat file untuk file handling
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

//Function menu user beserta menunya
int menu_user(ptr_user nama){
    int pilihan;
    //system("CLS");
    printf("===========================================\n");
    printf("Selamat datang %s\n",nama->name);
    printf("===========================================\n");
    //Tinggal di sesuaikan menu dengan pilihan nanti
    printf("\n1. List Jenis Sampah");
    printf("\n2. List Sampah Akun");
    printf("\n3. Penyetoran Sampah");
    printf("\n4. Saldo Akun");
    printf("\n\n99. Keluar");
    printf("\n\nPilihan: ");
    scanf("%d", &pilihan);
    return pilihan;
}

//Function menu admin beserta menunya
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
    printf("\n6. Hapus Jenis Sampah");
    printf("\n\n99. Keluar");
    printf("\n\nPilihan: ");
    scanf("%d", &pilihan);
    return pilihan;
}

//Function untuk halaman login
void login(char user_temp[32], char pass_temp[32]){
    printf("===========================\n");
    printf("=      Halaman Login      =\n");
    printf("===========================\n");
    printf("\nUsername : ");
    scanf(" %[^\n]",user_temp);
    printf("\npassword : ");
    scanf(" %[^\n]",pass_temp);
}

//Function untuk mengecek user/akun
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

//Function untuk login dan registrasi
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

//Function untuk menambah jenis sampah
void tambahSampah(FILE *dataSampah,int *counter_sampah){
    char namaSampah[32];
    char temp_nama_sampah[32];
    int hargaSampah, flag, temp_harga_sampah;
    int sentinel = 0;
    dataSampah = fopen("List Sampah.txt", "a+");
    printf("============================\n");
    printf("=    Input Jenis Sampah    =\n");
    printf("============================\n");
    //Loop error handling agar jenis sampah tidak dobel
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
            system("pause");
        }
    }while(flag == 1);
        
    printf("Silahkan Masukkan Harga Sampah : ");
    scanf("%d", &hargaSampah);
    fprintf(dataSampah, "%s\t%d\n", namaSampah,hargaSampah);
    (*counter_sampah)++;
    fclose(dataSampah);
}

//Function untuk melihat list sampah
void list_sampah(FILE *dataSampah, int counter_sampah){
    int i, temp_harga_sampah;
    char temp_nama_sampah[32];
    dataSampah = fopen("List Sampah.txt", "r");
    printf("=============================\n");
    printf("=     List Jenis Sampah     =\n");
    printf("=============================\n\n");
    for(i = 0; i < counter_sampah; i++){
        fscanf(dataSampah,"%s\t%d",temp_nama_sampah,&temp_harga_sampah);
        printf("%d. %s\t%d\n", i+1, temp_nama_sampah, temp_harga_sampah);
    }
    fclose(dataSampah);
}

//Function untuk melihat list akun
void listAkun(ptr_user database){
    ptr_user current = database;
    char user_temp[32];
    printf("=============================\n");
    printf("=          List Akun        =\n");
    printf("=============================\n\n");
    if(current == NULL){
        printf("\nThere is no account yet\n");
    }else{
        while(current != NULL){
            if(strcmp(current->username,user_temp) == 0){
                current = NULL;
                break;
            }
            printf("\nNama : %s\n", current->username);
            printf("Password : %s\n", current->password);
            current = current->next_user;
        }
    }
}

//Function untuk menghapus akun
void hapusAkun(ptr_user database){
    ptr_user current = database;
    char user_temp[32];
    ptr_user address_temp_after;
    ptr_user address_temp_before;
    
    listAkun(current);

    printf("Silahkan Input Nama User : ");
    scanf(" %[^\n]", user_temp);

    if(current == NULL){
        printf("\nThere is no account yet\n");
    }
    else{
        while(current != NULL){
            //mengarahkan linkedlist yang sebelumnya ke sesudah
            if(strcmp(current->username,user_temp) == 0){
                address_temp_after = current->next_user;
                address_temp_before->next_user = address_temp_after;
                break;
            }
            address_temp_before = current;
            current = current->next_user;
        }
    }
}

//Function untuk menghapus jenis sampah
int hapusSampah(int *counter_sampah){
    //Deklarasi variabel
    int i, temp_harga_sampah, baris, counter = 0;
    char temp_nama_sampah[32];
    FILE *file1, *file2;
    //Buka file list sampah asli
    file1 = fopen("List Sampah.txt", "r");
    if (!file1) {
        printf("\nFile tidak ditemukan\n\n");
        system("pause");
        return 0;
    }
    //Membuat file copy dari list sampah
    file2 = fopen("Temp Hapus.txt", "w"); 
    if (!file2) {
        printf("Gagal membuat file temporary\n\n");
        fclose(file1);
        return 0;
    }

    printf("\nMasukkan baris sampah yang ingin dihapus: ");
    scanf("%d", &baris);
    //Membuat copy dari file asli
    while (!feof(file1)){
        fscanf(file1, "%s\t%d", temp_nama_sampah, &temp_harga_sampah);
        if(!feof(file1)) {
            counter++;
            //Jika counter sama dengan baris maka akan meng-skip fprintf
            if (counter != baris){
        		fprintf(file2, "%s\t%d\n", temp_nama_sampah, temp_harga_sampah);
            }
        }
    }
    //Closing agar save dari buffer
    fclose(file1);
    fclose(file2);
    remove("List Sampah.txt");
    rename("Temp Hapus.txt", "List Sampah.txt");
    (*counter_sampah)--;
}

void store_sampah(ptr_user logged_in, FILE *dataSampah, int counter_sampah){
    ptr_trash temp;
    char temp_sampah[32];
    int temp_jumlah, flag_sampah;
    //printf("=============================\n");
    //printf("=        Setor Sampah       =\n");
    //printf("=============================\n\n");
    list_sampah(dataSampah,counter_sampah);
    printf("\nNama Sampah yang disetor: ");
    scanf(" %[^\n]", temp_sampah);
    temp = trash_checker(temp_sampah, logged_in->linked_account);
    if(temp == NULL){
        if(add_trash(&(logged_in->linked_account),dataSampah,temp_sampah) == 1){
            printf("\nSampah tidak di temukan\n");
            
        }else{
            printf("\nSampah terdata\n");
        }
    }else{
        printf("Sampah sudah ada\n");
        printf("Jumlah : ");
        scanf("%d",&temp_jumlah);
        temp->jumlah += temp_jumlah;
    }
}

struct Trash *trash_checker(char sampah_temp[32], ptr_trash database){
    int flag = 0;
    if(database == NULL){
        return NULL;
    }else{
        while(database != NULL){
            if(strcmpi(database->trash_name,sampah_temp) == 0){
                return database;
                break;  
            }
            database = database->next_trash;
        }
    }
}


int add_trash(ptr_trash *add,FILE *dataSampah, char sampah[32]){
    ptr_trash current;
    ptr_trash new;
    char nama_sampah[32];
    int harga_sampah,flag = 0;
    dataSampah = fopen("list Sampah.txt","r");
    while(!feof(dataSampah)){
        fscanf(dataSampah,"%s\t%d",nama_sampah,&harga_sampah);
        if(strcmpi(sampah,nama_sampah) == 0){
            flag = 0;
            break;
        }else{
            flag = 1;
        }
    }
    fclose(dataSampah);
    if(flag == 1){
        return 1;
    }else{
        new = malloc(sizeof(trash));
        strcpy(new->trash_name,nama_sampah);
        new->value = harga_sampah;
        new->next_trash = NULL;
        printf("\nJumlah : ");
        scanf("%d",&new->jumlah);
        if(*add == NULL){
            *add = new;
        }else{
            current = *add;
            while(current->next_trash != NULL){
                current = current->next_trash;
            }
            current->next_trash = new;
        }
        return 0;
    }
}