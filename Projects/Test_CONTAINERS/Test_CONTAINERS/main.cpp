#include <myth\containers\dictionary.h>
#include <myth\containers\list.h>

using namespace myth::containers;

#include <iostream>

int main()
{
	List<int> numbers;

	for(int i = 0; i < 50; i++)
		numbers.Add(i);

	std::cout << numbers.Count() << "\n";
	std::cout << numbers.Size() << "\n";

	for(int i = 0; i < 50; i += 4)
		numbers.Remove(i);

	
	std::cout << numbers.Count() << "\n";
	std::cout << numbers.Size() << "\n";


	for(int i = 0; i < 50; i ++)
		std::cout << numbers.Contains(i) << "\n";

	char x;
	std::cin >> x;
}
