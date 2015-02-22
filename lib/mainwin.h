#ifndef MAINWIN_H
#define MAINWIN_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QMainWindow>
#include <QPushButton>
#include <QMessageBox>
#include <QListWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QString>
#include <string>
#include <set>
#include <list>
#include "searchwin.h"
#include <deque>
#include "WebPage.h"
#include "loginwin.h"
#include <QGroupBox>
#include <QRadioButton>
#include <map>
#include "msort.h"

using namespace std;

class MainWin : public QMainWindow
{
	Q_OBJECT

	public:
		MainWin();
		MainWin(string main_file, string input_adfile, string output_adfile, QWidget *parent = 0);
		~MainWin();

	protected:
		struct ad_storage{
			string _keyword;
			double _price;
			string _company;
			int num_clicks;
		};


	private slots:
		void doSearch();
		void andSearch();
		void orSearch();
		void openLink(QListWidgetItem* item);
		void adClicked(QListWidgetItem* item);
		void showAbout();
		void sort_alpha();
		void sort_pagerank();
		void PageRank(mySet<WebPage*> search_results);
		void Expanded_Results(mySet<WebPage*>& search_results);
		void print_results(string ofile);
		void print_clicks();

	private:
		//layouts
		QGridLayout	   * mainLayout;
		//textboxes
		QLineEdit 	   * searchBar;
		QListWidget    * linksOutput;
		QListWidget    * advert_list;
		//buttons
		QPushButton    * btnSearchWord;
		QPushButton    * btnAbout;
		QPushButton	   * btnQuit;
		QPushButton	   * btnAnd;
		QPushButton    * btnOr;

		QString search_content;
		QString output_links;
		QRadioButton* rbtnAlphabetical;
		QRadioButton* rbtnPageRank;

		QWidget        * centerWidget;

		//variables
		deque<WebPage*> wp_list;
		map<string, WebPage*>* linktowp;
		string new_input;
		map<string, mySet<WebPage*>*> wp_map;
		deque<WebPage*> links_display;
		char sort_method;
		int num_adverts;
			//reading in advertisements;
		deque<ad_storage*> all_adverts;
		mySet<ad_storage*>  searched_ads;
		deque<ad_storage*>  searched_ads_display;
		string output_advert_file;
		string _username;

		//comparator for the advertisement bids
	struct AdComp
	{
		bool operator()(const ad_storage* lhs, const ad_storage* rhs)
		{
			if (lhs->_price>rhs->_price)
			{
				return true;
			}
			else if (lhs->_price==rhs->_price)//breaking ties alphabetically
			{
				if (lhs->_company<rhs->_company)
				{
					return true;
				}
				else
				{
					return false;
				}
			}
			else if (lhs->_price<rhs->_price)
			{
				return false;
			}
		}
	};
	
	struct AdOutputComp
	{
		bool operator()(const ad_storage* lhs, const ad_storage* rhs)
		{
			string company1 = lhs->_company;
			string company2 = rhs->_company;
			for(unsigned int i = 0; i < company1.size(); i++){
				company1[i] = tolower(company1[i]);
			}
			for(unsigned int i = 0; i < company2.size(); i++){
				company2[i] = tolower(company2[i]);
			}
				if (company1<company2)
				{
					return true;
				}
				else
				{
					return false;
				}
		}
	};
};	
	
#endif
