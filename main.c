//Homework3 Var1
#include <stdio.h>
#include <stdlib.h>
#include "list.h"

int main(int argc, char *argv[]){
	FILE *fo = NULL;

	if(argc != 2)
	{
		printf("need one text file");
		exit (1);
	}

  	if ((fo = fopen(argv[1], "r")) == NULL)
  	{
		printf("cant open file", argv[1]);
		exit (1);
	}
	
	if(!create_list(fo))
	{
		printf("Error");
		exit(1);
	}
	fclose(fo);
}

