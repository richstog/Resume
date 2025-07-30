#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
// #include <QAxObject>
QVector<RSZO> vec_rszo;
QVector<Target> vec_tar;
QVector<PRO> vec_pro;
int status = -1;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scene = new QGraphicsScene();
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    Resize();

    QRegularExpression re1("[1-9]|[1-9][0-9]|[1][0-9][0-9]|[2][0][0]");
    QValidator *val1 = new QRegularExpressionValidator(re1, this);

    ui->lineEdit->setValidator(val1);
    ui->lineEdit_2->setValidator(val1);
    ui->lineEdit_4->setValidator(val1);
    ui->lineEdit_5->setValidator(val1);
    ui->lineEdit_7->setValidator(val1);
    ui->lineEdit_8->setValidator(val1);

    QRegularExpression re2("[1-9]|[1-4][0-9]|[5][0]");
    QValidator *val2 = new QRegularExpressionValidator(re2, this);

    ui->lineEdit_3->setValidator(val2);

    QRegularExpression re3("[1-9]|[1][0-9]|[2][0]");
    QValidator *val3 = new QRegularExpressionValidator(re3, this);

    ui->lineEdit_6->setValidator(val3);

    connect(ui->lineEdit, &QLineEdit::textChanged, this, &MainWindow::pushButton_1_active);
    connect(ui->lineEdit_2, &QLineEdit::textChanged, this, &MainWindow::pushButton_1_active);
    connect(ui->lineEdit_3, &QLineEdit::textChanged, this, &MainWindow::pushButton_1_active);

    connect(ui->lineEdit_4, &QLineEdit::textChanged, this, &MainWindow::pushButton_2_active);
    connect(ui->lineEdit_5, &QLineEdit::textChanged, this, &MainWindow::pushButton_2_active);
    connect(ui->lineEdit_6, &QLineEdit::textChanged, this, &MainWindow::pushButton_2_active);

    connect(ui->lineEdit_7, &QLineEdit::textChanged, this, &MainWindow::pushButton_3_active);
    connect(ui->lineEdit_8, &QLineEdit::textChanged, this, &MainWindow::pushButton_3_active);

    connect(&map, SIGNAL(deleteSignal(QString, QPointF)), this, SLOT(deletepoint(QString, QPointF)));



}

void MainWindow::Resize()
{
    int Height = this->height() * 0.97;

    ui->graphicsView->setMinimumSize(Height, Height + 5);
    ui->graphicsView->setMaximumSize(Height, Height);

    map.getChart()->setMinimumSize(Height, Height);
    map.getChart()->setMaximumSize(Height, Height);

    scene->setSceneRect(0, 0, Height, Height);
    scene->addItem(map.getChart());
    ui->graphicsView->setScene(scene);
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key_Enter || event->key()==Qt::Key_Return){
        focusNextChild();
        if(ui->pushButton->hasFocus()){
            on_pushButton_clicked();
            ui->lineEdit->setFocus();
        }
        if(ui->pushButton_2->hasFocus()){
            on_pushButton_2_clicked();
            ui->lineEdit_4->setFocus();
        }
        if(ui->pushButton_3->hasFocus()){
            on_pushButton_3_clicked();
            ui->lineEdit_7->setFocus();
        }

    }else{
        return;
    }
}

MainWindow::~MainWindow()
{
    QFile file(QDir::currentPath()+"/save.txt");
    file.open(QIODevice::WriteOnly);
    file.write(QString::number(vec_rszo.size()).toUtf8()+"\n");
    for(int i(0);i<vec_rszo.length();i++){
        QString s = QString::number(vec_rszo[i].x) + " " + QString::number(vec_rszo[i].y) + " " + QString::number(vec_rszo[i].d) +"\n";
        file.write(s.toUtf8());
    }
    file.write(QString::number(vec_pro.size()).toUtf8()+"\n");
    for(int i(0);i<vec_pro.length();i++){
        QString s = QString::number(vec_pro[i].x) + " " + QString::number(vec_pro[i].y) + " " + QString::number(vec_pro[i].r) +"\n";
        file.write(s.toUtf8());
    }
    file.write(QString::number(vec_tar.size()).toUtf8()+"\n");
    for(int i(0);i<vec_tar.length();i++){
        QString s = QString::number(vec_tar[i].x) + " " + QString::number(vec_tar[i].y)+"\n";
        file.write(s.toUtf8());
    }
    file.write(QString::number(status).toUtf8());
    file.close();
    delete ui;
}

bool MainWindow::no_rep(double x, double y)
{
    for(int i(0);i<vec_pro.size();i++){
        if(vec_pro[i].x==x && vec_pro[i].y==y){
            return false;
        }
    }
    for(int i(0);i<vec_tar.size();i++){
        if(vec_tar[i].x==x && vec_tar[i].y==y){
            return false;
        }
    }
    for(int i(0);i<vec_rszo.size();i++){
        if(vec_rszo[i].x==x && vec_rszo[i].y==y){
            return false;
        }
    }
    return true;
}

void MainWindow::nopush()
{
    if(vec_pro.size()>=1 && vec_tar.size()>=1 && vec_rszo.size()>=1){
        ui->pushButton_7->setEnabled(true);
        ui->pushButton_8->setEnabled(true);
    }else{
        ui->pushButton_7->setEnabled(false);
        ui->pushButton_8->setEnabled(false);
        ui->pushButton_5->setEnabled(false);
    }
}

void MainWindow::pushButton_1_active()
{
    if (ui->lineEdit->text() != ""
            && ui->lineEdit_2->text() != ""
            && ui->lineEdit_3->text() != "")
    {
        ui->pushButton->setEnabled(true);
    }
    else ui->pushButton->setEnabled(false);
}

void MainWindow::pushButton_2_active()
{
    if (ui->lineEdit_4->text() != ""
            && ui->lineEdit_5->text() != ""
            && ui->lineEdit_6->text() != "")
    {
        ui->pushButton_2->setEnabled(true);
    }
    else ui->pushButton_2->setEnabled(false);
    status = 0;
}

void MainWindow::pushButton_3_active()
{
    if (ui->lineEdit_7->text() != ""
            && ui->lineEdit_8->text() != "")
    {
        ui->pushButton_3->setEnabled(true);
    }
    else ui->pushButton_3->setEnabled(false);
    status = 0;
}

void MainWindow::on_pushButton_6_clicked()
{
    vec_pro.clear();
    vec_tar.clear();
    vec_rszo.clear();
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();
    ui->lineEdit_5->clear();
    ui->lineEdit_6->clear();
    ui->lineEdit_7->clear();
    ui->lineEdit_8->clear();
    ui->label_9->clear();
    ui->textEdit->clear();
    ui->textEdit->setText("Здесь будет решение…");
    status=-1;

    nopush();
    map.clearSeries();
}

void MainWindow::on_pushButton_clicked()
{
    double x = ui->lineEdit->text().toDouble();
    double y = ui->lineEdit_2->text().toDouble();
    double d = ui->lineEdit_3->text().toDouble();
status = 0;
    if (no_rep(x,y))
    {
        RSZO asd(x,y,d);

        vec_rszo.push_back(asd);

        ui->lineEdit->clear();
        ui->lineEdit_2->clear();
        ui->lineEdit_3->clear();
        ui->label_9->clear();

        if (vec_pro.size() >= 1 && vec_tar.size() >= 1 && vec_rszo.size() >= 1)
        {
            ui->pushButton_7->setEnabled(true);
            ui->pushButton_8->setEnabled(true);
        }
        else
        {
            ui->pushButton_7->setEnabled(false);
            ui->pushButton_8->setEnabled(false);
            ui->pushButton_5->setEnabled(false);
        }

        ui->pushButton_5->setEnabled(false);
        map.drawChart(vec_rszo,vec_pro,vec_tar);
    }

}

void MainWindow::on_pushButton_2_clicked()
{
    double x = ui->lineEdit_4->text().toDouble();
    double y = ui->lineEdit_5->text().toDouble();
    double r = ui->lineEdit_6->text().toDouble();
status = 0;
    if (no_rep(x,y))
    {
        PRO asd(x,y,r);

        vec_pro.push_back(asd);

        ui->lineEdit_4->clear();
        ui->lineEdit_5->clear();
        ui->lineEdit_6->clear();
        ui->label_9->clear();

        if (vec_pro.size() >= 1 && vec_tar.size() >= 1 && vec_rszo.size() >= 1)
        {
            ui->pushButton_7->setEnabled(true);
            ui->pushButton_8->setEnabled(true);
        }
        else
        {
            ui->pushButton_7->setEnabled(false);
            ui->pushButton_8->setEnabled(false);
            ui->pushButton_5->setEnabled(false);
        }

        ui->pushButton_5->setEnabled(false);
        map.drawChart(vec_rszo,vec_pro,vec_tar);
    }

}

void MainWindow::on_pushButton_3_clicked()
{
    double x = ui->lineEdit_7->text().toDouble();
    double y = ui->lineEdit_8->text().toDouble();
status = 0;
    if (no_rep(x,y))
    {
        Target asd(x,y);

        vec_tar.push_back(asd);

        ui->lineEdit_7->clear();
        ui->lineEdit_8->clear();
        ui->label_9->clear();

        if (vec_pro.size() >= 1 && vec_tar.size() >= 1 && vec_rszo.size() >= 1)
        {
            ui->pushButton_7->setEnabled(true);
            ui->pushButton_8->setEnabled(true);
        }
        else
        {
            ui->pushButton_7->setEnabled(false);
            ui->pushButton_8->setEnabled(false);
            ui->pushButton_5->setEnabled(false);
        }

        ui->pushButton_5->setEnabled(false);
        map.drawChart(vec_rszo,vec_pro,vec_tar);
    }
}

void MainWindow::on_pushButton_7_clicked()
{
    Solution::solve(vec_rszo,vec_pro,vec_tar);
    QVector<Liner> vec = Solution::retall();
    map.drawChart(vec_rszo,vec_pro,vec_tar,vec,1);
    ui->textEdit->clear();
    for(int i(0);i<vec.size();i++){
        QString s = "("+QString::number(vec[i].a.x())+","+QString::number(vec[i].b.y())+") -> ("+QString::number(vec[i].b.x())+"," +QString::number(vec[i].b.y()) + ")";
        ui->textEdit->append(s);
    }
    ui->pushButton_5->setEnabled(true);
    ui->label_9->setText("Возможности");
    status=1;
}

void MainWindow::on_pushButton_8_clicked()
{
    Solution::solve(vec_rszo,vec_pro,vec_tar);
    QVector<Liner> vec = Solution::retopt();
    map.drawChart(vec_rszo,vec_pro,vec_tar,vec,2);
    ui->textEdit->clear();
    for(int i(0);i<vec.size();i++){
        QString s = "("+QString::number(vec[i].a.x())+","+QString::number(vec[i].b.y())+") -> ("+QString::number(vec[i].b.x())+"," +QString::number(vec[i].b.y()) + ")";
        ui->textEdit->append(s);
    }
    ui->pushButton_5->setEnabled(true);
    ui->label_9->setText("Оптимум");
    status=2;
}

void MainWindow::deletepoint(QString name, QPointF point)
{
    if(name == "RSZO") {
        for(int i = 0; i < vec_rszo.size(); i ++) {
            if(QPointF(vec_rszo[i].x, vec_rszo[i].y) == point) {
                vec_rszo.erase(vec_rszo.begin() + i);
            }
        }
    }

    if(name == "PRO") {
        for(int i = 0; i < vec_pro.size(); i ++) {
            if(QPointF(vec_pro[i].x, vec_pro[i].y) == point) {
                vec_pro.erase(vec_pro.begin() + i);
            }
        }
    }

    if(name == "TAR") {
        for(int i = 0; i < vec_tar.size(); i ++) {
            if(QPointF(vec_tar[i].x, vec_tar[i].y) == point) {
                vec_tar.erase(vec_tar.begin() + i);
            }
        }
    }
    ui->label_9->clear();
    ui->textEdit->clear();
    ui->pushButton_5->setEnabled(false);
    map.drawChart(vec_rszo, vec_pro, vec_tar);
}

void MainWindow::doc_opt()
{
//     QVector<Liner> vec = Solution::retopt();
//     QAxObject *wApp = new QAxObject("Word.Application");
//     QAxObject * wDoc = wApp->querySubObject("Documents");
//     wDoc = wDoc->querySubObject("Add()");
//     QAxObject * selection = wApp->querySubObject("Selection()");
//     QAxObject * range = wDoc->querySubObject("Range()");
//     QAxObject * font = selection->querySubObject("Font()");
//     font->setProperty("Name","Times New Roman");
//     font->setProperty("Size",14);
//     QAxObject * align = selection->querySubObject("ParagraphFormat()");
//     align->setProperty("SpaceAfter",0);
//     range->dynamicCall("SetRange(int,int)",0,0);
//     range->setProperty("Text","Решение\n\n");
//     align->setProperty("Alignment",1);

//     for(int i(0);i<vec.size();i++){
//         QString s = "РСЗО с координатами ("+QString::number(vec[i].a.x())+","+QString::number(vec[i].a.y())+") поразит цель с координатами ";
//         if(i!=vec.size()-1){
//             s.push_back("("+QString::number(vec[i].b.x())+","+QString::number(vec[i].b.y())+"); ");
//         }else{
//             s.push_back("("+QString::number(vec[i].b.x())+","+QString::number(vec[i].b.y())+"). ");
//         }

//         range->dynamicCall("SetRange(int,int)",(i+1)*100,(i+1)*100);
//         range->setProperty("Text",s+"\n");
//     }

//     wApp->setProperty("Visible",true);
}

void MainWindow::doc_vozm()
{
    // QVector<Liner> vec =  Solution::retall();
    // QAxObject *wApp = new QAxObject("Word.Application");
    // QAxObject * wDoc = wApp->querySubObject("Documents");
    // wDoc = wDoc->querySubObject("Add()");
    // QAxObject * selection = wApp->querySubObject("Selection()");
    // QAxObject * range = wDoc->querySubObject("Range()");
    // QAxObject * font = selection->querySubObject("Font()");
    // font->setProperty("Name","Times New Roman");
    // font->setProperty("Size",14);
    // QAxObject * align = selection->querySubObject("ParagraphFormat()");
    // align->setProperty("SpaceAfter",0);
    // range->dynamicCall("SetRange(int,int)",0,0);
    // range->setProperty("Text","Решение\n\n");
    // align->setProperty("Alignment",1);

    // for(int i(0);i<vec.size();i++){
    //     int cnt=0;
    //     QVector<Liner>v;
    //     v.clear();
    //     QString s = "РСЗО с координатами ("+QString::number(vec[i].a.x())+","+QString::number(vec[i].a.y())+") может поразить цель с координатами ";
    //     for(int j(i);j<vec.size();j++){
    //         if(vec[i].a==vec[j].a){
    //             cnt++;
    //             v.push_back(vec[j]);
    //         }
    //     }
    //     if(v.empty()){
    //         v.push_back(vec[i]);
    //     }
    //     i+=cnt-1;
    //     for(int j(0);j<v.size();j++){
    //         if(j!=v.size()-1){
    //             s.push_back("("+QString::number(v[j].b.x())+","+QString::number(v[j].b.y())+"), ");
    //         }else{
    //             if(i>=vec.size()-1){
    //                 s.push_back("("+QString::number(v[j].b.x())+","+QString::number(v[j].b.y())+"). ");
    //             }else{
    //                 s.push_back("("+QString::number(v[j].b.x())+","+QString::number(v[j].b.y())+"); ");
    //             }
    //         }
    //     }
    //     range->dynamicCall("SetRange(int,int)",(i+1)*100,(i+1)*100);
    //     range->setProperty("Text",s+"\n");
    // }

    // wApp->setProperty("Visible",true);
}

bool MainWindow::no_repeat(double x, double y)
{
    for(int i(0);i<vec_pro.size();i++){
        if(vec_pro[i].x==x && vec_pro[i].y==y){
            return false;
        }
    }
    for(int i(0);i<vec_tar.size();i++){
        if(vec_tar[i].x==x && vec_tar[i].y==y){
            return false;
        }
    }
    for(int i(0);i<vec_rszo.size();i++){
        if(vec_rszo[i].x==x && vec_rszo[i].y==y){
            return false;
        }
    }
    return true;
}

void MainWindow::on_push()
{
    if(vec_pro.size()>=1 && vec_tar.size()>=1 && vec_rszo.size()>=1){
        ui->pushButton_7->setEnabled(true);
        ui->pushButton_8->setEnabled(true);
    }else{
        ui->pushButton_7->setEnabled(false);
        ui->pushButton_8->setEnabled(false);
        ui->pushButton_5->setEnabled(false);
    }

}

void MainWindow::read(QString path, bool b)
{
     on_pushButton_6_clicked();
     QFile file(path);

        file.open(QIODevice::ReadOnly);
        QString s = file.readLine();
        QStringList q = s.split(" ");
        int n = q[0].toInt();
        for (int i(0); i<n; i++)
        {
            s = file.readLine();
            q = s.split(" ");
            if(no_repeat(q[0].toDouble(),q[1].toDouble()))
            vec_rszo.push_back(RSZO (q[0].toDouble(), q[1].toDouble(), q[2].toDouble()));
        }
        s = file.readLine();
        q = s.split(" ");
        n = q[0].toInt();
        for (int i(0); i<n; i++)
        {
            s = file.readLine();
            q = s.split(" ");
            if(no_repeat(q[0].toDouble(),q[1].toDouble()))
            vec_pro.push_back(PRO (q[0].toDouble(), q[1].toDouble(), q[2].toDouble()));
        }
        s = file.readLine();
        q = s.split(" ");
        n = q[0].toInt();
        for (int i(0); i<n; i++)
        {
            s = file.readLine();
            q = s.split(" ");
            if(no_repeat(q[0].toDouble(),q[1].toDouble()))
            vec_tar.push_back(Target (q[0].toDouble(), q[1].toDouble()));
        }
        if(b){
            s = file.readLine();
            q = s.split(" ");
            n = q[0].toInt();
            if(n==0){
                map.drawChart(vec_rszo,vec_pro,vec_tar);
                status=0;
            }else if(n==1){
                on_pushButton_7_clicked();
                status=1;
            }else if(n==2){
                on_pushButton_8_clicked();
                status=2;
            }
             on_push();
             return;
        }
        map.drawChart(vec_rszo,vec_pro,vec_tar);
        on_push();
        file.close();
}
void MainWindow::on_pushButton_4_clicked()
{
    QString s = QFileDialog :: getOpenFileName(this,tr("Выбрать файл"),QDir::currentPath(),"*.txt");
    if (s != "")
    {
        read(s,false);
    }
}


void MainWindow::on_pushButton_5_clicked()
{
    if(status==1){
        doc_vozm();
    }else if(status==2){
        doc_opt();
    }
}
