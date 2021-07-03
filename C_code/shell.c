/* Name : Bragadeeshan S
E- Number :e16055 
CO327 Lab01 */


#include<stdio.h>
#include<unistd.h>
#include<sys/syscall.h>
#include<sys/wait.h>
#include<string.h>
#include <pthread.h> 

void read_command( char cmd[], char *p[] ){
    char line[100];
    int count=0,i=0,j=0;
    char *array[100],*pch;

    //reading the line
    for(;;){
        int c = fgetc( stdin );
        line[count++] = (char)c;
        if (c == '\n') break ;
    }
    if (count == 1) return;
    pch =strtok (line , "\n");
    //Parcing the line
    while(pch != NULL){
        array[i++] = strdup (pch);
        pch = strtok(NULL,"\n");
    }
    //first word as the command
    strcpy(cmd,array[0]);

    for (int j=0; j<i ;j++){
        p[j] = array[j];
        p[i] = NULL;
    }


}



int main() 
{ 
     printf("### Simple Shell## \n Type 'exit' to close the shell \n");
    char cmd[100],command[100],*parameters[20];
    
    char *env[] = {(char *) "PATH =/bin",0};

    while (1) {
       
        read_command( command,parameters);
        if(fork()!=0){ 
            wait(NULL); //waiting for the child
        }
        else{
            strcpy( cmd , "/bin/");
            strcat( cmd, command);
            execve( cmd, parameters, env);
        }
        if (strcmp(command, "exit") == 0){
            break;
        }
    }

  return 0; 
}
