all:
	gcc -c wordlist.c -Ofast
	gcc -Ofast main.c -lssl -lcrypto -lmicrohttp wordlist.o -o eliamenisch-admincp-finder
	strip eliamenisch-admincp-finder

clean:
	rm -f eliamenisch-admincp-finder *.o
