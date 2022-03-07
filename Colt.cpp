#include <iostream>
using namespace std;


void OneTick() {
    ticks += 1;
}

int main() {
    while(true) {
        OneTick();
    }
	return 0;
}