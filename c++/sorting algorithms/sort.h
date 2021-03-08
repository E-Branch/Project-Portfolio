#pragma once
#include <cmath>

using std::floor;
using std::ceil;


//PART 1: insertion sort
template<class T> int insertionsort(T arr[], int size);
//PART 2: quicksort
template<class T> int quicksort(T arr[], int size);
template<class T> int quicksort(T arr[], int startinx, int endinx);
template<class T> int partition(T arr[], int startinx, int endinx, int& count);
//PART 3: mergesort
template<class T> int mergesort(T arr[], int size);
template<class T> int merge(T arr[], int statinx, int mid, int endinx);
//PART 4: shellsort
template<class T> int shellsort(T arr[], int size);




//IMPLEMENTATION




//part 1: insertion sort
//sorts the template array using the insertion sort process
template<class T>
int insertionsort(T arr[], int size){
	int count = 0;
	int sortinx = 0; // used to store the index that the array is sorted to (inclusive)
	
	while(sortinx < size-1){
		T insval = arr[sortinx+1]; // value of next element to be sorted
		int insinx = sortinx+1; // the index the next element will be sorted to
		bool found = false;
		while(!found && insinx > 0){
			//BAROMETER:
			//if the element to the left is smaller, insinx is in correct position
			count ++;
			
			if(arr[insinx-1] < insval){
				found = true;	
			}
			else{
				//otherwise, shift the next element in the sorted part right 
				//and move insinx to the left
				arr[insinx] = arr[insinx-1];
				insinx--;
			}
			
		}
		//set the element at the found position to the value
		arr[insinx] = insval;
		sortinx++;
	}
	return count;
}




//part 2: quicksort
//sorts the given template array using the quicksort process
template<class T>
int quicksort(T arr[], int size){
	return quicksort(arr,0,size-1);	
}

//helper functions for quicksort
//startinx=first element to be sorted, endinx = last element to be sorted (inclusive)
template<class T>
int quicksort(T arr[], int startinx, int endinx){
	//if the size of the subarray given is one, return 0 (no sorting required)
	if ( endinx-startinx <= 1){
			return 0;
	}
	int count = 0;
	int part = 0;
	
	//partition the array
	part = partition(arr,startinx,endinx,count);
	
	//split the two partitioned subarrays, and sort each of them
	return count + quicksort(arr,startinx,part-1) + quicksort(arr,part+1,endinx);
}


//partitions the string using the value at endinx as a pivot, increments count with main loop]
template<class T>
int partition(T arr[], int startinx, int endinx, int& count){
	T pivot = arr[endinx];
	int left_inx = 0;
	int right_inx = endinx-1;
	
	while(left_inx < right_inx){
		//BAROMETER:
		//if the element in the left index is greater than the pivot, its on the wrong side
		
		count++;
		if(arr[left_inx] > pivot){
			if(arr[right_inx] <= pivot){
				//swap them
				T val1 = arr[left_inx];
				T val2 = arr[right_inx];
				arr[left_inx] = val2;
				arr[right_inx] = val1;
				//them, both move to the next position
				left_inx++;
				right_inx--;
				
			}
			else{
				right_inx--;
				
			}
		}
		else{
			left_inx++;	
			
		}
		
	}
	//we cannot confirm that left_inx is the correct possition to place the pivot (such as if
	// the pivot is the largest element), so I'll find it with a loop
	int k =0;
	while(arr[k]<=pivot && k < endinx){
		k++;
		
	}
	
	
	//swap the value found with the pivot
	T val1 = arr[k];
	arr[k] = pivot;
	arr[endinx] = val1;
	
	return k;	
}




//part 3: mergesort
//sorts the template array using the mergesort process
template<class T>
int mergesort(T arr[], int size){
	int count = 0;
	int k = 2;
	while(k<=size){
		int g = 0;
		
		//merge all groups of size k
		while(g+k-1 < size){
			count += merge<T>(arr,g,g+(k/2),g+k-1);
			g=g+k;
			
		}
		//merge the remaining elements
		count += merge<T>(arr,g,g+((size-g)/2),size-1);
		k=k*2;
		
	}
	//merge the remaining
	count+= merge<T>(arr,0,k/2,size-1);
	return count;
	
}

//helper function for merge
// arr = the array to be sorted, startinx = the index of the first element to be merged
// mid = the index of the first element in the right subarray
// endinx = the last element to be merged
//returns count
template <class T>
int merge(T arr[], int startinx, int mid, int endinx){
	int count = 0;
	
	int left_inx = startinx; //the current position in the left subarray
	int mid_inx = mid; // the current position in the right subarray
	
	int s_temp = endinx-startinx+1; // the length of the temporary array
	T temp[ s_temp]; // a temporary array to save the new order of elements
	int t = 0; // the current index for temp
	
	//go through left and right subarrays, adding the smallest of either to temp until one is empty
	while(left_inx < mid && mid_inx <= endinx){
		if(arr[left_inx] < arr[mid_inx]){
			temp[t] = arr[left_inx];
			t++;
			left_inx++;
		}
		else{

			temp[t] = arr[mid_inx];
			t++;
			mid_inx++;
		}
	}
	
	//if the left subarray still contains values, add them
	while(left_inx < mid){
		temp[t] = arr[left_inx];
		t++;
		left_inx++;
	}
	
	//if the right subarray still contains values, add them
	while(mid_inx <= endinx){
		temp[t] = arr[mid_inx];
		t++;
		mid_inx++;
	}
	//BAROMETER:
	//copy the values from the temporary array back into arr
	for(int k = 0; k< s_temp && startinx+k <= endinx ;k++){
		count++;
		arr[startinx+k] = temp[k];
		
	}
	return count;
	
}




//part 4: shellsort
//sorts the tempplate array using the shellsort method
template <class T>
int shellsort(T arr[], int size){
	
	int count = 0;
	int total_groups = ceil( ((double)size) /2.0); // number of groups, aka gap
	
	while(total_groups>=1){
		//do each of the subarrays seperately
		int group_counter = 0;
		while(group_counter < total_groups){
			//create a temp array for the subarray
			int temp_size = ceil( ((double)size) / ((double)total_groups) );
			T temp[temp_size];
			int inx = 0; // the current index for the temporary array
			
			//copy the subarray into the temp array
			while(inx*total_groups + group_counter < size){
				temp[inx] = arr[ inx*total_groups + group_counter];
				inx++;
			}
			inx--; //this undoes the last increment in the while loop
				//now inx*total_groups+group_counter is not out of bounds
			
			//BAROMETER:
			//sort the temp array using insertion sort
			count+=insertionsort<T>(temp,temp_size);
			
			//copy the temp back into the subarray
			while(inx>=0){
				arr[ inx*total_groups + group_counter ] = temp[inx];
				inx--;
			}
			group_counter++;
		}
		//divide the number of groups by two
		total_groups/=2;
	}
	return count;
}
