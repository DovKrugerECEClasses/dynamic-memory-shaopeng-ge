#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <vector>
using namespace std;

const double PI = 3.14159265359;


class Vertex{
public:
    double x,y,z;
    Vertex(const double &x, const double &y, const double &z):x(x),y(y),z(z){}
    friend ostream& operator <<(ostream& s, const Vertex v){
        s << v.x << " " << v.y << " " << v.z << "\n";
        return s;
    }
};

class facetNormal{
private:
    double x,y,z;
public:
    facetNormal(const double &x, const double &y, const double &z):x(x),y(y),z(z){}
    friend ostream& operator <<(ostream& s, const facetNormal n){
        s << n.x << " " << n.y << " " << n.z << "\n";
        return s;
    }
};

facetNormal getNormal(const Vertex a,const Vertex b,const Vertex c){
    double x = (b.y - a.y)*(c.z - a.z) - (b.z - a.z)*(c.y - a.y);
    double y = (b.z - a.z)*(c.x - a.x) - (b.x - a.x)*(c.z - a.z);
    double z = (b.x - a.x)*(c.y - a.y) - (b.y - a.y)*(c.x - a.x);
    return facetNormal(x,y,z);
}

class Cube{
public:
    double s,x,y,z;
public:
    Cube(double s):s(s),x(0),y(0),z(0){}

    void translate(double dx, double dy, double dz){
        x += dx;
        y += dy;
        z += dz;
    }

    double volume(){
        return pow(s,3);
    }

    void write(const string& name){
        ofstream wr(name);
        wr << "solid " << name << "\n";

        Vertex a(0,0,0);
        Vertex b(s,0,0);
        Vertex c(s,s,0);
        Vertex d(0,s,0);
        Vertex e(0,0,s);
        Vertex f(s,0,s);
        Vertex g(s,s,s);
        Vertex h(0,s,s);

           //bottom side
        wr << "  facet normal" << "0 0 -1\n"
           << "    outer loop\n"
           << "      vertex " << a
           << "      vertex " << d
           << "      vertex " << b
           << "    endloop\n"
           << "  endfacet\n"

           << "  facet normal" << "0 0 -1\n"
           << "    outer loop\n"
           << "      vertex " << b
           << "      vertex " << d
           << "      vertex " << c
           << "    endloop\n"
           << "  endfacet\n"
           //back side
           << "  facet normal" << "-1 0 0\n"
           << "    outer loop\n"
           << "      vertex " << a
           << "      vertex " << e
           << "      vertex " << d
           << "    endloop\n"
           << "  endfacet\n"

           << "  facet normal" << "-1 0 0\n"
           << "    outer loop\n"
           << "      vertex " << d
           << "      vertex " << e
           << "      vertex " << h
           << "    endloop\n"
           << "  endfacet\n"
           //left side
           << "  facet normal" << "0 -1 0\n"
           << "    outer loop\n"
           << "      vertex " << b
           << "      vertex " << f
           << "      vertex " << e
           << "    endloop\n"
           << "  endfacet\n"

           << "  facet normal" << "0 -1 0\n"
           << "    outer loop\n"
           << "      vertex " << b
           << "      vertex " << e
           << "      vertex " << a
           << "    endloop\n"
           << "  endfacet\n"
           //right side
           << "  facet normal" << "0 1 0\n"
           << "    outer loop\n"
           << "      vertex " << d
           << "      vertex " << h
           << "      vertex " << g
           << "    endloop\n"
           << "  endfacet\n"

           << "  facet normal" << "0 1 0\n"
           << "    outer loop\n"
           << "      vertex " << d
           << "      vertex " << g
           << "      vertex " << c
           << "    endloop\n"
           << "  endfacet\n"
           //front side
           << "  facet normal" << "1 0 0\n"
           << "    outer loop\n"
           << "      vertex " << b
           << "      vertex " << g
           << "      vertex " << f
           << "    endloop\n"
           << "  endfacet\n"

           << "  facet normal" << "1 0 0\n"
           << "    outer loop\n"
           << "      vertex " << c
           << "      vertex " << g
           << "      vertex " << b
           << "    endloop\n"
           << "  endfacet\n"
           //up side
           << "  facet normal" << "0 0 1\n"
           << "    outer loop\n"
           << "      vertex " << f
           << "      vertex " << g
           << "      vertex " << e
           << "    endloop\n"
           << "  endfacet\n"

           << "  facet normal" << "0 0 1\n"
           << "    outer loop\n"
           << "      vertex " << h
           << "      vertex " << e
           << "      vertex " << g
           << "    endloop\n"
           << "  endfacet\n"


           <<"endsolid " << name << "\n";
    }


};

class Cylinder{
public:
    double r,h;
    int fn;
public:
    Cylinder(double r, double h):r(r),h(h),fn(50){}
    void write(const string& name){
        ofstream f(name);
        f << "solid " << name << "\n";
        for (double i = 0; i < 2*PI; i += PI*2/fn) {
            Vertex a(r*cos(i),r*sin(i),0);
            Vertex b(r*cos(i+PI*2/fn),r*sin(i+PI*2/fn),0);
            Vertex c(r*cos(i),r*sin(i),h);
            Vertex d(r*cos(i+PI*2/fn),r*sin(i+PI*2/fn),h);
            Vertex o1(0,0,0);
            Vertex o2(0,0,h);

            facetNormal n = getNormal(a,b,c);
            facetNormal up (0,0,-1);
            facetNormal down (0,0,1);

            f << "  facet normal " << n
              << "    outer loop\n"
              << "      vertex " << a
              << "      vertex " << b
              << "      vertex " << c
              << "    endloop\n"
              << "  endfacet\n"

              << "  facet normal " << n
              << "    outer loop\n"
              << "      vertex " << b
              << "      vertex " << d
              << "      vertex " << c
              << "    endloop\n"
              << "  endfacet\n"

              << "  facet normal " << down
              << "    outer loop\n"
              << "      vertex " << a
              << "      vertex " << o1
              << "      vertex " << b
              << "    endloop\n"
              << "  endfacet\n"

              << "  facet normal " << up
              << "    outer loop\n"
              << "      vertex " << c
              << "      vertex " << d
              << "      vertex " << o2
              << "    endloop\n"
              << "  endfacet\n";
        }
        f <<"endsolid " << name << "\n";
    }
};

class Design{
private:
   Cube c1;
   Cylinder c2;
public:
    Design():c1(Cube(0)),c2(Cylinder(0,0)){}
    void add(Cube c){
        c1 = c;
    }
    void add(Cylinder cyl){
        c2 = cyl;
    }
    void write(const string& name){
        ofstream wr(name);
        wr << "solid " << name << "\n";
        Vertex a(0,0,0);
        Vertex b(c1.s,0,0);
        Vertex c(c1.s,c1.s,0);
        Vertex d(0,c1.s,0);
        Vertex e(0,0,c1.s);
        Vertex f(c1.s,0,c1.s);
        Vertex g(c1.s,c1.s,c1.s);
        Vertex h(0,c1.s,c1.s);
        //bottom side
        wr << "  facet normal" << "0 0 -1\n"
           << "    outer loop\n"
           << "      vertex " << a
           << "      vertex " << d
           << "      vertex " << b
           << "    endloop\n"
           << "  endfacet\n"

           << "  facet normal" << "0 0 -1\n"
           << "    outer loop\n"
           << "      vertex " << b
           << "      vertex " << d
           << "      vertex " << c
           << "    endloop\n"
           << "  endfacet\n"
           //back side
           << "  facet normal" << "-1 0 0\n"
           << "    outer loop\n"
           << "      vertex " << a
           << "      vertex " << e
           << "      vertex " << d
           << "    endloop\n"
           << "  endfacet\n"

           << "  facet normal" << "-1 0 0\n"
           << "    outer loop\n"
           << "      vertex " << d
           << "      vertex " << e
           << "      vertex " << h
           << "    endloop\n"
           << "  endfacet\n"
           //left side
           << "  facet normal" << "0 -1 0\n"
           << "    outer loop\n"
           << "      vertex " << b
           << "      vertex " << f
           << "      vertex " << e
           << "    endloop\n"
           << "  endfacet\n"

           << "  facet normal" << "0 -1 0\n"
           << "    outer loop\n"
           << "      vertex " << b
           << "      vertex " << e
           << "      vertex " << a
           << "    endloop\n"
           << "  endfacet\n"
           //right side
           << "  facet normal" << "0 1 0\n"
           << "    outer loop\n"
           << "      vertex " << d
           << "      vertex " << h
           << "      vertex " << g
           << "    endloop\n"
           << "  endfacet\n"

           << "  facet normal" << "0 1 0\n"
           << "    outer loop\n"
           << "      vertex " << d
           << "      vertex " << g
           << "      vertex " << c
           << "    endloop\n"
           << "  endfacet\n"
           //front side
           << "  facet normal" << "1 0 0\n"
           << "    outer loop\n"
           << "      vertex " << b
           << "      vertex " << g
           << "      vertex " << f
           << "    endloop\n"
           << "  endfacet\n"

           << "  facet normal" << "1 0 0\n"
           << "    outer loop\n"
           << "      vertex " << c
           << "      vertex " << g
           << "      vertex " << b
           << "    endloop\n"
           << "  endfacet\n"
           //up side
           << "  facet normal" << "0 0 1\n"
           << "    outer loop\n"
           << "      vertex " << f
           << "      vertex " << g
           << "      vertex " << e
           << "    endloop\n"
           << "  endfacet\n"

           << "  facet normal" << "0 0 1\n"
           << "    outer loop\n"
           << "      vertex " << h
           << "      vertex " << e
           << "      vertex " << g
           << "    endloop\n"
           << "  endfacet\n";

        for (double i = 0; i < 2*PI; i += PI*2/c2.fn) {
            Vertex a(c2.r*cos(i),c2.r*sin(i),0);
            Vertex b(c2.r*cos(i+PI*2/c2.fn),c2.r*sin(i+PI*2/c2.fn),0);
            Vertex c(c2.r*cos(i),c2.r*sin(i),c2.h);
            Vertex d(c2.r*cos(i+PI*2/c2.fn),c2.r*sin(i+PI*2/c2.fn),c2.h);
            Vertex o1(0,0,0);
            Vertex o2(0,0,c2.h);

            facetNormal n = getNormal(a,b,c);
            facetNormal up (0,0,-1);
            facetNormal down (0,0,1);

            wr << "  facet normal " << n
              << "    outer loop\n"
              << "      vertex " << a
              << "      vertex " << b
              << "      vertex " << c
              << "    endloop\n"
              << "  endfacet\n"

              << "  facet normal " << n
              << "    outer loop\n"
              << "      vertex " << b
              << "      vertex " << d
              << "      vertex " << c
              << "    endloop\n"
              << "  endfacet\n"

              << "  facet normal " << down
              << "    outer loop\n"
              << "      vertex " << a
              << "      vertex " << o1
              << "      vertex " << b
              << "    endloop\n"
              << "  endfacet\n"

              << "  facet normal " << up
              << "    outer loop\n"
              << "      vertex " << c
              << "      vertex " << d
              << "      vertex " << o2
              << "    endloop\n"
              << "  endfacet\n";
        }
        wr <<"endsolid " << name << "\n";
    }

};



int main() {
    Design d;

    double s = 10;
    Cube c(s);
    double x=10,y=0,z=0;
    c.translate(x,y,z);
    cout << c.volume() << '\n';
    c.write("Cube.stl");        // how to get all my shapes into the same file

    double r = 10, height  = 20;
    Cylinder cyl(r, height);
    cyl.write("Cyl.stl");

    d.add(c);
    d.add(cyl);
    d.write("test.stl");
}