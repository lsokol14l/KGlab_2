#include "Decomposition.h"
#include <random>
#include <gl/GL.h>

// призма на 30
void Squads(std::mt19937& gen, std::uniform_real_distribution<double>& r)// SQUADS
{
	glBegin(GL_QUADS);
	Point A = { 1. / 2, 0 ,0 };
	Point A_t = { 1. / 2, 0 ,1 };

	Point B = { 4, 1. / 2,0 };
	Point B_t = { 4, 1. / 2,1 };

	Point C = { 3. / 2, 2, 0 };
	Point C_t = { 3. / 2, 2, 1 };

	Point D = { 0, 1. / 2 ,0 };
	Point D_t = { 0, 1. / 2 ,1 };

	Point E = { -3, 2 ,0 };
	Point E_t = { -3, 2 ,1 };

	Point F = { -9. / 2, 0 ,0 };
	Point F_t = { -9. / 2, 0 ,1 };

	Point G = { -1. / 2, -9. / 2 ,0 };
	Point G_t = { -1. / 2, -9. / 2 ,1 };

	Point H = { 2, -7. / 2 ,0 };
	Point H_t = { 2, -7. / 2 ,1 };

	Point N = { 0 };

	// стена
	WriteNormal(A, A_t, B_t, B);
	WriteSquare(A, A_t, B_t, B, gen, r);
	
	WriteNormal(B, B_t, C_t, C);
	WriteSquare(B, B_t, C_t, C, gen, r);
	
	WriteNormal(C, C_t, D_t, D);
	WriteSquare(C, C_t, D_t, D, gen, r);
	
	WriteNormal(D, D_t, E_t, E);
	WriteSquare(D, D_t, E_t, E, gen, r);
	
	WriteNormal(E, E_t, F_t, F);
	WriteSquare(E, E_t, F_t, F, gen, r);
	
	WriteNormal(F, F_t, G_t, G);
	WriteSquare(F, F_t, G_t, G, gen, r);
	
	WriteNormal(G, G_t, H_t, H);
	WriteSquare(G, G_t, H_t, H, gen, r);
	
	WriteNormal(H, H_t, A_t, A);
	WriteSquare(H, H_t, A_t, A, gen, r);

	//// пол
	WriteNormal(A, B, C, D);
	WriteSquare(A, B, C, D, gen, r);

	WriteNormal(D, G, H, A);
	WriteSquare(D, G, H, A, gen, r);
	// на 50
	//WriteSquare(D, E, H, A, gen, r);
	WriteNormal(D, E, F, G);
	WriteSquare(D, E, F, G, gen, r);

	// потолок

	WriteNormal(D_t, C_t, B_t, A_t);
	glColor4d(1, 1, 0, 0.7);
	// вместо WriteSquare(A_t, B_t, C_t, D_t, gen, r);
	glVertex3dv(A_t.p());
	glVertex3dv(B_t.p());
	glVertex3dv(C_t.p());
	glVertex3dv(D_t.p());
	// на 50
	//WriteSquare(D_t, E_t, H_t, A_t, gen, r);

	WriteNormal(G_t, F_t, E_t, D_t);

	// Вместо WriteSquare(D_t, E_t, F_t, G_t, gen, r);
	glVertex3dv(D_t.p());
	glVertex3dv(E_t.p());
	glVertex3dv(F_t.p());
	glVertex3dv(G_t.p());

	WriteNormal(D_t, A_t, H_t, G_t);

	// Вместо WriteSquare(D_t, G_t, H_t, A_t, gen, r);
	glVertex3dv(G_t.p());
	glVertex3dv(H_t.p());
	glVertex3dv(A_t.p());
	glVertex3dv(D_t.p());

	glEnd();
}

void WriteSquare(Point A, Point B, Point C, Point D, std::mt19937& gen, std::uniform_real_distribution<double>& r) {
	glColor3d(r(gen), r(gen), r(gen));
	glVertex3dv(A.p());
	glVertex3dv(B.p());
	glVertex3dv(C.p());
	glVertex3dv(D.p());
};

void WriteNormal(Point A, Point B, Point C, Point D) {
	Point N = getNormalSquare(A, B, C, D);
	glNormal3dv(N.p());
	//displayNormalSquare(A, B, C, D, N);
}

void displayNormal(Point A, Point B, Point C, Point N) {
	//Для проверки нарисуем вектор нормали.
	//Так как вектор - это просто направление,
	//для рисования его нужно приложить к какой-то точке.
	//Пусть вектор рисуется из центра полигона.
	//Вычисляем центр
	Point center{ (A.x + B.x + C.x) / 3.0,
	(A.y + B.y + C.y) / 3.0,
	(A.z + B.z + C.z) / 3.0 };
	//тут вектор нормали будет заканчиватся.
	Point N_end{ center.x + N.x,
	center.y + N.y,
	center.z + N.z };
	//рисуем вектор нормали
	//запоминаем, включено ли освещение
	//чтобы восстановить его, если это нужно.
	bool b_light = glIsEnabled(GL_LIGHTING);
	//отключаем освещение, чтобы раскрасить вектор привычным нам glColor
	if (b_light)
		glDisable(GL_LIGHTING);
	glBegin(GL_LINES);
	glColor3d(1, 0, 0);
	glVertex3dv((double*)&center);
	glVertex3dv((double*)&N_end);
	glEnd();
	//восстанавливаем освещение, если нужно.
	if (b_light)
		glEnable(GL_LIGHTING);
}

Point getNormal(Point A, Point B, Point C) {
	//вычисляем стороны-вектора
	Point BA1{ A.x - B.x,A.y - B.y,A.z - B.z };
	Point BC1{ C.x - B.x,C.y - B.y,C.z - B.z };
	Point N1{ BA1.y * BC1.z - BA1.z * BC1.y, -BA1.x * BC1.z + BA1.z * BC1.x, BA1.x * BC1.y - BA1.y * BC1.x };
	//Нормализуем нормаль
	double l1 = sqrt(N1.x * N1.x + N1.y * N1.y + N1.z * N1.z);
	N1.x /= l1;
	N1.y /= l1;
	N1.z /= l1;


	return N1;
}

Point getNormalSquare(Point A, Point B, Point C, Point D) {
	// Вычисляем нормали для двух треугольников
	Point N1 = getNormal(A, B, C);
	Point N2 = getNormal(A, C, D);

	// Усредняем нормали
	Point N{
		(N1.x + N2.x) / 2.0,
		(N1.y + N2.y) / 2.0,
		(N1.z + N2.z) / 2.0
	};

	// Нормализуем усреднённую нормаль
	double length = sqrt(N.x * N.x + N.y * N.y + N.z * N.z);
	N.x /= length;
	N.y /= length;
	N.z /= length;

	return N;
}

void displayNormalSquare(Point A, Point B, Point C, Point D, Point N) {
	// Вычисляем центр четырёхугольника
	Point center{
		(A.x + B.x + C.x + D.x) / 4.0,
		(A.y + B.y + C.y + D.y) / 4.0,
		(A.z + B.z + C.z + D.z) / 4.0
	};

	// Конечная точка нормали
	Point N_end{
		center.x + N.x,
		center.y + N.y,
		center.z + N.z
	};

	// Рисуем вектор нормали
	bool b_light = glIsEnabled(GL_LIGHTING);
	if (b_light)
		glDisable(GL_LIGHTING);
	glBegin(GL_LINES);
	glColor3d(1, 0, 0);
	glVertex3dv(center.p());
	glVertex3dv(N_end.p());
	glEnd();
	if (b_light)
		glEnable(GL_LIGHTING);
}