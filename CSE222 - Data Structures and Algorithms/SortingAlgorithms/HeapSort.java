public class HeapSort extends SortAlgorithm
{
	public HeapSort(int input_array[])
	{
		super(input_array);
	}

	@Override
	public void sort()
	{
		// Heap Sort Algorithm
		int n = arr.length;

		// Build Min Heap

		// We start mother of last node
		for (int i = n / 2 - 1; i >= 0; i--)
		{
			heapify(n, i);
		}

		// One by one extract an element from heap
		for (int i = n - 1; i > 0; i--)
		{
			// Move current root to end
			swap(0, i);

			// call max heapify on the reduced heap
			heapify(i, 0);
		}
	}

	void heapify(int n, int i)
	{
		int largest = i; // Initialize largest as root
		int left = 2 * i + 1;
		int right = 2 * i + 2;

		comparison_counter += 1;
		if (left < n && arr[left] > arr[largest])
		{
			largest = left;
		}

		comparison_counter += 1;
		if (right < n && arr[right] > arr[largest])
		{
			largest = right;
		}

		if (largest != i)
		{
			swap(i, largest);
			heapify(n, largest);
		}
	}


	@Override
	public void print()
	{
		System.out.print("Heap Sort\t=>\t");
		super.print();
	}
}
