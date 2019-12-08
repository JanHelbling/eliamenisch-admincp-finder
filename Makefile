all:
	gcc -c wordlist.c -Ofast
	gcc -Ofast main.c -lmicrohttp -lssl -lcrypto wordlist.o -o eliamenisch-admincp-finder
	strip eliamenisch-admincp-finder

clean:
	rm -f eliamenisch-admincp-finder *.o

install: all
	install -C -m 755 eliamenisch-admincp-finder /usr/bin/eliamenisch-admincp-finder

uninstall:
	rm /usr/bin/eliamenisch-admincp-finder
