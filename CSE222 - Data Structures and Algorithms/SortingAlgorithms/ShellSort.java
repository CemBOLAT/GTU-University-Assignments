
public class ShellSort extends SortAlgorithm
{
	public ShellSort(int input_array[])
	{
		super(input_array);
	}

	@Override
	public void sort()
	{
		// Shell Sort Algorithm

		int n = arr.length;
		int gap = n / 2;

		while (gap > 0)
		{
			// Use Insertion Sort for each gap
			for (int i = gap; i < n; i++)
			{
				int temp = arr[i];
				int j = i;

				for (; j >= gap; j -= gap)
				{
					comparison_counter += 1;
					if (arr[j - gap] > temp)
					{
						swap(j, j - gap);
						//arr[j] = arr[j - gap]; // Column shift
					}
					else
					{
						break;
					}
				}
				arr[j] = temp;
			}

			gap /= 2;
		}
	}


	@Override
	public void print()
	{
		System.out.print("Shell Sort\t=>\t");
		super.print();
	}
}
