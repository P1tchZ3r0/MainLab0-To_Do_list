#include <QApplication>
#include <QFont>
#include "MainWindow.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    QFont defaultFont;
    defaultFont.setFamily("Segoe UI");
    defaultFont.setPointSize(11);
    app.setFont(defaultFont);

    MainWindow window;
    window.show();

    return app.exec();
}