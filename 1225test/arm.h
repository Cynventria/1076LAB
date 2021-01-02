#pragma once
#include "HRSDK.h"
#include <iostream>
#include <Windows.h>
//#include "gripper.h"

using namespace std;

class ARM
{
private:
	//class robot declare
	HROBOT robot;

	//class parameter
	int overrideRatio = 70;	 //1-100% //25-35
	int ptpSpeed = 45;  //1-100% //25-35
	int linSpeed = 450;  //1-2000 mm/s //700
	int AccelerationRatio = 40; //1-100% //25-35



public:
	//pos coordinate
	const double pos_home[6] = { 0, 286.429, 282.85, 180, 0, 90 };

	//axis coordinate

	//現有函數
	ARM(HROBOT r); //初始化
	void goThePos(double* pos);
	void goThePos(const double* pos);
	void lineGoThePos(const double* pos);
	void lineGoThePosRel(const double* pos);
	void goTheAxis(double* pos);
	void goTheAxis(const double* pos);
	void getNowPos(double* pos);
	void getNowAxis(double* axis);
	void goHome();
	void setSpeed(int speed);//1~100
	void setptpSpeed(int ptpspeed);
	void setPosX(double x);
	void setPosY(double y);
	void setPosXY(double x, double y);
	void setPosZ(double z);
	void setPosRX(double rx);
	void setAxisJ1(double j1);
	void setAxisJ2(double j2);
	void setAxisJ3J5(double j3, double j5);
	void setAxisJ2J3J5(double j2, double j3, double j5);
	void setAxisJ5(double j5);
	void setAxisJ6(double j6);
	void cup_300ml();
	//現有函數

	void errorCheck();


	void goCheakPos();
	void goCatch();



	void goArticle1();
	void goArticle2();
	void goArticle3();
	void goPhotoPos();
	void goPhotoPlace();
	void goTest();
	void goPhotoPos(int num);
	void goPlanePhotoPos();
	void goSolidPhotoPos();
	void goMiddelePos();
	void goOriginalPos();
	void goBlockUp(double x, double y, double angle);

	void goDown();
	void goDownDown();
	void goUp();
	void goUpUp();
	void goBigUp();
	void goMoveXY(double x, double y);
	void goHeadStright();
	void goHeadModeZero();
	void goHeadModeOne();
	void goSolidPos(double x, double y, double angle, int num);
	//double* getnowpos();
	void turnOverOnBox();
	void turnOverAboveBox();
	void goOnBox();
	void goAboveBox();
	void goOnBoxWithAngle(double angle);
	void goSmallAboveBoxWithAngle(double angle);

	void gripperOpen();
	void gripperOpenLarge();
	void gripperClose();

};