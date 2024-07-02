#include<stdio.h>
#include<string.h>
typedef char* Position;
#define NotFound NULL 

char *Mystr(char* string,char *pattern){
	int Strlen = strlen(string);
	int Patlen = strlen(pattern);
	int i,j;
	int tmpi;
	for(i=0;i<Strlen;i++){
		tmpi=i;
		j=0;
		while(string[tmpi++] == pattern[j++] && j < Patlen);
		if(j==Patlen){
			return string+i;
		}
	}
	return NULL;
}


int main(){
	char string[] = "this is a simple example.";
//	char string[] = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
	char pattern[] = "simple";
//	char pattern[] = "ab";
	Position p = Mystr(string,pattern);
	if(p==NotFound)
		printf("NotFound\n");
	else
		printf("%s",p);
	return 0;
} 
