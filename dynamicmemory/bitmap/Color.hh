#pragma once

class Color{
private:
	uint32_t rgba;
public:
	Color(uint8_t r, uint8_t g, uint8_t b, uint8_t alpha = 1) {
		rgba = ((r & 0xff) << 24) + ((g & 0xff) << 16) + ((b & 0xff) << 8) + (alpha & 0xff);
	}

	char getColor()  {
		if (rgba == 0xff000001)
			return 'R';
		else if (rgba == 0xff0001)
			return 'B';
		else if (rgba == 0xff01)
			return 'G';
		else if (rgba == 0xffffff01)
			return 'W';
		else if (rgba == 0xffff0001)
			return 'Y';
		else if (rgba == 0x1)
			return 'K';
		else
			return  'X';
	}
};