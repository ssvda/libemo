#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <emoconnectionlistengine.h>
#include <emoslotbase.h>

using namespace Emo;

#ifndef UNITTEST_NAME
#	define UNITTEST_NAME ConnectionListEngineTest
#endif

template <EmoBool IsItWiderThanBus>
class UNITTEST_NAME : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(UNITTEST_NAME);

	CPPUNIT_TEST(testAllocate< 1>);
	CPPUNIT_TEST(testAllocate< 2>);
	CPPUNIT_TEST(testAllocate< 8>);
	CPPUNIT_TEST(testAllocate<16>);
	CPPUNIT_TEST(testAllocate<32>);
#ifdef EMO_64BIT
	CPPUNIT_TEST(testAllocate<64>);
#endif
	CPPUNIT_TEST(testIterate<3>);
	CPPUNIT_TEST(testNext<10>);

	CPPUNIT_TEST_SUITE_END();
public:

	typedef EmoConnectionListEngine<IsItWiderThanBus> Engine;

	template <EmoSizeType size>
	void testAllocate()
	{
		typename Engine::template Buffer<size> buffer;
		Engine::initialize(&buffer, size);

		EmoConnection* connections[size];

		for(EmoSizeType i=0; i<size; ++i)
		{
			connections[i] = Engine::allocate(&buffer, size);
			CPPUNIT_ASSERT(connections[i] != 0);
			connections[i]->m_slot = new EmoSlotBase;
		}

		CPPUNIT_ASSERT(Engine::allocate(&buffer, size) == 0);

		// check that connections are different

		for(EmoSizeType i=0; i<size; ++i)
		{
			for(EmoSizeType j=i+1; j<size; ++j)
			{
				CPPUNIT_ASSERT(connections[i] != connections[j]);
			}
		}

		//clear memory
		for(EmoSizeType i=0; i<size; ++i)
		{
			delete connections[i]->m_slot;
		}
	}

	template <EmoSizeType size>
	void testIterate()
	{
		typename Engine::template Buffer<size> buffer;
		Engine::initialize(&buffer, size);

		CPPUNIT_ASSERT(Engine::iterate(&buffer, size) == 0);
		EmoConnection *connection = Engine::allocate(&buffer, size);
		connection->m_slot = new EmoSlotBase;

		CPPUNIT_ASSERT(Engine::iterate(&buffer, size) == connection);

		delete connection->m_slot;
	}

	template <EmoSizeType size>
	void testNext()
	{
		typename Engine::template Buffer<size> buffer;

		Engine::initialize(&buffer, size);

		EmoConnection* connections[size];

		for(EmoSizeType i=0; i<size;  ++i)
		{
			connections[i] = Engine::allocate(&buffer, size);
			CPPUNIT_ASSERT(connections[i] != 0);
			connections[i]->m_slot = new EmoSlotBase;
		}

		CPPUNIT_ASSERT(Engine::allocate(&buffer, size) == 0);

		CPPUNIT_ASSERT(Engine::iterate(&buffer, size) == connections[0]);

		for(EmoSizeType i=0; i<size-1; ++i)
		{
			CPPUNIT_ASSERT(Engine::next(&buffer, connections[i], size) ==
			               connections[i+1]);
		}

		CPPUNIT_ASSERT(Engine::next(&buffer, connections[size-1], size) == 0);

		//clear memory
		for(EmoSizeType i=0; i<size; ++i)
		{
			delete connections[i]->m_slot;
		}
	}

	template <EmoSizeType size>
	void testFree()
	{
		typename Engine::template Buffer<size> buffer;

		Engine::initialize(&buffer, size);

		EmoConnection* connections[size];

		for(EmoSizeType i=0; i<size;  ++i)
		{
			connections[i] = Engine::allocate(&buffer, size);
			CPPUNIT_ASSERT(connections[i] != 0);
			connections[i]->m_slot = new EmoSlotBase;
		}

		CPPUNIT_ASSERT(Engine::allocate(&buffer, size) == 0);

		delete connections[0]->m_slot;
		Engine::free(&buffer, connections[0], size);

		//after delete we can allocate one
		connections[0] = Engine::allocate(&buffer, size);
		CPPUNIT_ASSERT(connections[0] != 0);

		//but second again out of size
		CPPUNIT_ASSERT(Engine::allocate(&buffer, size) == 0);

		//clear memory
		for(EmoSizeType i=0; i<size; ++i)
		{
			delete connections[i]->m_slot;
		}
	}

};

static CPPUNIT_NS::AutoRegisterSuite<UNITTEST_NAME<true> > CPPUNIT_JOIN(testTrue,UNITTEST_NAME);
static CPPUNIT_NS::AutoRegisterSuite<UNITTEST_NAME<false> > CPPUNIT_JOIN(testFalse,UNITTEST_NAME);

#undef UNITTEST_NAME
