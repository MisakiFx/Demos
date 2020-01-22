#pragma once


// CShowDlg 对话框

class CShowDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CShowDlg)

public:
	CShowDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CShowDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SHOW_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
private:
	int _width;				//屏幕的宽
	int _height;			//屏幕的高
	CDC _memDC;				//内存DC
	CRectTracker _tracker;	//橡皮筋
public:
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
};
