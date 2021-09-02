#pragma once
#include "ourBetterGraphics_eyy_.h"

LRESULT CALLBACK WindowProc(HWND window_handle, unsigned int message, WPARAM w_param, LPARAM l_param)
{
	LRESULT result = 0;
	switch (message)
	{
	case WM_DESTROY:
	case WM_QUIT:
	{
		globalRunning = false;
	}
	break;
	default:
		result = DefWindowProc(window_handle, message, w_param, l_param);
	}

	return result;
}

int CALLBACK WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nShowCmd)
{
#pragma region Initializer
	WNDCLASS wndclass = {};
	wndclass.style = CS_OWNDC | CS_VREDRAW | CS_HREDRAW;
	wndclass.lpfnWndProc = WindowProc;
	wndclass.hInstance = hInstance;
	wndclass.lpszMenuName = L"HelloThere";
	wndclass.lpszClassName = L"ButGoodbye";

	globalBuffer.width = 1280;
	globalBuffer.height = 720;

	globalBuffer.info.bmiHeader = {};
	globalBuffer.info.bmiHeader.biSize = sizeof(globalBuffer.info.bmiHeader);
	globalBuffer.info.bmiHeader.biWidth = globalBuffer.width;
	globalBuffer.info.bmiHeader.biHeight = -globalBuffer.height;
	globalBuffer.info.bmiHeader.biPlanes = 1;
	globalBuffer.info.bmiHeader.biBitCount = 32;
	globalBuffer.info.bmiHeader.biCompression = BI_RGB;

	globalBuffer.memory = VirtualAlloc(0, globalBuffer.width * globalBuffer.height * 4, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

	if (RegisterClass(&wndclass))
	{
		HWND window_handle = CreateWindowEx(0, wndclass.lpszClassName, L"HelloThere", WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, 
								CW_USEDEFAULT, globalBuffer.width, globalBuffer.height,
								0, 0, hInstance, 0);
		if (window_handle)
		{
			globalRunning = true;
			MSG message;
			HDC deviceContext = GetDC(window_handle);

#pragma endregion			
			int frameCounter = 0;

			Controller controller;
			unsigned deltatime;
			
			//DayLight Cycle
			float ghadi = 0;
			Color blue(116, 176, 213, 0xff), black(0, 0, 0, 0xff), red(225, 152, 88, 0xff);
			float blueInt=5.0f, blackInt=1.0f, moonInt=2.5f;
			Color screenColor(0, 0, 0, 0xff);

			auto lastframe = std::chrono::high_resolution_clock::now();
			Shape3D s;
#pragma region Loop

			while (globalRunning)
			{
				deltatime = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - lastframe).count();
				lastframe = std::chrono::high_resolution_clock::now();
				consoleLogSpace(1e6 / deltatime);
				controller.reset();
				while (PeekMessage(&message, 0, 0, 0, PM_REMOVE))
				{
					int multiplier = 10;
					unsigned int vkCode = message.wParam;
					TranslateMessage(&message);
					DispatchMessageA(&message);
					switch (message.message)
					{
					case WM_KEYDOWN:
						if (vkCode == 'W')
						{
							controller.up = true;
						}
						if (vkCode == 'S')
						{
							controller.down = true;
						}
						if (vkCode == 'A')
						{
							controller.left = true;
						}
						if (vkCode == 'D')
						{
							controller.right = true;
						}						
						if (vkCode == 'Z')
						{
							controller.wireframe = !controller.wireframe;
						}
						if (vkCode == 'X')
						{
							controller.colored = !controller.colored;
						}
						if (vkCode == 'C')
						{
							controller.shaded = !controller.shaded;
						}
						if (vkCode == 'V')
						{
							controller.dayCycle = !controller.dayCycle;
						}
						if (vkCode == 'U')
						{
							controller.yawF = true;
						}
						if (vkCode == 'O')
						{
							controller.yawB = true;
						}
						if (vkCode == 'B')
						{
							controller.generate = true;
						}
						if (vkCode == 'J')
						{
							controller.yawL = true;
						}
						if (vkCode == 'L')
						{
							controller.yawR = true;
						}
						if (vkCode == 'I')
						{
							controller.forward = true;
						}
						if (vkCode == 'K')
						{
							controller.backward = true;
						}
						if (vkCode == 'T') {
							controller.lUp = 1;
						}
						if (vkCode == 'F') {
							controller.lLeft = 1;
						}
						if (vkCode == 'G') {
							controller.lDown = 1;
						}
						if (vkCode == 'H') {
							controller.lRight = 1;
						}
						if (vkCode == 'R') {
							controller.lBackward = 1;
						}
						if (vkCode == 'Y') {
							controller.lForward = 1;
						}
						break;
					default:
						break;
					}
				}					
#pragma endregion
#pragma region SkyBox
				//Sky
				if (controller.dayCycle) {
					float change = 10.f * deltatime * 0.000001f;
					ghadi += change * pi / 180;
					if (ghadi > 2 * pi) { 
						ghadi = 0; 
						controller.reloadStars = true;
					}
				}
				//time region

				if (ghadi >= 0 && ghadi < 3.0f / 12.f * pi)
				{
					screenColor = blue; 
					controller.starOpacity = 1.0f;
					controller.clouds = true;
					controller.stars = false;
				}
				else if (ghadi >= 3.0f / 12.f * pi && ghadi < 5.0f / 12.f * pi)
				{
					screenColor = interPolateColors(3.0f / 12.f * pi, 5.0f / 12.f * pi, ghadi, blue, red);
					controller.clouds = false;
					controller.stars = false;
				}
				else if (ghadi >= 5.0f / 12.f * pi && ghadi < 7.0f / 12.f * pi)
				{
					screenColor = interPolateColors(5.0f / 12.f * pi, 7.0f / 12.f * pi, ghadi, red, black);
					controller.clouds = false;
					controller.stars = false;
				}
				else if (ghadi >= 7.0f / 12.f * pi && ghadi < 9.0f / 12.f * pi)
				{
					screenColor = black;
					controller.starOpacity = interPolate(7.0f / 12.f * pi, 9.0f / 12.f * pi, ghadi, 0.0f, 1.0f);
					controller.clouds = false;
					controller.stars = true;
				}
				else if (ghadi >= 9.0f / 12.f * pi && ghadi < 15.0f / 12.f * pi)
				{
					screenColor = black;
					controller.starOpacity = 1.f;
					controller.clouds = false;
					controller.stars = true;
				}
				else if (ghadi >= 15.0f / 12.f * pi && ghadi < 17.0f / 12.f * pi)
				{
					screenColor = black;
					controller.starOpacity = interPolate(15.0f / 12.f * pi, 17.0f / 12.f * pi, ghadi, 1.0f, 0.0f);
					controller.clouds = false;
					controller.stars = true;
				}
				else if (ghadi >= 17.0f / 12.f * pi && ghadi < 19.0f / 12.f * pi) {
					screenColor = interPolateColors(17.0f / 12.f * pi, 19.0f / 12.f * pi, ghadi, black, red);					
					controller.clouds = false;
					controller.stars = false;
				}
				else if (ghadi >= 19.0f / 12.f * pi && ghadi < 21.0f / 12.f * pi)
				{
					screenColor = interPolateColors(19.0f / 12.f * pi, 21.0f / 12.f * pi, ghadi, red, blue);
					controller.clouds = false;
					controller.stars = false;
				}
				else if (ghadi >= 21.0f / 12.f * pi && ghadi < 24.0f / 12.f * pi)
				{
					screenColor = blue;
					controller.starOpacity = 1.0f;
					controller.clouds = true;
					controller.stars = false;
				}

				//Intensity
				if (ghadi >= 0 && ghadi < 3.0f / 12.f * pi)
				{
					controller.Ia = blueInt;
				}
				else if (ghadi >= 3.0f / 12.f * pi && ghadi < 5.0f / 12.f * pi)
				{
					controller.Ia = interPolate(3.0f / 12.f * pi, 5.0f / 12.f * pi, ghadi, blueInt, blackInt);
				}
				else if (ghadi >= 5.0f / 12.f * pi && ghadi < 9.0f / 12.f * pi) {
					controller.Ia = interPolate(5.0f / 12.f * pi, 9.0f / 12.f * pi, ghadi, blackInt, moonInt);
				}
				else if (ghadi >= 9.0f / 12.f * pi && ghadi < 15.0f / 12.f * pi)
				{
					controller.Ia = moonInt;
				}
				else if (ghadi >= 15.0f / 12.f * pi && ghadi < 17.0f / 12.f * pi)
				{
					controller.Ia = interPolate(15.0f / 12.f * pi, 17.0f / 12.f * pi, ghadi, moonInt, blackInt);
				}
				else if (ghadi >= 17.0f / 12.f * pi && ghadi < 21.0f / 12.f * pi)
				{
					controller.Ia = interPolate(17.0f / 12.f * pi * pi, 21.0f / 12.f, ghadi, blackInt, blueInt);
				}
				else if (ghadi >= 21.0f / 12.f * pi && ghadi < 24.0f / 12.f * pi)
				{
					controller.Ia = blueInt;
				}

				controller.day = !(ghadi >= pi * 0.5f && ghadi < 1.5f * pi);
#pragma endregion
				ClrScr(screenColor);
				s.checkInput(controller, deltatime);
				s.draw();
#pragma region Initializer
				StretchDIBits(deviceContext, 0, 0, globalBuffer.width, globalBuffer.height,
							  0, 0, globalBuffer.width, globalBuffer.height, globalBuffer.memory, &globalBuffer.info, DIB_RGB_COLORS, SRCCOPY);
				frameCounter++;
			}
		}
	}
	return 0;
#pragma endregion
};