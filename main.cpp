#include "SImageData.h"
#include "IVSStippling.h"
#include "epswriter.hpp"


void main()
{
	SImageData imageData;
	
	char fileName[] = "D:/timg2.bmp";
	ImageLoad(fileName, imageData);
	ImageSave(imageData, "test.bmp");
//=================普通的调用==============================================
	/*
	typedef std::vector<glm::vec3> SResult;
	SResult result;
	ivsStippling(imageData, result, 0.4);
	epswriter c("circle.eps", 0, 0,  2*imageData.m_width,  2*imageData.m_height);
	cout << result.size() << endl;

	for (size_t i = 0; i <  result.size(); i++)
	{
		glm::vec3 stipple;
		stipple = result[i];
		c.filledCircle(int(stipple.x*imageData.m_width*2 ), int(stipple.y*imageData.m_height *2), stipple.z, -1,-1,-1);
	}
	*/
//=================================================================

//=========串行不同灰阶============================================================
/*	//============================================
	
	vector<glm::vec4> vRej;
	vector<float> rVals;
	rVals.clear();
	rVals.push_back(1.0);
	rVals.push_back(0.7);
	rVals.push_back(0.4);
	rVals.push_back(0.1);
	rVals.push_back(0.0);
	
	vRej.resize(10000);
	float s_0 = imageData.m_height*imageData.m_width;
	float s_d = IVS_M_PI * 4 * 4;
	MLISMultiAtRejRange(imageData, vRej, 30000, rVals,
		imageData.m_width, imageData.m_height, s_d, s_0, 0, 1000);
	
	//ivsStipplingVaryingRaidus(imageData, result,0.6);
	epswriter c("circle.eps", 0, 0, 4*imageData.m_width,4*imageData.m_height);
	cout << vRej.size()<< endl;

	for (size_t i = 0; i < vRej.size(); i++)
	{
		glm::vec4 stipple;
		stipple = vRej[i];
		c.filledCircle(int(stipple.x*imageData.m_width*4), int(stipple.y*imageData.m_height*4), stipple.z, (stipple.a*65535.0), (stipple.a*65535.0), (stipple.a*65535.0));
	}
	*/
	//const char * file_size_type_Name = "test";
	//DitherIVNoiseSimple(imageData, file_size_type_Name, imageData);
//======================================================================

//======================并行不同灰阶===============================================
	/*
	vector<float> grayImageR;


	int height = imageData.m_height;
	int width = imageData.m_width;

	for (size_t y = 0; y < imageData.m_height; ++y)
	{
		SColor* pixel = (SColor*)&imageData.m_pixels[y * imageData.m_pitch];
		for (size_t x = 0; x < imageData.m_width; ++x)
		{
			grayImageR.push_back((double)pixel->R / 255.0);
			
			++pixel;
		}
	}
	 
	vector<glm::vec4> vRej;
	
	vector<float> rVals;
	rVals.clear();
	//rVals.push_back(1.0);
	float colorbar = 10;
	/*
	for (int i = 0; i <= colorbar; i++)
	{
		rVals.push_back(float(i/colorbar));
	}*/
	/*
	rVals.push_back(0.);
	rVals.push_back(0.1);
	rVals.push_back(0.2);
	rVals.push_back(0.3);
	rVals.push_back(0.4);
	rVals.push_back(0.5);
	rVals.push_back(0.6);
	rVals.push_back(0.7);
	rVals.push_back(0.8);
	rVals.push_back(0.9);
	rVals.push_back(1.0);
	//rVals.push_back(0.99);
	//rVals.push_back(1.0);
	//rVals.push_back(0.0);
	
	float s_0 = imageData.m_height*imageData.m_width*4*4; //imageData.m_height*imageData.m_width;
	float s_d = IVS_M_PI*0.6*0.6; //IVS_M_PI * 1 * 1;
	//int n_max = 40960;
	int n = imageData.m_height*imageData.m_width*4*4;
	vRej.resize(n);
	
	MLISMultiThread(grayImageR, vRej, rVals,
		width, height, s_d, s_0, 6);

	
	
	

	epswriter c("circle.eps", 0, 0,  imageData.m_width,  imageData.m_height);
	
	//cout << vRej[100].z << endl;
	for (size_t i = 0; i < vRej.size(); i++)
	{
		glm::vec4 stipple;
		stipple = vRej[i];
		c.filledCircle(int(stipple.x*imageData.m_width ), int(stipple.y*imageData.m_height ), stipple.z, (vRej[i].a) * 65535, (vRej[i].a) * 65535, (vRej[i].a) * 65535);
		/*
		if(i%3==0)
			c.filledCircle(int(stipple.x*imageData.m_width * 4), int(stipple.y*imageData.m_height * 4), stipple.z, (0.2* 65535), (0.2 * 65535), (0.2 * 65535));
		else if(i%3==1)
			c.filledCircle(int(stipple.x*imageData.m_width * 4), int(stipple.y*imageData.m_height * 4), stipple.z, (0.5 * 65535), (0.5 * 65535), (0.5 * 65535));
		else
			c.filledCircle(int(stipple.x*imageData.m_width * 4), int(stipple.y*imageData.m_height * 4), stipple.z, (0.9 * 65535), (0.9 * 65535), (0.9 * 65535));
		*
	}
	*/
//===============================================================================


//==================彩色调用(RGB 0-1 and 0 min-max 1)=========================================================
	vector<float> grayImageR;
	vector<float> grayImageG;
	vector<float> grayImageB;

	int height = imageData.m_height;
	int width = imageData.m_width;

	for (size_t y = 0; y < imageData.m_height; ++y)
	{
		SColor* pixel = (SColor*)&imageData.m_pixels[y * imageData.m_pitch];
		for (size_t x = 0; x < imageData.m_width; ++x)
		{
			grayImageR.push_back((double)pixel->R / 255.0);
			grayImageG.push_back((double)pixel->G / 255.0);
			grayImageB.push_back((double)pixel->B / 255.0);
			++pixel;
		}
	}
	auto maxR = std::max_element(grayImageR.begin(), grayImageR.end());
	auto minR = std::min_element(grayImageR.begin(), grayImageR.end());
	float maxr = *maxR;
	float minr = *minR;

	auto maxG = std::max_element(grayImageG.begin(), grayImageG.end());
	auto minG = std::min_element(grayImageG.begin(), grayImageG.end());
	float maxg = *maxG;
	float ming = *minG;

	auto maxB = std::max_element(grayImageB.begin(), grayImageB.end());
	auto minB = std::min_element(grayImageB.begin(), grayImageB.end());
	float maxb = *maxB;
	float minb = *minB;

	vector<glm::vec4> vRejR;
	vector<glm::vec4> vRejG;
	vector<glm::vec4> vRejB;

	//三个调色板
	vector<float> rVals,gVals,bVals;
	rVals.clear();
	gVals.clear();
	bVals.clear();
	//rVals.push_back(1.0);
	float colorbar = 5;
	rVals.push_back(0.0);
	gVals.push_back(0.0);
	bVals.push_back(0.0);

	for (int i = 0; i <= colorbar; i++)
	{
		rVals.push_back(minr + float(i * (maxr-minr)/ colorbar));
		gVals.push_back(ming + float(i * (maxg - ming) / colorbar));
		bVals.push_back(minb + float(i * (maxb - minb) / colorbar));
	}
	rVals.push_back(1.0);
	gVals.push_back(1.0);
	bVals.push_back(1.0);
	/*
	rVals.push_back(0.);
	rVals.push_back(0.1);
	rVals.push_back(0.2);
	rVals.push_back(0.3);
	rVals.push_back(0.4);
	rVals.push_back(0.5);
	rVals.push_back(0.6);
	rVals.push_back(0.7);
	rVals.push_back(0.8);
	rVals.push_back(0.9);
	rVals.push_back(1.0);
	//rVals.push_back(0.99);
	//rVals.push_back(1.0);
	//rVals.push_back(0.0);
	*/
	float s_0 = imageData.m_height*imageData.m_width * 4 * 4; //imageData.m_height*imageData.m_width;
	float s_d = IVS_M_PI*0.6*0.6; //IVS_M_PI * 1 * 1;
								  //int n_max = 40960;
	int n = imageData.m_height*imageData.m_width * 4 * 4;
	vRejR.resize(n);
	vRejG.resize(n);
	vRejB.resize(n);

	MLISMultiThread(grayImageR, vRejR, rVals,
		width, height, s_d, s_0, 6);

	MLISMultiThread(grayImageG, vRejG, gVals,
		width, height, s_d, s_0, 6);

	MLISMultiThread(grayImageB, vRejB, bVals,
		width, height, s_d, s_0, 6);


	epswriter c("circle.eps", 0, 0, imageData.m_width, imageData.m_height);

	//cout << vRej[100].z << endl;
	for (size_t i = 0; i < vRejR.size(); i++)
	{
		glm::vec4 stipple;
		stipple = vRejR[i];
		c.filledCircle(int(stipple.x*imageData.m_width), int(stipple.y*imageData.m_height), stipple.z, (vRejR[i].a) * 65535, (vRejG[i].a) * 65535, (vRejB[i].a) * 65535);
		/*
		if(i%3==0)
		c.filledCircle(int(stipple.x*imageData.m_width * 4), int(stipple.y*imageData.m_height * 4), stipple.z, (0.2* 65535), (0.2 * 65535), (0.2 * 65535));
		else if(i%3==1)
		c.filledCircle(int(stipple.x*imageData.m_width * 4), int(stipple.y*imageData.m_height * 4), stipple.z, (0.5 * 65535), (0.5 * 65535), (0.5 * 65535));
		else
		c.filledCircle(int(stipple.x*imageData.m_width * 4), int(stipple.y*imageData.m_height * 4), stipple.z, (0.9 * 65535), (0.9 * 65535), (0.9 * 65535));
		*/
	}


//===================================================================================

}