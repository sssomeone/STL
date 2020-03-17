#include<iostream>
#include<vector>
#include<list>

using namespace std;

template<class T>
void add(T &a) {
	T b=100;
	++b;

}
int main() {
	const int a = 10;
	add(a);
	return 0;
}