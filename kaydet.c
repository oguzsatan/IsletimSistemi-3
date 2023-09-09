#include<stdio.h> 
#include<stdlib.h>
#include<unistd.h> 
#include<string.h>  
  
int main(int argc, char * argv[]) 
{ 
    FILE *fptr; 

    fptr = fopen("sonuc.txt", "a"); 
    if (fptr == NULL) 
    { 
        printf("Cannot open file \n"); 
        exit(0); 
    } 
    else
        fprintf(fptr, "%s\n", argv[1]);
  
    fclose(fptr); 
    return 0; 
}