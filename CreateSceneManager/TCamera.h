#pragma once
#include "TStd.h"
#include "THero.h"
class TCamera : public THero
{
public:
public:
	T_Math::FMatrix     m_matCamera;
	T_Math::FVector2    m_vCameraPos;
	void Frame()
	{
		m_matCamera.Translation(m_vCameraPos);
	}
	T_Math::FMatrix& GetMatrix()
	{
		return m_matCamera;
	}
	void  SetTransform(T_Math::FVector2   pos)
	{
		m_matCamera.Translation(pos);
	}
	void Up()
	{
		T_Math::FVector2 vCamDirection = { 0.0f, 1.0f };
		m_vCameraPos = m_vCameraPos + vCamDirection * 15.0f * g_fSecondPerFrame;
	}
	void Down()
	{
		T_Math::FVector2 vCamDirection = { 0.0f, -1.0f };
		m_vCameraPos = m_vCameraPos + vCamDirection * 100.0f * g_fSecondPerFrame;
	}
	void Right(float fValue)

	{
		
		T_Math::FVector2 vCamDirection = { -1.0f, 0.0f };
		m_vCameraPos = m_vCameraPos + vCamDirection * 100.0f * g_fSecondPerFrame;
	}
	void Left(float fValue)
	{
		m_vCameraPos.X = m_vCameraPos.X + fValue;
	
	}
};

