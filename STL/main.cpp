#include<iostream>
#include<vector>
#include"allocator.h"

int main() {
	std::vector<int, mystl::allocator<int>>v;
	for (int i = 0; i < 10; ++i)v.push_back(i);


	return 0;
}