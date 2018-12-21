////////////////////////////////////////////////////////////////////////////////
#pragma once
////////////////////////////////////////////////////////////////////////////////

#include "imp/ImageData.h"

#include "ui/ImageCtrl.h"

#include "data/PcData.h"
#include "data/PcAlg.h"

////////////////////////////////////////////////////////////////////////////////

class MainWindow : public CWindowImpl<MainWindow, CWindow, CFrameWinTraits>
{
public:
	DECLARE_WND_CLASS(_T("Pcolor Window Class"))

	//--------------------------------------------------------------------------
	enum { IDC_BTN_LOAD_IMAGE = 10,
		IDC_TEXT_PIXEL,
		IDC_BTN_SAVE_IMAGE,
		IDC_PIC_ORIGINAL,
		IDC_PIC_PROCESS,
		IDC_TEXT_GRAY,
		IDC_EDIT_GRAY,
		IDC_UPDOWN_GRAY,
		IDC_TEXT_R,
		IDC_EDIT_R,
		IDC_UPDOWN_R,
		IDC_TEXT_G,
		IDC_EDIT_G,
		IDC_UPDOWN_G,
		IDC_TEXT_B,
		IDC_EDIT_B,
		IDC_UPDOWN_B,
		IDC_BTN_LOAD_CFG,
		IDC_BTN_SAVE_CFG,
		IDC_LIST_LUT
	};

	CButton	       m_btnLoadImage;
	CStatic        m_txtPixel;
	CButton	       m_btnSaveImage;
	ImageCtrl      m_imageCtrlOriginal;
	ImageCtrl      m_imageCtrlProcess;
	CStatic        m_txtGray;
	CEdit          m_editGray;
	CUpDownCtrl    m_updGray;
	CStatic        m_txtR;
	CEdit          m_editR;
	CUpDownCtrl    m_updR;
	CStatic        m_txtG;
	CEdit          m_editG;
	CUpDownCtrl    m_updG;
	CStatic        m_txtB;
	CEdit          m_editB;
	CUpDownCtrl    m_updB;
	CButton        m_btnLoadCfg;
	CButton        m_btnSaveCfg;
	CListViewCtrl  m_listLut;

	MainWindow() : m_spImgOrg(std::make_shared<ATL::CImage>()),
					m_spImgPro(std::make_shared<ATL::CImage>())
	{
		m_imageCtrlOriginal.set_Image(m_spImgOrg);
		m_imageCtrlProcess.set_Image(m_spImgPro);
	}

private:
	std::shared_ptr<ATL::CImage> m_spImgOrg;
	std::shared_ptr<ATL::CImage> m_spImgPro;

	ColorData m_cData;
	GrayData  m_gData;

	PcCfg m_cfg;
	//--------------------------------------------------------------------------

public:
//message handler
	BEGIN_MSG_MAP(MainWindow)
		MESSAGE_HANDLER(WM_CREATE, OnCreate)
		MESSAGE_HANDLER(WM_CLOSE, OnClose)
		MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
		MESSAGE_HANDLER(WM_ERASEBKGND, OnEraseBkgnd)  // Sent when the window background must be erased (for example, when a window is resized).
		MESSAGE_HANDLER(WM_SIZE, OnSize)
//------------------------------------------------------------------------------
		COMMAND_HANDLER(IDC_BTN_LOAD_IMAGE, BN_CLICKED, OnBtnLoadImageClicked)
		COMMAND_HANDLER(IDC_BTN_SAVE_IMAGE, BN_CLICKED, OnBtnSaveImageClicked)
		NOTIFY_HANDLER(IDC_PIC_ORIGINAL, ICN_PIXEL, OnImageOriginalPixel)
		NOTIFY_HANDLER(IDC_PIC_ORIGINAL, ICN_SCROLL, OnImageOriginalScroll)
		NOTIFY_HANDLER(IDC_PIC_PROCESS, ICN_SCROLL, OnImageProcessScroll)
		COMMAND_HANDLER(IDC_BTN_LOAD_CFG, BN_CLICKED, OnBtnLoadCfgClicked)
		COMMAND_HANDLER(IDC_BTN_SAVE_CFG, BN_CLICKED, OnBtnSaveCfgClicked)
		NOTIFY_HANDLER(IDC_LIST_LUT, NM_CLICK, OnListLutClick)
		NOTIFY_HANDLER(IDC_UPDOWN_GRAY, UDN_DELTAPOS, OnUpdGrayDelta)
		NOTIFY_HANDLER(IDC_UPDOWN_R, UDN_DELTAPOS, OnUpdRDelta)
		NOTIFY_HANDLER(IDC_UPDOWN_G, UDN_DELTAPOS, OnUpdGDelta)
		NOTIFY_HANDLER(IDC_UPDOWN_B, UDN_DELTAPOS, OnUpdBDelta)
//------------------------------------------------------------------------------
		REFLECT_NOTIFICATIONS()
//------------------------------------------------------------------------------
	END_MSG_MAP()

	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		//----------------------------------------------------------------------
		m_btnLoadImage.Create(m_hWnd, rcDefault, _T("Load Image"),
						WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN | WS_CLIPSIBLINGS, 0,
						IDC_BTN_LOAD_IMAGE);
		m_txtPixel.Create(m_hWnd, rcDefault, _T(""),
						WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN | WS_CLIPSIBLINGS, 0,
						IDC_TEXT_PIXEL);
		m_btnSaveImage.Create(m_hWnd, rcDefault, _T("Save Image"),
						WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN | WS_CLIPSIBLINGS, 0,
						IDC_BTN_SAVE_IMAGE);
		m_imageCtrlOriginal.Create(m_hWnd, rcDefault, NULL,
						WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN | WS_CLIPSIBLINGS, 0,
						IDC_PIC_ORIGINAL);
		m_imageCtrlOriginal.UpdateScroll();
		m_imageCtrlProcess.Create(m_hWnd, rcDefault, NULL,
						WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN | WS_CLIPSIBLINGS, 0,
						IDC_PIC_PROCESS);
		m_imageCtrlProcess.UpdateScroll();
		m_txtGray.Create(m_hWnd, rcDefault, _T("Gray:"),
						WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN | WS_CLIPSIBLINGS, 0,
						IDC_TEXT_GRAY);
		m_editGray.Create(m_hWnd, rcDefault, _T("0"),
						WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | ES_NUMBER, 0,
						IDC_EDIT_GRAY);
		m_updGray.Create(m_hWnd, rcDefault, NULL,
						WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | UDS_AUTOBUDDY | UDS_SETBUDDYINT, 0,
						IDC_UPDOWN_GRAY);
		m_txtR.Create(m_hWnd, rcDefault, _T("R:"),
						WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN | WS_CLIPSIBLINGS, 0,
						IDC_TEXT_R);
		m_editR.Create(m_hWnd, rcDefault, _T("0"),
						WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | ES_NUMBER, 0,
						IDC_EDIT_R);
		m_updR.Create(m_hWnd, rcDefault, NULL,
						WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | UDS_AUTOBUDDY | UDS_SETBUDDYINT, 0,
						IDC_UPDOWN_R);
		m_txtG.Create(m_hWnd, rcDefault, _T("G:"),
						WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN | WS_CLIPSIBLINGS, 0,
						IDC_TEXT_G);
		m_editG.Create(m_hWnd, rcDefault, _T("0"),
						WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | ES_NUMBER, 0,
						IDC_EDIT_G);
		m_updG.Create(m_hWnd, rcDefault, NULL,
						WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | UDS_AUTOBUDDY | UDS_SETBUDDYINT, 0,
						IDC_UPDOWN_G);
		m_txtB.Create(m_hWnd, rcDefault, _T("B:"),
						WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN | WS_CLIPSIBLINGS, 0,
						IDC_TEXT_B);
		m_editB.Create(m_hWnd, rcDefault, _T("0"),
						WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | ES_NUMBER, 0,
						IDC_EDIT_B);
		m_updB.Create(m_hWnd, rcDefault, NULL,
						WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | UDS_AUTOBUDDY | UDS_SETBUDDYINT, 0,
						IDC_UPDOWN_B);
		m_updGray.SetRange32(0, 255);
		m_updGray.SetPos32(0);
		m_updGray.SetBuddy(m_editGray);
		m_updR.SetRange32(0, 255);
		m_updR.SetPos32(0);
		m_updR.SetBuddy(m_editR);
		m_updG.SetRange32(0, 255);
		m_updG.SetPos32(0);
		m_updG.SetBuddy(m_editG);
		m_updB.SetRange32(0, 255);
		m_updB.SetPos32(0);
		m_updB.SetBuddy(m_editB);
		m_btnLoadCfg.Create(m_hWnd, rcDefault, _T("Load Cfg"),
						WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN | WS_CLIPSIBLINGS, 0,
						IDC_BTN_LOAD_CFG);
		m_btnSaveCfg.Create(m_hWnd, rcDefault, _T("Save Cfg"),
						WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN | WS_CLIPSIBLINGS, 0,
						IDC_BTN_SAVE_CFG);
		m_listLut.Create(m_hWnd, rcDefault, NULL,
						WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | LVS_REPORT | LVS_SHOWSELALWAYS | LVS_SINGLESEL, 0,
						IDC_LIST_LUT);
		m_listLut.SetExtendedListViewStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES,
											LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
		m_listLut.InsertColumn(0, _T("Gray"), LVCFMT_LEFT, 50);
		m_listLut.InsertColumn(1, _T("R"), LVCFMT_LEFT, 50);
		m_listLut.InsertColumn(2, _T("G"), LVCFMT_LEFT, 50);
		m_listLut.InsertColumn(3, _T("B"), LVCFMT_LEFT, 50);
		//start state
		m_btnSaveImage.EnableWindow(FALSE);
		m_editGray.EnableWindow(FALSE);
		m_updGray.EnableWindow(FALSE);
		m_editR.EnableWindow(FALSE);
		m_updR.EnableWindow(FALSE);
		m_editG.EnableWindow(FALSE);
		m_updG.EnableWindow(FALSE);
		m_editB.EnableWindow(FALSE);
		m_updB.EnableWindow(FALSE);
		m_btnLoadCfg.EnableWindow(FALSE);
		m_btnSaveCfg.EnableWindow(FALSE);
		m_listLut.EnableWindow(FALSE);
		//----------------------------------------------------------------------
		return 0;
	}
	LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		return 1;
	}
	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		::PostQuitMessage(0);
		return 0;
	}
	LRESULT OnEraseBkgnd(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		CDCHandle dc((HDC)wParam);
		RECT rcClient;
		GetClientRect(&rcClient);
		CBrush bsh;
		bsh.CreateSolidBrush(RGB(64, 224, 225));
		dc.FillRect(&rcClient, bsh);
		return 1;
		// An application should return nonzero if it erases the background; otherwise, it should return zero.
	}
	LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		//----------------------------------------------------------------------
		if( wParam != SIZE_MINIMIZED ) {
			int w = LOWORD(lParam);
			int h = HIWORD(lParam);
			int x = 10;
			int y = 10;
			m_btnLoadImage.SetWindowPos(NULL, x, y, 80, 40, SWP_NOACTIVATE | SWP_NOZORDER);
			x += (80 + 10);
			m_txtPixel.SetWindowPos(NULL, x, y, 100, 40, SWP_NOACTIVATE | SWP_NOZORDER);
			x += (100 + 10);
			m_btnSaveImage.SetWindowPos(NULL, x, y, 80, 40, SWP_NOACTIVATE | SWP_NOZORDER);
			x = 10;
			y += (40 + 10);
			int wi = (w - 10 * 4) / 3;
			m_imageCtrlOriginal.SetWindowPos(NULL, x, y, wi, h - y - 10, SWP_NOACTIVATE | SWP_NOZORDER);
			m_imageCtrlOriginal.UpdateScroll();
			m_imageCtrlProcess.SetWindowPos(NULL, x + wi + 10, y, wi, h - y - 10, SWP_NOACTIVATE | SWP_NOZORDER);
			m_imageCtrlProcess.UpdateScroll();
			x = w - 10;
			y = 10;
			m_updB.SetWindowPos(NULL, x - 20, y, 20, 40, SWP_NOACTIVATE | SWP_NOZORDER);
			x -= 20;
			m_editB.SetWindowPos(NULL, x - 30, y, 30, 40, SWP_NOACTIVATE | SWP_NOZORDER);
			x -= 30;
			m_txtB.SetWindowPos(NULL, x - 20, y, 20, 40, SWP_NOACTIVATE | SWP_NOZORDER);
			x -= (20 + 10);
			m_updG.SetWindowPos(NULL, x - 20, y, 20, 40, SWP_NOACTIVATE | SWP_NOZORDER);
			x -= 20;
			m_editG.SetWindowPos(NULL, x - 30, y, 30, 40, SWP_NOACTIVATE | SWP_NOZORDER);
			x -= 30;
			m_txtG.SetWindowPos(NULL, x - 20, y, 20, 40, SWP_NOACTIVATE | SWP_NOZORDER);
			x -= (20 + 10);
			m_updR.SetWindowPos(NULL, x - 20, y, 20, 40, SWP_NOACTIVATE | SWP_NOZORDER);
			x -= 20;
			m_editR.SetWindowPos(NULL, x - 30, y, 30, 40, SWP_NOACTIVATE | SWP_NOZORDER);
			x -= 30;
			m_txtR.SetWindowPos(NULL, x - 20, y, 20, 40, SWP_NOACTIVATE | SWP_NOZORDER);
			x -= (20 + 10);
			m_updGray.SetWindowPos(NULL, x - 20, y, 20, 40, SWP_NOACTIVATE | SWP_NOZORDER);
			x -= 20;
			m_editGray.SetWindowPos(NULL, x - 30, y, 30, 40, SWP_NOACTIVATE | SWP_NOZORDER);
			x -= 30;
			m_txtGray.SetWindowPos(NULL, x - 40, y, 40, 40, SWP_NOACTIVATE | SWP_NOZORDER);
			x = w - 10;
			y += (40 + 10);
			m_btnSaveCfg.SetWindowPos(NULL, x - 80, y, 80, 40, SWP_NOACTIVATE | SWP_NOZORDER);
			m_btnLoadCfg.SetWindowPos(NULL, x - 80 - 10 - 80, y, 80, 40, SWP_NOACTIVATE | SWP_NOZORDER);
			x = 10 + wi + 10 + wi + 10;
			y += (40 + 10);
			m_listLut.SetWindowPos(NULL, x, y, w - 10 - x, h - 10 - y, SWP_NOACTIVATE | SWP_NOZORDER);
		}
		//----------------------------------------------------------------------
		bHandled = FALSE;
		return 1;
	}
	//-------------------------------------------------------------------------- Load
	LRESULT OnBtnLoadImageClicked(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		CFileDialog dlg(TRUE);
		if( dlg.DoModal() == IDOK ) {
			CWaitCursor wac;
			ATL::CImage image;
			if( FAILED(image.Load(dlg.m_szFileName)) ) {
				AtlMessageBox(NULL, _T("error load image"), _T("error"), MB_OK);
				return 0;
			}
			int iBPP = image.GetBPP();
			if( iBPP != 8 && iBPP != 24 ) {
				AtlMessageBox(NULL, _T("error load image"), _T("error"), MB_OK);
				return 0;
			}
			ImageDataHelper::ImageToColorData(image, m_cData);
			ImageDataHelper::ColorDataToGrayData(m_cData, m_gData);
			ImageDataHelper::GrayDataToImage(m_gData, *m_spImgOrg);
			ImageDataHelper::GrayDataToImage(m_gData, *m_spImgPro);
			m_imageCtrlOriginal.UpdateScroll();
			m_imageCtrlProcess.UpdateScroll();
			//state
			m_btnSaveImage.EnableWindow(FALSE);
			m_editGray.EnableWindow(FALSE);
			m_updGray.EnableWindow(FALSE);
			m_editR.EnableWindow(FALSE);
			m_updR.EnableWindow(FALSE);
			m_editG.EnableWindow(FALSE);
			m_updG.EnableWindow(FALSE);
			m_editB.EnableWindow(FALSE);
			m_updB.EnableWindow(FALSE);
			m_btnLoadCfg.EnableWindow(TRUE);
			m_btnSaveCfg.EnableWindow(FALSE);
			m_listLut.EnableWindow(FALSE);
			m_listLut.DeleteAllItems();
		}
		return 0;
	}
	LRESULT OnBtnSaveImageClicked(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		if( m_spImgPro.get() == NULL || m_spImgPro->IsNull() )
			return 0;
		CFileDialog dlg(FALSE);
		if( dlg.DoModal() == IDOK ) {
			CWaitCursor wac;
			if( FAILED(m_spImgPro->Save(dlg.m_szFileName, Gdiplus::ImageFormatBMP)) ) {
				AtlMessageBox(NULL, _T("error save image"), _T("error"), MB_OK);
				return 0;
			}
			m_btnSaveImage.EnableWindow(FALSE);
		}
		return 0;
	}
	LRESULT OnImageOriginalPixel(int idCtrl, LPNMHDR pNMHDR, BOOL& bHandled)
	{
		NMIMAGEPIXEL* pnm = (NMIMAGEPIXEL*)pNMHDR;
		if( pnm->rgb == CLR_INVALID ) {
			m_txtPixel.SetWindowText(_T(""));
			return 0;
		}
		CString str;
		COLORREF clr = m_spImgPro->GetPixel(pnm->x, pnm->y);
		str.Format(_T("%u\r\n%u %u %u"),
				(UINT)GetRValue(pnm->rgb),
				(UINT)GetRValue(clr), (UINT)GetGValue(clr), (UINT)GetBValue(clr)
				);
		m_txtPixel.SetWindowText(str);
		return 0;
	}
	LRESULT OnImageOriginalScroll(int idCtrl, LPNMHDR pNMHDR, BOOL& bHandled)
	{
		NMIMAGESCROLL* pnm = (NMIMAGESCROLL*)pNMHDR;
		m_imageCtrlProcess.SetScrollOffset(pnm->pt);
		return 0;
	}
	LRESULT OnImageProcessScroll(int idCtrl, LPNMHDR pNMHDR, BOOL& bHandled)
	{
		NMIMAGESCROLL* pnm = (NMIMAGESCROLL*)pNMHDR;
		m_imageCtrlOriginal.SetScrollOffset(pnm->pt);
		return 0;
	}
	LRESULT OnBtnLoadCfgClicked(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		CFileDialog dlg(TRUE);
		if( dlg.DoModal() == IDOK ) {
			CWaitCursor wac;
			PcCfg cfg;
			if( !cfg.Load(dlg.m_szFileName) ) {
				AtlMessageBox(NULL, _T("error load configuration"), _T("error"), MB_OK);
				return 0;
			}
			m_cfg = std::move(cfg);
			//ui
			m_editGray.EnableWindow(FALSE);
			m_updGray.EnableWindow(FALSE);
			m_editR.EnableWindow(FALSE);
			m_updR.EnableWindow(FALSE);
			m_editG.EnableWindow(FALSE);
			m_updG.EnableWindow(FALSE);
			m_editB.EnableWindow(FALSE);
			m_updB.EnableWindow(FALSE);
			m_btnSaveCfg.EnableWindow(FALSE);
			m_listLut.EnableWindow(TRUE);
			m_listLut.DeleteAllItems();
			CString str;
			for( size_t i = 0; i < m_cfg.GetCount(); i ++ ) {
				int r, g, b;
				m_cfg.GetRgbAt(i, r, g, b);
				m_listLut.InsertItem((int)i, _T(""));
				str.Format(_T("%d"), m_cfg.GetGrayAt(i));
				m_listLut.SetItemText((int)i, 0, str);
				str.Format(_T("%d"), r);
				m_listLut.SetItemText((int)i, 1, str);
				str.Format(_T("%d"), g);
				m_listLut.SetItemText((int)i, 2, str);
				str.Format(_T("%d"), b);
				m_listLut.SetItemText((int)i, 3, str);
			}
			generate_pseudo_color();
		}
		return 0;
	}
	LRESULT OnBtnSaveCfgClicked(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		CFileDialog dlg(FALSE);
		if( dlg.DoModal() == IDOK ) {
			CWaitCursor wac;
			if( !m_cfg.Save(dlg.m_szFileName) ) {
				AtlMessageBox(NULL, _T("error save configuration"), _T("error"), MB_OK);
				return 0;
			}
			m_btnSaveCfg.EnableWindow(FALSE);
		}
		return 0;
	}
	LRESULT OnListLutClick(int idCtrl, LPNMHDR pNMHDR, BOOL& bHandled)
	{
		NMHDR* pnmh = (NMHDR*)pNMHDR;
		int index = m_listLut.GetSelectedIndex();
		//no selection
		if( index < 0 ) {
			m_editGray.EnableWindow(FALSE);
			m_updGray.EnableWindow(FALSE);
			m_editR.EnableWindow(FALSE);
			m_updR.EnableWindow(FALSE);
			m_editG.EnableWindow(FALSE);
			m_updG.EnableWindow(FALSE);
			m_editB.EnableWindow(FALSE);
			m_updB.EnableWindow(FALSE);
			return 0;
		}
		int gray, r, g, b;
		gray = m_cfg.GetGrayAt(index);
		m_cfg.GetRgbAt(index, r, g, b);
		{
			int gray1, gray2;
			if( m_cfg.GetCount() == 1 ) {
				gray1 = 0;
				gray2 = 255;
			}
			else {
				if( index == m_cfg.GetCount() - 1 ) {
					gray1 = m_cfg.GetGrayAt(index - 1) + 1;
					gray2 = 255;
				}
				else if( index == 0 ) {
					gray1 = 0;
					gray2 = m_cfg.GetGrayAt(index + 1) - 1;
				}
				else {
					gray1 = m_cfg.GetGrayAt(index - 1) + 1;
					gray2 = m_cfg.GetGrayAt(index + 1) - 1;
				}
			}
			m_updGray.SetRange32(gray1, gray2);
		} //end block
		m_updGray.SetPos32(gray);
		m_updR.SetPos32(r);
		m_updG.SetPos32(g);
		m_updB.SetPos32(b);
		//ui
		m_editGray.EnableWindow(TRUE);
		m_updGray.EnableWindow(TRUE);
		m_editR.EnableWindow(TRUE);
		m_updR.EnableWindow(TRUE);
		m_editG.EnableWindow(TRUE);
		m_updG.EnableWindow(TRUE);
		m_editB.EnableWindow(TRUE);
		m_updB.EnableWindow(TRUE);
		return 0;
	}
	LRESULT OnUpdGrayDelta(int idCtrl, LPNMHDR pNMHDR, BOOL& bHandled)
	{
		NMUPDOWN* pnm = (NMUPDOWN*)pNMHDR;
		int v = calc_upd_value(pnm->iPos + pnm->iDelta, m_updGray);
		int index = m_listLut.GetSelectedIndex();
		ATLASSERT( index >= 0 );
		adjust_value_ui(v, 0, index);
		m_cfg.SetGrayAt(index, v);
		generate_pseudo_color();
		m_btnSaveCfg.EnableWindow(TRUE);
		return 0;
	}
	LRESULT OnUpdRDelta(int idCtrl, LPNMHDR pNMHDR, BOOL& bHandled)
	{
		NMUPDOWN* pnm = (NMUPDOWN*)pNMHDR;
		int v = calc_upd_value(pnm->iPos + pnm->iDelta, m_updR);
		int index = m_listLut.GetSelectedIndex();
		ATLASSERT( index >= 0 );
		adjust_value_ui(v, 1, index);
		m_cfg.SetRAt(index, v);
		generate_pseudo_color();
		m_btnSaveCfg.EnableWindow(TRUE);
		return 0;
	}
	LRESULT OnUpdGDelta(int idCtrl, LPNMHDR pNMHDR, BOOL& bHandled)
	{
		NMUPDOWN* pnm = (NMUPDOWN*)pNMHDR;
		int v = calc_upd_value(pnm->iPos + pnm->iDelta, m_updG);
		int index = m_listLut.GetSelectedIndex();
		ATLASSERT( index >= 0 );
		adjust_value_ui(v, 2, index);
		m_cfg.SetGAt(index, v);
		generate_pseudo_color();
		m_btnSaveCfg.EnableWindow(TRUE);
		return 0;
	}
	LRESULT OnUpdBDelta(int idCtrl, LPNMHDR pNMHDR, BOOL& bHandled)
	{
		NMUPDOWN* pnm = (NMUPDOWN*)pNMHDR;
		int v = calc_upd_value(pnm->iPos + pnm->iDelta, m_updB);
		int index = m_listLut.GetSelectedIndex();
		ATLASSERT( index >= 0 );
		adjust_value_ui(v, 3, index);
		m_cfg.SetBAt(index, v);
		generate_pseudo_color();
		m_btnSaveCfg.EnableWindow(TRUE);
		return 0;
	}

private:
	void generate_pseudo_color()
	{
		PcAlgHelper::PseudoColor(m_gData, m_cfg, m_cData);
		ImageDataHelper::ColorDataToImage(m_cData, *m_spImgPro);
		m_imageCtrlProcess.UpdateScroll();
		m_btnSaveImage.EnableWindow(TRUE);
	}
	int calc_upd_value(int v, CUpDownCtrl& upd)
	{
		int iMin, iMax;
		upd.GetRange32(iMin, iMax);
		if( v < iMin )  v = iMin;
		if( v > iMax )  v = iMax;
		return v;
	}
	void adjust_value_ui(int v, int iCol, int index)
	{
		CString str;
		str.Format(_T("%d"), v);
		m_listLut.SetItemText(index, iCol, str);
	}
	//--------------------------------------------------------------------------
};

////////////////////////////////////////////////////////////////////////////////
