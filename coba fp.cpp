#include <iostream>
#include <string>

#define max 10 // untuk membatasi stack pada history

const int MAX = 100; // maksimal jumlah antrian pada queue

using namespace std;

// Queue
struct Barang
{
    int nomorResi[MAX];
    string nama[MAX];
    int berat[MAX];
    string tujuan[MAX];
    int depan, ekor;
} q;

bool full(Barang *q)
{
    return (q->ekor == MAX - 1);
}

bool empty(Barang *q)
{
    return q->ekor == -1;
}

void display(Barang *q)
{
    if (empty(q))
    {
        cout << "Antrian kosong." << endl;
        return;
    }

    cout << "Isi Antrian:\n";
    for (int i = 0; i <= q->ekor; i++)
    {
        cout << "Nomor Resi: " << q->nomorResi[i] << " | Nama: " << q->nama[i]
             << " | Berat: " << q->berat[i] << " kg | Tujuan: " << q->tujuan[i] << endl;
    }
}

// Stack
struct History
{
    int nomorResi;
    string nama;
    int berat;
    string tujuan;
};

struct Tumpukan
{
    int atas;
    History data[max];
} T;

void awal(Tumpukan *T)
{
    T->atas = -1;
}

int kosong(Tumpukan *T)
{
    return (T->atas == -1);
}

int penuh(Tumpukan *T)
{
    return (T->atas == max - 1);
}

void input(Tumpukan *T, History data)
{
    if (!penuh(T))
    {
        T->atas++;
        T->data[T->atas] = data;
    }
}

void tampil(Tumpukan *T)
{
    if (kosong(T))
    {
        cout << "\nTumpukan kosong" << endl;
    }
    else
    {
        for (int i = T->atas; i >= 0; i--)
        {
            cout << "\nTumpukan ke " << i << " | Nomor Resi: " << T->data[i].nomorResi << " | Nama: " << T->data[i].nama
                 << " | Berat: " << T->data[i].berat << " kg | Tujuan: " << T->data[i].tujuan;
        }
    }
}

void urut(Tumpukan *T)
{
    // bubble sort
    int n = T->atas + 1; // Jumlah elemen dalam array
    History temp;

    for (int i = 0; i < n; i++)
    {
        for (int j = n - 1; j > i; j--)
        {
            if (T->data[j].tujuan < T->data[j - 1].tujuan)
            {
                temp = T->data[j];
                T->data[j] = T->data[j - 1];
                T->data[j - 1] = temp;
            }
        }
    }

    cout << "\nHistory Pengiriman (Urut berdasarkan nama tujuan):\n";
    tampil(T);
}

void bersih(Tumpukan *T)
{
    T->atas = -1;
    cout << "Tumpukan Sudah Kosong!";
}

void cari(Tumpukan *T)
{
    for (int i = T->atas; i >= 0; i--)
    {
        i;
        T->data[i].nomorResi;
        T->data[i].nama;
        T->data[i].berat;
        T->data[i].tujuan;
    }
}

int cariData(Tumpukan *T, string keyword)
{
    bool found = false; //false karang data seng digoleki durung ana
    int index = -1; // karena deklarasi variable index -1 membuat tumpukan masih seperti awal atau kosong

    for (int i = T->atas; i >= 0; i--)
    {
        if (T->data[i].nama == keyword)
        {
            found = true;
            index = i;
            break;
        }
    }

    return index;
}

int main()
{
    Barang q;
    q.depan = 0;
    q.ekor = -1;

    Tumpukan historyStack;
    awal(&historyStack);

    int pilihan;

    do
    {
        cout << "\n===========================================";
        cout << "\nMenu:\n";
        cout << "1. Masukkan Barang\n";
        cout << "2. Tampilkan Antrian Barang\n";
        cout << "3. Kirim Barang\n";
        cout << "4. History Pengiriman\n";
        cout << "5. Cari Data History\n";
        cout << "6. Bersihkan History \n";
        cout << "0. Keluar\n";
        cout << "===========================================\n";
        cout << "Pilih menu (0-6): ";
        cin >> pilihan;
        cout << endl;

        switch (pilihan)
        {
        case 1: //menggunakan queue
            if (!full(&q))
            {
                q.ekor++;
                q.nomorResi[q.ekor] = q.ekor + 1;
                cout << "Masukkan Nama: ";
                cin >> q.nama[q.ekor];
                cout << "Masukkan Berat / kg: ";
                cin >> q.berat[q.ekor];
                cout << "Masukkan Alamat: ";
                cin >> q.tujuan[q.ekor];
            }
            else
            {
                cout << "Antrian penuh" << endl;
            }
            break;

        case 2: // queue
            display(&q);
            break;

        case 3: //queue
            if (!empty(&q))
            {
                History historybaru;
                historybaru.nomorResi = q.nomorResi[q.depan];
                historybaru.nama = q.nama[q.depan];
                historybaru.berat = q.berat[q.depan];
                historybaru.tujuan = q.tujuan[q.depan]; 

                input(&historyStack, historybaru);

                cout << "Barang berhasil dikirim dengan nomor resi: " << historybaru.nomorResi << " (" << historybaru.nama << ")";

                // Geser antrian
                for (int i = q.depan; i < q.ekor; i++)
                {
                    q.nomorResi[i] = q.nomorResi[i + 1];
                    q.nama[i] = q.nama[i + 1];
                    q.berat[i] = q.berat[i + 1];
                    q.tujuan[i] = q.tujuan[i + 1];
                }

                q.ekor--;
            }
            else
            {
                cout << "Antrian kosong" << endl;
            }
            break;

        case 4:
            int pilihanSort;
            cout << "1. Menampilkan Semua History Terkirim\n";
            cout << "2. Menampilkan History Terkirim Sesuai Abjad Alamat\n\n";
            cout << "Masukan Pilihan : ";
            cin >> pilihanSort;

            if (pilihanSort == 1)
            {
                tampil(&historyStack);
            }
            else if (pilihanSort == 2)
            {
                urut(&historyStack);
            }
            else
            {
                cout << "Pilihan tidak valid";
            }
            break;

        case 5:
        {
            string keyword;
            cout << "Masukkan nama barang yang akan dicari: ";
            cin >> keyword;

            int index = cariData(&historyStack, keyword);

            if (index != -1)
            {
                cout << "\nData ditemukan pada history pengiriman:" << endl;
                cout << " | Nomor Resi: " << historyStack.data[index].nomorResi
                     << " | Nama: " << historyStack.data[index].nama
                     << " | Berat: " << historyStack.data[index].berat << " kg | Tujuan: " << historyStack.data[index].tujuan << endl;
            }
            else
            {
                cout << "Data tidak ditemukan pada history pengiriman." << endl;
            }

            break;
        }

        case 6:
            bersih(&historyStack);
            break;
        }
    } while (pilihan != 0);

    return 0;
}

