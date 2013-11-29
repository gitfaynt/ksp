#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "njvm.h"

int a, b, d;
unsigned int sp,fp;
int stack[SIZE];
unsigned int op;
int immediateV;
FILE *stream;
int fileSize;
int *fileArray;
int *sda;
int instructions;
int *progMem;

int main(int argc,char *argv[]){
	if (argc >1){
		if (strcmp(argv[1],"--version") == 0){
			printf("NJVM Version %i\n",VERSION);
			return 0;
		}
		if (strcmp(argv[1],"--help") == 0){
			printf("--version	show version and exit\n");
			printf("--help		show help and exit\n");
			return 0;
		}
		if ((strcmp(argv[1],"--help") == 1) && (strcmp(argv[1],"--version") == 1)){
			openFile(argv);

		    printf("Ninja VM started\n"); 

			listProg(instructions);
			execProg(instructions);
		}
	}
	return 0;
}

void openFile (char *argv[]){
	stream = fopen(argv[1],"r");

	if (stream == NULL){
		printf("Fehler beim öffnen\n");
		exit(99);
	}
	
	fseek(stream, 0, SEEK_END);
	fileSize= ftell(stream);
	fseek(stream, 0, SEEK_SET);

	printf("fs:%i",fileSize);
	fileArray = malloc(fileSize);
	fread(fileArray,4,fileSize,stream);
	
	if ( fileArray[0] != BIN){
		printf("ERROR: %s  is not a .bin file",argv[1]);
		exit(99);
	}
	if ( fileArray[1] > VERSION){
		printf("ERROR: file version is not compatible");
	}
	
	progMem = malloc(instructions);
	sda = malloc(fileArray[3]);
	instructions = *(fileArray+2);
	
	int i;
	for (i = 0;i < instructions;i++){
		progMem[i]= fileArray[i+4];
		printf("%i\n",fileArray[i+4]);
	}

	fclose(stream);
}

void listProg(int x){
	int count = 0;

	while (count < x){

		op = (progMem[count] & 0xFF000000) >> 24;
		immediateV = SIGN_EXTEND(progMem[count] & 0x00FFFFFF);		
		


		if (op == HALT){
			printf("%03i:\thalt\n",count);
		}
		if (op == PUSHC){
			printf("%03i:\tpushc\t%i\n", count, immediateV);
		}
		if (op == POPG){
			printf("%03i:\tpopg\t%i\n", count, immediateV);
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
		if (op == POPL){
			printf("%03i:\tpopl\t%i\n", count, immediateV);
		}
		if (op == PUSHL){
			printf("%03i:\tpushl\t%i\n", count, immediateV);
		}
		if (op == PUSHG){
			printf("%03i:\tpushg\t%i\n", count, immediateV);
		}

		count++;
	}
}

void execProg(int x){
	char c;
	int count = 0;
	sp = 0;
	fp = 0;

	while (count < x){
	
		op = (progMem[count] & 0xFF000000) >> 24;
		immediateV = SIGN_EXTEND(progMem[count] & 0x00FFFFFF);
		
		printf("%ixx%i\n",op,immediateV);

		if (op == HALT){
			printf("Ninja VM stopped\n");
			exit(0);
		}
		if (op == PUSHC){
			pushc(immediateV);
		}
		if (op == WRCHR){
			printf("%c", pop());
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
			printf("rdtest");
		}
		if (op == WRCHR){
			printf("%c", pop());
		}
		if (op == RDINT){
			scanf("%i", &a);
			pushc(a);
		}
		if (op == WRINT){
			printf("%i", pop());
		}
		if (op == PUSHG){
			pushg(immediateV);
		}
		if (op == PUSHL){
			pushl(immediateV);
		}
		if (op == POPG){
			popg(immediateV);
		}
		if (op == POPL){
			popl(immediateV);
		}
		if (op == ASF){
			fp = sp;
			sp = sp + immediateV;
		}
		if (op == RSF){
			fp = sp;
			fp = pop();
		}
		if (op == JMP){
			count = immediateV-1;
		}
		if (op == BRF){
			a = pop();
			if (a == 0){
				count = immediateV-1;
			}
		}
		if (op == BRT){
			a = pop();
			if (a == 1){
				count = immediateV-1;
			}
		}
		if (op == EQ){
			b = pop();
			a = pop();
			if (a == b){
				push(1);
			}else{
				push(0);
			}
		}
		if (op == NE){
			b = pop();
			a = pop();
			if (a != b){
				push(1);
			}else{
				push(0);
			}
		}
		if (op == LT){
			b = pop();
			a = pop();
			if (a > b){
				push(1);
			}else{
				push(0);
			}
		}
		if (op == LE){
			b = pop();
			a = pop();
			if (a >= b){
				push(1);
			}else{
				push(0);
			}
		}
		if (op == GT){
			b = pop();
			a = pop();
			if (a < b){
				push(1);
			}else{
				push(0);
			}
		}
		if (op == GE){
			b = pop();
			a = pop();
			if (a <= b){
				push(1);
			}else{
				push(0);
			}
		}
		count++;
	}
}

void push(wert){
	if ( sp < SIZE){
		printf("ERROR: Stack Overflow\n");
		exit(99);
	}
	stack[sp] = wert;
	sp++;
}
void pushg(wert){
	if ( sp > SIZE){
		printf("ERROR: Stack Overflow\n");
		exit(99);
	}
	stack[sp] = *(sda+wert);
	sp++;
}
void pushl(wert){
	stack[sp] = stack[fp+wert];
	sp++;
}
void popl(wert){
	sp--;
	stack[fp+wert] = stack[sp];
}
void popg(wert){
	*(sda+wert) = pop();
}
void pushc(int wert) {
	if (sp >= SIZE) {
		printf("Stack Overflow\nNJVM stopped\n");
		exit(99);
	}
	stack[sp] = wert;
	sp++;
}

int pop() {
	sp--;
	if (sp < 0) {
		printf("Stack underflow\nNJVM stopped\n");
		exit(99);
	}
	return stack[sp];
}
