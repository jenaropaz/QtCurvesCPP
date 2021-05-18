#include "renderarea.h"
#include <QPaintEvent>
#include <QPainter>
#include <qmath.h>


RenderArea::RenderArea(QWidget *parent) :
    QWidget(parent),
    //mBackgroundColor(QColor(0,0,255)),
    mShapeColor(255,255,255),
    mShape (Astroid)
{
    on_shape_changed();
}

QSize RenderArea::minimumSizeHint() const
{
    return QSize(100,100);


}
QSize RenderArea::sizeHint() const
{

    return QSize(400,200);

}

void RenderArea::on_shape_changed()
{
  switch(mShape)
  {
  case Astroid:
      mScale=60;
      mIntervalLength = 2 * M_PI;
      mStepCount = 1024;
      break;
  case Cycloid:
      mScale=6;
      mIntervalLength = 6 * M_PI;
      mStepCount = 512;
      break;
  case HuygensCycloid:
      mScale =8;
      mIntervalLength = 6 * M_PI;
      mStepCount = 512;
      break;
  case HypoCycloid:
      mScale =25;
      mIntervalLength = 2 * M_PI;
      mStepCount = 512;
      break;
  default:
      break;
  }

}
QPointF RenderArea::compute(float t)
{
    switch (mShape) {
    case Astroid:
        return compute_astroid(t);
        break;
    case Cycloid:
        return compute_cycloid(t);
        break;
    case HuygensCycloid:
        return compute_huygens(t);
        break;
    case HypoCycloid:
        return compute_hypo(t);
        break;
    default:
        break;
    }
    return QPointF(0,0);
}
QPointF RenderArea::compute_astroid(float t)
{
    float cos_t = cos(t);
    float sin_t = sin(t);
    float x = 2 * cos_t*cos_t*cos_t;
    float y = 2 * sin_t*sin_t*sin_t;
    return QPointF (x,y);
}
QPointF RenderArea::compute_cycloid(float t)
{
    return QPointF (
                1.5 * (1 - cos(t)),            // x
                1.5 * (t - sin(t))          // y
                );
}
QPointF RenderArea::compute_huygens(float t)
{

     return QPointF (
                 4 * (3 *cos(t)-cos(3*t)),   // x
                 4 * (3 *sin(t)-sin(3*t))    // y
                 );
}
QPointF RenderArea::compute_hypo(float t)
{
     return QPointF (
                 1.5 * (2 * cos(t) + cos(2 * t)),
                 1.5 * (2 * sin(t) - sin(2 * t))
                 );
}
void RenderArea::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    switch (mShape) {
    case Astroid:
        mBackgroundColor=Qt::red;
        break;
    case Cycloid:
        mBackgroundColor=Qt::green;
        break;
    case HuygensCycloid:
        mBackgroundColor=Qt::blue;
        break;
    case HypoCycloid:
        mBackgroundColor=Qt::black;
        break;
    default:
        break;
    }
    painter.setBrush(mBackgroundColor);
    painter.setPen(mShapeColor);

    painter.drawRect(this->rect());
    //painter.drawLine(this->rect().topLeft(),this->rect().bottomRight());


    QPoint center = this->rect().center();
    //int stepCount = 1024;
    //float mScale =60;
    //double mIntervalLength = 2 * M_PI;
    float step = mIntervalLength / mStepCount;
    for(float t = 0; t < mIntervalLength; t += step) {
        QPointF point = compute(t);

        QPoint pixel;
        pixel.setX(point.x() * mScale + center.x());
        pixel.setY(point.y() * mScale + center.y());

        painter.drawPoint(pixel);
    }
}
