#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void leaf(){
    char filename[20];
    sprintf(filename,"%d.txt",getpid());
    FILE *fp=fopen(filename,"w");
    srand(getpid());
    fprintf(fp, "%d\n",(rand()%100));
    fclose(fp);
}
void parent(int pid1,int pid2){
    wait(NULL);

	//some code will add...
	char filename1[20];
    sprintf(filename1,"%d.txt",pid1);
    char filename2[20];
    sprintf(filename2,"%d.txt",pid2);
    char filename3[20];
    sprintf(filename3,"%d.txt",getpid());
    FILE *fp1,*fp2,*fp3;
    fp1=fopen(filename1,"r");
    fp2=fopen(filename2,"r");
    int left,right;
    fscanf(fp1,"%d",&left);
    fscanf(fp2,"%d",&right);
    fclose(fp1);
    fclose(fp2);
    fp3=fopen(filename3,"w");
    fprintf(fp3, "%d",left+right);
    fclose(fp3);
}
void tree_creation(int height);

int main(){
	tree_creation(3);
}

void tree_creation(int height) {
    if (height == 0) {
        leaf();
        return;
    }
    pid_t pid = fork();
    if (pid < 0) {
        perror("fork failed");
        exit(EXIT_FAILURE);
    }
    if (pid > 0) { // Parent
        int pid2 = fork();
        if (pid2 < 0) {
            perror("fork failed");
            exit(EXIT_FAILURE);
        }
        if (pid2 > 0) {
            wait(NULL); 
            printf("Parent: %d, Child1: %d, Child2: %d\n", getpid(), pid, pid2);
            parent(pid, pid2);
        } else {
            tree_creation(--height);
        }
    } else { // Child
        tree_creation(--height);
    }
}
