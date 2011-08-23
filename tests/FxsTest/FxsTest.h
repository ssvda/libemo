#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <emofxs.h>

using namespace Emo;

#ifndef UNITTEST_NAME
#	define UNITTEST_NAME FxsTest
#endif

class UNITTEST_NAME : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(UNITTEST_NAME);
	CPPUNIT_TEST(testFls<EMO_BEST_FIT_INT(8)>);
	CPPUNIT_TEST(testFls<EMO_BEST_FIT_INT(16)>);
	CPPUNIT_TEST(testFls<EMO_BEST_FIT_INT(32)>);
	CPPUNIT_TEST(testFfs<EMO_BEST_FIT_INT(8)>);
	CPPUNIT_TEST(testFfs<EMO_BEST_FIT_INT(16)>);
	CPPUNIT_TEST(testFfs<EMO_BEST_FIT_INT(32)>);

#ifdef EMO_64BIT
	CPPUNIT_TEST(testFls<EMO_BEST_FIT_INT(64)>);
	CPPUNIT_TEST(testFfs<EMO_BEST_FIT_INT(64)>);
#endif

	CPPUNIT_TEST_SUITE_END();
public:

	template <typename BaseType>
	void testFls()
	{
		CPPUNIT_ASSERT(emoFls<BaseType>(0) ==-1);

		CPPUNIT_ASSERT(emoFls<BaseType>(3) == 1);
		CPPUNIT_ASSERT(emoFls<BaseType>(6) == 2);
		CPPUNIT_ASSERT(emoFls<BaseType>(10) == 3);

		CPPUNIT_ASSERT(emoFls<BaseType>(0x81) == 7);
		CPPUNIT_ASSERT(emoFls<BaseType>(0xFF) == 7);

		for(int i=1; i<EMO_BITS_IN_TYPE(BaseType); ++i)
		{
			CPPUNIT_ASSERT(emoFls<BaseType>(BaseType(1) << i) == i);
			CPPUNIT_ASSERT(emoFls<BaseType>((BaseType(1) << i) | 1)  == i);
		}
	}

	template <typename BaseType>
	void testFfs()
	{
		CPPUNIT_ASSERT(emoFfs<BaseType>(0) ==-1);

		CPPUNIT_ASSERT(emoFfs<BaseType>(3) == 0);
		CPPUNIT_ASSERT(emoFfs<BaseType>(6) == 1);
		CPPUNIT_ASSERT(emoFfs<BaseType>(10) == 1);

		CPPUNIT_ASSERT(emoFfs<BaseType>(0x81) == 0);
		CPPUNIT_ASSERT(emoFfs<BaseType>(0xFF) == 0);

		for(int i=1; i<EMO_BITS_IN_TYPE(BaseType); ++i)
		{
			CPPUNIT_ASSERT(emoFfs<BaseType>(BaseType(1) << i) == i);
			CPPUNIT_ASSERT(emoFfs<BaseType>((BaseType(1) << i) | 1) == 0);
		}
	}
};

static CPPUNIT_NS::AutoRegisterSuite<UNITTEST_NAME> CPPUNIT_JOIN(test,UNITTEST_NAME);

#undef UNITTEST_NAME
