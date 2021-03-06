#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    statusLabel = new QLabel(this);
    ui->barabar->addPermanentWidget(statusLabel);
    connect(this, SIGNAL(window_loaded()), this, SLOT(Initialization()));
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::setupTree(QMap<QString, Context*> *all_ftdi) {
    QMap<QString, Context*>::const_iterator i = all_ftdi->constBegin();
    QList<QTreeWidgetItem*> items;

    while (i != all_ftdi->constEnd()) {
        QTreeWidgetItem *twi = new QTreeWidgetItem();
        twi->setText(0, i.key());
        twi->setData(0, Qt::UserRole, QVariant::fromValue(i.value()));
        items.append(twi);
        ++i;
    }
    ui->treeWidget->clear();
    ui->treeWidget->insertTopLevelItems(0, items);
}

void MainWindow::showEvent(QShowEvent *ev) {
    QMainWindow::showEvent(ev);
    emit window_loaded();
}

void MainWindow::on_pushButton_clicked() {
    getAllDevices();
}

void MainWindow::Initialization() {
    getAllDevices();
}

void MainWindow::on_treeWidget_itemClicked(QTreeWidgetItem *item) {
    QVariant qv = item->data(0, Qt::UserRole);
    Context* ctx = qv.value<Context*>();
    qDebug() << ctx;
    getDevPins(ctx);
}

void MainWindow::error_Handler(const char* mesg, int errnum, error_layer el) {
    switch (el) {
        case DEBG:
            ui->textBrowser->append(QString("<font color=\"#0079b5\">Debug: %1 Code:(%2)</font>").arg(mesg).arg(errnum));
            break;
        case INFO:
            ui->textBrowser->append(QString("<font color=\"#00b518\">Info: %1 Code:(%2)</font>").arg(mesg).arg(errnum));
            break;
        case WARN:
            ui->textBrowser->append(QString("<font color=\"#b58818\">Warning: %1 Code:(%2)</font>").arg(mesg).arg(errnum));
            break;
        case ERRR:
            ui->textBrowser->append(QString("<font color=\"#b51818\">Error: %1 Code:(%2)</font>").arg(mesg).arg(errnum));
            break;
        case CRIT:
            ui->textBrowser->append(QString("<font color=\"#ff0000\">Critical: %1 Code:(%2)</font>").arg(mesg).arg(errnum));
            break;
        default:
            ui->textBrowser->append(QString("Message: %1 Code:(%2)").arg(mesg).arg(errnum));
            break;
    }
}
