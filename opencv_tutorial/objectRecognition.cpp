#include <iostream> 
#include <opencv2/opencv.hpp>


using namespace cv; 
using namespace std; 

void findMatching(Mat image){
  vector<vector<Point> > contours;
  vector<Vec4i> hierarchy;
  vector<vector<Point> > ref_contours;
  vector<Vec4i> ref_hierarchy;
  vector<Point> ref_contour;
  bool found = NULL;
  double distance;
  int i;
  double quality_measure = 0.05;
  
  Mat ref_image = imread("Apple.png", IMREAD_GRAYSCALE);
  Mat image_threshold;
  threshold(ref_image, image_threshold, 0, 255, THRESH_OTSU);
  findContours(image_threshold, ref_contours, ref_hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);
  drawContours(image_threshold, ref_contours, -1, (0, 255, 0), 4, LINE_8, ref_hierarchy, 0);
  ref_contour = ref_contours[0];

  findContours(image, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);

  if (contours.size() == 0){
    cout << "No objects detected\n";
    return;
  }
  else{
    cout << "Number of Objects Detected: " << contours.size() - 1 << endl;
    for (i = 0; i < contours.size(); i++){
      distance = matchShapes(contours[i], ref_contour, 1, 0);
      cout << "Distance for i " << i << ", " << distance << endl;
      if (distance < quality_measure){
	found = true;
	break;
      }
    }
    if (found)
      {
	Point2f center;
	float radius;
	
	minEnclosingCircle(contours[i], center, radius);
	cout << center << ", " << radius << endl;
	//	Mat output = Mat::zeros(image.rows, image.cols,CV_8UC3);
	circle(image, center, radius, (0, 255, 0), 2, 8);
	imshow("Result", image);
      }
    else{
      cout << "No match found\n";
    }
  }
  return;
}
      

// Driver code 
int main(int argc, char** argv) 
{ 
    // Read the image file as 
    Mat image = imread("Fruit2.png", IMREAD_GRAYSCALE); 
      // Error Handling 
    if (image.empty()) { 
        cout << "Image File "
             << "Not Found" << endl; 
  
        // wait for any key press 
        cin.get(); 
        return -1; 
    }

    Mat img_noise;
    medianBlur(image, img_noise, 3);
    Mat image_threshold;
    threshold(img_noise, image_threshold, 0, 255, THRESH_OTSU);
    findMatching(image_threshold);
    // Wait for any keystroke 
    waitKey(0); 
    return 0; 
}
