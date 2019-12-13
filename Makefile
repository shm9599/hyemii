all: led.h led.c button.h button.c buzzer.h buzzer.c fnd.h fnd.c textlcd.h textlcd.c bitmap.h bitmao.c 
	gcc -c led.c -o led.o
	gcc -c button.c -o button.o
	gcc -c buzzer.c -o buzzer.o
	gcc -c fnd.c -o fnd.o
	gcc -c textlcd.c -o textlcd.o
	gcc -c bitmap.c -o bitmap.o
	ar rc libMyPeri.a led.o button.o buzzer.o fnd.o textlcd.o bitmap.o
	gcc main89.c -o gametest -lMyPeri -L -lpthread



