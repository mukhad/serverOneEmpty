#include "funct.h"

using namespace std;

int main(int argc, char *argv[])
{
    int forkpid=fork();
    if(!forkpid){
        FILE *flog;
        flog = fopen ("server_final.log" , "a");
        if (flog == NULL){ printf ("Error opening file"); return 0;}
        char cmd1[]="Start";
        fprintfTimeToLogFile(flog,cmd1);

        cout << "demonization!!! pid:"<< getpid() << endl;
        for (int i=0;i<argc;i++){
                printf("Argument %d: %s\n",i,argv[i]);
        }
        const int SZ = 32;
        char ip[SZ]={0}, port[SZ]={0}, directory[SZ]={0};
        bool mode;
        getOpt(argc,argv,ip,port,directory,mode);

        cout << "server: " << ip << ":"<< port << "/" << directory << endl;
        fprintf(flog,"server:  %s:%s/%s",ip,port,directory);

        // создаём новый сеанс, чтобы не зависеть от родителя и переходим в корень диска
        setsid();
        chdir("~");

        close(STDIN_FILENO);
        close(STDOUT_FILENO);
        close(STDERR_FILENO);

        //startEvLoop(12345);

        char cmd2[]="End";
        fprintfTimeToLogFile(flog,cmd2);

        fclose (flog);
        //sleep(15);
    }



    int pid = getpid();
    cout << "stop, pid:"<< pid << endl;


    return 0;
}
