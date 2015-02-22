#include <string>
#include <iostream>
#include <ctype.h>
#include <stdio.h>

using namespace std;

int main()
{
	
	string dummy = "My Name is Bradley";
	
	cout<<dummy<<endl;
	for (int i =0; i<dummy.size(); i++)
	{
		dummy[i]=tolower(dummy[i]);
	}
	cout<<dummy<<endl;
	
	
	
	
	
	
	return 0;
}
