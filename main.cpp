#include <iostream>
#include "listChild.h"
#include "listParent.h"
#include "listRelasi.h"

using namespace std;

int main()
{
    int pilih;
    List_parent L1;
    createListParent(L1);
    List_child L2;
    createListChild(L2);
    List_Relasi L3;
    createListRelasi(L3);
    do
    {
        cout<<"======================MENU====================="<<endl
            <<"1.  Masukkan Data Mahasiswa"<<endl
            <<"2.  Masukkan Data Buku"<<endl
            <<"3.  Tampilkan List Mahasiswa"<<endl
            <<"4.  Tampilkan List Buku"<<endl
            <<"5.  Peminjaman"<<endl
            <<"6.  Pengembalian"<<endl
            <<"7.  Tampilkan Semua Peminjaman"<<endl
            <<"8.  Cari Data Peminjam dengan ID mahasiswa/buku"<<endl
            <<"9.  Hapus Data Mahasiswa"<<endl
            <<"10. Hapus Data Buku"<<endl
            <<"11. Total buku"<<endl
            <<"12. Total Mahasiswa"<<endl
            <<"13. Total Peminjaman"<<endl
            <<"0. exit"<<endl;
        cout<<"choose menu : ";
        cin>>pilih;
        switch(pilih)
        {
        case 1:
        {
            int id, year;
            string jurusan;
            cout<<"NIM : ";
            cin>>id;
            address_parent Q = findElmParent(L1, id);
            while(Q != NULL)
            {
                cout<<"NIM telah digunakan"<<endl;
                cout<<"NIM : ";
                cin>>id;
                Q = findElmParent(L1, id);
            }
            cout<<"Jurusan : ";
            cin>>jurusan;
            cout<<"Angkatan : ";
            cin>>year;
            address_parent P = createElmParent(id, jurusan, year);
            insertSortParent(L1, P);
            break;
        }
        case 2:
        {
            int idBuku, tahunBuku;
            string judul;
            cout<<"ID Buku : ";
            cin>>idBuku;
            address_child Q = findElmChild(L2, idBuku);
            while(Q != NULL)
            {
                cout<<"ID telah digunakan"<<endl;
                cout<<"ID Buku : ";
                cin>>idBuku;
                Q = findElmChild(L2, idBuku);
            }
            cout<<"Judul Buku : ";
            cin>>judul;
            cout<<"Tahun Terbit : ";
            cin>>tahunBuku;
            address_child P = createElmChild(idBuku, judul, tahunBuku);
            insertSortChild(L2, P);
            break;
        }
        case 3 :
        {
            printInfoParent(L1);
            break;
        }
        case 4 :
        {
            printInfoChild(L2);
            break;
        }
        case 5 :
        {
            int ID, idBuku;
            cout<<"Masukkan NIM :";
            cin>>ID;
            cout<<"Masukkan ID Buku : ";
            cin>>idBuku;
            address_parent Q = findElmParent(L1, ID);
            address_child R = findElmChild(L2, idBuku);
            while(Q == NULL || R == NULL){
                if(Q == NULL){
                    cout<<"NIM tidak ditemukan"<<endl;
                    cout<<"Masukkan NIM :";
                    cin>>ID;
                    Q = findElmParent(L1, ID);
                }else if(R == NULL){
                    cout<<"ID Buku tidak ditemukan"<<endl;
                    cout<<"Masukkan ID Buku : ";
                    cin>>idBuku;
                    R = findElmChild(L2, idBuku);
                }
            }
            address_relasi P = createElmRelasi(Q, R);
            insertRelasi(L3, P);
            break;
        }
        case 6 :
        {
            //coba kamu cari buat peminjamannya lebih dari satu terus kamu hapus
            //kamu coba perbaikin bugnya
            int ID, idBuku;
            cout<<"Masukkan NIM :";
            cin>>ID;
            cout<<"Masukkan ID Buku : ";
            cin>>idBuku;
            address_relasi P = findElmRelasi(L3, ID, idBuku);
            while(P == NULL)
            {
                cout<<"Data tidak ditemukan"<<endl;
                cout<<"Masukkan NIM :";
                cin>>ID;
                cout<<"Masukkan ID Buku : ";
                cin>>idBuku;
                P = findElmRelasi(L3, ID, idBuku);
            }
            if(P == first_relasi(L3))
            {
                deleteFirstRelasi(L3, P);
            }
            else if(P == last_relasi(L3))
            {
                deleteLastRelasi(L3, P);
            }
            else
            {
                deleteAfterRelasi(L3, prev_Relasi(P), P);
            }
        }
        case 7 :
        {
            printInfoRelasi(L3);
            break;
        }
        case 8 :
            {
                int nim;
                cout<<"Masukkan NIM : ";
                cin>>nim;
                address_parent P = findElmParent(L1, nim);
                address_relasi Q = findElmRelasiParent(L3, P);
                break;

            }
        case 9 :
            {
                int id;
                cout<<"Masukkan NIM : ";
                cin>>id;
                address_parent P = findElmParent(L1, id);
                address_relasi Q = findElmRelasiParent(L3, P);
                if(Q != NULL){
                    cout<<"Masih Ada Buku yang Belum Dikembalikan"<<endl;
                }else{
                   deleteParent(L1, P);
                }
                break;
             }
        case 10 :
            {
                int idBuku;
                cout<<"Masukkan ID Buku : ";
                cin>>idBuku;
                address_child P = findElmChild(L2, idBuku);
                address_relasi Q = findElmRelasiChild(L3, P);
                if(Q != NULL){
                    cout<<"Masih Ada Buku yang Belum Dikembalikan"<<endl;
                }else{
                   deleteChild(L2, P);
                }
                break;
            }
        case 13:
        {
            int sum = totalPeminjaman(L3);
            cout<<"Total peminjaman : "<<sum<<endl;
            break;
        }
        }

        cout<<endl;

    }
    while(pilih != 0);
    return 0;
}
