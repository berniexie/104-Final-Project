#ifndef MSORT_H
#define MSORT_H
#include <iostream>
#include <deque>
using namespace std;

template<class T, class Comparator>
void mergeSort(deque<T>& myarray, Comparator comp)
{
	int length=myarray.size();
	int mid=length/2;
	if(length<2)
		return;
	deque<T> left(mid);
	deque<T> right(length-mid);
	for(int i=0; i<(mid); i++)
		{left[i]=myarray[i];
		}
		cout << endl;
	for(int i=0; i<(length-mid); i++)
	{
		right[i]=myarray[i+mid];
	}
	mergeSort<T, Comparator>(left, comp);
	mergeSort<T, Comparator>(right, comp);
	merge(left, right, myarray, comp);


	
}
template<class T, class Comparator>
void merge(deque<T>& left, deque<T>& right, deque<T>& myarray, Comparator comp)
{
	 //int lengthMyArray=myarray.size();
	 int lengthLeft=left.size();
	 int lengthRight=right.size();
	 int i=0;
	 int j=0;
	 int k=0;
	 while(i<lengthLeft && j<lengthRight)
	 {
	 	if(comp(left[i], right[j]))
	 	{
	 		myarray[k]=left[i];
	 		++i;
	 	}
	 	else
	 	{
	 		myarray[k]=right[j];
	 		++j;
	 	}
	 	++k;
	 }
	 
	 while(i<lengthLeft)
	 {
		myarray[k]=left[i];
		++i; ++k;
	 }
	 while(j<lengthRight)
	 {
	 	myarray[k]=right[j];
	 	++j; ++k;
	 }
	 
}
#endif