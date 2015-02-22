#include "mainwin.h"
#include <sstream>
#include <string>
#include <exception>
#include <iostream>
#include "WebPage.h"
#include <deque>
#include <QString>
#include "../lib/msort.h"
#include <ctype.h>
#include <stdio.h>
#include <fstream>

using namespace std;

MainWin::MainWin(){

}

MainWin::MainWin(string main_file, string input_adfile, string output_adfile, QWidget *parent) : QMainWindow(parent)
{
	// allocate memory for all widgets
	mainLayout 					= new QGridLayout;
	QVBoxLayout* buttonLayout	= new QVBoxLayout;
	QHBoxLayout* buttonLayout2	= new QHBoxLayout;
	QHBoxLayout* radiobuttons 	= new QHBoxLayout;
	QVBoxLayout* ads = new QVBoxLayout;
	//adding the advertisement stuff
	QLabel *ad_name = new QLabel(tr("Advertisements: "));
	advert_list = new QListWidget;
	ads->addWidget(ad_name, 0);
	ads->addWidget(advert_list);

	QLabel *radioButtonsLabel 	= new QLabel(tr("Select Arrangement: "));

	rbtnAlphabetical  = new QRadioButton(tr("Alphabetically"));
	rbtnPageRank		= new QRadioButton(tr("by PageRank"));

	rbtnAlphabetical -> setChecked(true);
	radiobuttons->addWidget(radioButtonsLabel, 0);
	radiobuttons->addWidget(rbtnAlphabetical, 1);
	radiobuttons->addWidget(rbtnPageRank, 2);

	QLabel *searchlabel = new QLabel(tr("Search:"));
	searchBar 			= new QLineEdit;
	QLabel *outputlabel = new QLabel(tr("Searched Links:"));
	linksOutput 		= new QListWidget;

	btnSearchWord   = new QPushButton("&Search Word");
	btnAbout      	= new QPushButton("&About");
	btnAnd			= new QPushButton("&And");
	btnOr 			= new QPushButton("&Or");
	btnQuit 		= new QPushButton("&Quit");
	
	centerWidget  = new QWidget(this);
	centerWidget->setLayout(mainLayout);
	this->setCentralWidget(centerWidget);

	buttonLayout->addWidget(btnAnd, 1);
	buttonLayout->addWidget(btnOr, 2);
	buttonLayout->addWidget(btnSearchWord, 4);

	buttonLayout2->addWidget(btnAbout);
	//buttonLayout2->addWidget(btnQuit);

	mainLayout->addWidget(searchlabel, 0, 0);
	mainLayout->addWidget(outputlabel, 1, 0);
	mainLayout->addWidget(searchBar, 0, 1);
	mainLayout->addWidget(linksOutput, 1, 1);
	mainLayout->addLayout(buttonLayout, 1, 2);
	//radiobuttons layout
	mainLayout->addLayout(radiobuttons, 2, 1);
	mainLayout->addLayout(buttonLayout2, 3, 1);
	mainLayout->addLayout(ads, 1, 3);

///////////////////////Parsing, input, etc////////////////////////////

	ifstream in_ad_file(input_adfile);
	output_advert_file = output_adfile;
	ifstream file (main_file);
	if(file.fail() || in_ad_file.fail()){
		QMessageBox::information(this, tr("Error"), tr("File Failed"));
		this->close();
	}
	//this is a deque of webpages
	linktowp = new map<string, WebPage*>; //a map linking address links to WebPage pointers
	string filename;
	while(!file.eof()){
		file >> filename;
		WebPage* wp = new WebPage(filename); // in the data file?
		wp->set_clicks(0);
		//adding to the map
		linktowp->insert(pair<string, WebPage*>(filename, wp));
		wp_list.push_back(wp);
	}

	for(unsigned int i = 0; i < wp_list.size(); i++){
		wp_list[i]->parse(linktowp);
	}

	in_ad_file >> num_adverts;
	in_ad_file.ignore(1);
	string line_in_file;
	for(int i = 0; i < num_adverts; i++){
		getline(in_ad_file, line_in_file);
		stringstream ss;
		ss << line_in_file;
		string keyword;
		ss >> keyword;
		double price;
		ss >> price;
		string company;
		while(!ss.eof()){
			string word;
			ss >> word;
			word.push_back(' ');
			company += word;
		}
		//coverting keyword to all lowercase
		for (int j=0; j<keyword.size(); j++)
		{
			keyword[j]=tolower(keyword[j]);
		}
		ad_storage* advertisement = new ad_storage;
		advertisement->_keyword = keyword;
		advertisement->_price = price;
		advertisement->_company = company;
		advertisement->num_clicks = 0;
		//all_adverts stores the structs
		all_adverts.push_back(advertisement);
		//*_username = "";
	}

	//for(int i = 0; i < num_adverts; i++)
	//	cout << "keyword: " << all_adverts[i]->_keyword << " price: " << all_adverts[i]->_price << " company: " << all_adverts[i]->_company << endl;

	////////////////////////creating login_win////////////////////////////
	LoginWin* lgwin = new LoginWin(&_username, wp_list, linktowp);
	lgwin->setWindowFlags(Qt::WindowStaysOnTopHint);
	//cout<<"before show"<<endl;
	lgwin->show();
	//cout<<"after show"<<endl;
	/*display += ", welcome!";
	QLabel* welcome_msg = new QLabel(QString::fromStdString(display));
	mainLayout->addWidget(welcome_msg, 0, 3);*/
	//cout<<*_username<<endl;

///////////////////////////Connections//////////////////////////
	connect(btnSearchWord, SIGNAL(clicked()), this, SLOT(doSearch()),Qt::UniqueConnection);
	connect(btnAnd, SIGNAL(clicked()), this, SLOT(andSearch()),Qt::UniqueConnection);
	connect(btnOr, SIGNAL(clicked()), this, SLOT(orSearch()),Qt::UniqueConnection);
	connect(btnAbout, SIGNAL(clicked()), this, SLOT(showAbout()),Qt::UniqueConnection);

}

MainWin::~MainWin()
{

}

void MainWin::showAbout(){
	QMessageBox::information(this, tr("About"), tr("Qt Search Engine for CSCI 104 Project made by Bernard Xie"));
}

void MainWin::doSearch(){
	advert_list->clear();
	new_input = (searchBar->text()).toStdString();
	//converting all characters in new_input to lower case;
	for (unsigned int j=0; j<new_input.size(); j++)
	{
		new_input[j]=tolower(new_input[j]);
	}

	linksOutput->clear();
	mySet<WebPage*>* contained_wp = new mySet<WebPage*>;
	bool found = false;
	//inserting webpages that have the word
	for (unsigned int i = 0; i < wp_list.size(); i++){
		if(wp_list[i]->allWords().contains(new_input)){
			contained_wp->insert(wp_list[i]);
			found = true;
			//testing, printing the webpage added
		}
	}

	for (unsigned int j = 0; j < all_adverts.size(); j++){
		if(new_input == all_adverts[j]->_keyword && !searched_ads.contains(all_adverts[j])){
			cout << new_input << endl;
			searched_ads.insert(all_adverts[j]);
			}
		}

	mySet<ad_storage*>::iterator it0;
	for(it0 = searched_ads.begin(); it0 != searched_ads.end(); ++it0){
		searched_ads_display.push_back(*it0);
	}
	
	//sorting searched_ads_display
	AdComp ad_compare;
	mergeSort<ad_storage*,AdComp>(searched_ads_display, ad_compare);
	
	
////////////////STILL GOTTA SORT THIS ISH/////////////////////////////////

	//printing the ads
	for(unsigned int i = 0; i < searched_ads_display.size(); i++){
		//cout << searched_ads_display[i]->_company << endl;
		advert_list->addItem(QString::fromStdString(searched_ads_display[i]->_keyword + "-" + searched_ads_display[i]->_company));
	}

	if (found == false){
		QMessageBox::information(this, tr("Error"), tr("Did not find that word in any webpage"));
	}

	Expanded_Results(*contained_wp);

	wp_map.insert(pair<string, mySet<WebPage*>*>(new_input, contained_wp));

	mySet<WebPage*>* input_map = wp_map[new_input];
	mySet<WebPage*>::iterator it1;
	for(it1 = input_map->begin(); it1 != input_map->end(); ++it1){			
		links_display.push_back(*it1);
	}

	//deque<WebPage*> links_display

	//calling the pagerank function
	PageRank(*contained_wp);

	//sorting the list
	if(rbtnAlphabetical->isChecked()){
		sort_alpha();
	}
	if(rbtnPageRank->isChecked()){
		sort_pagerank();
	}

	//links_display will by now, so just add everything to linksOutput
	for(unsigned int i = 0; i < links_display.size(); i++){
		QString fname = QString::fromStdString(links_display[i]->filename());
		linksOutput->addItem(fname);
	}

	searchBar->clear();
	new_input.clear();
	searched_ads_display.clear();
	searched_ads.clear();
	connect(linksOutput, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(openLink(QListWidgetItem*)),Qt::UniqueConnection);
	connect(advert_list, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(adClicked(QListWidgetItem*)),Qt::UniqueConnection);
	//gotta connect ad signals

	links_display.clear();
}

void MainWin::andSearch(){
	//cout<<"i'm in and search"<<endl;
	advert_list->clear();
	new_input = (searchBar->text()).toStdString();
	//converting all characters in new_input to lower case;
	for (unsigned int j=0; j<new_input.size(); j++)
	{
		new_input[j]=tolower(new_input[j]);
	}
	//searchBar->clear();
	linksOutput->clear();
	string input;
	deque<string> storage;
	//inserting each word to be searched in the dque
	for (unsigned int i = 0; i < new_input.size(); i++){
		input.push_back(new_input[i]);
		if(new_input[i] == ' '){
			input.pop_back();
			storage.push_back(input);
			input.clear();
		}
	}
	storage.push_back(input);
	input.clear();
	
	for (unsigned int i =0; i < storage.size(); i++){
		mySet<WebPage*>* contained_wp = new mySet<WebPage*>;
		string word = storage[i];
					//cout << "iterating for: " << word << endl;
		for(unsigned int j = 0; j < wp_list.size(); j++ ){
			//cout << "iterating" << endl;
			if(wp_list[j]->allWords().contains(word)){
				//cout << "found a webpage that contains the word: " << word << endl;
				contained_wp->insert(wp_list[j]);
					//testing, printing the webpage added
			}
		}
		wp_map.insert(pair<string, mySet<WebPage*>*>(word, contained_wp));
	}
				
	mySet<WebPage*> intersect_set = *wp_map[storage[0]];
	for (unsigned int i = 1; i < storage.size(); i++ ){
		intersect_set = intersect_set.setIntersection(*wp_map[storage[i]]);		
	}

	Expanded_Results(intersect_set);

	if (intersect_set.size() == 0){
		QMessageBox::information(this, tr("Error"), tr("Did find any intersecting sets"));
	}

	mySet<WebPage*>::iterator it;
	for(it = intersect_set.begin(); it != intersect_set.end(); ++it){
		//QString fname = QString::fromStdString(it->filename());
		//WebPage* webpage = it;
		links_display.push_back(*it);
		//linksOutput->addItem(fname);
	}

	//sorting the list
	PageRank(intersect_set);

	//sorting the list
	if(rbtnAlphabetical->isChecked()){
		sort_alpha();
	}
	if(rbtnPageRank->isChecked()){
		sort_pagerank();
	}

	//links_display will by now, so just add everything to linksOutput

	for(unsigned int i = 0; i < links_display.size(); i++){
		QString fname = QString::fromStdString(links_display[i]->filename());
		linksOutput->addItem(fname);
	}
//ADVERTISEMENT DISPLAY STUFF
for (int i=0; i<storage.size();i++)
{
	for (unsigned int j = 0; j < all_adverts.size(); j++){
		if(storage[i] == all_adverts[j]->_keyword && !searched_ads.contains(all_adverts[j])){
			cout << storage[i] << endl;
			searched_ads.insert(all_adverts[j]);
			}
		}
}

	mySet<ad_storage*>::iterator it0;
	for(it0 = searched_ads.begin(); it0 != searched_ads.end(); ++it0){
		searched_ads_display.push_back(*it0);
	}
	AdComp ad_compare;
	mergeSort<ad_storage*,AdComp>(searched_ads_display, ad_compare);
////////////////STILL GOTTA SORT THIS ISH/////////////////////////////////

	//printing the ads
	for(unsigned int i = 0; i < searched_ads_display.size(); i++){
		cout << searched_ads_display[i]->_company << endl;
		advert_list->addItem(QString::fromStdString(searched_ads_display[i]->_company));
	}
	searchBar->clear();
	new_input.clear();
	searched_ads_display.clear();
	searched_ads.clear();
	connect(linksOutput, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(openLink(QListWidgetItem*)),Qt::UniqueConnection);
	connect(advert_list, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(adClicked(QListWidgetItem*)),Qt::UniqueConnection);
	links_display.clear();
}

void MainWin::orSearch(){
	cout<<"in OR search"<<endl;
	advert_list->clear();
	new_input = (searchBar->text()).toStdString();
	//converting all characters in new_input to lower case;
	for (unsigned int j=0; j<new_input.size(); j++)
	{
		new_input[j]=tolower(new_input[j]);
	}
	//searchBar->clear();
	linksOutput->clear();
	string input;
	//storage stores the words 
	deque<string> storage;
	for (unsigned int i = 0; i < new_input.size(); i++){
		input.push_back(new_input[i]);
		if(new_input[i] == ' '){
			input.pop_back();
			storage.push_back(input);
			input.clear();
		}
	}
	storage.push_back(input);
	input.clear();

	for (unsigned int i =0; i < storage.size(); i++){
		mySet<WebPage*>* contained_wp = new mySet<WebPage*>;
		string word = storage[i];
					//cout << "iterating for: " << word << endl;
		for(unsigned int j = 0; j < wp_list.size(); j++ ){
			//cout << "iterating" << endl;
			if(wp_list[j]->allWords().contains(word)){
				//cout << "found a webpage that contains the word: " << word << endl;
				contained_wp->insert(wp_list[j]);
					//testing, printing the webpage added
			}
		}
		wp_map.insert(pair<string, mySet<WebPage*>*>(word, contained_wp));
	}
				
	mySet<WebPage*> union_set = *wp_map[storage[0]];
	for (unsigned int i = 1; i < storage.size(); i++ ){
		union_set = union_set.setUnion(*wp_map[storage[i]]);		
	}
	if (union_set.size() == 0){
		QMessageBox::information(this, tr("Error"), tr("Did find any intersecting sets"));
	}

	Expanded_Results(union_set);

	mySet<WebPage*>::iterator it;
	for(it = union_set.begin(); it != union_set.end(); ++it){
		//QString fname = QString::fromStdString(it->filename());
		//WebPage* webpage = it;
		links_display.push_back(*it);
		//linksOutput->addItem(fname);
	}

	//sorting the list
	PageRank(union_set);

	//sorting the list
	if(rbtnAlphabetical->isChecked()){
		sort_alpha();
	}
	if(rbtnPageRank->isChecked()){
		sort_pagerank();
	}

	//links_display will by now, so just add everything to linksOutput

	for(unsigned int i = 0; i < links_display.size(); i++){
		QString fname = QString::fromStdString(links_display[i]->filename());
		linksOutput->addItem(fname);
	}
//ADVERTISEMENT DISPLAY STUFF
for (int i=0; i<storage.size();i++)
{
	for (unsigned int j = 0; j < all_adverts.size(); j++){
		if(storage[i] == all_adverts[j]->_keyword && !searched_ads.contains(all_adverts[j])){
			cout << storage[i] << endl;
			searched_ads.insert(all_adverts[j]);
			}
		}
}

	mySet<ad_storage*>::iterator it0;
	for(it0 = searched_ads.begin(); it0 != searched_ads.end(); ++it0){
		searched_ads_display.push_back(*it0);
	}
	AdComp ad_compare;
	mergeSort<ad_storage*,AdComp>(searched_ads_display, ad_compare);

	//printing the ads
	for(unsigned int i = 0; i < searched_ads_display.size(); i++){
		cout << searched_ads_display[i]->_company << endl;
		advert_list->addItem(QString::fromStdString(searched_ads_display[i]->_company));
	}
	searchBar->clear();
	new_input.clear();
	searched_ads_display.clear();
	searched_ads.clear();


	connect(linksOutput, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(openLink(QListWidgetItem*)), Qt::UniqueConnection);
	connect(advert_list, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(adClicked(QListWidgetItem*)),Qt::UniqueConnection);
	links_display.clear();
}

void MainWin::openLink(QListWidgetItem* item){
	//cout<<"in open link"<<endl;
	QString input = item->text();
	string link = input.toStdString();
	SearchWin* win = new SearchWin(link, linktowp, this);
	//update number of clicks
	linktowp->at(link)->increment_clicks();
	cout << linktowp->at(link)->get_clicks() << endl;
	//testing username
	//cout << "username is: " << _username << endl;
	print_clicks();
	win -> show();
}
//slot for when an advertisment gets clicked
void MainWin::adClicked(QListWidgetItem* item)
{
	QString input= item->text();
	string whole_text=input.toStdString();
	int position;
	for (int j=0; j<whole_text.size(); j++)
	{
		if (whole_text[j]=='-')
		{
			position=j;
		}
	}
	string keyword=whole_text.substr(0,position);
	//cout<<"keyword is "<<keyword<<endl;
	string company=whole_text.substr(position+1,whole_text.size()-1);
	//cout<<"company is "<<company<<endl;
	string link = "Visited Website of ";
	link += company;


	for (int i=0; i<all_adverts.size(); i++)
	{
		if((all_adverts[i]->_company)==company && (all_adverts[i]->_keyword)==keyword)
		{
			//cout<<"adjusting num clicks"<<endl;
			cout<<all_adverts[i]->_keyword<<" "<<all_adverts[i]->_price<<endl;
			all_adverts[i]->num_clicks=(all_adverts[i]->num_clicks)+1;
			//break;
		}
	}
	print_results(output_advert_file);

	QMessageBox::information(this, tr("Advertisement"), QString::fromStdString(link));
}
void MainWin::sort_alpha(){
	this->sort_method = 'a';
	AlphaStrComp compObj;
	mergeSort<WebPage*, AlphaStrComp>(links_display, compObj);


}

void MainWin::sort_pagerank(){
	this->sort_method = 'p';
	RankComp compObj;
	mergeSort<WebPage*, RankComp>(links_display, compObj);

}

void MainWin::Expanded_Results(mySet<WebPage*>& search_results){
	//mySet<WebPage*> viable_pages = search_results;
	mySet<WebPage*>::iterator it1;
	for(it1 = search_results.begin(); it1 != search_results.end(); ++it1){
		WebPage* wp = *it1;
		mySet<WebPage*> inlinks = wp->allIncomingLinks();
		mySet<WebPage*>::iterator it2;
		for(it2 = inlinks.begin(); it2 != inlinks.end(); ++it2){
			if (!search_results.contains(*it2))
				search_results.insert(*it2);
		}
		mySet<WebPage*> oglinks = wp->allOutgoingLinks();
		mySet<WebPage*>::iterator it3;
		for(it3 = oglinks.begin(); it3 != oglinks.end(); ++it3){
			if (!search_results.contains(*it3))
				search_results.insert(*it3);
		}
	}
	//return viable_pages;
}

void MainWin::PageRank(mySet<WebPage*> viable_pages){
	vector<WebPage*> vlinks;
	mySet<WebPage*>::iterator it4;
	for(it4 = viable_pages.begin(); it4 != viable_pages.end(); ++it4){
		//creating a vector of webpage links
		vlinks.push_back(*it4);
	}

	for(unsigned int i = 0; i < vlinks.size(); i++){
		double rank_value = 1.0/viable_pages.size();
		vlinks[i]->set_pagerank(rank_value);
	}

	double** adj_list = new double*[viable_pages.size()];
	for(unsigned int i = 0; i < viable_pages.size(); i++){
		adj_list[i] = new double[viable_pages.size()];
	}


	for(unsigned int i = 0; i < vlinks.size(); i++){
		mySet<WebPage*> ogoinglinks = vlinks[i]->allOutgoingLinks();
		bool has_outgoing_links = false;
		for(unsigned int j = 0; j < vlinks.size(); j++){
				if (ogoinglinks.contains(vlinks[j])){
					adj_list[j][i] = 1.0/ogoinglinks.size();
					has_outgoing_links = true;
				}
				else{
					adj_list[j][i] = 0.0;
				}
		}
		if(has_outgoing_links == false){
			for(unsigned int k = 0; k < vlinks.size(); k++){
				adj_list[k][i] = 1.0/vlinks.size();
			}
		}
	}
	
	vector<double> pr_list;
	for(unsigned int i = 0; i < vlinks.size(); i++){
		pr_list.push_back(1.0/vlinks.size());
	}

	double a = 0.15;

	//running simulations
	for(unsigned int itr = 0; itr < 30; itr ++){
		for (unsigned int i = 0; i < pr_list.size(); i++){
			double sum = 0.0;
			for(unsigned int j = 0; j < vlinks.size(); j++){
				sum = sum + (adj_list[i][j])*(pr_list[j]);
			}
			pr_list[i] = sum*a + ((1-a)/vlinks.size());
		}
	}

	for(unsigned int i = 0; i < vlinks.size(); i++){
		vlinks[i]->set_pagerank(pr_list[i]);
	}
}

void MainWin::print_results(string ofile){
	fstream outfile;
	outfile.open(ofile, std::ofstream::out | std::ofstream::trunc);
	bool repeat=0;
	deque<ad_storage*> print_adverts = all_adverts;
	AdOutputComp ad_compare;
	mergeSort<ad_storage*,AdOutputComp>(print_adverts, ad_compare);

	for(unsigned int i = 0; i < print_adverts.size(); i++){
		repeat=0;
		double price = (print_adverts[i]->num_clicks)*(print_adverts[i]->_price);
		for (unsigned int j=0; j<print_adverts.size(); j++)
		{
			if (print_adverts[i]->_company==print_adverts[j]->_company && i!=j && i<j)
			{
				//repeat=1;
				//print_adverts[i]->num_clicks=print_adverts[i]->num_clicks+print_adverts[j]->num_clicks;
				price=((print_adverts[i]->num_clicks)*(print_adverts[i]->_price)) + ((print_adverts[j]->num_clicks)*(print_adverts[j]->_price));
			}
			else if (print_adverts[i]->_company==print_adverts[j]->_company && i!=j && i>j)
			{
				repeat=1;
			}
		}
		if(repeat==0)
		{
		string output = print_adverts[i]->_company;
		outfile << output << endl;
		
		output = to_string(price);
		outfile << output << endl;
		outfile<<endl;
		}
	}
}

void MainWin::print_clicks(){
	string login_data_file = "data/login_data.txt";
	fstream data_ofile;
	data_ofile.open(login_data_file, fstream::in | fstream::out);
	while(!data_ofile.eof()){
		string data_word;
		data_ofile >> data_word;
		if(data_word == "username"){
			data_ofile >> data_word;
			if(data_word == _username){
				data_ofile>>data_word;
				data_ofile>>data_word;
				data_ofile.ignore(1, '\n');
				for(int i =0; i < wp_list.size(); i++){
					data_ofile<<(wp_list.at(i))->filename()<<" "<<(wp_list.at(i))->get_clicks()<<endl;
				}
			}
		}
	}

}
