#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDockWidget>
#include <QPushButton>
#include <QTextStream>
#include <QInputDialog>
#include <QFileDialog>
#include <QGraphicsItem>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSceneMoveEvent>
#include <QString>
#include <QMouseEvent>
#include <QColor>
#include <QPixmap>
#include <QFile>

#include "mainview.h"
#include "mainscene.h"
#include "baseobject.h"
#include "rectobject.h"
#include "lineobject.h"
#include "ellipseobject.h"
#include "operobj.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


    void initToolBar();
    void initWindow();

private slots:
    //File
    void on_actionSave_triggered();
    void on_actionNew_triggered();
    void on_actionOpen_triggered();

    //Figure
    void on_actionLine_triggered();
    void on_actionRectangle_triggered();
    void on_actionEllipse_triggered();

    //Setting
    void on_actionMagnify_triggered();
    void on_actionReduce_triggered();
    void on_actionSelect_triggered();
    void on_actionTrash_triggered();

    //Measure
    void on_actionVerDistance_triggered();
    void on_actionHorDistance_triggered();


    void curPosChange(QPointF pos);
    void on_penColorBtn_clicked();

signals:
    void penColorChange(QColor color);

private:
    Ui::MainWindow *ui;

    MainView* curView;
    MainScene* curScene;

    QString x;
    QString y;

};
#endif // MAINWINDOW_H
