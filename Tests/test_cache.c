void test_cache() {
    printf("Testing cache insertion and lookup...\n");

    char* url1 = "http://example.com";
    char* response1 = "Example response";
    add_cache_element(response1, sizeof(response1), url1);

    cache_element* found = find(url1);
    if (found != NULL) {
        printf("Cache hit: URL %s found with data: %s\n", url1, found->data);
    } else {
        printf("Cache miss: URL %s not found\n", url1);
    }

    char* url2 = "http://example2.com";
    cache_element* not_found = find(url2);
    if (not_found == NULL) {
        printf("Cache miss: URL %s not found (expected)\n", url2);
    }
}

