#include "MainWindow.h"
#include <vtkSphereSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkRenderWindow.h>
#include <Qdebug.h>
#include <QIcon>
#include <QFileDialog>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) ,
    m_filemanager(std::make_unique<FileManager>())
{
    // 设置无边框窗口
    setWindowFlags(Qt::FramelessWindowHint);
    setWindowIcon(QIcon(":/icon/favicon.ico")); // 覆盖可能的默认值
    ui.setupUi(this);
    initsolt();
    UpdateGUI();
    //test();
}

MainWindow::~MainWindow() = default;

void MainWindow::test()
{
    m_filemanager->testVTK();
}

void MainWindow::ReadDicomFile()
{
    QString fileName = QFileDialog::getOpenFileName(
        this, "选择文件", "", "All files (*.*)");
    if (!fileName.isEmpty()&&m_filemanager) {
        m_filemanager->UpdatePlotFile(fileName.toStdString());
    }
}

void MainWindow::ReadDicomFiles()
{
    // 打开文件夹选择对话框
    QString folderPath = QFileDialog::getExistingDirectory(
        this,                  // 父窗口
        "选择文件夹",           // 对话框标题
        QDir::homePath(),      // 初始目录（用户主目录）
        QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks
    );

    // 检查路径是否有效
    if (!folderPath.isEmpty() && m_filemanager)
    {
        m_filemanager->UpdatePlotFiles(folderPath.toStdString());
    } 
       
   
}

void MainWindow::StyleChanged(const QString &style)
{
    qDebug() << "当前选中文本：" << style;
    QString styledir = ":/QSS/" + style + ".qss";
    loadStyleSheet(styledir);
}

void MainWindow::ShutDown()
{
    QApplication::quit();
}

void MainWindow::initsolt()
{
    QObject::connect(ui.pushButton, &QPushButton::clicked, this, &MainWindow::ReadDicomFile);
    QObject::connect(ui.pushButton_6, &QPushButton::clicked, this, &MainWindow::ReadDicomFiles);
    QObject::connect(ui.comboBox, &QComboBox::currentTextChanged,this, &MainWindow::StyleChanged);
    QObject::connect(ui.pushButton_shutdown, &QPushButton::clicked, this, &MainWindow::ShutDown);
}

void MainWindow::UpdateGUI()
{
    if (!m_filemanager)
        return;
    m_filemanager->GetVTKopenGLWidget()->setParent(ui.frame_vtkrender);
    m_filemanager->GetVTKopenGLWidget()->setObjectName("VTKopenGLWidget");
    ui.horizontalLayout_2->addWidget(m_filemanager->GetVTKopenGLWidget());


}

void MainWindow::loadStyleSheet(const QString& path)
{
    QFile qssFile(path);
    if (!qssFile.exists()) {
        qWarning() << "QSS 文件不存在:" << path;
        return;
    }
    if (qssFile.open(QFile::ReadOnly)) {
        QString styleSheet = QLatin1String(qssFile.readAll());
        qApp->setStyleSheet(styleSheet); // 全局应用样式
        qssFile.close();
    }
    else {
        qWarning() << "无法打开 QSS 文件:" << path;
    }
}

