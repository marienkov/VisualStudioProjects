#pragma once
#include <string>
class Visitor;

class View
{
protected:
	std::string id;
	int col;
public:
	View();
	View(std::string, int);
	void setId(std::string);
	void setColor(int);
	virtual void accept(Visitor&);
	virtual ~View();

	struct VertexCoord {
	public:
		VertexCoord();
		VertexCoord(int, int, int);
		~VertexCoord();
		int x, y, z;
	};
};