#include <iostream>
#include "CustomMap.h"

using namespace std;

#ifndef MACROS
#define MACROS
#define info(msg, ...)(printf("[i] "msg"\n", ##__VA_ARGS__))
#define success(msg, ...)(printf("[+] "msg"\n", ##__VA_ARGS__))
#define error(msg, ...)(printf("[-] "msg"\n", ##__VA_ARGS__))
#endif

int main() {
	info("Hello!");
}