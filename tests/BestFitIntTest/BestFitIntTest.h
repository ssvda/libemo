#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <emobestfitint.h>

using namespace Emo;

#define UNITTEST_NAME BestFitIntTest

class UNITTEST_NAME : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(UNITTEST_NAME);
	CPPUNIT_TEST(testBestFit);
	CPPUNIT_TEST_SUITE_END();
public:

	void testBestFit()
	{
		CPPUNIT_ASSERT( typeid(EMO_BEST_FIT_INT( 1)) == typeid(unsigned char) );
		CPPUNIT_ASSERT( typeid(EMO_BEST_FIT_INT( 2)) == typeid(unsigned char) );
		CPPUNIT_ASSERT( typeid(EMO_BEST_FIT_INT( 3)) == typeid(unsigned char) );
		CPPUNIT_ASSERT( typeid(EMO_BEST_FIT_INT( 4)) == typeid(unsigned char) );
		CPPUNIT_ASSERT( typeid(EMO_BEST_FIT_INT( 5)) == typeid(unsigned char) );
		CPPUNIT_ASSERT( typeid(EMO_BEST_FIT_INT( 6)) == typeid(unsigned char) );
		CPPUNIT_ASSERT( typeid(EMO_BEST_FIT_INT( 7)) == typeid(unsigned char) );
		CPPUNIT_ASSERT( typeid(EMO_BEST_FIT_INT( 8)) == typeid(unsigned char) );

		CPPUNIT_ASSERT( typeid(EMO_BEST_FIT_INT( 9)) == typeid(unsigned short) );
		CPPUNIT_ASSERT( typeid(EMO_BEST_FIT_INT(10)) == typeid(unsigned short) );
		CPPUNIT_ASSERT( typeid(EMO_BEST_FIT_INT(11)) == typeid(unsigned short) );
		CPPUNIT_ASSERT( typeid(EMO_BEST_FIT_INT(12)) == typeid(unsigned short) );
		CPPUNIT_ASSERT( typeid(EMO_BEST_FIT_INT(13)) == typeid(unsigned short) );
		CPPUNIT_ASSERT( typeid(EMO_BEST_FIT_INT(14)) == typeid(unsigned short) );
		CPPUNIT_ASSERT( typeid(EMO_BEST_FIT_INT(15)) == typeid(unsigned short) );
		CPPUNIT_ASSERT( typeid(EMO_BEST_FIT_INT(16)) == typeid(unsigned short) );

		CPPUNIT_ASSERT( typeid(EMO_BEST_FIT_INT(17)) == typeid(unsigned int) );
		CPPUNIT_ASSERT( typeid(EMO_BEST_FIT_INT(18)) == typeid(unsigned int) );
		CPPUNIT_ASSERT( typeid(EMO_BEST_FIT_INT(19)) == typeid(unsigned int) );
		CPPUNIT_ASSERT( typeid(EMO_BEST_FIT_INT(20)) == typeid(unsigned int) );
		CPPUNIT_ASSERT( typeid(EMO_BEST_FIT_INT(21)) == typeid(unsigned int) );
		CPPUNIT_ASSERT( typeid(EMO_BEST_FIT_INT(22)) == typeid(unsigned int) );
		CPPUNIT_ASSERT( typeid(EMO_BEST_FIT_INT(23)) == typeid(unsigned int) );
		CPPUNIT_ASSERT( typeid(EMO_BEST_FIT_INT(24)) == typeid(unsigned int) );
		CPPUNIT_ASSERT( typeid(EMO_BEST_FIT_INT(25)) == typeid(unsigned int) );
		CPPUNIT_ASSERT( typeid(EMO_BEST_FIT_INT(26)) == typeid(unsigned int) );
		CPPUNIT_ASSERT( typeid(EMO_BEST_FIT_INT(27)) == typeid(unsigned int) );
		CPPUNIT_ASSERT( typeid(EMO_BEST_FIT_INT(28)) == typeid(unsigned int) );
		CPPUNIT_ASSERT( typeid(EMO_BEST_FIT_INT(29)) == typeid(unsigned int) );
		CPPUNIT_ASSERT( typeid(EMO_BEST_FIT_INT(30)) == typeid(unsigned int) );
		CPPUNIT_ASSERT( typeid(EMO_BEST_FIT_INT(31)) == typeid(unsigned int) );
		CPPUNIT_ASSERT( typeid(EMO_BEST_FIT_INT(32)) == typeid(unsigned int) );

		CPPUNIT_ASSERT( typeid(EMO_BEST_FIT_INT(33)) == typeid(unsigned long) );
		CPPUNIT_ASSERT( typeid(EMO_BEST_FIT_INT(34)) == typeid(unsigned long) );
		CPPUNIT_ASSERT( typeid(EMO_BEST_FIT_INT(35)) == typeid(unsigned long) );
		CPPUNIT_ASSERT( typeid(EMO_BEST_FIT_INT(36)) == typeid(unsigned long) );
		CPPUNIT_ASSERT( typeid(EMO_BEST_FIT_INT(37)) == typeid(unsigned long) );
		CPPUNIT_ASSERT( typeid(EMO_BEST_FIT_INT(38)) == typeid(unsigned long) );
		CPPUNIT_ASSERT( typeid(EMO_BEST_FIT_INT(39)) == typeid(unsigned long) );
		CPPUNIT_ASSERT( typeid(EMO_BEST_FIT_INT(40)) == typeid(unsigned long) );
		CPPUNIT_ASSERT( typeid(EMO_BEST_FIT_INT(41)) == typeid(unsigned long) );
		CPPUNIT_ASSERT( typeid(EMO_BEST_FIT_INT(42)) == typeid(unsigned long) );
		CPPUNIT_ASSERT( typeid(EMO_BEST_FIT_INT(43)) == typeid(unsigned long) );
		CPPUNIT_ASSERT( typeid(EMO_BEST_FIT_INT(44)) == typeid(unsigned long) );
		CPPUNIT_ASSERT( typeid(EMO_BEST_FIT_INT(45)) == typeid(unsigned long) );
		CPPUNIT_ASSERT( typeid(EMO_BEST_FIT_INT(46)) == typeid(unsigned long) );
		CPPUNIT_ASSERT( typeid(EMO_BEST_FIT_INT(47)) == typeid(unsigned long) );
		CPPUNIT_ASSERT( typeid(EMO_BEST_FIT_INT(48)) == typeid(unsigned long) );
		CPPUNIT_ASSERT( typeid(EMO_BEST_FIT_INT(49)) == typeid(unsigned long) );
		CPPUNIT_ASSERT( typeid(EMO_BEST_FIT_INT(50)) == typeid(unsigned long) );
		CPPUNIT_ASSERT( typeid(EMO_BEST_FIT_INT(51)) == typeid(unsigned long) );
		CPPUNIT_ASSERT( typeid(EMO_BEST_FIT_INT(52)) == typeid(unsigned long) );
		CPPUNIT_ASSERT( typeid(EMO_BEST_FIT_INT(53)) == typeid(unsigned long) );
		CPPUNIT_ASSERT( typeid(EMO_BEST_FIT_INT(54)) == typeid(unsigned long) );
		CPPUNIT_ASSERT( typeid(EMO_BEST_FIT_INT(55)) == typeid(unsigned long) );
		CPPUNIT_ASSERT( typeid(EMO_BEST_FIT_INT(56)) == typeid(unsigned long) );
		CPPUNIT_ASSERT( typeid(EMO_BEST_FIT_INT(57)) == typeid(unsigned long) );
		CPPUNIT_ASSERT( typeid(EMO_BEST_FIT_INT(58)) == typeid(unsigned long) );
		CPPUNIT_ASSERT( typeid(EMO_BEST_FIT_INT(59)) == typeid(unsigned long) );
		CPPUNIT_ASSERT( typeid(EMO_BEST_FIT_INT(60)) == typeid(unsigned long) );
		CPPUNIT_ASSERT( typeid(EMO_BEST_FIT_INT(61)) == typeid(unsigned long) );
		CPPUNIT_ASSERT( typeid(EMO_BEST_FIT_INT(62)) == typeid(unsigned long) );
		CPPUNIT_ASSERT( typeid(EMO_BEST_FIT_INT(63)) == typeid(unsigned long) );
		CPPUNIT_ASSERT( typeid(EMO_BEST_FIT_INT(64)) == typeid(unsigned long) );
	}

};

static CPPUNIT_NS::AutoRegisterSuite<UNITTEST_NAME> CPPUNIT_JOIN(test,UNITTEST_NAME);

#undef UNITTEST_NAME
