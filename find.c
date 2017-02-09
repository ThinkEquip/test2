#include <stdio.h>  
#include <stdlib.h>  
#include <dirent.h>  
#include <string.h>  
#include <sys/stat.h>  
#include <errno.h>       //for errno  
#include <fcntl.h> 

void readdir_fun(char *path,int classlevel);

int main(int argc, char **argv)
{
	char *pathvar;  
  
        pathvar = getenv( "HOME" );  //��ȡ��������HOME·��  
        if( pathvar != NULL )  
        {  
            printf("Home path variable is: %s\n",pathvar);  
        }  
        readdir_fun("/data/ccos",0);  
        return 0;  
	
}

void readdir_fun(char *path,int classlevel)  
{  
        DIR *dirp;//��Ŀ¼  
        char longpath[128];  
        struct dirent *dp;  
        struct stat buff;  
  
        if((dirp=opendir(path)) == NULL){
		    exit(-1);  	
		}
  
        while((dp=readdir(dirp))!=NULL)//һ��  
        {  
                if (dp->d_name[0]=='.')  
                        continue;  
                memset(longpath,'\0',sizeof(longpath));  
          /*strncpy(longpath,path,strlen(path));  
                strncat(longpath,"/",1);  
                strncat(longpath,dp->d_name,strlen(dp->d_name));*/  
                sprintf(longpath,"%s/%s",path,dp->d_name);  
                if (lstat(longpath,&buff)<0)  
                {  
                        printf("Error lstat %s,errno code is %d,err message is '%s'\n",dp->d_name,errno,strerror(errno));  
                        continue;  
                }  
                if (S_ISREG(buff.st_mode)){  
                        printf("��%d��Ŀ¼�ṹ��:%s, \n",classlevel,dp->d_name);  
                        continue;  
                        }  
                if (S_ISDIR(buff.st_mode))  
                {  
                                if (classlevel > 0 )  
                                        {  
                                                int i;  
                                                for(i=0; i<classlevel; i++){  
                                                                //      printf("   ");  
                                                        }  
                                        }  
                                printf("��%d��Ŀ¼�ṹ��%s,�ļ�������%d,�ļ�������%d,�ļ�ƫ����%d  \n",classlevel,dp->d_name,dp->d_type,dp->d_ino,dp->d_off);  
                                ++classlevel;  
                        readdir_fun(longpath,classlevel);  
                        --classlevel;  
                        usleep(100);  
                 }  
        }  
        closedir(dirp);  
}  