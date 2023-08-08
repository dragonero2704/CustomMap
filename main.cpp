#include <iostream>
#include "CustomMap.h"

#include "macros.h"
#include <time.h>
#include <random>

#include <map>

using namespace std;


int main() {
	// info("Hello");

	CustomMap<int, int>mp(1,1);
	info("false: %d", false);
	info("Empty? %d", mp.isempty());

	mp.insert(3, 5);
	info("Size: %lld", mp.size());
	auto it = mp.find(1);
	if (it == mp.end()) info("Key: %d not found", 1);
	else info("Find [%d] : %d",it->first, it->second);
	mp[1] = 1;
	it = mp.find(1);
	info("Find [%d] : %d", it->first, it->second);

	srand(time(NULL));
	int key,value;
	int MAX = 10;
	for (int i = 0; i < MAX; i++) {
		key = rand() % MAX;
		value = rand() % MAX;
		info("[%d]=%d", key, value);
		mp.insert(key,value);
	}
	mp[104] = 104;
	it = mp.find(104);
	info("mp[%d] = %d",it->first, it->second);
	info("Size: %lld", mp.size());

	info("Stampa tramite iterator");
	for (auto it = mp.begin(); it != mp.end(); it++) {
		cout << it->first<<" "<< it->second << endl;
	}
	info("Size: %lld", mp.size());

	info("Stampa tramite reverse iterator");
	for (auto it = mp.rbegin(); it != mp.rend(); it++) {
		cout << it->first << " " << it->second << endl;
	}

	return 0;
}