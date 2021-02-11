#include <stdlib.h> // EXIT_SUCCESS
#include <stdio.h>  // printf
#include <string.h>
#include <sys/types.h> // pid_t
#include <unistd.h>    // fork
#include <sys/wait.h>  // wait
#include <stdio_ext.h> //fpurge



int main(int argc, char * argv[]) {
    // cannot fail always have a name :slight_smile:
    //const char * prog_name = argv[0];


    printf("**************MiniShell***************");
    char str[25];

    int i=0;
    int k=0;
    while (i<99) {
        printf("\nsaisir :");
        //demande a l'ulilisateur a tapez la cammandes
        fgets(str, sizeof(str), stdin);
        //pour les flux de sortie
        fpurge(stdin);

        //mettre une fin a la cammande saisie 
        for (k=0; k<strlen(str); k++) {
            if (str[k] == '\n') {
                str[k]='\0';
            }
        }

         //enregistrer le historique
        FILE *historique;
        historique=fopen("historique.txt","a");
        fprintf(historique,"\n %s",str);
        fclose(historique);


        
        char * tab[15];
        int j=0;
        int nbr_arg=0;
        char *test;
        int len = strlen(str);
        char d[] = " ";
        char *p = strtok(str, d);
        while(p != NULL)
          {
              //stocker les cammandes saisie dans un tableau 
              tab[j]=p;
              p = strtok(NULL, d);
              j++;

          }
        nbr_arg=j;

        char *cmd= tab[0];
        printf("");
        printf("");

        int i;
    
                for (i=0; i<=j; i++) {
                    if (i==j) {
                        tab[i] = NULL;
                    }
                }
        char *arg[j-1];
        for (i=1; i<=j; i++) {
            arg[i-1]=tab[i];
        }
    pid_t pid = fork();
    if (pid > 0) {
        int status = 0;
        wait(&status);
    } 
    else if (pid == 0) {
      if (nbr_arg==1) {
        arg[0] = "-l";
        arg[1] = NULL;
      }

        execvp(cmd, arg);


    } else {
        perror("fork failed !\n");
        return EXIT_FAILURE;
    }


    }
}
