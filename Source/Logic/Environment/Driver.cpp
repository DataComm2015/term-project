#include "EnemyHierarchy.h"

using std::cout;
using std::cerr;
using std::endl;
using std::runtime_error;
using std::logic_error;


int main(void)
{
	try
	{
		EnemyHierarchy *eh = EnemyHierarchy::getInstance();
	}
	catch (logic_error &e)
	{
		cerr << e.what() << endl;
		return 1;
	}
	catch (runtime_error &e)
	{
		cerr << e.what() << endl;
	}

	return 0;
}