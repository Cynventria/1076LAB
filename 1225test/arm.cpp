#include "arm.h"



ARM::ARM(HROBOT r)
{

	this->robot = r;

	if (robot == -1)
	{
		cout << "robot connect error" << endl;
	}
	else
	{
		cout << "robot connect" << endl;
		speed_limit_off(robot);
		set_motor_state(robot, 1);
	}


	set_override_ratio(robot, overrideRatio);
	Sleep(100);

	set_lin_speed(robot, linSpeed);
	Sleep(100);

	set_acc_dec_ratio(robot, AccelerationRatio);
	Sleep(100);

	set_ptp_speed(robot, ptpSpeed);
	Sleep(100);


}

void ARM::goThePos(double pos[6]) {
	ptp_pos(robot, 0, pos);
	while (1) {
		if (get_motion_state(robot) == 1)
			break;
	}
	Sleep(100);
}
void ARM::goThePos(const double pos[6]) {
	double new_pos[6];
	for (int i = 0; i < 6; i++)
		new_pos[i] = pos[i];

	ptp_pos(robot, 0, new_pos);
	while (1) {
		if (get_motion_state(robot) == 1)
			break;
	}
	Sleep(100);
}
void ARM::lineGoThePos(const double pos[6]) {
	double new_pos[6];
	for (int i = 0; i < 6; i++)
		new_pos[i] = pos[i];
	lin_pos(robot, 1, 80, new_pos);
	while (1) {
		if (get_motion_state(robot) == 1)
			break;
	}
	Sleep(100);
}
void ARM::lineGoThePosRel(const double pos[6]) {
	double new_pos[6];
	for (int i = 0; i < 6; i++)
		new_pos[i] = pos[i];
	lin_rel_pos(robot, 1, 80, new_pos);
	while (1) {
		if (get_motion_state(robot) == 1)
			break;
	}
	Sleep(100);
}
void ARM::goTheAxis(double pos[6]) {
	ptp_axis(robot, 1, pos);
	while (1) {
		if (get_motion_state(robot) == 1)
			break;
	}
	Sleep(100);
}
void ARM::goTheAxis(const double pos[6]) {
	double new_pos[6];
	for (int i = 0; i < 6; i++)
		new_pos[i] = pos[i];
	ptp_axis(robot, 1, new_pos);
	while (1) {
		if (get_motion_state(robot) == 1)
			break;
	}
	Sleep(100);
}
void ARM::getNowPos(double pos[6]) {
	get_current_position(robot, pos);
}

void ARM::goHome() {
	double home_axis[6] = { 0.0,13.896,-14.014,0.0,-89.881,0.0 };//¤W»ÈHOME
	ptp_axis(robot, 0, home_axis);
	while (1) {
		if (get_motion_state(robot) == 1)
			break;
	}
	Sleep(100);
}

void ARM::setSpeed(int speed) {
	overrideRatio = speed;
	set_override_ratio(robot, overrideRatio);
	Sleep(100);
}
void ARM::setPosX(double x) {
	double pos[6];
	get_current_position(robot, pos);
	pos[0] = x;
	ptp_pos(robot, 1, pos);
	while (1) {
		if (get_motion_state(robot) == 1)
			break;
	}
	Sleep(100);
}
void ARM::setPosY(double y) {
	double pos[6];
	get_current_position(robot, pos);
	pos[1] = y;
	ptp_pos(robot, 1, pos);
	while (1) {
		if (get_motion_state(robot) == 1)
			break;
	}
	Sleep(100);
}
void ARM::setPosXY(double x, double y) {
	double pos[6];
	get_current_position(robot, pos);
	pos[0] = x;
	pos[1] = y;
	ptp_pos(robot, 1, pos);
	while (1) {
		if (get_motion_state(robot) == 1)
			break;
	}
	Sleep(100);
}
void ARM::setPosRX(double rx) {
	double pos[6];
	get_current_position(robot, pos);
	pos[4] = rx;
	ptp_pos(robot, 1, pos);
	while (1) {
		if (get_motion_state(robot) == 1)
			break;
	}
	Sleep(100);
}
void ARM::setptpSpeed(int ptpspeed) {
	ptpSpeed = ptpspeed;
	set_ptp_speed(robot, ptpSpeed);
	Sleep(100);
}
void ARM::setPosZ(double z) {
	double pos[6];
	get_current_position(robot, pos);
	pos[2] = z;
	lin_pos(robot, 0, 0, pos);
	//ptp_pos(robot, 1, pos);
	while (1) {
		if (get_motion_state(robot) == 1)
			break;
	}
	Sleep(100);
}
void ARM::setAxisJ2(double j2) {
	double axis[6];
	get_current_joint(robot, axis);
	axis[1] = j2;
	ptp_axis(robot, 1, axis);
	while (1) {
		if (get_motion_state(robot) == 1)
			break;
	}
	Sleep(100);
}
void ARM::setAxisJ5(double j5) {
	double axis[6];
	get_current_joint(robot, axis);
	axis[4] = j5;
	ptp_axis(robot, 1, axis);
	while (1) {
		if (get_motion_state(robot) == 1)
			break;
	}
	Sleep(100);
}
void ARM::setAxisJ1(double j1) {
	double axis[6];
	get_current_joint(robot, axis);
	axis[0] = j1;
	ptp_axis(robot, 1, axis);
	while (1) {
		if (get_motion_state(robot) == 1)
			break;
	}
	Sleep(100);
}
void ARM::setAxisJ3J5(double j3, double j5) {
	double axis[6];
	get_current_joint(robot, axis);
	axis[2] = j3;
	axis[4] = j5;
	ptp_axis(robot, 1, axis);
	while (1) {
		if (get_motion_state(robot) == 1)
			break;
	}
	//Sleep(100);
}
void ARM::setAxisJ2J3J5(double j2, double j3, double j5) {
	double axis[6];
	get_current_joint(robot, axis);
	axis[1] = j2;
	axis[2] = j3;
	axis[4] = j5;
	ptp_axis(robot, 1, axis);
	while (1) {
		if (get_motion_state(robot) == 1)
			break;
	}
	//Sleep(100);
}
void ARM::cup_300ml() {
	double pos_step1[6] = { 0.0,512.245,91.830,180.0,-24.482,90.0 };
	goThePos(pos_step1);
	Sleep(1000);
	double axis_step1[6] = { 0.0,-16.225,-34.805,-0.061,13.318,0.042 };
	goTheAxis(axis_step1);
	Sleep(2000);

	//22.818
	//setAxisJ5(22.818);
	double axis[6] = { 0.0,-15.577,-38.777,-0.051,27.159,0.032 };
	goTheAxis(axis);
	Sleep(8000);
	//double axis[6] = {0.00,-19.365,-45.566,-0.061,51.054,0.042};
	//goTheAxis(axis);
	//Sleep(1000);
	//goThePos(pos);
}
void ARM::getNowAxis(double* axis) {
	get_current_joint(robot, axis);
}
void ARM::setAxisJ6(double j6) {
	double axis[6];
	get_current_joint(robot, axis);
	axis[5] = j6;
	ptp_axis(robot, 1, axis);
	while (1) {
		if (get_motion_state(robot) == 1)
			break;
	}
	Sleep(100);
}