#include "mainwindow.h"
#include <QApplication>
#include <QVBoxLayout>
#include <QPalette>

#include "data/implementation/asyncdatalyr_taskhttp.h"
#include "modelparser/taskjson.h"
#include "models/interface/task.h"

#include "data/implementation/asyncdatalyr_personhttp.h"
#include "modelparser/person_json.h"
#include "models/interface/person.h"

#include "viewmodels/tasklistviewmodel.h"
#include "viewmodels/personlistviewmodel.h"

#include "tasklistview.h"
#include "tasklistctrl.h"
#include "taskeditview.h"
#include "taskeditctrl.h"

#include "personlistview.h"


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

    /********************** TASK LIST **************************/
    /* Dependencies used by MVC's: */
    AsyncDataLyr_Task* dataLayer = new AsyncDataLyr_TaskHttp( "http://localhost:8080",
                                                              "tasks",
                                                              new JsonTaskParser() );
    TaskListViewModel* model = new TaskListViewModel(dataLayer);
    model->getAllTasks();

    appPalette->setColor( QPalette::All, QPalette::Background, QColor("white") );
    TaskListView* view = new TaskListView( QLatin1String("All Tasks"),
                                           *appPalette,
                                           &menuBar);
    view->setModel(model);
    TaskListCtrl* controller = new TaskListCtrl( model, view );


    /********************** PERSON LIST **************************/
    /* Dependencies used by MVC's: */
    AsyncDataLyr_Person* dataLayerPerson = new AsyncDataLyr_PersonHttp( "http://localhost:8080",
                                                                        "persons",
                                                                        new JSONPersonParser() );
    PersonListViewModel* modelPersons = new PersonListViewModel(dataLayerPerson);
    modelPersons->getAllPersons();

    PersonListView* viewPersons = new PersonListView( QLatin1String("All Persons"),
                                                      *appPalette,
                                                      &menuBar );
    viewPersons->setModel(modelPersons);
    //PersonListCtrl* controllerPersons = new TaskListCtrl( modelPersons, viewPersons );

    menuBar.addWidget( view,
                       ":svg/update_icon_normal",
                       ":svg/update_icon_mover",
                       ":svg/update_icon_selected" );
    menuBar.addWidget( viewPersons,
                       ":svg/delete_icon_normal",
                       ":svg/delete_icon_mover",
                       ":svg/delete_icon_selected" );
    menuBar.show();

    return a.exec();
}
