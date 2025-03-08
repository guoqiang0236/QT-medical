#ifndef MED_IMG_MAINWINDOW_H
#define MED_IMG_MAINWINDOW_H

#include <QMainWindow>
#include <QVTKOpenGLNativeWidget.h>
#include <vtkRenderer.h>
#include <vtkSmartPointer.h>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onRotateButtonClicked();

private:
    QVTKOpenGLNativeWidget *vtkWidget;
    vtkSmartPointer<vtkRenderer> renderer;
};

#endif // MED_IMG_MAINWINDOW_H