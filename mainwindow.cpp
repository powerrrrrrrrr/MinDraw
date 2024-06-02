#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QDebug>
#include <QAbstractButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    initToolBar();
    initWindow();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initToolBar()
{
    //File
    ui->toolBar->addAction(ui->actionOpen);
    ui->toolBar->addAction(ui->actionNew);
    ui->toolBar->addAction(ui->actionSave);

    ui->toolBar->addSeparator();

    //Figure
    ui->toolBar->addAction(ui->actionLine);
    ui->toolBar->addAction(ui->actionRectangle);
    ui->toolBar->addAction(ui->actionEllipse);

    ui->toolBar->addSeparator();

    //Setting
    ui->toolBar->addAction(ui->actionMagnify);
    ui->toolBar->addAction(ui->actionReduce);
    ui->toolBar->addAction(ui->actionSelect);
    ui->toolBar->addAction(ui->actionTrash);

    ui->toolBar->addSeparator();

    //Measure
    ui->toolBar->addAction(ui->actionVerDistance);
    ui->toolBar->addAction(ui->actionHorDistance);
}

void MainWindow::initWindow()
{
    ui->tabWidget->setTabsClosable(true);
    ui->tabWidget->removeTab(1);
    ui->tabWidget->removeTab(0);

    //当前窗口发生变化，将视图设置为当前的窗口
    connect(ui->tabWidget, &QTabWidget::currentChanged, this, [=](int index){
        Q_UNUSED(index);
        curView = dynamic_cast<MainView*>(ui->tabWidget->currentWidget());
        curScene = dynamic_cast<MainScene*>(curView->scene());
    });

    connect(ui->tabWidget, &QTabWidget::tabCloseRequested, this, [=](int index){
        QMessageBox msgBox;

        msgBox.setText("the document has changed");
        msgBox.addButton("Save", QMessageBox::ActionRole);
        msgBox.addButton("Unsave", QMessageBox::ActionRole);
        msgBox.addButton("Cancel", QMessageBox::ActionRole);

        msgBox.exec();

        if(msgBox.clickedButton()->text() == "Save"){
            on_actionSave_triggered();
            ui->tabWidget->removeTab(index);
        }
        else if(msgBox.clickedButton()->text() == "Unsave"){
            ui->tabWidget->removeTab(index);
        }
    });

    QString str = QString("欢迎使用MiniCAD!");
    ui->NoteTextEdit->append(str);

    ui->penStyleCbox->addItem("DashLine");

}


void MainWindow::on_actionSave_triggered()
{
    if(ui->tabWidget->count() == 0){
        QMessageBox::critical(this, "Tips", "当前没有图层可以保存！");
    }
    else{
        curScene->saveScene(QRect(-297*3/2, -210*3/2, 297*3, 210*3));

        ui->NoteTextEdit->append("保存文件至当前文件夹");
    }
}

void MainWindow::on_actionNew_triggered()
{
    qDebug() << "on_actionNew_triggered";
    static int count = 0;
    QString text = "Page" + QString::number(count);
    count++;

    //QRectF aRect = (QRectF)ui->tabWidget->rect();
    MainScene* pScene = new MainScene(this);
    MainView* view = new MainView(pScene);
    pScene->setSceneRect(-297*3/2, -210*3/2, 297*3, 210*3);
    ui->tabWidget->addTab(view, text);
    ui->tabWidget->setCurrentWidget(view);

    curView = view;
    curScene = dynamic_cast<MainScene*>(curView->scene());

    connect(curView, &MainView::viewPosChange, this, &MainWindow::curPosChange);

    ui->NoteTextEdit->append("添加窗口");
}

void MainWindow::on_actionOpen_triggered()
{
    qDebug() << "open file!";
    ui->NoteTextEdit->append("打开文件");
}

void MainWindow::on_actionLine_triggered()
{
    if(ui->tabWidget->count() == 0) return;

    qDebug() << "on_actionLine_triggered";
    //curView->enableDrawLine(true);
    curScene->setDrawType(MainScene::Line);
    ui->NoteTextEdit->append("正在绘制直线");
}

void MainWindow::on_actionRectangle_triggered()
{
    if(ui->tabWidget->count() == 0) return;

    qDebug() << "on_actionRectangle_triggered";
    curScene->setDrawType(MainScene::Rect);

    ui->NoteTextEdit->append("正在绘制矩形");
}

void MainWindow::on_actionEllipse_triggered()
{
    if(ui->tabWidget->count() == 0) return;

    qDebug() << "on_actionEllipse_triggered";

    curScene->setDrawType(MainScene::Ellipse);
    ui->NoteTextEdit->append("正在绘制椭圆");
}

void MainWindow::on_actionTrash_triggered()
{
    if(ui->tabWidget->count() == 0) return;

    qDebug() << "on_actionTrash_triggered";

    curScene->setDrawType(MainScene::Trash);
    ui->NoteTextEdit->append("请选择要删除的图元");
}

void MainWindow::on_actionVerDistance_triggered()
{
    if(ui->tabWidget->count() == 0) return;

    qDebug() << "on_actionTrash_triggered";

    curScene->setDrawType(MainScene::VerDistance);
    ui->NoteTextEdit->append("测量竖直距离");
}

void MainWindow::on_actionHorDistance_triggered()
{
    if(ui->tabWidget->count() == 0) return;

    qDebug() << "on_actionHorDistance_triggered";

    curScene->setDrawType(MainScene::HorDistance);
    ui->NoteTextEdit->append("测量水平距离");
}

void MainWindow::curPosChange(QPointF pos)
{
    x = QString::number(pos.x());
    y = QString::number(pos.y());

    ui->xLineEdit->setText(x);
    ui->yLineEdit->setText(y);

}



void MainWindow::on_actionMagnify_triggered()
{
    if(ui->tabWidget->count() == 0) return;

    curView->setMagnify();
    ui->NoteTextEdit->append("放大");
}

void MainWindow::on_actionReduce_triggered()
{
    if(ui->tabWidget->count() == 0) return;

    curView->setReduce();
    ui->NoteTextEdit->append("缩小");
}

void MainWindow::on_actionSelect_triggered()
{
    if(ui->tabWidget->count() == 0) return;

    curScene->setDrawType(MainScene::None);
    ui->NoteTextEdit->append("选择图元");

}

void MainWindow::on_penColorBtn_clicked()
{
    if(ui->tabWidget->count() == 0) return;

    QColor color = QColorDialog::getColor();

    if(color.isValid()){
        QString red = QString::number(color.red());
        QString green = QString::number(color.green());
        QString blue = QString::number(color.blue());

        QString str = QString("background-color: rgb(%1,%2,%3);border: 1px solid black;border-redius:2px;").arg(red).arg(green).arg(blue);
        ui->penColorBtn->setStyleSheet(str);
        curScene->setMyPenColor(color);
        QString note = QString("更改画笔颜色为：%1，rgb ：%2，%3，%4").arg(color.name()).arg(red).arg(green).arg(blue);
        ui->NoteTextEdit->append(note);
    }
}


