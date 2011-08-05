#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#define UNITTEST_NAME EmptyCppUnitTestMyTest

class UNITTEST_NAME : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(UNITTEST_NAME);
	CPPUNIT_TEST(emptyTest);
	CPPUNIT_TEST_SUITE_END();
public:

	void setUp()
	{
	   // инициализация
	}

	void tearDown()
	{
	   // деинициализация
	}

	void emptyTest()
	{
	   CPPUNIT_ASSERT(true);
	}
};

static CPPUNIT_NS::AutoRegisterSuite<UNITTEST_NAME> CPPUNIT_JOIN(test,UNITTEST_NAME);

#undef UNITTEST_NAME
