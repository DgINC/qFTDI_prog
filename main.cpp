#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    if ( getuid() != 0 ){
        w.msgBox.setText("Root privileges are required for running.");
        w.msgBox.exec();
        a.quit();
        return EXIT_FAILURE;
    }

    return a.exec();
}

void MainWindow::getAllDevices(const int vid, const int pid) {
    QMap<QString, Context*> ftdi_list;

    Context* cftdi = new Context();
    List* list = List::find_all(*cftdi, vid, pid);

    for (List::iterator it = list->begin(); it != list->end(); it++) {
        ftdi_list.insertMulti(QString("Manufacturer: %1 Devtype: %2 Serial: %3").arg(convert(it->vendor())).arg(convert(it->description())).arg(convert(it->serial())), &*it);
        if(it->open() != 0) {
            error_Handler((const char *)"Device open failed", 0, ERRR);
        }
        it->close();
    }
    delete list;
    setupTree(&ftdi_list);
}

void MainWindow::getDevPins(Context* ctx) {
    unsigned char* pins;
    if(ctx->is_open()){ ctx->close(); }
    ctx->open();
    ctx->read_pins(pins);
    ctx->close();
    qDebug() << pins;
}

QString MainWindow::convert(const std::string& s)
{
   return QString::fromStdString(s);
}
