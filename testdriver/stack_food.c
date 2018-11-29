/**
 * Engi's Kitchen Expansion
 * Stack food test driver
 *
 * @author Muhammad Yanza Hattari, NIM 18217043
 */
#include "../adt/food_stack.h" 

int main () { 
	
	Food food;
	Stack stackfood ; 
	Kata kata;
	int price,x,y,i;
	
	CreateEmpty(&stackfood);
	kata = BuildKata("Kola");
	
	price = 100;
	x = 2;
	y =5;
	food = CreateFood(MakePOINT(x,y),kata,price);
	Push(&stackfood,&food);

	kata = BuildKata("Audi");

	price = 200;
	x = 3;
	y =6;
	food = CreateFood(MakePOINT(x,y),kata,price);
	Push(&stackfood,&food);
	
	printf("%d \n",NbElmt(stackfood));
	Food * ptrfood;
	Pop(&stackfood, &ptrfood);
	
	Kata foodname = ptrfood->name;
	for (i=1;i<=foodname.Length;i++) {
		printf("%c",foodname.TabKata[i]);
	}
	printf("\n");
	
	return 0;
} 
