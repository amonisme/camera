
// cameraDlg.h : ͷ�ļ�
//

#pragma once
#include "cv.h"
#include "highgui.h"
#include "CvvImage.h"
#include <io.h>
using namespace cv;

// CcameraDlg �Ի���
class CcameraDlg : public CDialogEx
{
// ����
public:
	CcameraDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_CAMERA_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
