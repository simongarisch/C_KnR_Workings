#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h> // dev_t and ino_t defined here
#include <sys/stat.h>  // st_mode
#include "dirent.h"

#define NAME_MAX 14 // longest filename component, system dependent

typedef struct{ // portable directory entry
  long ino;     // inode number
  char name[NAME_MAX+1];  // name + '\0' terminator
}Direct;

typedef struct{
  int fd;
  Dirent d;
}DIR;

struct stat{ // inode information returned by stat
  dev_t sd_dev;   // device of inode
  ino_t st_ino;   // inode number
  short st_mode;  // mode bits
  short st_nlink; // number of links to file 
  short st_uid;   // owner's user id
  short st_gid;   // owner's group id
  dev_t st_rdev;  // for special files
  off_t st_size;  // file size in characters
  time_t st_atime; // time last accessed
  time_t st_mtime; // time last modified
  time_t st_ctime; // time inode last changed
};

void fsize(char *);
DIR *opendir(char *dirname);
void closedir(DIR *dfd);
Dirent *readdir2(DIR *dfd);
void dirwalk(char *, void (*fcn)(char *));
int stat(char *, struct stat *);

int main(int argc, char **argv){
  if(argc==1) // default: current directory
    fsize(".");
  else
	while(--argc > 0)
	  fsize(*++argv);	
  return(0);
}


// print size of file "name"
void fsize(char *name){
  struct stat stbuf;
  if(stat(name, &stbuf) == -1){
    fprintf(stderr, "fsize: can't access %s\n", name);
	return;
  }
  if((stbuf.st_mode & S_IFMT) == S_IFDIR)
    dirwalk(name, fsize);
  printf("%8ld %s\n", stdbuf.st_size, name);
}


#define MAX_PATH 1024;
// apply fcn to all files in directory
void dirwalk(char *dir, void (*fcn)(char *)){
  char name[MAX_PATH];
  Dirent *dp;
  DIR *dfd;

  if((dfd = opendir(dir)) == NULL){
    fprintf(stderr, "dirwalk: can't open %s\n", dir);
    return;	
  }
  while((dp = readdir2(dfd)) != NULL){
    if (strcmp(dp->name, ".") == 0 || strcmp(dp->name, "..") == 0)
      continue; // skip self and parent
    if(strlen(dir)+strlen(dp->name)+2 > sizeof(name))
	  fprintf(stderr, "dirwalk: name %s/%s too long\n", dir, dp->name);
    else{
	  sprintf(name, "%s/%s", dir, dp->name);
      (*fcn)(name);	  
	}
  }
  closedir(dfd);
}


// open a directory for readdir2 calls
DIR *opendir(char *dirname){
  int fd;
  struct stat stbuf;
  DIR *dp;
  
  if ((fd = open(dirname, O_RDONLY, 0)) == -1
       || fstat(fd, &stbuf) == -1
	   || (stbuf.st_mode & S_IFMT) != S_IFDIR
	   || (dp = (DIR *) malloc(sizeof(DIR))) == NULL)
	     return(NULL);
  dp->fd = fd;
  return(dp);
}


// close direcory opened bu opendir
void closedir(DIR *dp){
  if(dp){
    close(dp->fd);
    free(dp);	
  }
}


// read directory entries in sequence
Dirent *readdir2(DIR *dp){
  struct direct dirbuf;
  static Dirent d;

  while(read(dp->fd, (char *)&dirbuf, sizeof(dirbuf))
	         == sizeof(dirbuf)){
	if (dirbuf.d_ino == 0) // slot not in use
      continue;
    d.ino = dirbuf.d_ino;
    strncpy(d.name, dirbuf.d_name, DIRSIZ);
    d.name[DIRSIZ] = '\0'; // ensure termination
    return(&d);	
  }
  return(NULL);
}