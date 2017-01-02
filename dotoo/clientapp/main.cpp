#include "mainwindow.h"
#include <QApplication>
#include <QVBoxLayout>
#include <QPalette>

#include "data/implementation/asyncdatalyr_taskhttp.h"
#include "modelparser/taskjson.h"
#include "models/interface/task.h"

#include "viewmodels/tasklistviewmodel.h"

#include "tasklistview.h"
#include "tasklistctrl.h"
#include "taskeditview.h"
#include "taskeditctrl.h"

#include "custommenubar.h"


using namespace Dotoo;
using namespace Dotoo::GUI;
using namespace Dotoo::Data;
using namespace Dotoo::ModelParser;


int main(int argc, char *argv[])
{
    using namespace Dotoo;

    QApplication a(argc, argv);

    QPalette* appPalette = new QPalette();
    appPalette->setColor( QPalette::All, QPalette::Background, QColor("grey") );

    CustomGUI::CustomMenuBar menuBar( CustomGUI::CustomMenuBar::Left, 70, *appPalette );

    /* Dependencies used by MVC's: */
    AsyncDataLyr_Task* dataLayer = new AsyncDataLyr_TaskHttp( "http://localhost:8080",
                                                              "tasks",
                                                              new JsonTaskParser() );
    TaskListViewModel* model = new TaskListViewModel(dataLayer);
    model->getAllTasks();

    appPalette->setColor( QPalette::All, QPalette::Background, QColor("white") );
    TaskListView* view = new TaskListView( QLatin1String("All Tasks"),
                                           *appPalette );
    view->setModel(model);
    TaskListCtrl* controller = new TaskListCtrl( model, view );

    menuBar.addWidget( view,
                       ":svg/update_icon_normal",
                       ":svg/update_icon_mover",
                       ":svg/update_icon_selected" );
    menuBar.addWidget( view,
                       ":svg/delete_icon_normal",
                       ":svg/delete_icon_mover",
                       ":svg/delete_icon_selected" );
    menuBar.show();

    return a.exec();
}
