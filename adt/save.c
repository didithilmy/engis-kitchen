#include <stdlib.h>
#include <stdio.h>

int main () {
	int i;
	char buffer[sizeof(int) * 4+1];
	
	FILE *f = fopen("fileeks.txt","w");
	
	
	char * nama = "hatta";
	int money = 1000;
	int life = 50;
	int time = 342;
	
	typedef struct {
		int capacity;
		int patience;
	} typequeue;
	
	typedef struct {
		int capacity;
		int isi;
		int patience;
		char * makanan;
	} typemeja;
	
	typequeue queue[10];
	typemeja meja[10];
	
	fprintf(f,"(%s );",nama); //ini untuk nama

	sprintf(buffer,"(%d );",money);
	fprintf(f,buffer);
	
	sprintf(buffer,"(%d );",life);
	fprintf(f,buffer);
	
	sprintf(buffer,"(%d );",time);
	fprintf(f,buffer);
	
	queue[1].capacity = 2; 
	queue[1].patience = 30;
	queue[2].capacity = 4;
	queue[2].patience = 14;
	queue[3].capacity = 2;
	queue[3].patience = 25;
	queue[4].capacity = 0;
	queue[4].patience = 0;
	
	i = 1;
	while (queue[i].capacity != 0) { // while (queue) != NULL 
		sprintf(buffer,"(%d %d )",queue[i].capacity,queue[i].patience);
		fprintf(f,buffer);
		i++;
	}
	fprintf(f,";"); //untuk ngasi ';'
	
	char * stack[10];
	stack[1] = "nasgor";
	stack[2] = "ayam";
	stack[3] = "hahaha";
	stack[4] = "null";
	i=1;
	while ( stack[i] != "null") { //while stack ga null
		fprintf (f,"(%s )",stack[i]);
		i++;
	}
	fprintf(f,";"); //untuk ngasi  
	
	meja[1].capacity = 2;
	meja[1].isi = 2;
	meja[1].patience = 20;
	meja[1].makanan = "nasgor";
	meja[2].capacity = 4;
	meja[2].isi = 2;
	meja[2].patience = 15;
	meja[2].makanan = "ayam";
	meja[3].capacity = 2;
	meja[3].isi = 2;
	meja[3].patience = 10;
	meja[3].makanan = "hahaha";
	meja[4].capacity = 2;
	meja[4].isi = 0;
	meja[4].patience = 0;
	meja[4].makanan = "null";
	
	i=1;
	while ( meja[i].isi != 0) { //while stack ga null
		sprintf(buffer,"%d %d %d ",meja[i].capacity, meja[i].isi, meja[i].patience);
		fprintf (f,"(%s %s )",buffer,meja[i].makanan);
		i++;
	}
	fprintf(f,".");
	
	fclose(f);
	return 0;
}