#include "Constants.h"
#include "GameWindow.h"

#include <QApplication>
#include <QMainWindow>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    GameWindow window;
    window.show();

    return app.exec();
}
