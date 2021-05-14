#include <iostream>
#include <Wal.hpp>

int main()
{
	WAL::WAL wal;

	try {
		wal.run();
		return 0;
	} catch (const std::exception &ex) {
		std::cerr << ex.what() << std::endl;
		return 84;
	}
}
