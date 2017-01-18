#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <sys/inotify.h>
#include <limits.h>

#define BUF_LEN (10 * (sizeof(struct inotify_event) + NAME_MAX + 1))

void showEvent(struct inotify_event *e) {
  switch(e->mask){
    case IN_ACCESS:
      syslog(LOG_NOTICE, "IN_ACCESS");
      break;

	  case IN_ATTRIB:
      syslog(LOG_NOTICE, "IN_ATTRIB");
      break;

    case IN_CLOSE_WRITE:
      syslog(LOG_NOTICE, "IN_CLOSE_WRITE");
      break;

    case IN_CLOSE_NOWRITE:
      syslog(LOG_NOTICE, "IN_CLOSE_NOWRITE");
      break;

    case IN_CREATE:
      syslog(LOG_NOTICE, "IN_CREATE");
      break;

    case IN_DELETE:
      syslog(LOG_NOTICE, "IN_DELETE");
      break;

    case IN_DELETE_SELF:
      syslog(LOG_NOTICE, "IN_DELETE_SELF");
      break;

    case IN_MODIFY:
      syslog(LOG_NOTICE, "IN_MODIFY");
      break;

    case IN_MOVE_SELF:
      syslog(LOG_NOTICE, "IN_MOVE_SELF");
      break;

    case IN_MOVED_FROM:
      syslog(LOG_NOTICE, "IN_MOVE_FROM");
      break;

    case IN_MOVED_TO:
      syslog(LOG_NOTICE, "IN_MOVE_TO");
      break;

    case IN_OPEN:
      syslog(LOG_NOTICE, "IN_OPEN");
      break;

    case IN_ALL_EVENTS:
      syslog(LOG_NOTICE, "IN_ALL_EVENTS");
      break;

    case IN_MOVE:
      syslog(LOG_NOTICE, "IN_MOVE");
      break;

    case IN_CLOSE:
      syslog(LOG_NOTICE, "IN_CLOSE");
      break;

    case IN_DONT_FOLLOW:
      syslog(LOG_NOTICE, "IN_DONT_FOLLOW");
      break;

    case IN_MASK_ADD:
      syslog(LOG_NOTICE, "IN_MASK_ADD");
      break;

    case IN_ONESHOT:
      syslog(LOG_NOTICE, "IN_ONESHOT");
      break;

    case IN_ONLYDIR:
      syslog(LOG_NOTICE, "IN_ONLYDIR");
      break;

    case IN_IGNORED:
      syslog(LOG_NOTICE, "IN_IGNORED");
      break;

    case IN_ISDIR:
      syslog(LOG_NOTICE, "IN_ISDR");
      break;

    case IN_Q_OVERFLOW:
      syslog(LOG_NOTICE, "IN_Q_OVERFLOW");
      break;

    case IN_UNMOUNT:
      syslog(LOG_NOTICE, "IN_UNMOUNT");
      break;
  }
}

inotify(int argc, char *argv[]){
  int fd, wd, i;
  char buf[BUF_LEN];
  size_t num;
  char *e;
  struct inotify_event *event;

  fd = inotify_init();

  // Error
  if (fd == -1) {
    syslog(LOG_NOTICE, "Error: fd");
    return 0;
  }

  for (i=1; i<argc; i++) {
    wd = inotify_add_watch(fd, argv[i], IN_ALL_EVENTS);
    // Error
    if (wd == -1) {
      syslog(LOG_NOTICE, "Error: wd");
      return 0;
    }
  }

  while (1) {
    num = read(fd, buf, BUF_LEN);
    // Error
    if (num == -1) {
      syslog(LOG_NOTICE, "Error: num");
      return 0;
    }

    for (e=buf; e<buf+num; ) {
      event = (struct inotify_event *)e;
      showEvent(event);
      e += sizeof(struct inotify_event) + event->len;
    }
  }
}

int daemonInotify(int argc, char *argv[]) {
   /* Our process ID and Session ID */
   pid_t pid, sid;

   /* Fork off the parent process */
   pid = fork();
   if (pid < 0) {
      exit(EXIT_FAILURE);
   }

   /* If we got a good PID, then
      we can exit the parent process. */
   if (pid > 0) {
      exit(EXIT_SUCCESS);
   }

   /* Change the file mode mask */
   umask(0);

   /* Open any logs here */

   /* Create a new SID for the child process */
   sid = setsid();

   if (sid < 0) {
      /* Log the failure */
      exit(EXIT_FAILURE);
   }

   /* Change the current working directory */
   if ((chdir("/")) < 0) {
      /* Log the failure */
      exit(EXIT_FAILURE);
   }

   /* Close out the standard file descriptors */
   close(STDIN_FILENO);
   close(STDOUT_FILENO);
   close(STDERR_FILENO);

   /* Daemon-specific initialization goes here */

   /* Funcionality */
   inotify(argc, argv);

   exit(EXIT_SUCCESS);
}
