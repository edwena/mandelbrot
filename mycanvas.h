#ifndef MYCANVAS_H
#define MYCANVAS_H

#include <QWidget>
#include <QGraphicsView>

class MyCanvas : public QWidget
{
    Q_OBJECT

public:
    explicit MyCanvas(QWidget *parent = nullptr);
    ~MyCanvas();

protected:
    void paintEvent(QPaintEvent *event);
//    void wheelEvent ( QWheelEvent * event );

private:
    bool should_i_paint_a_circle;
    bool should_i_color_it;
    QColor m_pallete[256];
    int *breakpoints;

public slots:
    void draw();
    void loadPalette();
    void loadFromFile();
};

#endif // MYCANVAS_H
