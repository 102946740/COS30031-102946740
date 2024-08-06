#include <iostream>

void Print(int x, int y) {
	std::cout << "printing values: " << x << " " << y << "\n";
}

void Add(int x) {
	std::cout << x << " + 5 = ";
	x += 5;
	std::cout << x << "\n";
}

void PrintOdd() {
	for (int i = 1; i < 20; i += 2) {
		std::cout << i << " ";
	}
	std::cout << "\n";
}

void PrintRand() {
	int Array[5];
	for (int i = 0; i < 5; i++) {
		Array[i] = rand();
	}
	for (int i : Array) {
		std::cout << i << " ";
	}
	std::cout << "\n";
}

class Benny {
public:
	int age = 22;

	void PrintAge() {
		std::cout << age << " is my age \n";
	}

private:
	std::string name = "Ben";
};


int main() {
	Print(5, 10);
	Add(10);

	int x = 5;

	int* pX = &x; // Pointer to x, int* is pointer to int and &x is the memory address of x
	std::cout << pX << "is a pointer to x :" << x << "\n";

	PrintOdd();
	PrintRand();

	std::string str = "this has spaces in is";
	std::string word = "";
		for (auto x : str)
		{
			if (x == ' ')
			{
				std::cout << word << "\n";
				word = "";
			}
			else {
				word = word + x;
			}
		}
		std::cout << word << "\n";
		Benny Ben;
		Ben.age = 5;
		Ben.PrintAge();
	return 0;
}