#include "searchwin.h"

using namespace std;

SearchWin::SearchWin(string input, map<string, WebPage*>* linktowp, QWidget *parent) : QMainWindow(parent)
{
	//allocating new widgets and layouts
	link_wp = linktowp;
	mainLayout = new QGridLayout;
	linksLayout = new QVBoxLayout;

	QLabel *outgoing_label = new QLabel(tr("Outgoing Links:"));
	QLabel *incoming_label = new QLabel(tr("Incoming Links:"));
	outgoingLinksOutput = new QListWidget;		
	incomingLinksOutput = new QListWidget;
	pageContent = new QPlainTextEdit;
		pageContent->setReadOnly(true);

	//allocating the center widget
	centerWidget  = new QWidget(this);
	centerWidget->setLayout(mainLayout);
	this->setCentralWidget(centerWidget);

	linksLayout->addWidget(outgoing_label);
	linksLayout->addWidget(outgoingLinksOutput);
	linksLayout->addWidget(incoming_label);
	linksLayout->addWidget(incomingLinksOutput);

	mainLayout->addWidget(pageContent, 0, 0);
	mainLayout->addLayout(linksLayout, 0, 1);

	//attaching signals and slots to the incoming/outputlink outputs
	QString text_content = QString::fromStdString(linktowp->at(input)->get_content());
	pageContent->setPlainText(text_content);

	incomingLinks = linktowp->at(input)->allIncomingLinks();
	outgoingLinks = linktowp->at(input)->allOutgoingLinks();

	//if(sorttype == 'a'){
	//if(sorttype == 'p'){

	mySet<WebPage*>::iterator it1, it2;
	for(it1 = incomingLinks.begin(); it1 != incomingLinks.end(); ++it1){
		QString fname1 = QString::fromStdString((*it1)->filename());
		incomingLinksOutput ->addItem(fname1);
		
	}

	
	for(it2 = outgoingLinks.begin(); it2 != outgoingLinks.end(); ++it2){
		QString fname2 = QString::fromStdString((*it2)->filename());
		outgoingLinksOutput ->addItem(fname2);
		
	}
	

	connect(incomingLinksOutput, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(openNewLink(QListWidgetItem*)),Qt::UniqueConnection);
	connect(outgoingLinksOutput, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(openNewLink(QListWidgetItem*)),Qt::UniqueConnection);
	

}

SearchWin::~SearchWin(){

}

void SearchWin::openNewLink(QListWidgetItem* item){
	QString input = item->text();
	string link = input.toStdString();
	SearchWin* win = new SearchWin(link, link_wp, this);
	win -> show();
}
