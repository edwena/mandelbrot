#include <mycanvas.h>
#include <QtWidgets>
#include <malloc.h>

MyCanvas::MyCanvas(QWidget *parent) :
    QWidget(parent)
{
    should_i_paint_a_circle = false;
    should_i_color_it = false;
}

MyCanvas::~MyCanvas()
{
}

void MyCanvas::loadPalette() {
    loadFromFile();
    should_i_color_it = true;
    repaint();
}

typedef struct {
    double a, b;
} complex;

complex build_complex(double a, double b) {
    complex num;
    num.a = a;
    num.b = b;
    return num;
}

double abs_sq(complex num) {
    return num.a * num.a + num.b * num.b;
}

complex find_sum(complex num1, complex num2) {
    return build_complex(num1.a + num2.a, num1.b + num2.b);
}

complex find_prod(complex num1, complex num2) {
    return build_complex((num1.a * num2.a) - (num1.b * num2.b),(num1.a * num2.b) + (num2.a * num1.b));
}

complex decart_interpreter(int Xsc, int Ysc, int Wsc, int Hsc) {
    return build_complex((3.0*Xsc/Wsc - 2 ), (2.0*(-Ysc)/Hsc + 1));
}


int is_it_mandelbrot(complex num) {
    complex Zn = build_complex(0,0);
    for(int i = 0; i < 256; i++) {
        if(abs_sq(Zn) >= 4) {
            return i;
        }
         Zn = find_sum(find_prod(Zn, Zn), num);
    }
    return 0;
}


void MyCanvas::draw() {

    int n = width()*height(), i = 0;
    breakpoints = (int*)malloc(n * sizeof(int));
    for(int Xsc=0; Xsc<width(); Xsc++) {
        for(int Ysc=0; Ysc<height(); Ysc++) {
            breakpoints[i] = is_it_mandelbrot (decart_interpreter (Xsc, Ysc, width(), height()));
            i++;
            }
        }
    should_i_paint_a_circle = true;
    repaint();
}




void MyCanvas::loadFromFile()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open Pallete"), "",
        tr("Pallete (*.pal);;All Files (*)"));
    if (fileName.isEmpty())
        return;
    else {
        QFile file(fileName);

        if (!file.open(QIODevice::ReadOnly)) {
            QMessageBox::information(this, tr("Unable to open file"),
                file.errorString());
            return;
        }
        QTextStream in(&file);

        int i = 0;
        while(!in.atEnd()) {
            QString line = in.readLine();

            int a, b, c;
            QTextStream(&line) >> a >> b >> c;
            m_pallete[i] = *(new QColor(a, b, c));
            i++;
        }

        file.close();
    }
}

void MyCanvas::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    if (should_i_paint_a_circle) {

        QPainter painter(this); // Создаём объект отрисовщика

        int i = 0;
        for(int Xsc=0; Xsc<width(); Xsc++) {
            for(int Ysc=0; Ysc<height(); Ysc++) {
                if (should_i_color_it) {
                    painter.setPen(m_pallete[breakpoints[i]]);
                } else {
                    painter.setPen(breakpoints[i] > 0 ? Qt::black : Qt::white);
                }
                painter.drawPoint(Xsc, Ysc);
                i++;
            }
        }
    }
}

//void MyCanvas::paintEvent(QPaintEvent *event)
//{
//    QRect rect = event->rect();
//    draw(rect);
//}

//void MyCanvas::draw(QRect &rect)
//{
//    QPainter painter(this);
//    painter.setRenderHint(QPainter::Antialiasing);
//    painter.setPen(Qt::black);
//    painter.drawText(rect, Qt::AlignCenter,
//                      "Data");
//    painter.drawRect(rect);
//}

