#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/inotify.h>

#define EVENT_SIZE  ( sizeof (struct inotify_event) )
#define EVENT_BUF_LEN     ( 1024 * ( EVENT_SIZE + 16 ) )

int main(int argc, char **argv)
{

  int length, i = 0;
  int fd;
  int wd;
  char buffer[EVENT_BUF_LEN];

 if(argc != 2){
     perror("usage : ./filewatcher [the path of the directory to watch] \n");
     exit(1);
 }
  /*creating the INOTIFY instance*/
  fd = inotify_init();

  /*checking for error*/
  if ( fd < 0 ) {
    perror( "inotify_init" );
    exit(1);
  }

  /*adding the “/tmp” directory into watch list. Here, the suggestion is to validate the existence of the directory before adding into monitoring list.*/
  wd = inotify_add_watch( fd, argv[1], IN_CREATE | IN_DELETE | IN_MODIFY);

    printf("path to the dir to read: %s. \n", argv[1]);
  /*read to determine the event change happens on the directory. Actually this read blocks until the change event occurs*/ 

    // printf(" before reading \n");
  length = read( fd, buffer, EVENT_BUF_LEN ); 
    printf("length : %d\n", length);
  /*checking for error*/
  if ( length < 0 ) {
    perror( "read" );
  }  

  /*actually read return the list of change events happens. Here, read the change event one by one and process it accordingly.*/
  while ( i < length ) {    

    struct inotify_event *event = ( struct inotify_event *)&buffer[i]; 

    if ( event->len ) {

        printf(" event length :  %d \n", event->len);
      if ( event->mask & IN_CREATE ) {
    
          printf( "New file %s created.\n", event->name );
        
      }
      else if ( event->mask & IN_DELETE ) {
       
          printf( "File %s deleted.\n", event->name );
    
      }
      else if(event->mask & IN_MODIFY){
          printf("File %s modified. \n", event->name);
      }

    }
    i += EVENT_SIZE + event->len;
  }
  /*removing the “/tmp” directory from the watch list.*/
   inotify_rm_watch( fd, wd );

  /*closing the INOTIFY instance*/
   close( fd );

}