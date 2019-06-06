/*******************************************************************************
 * Name          : mypoint.cpp
 * Author        : Brian S. Borowski
 * Version       : 1.0
 * Date          : January 9, 2016
 * Last modified : September 7, 2017
 * Description   : Class that represents a point in 3D space.
 ******************************************************************************/
#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

class MyPoint {

public:
    // Constructor that uses an initializer list.
    MyPoint(int x, int y, float z) : x_{x}, y_{y}, z_{z} { }
    // by the time the constructor complets all memeber variables must be initialized

    // Methods that do not modify member variables should be declared const.
    void print_coords() const {
        cout << "(x, y, z) = (" << x_ << ", " << y_ << ", " << fixed
             << setprecision(2) << z_ << ")" << endl;
    }

    // Mutator.
    void set_x(int x) {
        x_ = x;
    }

    // Accessor.
    int get_x() const {
        return x_;
    }
    // the order in which the private member variables appear/declared is the same order in which they must be initialized
private:
    // Member variables (fields). Use the trailing _ for these variables.
    int x_, y_;
    float z_;

};

void display_points(const vector<MyPoint> &points) {
    for (auto it = points.cbegin(); it != points.cend(); ++it) {
        it->print_coords();
    }
}

int main() {
    int x, y;

    MyPoint point1(5, 7, 1.9823412);
    MyPoint point2(1, 2, 3);
    MyPoint point3(4, 5, 6);

    vector<MyPoint> points;
    points.push_back(point1);
    points.push_back(point2);
    points.push_back(point3);

    vector<MyPoint> points_above_two;
    for (const auto &point : points) {
        if (point.get_x() > 2) {
            points_above_two.push_back(point);
        }
    }

    display_points(points_above_two);

    // Practice using standard in (STDIN).
    cout << "Input x: ";
    cin >> x;

    cout << "Input y: ";
    cin >> y;

    MyPoint some_point(x, y, 7);
    some_point.print_coords();
    return 0;
}
