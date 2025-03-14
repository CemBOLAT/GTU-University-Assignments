public class SelectionSort extends SortAlgorithm {

	public SelectionSort(int input_array[]) {
		super(input_array);
	}

    @Override
    public void sort() {
        // Selection Sort Algorithm
        int minIndex; // index of minimum element for each iterated subarray
        for (int i = 0; i < arr.length - 1; i++) { // iterate through the array
            minIndex = i; // set the minimum index to the current index
            for (int j = i + 1; j < arr.length; j++) { // iterate through the rest of the array
                comparison_counter += 1;
                if (arr[j] < arr[minIndex]) { // if the current element is less than the minimum element
                    minIndex = j; // then change the minimum index to the current index
                }
            }
            // Even if i and minIndex happen to be the same, using an 'if' statement to avoid unnecessary swaps wouldn't alter the time complexity.
            swap(i, minIndex); // swap the minimum element with the current element
        }
    }

    @Override
    public void print() {
    	System.out.print("Selection Sort\t=>\t");
    	super.print();
    }
}
