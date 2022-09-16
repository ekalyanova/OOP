#include "BlurApp.h"

#include <opencv2/core/mat.hpp>
#include <opencv2/imgcodecs.hpp>
#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

namespace
{
template <typename T>
T clamp(T val, T min, T max)
{
	if (val > max) return max;
	if (val < min) return min;

	return val;
}
}

BlurApp::BlurApp(const std::string& appName)
	: m_appName(appName)
	, m_blurRadius(40)
	, m_blurStrength(15)
	, m_posX(0)
	, m_posY(0)
{	
	cv::namedWindow(m_appName, cv::WINDOW_AUTOSIZE);
	cv::setMouseCallback(m_appName, OnMouseHandle, this);

	cv::createTrackbar("Radius: ", m_appName, &m_blurRadius, 1000, OnBlurParamsChanged);
	cv::createTrackbar("Strength: ", m_appName, &m_blurStrength, 1000, OnBlurParamsChanged);
}

BlurApp::~BlurApp()
{
	cv::destroyWindow(m_appName);
}

void BlurApp::Open(const std::string& path)
{
	m_image = cv::imread(path, cv::IMREAD_COLOR); // Read the file
	if (m_image.empty()) // Check for invalid input
	{
		std::cout << "Could not open or find the image" << std::endl;
		return;
	}

	m_blurred = m_image.clone();
	cv::imshow(m_appName, m_blurred);
	cv::waitKey(0);
}

void BlurApp::Update()
{	
	if(m_blurRadius == 0 || m_blurRadius > m_blurred.cols || m_blurRadius > m_blurred.rows)
	{
		cv::imshow(m_appName, m_image);
		return;
	}

	m_blurStrength = m_blurStrength % 2 == 1 ? m_blurStrength : m_blurStrength + 1;
	
	auto x = m_posX - m_blurRadius / 2;
	auto y = m_posY - m_blurRadius / 2;

	int radX = x < 0 ? m_blurRadius + x : m_blurRadius;
	int radY = y < 0 ? m_blurRadius + y : m_blurRadius;
	
	x = clamp(x, 0, m_blurred.cols);
	y = clamp(y, 0, m_blurred.rows);

	if (x + radX > m_blurred.cols)
		radX = -x + m_blurred.cols;

	if (y + radY > m_blurred.rows)
		radY = -y + m_blurred.rows;
	
	std::cout << x << " " << radX << " " << y << " "<< radY << std::endl;	

	m_blurred.release();
	m_blurred = m_image.clone();
	
	const cv::Rect roi(x, y, radX, radY);
	cv::GaussianBlur(m_blurred(roi), m_blurred(roi), cv::Size(m_blurStrength, m_blurStrength), -1,-1);

	cv::imshow(m_appName, m_blurred);
}

void BlurApp::OnMouseHandle(int event, int x, int y, int, void* instance)
{
	if (instance == nullptr) return;
	reinterpret_cast<BlurApp*>(instance)->OnMouseHandleInner( x, y);
}

void BlurApp::OnMouseHandleInner(int x, int y)
{
	m_posX = x;
	m_posY = y;

	Update();
}

void BlurApp::OnBlurParamsChanged(int x, void* instance)
{
	if (instance == nullptr) return;
	reinterpret_cast<BlurApp*>(instance)->Update();
}
