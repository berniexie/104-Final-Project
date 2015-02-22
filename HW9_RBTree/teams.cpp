#include <iostream>
#include <string>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <vector> 

using namespace std;
int main (int arc, char *argv[])
{
	ifstream myfile;
	myfile.open(argv[1]);
	long int counter=0;
	long long skill;
	unsigned long long total_skill=0;
	unsigned long long average_skill;
	unsigned long long partner_skill;
	
	string name;
	string number;
	string line;
	int number_people;
	stringstream holder;
	 unordered_map<long long,string> mymap;
	 unordered_map<string,string>pairs;
	//string *name_holder= new string[number_people];
	vector<string> name_holder;//keeps track of order of names

	while (getline(myfile,line))
	{
			if (counter==0)
			{
				number_people=atoi(line.c_str());
		
			}
			else
			{
			
				holder.clear();
				holder.str(line);
				holder>>name;
				holder>>number;
				skill=atol(number.c_str());
				total_skill=total_skill+skill;
				mymap.emplace(skill,name);
				name_holder.push_back(name);
			}
			
			
			counter++;
			
	}

	average_skill=total_skill/(number_people/2);//finding average skill per pairing

	try
	{
		for (unordered_map<long long,string>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
		{
			
			partner_skill=average_skill-(it->first);//finding the partner with the skill level needed to make the average skill level of the groups
			
			pairs.emplace(  (it->second) , mymap.at(partner_skill)  );//putting the finished pair in another unordered map
			
			
		}
		
	}
	catch (out_of_range& e)
		{
			
			cout<<e.what()<<endl;
		}
	
	for (int j=0; j<name_holder.size(); j++)
	{
			cout<<name_holder[j]<<" "<<pairs.at(name_holder[j])<<endl;
	}
	
	
	
	return 0;
	
}
