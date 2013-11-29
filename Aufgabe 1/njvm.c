#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define IMMEDIATE(x) ((x) & 0x00FFFFFFF)
#define SIGN_EXTEND(i) ((i) & 0x00800000 ? (i) | 0xFF000000 : (i))

#define HALT 		0

#define PUSHC 		1

#define ADD 		2
#define SUB		3
#define MUL		4
#define DIV		5
#define	MOD		6

#define RDINT		7
#define WRINT		8
#define RDCHR		9
#define WRCHR		10

int a, b, d;
int count; /*Programmzähler*/
unsigned int stackP = 0; /* Stack pointer*/
int stack[100];
unsigned int op;
int immediateV;

void listProg();
void execProg();

int pop() {
	stackP--;
	if (stackP < 0) {
		printf("Stack Unterlauf!\nNJVM wird beendet\n");
		exit(0);

	}
	return stack[stackP];
}

/****************************************************************************************************/
/*Funktion legt einen Wert auf den Stack*/
void pushc(int wert) {
	if (stackP >= 100) {
		printf("Stack Ueberlauf!\nNJVM wird beendet\n");
		exit(0);
	}
	stack[stackP] = wert;
	stackP++;
}

int main(int argc,char *argv[]){
	if (argc >1){
		if (strcmp(argv[1],"--version") == 0){
			printf("Version 1.0\n");
			return 0;
		}
	if (strcmp(argv[1],"--prog1") == 0){
			unsigned int prog_mem1[12];
			printf("Ninja Virtual Machine started\n");
			prog_mem1[0] = (PUSHC<<24)|IMMEDIATE(3);
			prog_mem1[1] = (PUSHC<<24)|IMMEDIATE(4);
			prog_mem1[2] = (ADD <<24);
			prog_mem1[4] = (PUSHC<<24)|IMMEDIATE(10);
			prog_mem1[5] = (PUSHC<<24)|IMMEDIATE(6);
			prog_mem1[6] = (SUB<<24);
			prog_mem1[7] = (MUL<<24);
			prog_mem1[8] = (WRINT<<24);
			prog_mem1[9] = (PUSHC<<24)|IMMEDIATE(10);
			prog_mem1[10]= (WRCHR<<24);
			prog_mem1[11]= (HALT<<24);
			listProg(sizeof(prog_mem1) / sizeof(int),prog_mem1);
			execProg(sizeof(prog_mem1) / sizeof(int),prog_mem1);
			return 0;
	}
	if (strcmp(argv[1],"--prog2") == 0){
			unsigned int prog_mem2[10];
			printf("Ninja Virtual Machine started\n");
			prog_mem2[0] = (PUSHC<<24)|IMMEDIATE(-2);
			prog_mem2[1] = (RDINT<<24);
			prog_mem2[3] = (MUL<<24);
			prog_mem2[4] = (PUSHC<<24)|IMMEDIATE(3);
			prog_mem2[5] = (ADD<<24);
			prog_mem2[6] = (WRINT<<24);
			prog_mem2[7] = (PUSHC<<24)|IMMEDIATE('\n');
			prog_mem2[8]= (WRCHR<<24);
			prog_mem2[9]= (HALT<<24);
			listProg(sizeof(prog_mem2) / sizeof(int),prog_mem2);
			execProg(sizeof(prog_mem2) / sizeof(int),prog_mem2);
			return 0;
	}
	if (strcmp(argv[1],"--prog3") == 0){
			unsigned int prog_mem3[5];
			printf("Ninja Virtual Machine started\n");
			prog_mem3[0]= (RDCHR<<24);
			prog_mem3[1] = (WRINT<<24);
			prog_mem3[2] = (PUSHC<<24)|IMMEDIATE('\n');
			prog_mem3[3]= (WRCHR<<24);
			prog_mem3[4]= (HALT<<24);
			listProg(sizeof(prog_mem3) / sizeof(int),prog_mem3);
			execProg(sizeof(prog_mem3) / sizeof(int),prog_mem3);
			return 0;
	}
	if (strcmp(argv[1],"--help") == 0){
		printf("--prog1		select program 1 to execute\n");
		printf("--prog2		select program 2 to execute\n");
		printf("--prog3		select program 3 to execute\n");
		printf("--version	show version and exit\n");
		printf("--help		show help and exit\n");
		return 0;
	}
}

printf("Ninja VM started\n");

return 0;
}

void listProg(int x, int prog_mem[]){
	count = 0;

	while (count < x){

		op = (prog_mem[count] & 0xFF000000) >> 24;
		immediateV = SIGN_EXTEND(prog_mem[count] & 0x00FFFFFF);		
			
		if (op == HALT){
			printf("%03i:\thalt\n",count);
		}
		if (op == PUSHC){
			printf("%03i:\tpushc\t%i\n", count, immediateV);
		}
		if (op == ADD){
			printf("%03i:\tadd\n",count);
		}
		if (op == SUB){
			printf("%03i:\tsub\n",count);
		}
		if (op == MUL){
			printf("%03i:\tmul\n",count);
		}
		if (op == DIV){
			printf("%03i:\tdiv\n",count);
		}
		if (op == MOD){
			printf("%03i:\tmod\n",count);
		}
		if (op == RDCHR){
			printf("%03i:\tRDCHR\n",count);
		}
		if (op == WRCHR){
			printf("%03i:\tWRCHR\n",count);
		}
		if (op == RDINT){
			printf("%03i:\tRDINT\n",count);
		}
		if (op == WRINT){
			printf("%03i:\tWRINT\n",count);
		}
		count++;
	}
}

void execProg(int x,int prog_mem[]){
	char c;
	count = 0;
	stackP = 0;

	op = (prog_mem[count] & 0xFF000000) >> 24;
	immediateV = SIGN_EXTEND(prog_mem[count] & 0x00FFFFFF);

	while (count < x){

		if (op == HALT){
			printf("Ninja VM stopped\n");
		}
		if (op == PUSHC){
			pushc(immediateV);
		}
		if (op == ADD){
			b = pop();
			a = pop();
			d = a+b;
			pushc(d);
		}
		if (op == SUB){
			b = pop();
			a = pop();
			d = a-b;
			pushc(d);
		}
		if (op == MUL){
			b = pop();
			a = pop();
			d = a*b;
			pushc(d);
		}
		if (op == DIV){
			b = pop();
			a = pop();	
			d = a/b;
			pushc(d);
		}
		if (op == MOD){
			b = pop();
			a = pop();
			if (b == 0) {
				printf("Modulorechnung durch 0 nicht erlaubt!\n");
				exit(0);
			}
			d = a%b;
			pushc(d);
	
		}
		if (op == RDCHR){
			if (scanf("%c", &c) == 0) {
				printf(
						"Unerwartete Eingabe.\n Program wird beendet\n");
				exit(0);
			}
			getchar();
			pushc(c);
		}
		if (op == WRCHR){
			printf("%c", pop());
		}
		if (op == RDINT){
			if (scanf("%i", &a) == 0) {
				printf(
						"Unerwartete Eingabe.\nProgram wird beendet\n");
				exit(0);
			}
			getchar();
			pushc(a);
		}
		if (op == WRINT){
			d= pop();
			printf("%i", d);
		}
		count++;
	}
}
