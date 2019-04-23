#include <http_func.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>

extern char *paths[];

int main(int argc,char *argv[]){
	char url[256];
	int opt,threadcount=10;
	
	while((opt = getopt(argc,argv,"hu:t:")) != EOF){
		switch(opt){
			case 'h':
				printf("Usage: eliamenisch-admincp-finder -t threads -u URL\n");
				return 0;
			case 'u':
				memcpy(url,optarg,256);
				break;
            case 't':
                threadcount = atoi(optarg);
                break;
			default:
			case '?':
				fprintf(stderr,"Invalid Option!\n");
				return 1;
		}
	}
	
	argc -= optind;
	argv += optind;
	
	if(!strstr(url,"http")){
		fprintf(stderr,"You must provide exact one URL with -u!\n");
		return 1;
	}
	int cnt = 0, code;
	char *buf = malloc(1024);
	char newurl[512];
    
    pid_t pids[threadcount];
    int pc;
    
	while(paths[cnt] != NULL){
        for(pc = 0;pc != threadcount;pc++){
	    if(paths[cnt] != NULL){
            sprintf(newurl,"%s%s",url,paths[cnt++]);
            pids[pc] = fork();
            if(!pids[pc]){
		        code = http_func(newurl,buf,12,HEAD,NULL);
		        if(code == 200){
			        printf("!!! [Found] !!! -> %s\n",newurl);
                    int c;
                    for(c=0;c!=threadcount;c++){
                        kill(pids[c],SIGKILL);
                    }
		            exit(0);
		        } else {
			        printf("[CHECKED] -> %s\n",newurl);
	        	}
                exit(0);
	        }
             }
            
        }
        for(pc=0;pc != threadcount;pc++){
              wait(NULL);
        }
    }
	free(buf);
	return 0;
}
