
#include "../adt/food_stack.h" 
#include "../adt/obj/food.h"


int main () { 
	
	Food food;
	Stack stackfood ; 
	Kata kata;
	int price,x,y;
	
	CreateEmpty(&stackfood);
	kata.TabKata[1] = 'K';
	kata.TabKata[2] = 'o';
	kata.TabKata[3] = 'l';
	kata.TabKata[4] = 'a';
	kata.Length = 4;
	
	price = 100;
	x = 2;
	y =5;
	food = CreateFood(MakePOINT(x,y),kata,price);
	Push(&stackfood,&food);
	
	kata.TabKata[1] = 'a';
	kata.TabKata[2] = 'u';
	kata.TabKata[3] = 'd';
	kata.TabKata[4] = 'i';
	kata.Length = 4;
	
	price = 200;
	x = 3;
	y =6;
	food = CreateFood(MakePOINT(x,y),kata,price);
	Push(&stackfood,&food);
	
	printf("%d \n",NbElmt(stackfood));
	//TODO POP MAAF DIT GUE GA BISA POP ANEH BET
	return 0;
} 
