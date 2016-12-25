#include "tasklistview.h"

#include <QHBoxLayout>
#include <QScrollArea>
#include <QRadialGradient>
#include <QSizePolicy>
#include <QLabel>

#include "customiconbutton.h"

#include "utilz/textviewutilz.h"


namespace Dotoo {
namespace GUI {



TaskListView::TaskListView( const QString headlineText,
                            const QPalette& appPalette,
                            QWidget* parent )
    : QWidget(parent),
      m_model(nullptr),
      m_defaultPalette(appPalette),
      m_listLayout(nullptr)
{  
    /****************************************************************/
    /*********             Initial Presenation:               *******/
    /****************************************************************/
    setMinimumSize( 600, 500 );
    setMaximumSize( 700, 2000 );
    setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Expanding );
    setAutoFillBackground( true );

    /****************************************************************/
    /*********                Widget's Style:                 *******/
    /****************************************************************/
    setPalette( m_defaultPalette );
    setBackgroundRole( QPalette::Background );



    /****************************************************************/
    /*********             Widget's sub-widgets:              *******/
    /****************************************************************/

    /*** Headline: ***/
    QFont headlineFont;
    headlineFont.setPointSize(40);
    headlineFont.setStyleHint(QFont::SansSerif);
    headlineFont.setWeight(30);
    m_headline = new QLabel();
    m_headline->setFont(headlineFont);
    m_headline->setText(headlineText);

    /*** Task list: ***/
    // Use 'mainWidget' for usage of scroll area (takes only a widget, no layouts):
    QWidget* mainWidget = new QWidget(this);
    mainWidget->setMinimumSize( 600, 500 );
    mainWidget->setMaximumSize( 700, 2000 );
    mainWidget->setPalette(m_defaultPalette);
    mainWidget->installEventFilter(this);           // mainWidget does not have functionality. Forward events to true widet.

    // Scroll area for list:
    QScrollArea* scrollArea = new QScrollArea(this);
    scrollArea->setPalette(m_defaultPalette);
    scrollArea->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    scrollArea->setMinimumSize(minimumSize());
    scrollArea->setWidgetResizable(true);
    scrollArea->setBackgroundRole(QPalette::Background);    // TODO: Maybe add a gradient would look nice.
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setFrameShape(QFrame::NoFrame);
    scrollArea->installEventFilter(this);
    scrollArea->setWidget(mainWidget);

    /*** Tool bar: ***/
    CustomIconButton* toolAdd = new CustomIconButton( ":svg/add_icon_normal",
                                                      ":svg/add_icon_mover",
                                                      ":svg/add_icon_selected",
                                                      false );
    toolAdd->setFixedSize(70,70);
    CustomIconButton* toolChange = new CustomIconButton( ":svg/add_icon_normal",
                                                         ":svg/add_icon_mover",
                                                         ":svg/add_icon_selected",
                                                         true );
    toolChange->setFixedSize(70,70);
    CustomIconButton* toolDelete = new CustomIconButton( ":svg/add_icon_normal",
                                                         ":svg/add_icon_mover",
                                                         ":svg/add_icon_selected",
                                                         true );
    toolDelete->setFixedSize(70,70);


    /****************************************************************/
    /*********               Widget's Effects:                *******/
    /****************************************************************/
    m_looseFocusEffect = new QGraphicsBlurEffect(this); // TODO: Evaluate better teamwork of scroll area and this effect.
    m_looseFocusEffect->setBlurRadius(8.0);
    m_looseFocusEffect->setEnabled(false);
    setGraphicsEffect(m_looseFocusEffect);

    /****************************************************************/
    /*********                Widget's Layout:                *******/
    /****************************************************************/

    m_listLayout = new QVBoxLayout();
    m_listLayout->setSpacing(10);
    m_listLayout->setSizeConstraint(QLayout::SetMinAndMaxSize);
    mainWidget->setLayout(m_listLayout);

    // Toolbox layout:
    QHBoxLayout* toolboxLayout = new QHBoxLayout();
    toolboxLayout->addWidget( toolAdd, 0, Qt::AlignCenter );
    toolboxLayout->addWidget( toolChange, 0, Qt::AlignCenter );
    toolboxLayout->addWidget( toolDelete, 0, Qt::AlignCenter );

    /*** Main VBox layout. Contains headline, task list itself (contained within
     *   scroll area and tool bar (for manipulating task and task list): ***/
    QVBoxLayout* mainLayout = new QVBoxLayout();
    mainLayout->addWidget(m_headline);
    mainLayout->addWidget(scrollArea);
    mainLayout->addLayout(toolboxLayout);     // TODO: Implement custom toolbar. Add here.
    setLayout(mainLayout);
}


TaskListView::~TaskListView()
{
}


void TaskListView::setHeadline( const QString& headlineText )
{
    TextViewUtilz::SetTextToLabel( m_headline, headlineText );
}


void TaskListView::setModel( TaskListViewModel* model )
{
    // Check validity of input pointer. Check whether model changed truely.
    if ( model && model != m_model )
    {
        // If model was already set, disconnect it:
        if ( m_model )
        {
            disconnect( m_model, 0, this, 0 );
        }

        // Apply new model reference:
        m_model = model;
        connect( m_model, &TaskListViewModel::changed,
                 this, &TaskListView::onModelChange );
        onModelChange();
    }
}


void TaskListView::onModelChange()
{
    // Remove old ones
    foreach ( TaskView* view, m_taskViews )
    {
        m_listLayout->removeWidget(view);
        delete view;
    }
    m_taskViews.clear();

    // Insert new ones:
    foreach ( TaskViewModel* taskModel, m_model->modelList() )
    {
        TaskView* view = new TaskView(m_defaultPalette);
        view->setModel(taskModel);
        m_listLayout->addWidget(view);
    }
}


} // namespace GUI
} // namespace Dotoo
