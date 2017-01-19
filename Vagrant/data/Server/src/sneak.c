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

  // Error controller
  bzero(buffer, 256);

  // Read
  i = read(newsockfd, buffer, 255);
  printf("%s\n", buffer);

  // Close the connection
  close(newsockfd);
  close(sockfd);
}
