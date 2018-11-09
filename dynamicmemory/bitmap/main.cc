#include <iostream>
#include "Color.hh"
using namespace std;

class Bitmap{
private:
	uint32_t width,height;
	char *p;
public:
	Bitmap(uint32_t w, uint32_t h) : width(w), height(h), p(new char[width * height]) {
		for (int i = 0; i < width * height; i++)
			p[i] = ' ';
	}

	~Bitmap(){
		delete [] p;
	}
	void plot(int x, int y, Color c){
		p[y*width + x] = c.getColor();
	}

	void line(const int& x0, const int& y0, const int& x1, const int& y1, const Color& c){
		int dx = x1 - x0;
		int dy = y1 - y0;
		double error = 0.0;
		double deltaerr = double(dy) / double(dx);
		int y = y0;
		for (int x = x0; x <= x1; ++x){
			plot(x,y,c);
			error += deltaerr;
			if (abs(error) >= 0.5){
				y += 1;
				error -= 1.0;
			}
		}
	}

	void horizLine(const int& x0, const int& x1, const int& y, const Color& c){
		for(int x = x0; x <= x1; ++x)
			plot(x,y,c);
	}

	void vertLine(const int& x, const int& y0, const int& y1, const Color& c){
		for(int y = y0; y <= y1; ++y)
			plot(x,y,c);
	}

	void drawRect(const int& x, const int& y, const uint& w, const uint& h, const Color& c){
		horizLine(x, x + w, y, c);
		vertLine(x, y, y + h, c);
		horizLine(x, x + w, y + h, c);
		vertLine(x + w, y, y + h, c);
	}

	void fillRect(const int& x0, const int& y0, const uint& w, const uint& h, const Color& c){
		for(int x = x0; x <= x0 + w; ++x){
			for(int y = y0; y <= y0 + h; ++y){
				plot(x,y,c);
			}
		}
	}

	void ellipse(const int& x0, const int& y0, const uint& w, const uint& h, const Color& c) {
		int y1,y2;
		for (int x = x0 - w / 2; x <= x0 + w / 2; ++x) {
			y1 = round(sqrt((1-4.0*(x-x0)*(x-x0)/(w*w))*(h*h/4.0))+y0);
			y2 = y0 - (y1-y0);
			plot(x,y1,c);
			plot(x,y2,c);
		}
	}




	friend ostream& operator <<(ostream& s, const Bitmap& b){
		for(int i=0; i<b.height; i++){
			for(int j=0; j<b.width; j++){
				s <<  b.p[i * b.width + j] << "  ";
			}
			cout<<'\n';
		}
		return s;
	}

};







int main() {
	Bitmap b(30,20); // 30 pixels across, 20 pixels high, each pixel RGBA   // top left pixel = (0,0)
	Color RED(255,0,0); // all red, no green, no blue (fully opaque)
	Color BLUE(0,255,0);
	Color GREEN(0,0,255);
	Color WHITE(255,255,255);
	Color BLACK(0,0,0);

	b.line(0,0,19,19, RED);
	b.line(0,5,29,10, BLUE);
	b.horizLine(0, 20, 19, GREEN); // from x=0 to x=20 at y=19
	b.vertLine(5, 0,19, GREEN); // from y = 0 to y=19 at x = 5
	b.fillRect(10,10, 4, 3,BLACK); // x = 10, y =10 w=4, h=3
	b.drawRect(10,10, 4, 3,WHITE); // x = 10, y =10 w=4, h=3
	b.ellipse(23,5, 8, 5, RED);    // ellipse centered at (23,5) w= 8, h=5
	cout << b;
}