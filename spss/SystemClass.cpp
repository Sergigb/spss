////////////////////////////////////////////////////////////////////////////////
// Filename: systemclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "SystemClass.h"


SystemClass::SystemClass()
{
	m_Input = NULL;
	m_Graphics = NULL;
	m_Fps = 0;
	m_Cpu = 0;
	m_Timer = 0;
	m_Position = 0;

}

SystemClass::SystemClass(const SystemClass& other)
{
}


SystemClass::~SystemClass()
{
}

bool SystemClass::Initialize()
{
	int screenWidth, screenHeight;
	bool result;


	// Initialize the width and height of the screen to zero before sending the variables into the function.
	screenWidth = 0;
	screenHeight = 0;

	// Initialize the windows api.
	InitializeWindows(screenWidth, screenHeight);

	// Create the input object.  This object will be used to handle reading the keyboard input from the user.
	m_Input = new InputClass;
	if(!m_Input)
	{
		return false;
	}

	// Initialize the input object.
	result = m_Input->Initialize(m_hinstance, m_hwnd, screenWidth, screenHeight);
	if(!result)
	{
		MessageBox(m_hwnd, L"Could not initialize the input object.", L"Error", MB_OK);
		return false;
	}

	// Create the graphics object.  This object will handle rendering all the graphics for this application.
	m_Graphics = new GraphicsClass;
	if(!m_Graphics)
	{
		return false;
	}

	// Initialize the graphics object.
	result = m_Graphics->Initialize(screenWidth, screenHeight, m_hwnd);
	if(!result)
	{
		return false;
	}

	// Create the fps object.
	m_Fps = new FpsClass;
	if(!m_Fps)
	{
		return false;
	}

	// Initialize the fps object.
	m_Fps->Initialize();

	// Create the cpu object.
	m_Cpu = new CpuClass;
	if(!m_Cpu)
	{
		return false;
	}

	// Initialize the cpu object.
	m_Cpu->Initialize();

	// Create the timer object.
	m_Timer = new TimerClass;
	if(!m_Timer)
	{
		return false;
	}

	// Initialize the timer object.
	result = m_Timer->Initialize();
	if(!result)
	{
		MessageBox(m_hwnd, L"Could not initialize the Timer object.", L"Error", MB_OK);
		return false;
	}	
	
	// Create the position object.
	m_Position = new PositionClass;
	if(!m_Position)
	{
		return false;
	}

	//Object Test

	m_object = new Object;
	if(!m_object)
		return false;

	m_object->SetCoordinates(0.0, 0.0, -2.0);

	return true;
}


void SystemClass::Shutdown()
{
	// Release the position object.
	if(m_Position)
	{
		delete m_Position;
		m_Position = 0;
	}

	// Release the timer object.
	if(m_Timer)
	{
		delete m_Timer;
		m_Timer = 0;
	}

	// Release the cpu object.
	if(m_Cpu)
	{
		m_Cpu->Shutdown();
		delete m_Cpu;
		m_Cpu = 0;
	}

	// Release the fps object.
	if(m_Fps)
	{
		delete m_Fps;
		m_Fps = 0;
	}

	// Release the graphics object.
	if(m_Graphics)
	{
		m_Graphics->Shutdown();
		delete m_Graphics;
		m_Graphics = NULL;
	}

	// Release the input object.
	if(m_Input)
	{
		m_Input->Shutdown();
		delete m_Input;
		m_Input = 0;
	}

	// Shutdown the window.
	ShutdownWindows();
	
	return;
}


void SystemClass::Run()
{
	MSG msg;
	bool done, result;


	// Initialize the message structure.
	ZeroMemory(&msg, sizeof(MSG));
	
	// Loop until there is a quit message from the window or the user.
	done = false;
	while(!done)
	{
		// Handle the windows messages.
		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		// If windows signals to end the application then exit out.
		if(msg.message == WM_QUIT)
		{
			done = true;
		}
		else
		{
			// Otherwise do the frame processing.
			result = Frame();
			if(!result)
			{
				done = true;
			}
		}

		// Check if the user pressed escape and wants to quit.
		if(m_Input->IsEscapePressed() == true)
		{
			done = true;
		}
	}

	return;
}


bool SystemClass::Frame()
{
	bool keyDown, result;
	float rotationY, rotationX;


	// Update the system stats.
	m_Timer->Frame();

	// Do the input frame processing.
	result = m_Input->Frame();
	if(!result)
	{
		return false;
	}

	//el input chapucero hay que cambiarlo

	if(m_Input->IsPressed(DIK_A)){
		m_object->rotate(0.0f, 0.01f, 0.0f);
	}

	if(m_Input->IsPressed(DIK_D)){
		m_object->rotate(0.0f, -0.01f, 0.0f);
	}

	if(m_Input->IsPressed(DIK_W)){
		m_object->rotate(0.01f, 0.0f, 0.0f);
	}

	if(m_Input->IsPressed(DIK_S)){
		m_object->rotate(-0.01f, 0.0f, 0.0f);
	}

	if(m_Input->IsPressed(DIK_Q)){
		m_object->rotate(0.0f, 0.0f, 0.01f);
	}

	if(m_Input->IsPressed(DIK_E)){
		m_object->rotate(0.0f, 0.0f, -0.01f);
	}

	if(m_Input->IsPressed(DIK_I)){
		m_object->translateLocal(0.01f, 0.0f, 0.0f);
	}

	if(m_Input->IsPressed(DIK_K)){
		m_object->translateLocal(-0.01f, 0.0f, 0.0f);
	}

	if(m_Input->IsPressed(DIK_J)){
		m_object->translateLocal(0.0f, 0.01f, 0.0f);
	}

	if(m_Input->IsPressed(DIK_L)){
		m_object->translateLocal(0.0f, -0.01f, 0.0f);
	}

	if(m_Input->IsPressed(DIK_O)){
		m_object->translateLocal(0.0f, 0.0f, -0.01f);
	}

	if(m_Input->IsPressed(DIK_U)){
		m_object->translateLocal(0.0f, 0.0f, 0.01f);
	}

	if(m_Input->IsRMBpressed())
		m_object->translateXYZ(0.0f, 0.0f, -0.2f);

	// Set the frame time for calculating the updated position.
	m_Position->SetFrameTime(m_Timer->GetTime());

	m_Position->Rotate(m_Input->IsPressed(DIK_LEFT), m_Input->IsPressed(DIK_RIGHT), m_Input->IsPressed(DIK_UP), m_Input->IsPressed(DIK_DOWN));

	// Get the current view point rotation.
	m_Position->GetRotation(rotationY, rotationX);

	// Do the frame processing for the graphics object.
	result = m_Graphics->Frame(rotationY, rotationX, m_Input->IsPressed(DIK_NUMPAD8));

	if(!result)
	{
		return false;
	}

	// Finally render the graphics to the screen.
	result = m_Graphics->Render(m_object);
	if(!result)
	{
		return false;
	}
	return true;
}




LRESULT CALLBACK SystemClass::MessageHandler(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam)
{
	switch(umsg){
		case WM_KEYUP:{
			MessageBox(m_hwnd, L"keyyyy.", L"DOOOWN", MB_OK);
		}
	}


	return DefWindowProc(hwnd, umsg, wparam, lparam);
}


void SystemClass::InitializeWindows(int& screenWidth, int& screenHeight)
{
	WNDCLASSEX wc;
	DEVMODE dmScreenSettings;
	int posX, posY;


	// Get an external pointer to this object.
	ApplicationHandle = this;

	// Get the instance of this application.
	m_hinstance = GetModuleHandle(NULL);

	// Give the application a name.
	m_applicationName = L"Engine";

	// Setup the windows class with default settings.
	wc.style = 0;//CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = m_hinstance;
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wc.hIconSm = wc.hIcon;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = m_applicationName;
	wc.cbSize = sizeof(WNDCLASSEX);
	
	// Register the window class.
	RegisterClassEx(&wc);

	// Determine the resolution of the clients desktop screen.
	screenWidth  = GetSystemMetrics(SM_CXSCREEN);
	screenHeight = GetSystemMetrics(SM_CYSCREEN);

	// Setup the screen settings depending on whether it is running in full screen or in windowed mode.
	if(FULL_SCREEN)
	{
		// If full screen set the screen to maximum size of the users desktop and 32bit.
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
		dmScreenSettings.dmSize       = sizeof(dmScreenSettings);
		dmScreenSettings.dmPelsWidth  = (unsigned long)screenWidth;
		dmScreenSettings.dmPelsHeight = (unsigned long)screenHeight;
		dmScreenSettings.dmBitsPerPel = 32;			
		dmScreenSettings.dmFields     = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		// Change the display settings to full screen.
		ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);

		// Set the position of the window to the top left corner.
		posX = posY = 0;
	}
	else
	{
		// If windowed then set it to 800x600 resolution.
		screenWidth  = 1280;
		screenHeight = 720;

		// Place the window in the middle of the screen.
		posX = (GetSystemMetrics(SM_CXSCREEN) - screenWidth)  / 2;
		posY = (GetSystemMetrics(SM_CYSCREEN) - screenHeight) / 2;
	}

	// Create the window with the screen settings and get the handle to it.
	m_hwnd = CreateWindowEx(WS_EX_CLIENTEDGE|WS_EX_ACCEPTFILES, m_applicationName, m_applicationName, 
				WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_POPUP,
				posX, posY, screenWidth, screenHeight, NULL, NULL, m_hinstance, NULL);

	// Bring the window up on the screen and set it as main focus.
	ShowWindow(m_hwnd, SW_SHOW);
	SetForegroundWindow(m_hwnd);
	SetFocus(m_hwnd);

	// Hide the mouse cursor.
	ShowCursor(false);

	return;
}


void SystemClass::ShutdownWindows()
{
	// Show the mouse cursor.
	ShowCursor(true);

	// Fix the display settings if leaving full screen mode.
	if(FULL_SCREEN)
	{
		ChangeDisplaySettings(NULL, 0);
	}

	// Remove the window.
	DestroyWindow(m_hwnd);
	m_hwnd = NULL;

	// Remove the application instance.
	UnregisterClass(m_applicationName, m_hinstance);
	m_hinstance = NULL;

	// Release the pointer to this class.
	ApplicationHandle = NULL;

	return;
}




LRESULT CALLBACK WndProc(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam){

	SetFocus(hwnd);
	switch(umessage)
	{
		// Check if the window is being destroyed.
		case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}

		// Check if the window is being closed.
		case WM_CLOSE:
		{
			PostQuitMessage(0);		
			return 0;
		}
		case WM_KEYDOWN:{
			
		}
						

		// All other messages pass to the message handler in the system class.
		default:
		{
			return ApplicationHandle->MessageHandler(hwnd, umessage, wparam, lparam);
		}
	}
}