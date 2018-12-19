////////////////////////////////////////////////////////////////////////////////

#include "precomp.h"

#include "window/MainWindow.h"

////////////////////////////////////////////////////////////////////////////////

CAppModule _Module;

////////////////////////////////////////////////////////////////////////////////

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPTSTR lpstrCmdLine, int nCmdShow)
{
	INITCOMMONCONTROLSEX iccx;
	iccx.dwSize = sizeof(iccx);
	iccx.dwICC = ICC_COOL_CLASSES | ICC_BAR_CLASSES;
	BOOL bRet = ::InitCommonControlsEx(&iccx);
	bRet;
	ATLASSERT(bRet);

	HRESULT hRes = _Module.Init(NULL, hInstance);
	hRes;
	ATLASSERT(SUCCEEDED(hRes));
	CMessageLoop theLoop;
	_Module.AddMessageLoop(&theLoop);
	MainWindow wndMain;
	//----------------------------------------------------------------------
	if( wndMain.Create(NULL, CWindow::rcDefault, _T("Pcolor Tool")) == NULL ) {
		ATLTRACE(_T("Main window creation failed!\n"));
		_Module.Term();
		return 0;
	}
	wndMain.ShowWindow(nCmdShow);
	//----------------------------------------------------------------------
	int nRet = theLoop.Run();
	_Module.RemoveMessageLoop();
	_Module.Term();

	return nRet;
}

////////////////////////////////////////////////////////////////////////////////
