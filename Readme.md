Server boot
	Load user.txt dan memasukkan username dan password setiap user ke dalam queue (buffer)
	Load grup.txt dan memasukkan namagrup dan daftar user tiap grup ke buffer

1. Client Konek ke server 
	si server bikin thread
	kemudian nerima koneksi pake thread
	Nyimpen thread id dan IP dari client yang konek ke 

2. Client register:
	send message yang isinya "--register--|username|password;"
	Message diterima server, dan mencatat username, IP, dan password ke daftaruser.txt
	Saat menulis message berhasil, server mengirim message ke client kalau register berhasil

3. Client login
	send message yang isinya "--login--|username|password;"
	Server mencari username dan password di buffer, apakah cocok
	Jika cocok
		Message diterima server, dan mencatat username dan IP ke queue (buffer) (queue ini menyimpan user yang sedang online)
		Server mengecek message yang belum diterima oleh client
		Jika ada, message tersebut dikirim ke client

4. Client send message ke suatu IP:
	Client kirim message ke server yang isinya "username/namagrup tujuan | message"
	Jika yang dituju adalah username
		Server mencatat message ke txt
		Server mencari IP client tujuan dari buffer nomer 3 sehingga didapatkan thread id
		Server mengirim pesan dari client asal ke client tujuan
		message txt dihapus
	Jika yang dituju adalah grup
		Server menyimpan message ke file txt
		Server mencari list user anggota dari grup
		Server melakukan pengiriman message ke setiap user seperti mengirim ke username
		Jika ada yang offline, message disimpan dalam bentuk txt, dan kalau usernya online, messsage dikirim lagi
		Jika semua user 

5. Client logout
	Client mengirim pesan yang berisi "--logout--:username;"
	Server menulis log, menghapus buffer 

	
Keterangan setiap file
user.txt berisi "user|password;"
grup.txt berisi "grupname|user1,user2,user3,user-n;"
log.txt berisi "[tanggal jam] 'log'" --> append terus tiap update

TO DO:
	- GROUP Chat
	- LOG Personal Message (History Chat)
	- LOG Group Chat (History Masing2 Personal Chat)
	- USer Baca file pertama kali di server ketika login -> ada pesan/kaga
	- Nulis ke file kalo waktu chat lawan chat nya ga ol