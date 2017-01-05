#include <QApplication>
#include <QPalette>

// 'Tasks' dependencies:
#include "data/implementation/asyncdatalyr_taskhttp.h"
#include "modelparser/taskjson.h"
#include "models/interface/task.h"
#include "tasklistviewmodel.h"
#include "tasklistview.h"
#include "tasklistctrl.h"

// 'Persons' dependencies:
#include "data/implementation/asyncdatalyr_personhttp.h"
#include "modelparser/person_json.h"
#include "models/interface/person.h"
#include "personlistviewmodel.h"
#include "personlistview.h"
#include "personlistctrl.h"

// 'Settings' dependencies:
#include "settingsview.h"
#include "settingsctrl.h"
#include "utilz/languagesetting.h"

#include "custommenubar.h"


using namespace Dotoo;
using namespace Dotoo::GUI;
using namespace Dotoo::Data;
using namespace Dotoo::ModelParser;


int main(int argc, char *argv[])
{
    using namespace Dotoo;

    QApplication a(argc, argv);

    // Color palette for consistent application style:
    QPalette* appPalette = new QPalette();
    appPalette->setColor( QPalette::All, QPalette::Background, QColor("grey") );

    // Menu bar:
    CustomGUI::CustomMenuBar menuBar( CustomGUI::CustomMenuBar::Left, 70, *appPalette );
    appPalette->setColor( QPalette::All, QPalette::Background, QColor("#fff5f5f5") );


    /********************** PERSON LIST MENU *************************/
    AsyncDataLyr_Person* dataLayerPerson = new AsyncDataLyr_PersonHttp( "http://localhost:8080",
                                                                        "persons",
                                                                        new JSONPersonParser() );
    PersonListViewModel* modelPersons = new PersonListViewModel(dataLayerPerson);
    modelPersons->getAllPersons();

    PersonListView* viewPersons = new PersonListView( *appPalette,
                                                      &menuBar );
    viewPersons->setModel(modelPersons);
    PersonListCtrl* controllerPersons = new PersonListCtrl( modelPersons, viewPersons );


    /********************** TASK LIST MENU **************************/
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


    /********************** SETTINGS MENU *************************/
    LanguageSetting langSetting( "lang" );
    SettingsView* viewSettings = new SettingsView( *appPalette );
    viewSettings->setLanguageModel( &langSetting );
    SettingsCtrl* controllerSettings = new SettingsCtrl( viewSettings,
                                                         &langSetting );


    // Add all menus to menu bar (it will manage all views):
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
    return a.exec();
}
