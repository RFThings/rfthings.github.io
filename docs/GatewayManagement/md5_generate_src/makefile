linux: main.c
	gcc -g -Wall -o md5_generate main.c -lssl -lcrypto -lc

windows:
	gcc -g -Wall -o md5_generate main.c -I "C:\Program Files\OpenSSL-Win64\include" -L "C:\Program Files\OpenSSL-Win64\lib\VC\x64\MD" -lssl -lcrypto

clean:
	rm -rf *.o md5_generate index.tmp.txt