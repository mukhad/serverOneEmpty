#include <signal.h>
#include <sys/stat.h>

#include "funct.h"


//sudo apt-get install libev-dev
//echo https://github.com/mukhad/serverOneEmpty.git > final.txt

//  ./final -h 127.0.0.1 -p 12345 -d /tst

using namespace std;

static void skeleton_daemon()
{
    pid_t pid;

    /* Fork off the parent process */
    pid = fork();

    /* An error occurred */
    if (pid < 0)
        exit(EXIT_FAILURE);

    /* Success: Let the parent terminate */
    if (pid > 0)
        exit(EXIT_SUCCESS);

    /* On success: The child process becomes session leader */
    if (setsid() < 0)
        exit(EXIT_FAILURE);

    /* Catch, ignore and handle signals */
    //TODO: Implement a working signal handler */
    signal(SIGCHLD, SIG_IGN);
    signal(SIGHUP, SIG_IGN);

    /* Fork off for the second time*/
    pid = fork();

    /* An error occurred */
    if (pid < 0)
        exit(EXIT_FAILURE);

    /* Success: Let the parent terminate */
    if (pid > 0)
        exit(EXIT_SUCCESS);

    /* Set new file permissions */
    umask(0);

    /* Change the working directory to the root directory */
    /* or another appropriated directory */
    chdir("/");

    /* Close all open file descriptors */
    int x;
    for (x = sysconf(_SC_OPEN_MAX); x>0; x--)
    {
        close (x);
    }

}

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

    FILE *flog;
    flog = fopen ("/home/box/server_final.log" , "a");
    if (flog == NULL){ printf ("Error opening file"); return 0;}
    fprintf(flog,"server:  %s:%s/%s\n",ip,port,directory);
    fclose (flog);

    if(start_demon){
         skeleton_daemon();
    }
    else{
        cout << "server: " << ip << ":"<< iport << "/" << directory << endl;
    }

    startEvLoop(iport,directory);


    /*
    int forkpid = 0;
    if(start_demon) forkpid=fork();
    if(!forkpid)
    {
        //FILE *flog;
        //flog = fopen ("server_final.log" , "a");
        //if (flog == NULL){ printf ("Error opening file"); return 0;}
        //char cmd1[]="Start";
        //fprintfTimeToLogFile(flog,cmd1);

        //cout << "demonization!!! pid:"<< getpid() << endl;
        //for (int i=0;i<argc;i++){
        //        printf("Argument %d: %s\n",i,argv[i]);
        //}


        //cout << "server: " << ip << ":"<< iport << "/" << directory << "  mode:" << mode << endl;
        //fprintf(flog,"server:  %s:%s/%s\n",ip,port,directory);

        // создаём новый сеанс, чтобы не зависеть от родителя и переходим в корень диска
        if(start_demon){
            setsid();

            signal(SIGCHLD, SIG_IGN);
            signal(SIGHUP, SIG_IGN);

            umask(0);
            chdir("/");

            // Close all open file descriptors
            //close(STDIN_FILENO);    close(STDOUT_FILENO);    close(STDERR_FILENO);
            for (int x = sysconf(_SC_OPEN_MAX); x>0; x--)   close (x);

        }


        startEvLoop(iport,directory);

        //char cmd2[]="End";
        //fprintfTimeToLogFile(flog,cmd2);

        //fclose (flog);
        //sleep(15);
    }
    */



    //int pid = getpid();
    //cout << "stop, pid:"<< pid << endl;


    return 0;
}
