// CShowDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "ScreenShot.h"
#include "CShowDlg.h"
#include "afxdialogex.h"


// CShowDlg 对话框

IMPLEMENT_DYNAMIC(CShowDlg, CDialogEx)

CShowDlg::CShowDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SHOW_DIALOG, pParent)
{
	//DC就是设备上下文

	// 获取屏幕的宽高
	_width = GetSystemMetrics(SM_CXSCREEN);
	_height = GetSystemMetrics(SM_CYSCREEN);

	//获取桌面DC
	CDC* pDC = GetDesktopWindow()->GetDC();

	//创建一张位图
	CBitmap bmp;
	bmp.CreateCompatibleBitmap(pDC, _width, _height);
	
	//创建内存DC
	_memDC.CreateCompatibleDC(pDC);
	_memDC.SelectObject(&bmp);
	_memDC.BitBlt(0, 0, _width, _height, pDC, 0, 0, SRCCOPY);

	//释放桌面DC
	pDC->DeleteDC();
	bmp.DeleteObject();
}

CShowDlg::~CShowDlg()
{
}

void CShowDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CShowDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
END_MESSAGE_MAP()


// CShowDlg 消息处理程序


BOOL CShowDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	//调整窗口大小
	MoveWindow(0, 0, _width, _height);

	//初始化橡皮筋
	_tracker.m_nStyle = CRectTracker::dottedLine | CRectTracker::resizeInside;//样式风格
	_tracker.m_nHandleSize = 5;//手柄大小
	_tracker.m_rect.SetRect(0, 0, 0, 0);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CShowDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CDialogEx::OnPaint()
	//将_memDC显示到屏幕上
	dc.BitBlt(0, 0, _width, _height, &_memDC, 0, 0, SRCCOPY);
	
	//画橡皮筋
	_tracker.Draw(&dc);
}


void CShowDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (_tracker.HitTest(point) < 0)
	{
		_tracker.TrackRubberBand(this, point, TRUE);
		_tracker.m_rect.NormalizeRect();
	}
	else
	{
		_tracker.Track(this, point, TRUE);
		_tracker.m_rect.NormalizeRect();
	}
	Invalidate(FALSE);
	CDialogEx::OnLButtonDown(nFlags, point);
}


void CShowDlg::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	//获取橡皮筋的宽和高
	int width = _tracker.m_rect.Width();
	int height = _tracker.m_rect.Height();

	//创建一个位图存取截图图片
	CBitmap bmp;
	bmp.CreateCompatibleBitmap(&_memDC, width, height);

	//创建临时内存DC
	CDC memDC;
	memDC.CreateCompatibleDC(NULL);
	memDC.SelectObject(&bmp);

	//复制橡皮筋内容给临时DC
	memDC.BitBlt(0, 0, width, height, &_memDC, _tracker.m_rect.left, _tracker.m_rect.top, SRCCOPY);

	//打开剪切板
	OpenClipboard();
	//清空剪切板
	EmptyClipboard();
	//设置剪切板数据
	SetClipboardData(CF_BITMAP, bmp);
	//关闭剪切板
	CloseClipboard();

	//保存到文件夹
	CTime t = CTime::GetCurrentTime();
	srand(time(NULL));
	int randNum = rand() % 900 + 100;
	CString strPicName;
	strPicName.Format(L".\\%s%d.png", t.Format(L"%Y%m%d%H%M%S"), randNum);
	CImage img;
	img.Attach(bmp);
	img.Save(strPicName);
	img.Detach();

	//释放内存
	memDC.DeleteDC();
	bmp.DeleteObject();
	_memDC.DeleteDC();

	//关闭对话框
	EndDialog(IDCANCEL);

	CDialogEx::OnLButtonDblClk(nFlags, point);
}
