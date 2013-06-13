#ifndef UBSELECTIONFRAME_H
#define UBSELECTIONFRAME_H

#include <QGraphicsRectItem>
#include <QtGui>
#include <core/UB.h>

class DelegateButton;
class UBGraphicsItemDelegate;
class UBGraphicsScene;

class UBSelectionFrame : public QObject, public QGraphicsRectItem
{
    Q_OBJECT

public:
    enum {om_idle, om_moving, om_rotating} mOperationMode;

    UBSelectionFrame();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;
    QPainterPath shape() const;

    void setLocalBrush(const QBrush &pBrush) {mLocalBrush = pBrush;}
    QBrush localBrush() const {return mLocalBrush;}
//    void setEnclosedItems(const QList<UBGraphicsItemDelegate*> pEncItems) {mEnclosedtems = pEncItems; updateRect();}
    void setEnclosedItems(const QList<QGraphicsItem*> pGraphicsItems);
    void updateRect();
    void updateScale();
    bool isEmpty() const {return this->rect().isEmpty();}

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

private slots:
    void setAntiScaleRatio(qreal pAntiscaleRatio) {mAntiscaleRatio = pAntiscaleRatio;}
    void onZoomChanged(qreal pZoom);
    void remove();
    void duplicate();

private:
    void translateItem(QGraphicsItem *item, const QPointF &translatePoint);
    void placeButtons();
    void placeExceptionButton(DelegateButton *pButton, QTransform pTransform);
    void clearButtons();
    inline int adjThickness() const {return mThickness * mAntiscaleRatio;}
    inline UBGraphicsScene* ubscene();

    QList<DelegateButton*> buttonsForFlags(UBGraphicsFlags fls);


private:
    int mThickness;
    qreal mAntiscaleRatio;
    QList<UBGraphicsItemDelegate*> mEnclosedtems;
    QBrush mLocalBrush;

    QPointF mPressedPos;
    QPointF mLastMovedPos;
    QPointF mLastTranslateOffset;
    qreal mRotationAngle;

    QList<DelegateButton*> mButtons;

    DelegateButton *mDeleteButton;
    DelegateButton *mDuplicateButton;
    DelegateButton *mZOrderUpButton;
    DelegateButton *mZOrderDownButton;

    DelegateButton *mRotateButton;

};

#endif // UBSELECTIONFRAME_H