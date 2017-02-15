#include "opencv2/objdetect.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <iostream>
#include <thread>
#include <chrono>
#include <string>
#include <stdlib.h>
#include <curl/curl.h>
#include <thread>

using namespace std;
using namespace cv;
using namespace std::chrono;

void detectAndDisplay( Mat frame, VideoCapture *capture_ptr );
void playVideo(string file_name, Mat *frame_ptr,Mat *frame_gray_ptr,VideoCapture *capture_ptr);
void checkAwake(Mat *frame_ptr,Mat *frame_gray_ptr, VideoCapture *capture_ptr);

string face_cascade_name = "haarcascade_frontalface_alt.xml";
string eyes_cascade_name = "haarcascade_eye_tree_eyeglasses.xml";
CascadeClassifier face_cascade;
CascadeClassifier eyes_cascade;
String window_name = "Capture - Face detection";
bool is_close=false, is_display=false;
milliseconds close_time;

int main( void )
{
    ios::sync_with_stdio(false);
    VideoCapture capture;
    Mat frame;

    //-- 1. Load the cascades
    if( !face_cascade.load( face_cascade_name ) ){ cout << "Error loading face cascade"; return -1; };
    if( !eyes_cascade.load( eyes_cascade_name ) ){ cout << "Error loading eyes cascade"; return -1; };

    //-- 2. Read the video stream
    capture.open( -1 );
    if ( ! capture.isOpened() ) { cout << "Error loading video"; return -1; }

    while ( capture.read(frame) )
    {
        if( frame.empty() )
        {
            cout << "No capture frame";
            break;
        }

        //-- 3. Apply the classifier to the frame
        detectAndDisplay( frame, &capture );

        char c = (char)waitKey(10);
        if( c == 27 ) { break; } // escape
    }
    return 0;
}

void resetCheck() {
    is_close=false; 
    is_display=false;
}

/** @function detectAndDisplay */
void detectAndDisplay( Mat frame, VideoCapture *capture_ptr )
{
    std::vector<Rect> faces;
    Mat frame_gray;

    cvtColor( frame, frame_gray, COLOR_BGR2GRAY );
    equalizeHist( frame_gray, frame_gray );

    //-- Detect faces
    face_cascade.detectMultiScale( frame_gray, faces, 1.1, 2, 0|CASCADE_SCALE_IMAGE, Size(30, 30) );

    for ( size_t i = 0; i < faces.size(); i++ )
    {
        Mat faceROI = frame_gray( faces[i] );
        std::vector<Rect> eyes;

        //-- In each face, detect eyes
        eyes_cascade.detectMultiScale( faceROI, eyes, 1.1, 2, 0 |CASCADE_SCALE_IMAGE, Size(30, 30) );

        //Don't check for eye close if there are more than 2 users
        if (faces.size()>1) {
            is_close=false;
            continue;
        }

        if (eyes.size()>=2 && is_display) {
            resetCheck();
            cout << "Target is awake" << endl;
        } else if (is_close && !is_display) {
            milliseconds curTime = duration_cast< milliseconds >(system_clock::now().time_since_epoch());
            milliseconds difference = duration_cast<milliseconds>(curTime - close_time);
            if (difference.count()>=5000) {
                srand (time(NULL));
                cout << "Target is sleeping" << endl;
                is_display=true;
                playVideo("test.mp4",&frame,&frame_gray, capture_ptr);
            }
        } else if (eyes.size()==0) {
            close_time= duration_cast< milliseconds >(system_clock::now().time_since_epoch());
            is_close=true;
        }

    }
}

void playVideo(string file_name, Mat *frame_ptr,Mat *frame_gray_ptr,VideoCapture *capture_ptr) {
    VideoCapture capture(file_name);
    Mat frame;
    string const WINDOW_NAME="vid";

    if( !capture.isOpened() )
        throw "Error openning video";

    namedWindow( WINDOW_NAME, 0);
    while (is_display) {
        checkAwake(frame_ptr,frame_gray_ptr,capture_ptr);
        capture >> frame;
        if(frame.empty())
            break;
        imshow(WINDOW_NAME, frame);
        waitKey(20);
    }
    destroyWindow(WINDOW_NAME);
}

void checkAwake(Mat *frame_ptr,Mat *frame_gray_ptr, VideoCapture *capture_ptr) {
    //Transfer all minimum required instance using pointer to detect faces and eyes
    Mat frame=*frame_ptr;
    Mat frame_gray=*frame_gray_ptr;
    VideoCapture capture=*capture_ptr;
    std::vector<Rect> faces;

    capture.read(frame);
    cvtColor( frame, frame_gray, COLOR_BGR2GRAY );
    equalizeHist( frame_gray, frame_gray );

    face_cascade.detectMultiScale( frame_gray, faces, 1.1, 2, 0|CASCADE_SCALE_IMAGE, Size(30, 30) );
    if (faces.size()>1) {
        resetCheck();
    } else if (faces.size()==1) {
        Mat faceROI = frame_gray( faces[0] );
        std::vector<Rect> eyes;
        eyes_cascade.detectMultiScale( faceROI, eyes, 1.1, 2, 0 |CASCADE_SCALE_IMAGE, Size(30, 30) );
        if (eyes.size()>=2) {
            resetCheck();
            cout << "Stop the video" << endl;
        }
    }
}
