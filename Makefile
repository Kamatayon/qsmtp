build: qsmtp.c
	gcc -shared -fPIC qsmtp.c smtp.c  -o qsmtp.so -DSMTP_OPENSSL -DKXVER=3 -lssl

