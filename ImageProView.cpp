
// ImageProView.cpp: CImageProView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "ImagePro.h"
#endif

#include "ImageProDoc.h"
#include "ImageProView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CImageProView

IMPLEMENT_DYNCREATE(CImageProView, CScrollView)

BEGIN_MESSAGE_MAP(CImageProView, CScrollView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CImageProView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_PIXEL_ADD, &CImageProView::OnPixelAdd)
	ON_COMMAND(ID_PIXEL_SUB, &CImageProView::OnPixelSub)
	ON_COMMAND(ID_PIXEL_MUL, &CImageProView::OnPixelMul)
	ON_COMMAND(ID_PIXEL_DIV, &CImageProView::OnPixelDiv)
	ON_COMMAND(ID_BINARY, &CImageProView::OnBinary)
	ON_COMMAND(ID_EXAM1, &CImageProView::OnExam1)
	ON_COMMAND(ID_Exam2, &CImageProView::OnExam2)
END_MESSAGE_MAP()

// CImageProView 생성/소멸

CImageProView::CImageProView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CImageProView::~CImageProView()
{
}

BOOL CImageProView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CScrollView::PreCreateWindow(cs);
}

// CImageProView 그리기

void CImageProView::OnDraw(CDC* pDC)
{
	CImageProDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	for (int y = 0; y < 256; y++)
		for (int x = 0; x < 256; x++)
			pDC->SetPixel(x, y, RGB(pDoc->InputImg[y][x], pDoc->InputImg[y][x], pDoc->InputImg[y][x]));

	for (int y = 0; y < 256; y++)
		for (int x = 0; x < 256; x++)
			pDC->SetPixel(x+300, y, RGB(pDoc->ResultImg[y][x], pDoc->ResultImg[y][x], pDoc->ResultImg[y][x]));
}

void CImageProView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: 이 뷰의 전체 크기를 계산합니다.
	sizeTotal.cx = 640;
	sizeTotal.cy = 480;
	SetScrollSizes(MM_TEXT, sizeTotal);
}


// CImageProView 인쇄


void CImageProView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CImageProView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CImageProView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CImageProView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

void CImageProView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CImageProView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CImageProView 진단

#ifdef _DEBUG
void CImageProView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CImageProView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CImageProDoc* CImageProView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CImageProDoc)));
	return (CImageProDoc*)m_pDocument;
}
#endif //_DEBUG


// CImageProView 메시지 처리기

void CImageProView::OnPixelAdd()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->PixelAdd();

	Invalidate(FALSE);
}

void CImageProView::OnPixelSub()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->PixelSub();

	Invalidate(FALSE);
}

void CImageProView::OnPixelMul()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->PixelMul();

	Invalidate(FALSE);
}

void CImageProView::OnPixelDiv()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->PixelDiv();

	Invalidate(FALSE);
}

void CImageProView::OnBinary()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->Binary();

	Invalidate(FALSE);
}

void CImageProView::OnExam1()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->Exam1();

	Invalidate(FALSE);
}

void CImageProView::OnExam2()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->Exam2();

	Invalidate(FALSE);
}
