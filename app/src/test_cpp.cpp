/*
 * test_cpp.cpp
 *
 *  Created on: May 16, 2018
 *      Author: truongcongtri
 */
/* Constructor */
#include "test_cpp.h"

Shape::Shape()
{
	this->width = 0;
	this->height = 0;
}

/* Destructor */
Shape::~Shape()
{
	//std::cout << "Run Destructor\n";
}

int Shape::getWidth()
{
	return this->width;
}

int Shape::getHeight()
{
	return this->height;
}

void Shape::setWidth(int width)
{
	this->width = width;
}

void Shape::setHeight(int height)
{
	this->height = height;
}



