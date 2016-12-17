#include "textviewutilz.h"

#include <QString>
#include <QFontMetrics>
#include <QLabel>



namespace TextViewUtilz {


void SetTextToLabel( QLabel *label,
                     const QString& text )
{
    QFontMetrics metrix(label->font());
    int width = label->width() - 2;
    QString clippedText = metrix.elidedText(text, Qt::ElideRight, width);
    label->setText(clippedText);
}




} // namespace Textviewutilz
