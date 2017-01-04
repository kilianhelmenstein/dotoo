#include "textviewutilz.h"

#include <QString>
#include <QFontMetrics>
#include <QLabel>



namespace TextViewUtilz {


void SetTextToLabel( QLabel *label,
                     const QString& text )
{
    if ( !label->wordWrap() )
    {
        QFontMetrics metrix(label->font());
        int width = label->width() - 2;
        QString clippedText = metrix.elidedText(text, Qt::ElideRight, width);
        label->setText(clippedText);
    } else
    {
        label->setText(text);
    }
}




} // namespace Textviewutilz
