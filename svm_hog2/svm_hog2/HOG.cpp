/*
HOG_SVM���
ѵ��+���


*/

#include "opencv2/opencv.hpp"
#include "opencv2/ml.hpp"

#include <stdio.h>
#include <string.h>
#include <cctype>
#include<iostream>
#include <fstream>

using namespace cv;
using namespace cv::ml;
using namespace std;

#define FILEPATH  "F://0xk/1xk_workspace/HOG_SVM/hog_svm_2/svm_hog2/svm_hog2/dataset1x1/"

///////////////////////////////////HOG+SVMʶ��ʽ2///////////////////////////////////////////////////	
void Train()
{
	////////////////////////////////����ѵ������ͼƬ·�������///////////////////////////////////////////////////
	//ͼ��·�������
	vector<string> imagePath;
	vector<int> imageClass;
	int numberOfLine = 0;
	string buffer;
	ifstream trainingData(string(FILEPATH)+"TrainData.txt");
	unsigned long n;

	while (!trainingData.eof())
	{
		getline(trainingData, buffer);
		if (!buffer.empty())
		{
			++numberOfLine;
			if (numberOfLine % 2 == 0)
			{
				//��ȡ�������
				imageClass.push_back(atoi(buffer.c_str()));
			}
			else
			{
				//��ȡͼ��·��
				imagePath.push_back(buffer);
			}
		}
	}

	//�ر��ļ�  
	trainingData.close();


	////////////////////////////////��ȡ������HOG����///////////////////////////////////////////////////
	//����������������
	int numberOfSample = numberOfLine / 2;
	Mat featureVectorOfSample(numberOfSample, 1764, CV_32FC1);//������ÿ��Ϊһ������

	//���������
	Mat classOfSample(numberOfSample, 1, CV_32SC1);

	Mat convertedImage;
	Mat trainImage;
	
	// ����HOG����
	for (vector<string>::size_type i = 0; i <= imagePath.size() - 1; ++i)
	{
		//����ͼƬ
		Mat src = imread(imagePath[i], -1);
		if (src.empty())
		{
			cout << "can not load the image:" << imagePath[i] << endl;
			continue;
		}
		//cout << "processing:" << imagePath[i] << endl;

		// ��һ��
		resize(src, trainImage, Size(64, 64));
		//imshow("src", trainImage);
		//int c = waitKey(0) & 255;
		//if (c == 'q' || c == 'Q' )
		//	break;
		// ��ȡHOG����
		HOGDescriptor hog(cvSize(64, 64), cvSize(16, 16), cvSize(8, 8), cvSize(8, 8), 9);
		vector<float> descriptors;
		double time1 = getTickCount();
		hog.compute(trainImage, descriptors, cvSize(4, 4));//����������ü�ⴰ�ڲ��������ͼƬ��С����64��128����������winStride
		double time2 = getTickCount();
		double elapse_ms = (time2 - time1) * 1000 / getTickFrequency();
		//cout << "HOG dimensions:" << descriptors.size() << endl;
		//cout << "Compute time:" << elapse_ms << endl;
		

		//���浽��������������
		for (vector<float>::size_type j = 0; j <= descriptors.size() - 1; ++j)
		{
			featureVectorOfSample.at<float>(i, j) = descriptors[j];
		}

		//�������������
		//!!ע���������һ��Ҫ��int ���͵�
		classOfSample.at<int>(i, 0) = imageClass[i];
	}


	///////////////////////////////////ʹ��SVM������ѵ��///////////////////////////////////////////////////	
	//���ò�����ע��Ptr��ʹ��
	Ptr<SVM> svm = SVM::create();
	svm->setType(SVM::C_SVC);
	svm->setKernel(SVM::LINEAR);//ע�����ʹ������SVM����ѵ������ΪHogDescriptor��⺯��ֻ֧�����Լ�⣡����
	svm->setTermCriteria(TermCriteria(CV_TERMCRIT_ITER, 1000, FLT_EPSILON));

	//ʹ��SVMѧϰ         
	svm->train(featureVectorOfSample, ROW_SAMPLE, classOfSample);

	//���������(���������SVM�Ĳ�����֧������,����rho)
	svm->save(string(FILEPATH) + "Classifier.xml");

	/*
	SVMѵ����ɺ�õ���XML�ļ����棬��һ�����飬����support vector������һ�����飬����alpha,��һ��������������rho;
    ��alpha����ͬsupport vector��ˣ�ע�⣬alpha*supportVector,���õ�һ������������������ǰ�����-1��֮���ٸ���������������һ��Ԫ��rho��
    ��ˣ���õ���һ�������������ø÷�������ֱ���滻opencv�����˼��Ĭ�ϵ��Ǹ���������cv::HOGDescriptor::setSVMDetector()����
	*/
	//��ȡ֧��������������Ĭ����CV_32F
	Mat supportVector = svm->getSupportVectors();//

	//��ȡalpha��rho
	Mat alpha;//ÿ��֧��������Ӧ�Ĳ�����(�������ճ���)��Ĭ��alpha��float64��
	Mat svIndex;//֧���������ڵ�����
	float rho = svm->getDecisionFunction(0, alpha, svIndex);
	
	//ת������:����һ��Ҫע�⣬��Ҫת��Ϊ32��
	Mat alpha2;
	alpha.convertTo(alpha2, CV_32FC1);

	//������������������
	Mat result(1, 1764, CV_32FC1);
	result = alpha2*supportVector;

	//����-1������Ϊʲô�����-1��
	//ע����Ϊsvm.predictʹ�õ���alpha*sv*another-rho�����Ϊ���Ļ�����Ϊ������������HOG�ļ�⺯���У�ʹ��rho+alpha*sv*another(anotherΪ-1)
	for (int i = 0; i < 1764; ++i)
		result.at<float>(0, i) *= -1;

	//�����������浽�ļ�������HOGʶ��
	//��������������б����Ĳ���(��)��HOG����ֱ��ʹ�øò�������ʶ��
	FILE *fp = fopen((string(FILEPATH) + "HOG_SVM.txt").c_str(), "wb");
	for (int i = 0; i<1764; i++)
	{
		fprintf(fp, "%f \n", result.at<float>(0,i));
	}
	fprintf(fp, "%f", rho);

	fclose(fp);

}
// ʹ��ѵ���õķ�����ʶ��
void Detect()
{
	Mat img;
	Mat partImg;
	FILE* f = 0;
	char _filename[1024];
	int result_count = 0;
	int partImg_count = 0;

	// ��ȡ����ͼƬ�ļ�·��
	f = fopen((string(FILEPATH) + "TestData.txt").c_str(), "rt");
	if (!f)
	{
		fprintf(stderr, "ERROR: the specified file could not be loaded\n");
		return;
	}

	
	//����ѵ���õ��б����Ĳ���(ע�⣬��svm->save����ķ�������ͬ)
	vector<float> detector;
	ifstream fileIn(string(FILEPATH) + "HOG_SVM.txt", ios::in);
	float val = 0.0f;
	while (!fileIn.eof())
	{
		fileIn >> val;
		//cout << val<<endl;
		detector.push_back(val);
	}
	fileIn.close();

	//����HOG
	HOGDescriptor hog(cvSize(64, 64), cvSize(16, 16), cvSize(8, 8), cvSize(8, 8), 9);
	hog.setSVMDetector(detector);// ʹ���Լ�ѵ���ķ�����
	//hog.setSVMDetector(HOGDescriptor::getDefaultPeopleDetector());//����ֱ��ʹ��05 CVPR��ѵ���õķ�����,�����Ͳ���Train()���������
	namedWindow("detector", 1);

	// ���ͼƬ
	for (;;)
	{
		// ��ȡ�ļ���
		char* filename = _filename;
		if (f)
		{
			if (!fgets(filename, (int)sizeof(_filename)-2, f))
				break;
			//while(*filename && isspace(*filename))
			//  ++filename;
			if (filename[0] == '#')
				continue;

			//ȥ���ո�
			int l = (int)strlen(filename);
			while (l > 0 && isspace(filename[l - 1]))
				--l;
			filename[l] = '\0';
			cout << filename;
			img = imread(filename);
			//imshow("1", img);

			
		}
		printf("%s:\n", filename);
		if (!img.data)
			continue;

		fflush(stdout);
		vector<Rect> found, found_filtered;
		double t = (double)getTickCount();
		// run the detector with default parameters. to get a higher hit-rate
		// (and more false alarms, respectively), decrease the hitThreshold and
		// groupThreshold (set groupThreshold to 0 to turn off the grouping completely).
		//��߶ȼ��
		resize(img, img, Size(960, 540));
		//xk20180508  padding ->Size(0,0)
		hog.detectMultiScale(img, found, 0, Size(8, 8), Size(0, 0), 1.05, 2);
		t = (double)getTickCount() - t;
		printf("detection time = %gms\n", t*1000. / cv::getTickFrequency());
		size_t i, j;

		//ȥ���ռ��о������������ϵ�����򣬱������
		for (i = 0; i < found.size(); i++)
		{
			Rect r = found[i];
			for (j = 0; j < found.size(); j++)
			if (j != i && (r & found[j]) == r)
				break;
			if (j == found.size())
				found_filtered.push_back(r);
		}

		// �ʵ���С����
		for (i = 0; i < found_filtered.size(); i++)
		{
			Rect r = found_filtered[i];
			// the HOG detector returns slightly larger rectangles than the real objects.
			// so we slightly shrink the rectangles to get a nicer output.
			r.x += cvRound(r.width*0.1);
			r.width = cvRound(r.width*0.8);
			r.y += cvRound(r.height*0.07);
			r.height = cvRound(r.height*0.8);
			//xk20180508  �������ͼƬ�����һ��ͼƬ��һ���֣�
			if (found_filtered.size()>1) {
				string partImgName = "partImg/" + to_string(partImg_count) + ".jpg";
				partImg_count++;
				//namedWindow(partImgName, 1);
				partImg = img(r);
				imwrite(partImgName, partImg);
			}
			rectangle(img, r.tl(), r.br(), cv::Scalar(0, 255, 0), 3);
		}

		imshow("detector", img);
		string resultPicName = "result/" + to_string(result_count)+".jpg";
		result_count++;
		//imwrite(resultPicName, img);//������ͼƬ
		int c = waitKey(10) & 255;
		if (c == 'q' || c == 'Q' || !f)
			break;
	}
	if (f)
		fclose(f);
	return;
}

void HOG_SVM2()
{
	//���ʹ��05 CVPR�ṩ��Ĭ�Ϸ�����������ҪTrain(),ֱ��ʹ��Detect���ͼƬ
	//Train();
	//cout << "Train done";
	Detect();
}

int main()
{
	 HOG_SVM2();
}