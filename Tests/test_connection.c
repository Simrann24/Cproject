void test_connectRemoteServer() {
    int port_num = 80; 
    int remoteSocketID = connectRemoteServer("example.com", port_num);
    assert(remoteSocketID >= 0);
    close(remoteSocketID);

}


void test_handle_request() {
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
 
    ParsedRequest *request = ParsedRequest_create();
    request->host = "example.com";
    request->path = "/";
    request->version = "HTTP/1.1";
    request->port = "80";
    char *tempReq = strdup("GET / HTTP/1.1\r\nHost: example.com\r\n\r\n");

    int result = handle_request(clientSocket, request, tempReq);
    assert(result == 0); 

    ParsedRequest_destroy(request);
    free(tempReq);
}
