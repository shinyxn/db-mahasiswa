#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct simpulMhs Mahasiswa;
typedef struct simpulMK MataKuliah;
typedef struct obj_mhs data_mhs;
typedef struct obj_matkul data_matkul;

struct obj_mhs{
    int NRP;
    char Nama[30];
    char Prodi[15];
};

struct simpulMhs {
    data_mhs data;
    Mahasiswa *nextMhs;
    Mahasiswa *prevMhs;
    MataKuliah *matkul;
};

struct obj_matkul{
    char KodeMK[6];
    char NamaMK[15];
    int nilai;
};

struct simpulMK {
    data_matkul data;
    MataKuliah *nextMK;
};

Mahasiswa *head=NULL;
Mahasiswa *tail=NULL;
Mahasiswa *baru=NULL;
MataKuliah *mbaru=NULL;

void tekan_enter_untuk_melanjutkan(){
    fflush(stdin);
    printf("\nTekan ( enter ) untuk melanjutkan\n");
    getchar();
}

void allocate_node_mhs(data_mhs m){
    baru = (Mahasiswa*)malloc(sizeof(Mahasiswa));
    baru->data = m;
    baru->matkul=NULL;
    baru->nextMhs=NULL;
    baru->prevMhs=NULL;
}

void allocate_node_matkul(data_matkul matkul){
    mbaru = (MataKuliah*)malloc(sizeof(MataKuliah));
    mbaru->data=matkul;
    mbaru->nextMK=NULL;
}

void sisip_depan_mahasiswa(data_mhs m){
    allocate_node_mhs(m);
    if (head==NULL){
        head=baru;
        tail=baru;
    }
    else if (head->data.NRP>m.NRP){
        baru->nextMhs=head;
        head->prevMhs=baru;
        head=head->prevMhs;
    }
    else{
        printf("DATA SUDAH ADA !!!\n");
        fflush(stdin);
        getchar();
    }
}

void sisip_belakang_mahasiswa(data_mhs m){
    allocate_node_mhs(m);
    if (tail->data.NRP<m.NRP){
        tail->nextMhs=baru;
        baru->prevMhs=tail;
        tail=tail->nextMhs;
    }
    else{
        printf("DATA SUDAH ADA !!!\n");
        fflush(stdin);
        getchar();
    }
}

void sisip_urut_data_mahasiswa(data_mhs m){
    if (head==NULL || head->data.NRP>=m.NRP){
        sisip_depan_mahasiswa(m);
        printf("DATA SUDAH MASUK!!!\n");
        tekan_enter_untuk_melanjutkan();
    }
    else if (tail->data.NRP<=m.NRP){
        sisip_belakang_mahasiswa(m);
        printf("DATA SUDAH MASUK!!!\n");
        tekan_enter_untuk_melanjutkan();
    }
    else{
        Mahasiswa *p = head;
        while (p->nextMhs!=NULL &&   p->nextMhs->data.NRP<m.NRP){
            p=p->nextMhs;
        }
        if (p->nextMhs==NULL || p->nextMhs->data.NRP == m.NRP){
            printf("DATA SUDAH ADA !!!\n");
            tekan_enter_untuk_melanjutkan();
        }
        else{
            allocate_node_mhs(m);
            baru->nextMhs=p->nextMhs;
            baru->prevMhs=p;
            p->nextMhs->prevMhs=baru;
            p->nextMhs=baru;
            printf("DATA SUDAH MASUK!!!\n");
            tekan_enter_untuk_melanjutkan();
        }
    }
}

void cetak_data_semua_mahasiswa(){
    printf("\n---------------------------------------------------------------------------------------------\n");
    printf("| NRP\t\t| Nama Mahasiswa\t| Prodi\t| Kode Matkul\t| Nama Matkul\t| Nilai\t|\n");
    printf("---------------------------------------------------------------------------------------------\n");
    Mahasiswa *p=head;
    while (p!=NULL){
        printf("| %d\t\t| %s\t\t| %s\t|",p->data.NRP,p->data.Nama,p->data.Prodi);
        MataKuliah *ctk_matkul = p->matkul;
        if (ctk_matkul==NULL)
            printf("             \t|            \t|      \t|\n");
        else{
            while (ctk_matkul!=NULL){
                printf(" %s\t| %s\t| %d\t|\n",ctk_matkul->data.KodeMK,ctk_matkul->data.NamaMK,ctk_matkul->data.nilai);
                ctk_matkul=ctk_matkul->nextMK;
                if (ctk_matkul!=NULL)
                    printf("|    \t\t|              \t|      \t|");
            }
        }
        p=p->nextMhs;
    }
    printf("---------------------------------------------------------------------------------------------\n");
    puts("");
}

void sisip_data_mahasiswa_baru(){
    data_mhs mhs;
    system("cls");
    printf("\t\t INPUT DATA MAHASISWA BARU\n\n");
    printf("Masukkan NRP Mahasiswa : ");
    fflush(stdin);
    scanf("%d",&mhs.NRP);
    printf("Masukkan Nama Mahasiswa : ");
    fflush(stdin);
    scanf("%s",mhs.Nama);
    printf("Masukkan Prodi Mahasiswa : ");
    fflush(stdin);
    scanf("%s",mhs.Prodi);
    sisip_urut_data_mahasiswa(mhs);
}

void hapus_depan(){
    Mahasiswa *freeman = head;
    if (head->nextMhs==NULL){
        head->nextMhs=NULL;
        head->prevMhs=NULL;
        tail=NULL;
        head=NULL;
        free(freeman);
    }
    else{
        head=head->nextMhs;
        head->prevMhs=NULL;
        freeman->nextMhs=NULL;
        free(freeman);
    }
}

void hapus_belakang(){
    Mahasiswa *freeman = tail;
    tail=tail->prevMhs;
    tail->nextMhs=NULL;
    freeman->prevMhs=NULL;
    free(freeman);
}

void hapus_data_mahasiswa(){
    system("cls");
    int nrp;
    Mahasiswa *p=head;
    printf("\t\t\tHAPUS DATA MAHASISWA\n\n");
    printf("Silahkan Masukkan NRP yang ingin dihapus : ");
    scanf("%d",&nrp);
    while (p->nextMhs!=NULL && p->data.NRP!=nrp){
        p=p->nextMhs;
    }
    if ( p->nextMhs==NULL && p->data.NRP!=nrp){
        printf("NRP TIDAK DITEMUKAN !!!");
        tekan_enter_untuk_melanjutkan();
    }
    else{
        printf("DATA\n");
        printf("NRP\t: ");
        printf("%d\n",p->data.NRP);
        printf("NAMA\t: ");
        printf("%s\n",p->data.Nama);
        printf("PRODI\t: ");
        printf("%s\n",p->data.Prodi);
        printf("TELAH DIHAPUS\n");
        if (p->matkul != NULL){
            printf("Maaf Hapus Mata Kuliah Terlebih Dahulu !!!\n");
            tekan_enter_untuk_melanjutkan();
        }
        else if (head->nextMhs==NULL || p==head){
            hapus_depan();
        }
        else if (tail->data.NRP == p->data.NRP ){
            hapus_belakang();
        }
        else{
            Mahasiswa *freeman = p;
            p->nextMhs->prevMhs = p->prevMhs;
            p->prevMhs->nextMhs = p->nextMhs;
            free(freeman);
        }
        tekan_enter_untuk_melanjutkan();
    }
}

void update_data_mahasiswa(){
    system("cls");
    int nrp;
    char nama[30];
    char prodi[30];
    Mahasiswa *p=head;
    printf("\t\t\tHAPUS DATA MAHASISWA\n\n");
    printf("Silahkan Masukkan NRP yang ingin dihapus : ");
    scanf("%d",&nrp);
    while (p->nextMhs!=NULL && p->data.NRP!=nrp){
        p=p->nextMhs;
    }
    if ( p->nextMhs==NULL && p->data.NRP!=nrp){
        printf("NRP TIDAK DITEMUKAN !!!");
        tekan_enter_untuk_melanjutkan();
    }
    else{
        printf("DATA\n");
        printf("NRP\t: ");
        fflush(stdin);
        printf("%d\n",p->data.NRP);
        printf("NAMA\t: ");
        fflush(stdin);
        printf("%s\n",p->data.Nama);
        printf("PRODI\t: ");
        fflush(stdin);
        printf("%s\n",p->data.Prodi);
        puts("");
        printf("Data Nama Baru : ");
        fflush(stdin);
        scanf("%s",nama);
        printf("Data Prodi Baru : ");
        fflush(stdin);
        scanf("%s",prodi);
        strcpy(p->data.Nama,nama);
        strcpy(p->data.Prodi,prodi);
        puts("Data Telah Di Update\n");
        tekan_enter_untuk_melanjutkan();
    }
}

void sisip_matkul(Mahasiswa *mhs, data_matkul matkul){
    allocate_node_matkul(matkul);
    MataKuliah *rear = mhs->matkul;
    if (rear == NULL){
        mhs->matkul = mbaru;
        mhs->matkul->nextMK=NULL;
    }
    else{
        while (rear->nextMK!=NULL){
            rear=rear->nextMK;
        }
        rear->nextMK=mbaru;
    }
}

void sisip_matkul_mahasiswa(){
    system("cls");
    int nrp;
    Mahasiswa *p=head;
    data_matkul dmatkul;
    printf("\t\t\t\tSISIP MATKUL MAHASISWA\n\n");
    printf("Silahkan Masukkan NRP yang ingin Disisipkan Matakuliah : ");
    scanf("%d",&nrp);
    while (p->nextMhs!=NULL && p->data.NRP!=nrp){
        p=p->nextMhs;
    }
    if ( p->nextMhs==NULL && p->data.NRP!=nrp){
        printf("NRP TIDAK DITEMUKAN !!!");
        tekan_enter_untuk_melanjutkan();
    }
    else{
        printf("DATA Mahasiwa Yang akan Disisipkan\n\n");
        printf("NRP\t: ");
        printf("%d\n",p->data.NRP);
        printf("NAMA\t: ");
        printf("%s\n",p->data.Nama);
        printf("PRODI\t: ");
        printf("%s\n",p->data.Prodi);
        puts("");
        printf("Masukkan Kode MataKuliah : ");
        scanf("%s",dmatkul.KodeMK);
        printf("Masukkan Nama MataKuliah : ");
        scanf("%s",dmatkul.NamaMK);
        printf("Masukkan Nilai Mata Kuliah : ");
        scanf("%d",&dmatkul.nilai);
        sisip_matkul(p,dmatkul);
        puts("Data Telah Di Update\n");
        tekan_enter_untuk_melanjutkan();
    }
}

void hapus_matkul_mahasiswa(){
    system("cls");
    int nrp;
    Mahasiswa *p=head;
    char kodeMK[30];
    data_matkul dmatkul;
    printf("\t\t\tHAPUS MATKUL MAHASISWA\n\n");
    printf("Silahkan Masukkan NRP yang ingin DiHapuskan Mata Kuliahnya Matakuliah : ");
    scanf("%d",&nrp);
    while (p->nextMhs!=NULL && p->data.NRP!=nrp){
        p=p->nextMhs;
    }
    if ( p->nextMhs==NULL && p->data.NRP!=nrp){
        printf("NRP TIDAK DITEMUKAN !!!");
        tekan_enter_untuk_melanjutkan();
    }
    else{
        printf("DATA Mahasiwa\n\n");
        printf("NRP\t: ");
        printf("%d\n",p->data.NRP);
        printf("NAMA\t: ");
        printf("%s\n",p->data.Nama);
        printf("PRODI\t: ");
        printf("%s\n",p->data.Prodi);
        puts("");
        MataKuliah *mtkl = p->matkul;
        if (mtkl==NULL){
            printf("Data masih belum memiliki Mata Kuliah\n");
            tekan_enter_untuk_melanjutkan();
        }
        else{
            printf("Masukkan Kode MataKuliah : ");
            scanf("%s",kodeMK);
            MataKuliah *before=mtkl;
            while (mtkl->nextMK!=NULL && mtkl->data.KodeMK!=kodeMK){
                before=mtkl;
                mtkl=mtkl->nextMK;
            }
            if ( mtkl->nextMK==NULL && strcmp(mtkl->data.KodeMK,kodeMK)){
                printf("MATA KULIAH TIDAK DITEMUKAN !!!");
                tekan_enter_untuk_melanjutkan();
            }
            else{
                printf("Kode Mata Kuliah\t: ");
                printf("%s\n",mtkl->data.KodeMK);
                printf("Nama Mata Kuliah\t: ");
                printf("%s\n",mtkl->data.NamaMK);
                printf("Nilai Mata Kuliah\t: ");
                printf("%d\n",mtkl->data.nilai);
                printf("\n\n");
                if (before==mtkl){
                    p->matkul=NULL;
                    free(mtkl);
                }
                else{
                    before->nextMK=mtkl->nextMK;
                    free(mtkl);
                }
                printf("Data Telah Terhapus\n\n");
                tekan_enter_untuk_melanjutkan();
            }
        }
    }
}

void tampil_final_data_mahasiswa(){
    system("cls");
    printf("\t\t......MELIHAT SELURUH DATA MAHASISWA.....");
    cetak_data_semua_mahasiswa();
    float rata_rata=0,rata_rata_total=0,jumlah_matkul=0,jumlah_matkul_total=0;
    printf("\t\tNilai RATA-RATA\n");
    printf("");
    printf("=================================================\n");
    printf("| NRP\t| NAMA\t| RATA - RATA\t| JUMLAH MATKUL\t|\n");
    printf("=================================================\n");
    Mahasiswa *p=head;
    while (p!=NULL){
        rata_rata = 0;
        jumlah_matkul = 0;
        MataKuliah *ctk_matkul = p->matkul;
        while (ctk_matkul!=NULL){
            rata_rata += ctk_matkul->data.nilai;
            jumlah_matkul++;
            rata_rata_total+=ctk_matkul->data.nilai;
            jumlah_matkul_total++;
            ctk_matkul=ctk_matkul->nextMK;
        }
        printf("| %d\t| %s\t| %.2f\t| %g\t|\n",p->data.NRP,p->data.Nama,rata_rata/jumlah_matkul,jumlah_matkul);
        p=p->nextMhs;
    }
    printf("=================================================\n\n");
    printf("RATA-RATA SELURUH MAHASISWA = %.2f\n",rata_rata_total/jumlah_matkul_total);
    printf("JUMLAH MATKUL TOTAL = %g\n",jumlah_matkul_total);
    tekan_enter_untuk_melanjutkan();
}

int main()
{
    int opsi=1;
    while (opsi!=7){
        system("cls");
        printf("\t\t\t\t<<<<<DATABASE MAHASISWA>>>>>\n");
        cetak_data_semua_mahasiswa();
        puts("");
        printf("1. Masukkan Data Mahasiswa Baru\n");
        printf("2. Hapus Data Mahasiswa\n");
        printf("3. Update Data Mahasiswa\n");
        printf("4. Sisip Mata Kuliah Mahasiswa\n");
        printf("5. Hapus Matkul Mahasiswa\n");
        printf("6. Tampilkan Seluruh Data dan Nilai Rata - Rata Mahasiswa\n");
        printf("Pilihan anda : ");
        scanf("%d",&opsi);
        switch(opsi){
        case 1:
            sisip_data_mahasiswa_baru();
            break;
        case 2:
            hapus_data_mahasiswa();
            break;
        case 3:
            update_data_mahasiswa();
            break;
        case 4:
            sisip_matkul_mahasiswa();
            break;
        case 5:
            hapus_matkul_mahasiswa();
            break;
        case 6:
            tampil_final_data_mahasiswa();
        case 7:
            break;
        default:
            printf("Maaf Input Anda Salah\n");
            tekan_enter_untuk_melanjutkan();
            break;
        }
    }
}


