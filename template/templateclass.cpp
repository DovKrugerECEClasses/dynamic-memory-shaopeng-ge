#include <iostream>
using namespace std;

template <typename Precision>
class Vec3d{
private:
    Precision x, y, z;
public:
    Vec3d(Precision a, Precision b, Precision c) : x(a), y(b), z(c){}

    friend Vec3d operator +(const Vec3d &a, const Vec3d &b){
        return Vec3d(a.x + b.x, a.y + b.y, a.z + b.z);
    }

    friend ostream& operator <<(ostream & s, const Vec3d& a){
        return s << "(" << a.x << ", " << a.y << ", " << a.z << ")" << "\n";
    }
};


int main() {
    Vec3d<float> a(1,2,3);
    Vec3d<double> b(1.5, 2.2, 3.5);
    cout << a << b << '\n';
    Vec3d<double> c(1.9, 1.1, 4.1);
    cout << b + c << '\n';
}