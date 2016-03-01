#include <signal.h>
#include <sys/stat.h>

#include "funct.h"


//sudo apt-get install libev-dev
//https://github.com/mukhad/serverOneEmpty.git

using namespace std;

int main(int argc, char *argv[])
{
    const int SZ = 32;
    char ip[SZ]={0}, port[SZ]={0}, directory[SZ]={0};
    bool mode = true;
    getOpt(argc,argv,ip,port,directory,mode);
    int iport;
    if(strlen(port)==0)
        iport = 12345;
    else
        iport = atoi(port);

    int forkpid = 0;

    signal(SIGCHLD, SIG_IGN);
    signal(SIGHUP, SIG_IGN);

    if(start_demon) forkpid=fork();
    if(!forkpid)
    {
        FILE *flog;
        flog = fopen ("server_final.log" , "a");
        if (flog == NULL){ printf ("Error opening file"); return 0;}
        char cmd1[]="Start";
        fprintfTimeToLogFile(flog,cmd1);

        cout << "demonization!!! pid:"<< getpid() << endl;
        for (int i=0;i<argc;i++){
                printf("Argument %d: %s\n",i,argv[i]);
        }


        cout << "server: " << ip << ":"<< iport << "/" << directory << "  mode:" << mode << endl;
        fprintf(flog,"server:  %s:%s/%s\n",ip,port,directory);

        // создаём новый сеанс, чтобы не зависеть от родителя и переходим в корень диска
        if(start_demon){
            setsid();
            chdir("/");
            umask(0);
            close(STDIN_FILENO);    close(STDOUT_FILENO);    close(STDERR_FILENO);
        }


        startEvLoop(iport,directory);

        char cmd2[]="End";
        fprintfTimeToLogFile(flog,cmd2);

        fclose (flog);
        //sleep(15);
    }



    int pid = getpid();
    cout << "stop, pid:"<< pid << endl;


    return 0;
}
