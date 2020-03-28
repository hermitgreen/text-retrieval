#include "mainwindow.h"
#include "QProgressDialog"
//8本书的拷贝
std::vector<Line> book;

//查询的字符列
std::vector<Word> list;

//获取书名
std::string getName(int bookNumber){
    std::string bookName;
    switch (bookNumber) {
    case 1:
        bookName = "HP_0_Harry_Potter_Prequel";
        break;
    case 2:
        bookName = "HP_2_Chamber_of_Secrets";
        break;
    case 3:
        bookName = "HP_3_Prisoner_of_Azkaban";
        break;
    case 4:
        bookName = "HP_4_Goblet_of_Fire";
        break;
    case 5:
        bookName = "HP_6_Hlaf-Blood_Prince";
        break;
    case 6:
        bookName = "HP_7_Deathly_Hallows_Book";
        break;
    case 7:
        bookName = "Quidditch_Through_the_Ages";
        break;
    case 8:
        bookName = "The_Tales_of_Beedle_the_Bard";
        break;
    default:
        break;
    }
	return bookName;
}

//初始化数据
void init() {
	std::string temp;
    for(int i=1;i<=8;i++){
        std::ifstream infile;
        switch (i) {
        case 1:
            //读入vector
               infile.open("1.txt");
               while (std::getline(infile,temp))
               {
                   Line l;
                   l.book = 1;
                   l.string = temp;
                   book.push_back(l);
               }
            break;
        case 2:
            infile.open("2.txt");
            while (std::getline(infile, temp))
            {
                Line l;
                l.book = 2;
                l.string = temp;
                book.push_back(l);
            }
            break;
        case 3:
            infile.open("3.txt");
            while (std::getline(infile, temp))
            {
                Line l;
                l.book = 3;
                l.string = temp;
                book.push_back(l);
            }
            break;
        case 4:
            infile.open("4.txt");
            while (std::getline(infile, temp))
            {
                Line l;
                l.book = 4;
                l.string = temp;
                book.push_back(l);
            }
            break;
        case 5:
            infile.open("5.txt");
            while (std::getline(infile, temp))
            {
                Line l;
                l.book = 5;
                l.string = temp;
                book.push_back(l);
            }
            break;
        case 6:
            infile.open("6.txt");
            while (std::getline(infile, temp))
            {
                Line l;
                l.book = 6;
                l.string = temp;
                book.push_back(l);
            }
            break;
        case 7:
            infile.open("7.txt");
            while (std::getline(infile, temp))
            {
                Line l;
                l.book = 7;
                l.string = temp;
                book.push_back(l);
            }
            break;
        case 8:
            infile.open("8.txt");
            while (std::getline(infile, temp))
            {
                Line l;
                l.book = 8;
                l.string = temp;
                book.push_back(l);
            }
            break;
        default:
            break;
        }
        infile.clear();
        infile.close();
    }
}
//判断是否为数字
bool isNumber(std::string str){
    bool flag;
    if(str[0] <= '9' && str[0]>='0'){
        flag = true;
    } else{
        flag = false;
    }
    return flag;
}
//查询字符串
void MainWindow::query(std::string word) {
    //页数和章节
    int page = 1;
    int chap = 1;
    std::string Chapter = "CHAPTER";
    std::string chapter = "Chapter";
    std::string temp;
    //第几本书
    int bk = 1;
    for(auto c : book){
        //分解字符串
        std::istringstream is(c.string);
        //读取特征码
        is >> temp;
        //判断该段是否为章节号
        if(temp == Chapter || temp == chapter){
            chap++;
            continue;
        }
        //判断该段是否为页号
        if(isNumber(temp)){
            page++;
            continue;
        }
        if(bk != c.book){
            bk++;
            page = 1;
            chap = 1;
        }
        do {
            //QString qs = QString::fromStdString(temp);
            //ui->textBrowser->append(qs);
            if(temp == word){
                Word w;
                w.book = c.book;
				w.page = page;
				w.text = c.string;
                w.chapter = chap;
				list.push_back(w);
            }
        }while (is >> temp);
    }
}
//查询详情
std::string query_detail(int index){
    std::string rtn = std::to_string(index) + ": ";

    if(index <= list.size()){
        rtn = list[index - 1].text;
    } else {
        rtn = "您输入了不合适的数据";
    }
    return rtn;
}
//打印详情
void MainWindow::print(std::string name) {
	int index = 1;
	for (auto c : list) {
        std::string str = std::to_string(index) + " " + name +" "+std::to_string(c.page)+" "
                +std::to_string(c.chapter)+" "+ getName(c.book);
		QString qs = QString::fromStdString(str);
        ui->textBrowser->append(qs);
        index++;
	}
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //设置主界面
    ui->setupUi(this);
    //无边框
    this->setWindowFlags(Qt::FramelessWindowHint);
    //隐藏清空按钮,查询详情按钮,返回按钮,详细内容显示界面,提示框
    ui->CLR_btn->hide();
    ui->query_no->hide();
    ui->back_btn->hide();
    ui->detail->hide();
    ui->result_label->hide();
    ui->progressBar->hide();
    //连接按钮的信号槽
    connect(ui->pushButton,&QPushButton::clicked,this,
            &MainWindow::buttonIsClicked);
    connect(ui->CLR_btn,&QPushButton::clicked,this,
            &MainWindow::CLRbuttonIsClicked);
    connect(ui->CL_btn,&QPushButton::clicked,this,
            &MainWindow::closeButtonIsClicked);
    connect(ui->query_no,&QPushButton::clicked,this,
            &MainWindow::queryNoButtonIsClicked);
    connect(ui->back_btn,&QPushButton::clicked,this,
            &MainWindow::backButtonIsClicked);
	//初始化数据
    init();
}

MainWindow::~MainWindow()
{
    delete ui;
}
//搜索按钮点击事件
void MainWindow::buttonIsClicked(){
    //进度条
    ui->progressBar->setValue(40);
    ui->progressBar->show();
    //显示页顶条
    ui->result_label->show();
    //获取用户输入的信息
    std::string word = ui->lineEdit->text().toStdString();
    //查询
	query(word);
    ui->progressBar->setValue(60);
	//输出
    print(word);
    //置入新的提示语
    ui->progressBar->setValue(100);
    ui->progressBar->hide();
    ui->hint_label->setText("您可进一步查找|清空您的输入");
    //置入输入约束，要求范围为一个整数
    QValidator *validator = new QIntValidator(1,9999,this);
    ui->lineEdit->setValidator(validator);
    //显示清空按钮和显示详情按钮
    ui->CLR_btn->show();
    ui->query_no->show();
    //隐藏搜索按钮
    ui->pushButton->hide();
    //制作一个空串
    QString nullString = "";
    //清空输入框
    ui->lineEdit->setText(nullString);
}
//返回按钮点击事件
void MainWindow::backButtonIsClicked(){
    //调整控件
    ui->back_btn->hide();
    ui->detail->hide();
    ui->query_no->show();
    ui->textBrowser->show();
    //取消输入约束
    ui->lineEdit->setValidator(0);
    //清空输入框
    QString nullString = "";
    ui->lineEdit->setText(nullString);
}
//显示详情按钮点击事件
void MainWindow::queryNoButtonIsClicked(){
    //获得操作符
    int word = ui->lineEdit->text().toInt();
    //查询
    QString qs = QString::fromStdString(query_detail(word));
    //显示
    ui->detail->setText(qs);
    //约束：不允许输入
    QValidator *validator = new QIntValidator(0,0,this);
    ui->lineEdit->setValidator(validator);
    //控件的调整
    ui->textBrowser->hide();
    ui->query_no->hide();
    ui->back_btn->show();
    ui->detail->show();
}
//清空按钮点击事件
void MainWindow::CLRbuttonIsClicked(){
    //制作一个空串
    QString nullString = "";
    //制作新的提示语
    //Tips：在linux下汉字“或”会在UTF-8码下产生冲突。故以‘/’代替之
    QString welcome = "请您输入人名/地名";
    //清空输出框
    ui->textBrowser->setText(nullString);
    ui->textBrowser->show();
    //隐藏清空按钮
    ui->CLR_btn->hide();
    //显示搜索按钮
    ui->pushButton->show();
    //隐藏详情按钮
    ui->query_no->hide();
    //置入新的提示语
    ui->hint_label->setText(welcome);
    //取消输入约束
    ui->lineEdit->setValidator(0);
    //隐藏详情页
    ui->detail->hide();
    //隐藏返回按钮
    ui->back_btn->hide();
    //清空上一次查询的数据
    list.clear();
}

//关闭程序点击事件
void MainWindow::closeButtonIsClicked(){
    QApplication* a;
    a->quit();
}




