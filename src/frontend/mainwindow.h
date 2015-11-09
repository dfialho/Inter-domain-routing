#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <backend/Network.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

private slots:
	void onButtonLoadClicked();
	void onButtonStartClicked();

private:
	Ui::MainWindow *ui;
	std::shared_ptr<Network> network;
};

#endif // MAINWINDOW_H
