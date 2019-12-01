#ifndef STACK
#define STACK
#include <iostream>
#define MAX 10000000
namespace Hanh 
{
	template<class T>
	class StackUsingLinkedList
	{
	private:
		struct Node
		{
			T data;
			Node * link;
			Node() {};
			Node(const T& data) : data(data), link(NULL) {}
		};
		Node *top;
	public:
		StackUsingLinkedList() : top(NULL) {};
		StackUsingLinkedList(const StackUsingLinkedList<T> &s)
		{
			const Node *cpCurrent = s.top;
			Node *lsCurrent = NULL;

			if (cpCurrent != NULL) {
				top = new Node(cpCurrent->data);
				lsCurrent = top;

				cpCurrent = cpCurrent->link;

			}

			while (cpCurrent != NULL) {
				Node *newNode = new Node(cpCurrent->data);
				lsCurrent->link = newNode;

				lsCurrent = lsCurrent->link;
				cpCurrent = cpCurrent->link;
			}
		}

		StackUsingLinkedList(Node *_top)
		{
			top = _top;
		}
		~StackUsingLinkedList() {};

		bool Isempty()
		{
			if (top == NULL)
				return true;
			return false;
		}


		void Push(T value)
		{
			Node *newnode = new Node();
			newnode->data = value;
			newnode->link = top;
			top = newnode;
		}

		void Pop()
		{
			if (Isempty())
			{
				std::cout << "Stack is empty";
			}
			else
			{
				Node *ptr = top;
				top = top->link;
				delete(ptr);
			}
		}

		T top_()
		{
			if (Isempty())
			{
				throw "Stack is empty";
			}
			else
			{
				return top->data;
			}
		}

		StackUsingLinkedList<T>& operator=(const StackUsingLinkedList<T> &a)
		{
			if (&a != this) {
				Node *tmp = top;

				while (tmp->link) {
					top = top->link;
					delete tmp;
					tmp = top;
				}

				tmp = a->top;

				while (tmp) {
					append(tmp);
					tmp = tmp->link;
				}
			}

			return *this;
		}

		
	};

	template<typename T>
	class Stack {
		T top;
		int a[MAX/10]; // Maximum size of Stack 
	public:
		

		Stack() { top = -1; }
		Stack(const Stack& s) {
			top = s.top;
			for (int i = 0; i < top; i++)
			  a[i] = s.a[i];
		}
		~Stack(){}
		bool Push(T x)
		{
			if (top >= (MAX - 1)) {
				return false;
			}
			else {
				a[++top] = x;
				return true;
			}
		};
		T Pop() 
		{
			if (top < 0) {
				return 0;
			}
			else {
				int x = a[top--];
				return x;
			}
		};
		T top_()
		{
			if (top < 0) {
				return 0;
			}
			else {
				int x = a[top];
				return x;
			}
		};
		bool isEmpty()
		{
			return (top < 0);
		};
	};





};
#endif 

