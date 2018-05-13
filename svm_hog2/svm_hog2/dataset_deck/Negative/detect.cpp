///*
//opencv3.2.0  vs2015
//HOG+SVM detect����
//��Ⲣ��������Ƶ
//�������������񣬱�����������ͼƬ�������������Ϊ�´�ѵ���ĸ�����
//*/
//
//
//#include "opencv2/opencv.hpp"
//#include "opencv2/ml.hpp"
//
//#include <stdio.h>
//#include <string.h>
//#include <cctype>
//#include<iostream>
//#include <fstream>
//
//using namespace cv;
//using namespace cv::ml;
//using namespace std;
//
//#define FILEPATH  "F://0xk/1xk_workspace/HOG_SVM/hog_svm/svm_hog/svm_hog2/svm_hog2/dataset_deck/"
//// ʹ��ѵ���õķ�����ʶ��
//void Detect()
//{
//	VideoCapture capture("out.avi");
//	double rate = capture.get(CV_CAP_PROP_FPS);//��ȡ��Ƶ�ļ���֡��  
//	VideoWriter writer("out1.avi", CV_FOURCC('M', 'J', 'P', 'G'), rate, Size(960, 540), true);//������Ƶ�Ĵ�СҪ����img�Ĵ�Сһ��
//	if (!writer.isOpened())
//	{
//		printf("write1 error .. \n"); return;
//	}
//
//	Mat img;
//	Mat partImg;
//	FILE* f = 0;
//	char _filename[1024];
//	int partImg_count = 0;
//
//	//����ѵ���õ��б����Ĳ���(ע�⣬��svm->save����ķ�������ͬ)
//	vector<float> detector;
//	ifstream fileIn(string(FILEPATH) + "HOG_SVM.txt", ios::in);
//	float val = 0.0f;
//	double fps = 0.0;
//	while (!fileIn.eof())
//	{
//		fileIn >> val;
//		//cout << val<<endl;
//		detector.push_back(val);
//	}
//	fileIn.close();
//
//	//����HOG
//	HOGDescriptor hog(cvSize(64, 64), cvSize(16, 16), cvSize(8, 8), cvSize(8, 8), 9);
//	hog.setSVMDetector(detector);// ʹ���Լ�ѵ���ķ�����
//								 //hog.setSVMDetector(HOGDescriptor::getDefaultPeopleDetector());//����ֱ��ʹ��05 CVPR��ѵ���õķ�����,�����Ͳ���Train()���������
//	//cout << "set HOG done" << endl;
//
//	// ���ͼƬ
//	while (capture.isOpened())
//	{
//		capture >> img;
//		if (img.empty()) break;
//		fflush(stdout);
//		vector<Rect> found, found_filtered;
//		double t = (double)getTickCount();
//		// run the detector with default parameters. to get a higher hit-rate
//		// (and more false alarms, respectively), decrease the hitThreshold and
//		// groupThreshold (set groupThreshold to 0 to turn off the grouping completely).
//		//��߶ȼ��
//		resize(img, img, Size(960, 540));
//		hog.detectMultiScale(img, found, 0, Size(8, 8), Size(0, 0), 1.05, 2);
//		t = (double)getTickCount() - t;
//		//printf("detection time = %gms\n", t*1000. / cv::getTickFrequency());
//		cout << 1000 / (t*1000. / cv::getTickFrequency()) << endl;
//		
//		size_t i, j;
//
//		//ȥ���ռ��о������������ϵ�����򣬱������
//		for (i = 0; i < found.size(); i++)
//		{
//			Rect r = found[i];
//			for (j = 0; j < found.size(); j++)
//				if (j != i && (r & found[j]) == r)
//					break;
//			if (j == found.size())
//				found_filtered.push_back(r);
//		}
//
//		//������������ͼƬ��Ϊ�������´�ѵ���� xk
//		for (i = 0; i < found_filtered.size(); i++)
//		{
//			Rect r = found_filtered[i];
//			//xk20180508
//			if (i>0) {        //��ս�� if(i>0)   if (found_filtered.size()>1)
//				string partImgName = "partImg/" + to_string(partImg_count) + ".jpg";
//				partImg_count++;
//				//namedWindow(partImgName, 1);
//				partImg = img(r);
//				imwrite(partImgName, partImg);
//			}
//		}
//
//		// �ʵ���С����
//		for (i = 0; i < found_filtered.size(); i++)
//		{
//			Rect r = found_filtered[i];
//			// the HOG detector returns slightly larger rectangles than the real objects.
//			// so we slightly shrink the rectangles to get a nicer output.
//			r.x += cvRound(r.width*0.1);
//			r.width = cvRound(r.width*0.8);
//			r.y += cvRound(r.height*0.07);
//			r.height = cvRound(r.height*0.8);
//			rectangle(img, r.tl(), r.br(), cv::Scalar(0, 255, 0), 3);
//		}
//
//		imshow("detector", img);
//		//��������Ƶ
//		writer << img;
//
//		//�ȴ�50ms������Ӽ����������q��Q��������Esc�������˳�
//		int key = waitKey(30);
//		if (key == 'q' || key == 'Q' || key == 27)
//			break;
//		
//	}
//	if (f)
//		fclose(f);
//
//	capture.release();
//	writer.release();
//	return;
//}
//
//int main()
//{
//	Detect();
//}