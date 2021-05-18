#ifndef RENDERAREA_H
#define RENDERAREA_H

#include <QWidget>
#include <QColor>

class RenderArea : public QWidget
{
    Q_OBJECT
public:
    explicit RenderArea(QWidget *parent = nullptr);

    QSize minimumSizeHint() const Q_DECL_OVERRIDE;
    QSize sizeHint() const Q_DECL_OVERRIDE;

    enum ShapesType {Astroid, Cycloid, HuygensCycloid, HypoCycloid};
    void setBackgroundColor(QColor color) {mBackgroundColor= color; }   //setter
    QColor backgroundColor()const  {return mBackgroundColor;} // getter

    void setShape(ShapesType shape) {mShape = shape; on_shape_changed();}
    ShapesType shape () const { return mShape;}

protected:
void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

signals:

public slots:

private:
    void on_shape_changed();
    QPointF compute(float t);
    QPointF compute_astroid(float t);
    QPointF compute_cycloid(float t);
    QPointF compute_huygens(float t);
    QPointF compute_hypo(float t);
    QColor mBackgroundColor;
    QColor mShapeColor;
    ShapesType mShape;

    double mIntervalLength;
    float mScale;
    int mStepCount;
};

#endif // RENDERAREA_H
