#ifndef QANIMATIONUTILZ_H
#define QANIMATIONUTILZ_H

class QObject;
class QWidget;
class QPropertyAnimation;



namespace QAnimationUtilz {


/*!
 * \brief   Creates a QPropertyAnimation that shrinks the given widget.
 *          Use this for fading out a view for example.
 *
 * \param   int duration            Animation's duration.
 *
 * \return  QPropertyAnimation*     Arranged animation object. Caller takes ownership
 *                                  of return object.
 */
QPropertyAnimation* CreateShrinkAnimation( QWidget* animatedWidget,
                                           int duration,
                                           QObject* parent=nullptr );


} // namespace QAnimationUtilz

#endif // QANIMATIONUTILZ_H
