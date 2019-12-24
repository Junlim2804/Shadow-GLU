#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>

#pragma comment (lib, "OpenGL32.lib")
#pragma comment (lib, "GLU32.lib")

#define WINDOW_TITLE "OpenGL Window"
int displaykey = 1;
float r = 0.0;
int on = 1;
float amb[] = { 1.0,1.0,1.0 };
float pos[] = { 0.0,1.0,0.0 };
float dif[] = { 1.0,1.0,1.0 };
float x=0, y=0.8, z=0.0;
float posD[] = { 0.0,0.0,0.0 };
float ambM[] = { 1.0,1.0,1.0 };
LRESULT WINAPI WindowProcedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE) PostQuitMessage(0);
		if (wParam == 'W') y +=0.1;
		if (wParam == 'S') y -= 0.1;
		if (wParam == 'A') x -= 0.1;
		if (wParam == 'D') x += 0.1;
		if (wParam == 'Q') z -= 0.1;
		if (wParam == 'E') z += 0.1;
		if (wParam == 'O') displaykey=1;
		if (wParam == 'P') displaykey=2;
		if (wParam == ' ')
		{
			if (on == 1)
				on = 0;
			else
				on = 1;
		}
		if (wParam == VK_UP) r += 1;
		if (wParam == VK_DOWN) r -= 1;
		break;

	default:
		break;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}
//--------------------------------------------------------------------

bool initPixelFormat(HDC hdc)
{
	PIXELFORMATDESCRIPTOR pfd;
	ZeroMemory(&pfd, sizeof(PIXELFORMATDESCRIPTOR));

	pfd.cAlphaBits = 8;
	pfd.cColorBits = 32;
	pfd.cDepthBits = 24;
	pfd.cStencilBits = 0;

	pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;

	pfd.iLayerType = PFD_MAIN_PLANE;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;

	// choose pixel format returns the number most similar pixel format available
	int n = ChoosePixelFormat(hdc, &pfd);

	// set pixel format returns whether it sucessfully set the pixel format
	if (SetPixelFormat(hdc, n, &pfd))
	{
		return true;
	}
	else
	{
		return false;
	}
}
//--------------------------------------------------------------------
void shadow()
{
	GLfloat matrix[16] =
	{
		y,-x,0,0,
		0,0,0,0,
		0,-z,y,0,
		0,-1,0,y
	};

	glDisable(GL_LIGHTING);
	
	
	glPushMatrix();
	glTranslatef(0.0, 1.25, 0.0);
	glMultMatrixf(matrix);
	glColor3f(0.0f, 0.0f, 0.0f);
	glTranslatef(0.0,0.5, 0.0);
	GLUquadricObj* sphere = NULL;
	sphere = gluNewQuadric();
	gluSphere(sphere, 0.2, 30, 30);
	gluDeleteQuadric(sphere);
	glPopMatrix();
}
void drawPyradmid(float s)
{
	glBegin(GL_POLYGON);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0, s, 0.0);
	glVertex3f(s, s, 0);
	glVertex3f(s, 0, 0);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(0, 0, 0);
	glVertex3f(0, s, 0);
	glVertex3f(s / 2, s / 2, s / 2);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(0, 0, 0);
	glVertex3f(s, 0, 0);
	glVertex3f(s / 2, s / 2, s / 2);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(s, 0, 0);
	glVertex3f(s, s, 0);
	glVertex3f(s / 2, s / 2, s / 2);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(s, s, 0);
	glVertex3f(0, s, 0);
	glVertex3f(s / 2, s / 2, s / 2);
	glEnd();




}
void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glClearColor(0, 0, 1, 1);
	if (on == 1)
	{
		glEnable(GL_LIGHTING);
		posD[0] = x;
		posD[1] = y;
		posD[2] = z;
		//glLightfv(GL_LIGHT0, GL_AMBIENT, amb);
		//glLightfv(GL_LIGHT0, GL_POSITION, pos);
		//glEnable(GL_LIGHT0);


		
		glLightfv(GL_LIGHT1, GL_DIFFUSE, dif);
		glLightfv(GL_LIGHT1, GL_POSITION, posD);
		glEnable(GL_LIGHT1);
	}
	else
		glDisable(GL_LIGHTING);
	//glColor3f(1, 0, 0);
	glLoadIdentity();
	glRotatef(r, 1, 1, 1);
	glMaterialfv(GL_FRONT,GL_DIFFUSE,ambM);
	if (displaykey == 1)
	{
		glPushMatrix();
		glColor3f(1, 1, 0);
		glTranslatef(x, y, z);
		GLUquadricObj* sphere = NULL;
		sphere = gluNewQuadric();
		gluSphere(sphere, 0.05, 30, 30);
		gluDeleteQuadric(sphere);
		glPopMatrix();
	
		glPushMatrix();
		glTranslatef(0.0, 0.5, 0.0);
		
		sphere = gluNewQuadric();
		gluSphere(sphere, 0.2, 30, 30);
		gluDeleteQuadric(sphere);
		glPopMatrix();
		glColor3f(1, 1, 1);
		glBegin(GL_QUADS);
		//front
		glVertex3f(2, 0, -1);
		glVertex3f(2, -0.1, -1);
		glVertex3f(-2, -0.1, -1);
		glVertex3f(-2, 0, -1);	//back

		glVertex3f(2, 0, 1);
		glVertex3f(2, -0.1, 1);
		//glTexCoord2d(0.0, 1.0);
		glVertex3f(-2, -0.1, 1);
		//glTexCoord2d(0.0, 0.0);
		glVertex3f(-2, 0, 1);
		//top	


		//glTexCoord2d(1.0, 0.0);
		glVertex3f(2, 0, 1);
		//glTexCoord2d(0.0, 0.0);
		glVertex3f(2, 0, -1);
		//glTexCoord2d(0.0, 1.0);
		glVertex3f(-2, 0, -1);

		glVertex3f(-2, 0, 1);

		//base
		//glTexCoord2d(1.0, 0.0);
		glVertex3f(2, -0.1, 1);
		//glTexCoord2d(0.0, 0.0);
		glVertex3f(2, -0.1, -1);
		//glTexCoord2d(0.0, 1.0);
		glVertex3f(-2, -0.1, -1);

		glVertex3f(-2, -0.1, 1);

		//left

		glVertex3f(-2, -0.1,1);
		//glTexCoord2d(1.0, 0.0);
		glVertex3f(-2, -0.1,-1);
		//glTexCoord2d(0.0, 0.0);
		glVertex3f(-2, 0, -1);
		//glTexCoord2d(0.0, 1.0);
		glVertex3f(-2, 0, 1);

		//right

		glVertex3f(2, -0.1, 1);
		//glTexCoord2d(1.0, 0.0);
		glVertex3f(2, -0.1, -1);
		//glTexCoord2d(0.0, 0.0);
		glVertex3f(2, 0, 1);
		//glTexCoord2d(0.0, 1.0);
		glVertex3f(2, 0, -1);

		glEnd();
	}
	else if (displaykey == 2)
		drawPyradmid(1);
	if(on==1)
		shadow();


}
//--------------------------------------------------------------------

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int nCmdShow)
{
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.hInstance = GetModuleHandle(NULL);
	wc.lpfnWndProc = WindowProcedure;
	wc.lpszClassName = WINDOW_TITLE;
	wc.style = CS_HREDRAW | CS_VREDRAW;

	if (!RegisterClassEx(&wc)) return false;

	HWND hWnd = CreateWindow(WINDOW_TITLE, WINDOW_TITLE, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,
		NULL, NULL, wc.hInstance, NULL);

	//--------------------------------
	//	Initialize window for OpenGL
	//--------------------------------

	HDC hdc = GetDC(hWnd);

	//	initialize pixel format for the window
	initPixelFormat(hdc);

	//	get an openGL context
	HGLRC hglrc = wglCreateContext(hdc);

	//	make context current
	if (!wglMakeCurrent(hdc, hglrc)) return false;

	//--------------------------------
	//	End initialization
	//--------------------------------

	ShowWindow(hWnd, nCmdShow);

	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		display();

		SwapBuffers(hdc);
	}

	UnregisterClass(WINDOW_TITLE, wc.hInstance);

	return true;
}
//--------------------------------------------------------------------

