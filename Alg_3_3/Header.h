#pragma once
#include <iostream>
#include <stdexcept>

using namespace std;

class Iterator
{
public:
	virtual int next() = 0;
	virtual bool has_next() = 0;
};

class Heap
{
	static const int SIZE = 100;
	int* heap;
	size_t heap_size;
	size_t max_size;
	Iterator* bftiterator;
	Iterator* dftiterator;
public:
	Heap() //constructor
	{
		max_size = 100;
		heap = new int[max_size];
		heap_size = 0;
		bftiterator = NULL;
		dftiterator = NULL;
	}
	~Heap() //destructor
	{
		delete[] heap;
	}

	void SwapDown(int key) //sifting the element down
	{
		int tmp;
		while (2 * key + 1 < heap_size)
		{
			int left = 2 * key + 1;
			int right = 2 * key + 2;
			int j = left;

			if (right < heap_size && heap[right] < heap[left])
			{
				j = right;
			}

			if (heap[key] <= heap[j])
			{
				break;
			}

			tmp = heap[key];
			heap[key] = heap[j];
			heap[j] = tmp;
			key = j;
		}
	}

	void SwapUp(int key) //sifting the element up
	{
		int tmp;
		while (heap[key] < heap[(key - 1) / 2])
		{
			tmp = heap[key];
			heap[key] = heap[(key - 1) / 2];
			heap[(key - 1) / 2] = tmp;
			key = (key - 1) / 2;
		}
	}

	void insert(int key) //inserts element to heap
	{
		if (heap_size == max_size)
		{
			int* heap2 = new int[max_size + 100];
			for (int i = 0; i < max_size; i++)
			{
				heap2[i] = heap[i];
			}
			max_size = max_size + 100;
			delete[] heap;
			heap = heap2;
		}
		heap_size++;
		heap[heap_size - 1] = key;
		SwapUp(heap_size - 1);
	}

	bool contains(int elem) // checks if heap contains entered element
	{
		for (int i = 0; i < heap_size; i++)
		{
			if (heap[i] == elem)
			{
				return true;
			}
		}
		return false;
	}

	void remove(int elem) //removes element from heap
	{
		for (int i = 0; i < heap_size; i++)
		{
			if (heap[i] == elem)
			{
				heap[i] = heap[heap_size - 1];
				SwapDown(i);
				heap_size--;
				break;
			}
		}
	}

	class bft_iterator : public Iterator
	{
		size_t current;
		Heap* heap;
	public:
		bft_iterator(size_t start, Heap* Heap) //constructor
		{
			current = start;
			heap = Heap;
		}

		int next() override // goes to next bfs iterator of heap element
		{
			if (!has_next())
			{
				throw out_of_range("no more elements\n");
			}
			current++;
			return heap->heap[current - 1];
		}

		bool has_next() override //check if bfs iterator of heap has next element
		{
			return (current != (heap->heap_size));
		}

	};

	Iterator* add_bft_iterator()//create iterator
	{
		bftiterator = new bft_iterator(0, this);
		return bftiterator;
	}


	class dft_iterator : public Iterator
	{
		size_t current;
		Heap* heap;
		bool* visited;

	public:
		dft_iterator(size_t start, Heap* Heap) //constructor
		{
			current = start;
			heap = Heap;
			visited = new bool[heap->heap_size];
			for (int i = 0; i < heap->heap_size; i++) { visited[i] = false; }
		}

		int next() override	// gets next heap element
		{
			if (!has_next())
			{
				throw out_of_range("no more elements\n");
			}
			size_t prev = current;
			visited[prev] = 1;
			if (!has_next())
			{
				return heap->heap[prev];
			}
			size_t left, right;
			while (1)
			{
				left = current * 2 + 1;
				right = current * 2 + 2;
				if (left < heap->heap_size)
				{
					if (!visited[left])
					{
						current = left;
						break;
					}
				}
				if (right < heap->heap_size)
				{
					if (!visited[right])
					{
						current = right;
						break;
					}
				}
				current = (current - 1) / 2;
			}
			return heap->heap[prev];
		}

		bool has_next() override //checking for the existence of the next element
		{
			if (heap->heap_size == 0)
			{
				return false;
			}
			size_t next_index = current;
			size_t left, right;
			while (1)
			{
				left = (next_index * 2) + 1;
				right = (next_index * 2) + 2;
				if (left < heap->heap_size)
				{
					if (!visited[left])
					{
						return true;
					}
				}
				if (right < heap->heap_size)
				{
					if (!visited[right])
					{
						return true;
					}
				}
				if (next_index != 0)
				{
					next_index = (next_index - 1) / 2;
				}
				else if (!visited[next_index])
				{
					return true;
				}
				else return false;
			}
		}

		~dft_iterator()//destructor
		{
			delete[] visited;
		}
	};

	Iterator* add_dft_iterator()//create iterator
	{
		if (dftiterator != nullptr)
		{
			delete dftiterator;
		}
		dftiterator = new dft_iterator(0, this);
		return dftiterator;
	}

};