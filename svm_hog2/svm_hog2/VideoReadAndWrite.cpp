///*
//opencv3.2.0  vs2015
//��д��Ƶ
//��ȡ��Ƶһ���ֲ�����
//
//��ȡ��ʼʱ�䣺begin  
//��ȡ��ֹʱ�䣺end
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
//	double rate = capture.get(CV_CAP_PROP_FPS);//��ȡ��Ƶ�ļ���֡��  
//	cout << rate << endl;
//	VideoWriter writer1("out.avi", CV_FOURCC('M', 'J', 'P', 'G'), rate, Size(960, 540),true);
//	if (!writer1.isOpened())
//	{
//		printf("write1 error .. \n"); return false;
//	}
//	Mat frame;
//	int begin = round(25 * rate);//��ȡƬ�εĿ�ʼʱ��
//	int end = round(30 * rate);//��ȡʱ�����ֹʱ��
//	int count = 0;//��ȡ֡��
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
//				//�ȴ�50ms������Ӽ����������q��Q��������Esc�������˳�
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