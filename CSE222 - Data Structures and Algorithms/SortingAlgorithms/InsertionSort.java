
public class InsertionSort extends SortAlgorithm {

	public InsertionSort(int input_array[]) {
		super(input_array);
	}

	@Override
	public void sort() {
		// Insertion Sort Algorithm
		for (int i = 0; i < arr.length; i++){
			for (int j = i - 1; j >= 0; j--){
				comparison_counter += 1;
				if (arr[j] > arr[j + 1]){
					swap(j, j + 1);
				}
				else {
					break;
				}
			}
		}
	}

	@Override
	public void print() {
		System.out.print("Insertion Sort\t=>\t");
		super.print();
	}
}
