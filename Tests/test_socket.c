void test_socket_connected() {
    int clientSocket = 1; 

    const char *testMsg = "Hello";
    ssize_t sentBytes = send(clientSocket, testMsg, strlen(testMsg), 0);
    assert(sentBytes == strlen(testMsg)); 

    char buffer[256];
    ssize_t receivedBytes = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
    assert(receivedBytes > 0); 
    buffer[receivedBytes] = '\0'; 


    assert(strcmp(buffer, "Expected Response") == 0);
}
