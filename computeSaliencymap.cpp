//this Saliencymap is impletement by "Saliency detection: A spectral residual approach".
//the lib. include opencv3.3.0

#include "opencv2/core/utility.hpp"
#include "opencv2/core.hpp"
#include <opencv2/core/persistence.hpp>
#include "opencv2/imgproc.hpp"
#include <opencv2\highgui\highgui.hpp>
using namespace cv;
bool computeSaliencymap(InputArray image, OutputArray saliencymap)
{
	//resize image from big to small
	//deal with gray image
	Mat grayTemp, grayDown;
	std::vector<Mat> mv;
	//deal with real size of image
	int resImWidth = 64;
	int resImHeight = 64;
	//intial image size
	Size resizedImageSize(resImWidth, resImHeight);

	Mat realImage(resizedImageSize, CV_64F);
	Mat imagetempImage(resizedImageSize, CV_64F);
	imagetempImage.setTo(0);

	Mat stitchImage(resizedImageSize, CV_64FC2);

	//Discrete Fourier Transform
	Mat imageDFT;

	//log(Amplitude)
	Mat logAmplitude;
	Mat angle(resizedImageSize, CV_64F);
	Mat magnitude(resizedImageSize, CV_64F);
	Mat logAmplitude_blur, imageGray;

	if (image.channels() == 3)
	{
		cvtColor(image, imageGray, COLOR_BGR2GRAY);
		resize(imageGray, grayDown, resizedImageSize, 0, 0, INTER_LINEAR);

	}
	else
	{
		resize(image, grayDown, resizedImageSize, 0, 0, INTER_LINEAR);
	}
	grayDown.convertTo(realImage, CV_64F);

	mv.push_back(realImage);
	mv.push_back(imagetempImage);

	merge(mv, stitchImage);
	dft(stitchImage, imageDFT);

	split(imageDFT, mv);

	//Get magnitude and phase of frequency spectrum 
	cartToPolar(mv.at(0), mv.at(1), magnitude, angle, false);
	log(magnitude, logAmplitude);
	//blur logAmplitude to get averaging filter
	blur(logAmplitude, logAmplitude_blur,Size(3,3),Point(-1,-1), BORDER_DEFAULT);

	exp(logAmplitude - logAmplitude_blur, magnitude);

	// Back to cartesian frequency domain
	polarToCart(magnitude, angle, mv.at(0), mv.at(1),false);
	merge(mv, imageDFT);
	dft(imageDFT, stitchImage, DFT_INVERSE);
	split(stitchImage, mv);

	cartToPolar(mv.at(0), mv.at(1), magnitude, angle, false);
	GaussianBlur(magnitude, magnitude, Size(5, 5), 8, 0, BORDER_DEFAULT);
	magnitude = magnitude.mul(magnitude);
	//normalizition
	double minVal, maxVal;
	minMaxLoc(magnitude, &minVal, &maxVal);
	magnitude = magnitude / maxVal;
	magnitude.convertTo(magnitude, CV_32F);

	resize(magnitude, saliencymap, image.size(), 0, 0, INTER_LINEAR);
	
	return true;



}

int main(void)
{
	Mat image;
	Mat saliencyMap;
	image = cv::imread("D:\\flower.jpg");
	computeSaliencymap(image, saliencyMap);
	imshow("test", saliencyMap);
	waitKey(0);
	return 0;
}