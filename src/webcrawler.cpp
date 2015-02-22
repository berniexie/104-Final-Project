#include "../lib/mySet.h"
#include "../webpage/WebPage.h"
#include "../src/WebPage.cpp"
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

void scan(WebPage* webpage, vector<WebPage*>*, mySet<string>*);

int main(int argc, char* argv[]){
	string incoming_filename = argv[1];
	string outgoing_filename = argv[2];
	string filename;
	vector<WebPage*> wp_list;
	mySet<string> wp_names;

	fstream file (incoming_filename);
	fstream ofile;
	ofile.open(outgoing_filename, std::ofstream::out | std::ofstream::trunc);


	if (file.bad() || ofile.bad()){
		cout << "Either your input or your output file has failed." << endl;
		return 0;
	}


	while(!file.eof()){
		//string webpage_file = "data/";
		file >> filename;
		//webpage_file.append(filename);
		//cout << "about to try: " << filename << endl;
		if(!wp_names.contains(filename)){
			//cout << "about to try: " << filename << endl;
			WebPage* wp = new WebPage(filename); // in the data file?
			wp_list.push_back(wp);
			wp_names.insert(filename);
			scan(wp, &wp_list, &wp_names);
		}
	}

	for(int i = 0; i < wp_list.size(); i++){
		ofile << wp_list[i]->filename();
		ofile << endl;
	}

	 file.close();
	 ofile.close();
	return 0;
}

void scan(WebPage* webpage, vector<WebPage*>* WpList, mySet<string>* WpNames){
	  //cout << "scanning: " << webpage->filename() << endl;
	  string link = "";
	  string content = webpage->get_contentwlinks();
	  //cout << content << endl;
	  string word, anchor;
	  bool is_link = false, is_anchor = false;
	  for (unsigned int i = 0; i < content.length(); i++){
	    if (content[i] == '(' && content[i-1] == ']'){
	      is_link = true;
	    }
	    if (content[i] == ')'){
	    	//cout << "found link!" << endl;
	      is_link = false;
	    }

	    //Adding links to a set of webpage names
	    if (is_link == true && content[i] == '('){
	      for (int j = i+1; content[j] != ')'; j++){
	        link.push_back(content[j]);
	      }
	      //cout << "found link: " << link << endl;
	      if (!WpNames->contains(link)){
	      	vector<string> list;
	      	WpNames->insert(link);
	      	WebPage* wp = new WebPage(link);
	      	WpList->push_back(wp);
	      	scan(wp, WpList, WpNames);
	      }
	      link.clear();
	    }
	  }
}