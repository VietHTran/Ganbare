#include "opencvcontroller.h"
#include <iostream>

using namespace std;

OpenCVController::OpenCVController() {
    is_off=true;
}

OpenCVController::~OpenCVController() {

}

void OpenCVController::runOpenCV() {
    cout << "Run OpenCV" << endl;
    while (!is_off) {
    }
    cout << "Exit OpenCV" << endl;
}
