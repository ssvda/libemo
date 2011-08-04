#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class EmptyCppUnitTestMyTest : public CppUnit::TestFixture
{
   CPPUNIT_TEST_SUITE(EmptyCppUnitTestMyTest);
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

CPPUNIT_TEST_SUITE_REGISTRATION(EmptyCppUnitTestMyTest);
