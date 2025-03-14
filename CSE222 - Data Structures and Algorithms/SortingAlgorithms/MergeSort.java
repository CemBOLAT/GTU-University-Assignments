public class MergeSort extends SortAlgorithm {

	public MergeSort(int input_array[]) {
		super(input_array);
	}

	private void merge(int arr[], int begin, int mid, int end){
        int leftIndex = begin; // Index of the left part of the array
        int rightIndex = mid + 1; // Index of the right part of the array
        int tempIndex = 0; // Index of the temporara array
        int temp[] = new int[end - begin + 1]; // Temporary array to store the merged array it costs O(n) memory space
        while (leftIndex <= mid && rightIndex <= end) { // Compare the elements of the left and right parts of the array
            comparison_counter += 1;

            if (arr[leftIndex] < arr[rightIndex]) { // If the left element is smaller than the right element
                temp[tempIndex] = arr[leftIndex];
                leftIndex++;
            } else { // If the right element is smaller than the left element
                temp[tempIndex] = arr[rightIndex];
                rightIndex++;
            }
            
            tempIndex++;
        }
        // One of the parts may have elements left because of the previous while loop finishes when one of the parts is empty
        while (leftIndex <= mid) { // if there are still elements in the left part of the array
            temp[tempIndex] = arr[leftIndex];
            leftIndex++;
            tempIndex++;
        }
        while (rightIndex <= end) { // if there are still elements in the right part of the array
            temp[tempIndex] = arr[rightIndex];
            rightIndex++;
            tempIndex++;
        }
        for (int i = 0; i < temp.length; i++) { // Copy the temporary array to the original array
            arr[begin + i] = temp[i];
        }
    }

    private void sort(int arr[], int begin, int end){
        // Merge Sort Algorithm
        if (begin >= end) { // Base case: If the array has only one element or is empty
            return;
        }
        int mid = (end + begin) / 2; // Find the middle index
        sort(arr, begin, mid); // sort left part of the array
        sort(arr, mid + 1, end); // sort right part of the array
        merge(arr, begin, mid, end); // merge these two parts
    }

    @Override
    public void sort() {
        int begin = 0;
        int end = arr.length - 1;
    	sort(arr, begin, end);
    }

    @Override
    public void print() {
    	System.out.print("Merge Sort\t=>\t");
    	super.print();
    }
}
