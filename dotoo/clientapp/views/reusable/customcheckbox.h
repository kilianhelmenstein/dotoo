#ifndef CUSTOMCHECKBOX_H
#define CUSTOMCHECKBOX_H

#include <QWidget>

class QSvgWidget;


namespace CustomGUI {


class CustomCheckBox : public QWidget
{
    Q_OBJECT
public:
    CustomCheckBox( bool defaultState=false,
                    QWidget* parent=nullptr );
    virtual ~CustomCheckBox() {}

    bool state() const { return m_state; }
    void setState( bool state );

private slots:
    void mouseReleaseEvent( QMouseEvent* );

signals:
    void toggled( bool state );

private:
    QSvgWidget* m_icon;

    bool m_state;
};

} // namespace CustomGUI

#endif // CUSTOMCHECKBOX_H
