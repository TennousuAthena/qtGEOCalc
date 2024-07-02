#include "widget.h"
#include "ui_widget.h"
#include "shape.h"
#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    // 设置形状下拉框的选项
    ui->shapeComboBox->addItem("Square");
    ui->shapeComboBox->addItem("Rectangle");
    ui->shapeComboBox->addItem("Circle");
    ui->shapeComboBox->addItem("Triangle2");
    ui->shapeComboBox->addItem("Triangle3");
    ui->shapeComboBox->addItem("Trapezoid");
    ui->shapeComboBox->addItem("Sphere");
    ui->shapeComboBox->addItem("Cube");
    ui->shapeComboBox->addItem("RectangularPrism");
    ui->shapeComboBox->addItem("Cylinder");
    ui->shapeComboBox->addItem("Cone");

    connect(ui->calculateAreaPerimeterButton, &QPushButton::clicked, this, &Widget::calculateAreaPerimeter);
    connect(ui->calculateVolumeButton, &QPushButton::clicked, this, &Widget::calculateVolume);
    connect(ui->shapeComboBox, &QComboBox::currentIndexChanged, this, &Widget::updateUI);

    updateUI(); // 初始化界面状态
}

Widget::~Widget()
{
    delete ui;
}

void Widget::calculateAreaPerimeter()
{
    QString shapeName = ui->shapeComboBox->currentText();
    auto shape = selectShape(shapeName);

    if (!shape) {
        ui->resultTextEdit->setText("Shape not found");
        return;
    }

    std::vector<double> parameters;
    if (!ui->parameterInput1->text().isEmpty()) parameters.push_back(ui->parameterInput1->text().toDouble());
    if (!ui->parameterInput2->text().isEmpty()) parameters.push_back(ui->parameterInput2->text().toDouble());
    if (!ui->parameterInput3->text().isEmpty()) parameters.push_back(ui->parameterInput3->text().toDouble());
    if (!ui->parameterInput4->text().isEmpty()) parameters.push_back(ui->parameterInput4->text().toDouble());
    if (!ui->parameterInput5->text().isEmpty()) parameters.push_back(ui->parameterInput5->text().toDouble());

    if (!shape->isValid(parameters)) {
        ui->resultTextEdit->setText("Invalid parameters");
        return;
    }

    double area = shape->area(parameters);
    double perimeter = shape->perimeter(parameters);

    QString result = QString("Area: %1\nPerimeter: %2").arg(area).arg(perimeter);
    ui->resultTextEdit->setText(result);
}

void Widget::calculateVolume()
{
    QString shapeName = ui->shapeComboBox->currentText();
    auto shape = selectShape(shapeName);

    if (!shape) {
        ui->resultTextEdit->setText("Shape not found");
        return;
    }

    std::vector<double> parameters;
    if (!ui->parameterInput1->text().isEmpty()) parameters.push_back(ui->parameterInput1->text().toDouble());
    if (!ui->parameterInput2->text().isEmpty()) parameters.push_back(ui->parameterInput2->text().toDouble());
    if (!ui->parameterInput3->text().isEmpty()) parameters.push_back(ui->parameterInput3->text().toDouble());
    if (!ui->parameterInput4->text().isEmpty()) parameters.push_back(ui->parameterInput4->text().toDouble());
    if (!ui->parameterInput5->text().isEmpty()) parameters.push_back(ui->parameterInput5->text().toDouble());

    if (!shape->isValid(parameters)) {
        ui->resultTextEdit->setText("Invalid parameters");
        return;
    }

    double volume = shape->volume(parameters);

    QString result = QString("Volume: %1").arg(volume);
    ui->resultTextEdit->setText(result);
}

void Widget::updateUI()
{
    QString shapeName = ui->shapeComboBox->currentText();
    auto shape = selectShape(shapeName);

    if (!shape) {
        return;
    }

    int dimension = shape->dimension();

    // 显示或隐藏体积和面积/周长相关控件
    if (dimension == 2) {
        ui->calculateVolumeButton->hide();
        ui->calculateAreaPerimeterButton->show();
    } else if (dimension == 3) {
        ui->calculateVolumeButton->show();
        ui->calculateAreaPerimeterButton->hide();
    }

    // 显示或隐藏参数输入框，并更新标签
    quint8 paramNums = shape->parameterNames().size();

    ui->label1->setText(paramNums > 0 ? shape->parameterNames()[0] : "");
    ui->parameterInput1->setVisible(paramNums > 0);

    ui->label2->setText(paramNums > 1 ? shape->parameterNames()[1] : "");
    ui->parameterInput2->setVisible(paramNums > 1);

    ui->label3->setText(paramNums > 2 ? shape->parameterNames()[2] : "");
    ui->parameterInput3->setVisible(paramNums > 2);

    ui->label4->setText(paramNums > 3 ? shape->parameterNames()[3] : "");
    ui->parameterInput4->setVisible(paramNums > 3);

    ui->label5->setText(paramNums > 4 ? shape->parameterNames()[4] : "");
    ui->parameterInput5->setVisible(paramNums > 4);
}
