#include "opencv2/opencv.hpp"
#include <iostream>
#include <ctype.h>
#include "tracker.h"


#define USE_ADAPTIVE_THRESHOLD 1// 采取动态的阈值检测
#define USE_LSH_MATCH 1// 

const int FEATURE_COUNT_THRESHOLD = 200;//动态检测的阈值
const int FEATURE_VALID_COUNT = 200;//规定每帧至多只检测的特征点个数

using namespace cv;
using namespace std;

#if defined _DEBUG
#pragma comment(lib,"opencv_core231d.lib")
#pragma comment(lib,"opencv_imgproc231d.lib")
#pragma comment(lib,"opencv_highgui231d.lib")
#pragma comment(lib,"opencv_features2d231d.lib")
#pragma comment(lib,"opencv_calib3d231.lib")
#pragma comment(lib,"opencv_video231d.lib")
#pragma comment(lib,"opencv_objdetect231d.lib")
#else
#pragma comment(lib,"opencv_core249.lib")
#pragma comment(lib,"opencv_imgproc249.lib")
#pragma comment(lib,"opencv_highgui249.lib")
#pragma comment(lib,"opencv_features2d249.lib")
#pragma comment(lib,"opencv_calib3d249.lib")
#pragma comment(lib,"opencv_video249.lib")
#pragma comment(lib,"opencv_objdetect249.lib")
#pragma comment(lib,"opencv_flann249.lib")



#endif

const int WIDTH = 640;
const int HEIGHT = (WIDTH * 3) / 4;

#define MAX_INDEX_NUM 1000

extern int randomIndex[1000] = {

	41,467,334,500,169,724,478,358,962,464,705,145,281,827,961,491,995,942,436,391,604,902,153,292,382,421,716,718,895,447,726,771,538,869,912,667,299,35,894,703,811,322,333,673,664,141,711,253,868,547,644,662,757,37,859,723,741,529,778,316,190,842,288,106,40,264,648,446,805,890,729,370,350,6,101,393,548,629,623,84,954,756,840,966,376,931,308,944,439,626,323,537,118,82,929,541,833,115,639,658,
	704,930,977,306,386,21,745,924,72,270,829,777,573,97,512,986,290,161,636,355,767,655,574,31,52,150,941,430,107,191,7,337,457,287,753,383,945,909,209,758,221,588,422,946,506,30,413,168,900,591,762,410,359,624,483,595,602,291,836,374,20,596,348,199,668,484,734,53,999,418,938,788,127,728,893,807,310,617,813,514,309,616,935,451,600,249,519,556,798,303,224,8,844,609,989,702,195,485,93,343,
	523,587,314,503,448,200,458,618,580,796,589,9,157,472,622,38,179,657,958,815,888,156,511,202,634,272,55,328,646,362,886,875,433,142,416,881,998,651,699,557,476,892,389,75,712,510,3,861,688,401,789,255,423,2,585,182,285,88,426,832,932,154,721,189,976,329,368,692,425,555,434,549,441,60,139,279,996,687,437,866,949,193,297,286,105,488,282,455,114,701,671,786,263,313,185,808,321,558,982,481,
	144,196,222,129,535,450,173,466,44,659,24,649,186,474,22,18,787,905,625,477,414,824,874,372,159,70,487,518,177,773,763,192,985,102,480,213,627,802,99,527,543,23,972,61,181,432,505,593,725,492,64,187,360,974,170,235,760,896,550,140,694,695,19,125,576,302,371,678,851,119,152,800,87,926,10,315,227,43,164,109,882,86,565,577,928,520,123,737,261,525,260,116,326,11,411,790,188,940,713,578,
	365,58,357,324,108,113,887,801,850,460,428,993,384,405,540,111,835,356,823,216,526,271,361,112,717,696,229,559,296,855,584,654,369,532,963,607,911,635,67,848,675,223,754,175,459,825,870,934,205,783,398,637,534,176,300,641,462,611,877,424,752,443,818,610,17,831,685,90,497,990,353,740,258,335,759,605,775,608,997,561,240,174,601,77,215,683,992,392,670,27,498,970,847,663,706,363,171,489,542,619,
	913,232,750,975,539,98,247,971,864,545,546,769,262,289,865,245,508,318,132,570,901,103,969,15,28,347,943,409,463,49,681,342,146,690,843,620,748,536,226,853,923,257,766,955,25,1,496,515,964,948,606,429,404,812,375,36,736,814,994,256,652,936,838,482,131,230,841,650,452,233,454,148,124,317,80,858,50,155,903,676,643,653,674,220,402,878,259,781,504,698,722,461,234,959,493,269,937,700,117,330,
	39,212,85,710,774,380,951,679,110,898,73,956,689,184,71,885,867,295,598,693,686,528,826,816,516,666,340,415,873,531,806,268,907,307,12,136,630,809,293,54,345,708,248,479,238,918,486,633,158,925,647,830,278,799,352,575,567,336,397,897,828,449,560,147,162,792,714,569,638,521,475,615,524,469,910,135,4,568,373,194,876,396,572,640,819,419,166,74,509,172,968,779,552,495,764,364,821,122,594,950,
	672,967,408,908,204,319,367,283,331,583,776,856,490,677,68,991,727,871,697,612,237,501,128,149,465,267,793,442,770,381,590,327,42,860,742,614,661,63,435,586,48,735,810,599,837,244,794,252,208,243,100,891,854,919,780,544,899,834,785,791,210,979,277,276,582,761,56,163,862,904,680,198,32,387,517,241,621,95,916,178,579,81,784,973,922,91,857,236,551,183,394,180,65,513,78,947,445,214,522,231,
	351,431,197,747,473,274,981,320,165,206,984,978,684,906,390,420,444,507,311,406,768,0,388,987,217,665,104,872,656,251,79,933,720,440,562,797,76,880,400,707,225,33,29,83,470,5,47,965,669,134,597,218,563,301,151,738,822,338,339,733,130,846,920,795,719,239,468,581,399,349,502,346,126,566,203,51,456,803,915,133,642,385,69,730,731,883,273,917,749,631,407,782,765,250,138,530,746,34,137,211,
	879,953,427,743,889,26,89,66,412,395,755,265,45,927,839,645,939,16,284,715,957,254,366,438,632,554,988,533,804,13,266,275,494,471,739,160,553,379,914,453,592,377,744,849,294,94,817,613,628,120,312,332,603,403,143,325,280,571,751,201,219,14,62,709,304,499,682,983,732,820,344,980,845,246,59,46,852,167,354,207,884,242,298,96,121,564,960,417,305,57,92,378,952,691,228,341,863,921,660, 772 
};



OpticalFlow* opticalflow;

std::vector <std::vector<MatchedPoints> >refMatchedKeypoints;	///< 模板图像中参与匹配的特征点
std::vector <std::vector<MatchedPoints> >sceMatchedKeypoints;	///< 场景图像 中参与匹配的特征点
std::vector <std::vector<RefKeypoints> >referenceRepository;//模板的检测到的特诊点



bool niceHomography(const Mat imgMat)
{
  CvMat H1 = imgMat;
  CvMat* H = &H1;
  const double det = cvmGet(H, 0, 0) * cvmGet(H, 1, 1) - cvmGet(H, 1, 0) * cvmGet(H, 0, 1);
  if (det < 0)
    return false;

  const double N1 = sqrt(cvmGet(H, 0, 0) * cvmGet(H, 0, 0) + cvmGet(H, 1, 0) * cvmGet(H, 1, 0));
  if (N1 > 4 || N1 < 0.1)
    return false;

  const double N2 = sqrt(cvmGet(H, 0, 1) * cvmGet(H, 0, 1) + cvmGet(H, 1, 1) * cvmGet(H, 1, 1));
  if (N2 > 4 || N2 < 0.1)
    return false;

  const double N3 = sqrt(cvmGet(H, 2, 0) * cvmGet(H, 2, 0) + cvmGet(H, 2, 1) * cvmGet(H, 2, 1));
  if (N3 > 0.002)
    return false;

  return true;
}



void tracking(int id, IplImage *prevImage, IplImage* frame)
{

	int ind1 = 0;
	int index1 = 0;
	
	
	std::vector<MatchedPoints> sceneKeypoints;
	opticalflow->TrackFeatures(prevImage, frame, &sceMatchedKeypoints[id], &sceneKeypoints, id);			
		
	for( ind1 = 0; ind1 < sceneKeypoints.size(); ind1++)
	{
		if(sceneKeypoints[ind1].bUsed && sceneKeypoints[ind1].ID == id )//表示跟踪成功
		{
			sceMatchedKeypoints[id][index1] = sceneKeypoints[ind1];//跟踪成功则加到 场景图像 中能参与匹配的特征点里去
			index1++;
		}
		else // tracking fail feature
		{
			referenceRepository[id][refMatchedKeypoints[id][index1].index].bActive = false; //跟踪失败，将模板图像里参与了匹配的特征点变为不参与匹配，即class_id = 0
			sceMatchedKeypoints[id].erase(sceMatchedKeypoints[id].begin() + index1);//删除场景里对应的之前参与了匹配的特征点
			refMatchedKeypoints[id].erase(refMatchedKeypoints[id].begin() + index1);//删除模板里对应的之前参与了匹配的特征点
		}
	}

}



int main( int argc, char** argv )
{

	CvScalar colors[] = {CV_RGB(255, 0, 255), CV_RGB(0, 0, 255),CV_RGB(0, 255, 255),   CV_RGB(255, 0, 0), CV_RGB(255, 255, 255)};

	if(argc < 2)
	{
		std::cout<<"please input images" << std::endl;
		return -1;
	}

	int numImages = argc - 1;
	std::vector<cv::Mat> refImage;
	std::vector<cv::Mat> refGrayImages;
	
	for(int i = 0; i < numImages; i++)
	{
		Mat ref = cv::imread(argv[i+1], 1);
		if (ref.empty())
		{
			std::cout<<"image not found." << std::endl;
			return -1;
		}
		Mat refGray;
		cv::cvtColor(ref, refGray, CV_BGR2GRAY);
		GaussianBlur(refGray, refGray, cv::Size(3, 3), 0);
		refGrayImages.push_back(refGray);
		refImage.push_back(ref);
		
	}



	for (int ind = 0; ind < numImages; ind++ )
	{
		std::vector<MatchedPoints> sceMatchedPtsTmp;
		std::vector<MatchedPoints> refMatchedPtsTmp;
		sceMatchedKeypoints.push_back(sceMatchedPtsTmp);
		refMatchedKeypoints.push_back(refMatchedPtsTmp);
	}
	
	
	std::vector<cv::Mat> refImagesDescriptors;//模板的描述
	cv::Ptr<cv::FeatureDetector> detector;
	int threshold = 30;

	
	cv::Ptr<cv::DescriptorExtractor> descriptorExtractor;//BRISK的描述算子
	descriptorExtractor = new FREAK(true, true, 22, 4, std::vector<int>());

	if (descriptorExtractor.empty())
	{
		std::cout<< " not descriptorExtractor. Check spelling!" << std::endl;
		return -1;
	}
	
	detector = new cv::FastAdjuster();//FAST检测子
	if (detector.empty())
	{
		std::cout << " not detector recognized. Check spelling!" << std::endl;
		return 0;
	}



	vector < vector<cv::KeyPoint> >rfkps;
		
	detector->detect(refGrayImages, rfkps);
	descriptorExtractor->compute(refGrayImages, rfkps, refImagesDescriptors);//提取模板的描述
	for(int i = 0; i < numImages; i++)
	{
		std::vector<RefKeypoints> temp;
		referenceRepository.push_back(temp);
		for(int j = 0; j < rfkps[i].size(); j++)
		{
			RefKeypoints RK;
			RK.bActive = false;
			RK.kp.pt.x = rfkps[i][j].pt.x;
			RK.kp.pt.y = rfkps[i][j].pt.y;
			RK.kp.angle = rfkps[i][j].angle;
			RK.kp.size = rfkps[i][j].size;
			RK.kp.octave = rfkps[i][j].octave;
			RK.kp.response = rfkps[i][j].response;
			RK.kp.class_id = i;
			RK.index = j;
			referenceRepository[i].push_back(RK);
		}
	}


	//drawKeypoints();
	std::vector<cv::DMatch> matches;
	std::vector <std::vector<cv::DMatch>> LSHmatches;
	
	cv::Ptr<cv::FlannBasedMatcher> matcher;
	cv::Ptr<cv::flann::IndexParams> indexParams = new cv::flann::LshIndexParams(1, 20, 2);
	matcher = new cv::FlannBasedMatcher(indexParams);
	matcher->add(refImagesDescriptors);
	matcher->train();
	
	VideoCapture cap;
	cap.open(0);
    if( !cap.isOpened() )
    {
        cout << "Could not initialize capturing...\n";
        return 0;
    }

	opticalflow = new OpticalFlow();//跟踪对象， 我用的是光流法，但是增强了跟踪的可靠性，具体看跟踪的代码
	opticalflow->Initialize(WIDTH, HEIGHT, cvSize(9, 9), 3);
	


    Mat frame, gray, prevGray, image;
  
	IplImage* prevImage;									///<用于跟踪特征点的灰度图像
	std::vector<MatchedPoints> matchedPoints;
	cv::Mat sceDescriptors;//描述特征的变量
									///< 
	prevImage = cvCreateImage(cvSize(WIDTH, HEIGHT), IPL_DEPTH_8U, 1);   
	std::vector<int> numMatchedPointsPerRef;
	numMatchedPointsPerRef.resize(numImages);
	while(1)
    {
		for(int n = 0; n < numImages; n++)
			numMatchedPointsPerRef[n] = 0;
		
        cap >> image;
		//image = imread("1.png", 1);
        if( image.empty() )
            break;
		image.copyTo(frame);

		
		cvtColor(image, gray, CV_BGR2GRAY);
		GaussianBlur(gray, gray, cv::Size(3, 3), 0);
		IplImage grayImage(gray);
		printf("\n");
		double tt = (double)cvGetTickCount();
		for(int i = 0; i < numImages; i++)
		{
			tracking(i, prevImage, &grayImage);
		}
		tt = (double)cvGetTickCount() - tt;
		
		printf( "tracking time = %g ms\n", tt/(cvGetTickFrequency()*1000.));
		//ClassifyIDsAndGetHomographies(numImages, matchedPoints, prevImage, &grayImage, sideBySideImage);
						
		std::vector<cv::KeyPoint> sceneDetectedKeypoints;//检测到的特征点
		std::vector<cv::KeyPoint> sceneCvKeypoints;//选取的规定数量的特征点
		std::vector<SceKeypoints> sceneKeypoints;
		
		tt = (double)cvGetTickCount();
		detector->detect(gray,sceneDetectedKeypoints);
		tt = ((double)cvGetTickCount() - tt)  /*/sceneDetectedKeypoints.size()*/;
		printf( "detection time = %g ms\n", (tt/(cvGetTickFrequency()*1000.)));
		//sprintf(text5, "all time = %gms",tt/(cvGetTickFrequency()*1000.));

		int localcount = sceneDetectedKeypoints.size();

			int randInd = 0;
			if ( sceneDetectedKeypoints.size() < FEATURE_VALID_COUNT  )//限定检测特征点的个数
			{
				for(int i = 0; i < sceneDetectedKeypoints.size(); i++)
				{
					cv::KeyPoint fpt;

					fpt.class_id = sceneDetectedKeypoints[i].class_id;
					fpt.pt.x = sceneDetectedKeypoints[i].pt.x;
					fpt.pt.y = sceneDetectedKeypoints[i].pt.y;
					fpt.size = sceneDetectedKeypoints[i].size;
					fpt.angle = sceneDetectedKeypoints[i].angle;
					fpt.octave = sceneDetectedKeypoints[i].octave;
					fpt.response = sceneDetectedKeypoints[i].response;
					sceneCvKeypoints.push_back(fpt);

				}

			}
			else
			{
				for ( int i = 0; i < MAX_INDEX_NUM; i++ )
				{
					randInd = randomIndex[i];                                                                         
					if ( randInd >= sceneDetectedKeypoints.size())
					{
						continue;
					}
					if(sceneCvKeypoints.size() >= FEATURE_VALID_COUNT)
						break;
					cv::KeyPoint fpt;
					fpt.class_id = sceneDetectedKeypoints[randInd].class_id;
					fpt.pt.x = sceneDetectedKeypoints[randInd].pt.x;
					fpt.pt.y = sceneDetectedKeypoints[randInd].pt.y;
					fpt.size = sceneDetectedKeypoints[randInd].size;
					fpt.angle = sceneDetectedKeypoints[randInd].angle;
					fpt.octave = sceneDetectedKeypoints[randInd].octave;
					fpt.response = sceneDetectedKeypoints[randInd].response;
					sceneCvKeypoints.push_back(fpt);
				}
			}

			tt = (double)cvGetTickCount();
			descriptorExtractor->compute(gray, sceneCvKeypoints, sceDescriptors);
			tt = (double)cvGetTickCount() - tt;
			printf( "descriptorExtractor time = %gms\n", tt/(cvGetTickFrequency()*1000.));

			for(int i = 0; i < sceneCvKeypoints.size(); i++)//转换为SceKeypoints结构体来表示，SceKeypoints结构体多了一个repositoryRef变量，用于记录（假如这个特征点参与了匹配）这个特征点匹配到的模板图像里的那个特征点的序号，初始化为-1
			{
				SceKeypoints fpt;

				fpt.kp.class_id = -1;
				fpt.bActive = false;
				fpt.repositoryRef = -1;
				fpt.kp.pt.x = sceneCvKeypoints[i].pt.x;
				fpt.kp.pt.y = sceneCvKeypoints[i].pt.y;
				fpt.kp.angle = sceneCvKeypoints[i].angle;
				fpt.kp.size = sceneCvKeypoints[i].size;
				fpt.kp.response = sceneCvKeypoints[i].response;
				fpt.kp.octave = sceneCvKeypoints[i].octave;
				sceneKeypoints.push_back(fpt);

			}
#if USE_LSH_MATCH//
			tt = (double)cvGetTickCount();
			matcher->knnMatch(sceDescriptors, LSHmatches, 1);
			tt = (double)cvGetTickCount() - tt;
			printf( "match time = %gms\n", tt/(cvGetTickFrequency()*1000.));
#else
			tt = (double)cvGetTickCount();
			descriptorMatcher->match(sceDescriptors, matches);
			tt = ((double)cvGetTickCount() - tt);
			printf( "bruce match time = %gms\n", tt/(cvGetTickFrequency()*1000.));			
#endif			
			double max_dist = 0; double min_dist = 100;  
			
#if USE_LSH_MATCH//
			for( int i = 0; i < LSHmatches.size(); i++ )  
			{   for( int j = 0; j < LSHmatches[i].size(); j++ )
				{
					double dist = LSHmatches[i][j].distance;  
					if( dist < min_dist ) min_dist = dist;  
					if( dist > max_dist ) max_dist = dist;  
				}
			}  
#else
			//找较好的匹配对
			for( int i = 0; i < matches.size(); i++ )  
			{   
				double dist = matches[i].distance;  
				if( dist < min_dist ) min_dist = dist;  
				if( dist > max_dist ) max_dist = dist;  
			}  
#endif				 
			matchedPoints.clear();

#if USE_LSH_MATCH//
			for( int i = 0; i < LSHmatches.size(); i++ )  
			{   for( int j = 0; j < LSHmatches[i].size(); j++ )
				{
					if( LSHmatches[i][j].distance < 0.25*max_dist )  
					{   
						MatchedPoints matchedPt;
						
						matchedPt.ID = LSHmatches[i][j].imgIdx;
						matchedPt.xImg = sceneKeypoints[LSHmatches[i][j].queryIdx].kp.pt.x;
						matchedPt.yImg = sceneKeypoints[LSHmatches[i][j].queryIdx].kp.pt.y;
						matchedPt.xRef = referenceRepository[matchedPt.ID][LSHmatches[i][j].trainIdx].kp.pt.x;
						matchedPt.yRef = referenceRepository[matchedPt.ID][LSHmatches[i][j].trainIdx].kp.pt.y;
						
						matchedPt.index = referenceRepository[matchedPt.ID][LSHmatches[i][j].trainIdx].index;
						matchedPoints.push_back(matchedPt);
						
						
					}  
				}
			}
#else
			for( int i = 0; i < matches.size(); i++ )  
			{   
				if( matches[i].distance < 0.4*max_dist )  
				{   
					MatchedPoints matchedPt;
					
					matchedPt.ID = matches[i].imgIdx;
					matchedPt.xImg = sceneKeypoints[matches[i].queryIdx].kp.pt.x;
					matchedPt.yImg = sceneKeypoints[matches[i].queryIdx].kp.pt.y;
					matchedPt.xRef = referenceRepository[matchedPt.ID][matches[i].trainIdx].kp.pt.x;
					matchedPt.yRef = referenceRepository[matchedPt.ID][matches[i].trainIdx].kp.pt.y;
					
					matchedPt.index = referenceRepository[matchedPt.ID][matches[i].trainIdx].index;
					matchedPoints.push_back(matchedPt);
					
					
				}  
			}
#endif
			for(int j = 0; j < numImages; j++)
			{
				for(int i = 0; i < matchedPoints.size(); i++)
				{
					if(matchedPoints[i].ID == j)
						numMatchedPointsPerRef[j]++;
				}
			}
	
			int idRef = 0;
			int index = *max_element(numMatchedPointsPerRef.begin(),numMatchedPointsPerRef.end());
			for(int i = 0; i < numMatchedPointsPerRef.size(); i++)
			{
				if(numMatchedPointsPerRef[i] == index)
					idRef = i;
			}
			int id = idRef;

					
				
			if((int)matchedPoints.size() > 9)
			{
					
				for(int i = 0; i < matchedPoints.size(); i++)
				{
					if(/*!matchedPoints[i].bUsed && */matchedPoints[i].ID == id && !referenceRepository[id][matchedPoints[i].index].bActive)
					{
						//限定匹配对数
						if (sceMatchedKeypoints[id].size() > 199 )
							break;
						referenceRepository[id][matchedPoints[i].index].bActive = true;

						MatchedPoints sceMatchedPts;
						MatchedPoints refMatchedPts;

						sceMatchedPts.bUsed = true;					
						sceMatchedPts.xImg = matchedPoints[i].xImg;
						sceMatchedPts.yImg= matchedPoints[i].yImg;
						sceMatchedPts.ID = matchedPoints[i].ID;
						sceMatchedPts.index = matchedPoints[i].index;
						//sceMatchedPts.angleBinIndex =  matchedPoints[i].angleBinIndex;

						refMatchedPts.bUsed = true;					
						refMatchedPts.xImg = matchedPoints[i].xRef;
						refMatchedPts.yImg = matchedPoints[i].yRef;
						refMatchedPts.ID = matchedPoints[i].ID;
						refMatchedPts.index = matchedPoints[i].index;
						//refMatchedPts.angleBinIndex = matchedPoints[i].angleBinIndex;
							
						sceMatchedKeypoints[id].push_back(sceMatchedPts);
						refMatchedKeypoints[id].push_back(refMatchedPts);

							
					}

				}
			}
				
				
			Mat homo;
			Mat homograph;
			vector<Point2f>	pt1,pt2;
			if((int)refMatchedKeypoints[id].size() > 9)
			{
					
				for(int i = 0; i < refMatchedKeypoints[id].size(); i++)
				{
					if( sceMatchedKeypoints[id][i].bUsed && id == sceMatchedKeypoints[id][i].ID)
					{
						pt1.push_back(Point2f(sceMatchedKeypoints[id][i].xImg, sceMatchedKeypoints[id][i].yImg));
						pt2.push_back(Point2f(refMatchedKeypoints[id][i].xImg, refMatchedKeypoints[id][i].yImg));
						//cvCircle(sideBySideImage, cvPoint(sceMatchedKeypoints[id][i].xImg, sceMatchedKeypoints[id][i].yImg), 3, Scalar(0,255,0), -1);
						//cvLine(sideBySideImage, cvPoint(sceMatchedKeypoints[id][i].xImg, sceMatchedKeypoints[id][i].yImg), cvPoint(refMatchedKeypoints[id][i].xImg + WIDTH, refMatchedKeypoints[id][i].yImg), CV_RGB(255, 255, 0));
					}
				}
					
					
					
				tt = (double)cvGetTickCount();
				homo = findHomography(pt2, pt1, CV_RANSAC, 10);//第一次算homograph	
				double ttt = (double)cvGetTickCount() - tt;
				//if(niceHomography(homo))
				{
					vector<Point2f>	pt1,pt2;
					for(int j=0; j<(int)refMatchedKeypoints[id].size(); j++)
					{					
						vector<Point2f> refImagePoint, imagePoint;
						refImagePoint.push_back(Point2f(refMatchedKeypoints[id][j].xImg, refMatchedKeypoints[id][j].yImg));
							
						perspectiveTransform(refImagePoint, imagePoint, homo);
						float error = ((sceMatchedKeypoints[id][j].xImg - imagePoint[0].x)*(sceMatchedKeypoints[id][j].xImg - imagePoint[0].x) + (sceMatchedKeypoints[id][j].yImg - imagePoint[0].y)*(sceMatchedKeypoints[id][j].yImg - imagePoint[0].y));
						if(error <= 16.0)//用计算的homograph矩阵，让模板图像的每个特征点warp到场景图像中去，看看与场景图像中对应的特征点的距离，大于2则去除
						{
							refMatchedKeypoints[id][j].bUsed = true;
							sceMatchedKeypoints[id][j].bUsed = true;

							pt1.push_back(Point2f(sceMatchedKeypoints[id][j].xImg, sceMatchedKeypoints[id][j].yImg));
							pt2.push_back(Point2f(refMatchedKeypoints[id][j].xImg, refMatchedKeypoints[id][j].yImg));
							//cvCircle(sideBySideImage, cvPoint(sceMatchedKeypoints[id][j].xImg, sceMatchedKeypoints[id][j].yImg), 3, Scalar(0,255,0), -1);
							//cvLine(sideBySideImage, cvPoint(sceMatchedKeypoints[id][j].xImg, sceMatchedKeypoints[id][j].yImg), cvPoint(refMatchedKeypoints[id][j].xImg + WIDTH, refMatchedKeypoints[id][j].yImg), CV_RGB(255, 0, 0));
								
						}
						else
						{
							refMatchedKeypoints[id][j].bUsed = false;
							sceMatchedKeypoints[id][j].bUsed = false;
								
							referenceRepository[id][refMatchedKeypoints[id][j].index].bActive = false;
							refMatchedKeypoints[id].erase(refMatchedKeypoints[id].begin() + j);
							sceMatchedKeypoints[id].erase(sceMatchedKeypoints[id].begin() + j);
							j--;
								
								
						}
					}
				}

				tt = (double)cvGetTickCount();
				if((int)refMatchedKeypoints[id].size() > 9)
					homograph = findHomography(pt2, pt1, CV_RANSAC, 5);//第2次算homograph	
				double tttt = (double)cvGetTickCount() - tt;
				printf( "homo time = %gms\n", (ttt + tttt)/(cvGetTickFrequency()*1000.));
					
			}
				

				
								

			if((int)refMatchedKeypoints[id].size() > 9 /*&& niceHomography(homograph)*/)
			{
				double m1[9];
				for (int ind1 = 0; ind1 < 3; ind1++ )
				{
					for (int ind2 = 0; ind2 < 3; ind2++ )
					{
						m1[3* ind1 + ind2]	= homograph.at<double>(ind1, ind2);
					}
						
				}
					
				CvLevMarq solver(8, 0, cvTermCriteria(CV_TERMCRIT_ITER+CV_TERMCRIT_EPS, 10, DBL_EPSILON));
				CvMat modelPart = cvMat(solver.param->rows, solver.param->cols, CV_64F,  m1);
				cvCopy(&modelPart, solver.param);

				while(true)
				{
					const CvMat* _param = 0;
					CvMat* _JtJ = 0;
					CvMat* _JtErr = 0;
					double* _errNorm = 0;

					if( !solver.updateAlt( _param, _JtJ, _JtErr, _errNorm ))
						break;
						
					for(int i=0; i<refMatchedKeypoints[id].size(); i++)
					{
						const double* h = _param->data.db;
						double Mx = refMatchedKeypoints[id][i].xImg;
						double My = refMatchedKeypoints[id][i].yImg;
						double mx = sceMatchedKeypoints[id][i].xImg;
						double my = sceMatchedKeypoints[id][i].yImg;
						double ww = 1./(h[6]*Mx + h[7]*My + 1.);
						double _xi = (h[0]*Mx + h[1]*My + h[2])*ww;
						double _yi = (h[3]*Mx + h[4]*My + h[5])*ww;

						double err[] = { _xi - mx, _yi - my };
						if( _JtJ || _JtErr )
						{
							double J[][8] =
							{
								{ Mx*ww, My*ww, ww, 0, 0, 0, -Mx*ww*_xi, -My*ww*_xi },
								{ 0, 0, 0, Mx*ww, My*ww, ww, -Mx*ww*_yi, -My*ww*_yi }
							};
							for(int j=0; j<8; j++)
							{
								for(int k=j; k<8; k++)
								{
									_JtJ->data.db[j*8+k] += J[0][j]*J[0][k] + J[1][j]*J[1][k];
								}
								_JtErr->data.db[j] += J[0][j]*err[0] + J[1][j]*err[1];
							}
						}
						if( _errNorm )
							*_errNorm += err[0]*err[0] + err[1]*err[1];
					}
				}

				cvCopy( solver.param, &modelPart );
					
				for (int ind1 = 0; ind1 < 3; ind1++ )
				{
					for (int ind2 = 0; ind2 < 3; ind2++ )
					{
						homograph.at<double>(ind1, ind2) = *(modelPart.data.db);
						modelPart.data.db++;
					}
						
				}
				
			}


			if((int)refMatchedKeypoints[id].size() > 9)
			{
				vector<Point2f>	pt3, pt4;
				if(niceHomography(homograph))
				{			
					pt3.resize(4);
					pt4.resize(4);
						
					pt3[0].x = 0;
					pt3[0].y = 0;

					pt3[1].x = refImage[id].cols;
					pt3[1].y = 0;

					pt3[2].x = refImage[id].cols;
					pt3[2].y = refImage[id].rows;

					pt3[3].x = 0;
					pt3[3].y = refImage[id].rows;
						
					perspectiveTransform(pt3, pt4, homograph);
			

						
					line(frame, pt4[1],pt4[2], colors[id], 2);
					line(frame, pt4[2],pt4[3], colors[id], 2);
					line(frame, pt4[1],pt4[0], colors[id], 2);
					line(frame, pt4[0],pt4[3], colors[id], 2);
				}
			}
				
		cvCopyImage(&grayImage, prevImage);
		imshow("window", frame);				
		
		char c = (char)waitKey(1);
        if( c == 27 )
            break;
		
    }
	opticalflow->Release();
	delete opticalflow;
	
    return 0;
}

