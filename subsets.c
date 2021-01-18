#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

void print_int_arr(int *arr, int arr_size){
	int i;
	for (i=0; i<arr_size; i++){
		printf("%d ", arr[i]);
	}
	printf("\n");
}

// long ipow(int base, int exponent){
// 	long result=1;
// 	for(int i=exponent; i>0; i--){
// 		result *= base;
// 	} // 	return result;
// }

				// int *ret[4];
				// int nums1[2] = {1,2};
				// int nums4[3];
				// nums4[0] = 0;
				// nums4[1] = 4;
				// nums4[2] = 4;
				// ret[0] = nums1;
				// ret[1] = nums4;
				// ret[2] = nums1;
				// ret[3] = nums4;
				// int i;
				// for(i=0; i<4; i++) {
				// 	printf("%d\n", ret[i][1]);
				// }


int combinations_size(int n, int k){
	int k_larger;
	int k_smaller;
	int i;
	int ret = 1;

	k_larger = MAX(k, n-k);
	k_smaller = MIN(k, n-k);

	for (i=k_larger+1; i<=n; i++) {
		ret *= i;
	}

	for (i=1; i<=k_smaller; i++) {
		ret /= i;
	}
	return ret;
}

int **combos(int *nums, int num_size, int k, int *ret_size){
	*ret_size = combinations_size(num_size, k);
	int **ret = (int **) malloc(sizeof(int *) * (*ret_size));
	// printf("Expected return size for n=%d and k=%d: %d\n", 
	// num_size, k, combinations_size(num_size, k));

	// k represents the # of value we will pick from nums
	if ((k == 0) || (k > num_size)) {
		printf("\n");
		return ret;
	}
	if (k == num_size) {
		int *this_ret = (int *)malloc(sizeof(int)*k);
		int i;
		for (i=0; i<k; i++) {
			this_ret[i] = nums[i];
		}
		ret[0] = this_ret;
		return ret;
	}

	// calculate the size of the return_array

	int indicies[k];
	int max_ref[k];
	int val;
	int i;

	for (i=0; i<k; i++){
		indicies[i] = i;
		max_ref[k-i-1] = num_size-i-1;
	}

	int turn = 0;
	while(1) {
		int *this_ret = (int *)malloc(sizeof(int)*k);
		for (i=0; i<k; i++){
			this_ret[i] = nums[indicies[i]];
		}
		ret[turn] = this_ret;
		
		i = k - 1;
		while ((i != -1) && (indicies[i] == max_ref[i])){
			i--;
		}
		if (i == -1) {
			// max_ref has been reached: function is complete and we have 
			// explored every combinations
			return ret;
		}

		// the completion of while loop means we point at the first index 
		// to be incremented
		val = indicies[i]+1;
		for (; i<k; i++){
			indicies[i] = val;
			val++;
		}

		// update turn: the value that keeps track of ret's index
		turn++;
	}
}


int **subsets(int *nums, int num_size, int *return_size, int **ret_subset_size){
    *return_size = 1 << num_size;
	*ret_subset_size = (int *) malloc(sizeof(int) * (*return_size));
    int **ret = (int **) malloc((*return_size) * sizeof(int*));
	int c;
	int j;
	int combo_size;
	int ret_index = 0;
	int **this_ret;
	for (c=0;c<=num_size;c++){
		this_ret = combos(nums, num_size, c, &combo_size);
		for (j=0; j<combo_size; j++) {
			ret[ret_index] = this_ret[j];
			(*ret_subset_size)[ret_index] = c;

			// print_int_arr(ret[ret_index], c);
			// free(this_ret[j]);

			ret_index++;
		}
		free(this_ret);
	}
	return ret;
}

int main(){
	int i;
	int return_size;
	int num_size = 6;
	int nums[num_size];
	int *return_subset_size;
	for (i=0; i<num_size; i++){
		nums[i] = i;
	}

	int note;
	note = 1<<10;
	int **ret = subsets(nums, num_size, &return_size, &return_subset_size);

	// printf("return (subset) size gave: %d\n", return_size);
	// printf("note: %d\n", note);

	// print the result and exit
	for (i=0; i<return_size; i++){
		print_int_arr(ret[i], return_subset_size[i]);
		free(ret[i]);
	}
	free(ret);
	free(return_subset_size);
	return 0;
}
