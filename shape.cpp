#include "shape.h"
#include <memory>
#include <QString>

// 定义一个辅助函数，根据输入字符串返回对应的 Shape 对象
std::unique_ptr<Shape> selectShape(const QString& shapeName)
{
    if (shapeName == "Square") {
        return std::make_unique<Square>();
    } else if (shapeName == "Rectangle" ) {
        return std::make_unique<Rectangle>();
    } else if (shapeName == "Circle") {
        return std::make_unique<Circle>();
    } else if (shapeName == "Triangle2") {
        return std::make_unique<Triangle>();
    } else if (shapeName == "Triangle3") {
        return std::make_unique<TriangleWithSides>();
    } else if (shapeName == "Trapezoid") {
        return std::make_unique<Trapezoid>();
    } else if (shapeName == "Sphere") {
        return std::make_unique<Sphere>();
    } else if (shapeName == "Cube") {
        return std::make_unique<Cube>();
    } else if (shapeName == "RectangularPrism") {
        return std::make_unique<RectangularPrism>();
    } else if (shapeName == "Cylinder") {
        return std::make_unique<Cylinder>();
    } else if (shapeName == "Cone") {
        return std::make_unique<Cone>();
    } else {
        return nullptr; // 未找到匹配的形状，返回空指针
    }
}

