#include <iostream>
#include <cmath>  
#include <string>
#include <vector>
#include <algorithm>
 
using namespace std;
 
class Shape {
private:
    static int objectCount; // Объектуудыг тоолох статик хувьсагч
    
public:
    string name;
    float side;

    // Объектийн тоог оноох болон авах статик гишүүн функцууд
    static void setObjectCount(int count) {
        objectCount = count;
    }
    
    static int getObjectCount() {
        return objectCount;
    }

    // Shape классын байгуулагч функц
    Shape() : name(""), side(0) {
        this->objectCount++; // Объект үүсэхэд тоолуурыг нэмэгдүүлэх
    }
    
    Shape(string n, float s) : name(n), side(s) {
        this->objectCount++; // this заагчийг ашиглах
    }
    
    // Устгагч функц
    virtual ~Shape() {
        this->objectCount--; // Объект устахад тоолуурыг багасгах
    }
 
    void Input() {
        cout << "Дүрсийн нэрийг оруулна уу: ";
        cin >> this->name; // this заагчийг ашиглах
        cout << "Талын урт эсвэл радиусыг оруулна уу: ";
        cin >> this->side; // this заагчийг ашиглах
    }
    
    // Объектийн тоог хэвлэх статик функц
    static void printObjectCount() {
        cout << "Одоогийн дүрсийн объектуудын тоо: " << objectCount << endl;
    }
};

// Статик гишүүн хувьсагчийг эхлүүлэх
int Shape::objectCount = 0;
 
class Vertex {
public:
    float x_p;
    float y_p;
    
    // Vertex классын байгуулагч
    Vertex() : x_p(0), y_p(0) {}
    Vertex(float x, float y) : x_p(x), y_p(y) {}
};
 
class TwoDShape : public Shape {
public:
    float x_coordinate;
    float y_coordinate;
    float area;
    float perimeter;
 
    // Эцэг классын байгуулагчийг дуудах байгуулагч
    TwoDShape() : Shape(), x_coordinate(0), y_coordinate(0), area(0), perimeter(0) {}
    
    TwoDShape(string n, float s, float x_p, float y_p) 
        : Shape(n, s), x_coordinate(x_p), y_coordinate(y_p), area(0), perimeter(0) {}
        
    // Талбай тооцох жинхэнэ хийсвэр функц
    virtual void Area1() = 0;
    
    // Периметр тооцох жинхэнэ хийсвэр функц
    virtual void Perimeter1() = 0;
    
    // Дэлгэцлэх жинхэнэ хийсвэр функц
    virtual void Display() = 0;
    
    // Талбайг авах функц (эрэмбэлэхэд)
    float getArea() {
        return this->area;
    }
    
    // Периметрийг авах функц (эрэмбэлэхэд)
    float getPerimeter() {
        return this->perimeter;
    }
};
 
const float pi = 3.14159;
 
class Circle : public TwoDShape {
public:
    // Эцэг классын байгуулагчийг дуудах байгуулагч
    Circle() : TwoDShape() {}
    
    Circle(float x_p, float y_p, float radius) 
        : TwoDShape("Тойрог", radius, x_p, y_p) {}
 
    void Area1() override {
        this->area = this->side * this->side * pi; // this заагчийг ашиглах
    }
 
    void Perimeter1() override {
        this->perimeter = this->side * 2 * pi; // this заагчийг ашиглах
    }
 
    void Input() {
        this->name = "Тойрог"; // this заагчийг ашиглах
        cout << "Тойргийн радиусыг оруулна уу: ";
        cin >> this->side; // this заагчийг ашиглах
        cout << "Төвийн X координатыг оруулна уу: ";
        cin >> this->x_coordinate; // this заагчийг ашиглах
        cout << "Төвийн Y координатыг оруулна уу: ";
        cin >> this->y_coordinate; // this заагчийг ашиглах
    }
 
    void Display() override {
        cout << "Радиус " << this->side // this заагчийг ашиглах
             << " ба төв координат (" << this->x_coordinate << ", " << this->y_coordinate 
             << ")-тай тойрог: Талбай = " << this->area << ", Периметр = " << this->perimeter << endl;
    }
};
 
class Square : public TwoDShape {
public:
    Vertex UpLeft, UpRight, DownLeft, DownRight;
 
    // Эцэг классын байгуулагчийг дуудах байгуулагч
    Square() : TwoDShape() {}
    
    Square(float x_p, float y_p, float side_length) 
        : TwoDShape("Квадрат", side_length, x_p, y_p) {}
 
    void Area1() override {
        this->area = this->side * this->side; // this заагчийг ашиглах
    }
 
    void Perimeter1() override {
        this->perimeter = this->side * 4; // this заагчийг ашиглах
    }
 
    void Input() {
        this->name = "Квадрат"; // this заагчийг ашиглах
        cout << "Квадратын талын уртыг оруулна уу: ";
        cin >> this->side; // this заагчийг ашиглах
        cout << "X координатыг оруулна уу: ";
        cin >> this->x_coordinate; // this заагчийг ашиглах
        cout << "Y координатыг оруулна уу: ";
        cin >> this->y_coordinate; // this заагчийг ашиглах
    }
 
    void findingvertexes() {
        this->UpLeft = Vertex(this->x_coordinate, this->y_coordinate); // this заагчийг ашиглах
        this->DownRight.x_p = this->x_coordinate + this->side;
        this->DownRight.y_p = this->y_coordinate - this->side;
 
        this->UpRight.x_p = this->x_coordinate + this->side;
        this->UpRight.y_p = this->y_coordinate;
        
        this->DownLeft.x_p = this->x_coordinate; 
        this->DownLeft.y_p = this->y_coordinate - this->side;
        
        cout << "Квадратын оройнууд:\n";
        cout << "Доод зүүн: (" << this->DownLeft.x_p << ", " << this->DownLeft.y_p << ")\n";
        cout << "Доод баруун: (" << this->DownRight.x_p << ", " << this->DownRight.y_p << ")\n";
        cout << "Дээд баруун: (" << this->UpRight.x_p << ", " << this->UpRight.y_p << ")\n";
        cout << "Дээд зүүн: (" << this->x_coordinate << ", " << this->y_coordinate<< ")\n";
    }
 
    void Display() override {
        cout << "Тал " << this->side // this заагчийг ашиглах
             << "-тай квадрат: Талбай = " << this->area 
             << ", Периметр = " << this->perimeter << endl;
    }
};
 
class EquiTriangle : public TwoDShape {
public:
    Vertex bottomLeft, bottomRight, topVertex;
 
    // Эцэг классын байгуулагчийг дуудах байгуулагч
    EquiTriangle() : TwoDShape() {}
    
    EquiTriangle(float x_p, float y_p, float side_length) 
        : TwoDShape("Гурвалжин", side_length, x_p, y_p) {}
 
    void Area1() override {
        this->area = (sqrt(3) / 4) * this->side * this->side; // this заагчийг ашиглах
    }
 
    void Perimeter1() override {
        this->perimeter = this->side * 3; // this заагчийг ашиглах
    }
 
    void Input() {
        this->name = "Гурвалжин"; // this заагчийг ашиглах
        cout << "Тэгш талт гурвалжны талын уртыг оруулна уу: ";
        cin >> this->side; // this заагчийг ашиглах
        cout << "X координатыг оруулна уу: ";
        cin >> this->x_coordinate; // this заагчийг ашиглах
        cout << "Y координатыг оруулна уу: ";
        cin >> this->y_coordinate; // this заагчийг ашиглах
    }
 
    void findingvertexes() {
        this->topVertex = Vertex(this->x_coordinate, this->y_coordinate); // this заагчийг ашиглах
        
        this->bottomRight.x_p = this->x_coordinate - (this->side/2);
        this->bottomRight.y_p = this->y_coordinate - (sqrt(3) / 2) * this->side;
 
        this->bottomLeft.x_p = this->x_coordinate + (this->side / 2);
        this->bottomLeft.y_p = this->y_coordinate - (sqrt(3) / 2) * this->side;
 
        cout << "Тэгш талт гурвалжны оройнууд:\n";
        cout << "Доод зүүн: (" << this->bottomLeft.x_p << ", " << this->bottomLeft.y_p << ")\n";
        cout << "Доод баруун: (" << this->bottomRight.x_p << ", " << this->bottomRight.y_p << ")\n";
        cout << "Дээд орой: (" << this->x_coordinate << ", " << this->y_coordinate << ")\n";
    }
 
    void Display() override {
        cout << "Тал " << this->side // this заагчийг ашиглах
             << "-тай тэгш талт гурвалжин: Талбай = " << this->area 
             << ", Периметр = " << this->perimeter << endl;
    }
};

// Дүрсүүдийг талбайгаар нь эрэмбэлэх функц
bool compareByArea(TwoDShape* a, TwoDShape* b) {
    return a->getArea() < b->getArea();
}

// Дүрсүүдийг периметрээр нь эрэмбэлэх функц
bool compareByPerimeter(TwoDShape* a, TwoDShape* b) {
    return a->getPerimeter() < b->getPerimeter();
}
 
int main() {
    int choice;
    int continue1;
    vector<TwoDShape*> shapes;
 
    cout << "Та дүрс оруулахыг хүсч байна уу? (Тийм - 1, Үгүй - 0): ";
    cin >> continue1;
 
    while (continue1 == 1) {
        cout << "Дүрс сонгоно уу:\n1. Тойрог\n2. Квадрат\n3. Тэгш талт гурвалжин\nСонголтоо оруулна уу: ";
        cin >> choice;
 
        if (choice == 1) {
            Circle* c = new Circle();
            c->Input();
            c->Area1();
            c->Perimeter1();
            c->Display();
            shapes.push_back(c);
        } else if (choice == 2) {
            Square* s = new Square();
            s->Input();
            s->Area1();
            s->Perimeter1();
            s->Display();
            s->findingvertexes();
            shapes.push_back(s);
        } else if (choice == 3) {
            EquiTriangle* t = new EquiTriangle();
            t->Input();
            t->Area1();
            t->Perimeter1();
            t->Display();
            t->findingvertexes();
            shapes.push_back(t);
        } else {
            cout << "Алдаа! 1, 2, эсвэл 3 гэж оруулна уу." << endl;
        }
        
        // Одоогийн дүрсийн объектуудын тоог харуулах
        Shape::printObjectCount();
 
        cout << "Та өөр дүрс оруулахыг хүсч байна уу? (Тийм - 1, Үгүй - 0): ";
        cin >> continue1;
    }
    
    // Дүрсүүдийг талбайгаар нь эрэмбэлэх
    if (!shapes.empty()) {
        sort(shapes.begin(), shapes.end(), compareByArea);
        
        cout << "\n\nТалбайгаар эрэмбэлсэн дүрсүүд (бага-их):\n";
        for (TwoDShape* shape : shapes) {
            shape->Display();
        }
        
        // Дүрсүүдийг периметрээр нь эрэмбэлэх
        sort(shapes.begin(), shapes.end(), compareByPerimeter);
        
        cout << "\n\nПериметрээр эрэмбэлсэн дүрсүүд (бага-их):\n";
        for (TwoDShape* shape : shapes) {
            shape->Display();
        }
    }
    
    // Санах ойг чөлөөлөх
    for (TwoDShape* shape : shapes) {
        delete shape;
    }
    
    // Эцсийн объектийн тоо (хэрэв бүх объект зөв устсан бол 0 байх ёстой)
    Shape::printObjectCount();
 
    return 0;
}