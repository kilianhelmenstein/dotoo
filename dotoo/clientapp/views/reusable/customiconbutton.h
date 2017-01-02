#ifndef CUSTOMICONBUTTON_H
#define CUSTOMICONBUTTON_H

#include <QWidget>
#include <QString>

class QSvgWidget;



namespace CustomGUI {



class CustomIconButton : public QWidget
{
    Q_OBJECT
public:
    CustomIconButton( const QString& iconNormal,
                      const QString& iconMouseOver,
                      const QString& iconSelected,
                      bool selectable=false,
                      bool deselectableByMouse=true,
                      QWidget* parent=nullptr );
    virtual ~CustomIconButton() {}

    bool selectable() const { return m_selectable; }
    bool selected() const { return m_isSelected; }
    void setSelected( bool selected );

private slots:
    void mousePressEvent( QMouseEvent* event );

    void mouseReleaseEvent( QMouseEvent* event );

    /*!
     * \brief   Lets widget look highlighted.
     */
    void enterEvent(QEvent*);

    /*!
     * \brief   Lets widget look un-highlighted.
     */
    void leaveEvent(QEvent*);

signals:
    void clicked( bool isSelected );

private:
    QSvgWidget* m_icon;

private:
    const QString m_iconNormal;
    const QString m_iconMouseOver;
    const QString m_iconSelected;

    const bool m_selectable;
    const bool m_deselectableByMouse;
    bool m_isSelected;
};


} // namespace CustomGUI

#endif // CUSTOMICONBUTTON_H
