#include "mainwindow.h"
#include <QApplication>
#include <QPushButton>
#include <QDate>
#include <QVBoxLayout>
#include <QScrollArea>

#include "data/implementation/asyncdatalyr_taskhttp.h"
#include "modelparser/taskjson.h"
#include "models/interface/task.h"
#include "viewmodels/taskviewmodel.h"
#include "views/taskview.h"


using namespace Dotoo;
using namespace Data;
using namespace ModelParser;


int main(int argc, char *argv[])
{
    using namespace Dotoo;

    QApplication a(argc, argv);

    QWidget mainW;

    QVBoxLayout* listLayout = new QVBoxLayout;

    /* Dependencies used by MVC's: */
    BytestreamTaskParser* parser = new JsonTaskParser();
    AsyncDataLyr_Task* dataLayer = new AsyncDataLyr_TaskHttp( "http://localhost:8080",
                                                              "tasks",
                                                              parser );
    Task* task = new Task();
    task->setId(1);
    TaskViewModel* viewmodel = new TaskViewModel( dataLayer, *task );

    for ( int i=0 ; i<10 ; ++i )
    {
        TaskView* view = new TaskView();
        view->setModel( viewmodel );
        viewmodel->get();
        listLayout->addWidget( view );
    }

    mainW.setLayout( listLayout );

    QScrollArea* scrollArea = new QScrollArea;
    scrollArea->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    scrollArea->setBackgroundRole(QPalette::Light);
    scrollArea->setWidget(&mainW);
    scrollArea->show();

    return a.exec();
}
