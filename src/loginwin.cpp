#include "loginwin.h"

using namespace std;

LoginWin::LoginWin(){

}

LoginWin::LoginWin(string* user, deque<WebPage*>& wp_list, map<string, WebPage*>* linktowp, QWidget *parent) : QMainWindow(parent)
{
	///////////////////////////Qt Implementaion/////////////////////////////
	lw_main_layout = new QGridLayout;
	username_enter = new QLineEdit;
	password_enter = new QLineEdit;
	password_enter->setEchoMode(QLineEdit::Password); //making it display stars
	
	createaccount = new QPushButton(tr("Create Account"));
	login 		  = new QPushButton(tr("Login"));

	QLabel* login_label = new QLabel(tr("Enter Username:"));
	QLabel* pw_label = new QLabel(tr("Enter Password:"));

	centerWidget = new QWidget(this);
	centerWidget->setLayout(lw_main_layout);
	this->setCentralWidget(centerWidget);

	lw_main_layout->addWidget(login_label, 0, 0);
	lw_main_layout->addWidget(pw_label, 0, 1);
	lw_main_layout->addWidget(username_enter, 1, 0);
	lw_main_layout->addWidget(password_enter, 1, 1);
	lw_main_layout->addWidget(createaccount, 2, 0);
	lw_main_layout->addWidget(login, 2, 1);

	///////////////////////////Initialization Code//////////////////////////
	//display_account = display_username;

	webpage_list_ptr=&wp_list;
	links_to_webpages= linktowp;
	user_ptr=user;
	connect(createaccount, SIGNAL(clicked()), this, SLOT(create_new_account()));
	connect(login, SIGNAL(clicked()), this, SLOT(check_acc_valid()));
}

LoginWin::~LoginWin(){

}

void LoginWin::create_new_account(){
	username = (username_enter->text()).toStdString();
	password = (password_enter->text()).toStdString();
	cout<<username<<" "<<password<<endl;
	
	bool already_exist=0;

	fstream login_data;
	login_data.open (login_file, fstream::in | fstream::out | fstream::app);

	if(username.size() <= 5 || password.size() <= 5){
		QMessageBox::information(this, tr("Error"), tr("Username and password must be over 5 characters"));
		username_enter->clear();
		password_enter->clear();
		return;
	}
	
	while(!login_data.eof()){
		string parsing;
		login_data >> parsing;
		if(parsing == "username"){
			login_data >> parsing;

			if(parsing == username)
			{
				QMessageBox::information(this, tr("error"), tr("Invalid Username, please use a different one"));
				return;
				already_exist=1;
			}
		}
	}
	
	
	if(already_exist==0)
	{

		login_data.clear();

		login_data<<"username "<<username<<endl;
		login_data<<"password "<<password<<endl;
		for (int i=0; i<webpage_list_ptr->size(); i++)
		{	
			login_data<<(webpage_list_ptr->at(i))->filename()<<" "<<(webpage_list_ptr->at(i))->get_clicks()<<endl;
		}
		login_data<<endl;
		//user_ptr=user;
		*user_ptr=username;
	}
	cout<<"checkpoint1"<<endl;
	//*display_account = username;
	username_enter->clear();
	password_enter->clear();
	//this->destroy();
	string display = "Welcome " + username;
	QMessageBox::information(this, tr("Welcome!"), QString::fromStdString(display));
	this->close();
	cout<<"checkpoint2"<<endl;
	return;
}

void LoginWin::check_acc_valid(){
	cout<<"in check acc valid"<<endl;
	username = (username_enter->text()).toStdString();
	password = (password_enter->text()).toStdString();
	fstream login_data;
	login_data.open (login_file, fstream::in | fstream::out);

	bool already_exist=0;
	while(!login_data.eof()){
			string parsing;
			login_data >> parsing;
			if(parsing == "username"){
				login_data >> parsing;
				if(parsing == username)
				{
					login_data >> parsing;
					if(parsing == "password"){
						login_data >> parsing;
						if(parsing == password){
							for (int i=0; i<webpage_list_ptr->size(); i++)
							{
								string wp_name;
								int wp_click_count;
								login_data >> wp_name;
								login_data >> wp_click_count;
								links_to_webpages->at(wp_name)->set_clicks(wp_click_count);
							}
							//user_ptr=user;
							*user_ptr=username;
							string display = "Welcome back, " + username;
							QMessageBox::information(this, tr("Welcome!"), QString::fromStdString(display));
							already_exist=1;
							this->close();
						}
					}
				}
			}
		}
	
	
	if(already_exist==0)
	{
		QMessageBox::information(this, tr("error"), tr("Couldn't find your username, or your password was incorrect, try again"));

	}

	username_enter->clear();
	password_enter->clear();
	//this->destroy();
	return;
}
