#ifndef _TRACKER_H_
#define _TRACKER_H_

#include <vector>
#include <opencv/cv.h>

//#include "Recognition.h"

using namespace cv;
using namespace std;

struct RefKeypoints
{
	cv::KeyPoint kp;
	bool bActive;
	int index;//在所有的点里面的序号

	RefKeypoints()
	{
		index = -1;
		bActive = false;
	}

};

struct SceKeypoints
{
	cv::KeyPoint kp;
	bool bActive;
	int repositoryRef;//对应到模板特征点的序号

	SceKeypoints()
	{
		repositoryRef = -1;
		bActive = false;
	}

};

struct MatchedPoints
{
	float xImg;
	float yImg;

	float xRef;
	float yRef;
	
	int ID;
	bool bUsed;
	int index;

	MatchedPoints()
	{
		index = -1;
		ID = -1;
		bUsed = false;
	}

};

struct  OpticalFlow
{
private:
	const static int MAX_POINT_COUNT = 200;

	int imageWidth;							
	int imageHeight;						
	CvSize windowSize;						
	int pyramidLevel;						
	
	CvPoint2D32f feature1[MAX_POINT_COUNT];	
	CvPoint2D32f feature2[MAX_POINT_COUNT];	
	char foundFeature[MAX_POINT_COUNT];		
	float errorFeature[MAX_POINT_COUNT];

	CvTermCriteria terminationCriteria;		
	int eMax;								
	IplImage* pyramid1;
	IplImage* pyramid2;

	int winsize_ncc;
	IplImage *rec0;
    IplImage *rec1;
    IplImage *res;

	
public:
	~OpticalFlow()
	{
		this->Release();
	}

	
	inline void SetImageSize(int width, int height){this->imageWidth=width;this->imageHeight=height;};
	inline CvSize GetImageSize(){return cvSize(this->imageWidth, this->imageHeight);};
	inline void SetWindowSize(CvSize size=cvSize(8, 8)){this->windowSize = size;};
	inline void SetPyramidLevel(int level=3){this->pyramidLevel = level;};
	

	void Initialize(
					int width,							
					int height,							
					CvSize windowSize=cvSize(8, 8),		
					int pyramidLevel=3					
					);



	int TrackFeatures(
					IplImage* prevGrayImage,					
					IplImage* currGrayImage,					
					std::vector<MatchedPoints>* prevPoints,		
					std::vector<MatchedPoints>* currentPoints,
					int id
					);
	void normCrossCorrelation(IplImage *imgI, IplImage *imgJ,
                           CvPoint2D32f *points0,  CvPoint2D32f *points1, int nPts, char *status,
                          float *match, int winsize, int method);

	void Release();
};


#endif 