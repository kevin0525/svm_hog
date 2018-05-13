///*
//opencv3.2.0  vs2015
//hog+svm detect����
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
//#define filepath  "f://0xk/1xk_workspace/hog_svm/hog_svm/svm_hog/svm_hog2/svm_hog2/dataset_deck/"
//// ʹ��ѵ���õķ�����ʶ��
//void detect()
//{
//	videocapture capture("out.avi");
//	double rate = capture.get(cv_cap_prop_fps);//��ȡ��Ƶ�ļ���֡��  
//	videowriter writer("out1.avi", cv_fourcc('m', 'j', 'p', 'g'), rate, size(960, 540), true);//������Ƶ�Ĵ�СҪ����img�Ĵ�Сһ��
//	if (!writer.isopened())
//	{
//		printf("write1 error .. \n"); return;
//	}
//
//	mat img;
//	mat partimg;
//	file* f = 0;
//	char _filename[1024];
//	int partimg_count = 0;
//
//	//����ѵ���õ��б����Ĳ���(ע�⣬��svm->save����ķ�������ͬ)
//	vector<float> detector;
//	ifstream filein(string(filepath) + "hog_svm.txt", ios::in);
//	float val = 0.0f;
//	double fps = 0.0;
//	while (!filein.eof())
//	{
//		filein >> val;
//		//cout << val<<endl;
//		detector.push_back(val);
//	}
//	filein.close();
//
//	//����hog
//	hogdescriptor hog(cvsize(64, 64), cvsize(16, 16), cvsize(8, 8), cvsize(8, 8), 9);
//	hog.setsvmdetector(detector);// ʹ���Լ�ѵ���ķ�����
//								 //hog.setsvmdetector(hogdescriptor::getdefaultpeopledetector());//����ֱ��ʹ��05 cvpr��ѵ���õķ�����,�����Ͳ���train()���������
//	//cout << "set hog done" << endl;
//
//	// ���ͼƬ
//	while (capture.isopened())
//	{
//		capture >> img;
//		if (img.empty()) break;
//		fflush(stdout);
//		vector<rect> found, found_filtered;
//		double t = (double)gettickcount();
//		// run the detector with default parameters. to get a higher hit-rate
//		// (and more false alarms, respectively), decrease the hitthreshold and
//		// groupthreshold (set groupthreshold to 0 to turn off the grouping completely).
//		//��߶ȼ��
//		resize(img, img, size(960, 540));
//		hog.detectmultiscale(img, found, 0, size(8, 8), size(0, 0), 1.05, 2);
//		t = (double)gettickcount() - t;
//		//printf("detection time = %gms\n", t*1000. / cv::gettickfrequency());
//		cout << 1000 / (t*1000. / cv::gettickfrequency()) << endl;
//		
//		size_t i, j;
//
//		//ȥ���ռ��о������������ϵ�����򣬱������
//		for (i = 0; i < found.size(); i++)
//		{
//			rect r = found[i];
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
//			rect r = found_filtered[i];
//			//xk20180508
//			if (i>0) {        //��ս�� if(i>0)   if (found_filtered.size()>1)
//				string partimgname = "partimg/" + to_string(partimg_count) + ".jpg";
//				partimg_count++;
//				//namedwindow(partimgname, 1);
//				partimg = img(r);
//				imwrite(partimgname, partimg);
//			}
//		}
//
//		// �ʵ���С����
//		for (i = 0; i < found_filtered.size(); i++)
//		{
//			rect r = found_filtered[i];
//			// the hog detector returns slightly larger rectangles than the real objects.
//			// so we slightly shrink the rectangles to get a nicer output.
//			r.x += cvround(r.width*0.1);
//			r.width = cvround(r.width*0.8);
//			r.y += cvround(r.height*0.07);
//			r.height = cvround(r.height*0.8);
//			rectangle(img, r.tl(), r.br(), cv::scalar(0, 255, 0), 3);
//		}
//
//		imshow("detector", img);
//		//��������Ƶ
//		writer << img;
//
//		//�ȴ�50ms������Ӽ����������q��q��������esc�������˳�
//		int key = waitkey(30);
//		if (key == 'q' || key == 'q' || key == 27)
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
//	detect();
//}