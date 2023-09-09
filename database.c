// C program to implement one side of FIFO 
// This side reads first, then reads 
#include <stdio.h> 
#include <string.h> 
#include <fcntl.h> 
#include <sys/stat.h> 
#include <sys/types.h> 
#include <unistd.h> 
  
int main() 
{ 
    int fd1; 
  
    // FIFO file path 
    char * myfifo = "/tmp/myfifo"; 
  
    // Creating the named file(FIFO) 
    // mkfifo(<pathname>,<permission>) 
    mkfifo(myfifo, 0666); 
  
    char sorgu[80], str2[80]; 
    while (1) 
    { 
        // First open in read only and read 
        fd1 = open(myfifo,O_RDONLY); 
        read(fd1, sorgu, 80); 
        printf("Sorgu:%s\n",sorgu);

        int sorgeLen = strlen(sorgu);
        int boslukInd[5];
        int count = 0;
        int i = 0, j = 0, esittirInd = 0;

        for(i = 0 ; i <sorgeLen ; i++){
            if(sorgu[i] == ' '){
                boslukInd[count] = i;
                count++;
            }
        }
        for(i = 0 ; i <sorgeLen ; i++){
            if(sorgu[i] == '='){
                esittirInd = i;
            }
        }

        char istenen[20], dosyaAdi[20], sutun[20], deger[20];
        for(i = boslukInd[0] + 1, j = 0; i < boslukInd[1] ; i++, j++){
            istenen[j] = sorgu[i];
            istenen[j+1] = '\0';
        }
        for(i = boslukInd[2] + 1, j = 0; i < boslukInd[3] ; i++, j++){
            dosyaAdi[j] = sorgu[i];
            dosyaAdi[j+1] = '\0';
        }
        for(i = boslukInd[4] + 1, j = 0; i < esittirInd ; i++, j++){
            sutun[j] = sorgu[i];
            sutun[j+1] = '\0';
        }
        for(i = esittirInd + 1, j = 0; i < sorgeLen -1 ; i++, j++){
            deger[j] = sorgu[i];
            deger[j+1] = '\0';
        }

        //printf("%s %s %s %s\n ", istenen, dosyaAdi, sutun, deger);
        int control = 0;
        FILE * fp;
        char kelime[100];
        char deger2[100];
        if(strcmp(dosyaAdi, "veri1.txt")==0){
            fp = fopen ("veri1.txt", "r+");
            if(strcmp(sutun, "ad")==0){
                while(fscanf(fp,"%s %s", kelime, deger2) != EOF){     
                    if(strcmp(kelime, deger)==0){
                        control = 1;
                        break;
                    }
                }
            }
            if(strcmp(sutun, "number")==0){
                while(fscanf(fp,"%s %s", kelime, deger2) != EOF){     
                    if(strcmp(deger2, deger)==0){
                        control = 1;
                        break;
                    }
                }
            }
        }
        if(strcmp(dosyaAdi, "veri2.txt")==0){
            fp = fopen ("veri2.txt", "r+");
            if(strcmp(sutun, "ad")==0){
                while(fscanf(fp,"%s %s", kelime, deger2) != EOF){     
                    if(strcmp(kelime, deger)==0){
                        control = 1;
                        break;
                    }
                }
            }
            if(strcmp(sutun, "number")==0){
                while(fscanf(fp,"%s %s", kelime, deger2) != EOF){     
                    if(strcmp(deger2, deger)==0){
                        control = 1;
                        break;
                    }
                }
            }
        }
        // Print the read string and close 
        close(fd1); 
  
        // Now open in write mode and write 
        // string taken from user. 
        fd1 = open(myfifo,O_WRONLY);
        if(control == 0){
            char ret[5] = "null";
            ret[5] = '\0';
            write(fd1, ret, strlen(ret)+1);
        }
        if(control == 1){
            if(strcmp(istenen, "ad") == 0){
                write(fd1, kelime, strlen(kelime)+1); 
            }
            if(strcmp(istenen, "number") == 0){
                write(fd1, deger2, strlen(deger2)+1); 
            }
            if(strcmp(istenen, "*") == 0){
                int len1 = strlen(kelime);
                int len2 = strlen(deger2);
                int len3 = len1+len2+1;
                char res[len3];
                for(i = 0 ; i < len1 ; i++){
                    res[i] = kelime[i];
                }
                res[len1] = ' ';
                for(i = len1 + 1, j = 0; i < len3 ; i++, j++){
                    res[i] = deger2[j];
                }
                res[len3] = '\0';
                write(fd1, res, len3+1); 
            }
        }
        
        
        close(fd1); 
    } 
    return 0; 
} 