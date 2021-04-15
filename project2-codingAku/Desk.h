#ifndef Desk_H
#define Desk_H


class Desk
{
public:
	int ID;
	float processTime;
	bool validity;
	Desk(float processTime);
	bool operator <(const Desk& other);
};
#endif 

