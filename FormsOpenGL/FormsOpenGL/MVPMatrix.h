#pragma once
class MVPMatrix
{
public:
	MVPMatrix();
	virtual ~MVPMatrix();

	float* getCurrentMVP();
	void makeIdentityMatrix();
	void translateMVP(const float(&translation)[4]);
	void scaleMVP(const float(&translation)[4]);
private:
	float MVP[4][4];
};

