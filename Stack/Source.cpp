#include <iostream>
#include <functional>
#include "stack.h"
#include <chrono>
#include <ctime>   
#include <fstream>
#include <vector>



int main(void)
{
	//Hanh::StackUsingLinkedList<int> stack;
	//std::vector<int> L = { 1000, 10000, 20000, 30000, 40000, 100000, 50000, 70000, 80000, 90000 };
	std::vector<int> L = { 1000 };

	std::ofstream copy("copy.txt", std::ios::app);
	std::ofstream push("push.txt", std::ios::app);
	std::ofstream pop("pop.txt", std::ios::app);
	for (int i = 0; i < L.size(); i++) {
		Hanh::StackUsingLinkedList<int> stack;
		//Hanh::Stack<int> stack;
		// push
		auto start = std::chrono::system_clock::now();
		for (int j = 0; j < L[i]; j++)
			stack.Push(j);
		auto end = std::chrono::system_clock::now();

		std::chrono::duration<double> elapsed_seconds2 = end - start;
		push << L[i] << " " << elapsed_seconds2.count() << std::endl;
		//copy
		auto start1 = std::chrono::system_clock::now();
		Hanh::StackUsingLinkedList<int> stackcopy(stack);
		//Hanh::Stack<int> stackcopy(stack);
		//std::cout << stack.top_() << " " << stackcopy.top_();
		auto end1 = std::chrono::system_clock::now();
		std::chrono::duration<double> elapsed_seconds21 = end1 - start1;
		copy << L[i] << " " << elapsed_seconds21.count() << std::endl;

		//pop
		auto start2 = std::chrono::system_clock::now();
		//for (int j = 0; j < L[i]; j++)
			stack.Pop();
		auto end2 = std::chrono::system_clock::now();
		std::chrono::duration<double> elapsed_seconds22 = end2 - start2;
		pop << L[i] << " " << elapsed_seconds22.count() << std::endl;
	}
	copy.close();
	system("pause");
	return 0;
}