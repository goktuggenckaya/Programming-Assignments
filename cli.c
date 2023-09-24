#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <fcntl.h>
#include <sys/wait.h>


int main(int argc, char * argv[]){
    int arrcmd[200];
    int imm=0;
    FILE *ptr;
    ptr = fopen("command2.txt","rb");
    if (ptr==NULL){
        printf("not working bravo");
    }
    char line[100];
    const char s[2] = " ";
    char *token;
    const char dashh = '-';
    const char greatero = '>';
    const char smalleri = '<';
    const char andop = '&';
    while (fgets(line,sizeof(line),ptr)){
        char *cmd_name;
        char *input= NULL;
        char *option= NULL;
        char *outfile= NULL;
        char *inpfile= NULL;
        char *symbol= NULL;
        bool isfirst = true;
        bool issecond = false;
        bool isinputfile = false;
        bool isoutputfile = false;
        bool noinp= false;
        line[strcspn(line, "\n")] = 0;
        token = strtok(line,s);
        while (token!=NULL){;
            if (isinputfile){
                inpfile= token;
                isinputfile=false;
                noinp=true;
            }
            if(isoutputfile){
                outfile = token;
                isoutputfile = false;
                noinp=true;
            }

            if (issecond == true){
                char *optret;
                char *inpret;
                char *outret;
                char *andret;
                optret= strchr(token, dashh);
                inpret= strchr(token, smalleri);
                outret= strchr(token, greatero);
                andret= strchr(token, andop);
                if(optret!=NULL){
                    option = token;
                }
                else if(inpret!=NULL){
                    isinputfile = true;
                }
                else if(outret!=NULL){
                    isoutputfile = true;
                }
                else if(andret!=NULL){
                    symbol= token;
                }
                else if(noinp==false){
                    input = token;
                }
            }
            if (isfirst==true){
                cmd_name = token;
                isfirst = false;
                issecond = true;
            }
            
            token = strtok(NULL,s);
        }
        printf("----------\n");
        printf("Command: %s\n", cmd_name);
        (input !=NULL) ? printf("Inputs: %s\n",input) : printf("Inputs:\n");
        (option !=NULL) ? printf("Options: %s\n",option) : printf("Options:\n");
        if (outfile!= NULL){
            printf("Redirection: >\n");
        } else if (inpfile != NULL) {
            printf("Redirection: <\n");
        } else{
            printf("Redirection: -\n");
        }
        (symbol !=NULL) ? printf("Background Job: y\n") : printf("Background Job: n\n");
        printf("----------\n");
        fflush(stdout);
        if (!((cmd_name[0]== 'w') && (cmd_name[1] == 'a'))){
            int rc = fork();
            if (rc<0){
             exit(1);
            }else if(rc==0){
                if(symbol != NULL){
                    arrcmd[imm]= (int)getpid();
                    imm++;
                }
                if (outfile != NULL){
                    close(STDOUT_FILENO);
                    open(outfile, O_CREAT|O_WRONLY|O_TRUNC, S_IRWXU);
                }
                if (inpfile != NULL){
                    int fd0 = open(inpfile, O_RDONLY, 0);
                    dup2(fd0, STDIN_FILENO);
                    close(fd0);
                }
                int i =0;
                char *myargs[10];
                myargs[i]= strdup(cmd_name);
                i++;
                if (input !=NULL) {
                    myargs[i]= strdup(input);
                    i++;
                }
               if (option !=NULL) {
                    myargs[i]= strdup(option);
                    i++;
                }
                myargs[i]=NULL;
                execvp(myargs[0], myargs);
            }else{
                if(symbol ==NULL){
                    int rc_wait = wait(NULL);
               }
            }
        } else{
            int is= 0;
            while (is<imm) {
                waitpid(arrcmd[is], NULL, 0);
                is++;
            }
        }

    }
    fclose(ptr);
    return 0;
}