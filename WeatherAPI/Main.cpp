#include "Weather.h"

int main()
{
	Weather w("", "");
	w.fetch();
	w.printData();

	std::cout << "\nPress enter to continue...";
	std::cin.get();

	return 0;
}