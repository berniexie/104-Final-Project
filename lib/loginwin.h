#ifndef LOGINWIN_H
#define LOGINWIN_H

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
#include <QGroupBox>
#include <QRadioButton>
#include <map>
#include <sstream>
#include <string>
#include <exception>
#include <iostream>
#include <fstream>

using namespace std;

class LoginWin : public QMainWindow
{
	Q_OBJECT

	public:
		LoginWin();
		LoginWin(string  *user, deque<WebPage*>& wp_list, map<string, WebPage*>* linktowp, QWidget *parent = 0);
		~LoginWin();

	private slots:
		void create_new_account();
		void check_acc_valid();


	private:
		QGridLayout* lw_main_layout;
		QLineEdit*	username_enter;
		QLineEdit*	password_enter;
		//^ Gotta setEchoModeMode(2)
		QPushButton* createaccount;
		QPushButton* login;

		QWidget        * centerWidget;

		map<string, int> wp_click_counts;
		string username;
		string *user_ptr;
		string password;
		string login_file = "data/login_data.txt";
		deque<WebPage*> *webpage_list_ptr;
		map<string, WebPage*>* links_to_webpages;
};

#endif
