#ifndef _FRAME_H_
#define _FRAME_H_

class Cell;

class Frame
{
public:
	Frame(int w, int h);
	virtual ~Frame();
protected:
	int width;
	int height;
};

#endif
