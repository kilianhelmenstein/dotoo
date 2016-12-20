#include "tasklistview.h"

#include <QScrollArea>


namespace Dotoo {
namespace GUI {



TaskListView::TaskListView( const QPalette& appPalette, QWidget* parent )
    : QWidget(parent),
      m_model(nullptr),
      m_defaultPalette(appPalette),
      m_listLayout(nullptr)
{
    QPalette myPalette(appPalette);
    QBrush brush(Qt::RadialGradientPattern);
    myPalette.setBrush(QPalette::All,QPalette::Background, brush );
    setPalette(myPalette);
    setBackgroundRole(QPalette::Light);

    m_listLayout = new QVBoxLayout;
    setLayout(m_listLayout);

    QScrollArea* scrollArea = new QScrollArea();
    scrollArea->setPalette(myPalette);
    scrollArea->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    scrollArea->setWidget(this);
}


TaskListView::~TaskListView()
{
}


void TaskListView::setModel( TaskListViewModel* model )
{
    if ( model && model != m_model )
    {
        if ( m_model )
        {
            disconnect( m_model, 0, this, 0 );
        }

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
