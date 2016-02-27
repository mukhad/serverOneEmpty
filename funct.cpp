#include <stdio.h>
#include <netinet/in.h>
#include <ev.h>

#include "funct.h"
using namespace std;

void read_callback(struct ev_loop *loop, struct ev_io *watcher,int revents){

    char buffer[2048];

    ssize_t r=recv(watcher->fd,buffer,2048,MSG_NOSIGNAL);

    cout << "read:" << r << endl;

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
        send(watcher->fd,buffer,r,MSG_NOSIGNAL);

    }
}

void accept_callback(struct ev_loop *loop, struct ev_io *watcher,int revents){

    int ClientSocket = accept(watcher->fd,0,0);

    struct ev_io *w_client = (struct ev_io*)malloc(sizeof(struct ev_io));

    ev_io_init(w_client,read_callback,ClientSocket,EV_READ);
    ev_io_start(loop,w_client);

    cout << "accept" << endl;
}

int startEvLoop(int sport){

    struct ev_loop *loop = ev_default_loop(0);
    int MasterSocket = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    cout << "mastersocket: " << MasterSocket << ":" << sport << endl;

    struct sockaddr_in addr;
    bzero(&addr, sizeof(addr));
    addr.sin_family= AF_INET;
    addr.sin_port = htons(sport);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);

    int r = bind(MasterSocket,(struct sockaddr*)&addr,sizeof(addr));
    cout << "bind(): " << r << endl;

    r = listen(MasterSocket,SOMAXCONN);
    cout << "listen(): " << r << endl;

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
    fprintf (f,"\n\t%s\tTime: %s", cmd, asctime(timeinfo));
    return 0;
}
