#include <time.h>
#include <sys/resource.h>
#include "stdlib.h"
#include <string>
#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>

double get_cpu_time()
{ struct rusage ruse;
  getrusage(RUSAGE_SELF, &ruse);
  return ruse.ru_utime.tv_sec+ruse.ru_utime.tv_usec/1000000.0 + 
         ruse.ru_stime.tv_sec+ruse.ru_stime.tv_usec/1000000.0; 
}

int quicksort(string array[], int start, int end)
{
	int ptr = start;                
	string temp = "";
	if (start < end){
		for (int i = start; i < end; i++){
			if (array[i] <= array[end]){
				temp = array[ptr];
				array[ptr] = array[i];
				array[i] = temp;
				ptr = ptr+1;
			}
		}
		temp = array[end];
		array[ptr] = array[ptr];
		array[ptr] = temp;
		quicksort(array, start, ptr-1);
		quicksort(array, ptr+1, end);
	}
}

void merge(string array[], int low, int mid, int high){

	int i = 0;
	int j = 0;
	int k = 0;
	const int size = (high-low)+1;
	string newarray[size];	
	while(i<mid+1&&j<high+1){
		if(array[i]>array[j]){
			newarray[k] = array[j];
			j++;
		}
		else{
			newarray[k] = array[i];
			i++;
		}
	}
	k = 0;
	i = low;
	while(k<size){
		array[i] = newarray[k];
		i++;
		k++;
	}
}

void mergesort(string array[], int left, int right){

	if (left < right){
        	int mid = left+(right-left)/2;
        	mergesort(array, left, mid);
        	mergesort(array, mid+1, right);		
		merge(array,left,mid,right);
	}
}

void main(){

	ifstream fin;
	fin.open("data1.txt");
	int num = 0;
	cout<<"Please enter the number of strings you would like to sort\n";
	cin>>num;
	const int constnum = num;
	string quickarray[num];
	string mergearray[num];
	int i = 0;
	string temp = "";
	while(i<num){
		
		getline(fin,temp);
		quickarray[i] = temp;
		mergearray[i] = temp;
		i++;
	}
	double start = get_cpu_time();
	quicksort(quickarray,0,num-1);
	double tot = get_cpu_time() - start;
	cout<<"Time for quicksort: "<<tot<<endl;
	start = get_cpu_time();
	mergesort(mergearray,0,num-1);
	tot = get_cpu_time() - start;
	cout<<"Time for mergesort: "<<tot<<endl;
	fin.close();
}
