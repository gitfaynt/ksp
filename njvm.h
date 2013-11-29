#define HALT                   0

#define PUSHC		           1

#define ADD                    2
#define SUB                    3
#define MUL                    4
#define DIV                    5
#define MOD                    6

#define RDINT                  7
#define WRINT                  8
#define RDCHR                  9
#define WRCHR                  10

#define PUSHG	               11
#define POPG	               12

#define ASF		               13
#define RSF                    14
#define PUSHL	               15
#define POPL	               16

#define EQ                     17
#define NE                     18
#define LT                     19
#define LE                     20
#define GT                     21
#define GE                     22

#define JMP			           23
#define BRF			           24
#define BRT			           25
/*
#define CALL 22
#define RET 23
#define DROP 24
#define PUSHR 25
#define POPR 26
*/

#define IMMEDIATE(x) ((x) & 0x00FFFFFFF)
#define SIGN_EXTEND(i) ((i) & 0x00800000 ? (i) | 0xFF000000 : (i))

#define BIN 1178749518
#define SIZE 1000
#define VERSION 2

void debug(void);
void pushg(int wert);
void pushc(int wert);
void pushl(int wert);
void popg(int wert);
void popl(int wert);
void push(int wert);
void listProg();
void execProg();
void openFile();
int pop();