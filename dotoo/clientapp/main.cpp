#include "mainwindow.h"
#include <QApplication>
#include <QVBoxLayout>
#include <QPalette>

#include "data/implementation/asyncdatalyr_taskhttp.h"
#include "modelparser/taskjson.h"
#include "models/interface/task.h"

#include "viewmodels/tasklistviewmodel.h"

#include "tasklistview.h"


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
    AsyncDataLyr_Task* dataLayer = new AsyncDataLyr_TaskHttp( "http://localhost:8080",
                                                              "tasks",
                                                              new JsonTaskParser() );
    TaskListViewModel* model = new TaskListViewModel(dataLayer);
    model->getAllTasks();

    QPalette* appPalette = new QPalette();
    appPalette->setColor( QPalette::All, QPalette::Background, QColor("white") );
    TaskListView* view = new TaskListView( QLatin1String("All Tasks"),
                                           *appPalette );
    view->setModel(model);

    QVBoxLayout* layout = new QVBoxLayout();
    layout->setSizeConstraint(QLayout::SetMinAndMaxSize);
    layout->addWidget(view);

    mainW.setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Expanding );
    mainW.setLayout(layout);
    mainW.show();

    return a.exec();
}
