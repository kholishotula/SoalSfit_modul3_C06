# SoalShift_modul3_C06

Kholishotul Amaliah   05111740000030<br>
Nandha Himawan        05111740000180

1. Buatlah program C yang bisa menghitung faktorial secara parallel lalu menampilkan hasilnya secara berurutan<br>
Contoh:<br>
    ./faktorial 5 3 4<br>
    3! = 6<br>
    4! = 24<br>
    5! = 120<br>
    
Langkah-langkah :<br>
- Menyimpan jumlah argumen ke variabel argc, dan menyimpan argumennya dalam bentuk array ke variabel argv[]
- Membuat array of integer untuk menyimpan nilai argumen
```c
int num[size];
for(i=1;i<size;i++) {
	num[i] = atoi(argv[i]);
}
```
- Menyortir array num dari nilai kecil ke besar menggunakan bubble sort
```c
void sort (int A[], int n)
{
	int a, i, j;
	for (i = 1; i < n; ++i) 
	{
		for (j = i + 1; j < n; ++j)
		{
			if (A[i] > A[j]) 
			{
				a = A[i];
				A[i] = A[j];
				A[j] = a;
			}
		}
	}
}
```
dan memanggilnya dengan
```c
sort(num, size);
```
- Mengalokasikan array of thread sebesar jumlah argumen dan create thread tersebut dengan passing argumen angka dari array num dan menjalankan fungsi faktorial
```c
pthread_t tid[size];

for(i=1;i<size;i++) {
	pthread_create(&tid[i], NULL, faktorial, &num[i]);
}
```
- Fungsi faktorial. hasil faktorial disimpan dalam array of integer dengan nama result
```c
void *faktorial(void *arg)
{
	int i, j;
	int res;
	int *num = (int*) arg;
	res = 1;
	for(i=2;i<=*num;i++) {
		res*=i;
	}
	result[iter] = res;
	iter++;
}
```
- Jangan lupa thread nya dijoin
```c
for(i=1;i<size;i++) {
	pthread_join(tid[i], NULL);
}
```
- Menyortir array hasil faktorial
```c
sort(result, size);
```
- Menampilkan hasil faktorial
```c
for(i=1;i<size;i++) {
		printf("%d! = %d\n", num[i], result[i]);
	}
```

2. Pada suatu hari ada orang yang ingin berjualan 1 jenis barang secara private, dia memintamu membuat program C dengan spesifikasi sebagai berikut:<br>
a. Terdapat 2 server: server penjual dan server pembeli<br>
b. 1 server hanya bisa terkoneksi dengan 1 client<br>
c. Server penjual dan server pembeli memiliki stok barang yang selalu sama<br>
d. Client yang terkoneksi ke server penjual hanya bisa menambah stok
- Cara menambah stok: client yang terkoneksi ke server penjual mengirim string “tambah” ke server lalu stok bertambah 1<br>
e. Client yang terkoneksi ke server pembeli hanya bisa mengurangi stok
- Cara mengurangi stok: client yang terkoneksi ke server pembeli mengirim string “beli” ke server lalu stok berkurang 1<br>
f. Server pembeli akan mengirimkan info ke client yang terhubung dengannya apakah transaksi berhasil atau tidak berdasarkan ketersediaan stok
- Jika stok habis maka client yang terkoneksi ke server pembeli akan mencetak “transaksi gagal”<br>
- Jika stok masih ada maka client yang terkoneksi ke server pembeli akan mencetak “transaksi berhasil”<br>
g. Server penjual akan mencetak stok saat ini setiap 5 detik sekali<br>
h. Menggunakan thread, socket, shared memory<br>
-Server Penjual<br>
-untuk menambah stok gunakan :
```
while(1){
    char buffer[1024] = {0};
    valread = read( new_socket , buffer, 1024);
    if(strcmp(buffer,"tambah")==0){
        *value = *value+1;
        printf("%d\n", *value);
        
    }
```
-untuk menampilkan stok tiap 5 detik, gunakan thread :
```
void* tampilstok (void* arg){
key_t key = 1234;
int *value; 

int shmid = shmget(key, sizeof(int), IPC_CREAT | 0666);
value = shmat(shmid, NULL, 0);
while(1){
    if(flag == 0)
    break;

    printf("stok : %d\n",*value);
    sleep(5);
}
}
```
-Server Pembeli<br>
-untuk mengurangi stok gunakan :
```
while(1){
    char buffer[1024] = {0};
    valread = read( new_socket , buffer, 1024);
    if(strcmp(buffer,"beli")==0){
        if(*value>0){
            *value = *value - 1;
            char *sukses = "Transaksi Berhasil\n";
            send(new_socket , sukses , strlen(sukses) , 0 );
        }
        else{
            char *gagal = "Transaksi Gagal\n";
            send(new_socket , gagal , strlen(gagal) , 0 );
        }
    }
```
-kedua server menggunakan shared memory untuk variabel penyimpan jumlah stok barang :
```
key_t key = 1234;
int *value;

int shmid = shmget(key, sizeof(int), IPC_CREAT | 0666);
value = shmat(shmid, NULL, 0);
```

-Client<br>
-pilih akan connect ke server mana :
```
        printf("insert port : \n1.Penjual(8080)\n2.Pembeli(8081)\n");
        int x; scanf("%d",&x);
        PORT = x;
```
-sambungkan dengan server menggunakan thread :
```
        pthread_create(&thread1, NULL, konek, NULL);
        pthread_join(thread1,NULL);
```

    
3. Agmal dan Iraj merupakan 2 sahabat yang sedang kuliah dan hidup satu kostan, sayangnya mereka mempunyai gaya hidup yang berkebalikan, dimana Iraj merupakan laki-laki yang sangat sehat,rajin berolahraga dan bangun tidak pernah kesiangan sedangkan Agmal hampir menghabiskan setengah umur hidupnya hanya untuk tidur dan ‘ngoding’. Dikarenakan mereka sahabat yang baik, Agmal dan iraj sama-sama ingin membuat satu sama lain mengikuti gaya hidup mereka dengan cara membuat Iraj sering tidur seperti Agmal, atau membuat Agmal selalu bangun pagi seperti Iraj. Buatlah suatu program C untuk menggambarkan kehidupan mereka dengan spesifikasi sebagai berikut:<br>
a. Terdapat 2 karakter Agmal dan Iraj<br>
b. Kedua karakter memiliki status yang unik
- Agmal mempunyai WakeUp_Status, di awal program memiliki status 0
- Iraj memiliki Spirit_Status, di awal program memiliki status 100
- Terdapat 3 Fitur utama
	+ All Status, yaitu menampilkan status kedua sahabat<br>
	Ex: Agmal WakeUp_Status = 75 <br>
	Iraj Spirit_Status = 30
	+ “Agmal Ayo Bangun” menambah WakeUp_Status Agmal sebesar 15 point
	+ “Iraj Ayo Tidur” mengurangi Spirit_Status Iraj sebanyak 20 point
- Terdapat Kasus yang unik dimana:
	+ Jika Fitur “Agmal Ayo Bangun” dijalankan sebanyak 3 kali, maka Fitur “Iraj Ayo Tidur” Tidak bisa dijalankan selama 10 detik (Dengan mengirim pesan ke sistem “Fitur Iraj Ayo Tidur disabled 10 s”)
	+ Jika Fitur  “Iraj Ayo Tidur” dijalankan sebanyak 3 kali, maka Fitur “Agmal Ayo Bangun” Tidak bisa dijalankan selama 10 detik (Dengan mengirim pesan ke sistem “Agmal Ayo Bangun disabled 10 s”)
- Program akan berhenti jika Salah Satu :
	+ WakeUp_Status Agmal >= 100 (Tampilkan Pesan “Agmal Terbangun,mereka bangun pagi dan berolahraga”)
	+ Spirit_Status Iraj <= 0 (Tampilkan Pesan “Iraj ikut tidur, dan bangun kesiangan bersama Agmal”)
- Syarat Menggunakan Lebih dari 1 Thread

Langkah-langkah :<br>
- 

4. Buatlah sebuah program C dimana dapat menyimpan list proses yang sedang berjalan (ps -aux) maksimal 10 list proses. Dimana awalnya list proses disimpan dalam di 2 file ekstensi .txt yaitu  SimpanProses1.txt di direktori /home/Document/FolderProses1 dan SimpanProses2.txt di direktori /home/Document/FolderProses2 , setelah itu masing2 file di  kompres zip dengan format nama file KompresProses1.zip dan KompresProses2.zip dan file SimpanProses1.txt dan SimpanProses2.txt akan otomatis terhapus, setelah itu program akan menunggu selama 15 detik lalu program akan mengekstrak kembali file KompresProses1.zip dan KompresProses2.zip <br>
Dengan Syarat : <br>
- Setiap list proses yang di simpan dalam masing-masing file .txt harus berjalan bersama-sama
- Ketika mengkompres masing-masing file .txt harus berjalan bersama-sama
- Ketika Mengekstrak file .zip juga harus secara bersama-sama
- Ketika Telah Selesai melakukan kompress file .zip masing-masing file, maka program akan memberi pesan “Menunggu 15 detik untuk mengekstrak kembali”
- Wajib Menggunakan Multithreading
- Boleh menggunakan system

Langkah-langkah :<br>
- Mengalokasikan array of thread sebesar 2, untuk masing2 proses
```c
pthread_t tid1[2];
pthread_t tid2[2];
pthread_t tid3[2];
```
- Create thread untuk simpan proses terlebih dahulu, lalu dijoinkan
```c
pthread_create(&tid1[0], NULL, simpan_proses1, NULL);
pthread_create(&tid1[1], NULL, simpan_proses2, NULL);
pthread_join(tid1[0], NULL);
pthread_join(tid1[1], NULL);
```
Untuk mendapatkan list proses, maka ps -aux. Untuk mendapatkan 10 proses saja, maka menggunakan head -n 11. tail -n 10 diperlukan untuk mendapatkan list proses saja, tanpa header. Kemudian disimpan ke direktori yang diinginkan. Fungsi simpan_proses adalah sebagai berikut
```c
void* simpan_proses1(void *arg)
{
	system("ps -aux | head -n 11 | tail -n 10 > /home/maya/Documents/FolderProses1/SimpanProses1.txt");
}

void* simpan_proses2(void *arg)
{
	system("ps -aux | head -n 11 | tail -n 10 > /home/maya/Documents/FolderProses2/SimpanProses2.txt");
}
```
- Create thread untuk mengompres file terlebih dahulu, lalu dijoinkan
```c
pthread_create(&tid2[0], NULL, kompres1, NULL);
pthread_create(&tid2[1], NULL, kompres2, NULL);
pthread_join(tid2[0], NULL);
pthread_join(tid2[1], NULL);
```
Supaya setelah mengompres file tersebut dihapus, maka kami menggunakan opsi -mj
```c
void *kompres1(void *arg)
{
	system("zip -mj /home/maya/Documents/FolderProses1/KompresProses1.zip /home/maya/Documents/FolderProses1/SimpanProses1.txt");
	status = 1;
}

void *kompres2(void *arg)
{
	system("zip -mj /home/maya/Documents/FolderProses2/KompresProses2.zip /home/maya/Documents/FolderProses2/SimpanProses2.txt");
	status = 1;
}
```
- Ketika proses kompres selesai, menampilkan pesan menunggu dan sleep sistem selama 15 detik. Untuk mengetahui status bahwa kompres selesai, kami menggunakan variabel global status, yang akan bernilai 1 ketika kompres selesai
```c
while(status!=1) {}
printf("Menunggu 15 detik untuk mengekstrak kembali\n");
sleep(15);
```
- Create thread untuk mengekstrak terlebih dahulu, lalu dijoinkan
```c
pthread_create(&tid3[0], NULL, ekstrak1, NULL);
pthread_create(&tid3[1], NULL, ekstrak2, NULL);
pthread_join(tid3[0], NULL);
pthread_join(tid3[1], NULL);
```
dengan fungsi ekstrak sebagai berikut
```c
void * ekstrak1(void *arg)
{
	system("unzip /home/maya/Documents/FolderProses1/KompresProses1.zip -d /home/maya/Documents/FolderProses1");
}

void * ekstrak2(void *arg)
{
	system("unzip /home/maya/Documents/FolderProses2/KompresProses2.zip -d /home/maya/Documents/FolderProses2");
}
```

5. Angga, adik Jiwang akan berulang tahun yang ke sembilan pada tanggal 6 April besok. Karena lupa menabung, Jiwang tidak mempunyai uang sepeserpun untuk membelikan Angga kado. Kamu sebagai sahabat Jiwang ingin membantu Jiwang membahagiakan adiknya sehingga kamu menawarkan bantuan membuatkan permainan komputer sederhana menggunakan program C. Jiwang sangat menyukai idemu tersebut. Berikut permainan yang Jiwang minta.<br>
a. Pemain memelihara seekor monster lucu dalam permainan. Pemain dapat  memberi nama pada monsternya.<br>
b. Monster pemain memiliki hunger status yang berawal dengan nilai 200 (maksimalnya) dan nanti akan berkurang 5 tiap 10 detik.Ketika hunger status mencapai angka nol, pemain akan kalah. Hunger status dapat bertambah 15 apabila pemain memberi makan kepada monster, tetapi banyak makanan terbatas dan harus beli di Market.<br>
c. Monster pemain memiliki hygiene status yang berawal dari 100 dan nanti berkurang 10 tiap 30 detik. Ketika hygiene status mencapai angka nol, pemain akan kalah. Hygiene status' dapat bertambah 30 hanya dengan memandikan monster. Pemain dapat memandikannya setiap 20 detik(cooldownnya 20 detik).<br>
d. Monster pemain memiliki health status yang berawal dengan nilai 300. Variabel ini bertambah (regenerasi)daa 5 setiap 10 detik ketika monster dalam keadaan standby.<br>
e. Monster pemain dapat memasuki keadaan battle. Dalam keadaan ini, food status(fitur b), hygiene status'(fitur c), dan ‘regenerasi’(fitur d) tidak akan berjalan. Health status dari monster dimulai dari darah saat monster pemain memasuki battle. Monster pemain akan bertarung dengan monster NPC yang memiliki darah 100. Baik monster pemain maupun NPC memiliki serangan sebesar 20. Monster pemain dengan monster musuh akan menyerang secara bergantian. <br>
f. Fitur shop, pemain dapat membeli makanan sepuas-puasnya selama stok di toko masih tersedia.
- Pembeli (terintegrasi dengan game)
  + Dapat mengecek stok makanan yang ada di toko.
  + Jika stok ada, pembeli dapat membeli makanan.
- Penjual (terpisah)
  + Bisa mengecek stok makanan yang ada di toko
  + Penjual dapat menambah stok makanan.<br>

Spesifikasi program:<br>
A. Program mampu mendeteksi input berupa key press. (Program bisa berjalan tanpa perlu menekan tombol enter)<br>
B. Program terdiri dari 3 scene yaitu standby, battle, dan shop.<br>
C. Pada saat berada di standby scene, program selalu menampilkan health status, hunger status, hygiene status, stok makanan tersisa, dan juga status kamar mandi (“Bath is ready” jika bisa digunakan, “Bath will be ready in [bath cooldown]s” jika sedang cooldown). Selain itu program selalu menampilkan 5 menu, yaitu memberi makan, mandi, battle, shop, dan exit. Contoh :<br>

Standby Mode<br>
Health : [health status]<br>
Hunger : [hunger status]<br>
Hygiene : [hygiene status]<br>
Food left : [your food stock]<br>
Bath will be ready in [cooldown]s<br>
Choices<br>
1. Eat
2. Bath
3. Battle
4. Shop
5. Exit

D. Pada saat berada di battle scene, program selalu menampilkan health status milik pemain dan monster NPC. Selain itu, program selalu menampilkan 2 menu yaitu serang atau lari. Contoh :

Battle Mode<br>
Monster’s Health : [health status]<br>
Enemy’s Health : [enemy health status]<br>
Choices<br>
1. Attack
2. Run

E. Pada saat berada di shop scene versi pembeli, program selalu menampilkan food stock toko dan milik pemain. Selain itu, program selalu menampilkan 2 menu yaitu beli dan kembali ke standby scene. Contoh :

Shop Mode<br>
Shop food stock : [shop food stock]<br>
Your food stock : [your food stock]<br>
Choices<br>
1. Buy
2. Back

F. Pada program penjual, program selalu menampilkan food stock toko. Selain itu, program juga menampilkan 2 menu yaitu restock dan exit. Contoh :

Shop<br>
Food stock : [shop food stock]<br>
Choices<br>
1. Restock
2. Exit

G. Pastikan terminal hanya mendisplay status detik ini sesuai scene terkait (hint: menggunakan system(“clear”))
