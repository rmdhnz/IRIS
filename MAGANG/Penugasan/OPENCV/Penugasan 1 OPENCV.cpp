#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <bits/stdc++.h>
using namespace std;
using namespace cv;
int width = 1200,height = 700;
int main (int argc, char** argv){
    string path = "bola.jpeg";
    Mat foto,img_resize,img_color,tresh,output_foto;
    foto=imread(path);
    Point2f center;
    float radius;
    resize(foto,img_resize,Size(width,height));
    cvtColor(img_resize, img_color, COLOR_BGR2HSV);
    int L_H = 0,U_H = 58,L_S = 93,U_S = 250,L_V = 0,U_V = 255;

    inRange(img_color, Scalar (L_H, L_S, L_V), Scalar(U_H, U_S, U_V), tresh);
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    findContours(tresh, contours, hierarchy, RETR_TREE, CHAIN_APPROX_NONE);
    for (int i=0;i<contours.size();i++){
            vector<Point>cntrs;
            cntrs = contours[i];
            minEnclosingCircle(cntrs,center,radius);
            if (radius>=90 && radius <=180){
                circle(img_resize,center,radius,Scalar(225,0,0),3);
                printf ("x= %.2f, y= %.2f, radius= %.2f\n\n", center.x, center.y, radius);
                }
    }
    rotate(img_resize,output_foto,ROTATE_90_COUNTERCLOCKWISE);
    imshow("Display", output_foto);
    waitKey(0);
}
