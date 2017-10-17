#include <string>
#include <iostream>
#include "opencv2/opencv.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/highgui.hpp"


using namespace cv;
using namespace std;

int Hmin = 155;
int Hmax = 179;

int Smin = 130;
int Smax = 255;

int Vmin = 100;
int Vmax = 255;

const int FRAME_WIDTH = 640;
const int FRAME_HEIGHT = 480;

int MAX_NUM_OBJECTS=10;
int MIN_OBJECT_AREA = 20*20;
int MAX_OBJECT_AREA = FRAME_HEIGHT*FRAME_WIDTH/1.5;


// exports for the filter
extern "C" {
    bool filter_init(const char * args, void** filter_ctx);
    void filter_process(void* filter_ctx, Mat &src, Mat &dst);
    void filter_free(void* filter_ctx);
}


/**
    Initializes the filter. If you return something, it will be passed to the
    filter_process function, and should be freed by the filter_free function
*/
bool filter_init(const char * args, void** filter_ctx) {
    return true;
}

string intToString(int number){


	std::stringstream ss;
	ss << number;
	return ss.str();
}

void drawObject(int x, int y,Mat &frame){



	circle(frame,Point(x,y),20,Scalar(0,255,0),2);
    if(y-25>0)
    line(frame,Point(x,y),Point(x,y-25),Scalar(0,255,0),2);
    else line(frame,Point(x,y),Point(x,0),Scalar(0,255,0),2);
    if(y+25<FRAME_HEIGHT)
    line(frame,Point(x,y),Point(x,y+25),Scalar(0,255,0),2);
    else line(frame,Point(x,y),Point(x,FRAME_HEIGHT),Scalar(0,255,0),2);
    if(x-25>0)
    line(frame,Point(x,y),Point(x-25,y),Scalar(0,255,0),2);
    else line(frame,Point(x,y),Point(0,y),Scalar(0,255,0),2);
    if(x+25<FRAME_WIDTH)
    line(frame,Point(x,y),Point(x+25,y),Scalar(0,255,0),2);
    else line(frame,Point(x,y),Point(FRAME_WIDTH,y),Scalar(0,255,0),2);

	putText(frame,"Red Object",Point(x,y+30),1,1,Scalar(0,255,0),2);

}
/**
    Called by the OpenCV plugin upon each frame
*/
void filter_process(void* filter_ctx, Mat &src, Mat &dst) {
   

	//Matrix storage for HSV
	Mat HSV;

	//Matrix storage for binary threshold image
	Mat threshold;

	int x=0, y=0;
	
	//convert frame from BGR to HSV
	cvtColor(src, HSV, COLOR_BGR2HSV);

	//filter HSV image between values and store filtered image to 
	//threshold matrix
	inRange(HSV,Scalar(Hmin, Smin, Vmin),Scalar(Hmax, Smax, Vmax),threshold);

	Mat erodeElement = getStructuringElement(MORPH_RECT, Size(3,3));

	Mat dilateElement = getStructuringElement(MORPH_RECT, Size(8,8));

	//erode(src,dst,erodeElement);

	//dilate(src,dst,dilateElement);

	Mat temp;
	threshold.copyTo(temp);

	//Vectors for output of findContours
	vector< vector<Point> > contours;
	vector<Vec4i> hierarchy;

	findContours(temp,contours,hierarchy,CV_RETR_CCOMP,CV_CHAIN_APPROX_SIMPLE );

	double refArea = 0;
	bool objectFound = false;

	if (hierarchy.size() > 0) {
		int numObjects = hierarchy.size();
        //if number of objects greater than MAX_NUM_OBJECTS we have a noisy filter
        if(numObjects<MAX_NUM_OBJECTS){
			for (int index = 0; index >= 0; index = hierarchy[index][0]) {

				Moments moment = moments((cv::Mat)contours[index]);
				double area = moment.m00;

				//if the area is less than 20 px by 20px then it is probably just noise
				//if the area is the same as the 3/2 of the image size, probably just a bad filter
				//we only want the object with the largest area so we safe a reference area each
				//iteration and compare it to the area in the next iteration.
                		if(area>MIN_OBJECT_AREA && area<MAX_OBJECT_AREA && area>refArea){
					x = moment.m10/area;
					y = moment.m01/area;
					objectFound = true;
					refArea = area;
				}else {
					objectFound = false;
				}

			}
			//let user know you found an object
			if(objectFound ==true){
				putText(dst,"Tracking Object",Point(0,50),2,1,Scalar(0,255,0),2);
				//draw object location on screen
				drawObject(x,y,dst);
			}

		}else {
			putText(dst,"TOO MUCH NOISE! ADJUST FILTER",Point(0,50),1,2,Scalar(0,0,255),2);
		}
	}


    dst = src;

}

/**
    Called when the input plugin is cleaning up
*/
void filter_free(void* filter_ctx) {
    // empty
}