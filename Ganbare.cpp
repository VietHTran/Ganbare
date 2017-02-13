#include "opencv2/objdetect.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

#include <iostream>
#include <thread>
#include <chrono>
#include <string>
#include <stdlib.h>
#include <curl/curl.h>

using namespace std;
using namespace cv;
using namespace std::chrono;

void detectAndDisplay( Mat frame );

String face_cascade_name = "haarcascade_frontalface_alt.xml";
String eyes_cascade_name = "haarcascade_eye_tree_eyeglasses.xml";
CascadeClassifier face_cascade;
CascadeClassifier eyes_cascade;
String window_name = "Capture - Face detection";
bool isClose=false, isDisplay=false;
milliseconds closeTime;

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
        detectAndDisplay( frame );

        char c = (char)waitKey(10);
        if( c == 27 ) { break; } // escape
    }
    return 0;
}

void resetCheck() {
    isClose=false; 
    isDisplay=false;
}

/** @function detectAndDisplay */
void detectAndDisplay( Mat frame )
{
    const string youtubeKeys[]={
    //Star Wars ost
    "cUBUlKgsNK8",
    "bzWSJG93P8",
    "o--bLEobBFY",
    //HjN ost
    "o2BE3IILRto",
    "uD7IUpQ7EsY",
    "3AtIhuKn2No",
    //Others
    "B3vqcbJwgCI",
    "VgSMxY6asoE",
    "8VGJGXMUhmc",
    ""
    };
    int length=sizeof(youtubeKeys)/sizeof(*youtubeKeys);
    std::vector<Rect> faces;
    Mat frame_gray;

    cvtColor( frame, frame_gray, COLOR_BGR2GRAY );
    equalizeHist( frame_gray, frame_gray );

    //-- Detect faces
    face_cascade.detectMultiScale( frame_gray, faces, 1.1, 2, 0|CASCADE_SCALE_IMAGE, Size(30, 30) );

    for ( size_t i = 0; i < faces.size(); i++ )
    {
        Point center( faces[i].x + faces[i].width/2, faces[i].y + faces[i].height/2 );
        ellipse( frame, center, Size( faces[i].width/2, faces[i].height/2 ), 0, 0, 360, Scalar( 255, 0, 255 ), 4, 8, 0 );

        Mat faceROI = frame_gray( faces[i] );
        std::vector<Rect> eyes;

        //-- In each face, detect eyes
        eyes_cascade.detectMultiScale( faceROI, eyes, 1.1, 2, 0 |CASCADE_SCALE_IMAGE, Size(30, 30) );

        for ( size_t j = 0; j < eyes.size(); j++ )
        {
            Point eye_center( faces[i].x + eyes[j].x + eyes[j].width/2, faces[i].y + eyes[j].y + eyes[j].height/2 );
            int radius = cvRound( (eyes[j].width + eyes[j].height)*0.25 );
            circle( frame, eye_center, radius, Scalar( 255, 0, 0 ), 4, 8, 0 );
        }

        //Don't check for eye close if there are more than 2 users
        if (faces.size()>1) {
            isClose=false;
            continue;
        }

        if (eyes.size()>=2 && isDisplay) {
            resetCheck();
            cout << "Target is awake" << endl;
        } else if (isClose && !isDisplay) {
            milliseconds curTime = duration_cast< milliseconds >(system_clock::now().time_since_epoch());
            milliseconds difference = duration_cast<milliseconds>(curTime - closeTime);
            if (difference.count()>=5000) {
                srand (time(NULL));
                cout << "Target is sleeping" << endl;
                string randKey=youtubeKeys[rand()%(length-1)];
                //string command="firefox http://plainvid.azurewebsites.net?link="+randKey;
                //system(command.c_str()); //TODO: Turn off when awake + Replace system call
                isDisplay=true;
            }
        } else if (eyes.size()==0) {
            closeTime= duration_cast< milliseconds >(system_clock::now().time_since_epoch());
            isClose=true;
        }

    }
    //-- Show what you got
    imshow( window_name, frame );
}
