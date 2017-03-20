#include <opencv2/opencv.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <iostream>
#include <thread>
#include <chrono>
#include <string>
#include <stdlib.h>
#include <curl/curl.h>

#include "opencvcontroller.h"
#include "qtserver.h"

using namespace std;
using namespace cv;
using namespace std::chrono;

void detectAndDisplay( Mat frame, OpenCVController* controller );
void resetCheck();

string face_cascade_name = "../cascade/haarcascade_frontalface_alt.xml";
string eyes_cascade_name = "../cascade/haarcascade_eye_tree_eyeglasses.xml";
CascadeClassifier face_cascade;
CascadeClassifier eyes_cascade;
string window_name = "Capture - Face detection";
bool is_close=false, is_display=false;
milliseconds close_time;
RNG rng(12345);

OpenCVController::OpenCVController() {
    is_off=true;
}

OpenCVController::~OpenCVController() {
}

void OpenCVController::runOpenCV() {
    cout << "Run OpenCV" << endl;

    VideoCapture capture;
    Mat frame;

    if( !face_cascade.load( face_cascade_name ) ){
        cout << "Error loading face cascade" << endl;
    }
    if( !eyes_cascade.load( eyes_cascade_name ) ){
        cout << "Error loading eyes cascade" << endl;
    };

    capture.open( -1 );

    if ( ! capture.isOpened() ) {
        cout << "Error loading video";
    }

    while (!is_off && capture.read(frame)) {
        if( frame.empty() ) {
            cout << "No capture frame";
            break;
        }
        detectAndDisplay(frame,this);
    }
    cout << "Exit OpenCV" << endl;
}

void detectAndDisplay( Mat frame, OpenCVController* controller ) {
    std::vector<Rect> faces;
    Mat frame_gray;
    cvtColor( frame, frame_gray, CV_BGR2GRAY );

    face_cascade.detectMultiScale( frame_gray, faces, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE, Size(30, 30) );

    for( size_t i = 0; i < faces.size(); i++ ) {
        Mat faceROI = frame_gray( faces[i] );
        std::vector<Rect> eyes;

        eyes_cascade.detectMultiScale( faceROI, eyes, 1.1, 2, 0 |CV_HAAR_SCALE_IMAGE, Size(30, 30) );

        //Don't check for eye close if there are more than 2 users
        if (faces.size()>1) {
            is_close=false;
            continue;
        }

        //Checking if face has 2 eyes
        if (eyes.size()>=2 && is_display) {
            resetCheck();
            cout << "awake" << endl;
            emit controller->onStateChanged("0");
        } else if (is_close && !is_display) {
            milliseconds curTime = duration_cast< milliseconds >(system_clock::now().time_since_epoch());
            milliseconds difference = duration_cast<milliseconds>(curTime - close_time);
            if (difference.count()>=5000) {
                srand (time(NULL));
                cout << "sleeping" << endl;
                emit controller->onStateChanged("1");
                is_display=true;
            }
        } else if (eyes.size()==0) {
            close_time= duration_cast< milliseconds >(system_clock::now().time_since_epoch());
            is_close=true;
        }
    }
}

void resetCheck() {
    is_close=false;
    is_display=false;
}
