public class QuickSort extends SortAlgorithm {

	public QuickSort(int input_array[]) {
		super(input_array);
	}

    private int partition(int arr[], int begin, int end){
        // Partitioning the array using the last element as the pivot
        int current_index = begin; // Index of the current element being compared
        int swap_marker = begin - 1; // Index of the swap point for the pivot element
        int pivot = arr[end]; // Pivot element
        for (current_index = begin; current_index < end; current_index++) { // Compare each element with the pivot
            comparison_counter += 1;
            if (arr[current_index] < pivot) { // If the element is less than the pivot, swap it with the swap marker
                swap_marker += 1;
                //There is no check for unnecessary swaps because the swap operation is O(1) and it is not a big deal; also, the output PDF doesn't seem to care much either.
                swap(swap_marker, current_index); 
            }
        }
        swap(swap_marker + 1, end); // Swap the pivot element with the element at the swap marker
        return swap_marker + 1;  // Return the index of the pivot element after partitioning
    }

    private void sort(int arr[], int begin, int end){
        // Quick Sort Algorithm
        if (begin >= end) { // Base case: If the array has only one element or is empty
            return;
        }
        int partitionIndex = partition(arr, begin, end); // partitioning index
        sort(arr, begin, partitionIndex - 1); // sort left partition
        sort(arr, partitionIndex + 1, end); // sort right partition
    }

    @Override
    public void sort() {
        int begin = 0;
        int end = arr.length - 1;

    	sort(arr, begin, end);
    }

    @Override
    public void print() {
    	System.out.print("Quick Sort\t=>\t");
    	super.print();
    }
}
