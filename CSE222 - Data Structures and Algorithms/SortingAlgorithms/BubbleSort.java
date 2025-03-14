public class BubbleSort extends SortAlgorithm {

	public BubbleSort(int input_array[]) {
		super(input_array);
	}

	@Override
	public void sort() {
		// Bubble Sort Algorithm
		boolean swapped = false; // Flag to check if any swapping has been done in the current iteration

		for (int i = 0; i < arr.length - 1; i++) {
			swapped = false;
			// Each iteration of the outer loop will place the largest element at the end of the array.
			for (int j = 0; j < arr.length - i - 1; j++) {
				comparison_counter += 1;
				if (arr[j] > arr[j + 1]) { // Swap if the element is greater than the next element
					swap(j, j + 1);
					swapped = true;
				}
			}
			if (!swapped) { // If no swapping has been done in the current iteration, the array is already sorted.
				break;
			}
		}
	}

	@Override
	public void print() {
		System.out.print("Bubble Sort\t=>\t");
		super.print();
	}
}
