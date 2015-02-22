#ifndef SEARCHWIN_H
#define SEARCHWIN_H

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
#include <QPlainTextEdit>
#include "WebPage.h"
#include "mySet.h"

using namespace std;

class SearchWin : public QMainWindow
{
	Q_OBJECT

	public:
		SearchWin(string input, map<string, WebPage*>* linktowp, QWidget *parent = 0);
		~SearchWin();

	private slots:
		void openNewLink(QListWidgetItem* item);

	private:
		QGridLayout	    * mainLayout;
		QVBoxLayout     * linksLayout;

		QListWidget     * outgoingLinksOutput;
		QListWidget     * incomingLinksOutput;
		QPlainTextEdit	* pageContent; 

		QWidget        * centerWidget;

		//other stuff
		mySet<WebPage*> incomingLinks;
		mySet<WebPage*> outgoingLinks;
		map<string, WebPage*>* link_wp;
};

#endif