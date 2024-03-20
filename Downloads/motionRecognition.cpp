/*
* To compile: g++ opencv_test2.cpp -o opencv_test2 $(pkg-config --cflags --libs opencv)
*/
#include <opencv2/opencv.hpp>
#include <opencv2/tracking.hpp>
#include <opencv2/core/ocl.hpp>
#include <unistd.h>

using namespace cv;
using namespace std;
 
int main(int argc, char **argv) {

    Mat frame, gray, frameDelta, thresh, lastFrame;
    vector<vector<Point> > contours;
    VideoCapture capture; //open camera
    int i, largest_area, largest_area_index;
    
    //set the video size to 512x288 to process faster
    capture.set(3, 320);
    capture.set(4, 240);

    capture.open(0);
    if (capture.isOpened()){
      
      capture >> frame;
      
    //convert to grayscale and set the last frame
      cvtColor(frame, lastFrame, COLOR_BGR2GRAY);
      GaussianBlur(lastFrame, lastFrame, Size(21, 21), 0);

      while(1) {

	capture >> frame;
      
	//convert to grayscale
	cvtColor(frame, gray, COLOR_BGR2GRAY);
	GaussianBlur(gray, gray, Size(21, 21), 0);

	//compute difference between first frame and current frame
	absdiff(lastFrame, gray, frameDelta);
	threshold(frameDelta, thresh, 25, 255, THRESH_BINARY);
        
        dilate(thresh, thresh, Mat(), Point(-1,-1), 2);
        findContours(thresh, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

	largest_area = 0;
        for(i = 0; i< contours.size(); i++) {
	  if(contourArea(contours[i]) > largest_area) {
	    largest_area_index = i;
	  }
	}
	Point2f center;
	float radius;
	minEnclosingCircle(contours[largest_area_index], center, radius);
	circle(frame, center, radius, (110, 110, 0), 3, 0);    

	lastFrame = gray.clone();

        imshow("Camera", frame);
	
        if(waitKey(1) == 27){
	  //exit if ESC is pressed
	  break;
        }
	
      }
    }
    else
      cout << "Camera not available\n";
      
    return 0;
}
