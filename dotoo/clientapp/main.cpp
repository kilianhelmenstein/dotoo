#include "mainwindow.h"
#include <QApplication>
#include <QPushButton>
#include <QDate>
#include <QVBoxLayout>
#include <QScrollArea>

#include "data/implementation/asyncdatalyr_taskhttp.h"
#include "modelparser/taskjson.h"
#include "models/interface/task.h"

#include "viewmodels/tasklistviewmodel.h"

#include "views/tasklistview.h"


using namespace Dotoo;
using namespace Dotoo::GUI;
using namespace Dotoo::Data;
using namespace Dotoo::ModelParser;


int main(int argc, char *argv[])
{
    using namespace Dotoo;

    QApplication a(argc, argv);

    QWidget mainW;

    /* Dependencies used by MVC's: */
    BytestreamTaskParser* parser = new JsonTaskParser();
    AsyncDataLyr_Task* dataLayer = new AsyncDataLyr_TaskHttp( "http://localhost:8080",
                                                              "tasks",
                                                              parser );

    TaskListViewModel* model = new TaskListViewModel(dataLayer);

    QPalette defaultPalette;
    TaskListView* view = new TaskListView(defaultPalette);
    view->setModel(model);

    model->getAllTasks();

    QVBoxLayout layout;
    layout.addWidget(view);
    mainW.setLayout(&layout);
    mainW.show();
    return a.exec();
}
