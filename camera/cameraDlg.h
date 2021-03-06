
// cameraDlg.h : 头文件
//

#pragma once
#include "cv.h"
#include "highgui.h"
#include "CvvImage.h"
#include <io.h>
using namespace cv;

// CcameraDlg 对话框
class CcameraDlg : public CDialogEx
{
// 构造
public:
	CcameraDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_CAMERA_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedRecord();
	afx_msg int SaveImg(Mat mat, int flag);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
};
