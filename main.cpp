#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <chrono>


using namespace std;
using namespace std::chrono;

// Created a struct to get different type of data from each line of txt file
struct data{
		string name;
		string item;
		string order_id;
		int units_sold;
		float total_profit;

	};

// this function is used for quick sort it simply swaps when 
//  we find the position of the pivot
void swap(struct data arr[] , int pos1, int pos2){
	struct data temp;
	temp = arr[pos1];
	arr[pos1] = arr[pos2];
	arr[pos2] = temp;
}
// this is for partitioning of the array based on pivot's data
//what's important here is that first we check and swap by checking name 
// then if they have the same country name we're checking the total profit
// and sorting them in ascending order

int partition(struct data arr[], int l, int h, struct data pivot){
	int i = l;
	int j = l;
	while( i <= h){
		if(arr[i].name > pivot.name){
			i++;
		}
		else if(arr[i].name==pivot.name){
			if(arr[i].total_profit>pivot.total_profit){
				i++;
			}
			else{
				swap(arr,i,j);
				i++;
				j++;
			}
		}
		else{
			swap(arr,i,j);
			i++;
			j++;
		}
	}
	return j-1;
}
// here we're calling quicksort function getting position and calling again recursively
void quickSort(struct data arr[], int l, int h){
	if(l < h){
	struct data pivot = arr[h];
	int pos = partition(arr, l, h, pivot);
	
	quickSort(arr, l, pos-1);
	quickSort(arr, pos+1, h);
	}
}

// changed the main function arguments to be able to get the N from command line
int 
main(int argc, char* argv[])
{
	
	ifstream file;
	file.open("sales.txt");

	if (!file)
	{
		cerr << "File cannot be opened!";
		exit(1);
	}

// We're getting the N as an input since it's passed
// as char* I changed it's type with using stoi function
	int N; // you should read value of N from command line
	N= stoi(argv[1]);
	string line;
	
// used dynamically allocated array to increase limit available memory 
	struct data* arr=new struct data[N];

	getline(file, line); // this is the header line

	for (int i = 0; i < N; i++)
	{
		getline(file, line, '\t'); // country (string)
		arr[i].name = line;
		getline(file, line, '\t'); // item type (string)
		arr[i].item= line;
		getline(file, line, '\t'); // order id (string)
		arr[i].order_id = line;
		file >> arr[i].units_sold;			   // units sold (integer)
		file >> arr[i].total_profit;			   // total profit (float)
		getline(file, line, '\n'); // this is for reading the \n character into dummy variable.
	}

//this function for measuring the time taken by sorting function in microseconds
	auto start = high_resolution_clock::now();
	quickSort(arr,0,N-1);
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);
 
    cout << "Time taken by function: "<< duration.count() << " microseconds" << endl;
	// from 115-135 we're using 
	//ofstream to open a txt file and write the data that we got in array after sorted
	ofstream sortedN;
	
	sortedN.open("sortedN.txt");

	if (!sortedN){
		cerr << "File cannot be opened!";
		exit(1);
	}
	else{
		
    sortedN << "Country	Item Type	Order ID	Units Sold	Total Profit\n";
    
    for(int k = 0; k < N; k++){
        sortedN << arr[k].name<<'\t'<<arr[k].item<<'\t'<<arr[k].order_id<<'\t'<<arr[k].units_sold<<'\t'<<arr[k].total_profit << endl ;
    }
    sortedN.close();
  
	}


	return 0;
}