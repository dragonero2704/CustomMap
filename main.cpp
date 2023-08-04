#include <iostream>
#include "CustomMap.h"
#include <stdio.h>
using namespace std;

#ifndef MACROS
#define MACROS
#define info(msg, ...) printf("[i] "msg, ##__VA_ARGS__)
#define success(msg, ...) printf("[+] "msg, ##__VA_ARGS__)
#define error(msg, ...) printf("[-] "msg, ##__VA_ARGS__)
#endif

int main() {
	info("Hello");
}