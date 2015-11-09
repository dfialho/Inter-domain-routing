#include "frontend/statsdialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
	StatsDialog w;
    w.show();

    return a.exec();
}
