#include "Desk.h"

static int id = 1;
Desk::Desk(float processTime)
{
	this->ID = id++;
	this->processTime = processTime;
	this->validity = true;
}
bool Desk::operator <(const Desk& other) {
	return this->ID < other.ID;
}