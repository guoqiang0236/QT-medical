#include <QApplication>
#include "MainWindow.h"
#include <vtkOpenGLRenderWindow.h>  // 必须包含

int main(int argc, char *argv[]) {
    // 必须在QApplication之前调用
    QSurfaceFormat::setDefaultFormat(QVTKOpenGLNativeWidget::defaultFormat());

    QApplication app(argc, argv);
    MainWindow window;
    window.show();
    return app.exec();
}