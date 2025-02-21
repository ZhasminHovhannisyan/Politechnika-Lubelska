#include <iostream>
#include <cstdlib>
using namespace std;

class vector3w  //class definition
{
    float x, y, z;
 public:
    vector3w(float a = 0.0, float b = 0.0, float c = 0.0) {x = a; y = b; z = c;}
    void display();
    vector3w sum(vector3w &v);
    vector3w operator+(vector3w &v);

};

// simple sum function as a class method
vector3w vector3w::sum(vector3w &v)
{
    vector3w w;
    w.x = x + v.x;
    w.y = y + v.y;
    w.z = z + v.z;
    return w;
}

// overloaded operator +
vector3w vector3w::operator+(vector3w &v)
{
    vector3w w;
    w.x = x + v.x;
    w.y = y + v.y;
    w.z = z + v.z;
    return w;
}

void vector3w::display()
{
    cout << "[" << x << "," << y << "," << z << "]";
}

int main()
{
    system("clear");
    vector3w v1(1, 2, 3), v2(3, 0, 2), w;
    cout << "\nv1="; v1.display();
    cout << "\nv2="; v2.display();
    w = v1.sum(v2);
    cout << "\nw=v1.sum(v2)="; w.display();
    w = v1.operator+(v2);
    cout << "\nw=v1.operator+(v2)="; w.display();

    //the same, but in a simpler form using an overloaded operator +
    w = v1 + v2;
    cout << "\nw = v1 + v2 = "; w.display();
    cout << endl;
    return 0;
}
