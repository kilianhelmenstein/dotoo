#include <QApplication>
#include <QMainWindow>
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
#include "personlistctrl.h"

#include "custommenubar.h"

#include "settingsview.h"
#include "settingsctrl.h"
#include "utilz/languagesetting.h"


using namespace Dotoo;
using namespace Dotoo::GUI;
using namespace Dotoo::Data;
using namespace Dotoo::ModelParser;


int main(int argc, char *argv[])
{
    using namespace Dotoo;

    QApplication a(argc, argv);
    QMainWindow mainWindow;

    QPalette* appPalette = new QPalette();
    appPalette->setColor( QPalette::All, QPalette::Background, QColor("grey") );

    CustomGUI::CustomMenuBar menuBar( CustomGUI::CustomMenuBar::Left, 70, *appPalette );
    appPalette->setColor( QPalette::All, QPalette::Background, QColor("#fff5f5f5") );


    /********************** PERSON LIST **************************/
    /* Dependencies used by MVC's: */
    AsyncDataLyr_Person* dataLayerPerson = new AsyncDataLyr_PersonHttp( "http://localhost:8080",
                                                                        "persons",
                                                                        new JSONPersonParser() );
    PersonListViewModel* modelPersons = new PersonListViewModel(dataLayerPerson);
    modelPersons->getAllPersons();

    PersonListView* viewPersons = new PersonListView( *appPalette,
                                                      &menuBar );
    viewPersons->setModel(modelPersons);
    PersonListCtrl* controllerPersons = new PersonListCtrl( modelPersons, viewPersons );


    /********************** TASK LIST **************************/
    /* Dependencies used by MVC's: */
    AsyncDataLyr_Task* dataLayer = new AsyncDataLyr_TaskHttp( "http://localhost:8080",
                                                              "tasks",
                                                              new JsonTaskParser() );
    TaskListViewModel* model = new TaskListViewModel(dataLayer);
    model->getAllTasks();

    TaskListView* view = new TaskListView( *appPalette,
                                           &menuBar);
    view->setModel(model);
    view->setPersonsModel(modelPersons);
    TaskListCtrl* controller = new TaskListCtrl( model, view );

    // Settings menu:
    LanguageSetting langSetting( "lang" );
    SettingsView* viewSettings = new SettingsView( *appPalette );
    viewSettings->setLanguageModel( &langSetting );
    SettingsCtrl* controllerSettings = new SettingsCtrl( viewSettings,
                                                         &langSetting );


    menuBar.addWidget( view,
                       ":svg/task_menu_normal",
                       ":svg/task_menu_mover",
                       ":svg/task_menu_selected" );
    menuBar.addWidget( viewPersons,
                       ":svg/persons_menu_normal",
                       ":svg/persons_menu_mover",
                       ":svg/persons_menu_selected" );
    menuBar.addWidget( viewSettings,
                       ":svg/settings_menu_normal",
                       ":svg/settings_menu_mover",
                       ":svg/settings_menu_selected" );

    menuBar.show();
//    mainWindow.setCentralWidget( &menuBar );
//    mainWindow.show();

    return a.exec();
}
