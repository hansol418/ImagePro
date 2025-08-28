
// ImageProDoc.cpp: CImageProDoc 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "ImagePro.h"
#endif

#include "ImageProDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CImageProDoc

IMPLEMENT_DYNCREATE(CImageProDoc, CDocument)

BEGIN_MESSAGE_MAP(CImageProDoc, CDocument)
END_MESSAGE_MAP()


// CImageProDoc 생성/소멸

CImageProDoc::CImageProDoc() noexcept
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.

}

CImageProDoc::~CImageProDoc()
{
}

BOOL CImageProDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.

	return TRUE;
}




// CImageProDoc serialization

void CImageProDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring() == TRUE)
	{
		ar.Write(ResultImg, 256 * 256);
	}
	else
	{
		CFile* fp = ar.GetFile();
		if (fp->GetLength() == 256 * 256) 
		{
			ar.Read(InputImg, 256 * 256);
		}			
		else 
		{
			AfxMessageBox(L"256X256 크기의 파일만 사용가능합니다.");
		}			
	}
}

#ifdef SHARED_HANDLERS

// 축소판 그림을 지원합니다.
void CImageProDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 문서의 데이터를 그리려면 이 코드를 수정하십시오.
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 검색 처리기를 지원합니다.
void CImageProDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CImageProDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CImageProDoc 진단

#ifdef _DEBUG
void CImageProDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CImageProDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CImageProDoc 명령

void CImageProDoc::PixelAdd()
{
	// TODO: 여기에 구현 코드 추가.
	int Value = 0;

	for(int x=0; x<256; x++)
		for (int y = 0; y < 256; y++) 
		{
			Value = InputImg[x][y] + 100;
			if (Value > 255) 
				ResultImg[x][y] = 255;
			else 
				ResultImg[x][y] = Value;
		}

	/*for (int x = 0; x < 256; x++)
		for (int y = 0; y < 256; y++)
		{
			ResultImg[x][y] = InputImg[x][y] = 100;
		}*/
}

void CImageProDoc::PixelSub()
{
	// TODO: 여기에 구현 코드 추가.
	int Value = 0;

	for (int x = 0; x < 256; x++)
		for (int y = 0; y < 256; y++)
		{
			Value = InputImg[x][y] - 50;
			if (Value < 0)
				ResultImg[x][y] = 0;
			else
				ResultImg[x][y] = Value;
		}
}

void CImageProDoc::PixelMul()
{
	// TODO: 여기에 구현 코드 추가.
	int Value = 0;

	for (int x = 0; x < 256; x++)
		for (int y = 0; y < 256; y++)
		{
			Value = InputImg[x][y] * 1.5;
			if (Value > 255)
				ResultImg[x][y] = 255;
			else
				ResultImg[x][y] = Value;
		}
}

void CImageProDoc::PixelDiv()
{
	// TODO: 여기에 구현 코드 추가.
	

	for (int x = 0; x < 256; x++)
		for (int y = 0; y < 256; y++)
			ResultImg[x][y] = InputImg[x][y] / 1.5;
}

void CImageProDoc::Binary()
{
	// TODO: 여기에 구현 코드 추가.
	for (int x = 0; x < 256; x++)
		for (int y = 0; y < 256; y++)
			if (InputImg[x][y] < 127)
				ResultImg[x][y] = 0;
			else
				ResultImg[x][y] = 255;
}

void CImageProDoc::Exam1()
{
	// TODO: 여기에 구현 코드 추가.
	for(int x = 0; x < 256; x++)
		for(int y = 0; y < 256; y++)
			ResultImg[x][y] = InputImg[x][y];

	for(int x=20; x<50; x++)
		for(int y=64; y<192; y++)
			ResultImg[x + 30][y] = InputImg[x][y];
}

void CImageProDoc::Exam2()
{
	// TODO: 여기에 구현 코드 추가.
	for (int x = 0; x < 256; x++)
		for (int y = 0; y < 256; y++)
			ResultImg[x][y] = InputImg[x][y];

	for (int x = 20; x < 50; x++)
		for (int y = 64; y < 192; y++)
			ResultImg[x + 30][y] = InputImg[69 - x][y];
}
