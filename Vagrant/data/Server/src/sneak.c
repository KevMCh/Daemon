#include "utils.h"

void sneak(int argc, char *argv[]) {

  int sockfd, newsockfd, portnumber;
  socklen_t clilongitud;
  char buffer[256];
  struct sockaddr_in serv_addr, cli_addr;
  int i;

  // Create the socket
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  bzero((char*)&serv_addr, sizeof(serv_addr));

  // Add the port number
  portnumber = atoi(argv[1]);

  // Server information
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = INADDR_ANY;
  serv_addr.sin_port = htons(portnumber);

  bind(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

  // Listen in the port, maximium five connections
  listen(sockfd, 5);

  clilongitud = sizeof(cli_addr);

  // Accept the connections
  newsockfd = accept(sockfd, (struct sockaddr*)&cli_addr, &clilongitud);

  if(newsockfd < 0){
    syslog(LOG_NOTICE, "Error socket");
  }

  while(1){
    bzero(buffer, 256);
    // Read
    i = read(newsockfd, buffer, 255);

    if(i > 0) {
      syslog(LOG_NOTICE, "%s", buffer);
    } else {
      if(i == 0){
        break;
      } else {
        return;
      }
    }
  }

  // Close the connection
  close(newsockfd);
  close(sockfd);
}

int daemonSneak(int argc, char *argv[]) {
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
   sneak(argc, argv);

   exit(EXIT_SUCCESS);
}
