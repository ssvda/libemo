#include <cppunit/ui/text/TestRunner.h>

#include "UnitTests.generated.h"

int main()
{
	CppUnit::TextUi::TestRunner runner;
	CppUnit::TestFactoryRegistry &registry = CppUnit::TestFactoryRegistry::getRegistry();
	runner.addTest(registry.makeTest());
	if(runner.run())
		return 0;
	else
		return 1;
}
