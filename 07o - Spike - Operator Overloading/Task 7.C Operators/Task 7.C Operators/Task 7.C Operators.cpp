#include <iostream>

struct Vector {
    int x, y, z;

    // Constructors for each type
    Vector(int x, int y) : x(x), y(y), z(0) {}

    Vector(int x, int y, int z) : x(x), y(y), z(z) {}

    // Operator overloading
    Vector operator+(const Vector& other) const {
        return Vector(x + other.x, y + other.y, z + other.z);
    }

    Vector& operator+=(const Vector& other) {
        x += other.x;
        y += other.y;
        z += other.z;
        return *this;
    }

    Vector operator-(const Vector& other) const {
        return Vector(x - other.x, y - other.y, z - other.z);
    }

    Vector& operator-=(const Vector& other) {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        return *this;
    }

    bool operator==(const Vector& other) const {
        return (x == other.x && y == other.y && z == other.z);
    }

    Vector operator*(int scalar) const {
        return Vector(x * scalar, y * scalar, z * scalar);
    }

    Vector& operator*=(int scalar) {
        x *= scalar;
        y *= scalar;
        z *= scalar;
        return *this;
    }

    Vector operator/(int scalar) const {
        return Vector(x / scalar, y / scalar, z / scalar);
    }

    Vector& operator/=(int scalar) {
        x /= scalar;
        y /= scalar;
        z /= scalar;
        return *this;
    }

    bool operator>=(const Vector& other) const {
        return (x >= other.x && y >= other.y && z >= other.z);
    }

    bool operator<=(const Vector& other) const {
        return (x <= other.x && y <= other.y && z <= other.z);
    }

    int& operator[](int index) {
        switch (index) {
        case 0: return x;
        case 1: return y;
        case 2: return z;
        default: throw std::out_of_range("Index out of range");
        }
    }

    Vector operator++(int) { // Postfix increment
        Vector temp = *this;
        x++;
        y++;
        z++;
        return temp;
    }

    Vector operator--(int) { // Postfix decrement
        Vector temp = *this;
        x--;
        y--;
        z--;
        return temp;
    }
};

int main() {
    Vector vec1(1, 2);       // 2D Vector
    Vector vec2(1, 2, 3);    // 3D Vector

    Vector x(4, 2, 0);
    Vector y = x;

    std::cout << "Y == X? " << (y == Vector(4, 2, 0)) << "\n"; // returns 1 if y == x and 0 if y != x

    Vector RetVector(0, 0, 0);
    RetVector = Vector(1, 2, 3) + Vector(3, 2, 1);
    std::cout << RetVector.x << " " << RetVector.y << " " << RetVector.z << "\n";

    Vector Multiply = Vector(1, 1, 1) * 3;
    std::cout << Multiply.x << " " << Multiply.y << " " << Multiply.z << "\n";

    Multiply *= 5;
    std::cout << Multiply.x << " " << Multiply.y << " " << Multiply.z << "\n";

    Vector Divide = Vector(10, 10, 10) / 2;
    std::cout << Divide.x << " " << Divide.y << " " << Divide.z << "\n";

    Divide /= 5;
    std::cout << Divide.x << " " << Divide.y << " " << Divide.z << "\n";

    std::cout << "X[1] = " << x[1] << "\n"; // Accessing y using the [] operator

    x++;
    std::cout << "After x++: " << x.x << " " << x.y << " " << x.z << "\n";

    x--;
    std::cout << "After x--: " << x.x << " " << x.y << " " << x.z << "\n";

    std::cout << "X >= Y? " << (x >= y) << "\n";
    std::cout << "X <= Y? " << (x <= y) << "\n";
}
