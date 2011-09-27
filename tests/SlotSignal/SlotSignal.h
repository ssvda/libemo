#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <emoslot.h>
#include <emosignal.h>
#include <emobind.h>
#include <emoobjectbase.h>

using namespace Emo;

#ifndef UNITTEST_NAME
#	define UNITTEST_NAME SlotSignal
#endif

int theGlobal;

class MocSender
{
public:
	EMO_SIGNAL(MocSender, (), 0, ()) incrementByOne;
	
	typedef EMO_SIGNAL_X(MocSender,
	                     Emo::EmoTinySignalInternals,
	                     (int v), 1,
	                     (EMO_SIGNAL_ARGUMENT(0, v))) IncrementOnType;
	IncrementOnType incrementOn;
	
	typedef EMO_SIGNAL_X(MocSender,
	                     Emo::EmoStaticSignalInternals,
	                     (int v), 1,
	                     (EMO_SIGNAL_ARGUMENT(0, theGlobal))) IncrementByGlobalType;
	IncrementByGlobalType incrementByGlobal;
};

class MocReceiver
	:public EmoObjectBase
{
public:
	MocReceiver()
		:m_result(0)
	{
	}
	EMO_SLOTS(increment);
	
	void increment()
	{
		++this->m_result;
	}
	
	void increment(int value);
	
	EMO_SLOTS(decrement);
	
	void decrement(int v)
	{
		this->m_result -= v - 1;
	}
	
	int result() const
	{
		return this->m_result;
	}
	
private:
	int m_result;
};

void MocReceiver::increment(int value)
{
	this->m_result += value;
}

EMO_MASTER(MocReceiver::increment, MocReceiver)

EMO_SLOT_DECL(MocReceiver::increment, (), ())
EMO_SLOT_DECL(MocReceiver::increment, (int), (EMO_SLOT_ARGUMENT(0, int)))

EMO_MASTER(MocReceiver::decrement, MocReceiver)

EMO_SLOT_DECL(MocReceiver::decrement, (int), (EMO_SLOT_ARGUMENT(0, int)))

class UNITTEST_NAME
	:public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(UNITTEST_NAME);
	
	CPPUNIT_TEST(testForDirectSlotCall);
	CPPUNIT_TEST(testForConnectionWOArguments);
	CPPUNIT_TEST(testForConnectionWArguments);
	CPPUNIT_TEST(testForConnectionPredefinedArgument);
	CPPUNIT_TEST(testForSenderOutsideOfMaster);
	
	CPPUNIT_TEST_SUITE_END();
	
public:
	void testForDirectSlotCall()
	{
		MocReceiver r;
		r.increment();
		CPPUNIT_ASSERT(r.result() == 1);
	}
	
	void testForConnectionWOArguments()
	{
		MocReceiver r;
		MocSender s;
		emoBind<EMO_SLOT(MocReceiver::increment)()>(&r, s.incrementByOne);
		s.incrementByOne();
		CPPUNIT_ASSERT(r.result() == 1);
	}
	
	void testForConnectionWArguments()
	{
		MocReceiver r;
		MocSender s;
		emoBind<EMO_SLOT(MocReceiver::increment)(int)>(&r, s.incrementOn);
		s.incrementOn(10);
		CPPUNIT_ASSERT(r.result() == 10);
	}
	
	void testForConnectionPredefinedArgument()
	{
		MocReceiver r;
		MocSender s;
		emoBind<EMO_SLOT(MocReceiver::increment)(int)>(&r, s.incrementByGlobal);
		theGlobal = 3;
		s.incrementByGlobal(1);
		CPPUNIT_ASSERT(r.result() == 3);
	}
	
	void testForSenderOutsideOfMaster()
	{
		MocReceiver r;
		MocSender::IncrementOnType sig;
		emoBind<EMO_SLOT(MocReceiver::increment)(int)>(&r, sig);
		sig(1);
		CPPUNIT_ASSERT(r.result() == 1);
	}
	
	void testForSeveralSlots()
	{
		MocReceiver r;
		MocSender s;
		emoBind<EMO_SLOT(MocReceiver::increment)(int)>(&r, s.incrementOn);
		emoBind<EMO_SLOT(MocReceiver::decrement)(int)>(&r, s.incrementOn);
		s.incrementOn(10);
		CPPUNIT_ASSERT(r.result() == 1);
	}
};

static CPPUNIT_NS::AutoRegisterSuite<UNITTEST_NAME> CPPUNIT_JOIN(test,UNITTEST_NAME);

#undef UNITTEST_NAME
