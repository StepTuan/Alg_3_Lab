#include "pch.h"
#include "CppUnitTest.h"
#include <stdexcept>
#include "../Alg_3_3/Header.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest3
{
	TEST_CLASS(UnitTest3)
	{
	public:

		TEST_METHOD(insert)
		{
			Heap Heap;

			Heap.insert(75);
			Heap.insert(98);
			Heap.insert(1);
			Heap.insert(87);
			Heap.insert(15);
			Heap.insert(63);
			Heap.insert(42);
			Heap.insert(62);
			Heap.insert(732);

			Iterator* iterator;
			iterator = Heap.add_bft_iterator();
			Assert::AreEqual(iterator->next(), 1);
			Assert::AreEqual(iterator->next(), 15);
			Assert::AreEqual(iterator->next(), 42);
			Assert::AreEqual(iterator->next(), 62);
			Assert::AreEqual(iterator->next(), 87);
			Assert::AreEqual(iterator->next(), 75);
			Assert::AreEqual(iterator->next(), 63);
			Assert::AreEqual(iterator->next(), 98);
			Assert::AreEqual(iterator->next(), 732);
		}


		TEST_METHOD(remove)
		{
			Heap Heap;

			Heap.insert(75);
			Heap.insert(98);
			Heap.insert(1);
			Heap.insert(87);
			Heap.insert(15);
			Heap.insert(63);
			Heap.insert(42);
			Heap.insert(62);
			Heap.insert(732);
			Heap.remove(87);

			Iterator* iterator;
			iterator = Heap.add_bft_iterator();

			Assert::AreEqual(iterator->next(), 1);
			Assert::AreEqual(iterator->next(), 15);
			Assert::AreEqual(iterator->next(), 42);
			Assert::AreEqual(iterator->next(), 62);
			Assert::AreEqual(iterator->next(), 732);
			Assert::AreEqual(iterator->next(), 75);
			Assert::AreEqual(iterator->next(), 63);
			Assert::AreEqual(iterator->next(), 98);
		}

		TEST_METHOD(contains)
		{
			Heap Heap;
			Heap.insert(75);
			Heap.insert(98);
			Heap.insert(1);
			Heap.insert(87);
			Heap.insert(15);
			Heap.insert(63);
			Heap.insert(42);
			Heap.insert(62);
			Heap.insert(732);

			Assert::AreEqual(Heap.contains(1), true);
			Assert::AreEqual(Heap.contains(1000), false);
		}


	};
}