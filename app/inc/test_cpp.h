/*
 * test_cpp.h
 *
 *  Created on: May 16, 2018
 *      Author: truongcongtri
 */

#ifndef TEST_CPP_H_
#define TEST_CPP_H_



class Shape
{
private:
	int width;
	int height;
public:
	/* Constructor */
	Shape();
	/* Destructor */
	~Shape();
	int getWidth();
	int getHeight();
	void setWidth(int width);
	void setHeight(int height);
	virtual int perimeter()
	{
		//std::cout << "Shape class\n";
		return this->height + this->width;
	}
};


#endif /* TEST_CPP_H_ */
