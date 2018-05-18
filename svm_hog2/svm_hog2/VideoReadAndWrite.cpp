///*
//opencv3.2.0  vs2015
//读写视频
//截取视频一部分并保存
//
//截取开始时间：begin  
//截取终止时间：end
//*/
//
//#include <opencv2/opencv.hpp>
//#include <opencv2/highgui/highgui.hpp>  
//#include <opencv2/core/core.hpp>  
//#include <stdio.h>
//#include <string.h>
//#include<iostream>
//#include <fstream>
//using namespace cv;
//using namespace std;
//
//int main() {
//
//	VideoCapture capture("F://000workspace/a.mp4");
//	double rate = capture.get(CV_CAP_PROP_FPS);//获取视频文件的帧率  
//	cout << rate << endl;
//	VideoWriter writer1("out.avi", CV_FOURCC('M', 'J', 'P', 'G'), rate, Size(960, 540),true);
//	if (!writer1.isOpened())
//	{
//		printf("write1 error .. \n"); return false;
//	}
//	Mat frame;
//	int begin = round(25 * rate);//截取片段的开始时间
//	int end = round(30 * rate);//截取时间的终止时间
//	int count = 0;//截取帧数
//	//cout << time << endl;
//	while (capture.isOpened()) {
//		
//		capture >> frame;
//		resize(frame, frame, Size(960,540));
//			
//		if (count > begin) {
//			if (count < end) {
//				imshow("Video", frame);
//				writer1 << frame;
//				//等待50ms，如果从键盘输入的是q、Q、或者是Esc键，则退出
//				int key = waitKey(2);
//				if (key == 'q' || key == 'Q' || key == 27)
//					break;
//			}
//			else {
//				break;
//			}
//		}
//		count++;
//		if (frame.empty())
//			break;
//		if (count >end) break;
//		
//	}
//	writer1.release();
//	capture.release();
//
//	return 0;
//}