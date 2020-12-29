// License: Apache 2.0. See LICENSE file in root directory.
// Copyright(c) 2017 Intel Corporation. All Rights Reserved.

#include <opencv2/opencv.hpp> // Include OpenCV API
#include <opencv2\xfeatures2d.hpp>
#include <cstdlib> // atoi 函數所在函式庫
#include "HRSDK.h"
#include "arm.h"
#include <librealsense2/rs.hpp> // Include RealSense Cross Platform API
#include <iostream>             // for cout
#include <algorithm>
#include <fstream>
#include <stdio.h>
#include <math.h>

#include <stdio.h>
#include <math.h>

#include "HRSDK.h"
#include "arm.h"
#include "sucker.h"
#define PI 3.1415926

using namespace std;
using namespace cv;


void __stdcall FuncName(uint16_t, uint16_t, uint16_t*, int) {
}

HROBOT robot;

double prepare1[6] = { 99, 424.3, 105, -180, 0, 90 };
double prepare2[6] = { 89, 424.3, 105, -180, 0, 90 };
//double parameter_a = -0.0005, parameter_b = 0.2078, parameter_c = -71.8573, parameter_d = 0.2074, parameter_e = 0.0011, parameter_f = 236.3920;
//double parameter_a = -0.002747, parameter_b = 0.208207, parameter_c = -72.270045, parameter_d = 0.207572, parameter_e = 0.000294, parameter_f = 221.339398;
//double parameter_a = -0.0002, parameter_b = 0.2115, parameter_c = -67.8573, parameter_d = 0.2082, parameter_e = 0.0013, parameter_f = 236.3920;
//puzzle1
double parameter_a = -0.002723, parameter_b = 0.210838, parameter_c = -58.866506, parameter_d = 0.212785, parameter_e = 0.003571, parameter_f = 233.831208;
//puzzle2
//double parameter_a = -0.002723, parameter_b = 0.210838, parameter_c = -58.866506, parameter_d = 0.206785, parameter_e = 0.004971, parameter_f = 232.801208;
double table_distance_arm = 60.0000;
double table_distance_camera = 0.2951;
float adjust_x, adjust_y;

double puzzle1[6] = { 100.211, 435.741, 127.911, -180, 0, 0 };//往左蓋住左邊黑膠帶
double puzzle2[6] = { -370.645, 435.741, 127.911, -180, 0, 0 };//右邊黑膠帶
//double puzzle[6] = { -86.03, 435.741, 127.911, -180, 0, 0 };

double puzzle[6] = { -47.269 + 5, 314.0 + 325.275 - 314, 127.911, -180, 0, 0 };


int pri[35] = { 2, 1, 1, 1, 2,    1, 0, 0, 0, 1,    1, 0, 0, 0, 1,     1, 0, 0, 0, 1,     1, 0, 0, 0, 1,     1, 0, 0, 0, 1,     2, 1, 1, 1, 2 };
//for moving priority calculation
int step1();
int step2();
int step3();
//int step4();

int main(int argc, char * argv[])
{
	step1();
	waitKey(500);
	system("D:\\109HIWIN\\run_puz.bat");
	waitKey(1000);
	step2();
	waitKey(5000);
	step3();
	waitKey(500);
	system("D:\\109HIWIN\\run_puz.bat");
	waitKey(1000);
	parameter_a = -0.002723; parameter_b = 0.210838; parameter_c = -58.866506; parameter_d = 0.206785; parameter_e = 0.004971; parameter_f = 232.801208;
	parameter_c = parameter_c - 470.856;
	step2();
}

int step1(){
	//system("D://109HIWIN//run.bat");
	
	robot = Connect("192.168.0.3", 1, FuncName);

	ARM arm(robot);
	rs2::config cfg;
	cfg.enable_stream(RS2_STREAM_COLOR, 1920, 1080, RS2_FORMAT_BGR8, 10); // BGR888格式彩色影像 30fps
	rs2::pipeline pipe; // Declare RealSense pipeline, encapsulating the actual device and sensors
	pipe.start(cfg);

	arm.goThePos(puzzle1);//
	//waitKey(20);
	rs2::frameset frames = pipe.wait_for_frames();
	rs2::frame color_frame = frames.get_color_frame();

	Mat color_image(Size(1920, 1080), CV_8UC3, (void*)color_frame.get_data(), Mat::AUTO_STEP);

	imwrite("D:/109HIWIN/yolo/darknet-master_2/build/darknet/x64/Result.jpg", color_image);
	//imwrite("D:/109HIWIN/yolo/darknet-master/build/darknet/x64/Result0.jpg", color_image);
	//imshow("ok", color_image);
	waitKey(2);
	printf("saved");
	pipe.stop();
	destroyAllWindows();
	return EXIT_SUCCESS;
}

	/*


	
	robot = Connect("192.168.0.3", 1, FuncName);

	ARM arm(robot);
	rs2::config cfg;
	cfg.enable_stream(RS2_STREAM_COLOR, 1920, 1080, RS2_FORMAT_BGR8, 10); // BGR888格式彩色影像 30fps
	rs2::pipeline pipe; // Declare RealSense pipeline, encapsulating the actual device and sensors
	pipe.start(cfg);

	arm.goThePos(puzzle2);
	waitKey(20);
	rs2::frameset frames = pipe.wait_for_frames();
	rs2::frame color_frame = frames.get_color_frame();

	Mat color_image(Size(1920, 1080), CV_8UC3, (void*)color_frame.get_data(), Mat::AUTO_STEP);

	imwrite("D://109HIWIN//yolo//darknet-master//build//darknet//x64//Result.jpg", color_image);
	imshow("ok", color_image);
	waitKey(2);
	printf("saved");
	pipe.stop();
	destroyAllWindows();
	return EXIT_SUCCESS;
}
catch (const rs2::error & e)
{
	std::cerr << "RealSense error calling " << e.get_failed_function() << "(" << e.get_failed_args() << "):\n    " << e.what() << std::endl;
	return EXIT_FAILURE;
}
catch (const std::exception& e)
{
	std::cerr << e.what() << std::endl;
	return EXIT_FAILURE;
}*/





int step2() {
	robot = Connect("192.168.0.3", 1, FuncName);
	cout << "test" << endl;

	ARM arm(robot);
	Sucker sucker;
	sucker.close();
	arm.goThePos(prepare1);
	rs2::colorizer color_map; // Declare depth colorizer for pretty visualization
	char file[55] = { 0 };
	vector <Mat> imagetrain;
	Mat image;
	imagetrain.clear();
	vector < vector <KeyPoint>> keypoints_train(35, vector <KeyPoint>());
	vector <Mat> descriptor_train(35);
	Ptr<cv::xfeatures2d::SURF> Detector = cv::xfeatures2d::SURF::create(250);
	parameter_c = parameter_c + (100.211 + 86.03);
	vector < vector <double> > puzzle_place(35);
	//286.378 331.623 309.005
	//--64.971 -31.502 -48.2365
	adjust_x = -47.269 + 66.7 + 5;
	adjust_y = 325.275 - 314;
	puzzle_place[0] = { -66.0 + adjust_x,314.0 + adjust_y }; puzzle_place[1] = { -34.2 + adjust_x,314.0 + adjust_y }; puzzle_place[2] = { -1.3 + adjust_x,314.0 + adjust_y }; puzzle_place[3] = { 31.7 + adjust_x,314.0 + adjust_y }; puzzle_place[4] = { 63.5 + adjust_x,314.0 + adjust_y };
	puzzle_place[5] = { -66.0 + adjust_x,344.5 + adjust_y }; puzzle_place[6] = { -34.2 + adjust_x,344.5 + adjust_y }; puzzle_place[7] = { -1.3 + adjust_x,344.5 + adjust_y }; puzzle_place[8] = { 31.7 + adjust_x,344.5 + adjust_y }; puzzle_place[9] = { 63.5 + adjust_x,344.5 + adjust_y };
	puzzle_place[10] = { -66.0 + adjust_x,381.1 + adjust_y }; puzzle_place[11] = { -34.2 + adjust_x,381.1 + adjust_y }; puzzle_place[12] = { -1.3 + adjust_x,381.1 + adjust_y }; puzzle_place[13] = { 31.7 + adjust_x,381.1 + adjust_y }; puzzle_place[14] = { 63.5 + adjust_x,381.1 + adjust_y };
	puzzle_place[15] = { -66.0 + adjust_x,416.1 + adjust_y }; puzzle_place[16] = { -34.2 + adjust_x,416.1 + adjust_y }; puzzle_place[17] = { -1.3 + adjust_x,416.1 + adjust_y }; puzzle_place[18] = { 31.7 + adjust_x,416.1 + adjust_y }; puzzle_place[19] = { 63.5 + adjust_x,416.1 + adjust_y };
	puzzle_place[20] = { -66.0 + adjust_x,451.7 + adjust_y }; puzzle_place[21] = { -34.2 + adjust_x,451.7 + adjust_y }; puzzle_place[22] = { -1.3 + adjust_x,451.7 + adjust_y }; puzzle_place[23] = { 31.7 + adjust_x,451.7 + adjust_y }; puzzle_place[24] = { 63.5 + adjust_x,451.7 + adjust_y };
	puzzle_place[25] = { -66.0 + adjust_x,487.7 + adjust_y }; puzzle_place[26] = { -34.2 + adjust_x,487.7 + adjust_y }; puzzle_place[27] = { -1.3 + adjust_x,487.7 + adjust_y }; puzzle_place[28] = { 31.7 + adjust_x,487.7 + adjust_y }; puzzle_place[29] = { 63.5 + adjust_x,487.7 + adjust_y };
	puzzle_place[30] = { -66.0 + adjust_x,519.7 + adjust_y }; puzzle_place[31] = { -34.2 + adjust_x,522.8 + adjust_y }; puzzle_place[32] = { -1.3 + adjust_x,519.7 + adjust_y }; puzzle_place[33] = { 31.7 + adjust_x,522.8 + adjust_y }; puzzle_place[34] = { 63.5 + adjust_x,519.7 + adjust_y };
	char temp[10] = { 0 };
	double pu[6] = { puzzle_place[0][0],puzzle_place[0][1],table_distance_arm + 5,-180.0,0, 0 };//z cannot less than -56
	//arm.goThePos(pu);
	//system("pause");
	cout << "finish read train data" << endl;

	for (int i = 0; i < 35; i++) {
		sprintf_s(file, 55, "D://hiwin//color//%d.jpg", i + 1);
		image = cv::imread(file);
		imagetrain.push_back(image);
	}
	cout << "finish read train image" << endl;


	ifstream inf;
	inf.open("C://Users//isci//Desktop//1025film//puzzle-prediction.txt");
	string sline;//每一行
	string out;
	string s1, s2, s3, s4;
	int x, y, w, h;
	vector<Rect> bound;
	int matched_pieces = 0;
	while (getline(inf, sline))
	{
		istringstream sin(sline);
		sin >> s1 >> s2 >> s3 >> s4;
		x = atof(s1.c_str());	 // 加上 c_str() 把 string 轉成 float
		y = atof(s2.c_str());	 // 加上 c_str() 把 string 轉成 float
		w = atof(s3.c_str());	 // 加上 c_str() 把 string 轉成 float
		h = atof(s4.c_str());	 // 加上 c_str() 把 string 轉成 float



		if (x < 0)
			x = 0;
		else if (y < 0)
			y = 0;
		if ((x + w) > 1920) {
			w = 1920 - x;
			cout << "x over" << endl;
		}
		if ((y + h) > 1080) {
			h = 1080 - y;
			cout << "y over" << endl;
		}

		//	cout << x << " " << y << " " << w << " " << h << endl;
		Rect temp(x, y, w, h);
		cout << temp.tl() << "   " << temp.br() << endl;
		bound.push_back(temp);
		matched_pieces++;
	}
	//cout << "matched pieces :  " << matched_pieces << endl;
	vector < Mat> output(matched_pieces);
	vector <Point2f> certer_point(matched_pieces);
	Mat test_image, imageBlur, imageMask;
	test_image = imread("D:/109HIWIN/yolo/darknet-master_3/build/darknet/x64/Result.jpg");
	cout << "w= " << test_image.cols << " ; h= " << test_image.rows << endl;


	//GaussianBlur(test_image, imageBlur, Size(11, 11), 2);
	//imageMask = test_image - imageBlur;
	//test_image = test_image + imageMask;
	vector<Mat> imageRGB;
	split(test_image, imageRGB);
	//imageRGB[0] += 79;
	//imageRGB[1] += 82;
	//imageRGB[2] += 110;
	imageRGB[0] *= 1.61;
	imageRGB[1] *= 1.63;
	imageRGB[2] *= 1.99;
	merge(imageRGB, test_image);



	for (int i = 0; i < matched_pieces; i++) {
		output[i] = test_image(bound[i]);
		circle(output[i], Point(0.5*bound[i].width, 0.5*bound[i].height), 4, Scalar(255, 255, 136), -1);
		Point2f point_temp((bound[i].x + 0.5 * bound[i].width), (bound[i].y + 0.5 * bound[i].height));
		certer_point[i] = point_temp;

		//cv::resize(output[i],  output[i], cv::Size(output[i].cols * 2, output[i].rows * 2));



		//imshow("try", output[i]);
		//waitKey(2);
		//system("pause");
	}
	cout << "finish read test datas" << endl;

	cv::FileStorage store("D://hiwin//store.bin", cv::FileStorage::READ);
	cout << "open" << endl;
	//291.917 335.803  313.86
	//-54.971 -20.824 -37.8975
	for (int i = 0; i < 35; i++) {
		sprintf_s(temp, 10, "keypts%d", i + 1);
		cv::FileNode n1 = store[temp];
		cv::read(n1, keypoints_train[i]);

		sprintf_s(temp, 10, "descrip%d", i + 1);
		cv::FileNode n2 = store[temp];
		cv::read(n2, descriptor_train[i]);
		//cout << "read success : " << i + 1 << endl;
	}
	store.release();



	//system("PAUSE");
	int totalTrainDesc = 0;
	for (vector<Mat>::const_iterator tdIter = descriptor_train.begin(); tdIter != descriptor_train.end(); tdIter++)
		totalTrainDesc += tdIter->rows;

	cout << "; Total train descriptors count: " << totalTrainDesc << endl;
	cout << ">" << endl;
	Ptr<DescriptorMatcher> matcher = cv::DescriptorMatcher::create("FlannBased");
	vector<cv::DMatch> matches;

	matcher->add(descriptor_train);
	matcher->train();
	const auto window_name_test = "test Image";
	namedWindow(window_name_test, WINDOW_AUTOSIZE);
	const auto window_name_matched = "matched Image";
	namedWindow(window_name_matched, WINDOW_AUTOSIZE);

	const auto window_name_tmp = "tmp";
	namedWindow(window_name_tmp, WINDOW_AUTOSIZE);

	
	vector<int> pic_id;
	vector<float> angles;
	vector<Point2f> centerPt;//重排順序用

	waitKey(2000);
	for (int a = 0; a < matched_pieces; a++) {
		imshow(window_name_test, output[a]);
		waitKey(5);
		vector<KeyPoint> keypoints_test;
		Mat descriptor_test;
		Detector->detect(output[a], keypoints_test);
		Detector->compute(output[a], keypoints_test, descriptor_test);

		Mat outp;
		cv::drawKeypoints(output[a], keypoints_test, outp, cv::Scalar::all(-1), cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
		imshow(window_name_tmp, outp);

		Mat img_key_points_test;
		cout << "Query descriptors count: " << descriptor_test.rows << endl;

		matcher->match(descriptor_test, matches);
		cout << "Picture : " << a + 1 << endl << "number of matches: " << matches.size() << endl;
		double minDist = 10000;
		double maxDist = 0;
		vector<DMatch> goodmatches;
		//
		for (int i = 0; i < matches.size(); i++)
		{
			double dist = matches[i].distance;
			if (dist < minDist)
				minDist = dist;
			else if (dist > maxDist)
				maxDist = dist;
		}
		//cout << "min dist=" << minDist << endl;
		//cout << "max dist=" << maxDist << endl;
		for (int i = 0; i < matches.size(); i++)
		{
			double dist = matches[i].distance;
			if (dist <= 0.6 * maxDist) {
				goodmatches.push_back(matches[i]);
			}
		}
		cout << "goodmatches size : " << goodmatches.size() << endl;
		//scene = query; object = train
		vector < float > average_distance(35, 0);
		vector < int > count_number(35, 0);
		int matched_picture = 0;
		int matched_matches = 0;
		vector<DMatch> drawmatches;
		for (int index = 0; index < 35; index++) {
			for (size_t i = 0; i < goodmatches.size(); i++) {
				if (goodmatches[i].imgIdx == index) {
					average_distance[index] += goodmatches[i].distance;
					count_number[index] ++;
				}
			}
			if (count_number[index] < 1)
				average_distance[index] = 1;
			else
				average_distance[index] = average_distance[index] / count_number[index];
			//	cout << "for train number " << index + 1 << "  ; average_distance =   " << average_distance[index] << "  ; pieces = " << count_number[index] << endl;
			if (count_number[index] > matched_matches) {
				matched_picture = index;
				matched_matches = count_number[index];
			}
			average_distance[index] = 0;
			count_number[index] = 0;
		}
		matched_matches = 0;
		for (int i = 0; i < goodmatches.size(); i++)
		{
			if (goodmatches[i].imgIdx == matched_picture) {
				drawmatches.push_back(goodmatches[i]);
			}
		}
		Mat show;
		cout << "matched number :  " << matched_picture + 1 << endl;
		imshow(window_name_matched, imagetrain[matched_picture]);
		waitKey(3);


		//----------目標物體用矩形標識出來------------

		vector<Point2f> obj;
		vector<Point2f> scene;
		int coo = 0;
		for (int i = 0; i < matches.size(); i++) {
			if (matches[i].imgIdx == matched_picture) {
				obj.push_back(keypoints_test[matches[i].queryIdx].pt);
				scene.push_back(keypoints_train[matched_picture][matches[i].trainIdx].pt);
				coo++;
			}
			//	cout << "number" << i << "  ,imgIdx=  " << goodmatches[i].imgIdx << endl;
		}
		cout << "matched points : " << coo << endl;
		//matches
		//生成透視矩陣
		vector <double> pos(2);
		vector <double> move(2);
		double first_rotate = 0.0, second_rotate = 0.0;
		if (coo > 8) {
			Mat H = findHomography(obj, scene, RANSAC);
			//cout << H << endl;
			float theta = -atan2(H.at<double>(0, 1), H.at<double>(0, 0)) * 180 / 3.14159;
			cout << "theta =  " << theta << endl << "center at " << certer_point[a] << endl;


			pic_id.push_back(matched_picture);
			angles.push_back(theta);
			centerPt.push_back(certer_point[a]);

		}
		else
			cout << "not enough matched points" << endl;

		drawmatches.clear();
		goodmatches.clear();
		matched_picture = 0;
		keypoints_test.clear();
	}
		/*
		vector<int> inMatched;
		vector<int> pic_id;
		vector<float> angles;
		vector<Point2f> centerPt;
*/

		vector<int> movQueue;
		//int pri[35] = { 2, 1, 1, 1, 2,    1, 0, 0, 0, 1,    1, 0, 0, 0, 1,     1, 0, 0, 0, 1,     1, 0, 0, 0, 1,     1, 0, 0, 0, 1,     2, 1, 1, 1, 2 };
		int max_pri = -1;
		int max_pri_id = -1;

		while (movQueue.size() < pic_id.size()) {
			for (int i = 0; i < pic_id.size(); i++) {

				if (max_pri_id == -1 || pri[pic_id[i]] > max_pri) {
					max_pri_id = pic_id[i];
					max_pri = pri[pic_id[i]];

				}
			}



			int j = max_pri_id;

			int a = j - 1;
			int b = j + 1;
			int c = j - 5;
			int d = j + 5;

			if ((j-1 + 1) % 5 != 0) pri[a]++;
			if ((j-1 - 1) % 5 != 0) pri[b]++;
			if (c >= 0) pri[c]++;
			if (d < 35) pri[d]++;
			printf("> %d %d\n", j, pri[j]);
			pri[max_pri_id] = -10000;

			movQueue.push_back(j);
			
			max_pri = -1;
			max_pri_id = -1;


		}






	for(int i = 0; i < movQueue.size(); i++){
		vector <double> pos(2);
		vector <double> move(2);
		double first_rotate = 0.0, second_rotate = 0.0;
		float theta;
		int matched_picture;
		Point2f centerPoint;
		for (int j = 0; j < pic_id.size(); j++) {
			if (pic_id[j] == movQueue[i]) {
				theta = angles[j];
				centerPoint = centerPt[j];
				matched_picture = pic_id[j];

			}
		}

		cout << "puz id: " << matched_picture << "center @" << centerPoint << endl;


		if (theta > 180) {
			theta = theta - 360;
		}
		else if (theta < -180) {
			theta = theta + 360;
		}
		//	system("pause");
		if (theta <= 0) {
			first_rotate = 0.0;
			second_rotate = -theta;
			cout << "first_rotate = " << first_rotate << " ;  second_rotate =  " << second_rotate << endl;
		}
		else {
			first_rotate = theta;
			second_rotate = 0;
			cout << "first_rotate = " << first_rotate << " ;   second_rotate =  " << second_rotate << endl;
		}
		pos[0] = (parameter_a * centerPoint.x + parameter_b * centerPoint.y + parameter_c);
		pos[1] = (parameter_d * centerPoint.x + parameter_e * centerPoint.y + parameter_f);
		double p0[6] = { pos[0] , pos[1] , table_distance_arm + 5 , -180.0 , 0 , first_rotate };//z cannot less than -56
		arm.setPosXY(pos[0], pos[1]);
		arm.goThePos(p0);
		//system("pause");
		sucker.open();
		arm.setPosZ(table_distance_arm - 7);
		arm.setPosZ(table_distance_arm + 10);
		int doMove = 0;
		for (int ii = 0; ii < 35; ii++)
		{
			if (ii == matched_picture) {
				pos = puzzle_place[ii];
				if (ii == 0) {
					move[0] = puzzle_place[ii][0] - 2;
					move[1] = puzzle_place[ii][1] - 2;
					doMove++;
				}
				else if (ii < 4) {
					move[0] = puzzle_place[ii][0];
					move[1] = puzzle_place[ii][1] - 2;
					doMove++;
				}
				else if (ii == 4) {
					move[0] = puzzle_place[ii][0] + 2;
					move[1] = puzzle_place[ii][1] - 2;
					doMove++;
				}
				else if (ii == 34) {
					move[0] = puzzle_place[ii][0] + 2;
					move[1] = puzzle_place[ii][1] + 2;
					doMove++;
				}
				else if (ii > 30) {
					move[0] = puzzle_place[ii][0];
					move[1] = puzzle_place[ii][1] + 2;
					doMove++;
				}
				else if (ii == 30) {
					move[0] = puzzle_place[ii][0] - 2;
					move[1] = puzzle_place[ii][1] + 2;
					doMove++;
				}
				else if ((ii / 5) == 0) {
					move[0] = puzzle_place[ii][0] + 2;
					move[1] = puzzle_place[ii][1];
					doMove++;
				}
				else if ((ii / 5) == 4) {
					move[0] = puzzle_place[ii][0] + 2;
					move[1] = puzzle_place[ii][1];
					doMove++;
				}
				else {
					move[0] = puzzle_place[ii][0];
					move[1] = puzzle_place[ii][1];
					doMove++;
				}
			}
		}
		arm.setPosXY(pos[0], pos[1]);
		double p2[6] = { pos[0],pos[1],table_distance_arm + 5,-180.0,0, second_rotate };//z cannot less than -56
		arm.goThePos(p2);
		arm.setPosZ(table_distance_arm - 5);
		p2[2] = table_distance_arm - 5;
		sucker.close();
		p2[0] = pos[0] + 2; p2[1] = pos[1] + 2; arm.goThePos(p2);
		p2[0] = pos[0] - 2; p2[1] = pos[1] - 2; arm.goThePos(p2);
		p2[0] = pos[0] + 2; p2[1] = pos[1] - 2; arm.goThePos(p2);
		p2[0] = pos[0] - 2; p2[1] = pos[1] + 2; arm.goThePos(p2);

		if (doMove > 0) {
			double p3[6] = { move[0],move[1],table_distance_arm - 5,-180.0,0, second_rotate };//z cannot less than -56
			arm.goThePos(p3);
		}
		arm.setPosZ(table_distance_arm + 10);
		arm.goThePos(prepare2);
	}
	
		//drawmatches.clear();
		//goodmatches.clear();
		//matched_picture = 0;
		//keypoints_test.clear();
		//system("pause");
	
	system("pause");
	return 0;
}

int step3() {
	//system("D://109HIWIN//run.bat");

	robot = Connect("192.168.0.3", 1, FuncName);

	ARM arm(robot);
	rs2::config cfg;
	cfg.enable_stream(RS2_STREAM_COLOR, 1920, 1080, RS2_FORMAT_BGR8, 10); // BGR888格式彩色影像 30fps
	rs2::pipeline pipe; // Declare RealSense pipeline, encapsulating the actual device and sensors
	pipe.start(cfg);

	arm.goThePos(puzzle2);//
	//waitKey(20);
	rs2::frameset frames = pipe.wait_for_frames();
	rs2::frame color_frame = frames.get_color_frame();

	Mat color_image(Size(1920, 1080), CV_8UC3, (void*)color_frame.get_data(), Mat::AUTO_STEP);

	imwrite("D:/109HIWIN/yolo/darknet-master_3/build/darknet/x64/Result.jpg", color_image);
	//imwrite("D:/109HIWIN/yolo/darknet-master/build/darknet/x64/Result0.jpg", color_image);
	//imshow("ok", color_image);
	waitKey(2);
	printf("saved");
	pipe.stop();
	destroyAllWindows();
	return EXIT_SUCCESS;
}