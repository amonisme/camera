
// cameraDlg.cpp : 实现文件
//

#include "stdafx.h"
#include"resource.h"
#include "camera.h"
#include "cameraDlg.h"
#include "afxdialogex.h"
#include <time.h>
#include <direct.h>
#include <windows.h>
#include <iostream>
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CvCapture* capture;
CRect rect;
CDC *pDC;
HDC hDC;
CWnd *pwnd;
int flag = 0;

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CcameraDlg 对话框



CcameraDlg::CcameraDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CcameraDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CcameraDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CcameraDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CcameraDlg::OnBnClickedRecord)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON2, &CcameraDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CcameraDlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// CcameraDlg 消息处理程序

BOOL CcameraDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{   
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	ShowWindow(SW_MAXIMIZE);

	// TODO:  在此添加额外的初始化代码
	pwnd = GetDlgItem(IDC_ShowImage);
	//pwnd->MoveWindow(35,30,352,288);  
	pDC = pwnd->GetDC();
	//pDC =GetDC();  
	hDC = pDC->GetSafeHdc();
	pwnd->GetClientRect(&rect);


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CcameraDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CcameraDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CcameraDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CcameraDlg::OnBnClickedRecord()
{
	// TODO:  在此添加控件通知处理程序代码
	//AfxMessageBox("OK");  
	if (!capture)
	{
		capture = cvCaptureFromCAM(0);
		//AfxMessageBox("OK");  
	}

	if (!capture)
	{
		AfxMessageBox(_T("无法打开摄像头"));
		return;
	}

	// 测试  
	IplImage* m_Frame;
	m_Frame = cvQueryFrame(capture);//cvQueryFrame从摄像头或者文件中抓取并返回一帧
	CvvImage m_CvvImage;
	m_CvvImage.CopyOf(m_Frame, 3); //将m_Frame复制到当前对象中，复制后图像的通道为3，即RGB
	if (true)
	{
		m_CvvImage.DrawToHDC(hDC, &rect);
		//cvWaitKey(10); 
	}

	// 设置计时器,每10ms触发一次事件  
	SetTimer(1, 10, NULL);
}


void CcameraDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值

	CDialogEx::OnTimer(nIDEvent);
	/************************************************************************/
	/* 显示摄像头                                                           */
	/************************************************************************/
	IplImage* m_Frame;
	m_Frame = cvQueryFrame(capture);
	CvvImage m_CvvImage;
	m_CvvImage.CopyOf(m_Frame, 1);

	IplImage* img = 0;
	char image_name[25];
	if (capture)
	{
		m_CvvImage.DrawToHDC(hDC, &rect);
		SaveImg(m_Frame,0);
		//char key = cvWaitKey(2000);
	}

}

void CcameraDlg::OnBnClickedButton2()
{
	// TODO:  在此添加控件通知处理程序代码
	cvReleaseCapture(&capture);
	/*CDC MemDC;
	CBitmap m_Bitmap1;
	//m_Bitmap1.LoadBitmap(_T("IDB_BITMAP1"));
	MemDC.CreateCompatibleDC(NULL);
	//MemDC.SelectObject(&m_Bitmap1);
	pDC->StretchBlt(rect.left, rect.top, rect.Width(), rect.Height(), &MemDC, 0, 0, 48, 48, SRCCOPY);*/
}


void CcameraDlg::OnBnClickedButton3()
{
	// TODO:  在此添加控件通知处理程序代码
	IplImage* m_Frame;
	m_Frame = cvQueryFrame(capture);
	CvvImage m_CvvImage;
	m_CvvImage.CopyOf(m_Frame, 1);
	SaveImg(m_Frame, 1);
}

int CcameraDlg::SaveImg(Mat mat, int flag)
{
	//flag=1 不新建文件夹；flag=0新建文件夹
	char path[100] = "F:\\pic\\";
	time_t t = time(0);
	char tmp[64];
	strftime(tmp, sizeof(tmp), "%Y%m%d", localtime(&t));
	strcat(path, tmp);
	if (0 == flag && (_access(path, 0) == -1))
	{
		_mkdir(path);
	}
	else if (1 == flag)
	{
		strcat(path, "\\手工截图");
		_mkdir(path);
	}
	_mkdir(path);
	strftime(tmp, sizeof(tmp), "%H_%M_%S", localtime(&t));
	strcat(path, "\\");
	strcat(path, tmp);
	strcat(path, ".jpg");
	int save = cv::imwrite(path, mat);
	cout << path << (save ? " Saved!" : "Can't be saved") << endl;
	//imwrite(fileName,img);
	return save;
}
