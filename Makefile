CC = m68k-palmos-gcc
CFLAGS = -O2 -IWristPDA_SDK_v1.3/Include

all: CrypticWatch.prc

CrypticWatch.prc: CrypticWatch bin.stamp
	build-prc CrypticWatch.prc "CrypticWatch" Foss CrypticWatch *.bin

CrypticWatch: main.o
	$(CC) $(CFLAGS) -o CrypticWatch main.o

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

bin.stamp: res.rcp res.h
	pilrc res.rcp

clean:
	-rm -f *.[oa] CrypticWatch *.bin *.stamp
