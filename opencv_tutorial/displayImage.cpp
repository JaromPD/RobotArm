
#include <opencv2/objdetect.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream> 

using namespace cv; 
using namespace std; 

void findFace(Mat image){
  CascadeClassifier faceCascade;
  vector<Rect> faces;
  Point center;
  int radius;
  
  faceCascade.load("haarcascade_frontalface_default.xml");

  faceCascade.detectMultiScale(image, faces, 1.1, 2, 0|CASCADE_SCALE_IMAGE, Size(30, 30));
  for (int i = 0; i < faces.size(); i++)
    {
      Rect r = faces[i];
      center.x = cvRound(r.x + r.width * 0.5);
      center.y = cvRound(r.y + r.height * 0.5);
      radius = cvRound((r.width + r.height) * 0.25);
      circle(image, center, radius, (0, 0, 255), 3, 8, 0);
    }
  return;
}

// Driver code 
int main(int argc, char** argv) 
{
  //  VideoCapture capture;
  Mat image;
  Mat gray;
  
  //  capture.open(0);
  /*  if (capture.isOpened()){
    while(1){
      capture >> image;
      if (image.empty())
	break;
  */
  gray = imread("lena.jpeg",IMREAD_GRAYSCALE);
  //      cvtColor(image, gray, COLOR_BGR2GRAY);

  imshow("Input", gray);
  waitKey(0);
      
  findFace(gray);
    // Wait for any keystroke
  imshow("Result", gray);
  waitKey(0);
  
    
  
  return 0; 
}
