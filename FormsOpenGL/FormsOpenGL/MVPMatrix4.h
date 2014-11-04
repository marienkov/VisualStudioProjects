#pragma once
class MVPMatrix4
{
public:
	MVPMatrix4();
	virtual ~MVPMatrix4();

	float* getCurrentModelMatrix4();
	float* getCurrentViewMatrix4();
	float* getCurrentProjectionMatrix4();
	float* getCurrentMVP4();
	
	void makeIdentityMatrix4(float* matrix4);

	void translateModel4(const float(&translation4)[4]);
	void scaleModel4(const float(&scale4)[4]);
	void rotateModel4(const float(&rotate4)[4]);
private:
	bool changed;

	float* model4;
	float* view4;
	float* projection4;
	float* MVP4;
};

