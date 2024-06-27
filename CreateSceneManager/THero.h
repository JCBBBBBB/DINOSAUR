#pragma once
#include "TPawn.h"
class THero : public TPawn
{
public:
	float m_fSpeed = 100.0f;
	virtual void  Frame() override;
	virtual void  Front();
	virtual void  Back();
	virtual void  Left();
	virtual void  Right();
	void	SetVertexData(RECT rt) override;
	THero();
};
