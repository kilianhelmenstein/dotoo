#ifndef CUSTOMICONBUTTON_H
#define CUSTOMICONBUTTON_H

#include <QWidget>
#include <QString>

class QSvgWidget;


class CustomIconButton : public QWidget
{
    Q_OBJECT
public:
    CustomIconButton( const QString& iconNormal,
                      const QString& iconMouseOver,
                      const QString& iconSelected,
                      bool selectable=false,
                      QWidget* parent=nullptr );
    virtual ~CustomIconButton() {}

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
    bool m_isSelected;
};

#endif // CUSTOMICONBUTTON_H
