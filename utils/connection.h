#include <stdio.h>

int connectRemoteServer(char* host_addr, int port_num);

int handle_request(int clientSocket, ParsedRequest *request, char *tempReq);

int checkHTTPversion(char *msg);


