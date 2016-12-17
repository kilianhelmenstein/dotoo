#ifndef CUSTOMCHECKBOX_H
#define CUSTOMCHECKBOX_H

#include <QWidget>

class QSvgWidget;


class CustomCheckBox : public QWidget
{
    Q_OBJECT
public:
    CustomCheckBox( QWidget* parent=nullptr );
    virtual ~CustomCheckBox() {}

private slots:
    void mouseReleaseEvent( QMouseEvent* event );

signals:
    void toggled( bool state );

private:
    QSvgWidget* m_icon;

    bool m_state;
};

#endif // CUSTOMCHECKBOX_H
