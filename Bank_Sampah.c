#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<windows.h>
#include<omp.h>

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
    int total;
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
void store_sampah(ptr_user logged_in, FILE *dataSampah);
struct Trash *trash_checker(char sampah_temp[32], ptr_trash database);
int add_trash(ptr_trash *add,FILE *dataSampah, char sampah[32]);
void list_sampah_akun(ptr_trash print, char nama[32]);
void store_akun_to_file(FILE *store, ptr_user data);
void load_akun_from_file(FILE *store, ptr_user *load);
void saldoAkun(ptr_trash data);

//Main function section
int main(){
    system("color c0");
    int counter_user = 0, counter_trash = 0, select = 0, sentinelMenu = 0;
    char user_temp[32], pass_temp[32];
    //set for the linked list User
    ptr_user head = NULL;
    ptr_user temp = NULL;
    //set for the file
    FILE *file;
    count_create(file, &counter_user, "User.txt");
    count_create(file, &counter_trash, "List Sampah.txt");
    //load data
    if(counter_user > 0)
    load_akun_from_file(file,&head);

    //Switch case baik untuk user maupun admin 
    while (1)
    {
        system("CLS");
        login(user_temp, pass_temp); //display login
        if(strcmp(user_temp,"admin")==0 && strcmp(pass_temp,"admin")==0){
            do{
                sentinelMenu = 0;
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
                        break;
                    case 2:
                        system("CLS");
                        tambahSampah(file,&counter_trash);
                        system("pause");
                        break;
                    case 3:
                        system("CLS");
                        listAkun(head);
                        system("pause");
                        break;
                    case 4:
                        system("CLS");
                        hapusAkun(head);
                        system("pause");
                        break;
                    case 5:
                        system("CLS");
                        list_sampah(file,counter_trash);
                        hapusSampah(&counter_trash);
                        system("pause");
                        break;
                    default:
                        system("CLS");
                        printf("\n\nPilihan tidak diketahui, mohon coba lagi\n\n");
                        system("pause");
                        break;
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
                    sentinelMenu = 0;
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
                            break;

                        case 2:
                            system("CLS");
                            list_sampah_akun(temp->linked_account, temp->name);
                            system("pause");
                            break;

                        case 3:
                            system("CLS");
                            list_sampah(file,counter_trash);
                            store_sampah(temp,file);
                            system("pause");
                            break;
                        case 4:
                            system("CLS");
                            list_sampah_akun(temp->linked_account, temp->name);
                            saldoAkun(temp->linked_account);
                            system("pause");
                            break;
                        
                        default:
                            system("CLS");
                            printf("\nPilihan tidak diketahui, mohon coba lagi\n\n");
                            system("pause");
                            break;
                    }
                }while(sentinelMenu != 99);
            }
        }
        sentinelMenu = 0;
        printf("\nexit(1)? ");
        scanf("%d", &sentinelMenu);
        if(sentinelMenu == 1){
            store_akun_to_file(file,head);
            exit(0);
        }
        system("CLS");
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
    fflush(stdin);
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
    printf("\n3. List Akun");
    printf("\n4. Hapus Akun");
    printf("\n5. Hapus Jenis Sampah");
    printf("\n\n99. Keluar");
    fflush(stdin);
    printf("\n\nPilihan: ");
    scanf("%d", &pilihan);
    return pilihan;
}

//Function untuk halaman login
void login(char user_temp[32], char pass_temp[32]){
    printf("============================\n");
    printf("=        Bank Sampah       =\n");
    printf("============================\n");
    printf("\nUsername : ");
    scanf(" %[^\n]",user_temp); //meminta username dari pengguna
    printf("\npassword : ");
    scanf(" %[^\n]",pass_temp);//meminta password dari pengguna
}

//Function untuk mengecek user/akun
struct User *user_checker(char user_temp[32], char pass_temp[32], ptr_user database){
    ptr_user current = database;
    if(current == NULL){ //mengecek apakah linked list memiliki isi atau tidak
        printf("\nThere is no account yet\n");
        return NULL;
    }else{
        while(current != NULL){ //mengecek apakah data yang diinput memiliki kesamaan pada data sebelumnya
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
        printf("=~=~=~=~=~=~=~=~=~=~=~=~=~=\n");
        printf("=      Halaman Login      =\n");
        printf("=~=~=~=~=~=~=~=~=~=~=~=~=~=\n\n");
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
        flag = 0; //meminta nama sampah dari user untuk ditambahkan
        printf("\nSilahkan Masukkan Nama Sampah : ");
        scanf(" %[^\n]", namaSampah);
        do{ //mengecek apakah sampah yang diinput sudah ada
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
    //meminta harga untuk jenis sampah baru    
    printf("Silahkan Masukkan Harga Sampah : ");
    scanf("%d", &hargaSampah);
    fprintf(dataSampah, "%s\t%d\n", namaSampah,hargaSampah);//mememasukkan sampah baru ke file data
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
    #pragma omp parallel
    {
	    #pragma omp for ordered private(temp_nama_sampah, temp_harga_sampah)
		for(i = 0; i < counter_sampah; i++){
	        #pragma omp ordered
			{   //mengambil list sampah dari file untuk ditampilkan
				#pragma omp critical
				fscanf(dataSampah," %[^\t]\t%d",temp_nama_sampah,&temp_harga_sampah);
			    printf("%d. %10s\t%15d\t\n", i+1, temp_nama_sampah, temp_harga_sampah);
			}
	    }
	    #pragma omp barrier
	    fclose(dataSampah);
	}
}
//Function untuk melihat list akun
void listAkun(ptr_user database){
    ptr_user head = database;
    ptr_user current;
    char user_temp[32];
    printf("=============================\n");
    printf("=          List Akun        =\n");
    printf("=============================\n\n");
    printf("%3sUsername%10sNama\n\n"," "," ");
    if(head == NULL){
        printf("\nThere is no account yet\n");
    }else{
        #pragma omp parallel
        {
            current = head;
            #pragma omp master
            {
                while (current){
                #pragma omp task firstprivate (current)
                {   //mengambil list akun dari file untuk di print
                	#pragma omp critical
                    printf("%10s%15s\n",current->username,current->name);
                }
                current = current->next_user;
                }
            }
        }
    }
}

//Function untuk menghapus akun
void hapusAkun(ptr_user database){
    int flag = 0;
    ptr_user current = database;
    char user_temp[32];
    ptr_user address_temp_after;
    ptr_user address_temp_before;
    
    listAkun(current);
    //meminta pengguna data yang ingin dihapus
    printf("Silahkan Input Nama User : ");
    scanf(" %[^\n]", user_temp);

    if(current == NULL){
        printf("\nThere is no account yet\n");
    }
    else{
        while(current != NULL){
            //mengarahkan linkedlist yang sebelumnya ke sesudah untuk melompati data yang ingin dihapus
            if(strcmp(current->username,user_temp) == 0){
                address_temp_after = current->next_user;
                address_temp_before->next_user = address_temp_after;
                flag = 1;
                break;
            }
            address_temp_before = current;
            current = current->next_user;
        }
        if(flag == 0)
        printf("there is no account (%s)", user_temp);
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
    do{
        fflush(stdin);
        printf("\nMasukkan baris sampah yang ingin dihapus: ");
    }while(scanf("%d", &baris) != 1);
    
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

void store_sampah(ptr_user logged_in, FILE *dataSampah){//menyetor sampah yang diinginkan pengguna
    ptr_trash temp;
    char temp_sampah[32];
    int temp_jumlah, flag_sampah;
    printf("=============================\n");
    printf("=        Setor Sampah       =\n");
    printf("=============================\n\n");
    printf("\nNama Sampah yang disetor: ");
    scanf(" %[^\n]", temp_sampah);
    temp = trash_checker(temp_sampah, logged_in->linked_account);
    if(temp == NULL){ //mengecek apakah sampah yang disetor terdaftar pada jenis sampah
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
    }else{ //mengecek apakah jenis sampah sudah ada pada database
        while(database != NULL){
            if(strcmpi(database->trash_name,sampah_temp) == 0){
                return database;
                break;  
            }
            database = database->next_trash;
        }
    }
}

//menambahkan jenis sampah pada file data sampah
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
//menunjukkan sampah yang telah di setor oleh pengguna
void list_sampah_akun(ptr_trash print, char nama[32]){
    ptr_trash current;
    printf("=============================\n");
    printf("=        Sampah %s \n",nama);
    printf("=============================\n\n");
    printf("%6sNama%10sJumlah\n\n"," "," ");
    if(print == NULL){
        printf("\nThere is no trash yet\n");
    }else{
        #pragma omp parallel
        {
            current = print;
            #pragma omp master
            {
                while (current){
                #pragma omp task firstprivate(current)
                {
                    #pragma omp critical
                    printf("%10s%15d\n", current->trash_name, current->jumlah);
                }
                current = current->next_trash;
                }
            }
        }
    }
}
//menyimpan data akun pada file agar tidak hilang saat dijalankan selanjutnya
void store_akun_to_file(FILE *store, ptr_user data){
    FILE *sampah;
    store = fopen("User.txt", "w");
    char filename[32];

    while(data!=NULL){
        fprintf(store,"%s\t%s\t%s\n",data->username,data->password,data->name);
        if(data->linked_account!=NULL){
            snprintf(filename,sizeof(filename),"%s.txt",data->username);
            sampah = fopen(filename,"w");
            while(data->linked_account!=NULL){
                fprintf(sampah,"%s\t%d\t%d\n",data->linked_account->trash_name,data->linked_account->jumlah,data->linked_account->value);
                data->linked_account = data->linked_account->next_trash;
            }
            fclose(sampah);
        }
        data = data->next_user;
    }
    fclose(store);
}
//mengambil data saat memulai program
void load_akun_from_file(FILE *store, ptr_user *load){
    ptr_user new;
    ptr_user temp_user;
    ptr_trash new_trash;
    ptr_trash temp;
    char filename[32];
    FILE *sampah;

    store = fopen("User.txt","r");
    while(!feof(store)){
        new = malloc(sizeof(user));
        fscanf(store," %[^\t]\t %[^\t]\t %[^\n]\n",new->username,new->password,new->name);
        new->next_user = NULL;
        new->linked_account = NULL;
        snprintf(filename,sizeof(filename),"%s.txt",new->username);
        sampah = fopen(filename,"r");
        if(sampah != NULL){
            while(!feof(sampah)){
                temp = new->linked_account;
                new_trash = malloc(sizeof(trash));
                fscanf(sampah," %[^\t]\t%d\t%d\n",new_trash->trash_name,&new_trash->jumlah,&new_trash->value);
                new_trash->next_trash = NULL;
                if(temp == NULL){
                    new->linked_account = new_trash;
                }else{
                    while(temp->next_trash!=NULL){
                        temp = temp->next_trash;
                    }
                    temp->next_trash = new_trash;
                }
            }
            fclose(sampah);
        }
        if(*load == NULL){
            *load = new;
        }else{
            temp_user = *load;
            while(temp_user->next_user != NULL){
                temp_user = temp_user->next_user;
            }
            temp_user->next_user = new;
        }
    }
    fclose(store);
}
//menunjukkan saldo akun yang tersisa pada akun pengguna
void saldoAkun(ptr_trash data){
    int i,sum = 0;
    printf("=============================\n");
    printf("=      Total Saldo Akun     =\n");
    printf("=============================\n");
    ptr_trash current;
    current = data;

    #pragma omp parallel
    {
        current = data;
        #pragma omp master
        {
            while (current){
            #pragma omp task firstprivate(current)
            {
                #pragma omp critical
                sum += (current->jumlah)*(current->value);
            }
            current = current->next_trash;
            }
        }
    }
    printf("Total: Rp. %d\n\n", sum);
}