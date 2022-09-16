//------------------------------------------------------------------------------
// Blur.h
//
// Blur implements...
//
// Copyright (c) 2019 GlenSand
// All rights reserved.
//
// Date: 17.01.2020
// Author: Bezborodov Gleb
//------------------------------------------------------------------------------
#pragma once
#include <string>
#include <opencv2/core/mat.hpp>

class BlurApp final
{
public:
	
	BlurApp(const std::string &appName);
	~BlurApp();

	void			Open(const std::string& path);

private:
	void			Update();
	
	static void		OnMouseHandle(int event, int x, int y, int, void* instance);
	void			OnMouseHandleInner(int x, int y);

	static void		OnBlurParamsChanged(int x, void* instance);
	
	std::string		m_appName;

	int				m_blurRadius;
	int				m_blurStrength;

	int				m_posX;
	int				m_posY;

	cv::Mat			m_image;
	cv::Mat			m_blurred;
};
