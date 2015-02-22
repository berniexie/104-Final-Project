#include <QApplication>
#include "mainwin.h"
#include <map>
#include <sstream>

int main(int argc, char* argv[])
{
	QApplication app(argc, argv);  

	string input_adfile = argv[2];
	string output_adfile = argv[3];

	string filename = argv[1];
	MainWin* window = new MainWin(filename, input_adfile, output_adfile);

	window->setWindowTitle("Search Engine");
	window->show();

	return app.exec();
}