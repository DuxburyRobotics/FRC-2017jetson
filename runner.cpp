#include <iostream>
#include <unistd.h>
#include "GripPipeline.h"
//#include "networktables/NetworkTable.h"
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
//#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main()
{
	//AxisCamera cam = AxisCamera("Axis-Camera", "10.49.8.12");
	Mat frame;
	VideoCapture cap;
	cap.open("http://10.49.8.12/axis-cgi/mjpg/video.cgi"); //standard html example
	//cap.open("rtsp://10.49.8.12:554/axis-media/media.amp"); //rtsp example
	//NetworkTable *vision;
	grip::GripPipeline mygrip;

	if(!cap.isOpened()) // tests for camera
	{
		cout << "no camera" << endl ;
		return -1;
	}

/* Network table connection
	while(1)
	{	
		try
		{
			NetworkTable::SetIPAddress("roborio-4908-frc.local");
			NetworkTable::SetClientMode();
			NetworkTable::Initialize();
			vision = NetworkTable::GetTable("vision");
			cout << "connected to vision table" << endl ;

			break;
		}
		catch(...)
		{
			cout << "no networkTable..waiting 2 seconds" << endl ;
			usleep(2000);
		}
	}
*/

	while(1)
	{
		bool rGood = cap.read(frame);
		if(!rGood)
		{
			cout << "bad read from camera" << endl;
		} else {

	       	mygrip.GripPipeline::process(frame);

			cv::Rect r = cv::boundingRect(mygrip.GripPipeline::getfilterContoursOutput().get(0));

/*  Talk to netowrk table
 * 			vision->PutNumber("centerX", (r.x + (r.width / 2.0)));
			vision->PutNumber("centerY", (r.y + (r.height / 2.0)));
			vision->PutNumber("width", r.width);
			vision->PutNumber("height", r.height);
			vision->PutNumber("area", r.area());*/

			cout << "centerX: " << r.x " " << (r.width / 2.0) << endl;
			cout << "centerY: "  r.y << " " (r.height / 2.0) << endl;
			cout << "width: " << r.width << endl;
			cout << "height: " << r.height << endl;
			cout << "area: " << r.area() << endl;
		}
	}

}
