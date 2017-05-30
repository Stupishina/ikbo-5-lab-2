#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define K 256

int *tape;
int size = 1;
int l = 0;

char* space (char* s, char* a);

int main() {
char c[K], name[K], **a;
int N=0, i = 0;
FILE *File;
printf ("Enter file name\n");
scanf("%s", name);
File = fopen(name, "r");
while (File == NULL){
    printf("File not found. Try again.\n");
    scanf("%s", name);
    File=fopen(name, "r");
}

a=(char**)malloc((N+1)*sizeof(char*));
while(fgets(c, K, File)) {
    if(c[0] != '*'){
        a[N]=space(c, a[N]);
        N++;
        a=(char**)realloc(a,(N+1)*sizeof(char*));
    }
}
fclose(File);
tape=(int*)malloc(sizeof(int));
tape[l]=0;
commands(a, 0, N);
for(i=0; i < N; i++) free(a[N]);
free(a);
printf("\n Tape : ");
for(i=0; i<size; i++)
    printf("  %d", tape[i]);
return 0;
}

char *space(char* c, char* a){
int i, j;
j = 0;
a = (char*)malloc(sizeof(char)*6);
for (i=0; c[i]; i++){
    if (c[i]!=' ' && c[i]!='\n'){
        a[j]=c[i];
        j++;
        a=(char*)realloc(a,(j+6)*sizeof(char));
        }
    }
a=(char*)realloc(a, j*sizeof(char));
return a;
}

int commands(char** a, int left, int right) {
int i, temp = 0;
for (i=left; i<right; i++) {
        if (strcmp(a[i], "movl")==0) movl();
        else if (strcmp(a[i], "movr")==0) movr();
        else if (strcmp(a[i], "inc")==0) inc();
        else if (strcmp(a[i], "dec")==0) dec();
        else if (strcmp(a[i], "print")==0) printf("\n%d", tape[l]);
        else if (strcmp(a[i], "get")==0){
            printf("\nEnter symbol:\n");
            scanf ("%hhd", &tape[l]);
            }
        else if (strcmp(a[i], "printc")==0) printf("\n%c", tape[l]);
        else if (strcmp(a[i], "begin")==0) temp=i+1;
        else if (strcmp(a[i], "end")==0) {
            while (tape[l]!=0) commands(a, temp, i);
            }
        else printf("\nERROR");
        if (tape[l]<0 || tape[l]>K) {
                printf ("\nERROR");
                tape[l]=0;
        }
    }

return 0;
}

int movl() {
if (l==0) {
    int i;
    int *temp;
    size++;
    temp = (int*) realloc (tape, sizeof(int)*size);
    if(temp != NULL){
        for (i=size-1; i!=0; i--)
            temp[i]=temp[i-1];
        temp[0] = 0;
        tape = temp;
    }
    else return 1;
    }
    else l--;
return 0;
}

int movr(){
if (l==(size-1)) {
    int *temp;
    size++;
    l++;
    temp=(int*) realloc (tape, sizeof(int) * size);
    if(temp != NULL){
        temp[size-1] = 0;
        tape=temp;
    }
    else
        return 1;
    }
    else l++;
return 0;
}

int inc() {
if(tape[l]<K) tape[l]++;
else tape[l] = 0;
return 0;
}

int dec() {
if(tape[l]>0) tape[l]--;
else tape[l]=K;
return 0;
}




