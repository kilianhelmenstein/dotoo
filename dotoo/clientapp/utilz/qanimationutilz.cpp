#include "qanimationutilz.h"

#include <QWidget>
#include <QPropertyAnimation>


namespace QAnimationUtilz {


QPropertyAnimation* CreateShrinkAnimation( QWidget* animatedWidget,
                                           int duration,
                                           QObject* parent )
{
    QPropertyAnimation* resultingAnimation = new QPropertyAnimation( animatedWidget,
                                                                     "geometry",
                                                                     parent );
    resultingAnimation->setDuration( duration );
    resultingAnimation->setStartValue( animatedWidget->geometry() );
    resultingAnimation->setEndValue( QRect(animatedWidget->x() + animatedWidget->width()/2,
                                         animatedWidget->y() + animatedWidget->height()/2,
                                         0, 0 ) );

    return resultingAnimation;
}




} // namespace QAnimationUtilz
