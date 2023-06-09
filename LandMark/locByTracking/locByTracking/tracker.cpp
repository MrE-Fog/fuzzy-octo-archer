#include "tracker.h"

//对每个跟踪到的特征点，当前帧和前一帧进行模板匹配
void OpticalFlow::normCrossCorrelation(IplImage *imgI, IplImage *imgJ,
                           CvPoint2D32f *points0,  CvPoint2D32f *points1, int nPts, char *status,
                          float *match, int winsize, int method)
{
    
    for(int i = 0; i < nPts; i++)
    {
		if(status[i])
        {
            cvGetRectSubPix(imgI, rec0, points0[i]);
            cvGetRectSubPix(imgJ, rec1, points1[i]);
            cvMatchTemplate(rec0, rec1, res, method);
            match[i] = ((float *)(res->imageData))[0];
			
        }
        else
        {
            match[i] = 0.0;
			
        }
    }

}

void OpticalFlow::Release()
{
	if(pyramid1) cvReleaseImage(&pyramid1);
	pyramid1 = NULL;
	if(pyramid2) cvReleaseImage(&pyramid2);
	pyramid2 = NULL;

	if(rec0)
		cvReleaseImage(&rec0);
    if(rec1)
		cvReleaseImage(&rec1);
    if(res)
		cvReleaseImage(&res);
}

void OpticalFlow::Initialize(int width, int height, CvSize windowSize, int pyramidLevel)
{
	
	this->SetImageSize(width, height);
	this->SetWindowSize(windowSize);
	this->SetPyramidLevel(pyramidLevel);

	terminationCriteria = cvTermCriteria(CV_TERMCRIT_ITER | CV_TERMCRIT_EPS, 20, .3);

	
	pyramid1 = cvCreateImage(this->GetImageSize(), IPL_DEPTH_8U, 1);
	pyramid2 = cvCreateImage(this->GetImageSize(), IPL_DEPTH_8U, 1);

	winsize_ncc = 10;
	rec0 = cvCreateImage(cvSize(winsize_ncc, winsize_ncc), 8, 1);
    rec1 = cvCreateImage(cvSize(winsize_ncc, winsize_ncc), 8, 1);
    res = cvCreateImage(cvSize(1, 1), IPL_DEPTH_32F, 1);
}



int OpticalFlow::TrackFeatures(IplImage* prevGrayImage, IplImage* currGrayImage, std::vector<MatchedPoints>* prevPoints, std::vector<MatchedPoints>* currentPoints, int id)
{
	int pointCount = MIN((int)prevPoints->size(), this->MAX_POINT_COUNT);
	//float ncc[MAX_POINT_COUNT];

	if(pointCount >= 1)
	{
		
		for(int i=0; i<pointCount; i++)
		{
			if((*prevPoints)[i].ID == id)
				this->feature1[i] = cvPoint2D32f((*prevPoints)[i].xImg, (*prevPoints)[i].yImg);
		}
		cvCalcOpticalFlowPyrLK(prevGrayImage, currGrayImage, pyramid1, pyramid2, feature1, feature2, pointCount, this->windowSize, this->pyramidLevel, foundFeature, errorFeature, terminationCriteria, 0);

		
		/*normCrossCorrelation(prevGrayImage, currGrayImage, feature1, feature2, pointCount, foundFeature, ncc,
                         this->winsize_ncc, CV_TM_CCOEFF_NORMED);*/

	
		//int index = 0;
		for(int i=0; i<pointCount; i++)
		{
			if(foundFeature[i]/* && ncc[i] >= 0.7*/)//当前帧跟前一帧的特征点相似度大于0.7，才算跟踪准确
			{
				MatchedPoints point = (*prevPoints)[i];
				point.xImg = feature2[i].x;
				point.yImg = feature2[i].y;
				currentPoints->push_back(point);
				//index++;
			}
			else
			{
				(*prevPoints)[i].bUsed = false;//移除匹配
				currentPoints->push_back((*prevPoints)[i]);
			}
		}
		return 1;
	}
	else
	{
		return 0;
	}
}

