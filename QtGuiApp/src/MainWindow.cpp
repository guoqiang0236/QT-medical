#include "MainWindow.h"
#include <vtkSphereSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkRenderWindow.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) 
{
    // 必须设置抗锯齿等参数
    vtkWidget = new QVTKOpenGLNativeWidget();
    vtkWidget->setFormat(QVTKOpenGLNativeWidget::defaultFormat());

    // VTK管线
    auto sphereSource = vtkSmartPointer<vtkSphereSource>::New();
    sphereSource->SetRadius(2.0);
    sphereSource->Update();

    auto mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputConnection(sphereSource->GetOutputPort());

    auto actor = vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mapper);

    renderer = vtkSmartPointer<vtkRenderer>::New();
    renderer->AddActor(actor);
    renderer->SetBackground(0.1, 0.2, 0.3);

    vtkWidget->renderWindow()->AddRenderer(renderer);
    vtkWidget->renderWindow()->Render();

    setCentralWidget(vtkWidget);  // 必须设置中心控件！
}

MainWindow::~MainWindow() = default;

void MainWindow::onRotateButtonClicked() {
    renderer->GetActiveCamera()->Azimuth(10);
    vtkWidget->renderWindow()->Render();
}