#include <iostream>
#include "CustomMap.h"

#include "macros.h"
#include <time.h>
#include <random>

//#include "CustomNode.cpp"
using namespace std;


int main() {
	// info("Hello");

	CustomMap<int, int>mp(1,1);
	info("false: %d", false);
	info("Empty? %d", mp.isempty());

	mp.insert(3, 5);
	info("Size: %d", mp.size());
	info("Find [%d] : %d",1,mp.find(1));
	info("Find [%d] : %d", 3, mp.find(3));
	srand(time(NULL));
	int key,value;
	int MAX = 10000;
	for (int i = 0; i < MAX; i++) {
		key = rand() % MAX;
		value = rand() % MAX;
		info("[%d]=%d", key, value);
		mp.insert(key,value);
	}
	mp[104] = 104;
	info("mp[5] = %d",mp.find(5));
	info("Size: %d", mp.size());

	return 0;
}