#ifndef SHAPE_H
#define SHAPE_H

#include <QString>
#include <vector>
#include <cmath>
#include <memory>

class Shape
{
public:
    virtual ~Shape() {}

    // 添加维度属性
    virtual int dimension() const = 0;

    virtual QString nameEN() const = 0;
    virtual std::vector<QString> parameterNames() const = 0;

    // 面积计算方法
    virtual double area(const std::vector<double>& parameters) const { return 0.0; }

    // 周长计算方法
    virtual double perimeter(const std::vector<double>& parameters) const { return 0.0; }

    // 体积计算方法
    virtual double volume(const std::vector<double>& parameters) const { return 0.0; }

    // 数据合法性检测方法
    virtual bool isValid(const std::vector<double>& parameters) const = 0;
};

// 二维图形类
class TwoDimensionalShape : public Shape
{
public:
    int dimension() const override { return 2; }
};

// 三维形体类
class ThreeDimensionalShape : public Shape
{
public:
    int dimension() const override { return 3; }
};

// 正方形类
class Square : public TwoDimensionalShape
{
public:
    QString nameEN() const override { return "Square"; }
    std::vector<QString> parameterNames() const override { return {"Side Length"}; }

    double area(const std::vector<double>& parameters) const override {
        return parameters[0] * parameters[0];
    }

    double perimeter(const std::vector<double>& parameters) const override {
        return 4 * parameters[0];
    }

    bool isValid(const std::vector<double>& parameters) const override {
        return parameters.size() == 1 && parameters[0] > 0;
    }
};

// 矩形类
class Rectangle : public TwoDimensionalShape
{
public:
    QString nameEN() const override { return "Rectangle"; }
    std::vector<QString> parameterNames() const override { return {"Length", "Width"}; }

    double area(const std::vector<double>& parameters) const override {
        return parameters[0] * parameters[1];
    }

    double perimeter(const std::vector<double>& parameters) const override {
        return 2 * (parameters[0] + parameters[1]);
    }

    bool isValid(const std::vector<double>& parameters) const override {
        return parameters.size() == 2 && parameters[0] > 0 && parameters[1] > 0;
    }
};

// 圆形类
class Circle : public TwoDimensionalShape
{
public:
    QString nameEN() const override { return "Circle"; }
    std::vector<QString> parameterNames() const override { return {"Radius"}; }

    double area(const std::vector<double>& parameters) const override {
        return M_PI * parameters[0] * parameters[0];
    }

    double perimeter(const std::vector<double>& parameters) const override {
        return 2 * M_PI * parameters[0];
    }

    bool isValid(const std::vector<double>& parameters) const override {
        return parameters.size() == 1 && parameters[0] > 0;
    }
};

// 三角形类
class Triangle : public TwoDimensionalShape
{
public:
    QString nameEN() const override { return "Triangle / Base + Height"; }
    std::vector<QString> parameterNames() const override { return {"Base", "Height"}; }

    double area(const std::vector<double>& parameters) const override {
        return 0.5 * parameters[0] * parameters[1];
    }

    double perimeter(const std::vector<double>& parameters) const override {
        // Assuming an equilateral triangle for simplicity
        return 3 * parameters[0];
    }

    bool isValid(const std::vector<double>& parameters) const override {
        return parameters.size() == 2 && parameters[0] > 0 && parameters[1] > 0;
    }
};

// 三角形类（3条边）
class TriangleWithSides : public TwoDimensionalShape
{
public:
    QString nameEN() const override { return "Triangle / 3 Sides"; }
    std::vector<QString> parameterNames() const override { return {"Side A", "Side B", "Side C"}; }

    double area(const std::vector<double>& parameters) const override {
        double a = parameters[0];
        double b = parameters[1];
        double c = parameters[2];
        double s = (a + b + c) / 2; // 半周长
        return sqrt(s * (s - a) * (s - b) * (s - c)); // Heron公式
    }

    double perimeter(const std::vector<double>& parameters) const override {
        return parameters[0] + parameters[1] + parameters[2]; // 周长
    }

    bool isValid(const std::vector<double>& parameters) const override {
        if (parameters.size() != 3) return false;
        double a = parameters[0], b = parameters[1], c = parameters[2];
        return a > 0 && b > 0 && c > 0 && (a + b > c) && (a + c > b) && (b + c > a);
    }
};

// 梯形类
class Trapezoid : public TwoDimensionalShape
{
public:
    QString nameEN() const override { return "Trapezoid"; }
    std::vector<QString> parameterNames() const override { return {"Base1", "Base2", "Height", "Side1", "Side2"}; }

    double area(const std::vector<double>& parameters) const override {
        return 0.5 * (parameters[0] + parameters[1]) * parameters[2];
    }

    double perimeter(const std::vector<double>& parameters) const override {
        return parameters[0] + parameters[1] + parameters[3] + parameters[4];
    }

    bool isValid(const std::vector<double>& parameters) const override {
        return parameters.size() == 5 && parameters[0] > 0 && parameters[1] > 0 && parameters[2] > 0 && parameters[3] > 0 && parameters[4] > 0;
    }
};

// 球体类
class Sphere : public ThreeDimensionalShape
{
public:
    QString nameEN() const override { return "Sphere"; }
    std::vector<QString> parameterNames() const override { return {"Radius"}; }

    double volume(const std::vector<double>& parameters) const override {
        return (4.0 / 3.0) * M_PI * std::pow(parameters[0], 3);
    }

    bool isValid(const std::vector<double>& parameters) const override {
        return parameters.size() == 1 && parameters[0] > 0;
    }
};

// 立方体类
class Cube : public ThreeDimensionalShape
{
public:
    QString nameEN() const override { return "Cube"; }
    std::vector<QString> parameterNames() const override { return {"Side Length"}; }

    double volume(const std::vector<double>& parameters) const override {
        return std::pow(parameters[0], 3);
    }

    bool isValid(const std::vector<double>& parameters) const override {
        return parameters.size() == 1 && parameters[0] > 0;
    }
};

// 长方体类
class RectangularPrism : public ThreeDimensionalShape
{
public:
    QString nameEN() const override { return "Rectangular Prism"; }
    std::vector<QString> parameterNames() const override { return {"Length", "Width", "Height"}; }

    double volume(const std::vector<double>& parameters) const override {
        return parameters[0] * parameters[1] * parameters[2];
    }

    bool isValid(const std::vector<double>& parameters) const override {
        return parameters.size() == 3 && parameters[0] > 0 && parameters[1] > 0 && parameters[2] > 0;
    }
};

// 圆柱类
class Cylinder : public ThreeDimensionalShape
{
public:
    QString nameEN() const override { return "Cylinder"; }
    std::vector<QString> parameterNames() const override { return {"Radius", "Height"}; }

    double volume(const std::vector<double>& parameters) const override {
        return M_PI * std::pow(parameters[0], 2) * parameters[1];
    }

    bool isValid(const std::vector<double>& parameters) const override {
        return parameters.size() == 2 && parameters[0] > 0 && parameters[1] > 0;
    }
};

// 圆锥类
class Cone : public ThreeDimensionalShape
{
public:
    QString nameEN() const override { return "Cone"; }
    std::vector<QString> parameterNames() const override { return {"Radius", "Height"}; }

    double volume(const std::vector<double>& parameters) const override {
        return (1.0 / 3.0) * M_PI * std::pow(parameters[0], 2) * parameters[1];
    }

    bool isValid(const std::vector<double>& parameters) const override {
        return parameters.size() == 2 && parameters[0] > 0 && parameters[1] > 0;
    }
};

std::unique_ptr<Shape> selectShape(const QString& shapeName);

#endif // SHAPE_H
