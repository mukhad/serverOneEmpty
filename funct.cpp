#include <netinet/in.h>
#include <ev.h>
#include <pthread.h>

#include "funct.h"
using namespace std;

//struct ev_loop *loop;
//int ClientSocket=0;
int fd;
char buffer[2048];
ssize_t buf_size;

/*

void *runThread(void *value){


    send(fd,buffer,buf_size,MSG_NOSIGNAL);

    cout << fd << " " << buffer << endl;


    return NULL;
}*/

string getAnser(char *buf){

    /*404*/
    if (!start_demon) cout << "patch1:\n" << buf <<endl;
    string res;
    string msg(buf);


    string body404 = "<html><body><h1>404 NOT FOUND</h1></body><html>\n";
    ostringstream sslen;
    sslen << body404.length();


    res=  "HTTP/1.0 404 NOT FOUND\r\nContent-length: ";
    res+= sslen.str();
    res+= "\r\nContent-Type: text/html\r\nConnection: close\r\n\r\n";
    res+= body404;

    size_t pos=msg.find(' ',0);

    if(pos>0 && "GET"==msg.substr(0,pos))
    {
        /*определяем метод*/
        size_t posf=msg.find(' ',pos+1);/*определяем запрашиваемый файл*/
        std::string path=msg.substr(pos+1+1,posf-pos-1-1);
        pos=path.find('?',0);

        if(pos!=-1)
            path=path.substr(0,path.find('?',0));//отрежем все параметры, т.к. не обрабатываются они

        /*проверяем наличие файла*/
        if(path.length() && path[path.length()-1]!='/'){
            FILE * file=fopen(path.c_str(),"r");
            if(file!=NULL){
               int n,len=0;
               string res_file;

               while ((n = fgetc(file)) != EOF) {
                   res_file+=(char)n;
                   ++len;
               }
               fclose(file);

               ostringstream sslen;
               sslen << len;

            /*200*/
            res= "HTTP/1.0 200 OK\r\nContent-length: ";
            res+=  sslen.str();
            res+="\r\nConnection: close\r\nContent-Type: text/html\r\n\r\n";

            res+=res_file;
            }
        }
    }
    return res;
}




void read_callback(struct ev_loop *loop, struct ev_io *watcher,int revents){

    char buffer[2048];

    ssize_t r=recv(watcher->fd,buffer,2048,MSG_NOSIGNAL);

    if (!start_demon) cout << "read(" << r << "):\n" << buffer <<"\n=========="<< endl;

    if (r<0){
        return; //error
    }else if(r==0){
        ev_io_stop(loop,watcher); //exit on empty string
        //
        ev_unloop(loop,EVUNLOOP_ALL);
        free(watcher);
        cout << "quit" << endl;
        return;
    }else{
        //send(watcher->fd,buffer,r,MSG_NOSIGNAL);
        string ans = getAnser(buffer);
        //ans = "hello";
        send(watcher->fd,ans.c_str(),ans.length(),MSG_NOSIGNAL);
        if (!start_demon) cout << "ans:\n" << ans << "\n=========="<< endl;
    }
}

void accept_callback(struct ev_loop *loop, struct ev_io *watcher,int revents){

       if (!start_demon) cout << "accept" << endl;

       int ClientSocket = accept(watcher->fd,0,0);
       struct ev_io *w_client = (struct ev_io*)malloc(sizeof(struct ev_io));
       ev_io_init(w_client,read_callback,ClientSocket,EV_READ);
       ev_io_start(loop,w_client);


}

int startEvLoop(int sport,char *dir){

    int MasterSocket = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    if (!start_demon) cout << "mastersocket: " << MasterSocket << ":" << sport << endl;

    struct sockaddr_in addr;
    bzero(&addr, sizeof(addr));
    addr.sin_family= AF_INET;
    addr.sin_port = htons(sport);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);

    int r = bind(MasterSocket,(struct sockaddr*)&addr,sizeof(addr));
    cout << "bind(): " << r << endl;

    r = listen(MasterSocket,SOMAXCONN);
    cout << "listen(): " << r << endl;

    struct ev_loop *loop = ev_default_loop(0);

    struct ev_io w_accept;
    ev_io_init(&w_accept,accept_callback,MasterSocket,EV_READ);
    ev_io_start(loop,&w_accept);

    while(1)
        ev_loop(loop,0);

    return 0;
}

int getOpt(int argc, char *argv[],char *ip, char *port, char *directory, bool &mode ){

    int rez = 0;
    while ( (rez = getopt(argc,argv,"h:p:d:t")) != -1){
        switch (rez){
            case 'h': strncpy(ip, optarg, MAX_ARG);break;
            case 'p': strncpy(port, optarg, MAX_ARG); break;
            case 'd': strncpy(directory, optarg, MAX_ARG); break;
            case 't': mode = false; break;
        }
        //cout << optarg << endl;
    }
    return 0;
}
int fprintfTimeToLogFile(FILE *f, char* cmd){
    time_t rawtime;
    struct tm * timeinfo;
    time (&rawtime);
    timeinfo = localtime (&rawtime);
    fprintf (f,"\t%s\tTime: %s\n", cmd, asctime(timeinfo));
    return 0;
}
