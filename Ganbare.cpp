#include <opencv2/objdetect.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <iostream>
#include <thread>
#include <chrono>
#include <string>
#include <stdlib.h>
#include <curl/curl.h>
#include <thread>
#include <strings.h>
#include "server.h"

using namespace std;
using namespace cv;
using namespace std::chrono;

void detectAndDisplay( Mat frame);
void defer();
void resetCheck();

string face_cascade_name = "haarcascade_frontalface_alt.xml";
string eyes_cascade_name = "haarcascade_eye_tree_eyeglasses.xml";
CascadeClassifier face_cascade;
CascadeClassifier eyes_cascade;
String window_name = "Capture - Face detection";
bool is_close=false, is_display=false;
milliseconds close_time;
Server server(1500);

int main( void )
{
    ios::sync_with_stdio(false);
    try {
        server.waitForClient();
    } catch (const exception &e) {
        cout << "Error connecting to client" << endl;
        return 1;
    }
    cout << "Sucessfully connect to client." << endl;
    cout << "Ready to scan for facial expression" << endl;

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
        detectAndDisplay( frame);

        char c = (char)waitKey(10);
        if( c == 27 ) { break; } // escape
    }
    return 0;
}


/** @function detectAndDisplay */
void detectAndDisplay( Mat frame)
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
            string status="awake\n";
            server.sendToClientStr(status);
            cout << status << endl;
        } else if (is_close && !is_display) {
            milliseconds curTime = duration_cast< milliseconds >(system_clock::now().time_since_epoch());
            milliseconds difference = duration_cast<milliseconds>(curTime - close_time);
            if (difference.count()>=5000) {
                srand (time(NULL));
                string status="sleeping\n";
                server.sendToClientStr(status);
                cout << status << endl;
                is_display=true;
            }
        } else if (eyes.size()==0) {
            close_time= duration_cast< milliseconds >(system_clock::now().time_since_epoch());
            is_close=true;
        }

    }
}

void defer() {
	server.closeConnection();
}

void resetCheck() {
    is_close=false; 
    is_display=false;
}
