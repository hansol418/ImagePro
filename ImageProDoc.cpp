
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

void CImageProDoc::Exam3()
{
	// TODO: 여기에 구현 코드 추가.
	for (int x = 0; x < 256; x++) {
		for (int y = 0; y < 256; y++) {
			ResultImg[x][y] = InputImg[x][y];
		}
	}
	for (int x = 0; x < 5; x++) {
		for (int y = 60; y < 200; y++) {
			ResultImg[20 + x][y] = 255;
			ResultImg[50 - x][y] = 255;
		}
	}
	for (int y = 0; y < 5; y++) {
		for (int x = 20; x < 50; x++) {
			ResultImg[x][60 + y] = 255;
			ResultImg[x][200 - y] = 255;
		}
	}
	
}

void CImageProDoc::LoadTwoImages()
{
	// TODO: 여기에 구현 코드 추가.
	CFile file;	//CFile 객체 선언
	CFileDialog dlg(TRUE);	// 파일 선택 대화상자 객체 선언
							// TRUE:파일 열기
							// FLASE:파일 저장

	AfxMessageBox(L"첫 번째 영상파일을 선택하세요!");

	if (dlg.DoModal() == IDOK) {	//파일 선택 대화 상자 실행
		file.Open(dlg.GetPathName(), CFile::modeRead);	//파일 열기
		file.Read(InputImg, 256 * 256);	//영상 읽기
		file.Close();	//파일 닫기
	}

	AfxMessageBox(L"두 번째 영상파일을 선택하세요!");

	if (dlg.DoModal() == IDOK) {	//파일 선택 대화 상자 실행
		file.Open(dlg.GetPathName(), CFile::modeRead);	//파일 열기
		file.Read(InputImg2, 256 * 256);	//영상 읽기
		file.Close();	//파일 닫기
	}
}

void CImageProDoc::Two_Image_Add()
{
	// TODO: 여기에 구현 코드 추가.
	LoadTwoImages();

	int data = 0;

	for(int x = 0; x< 256; x++)
		for (int y = 0; y < 256; y++) 
		{
			data = InputImg[x][y] + InputImg2[x][y];

			if (data > 255)
				ResultImg[x][y] = 255;
			else
				ResultImg[x][y] = data;

		}
}

void CImageProDoc::Two_Image_Sub()
{
	// TODO: 여기에 구현 코드 추가.
	LoadTwoImages();

	int data = 0;

	for (int x = 0; x < 256; x++)
		for (int y = 0; y < 256; y++)
		{
			data = InputImg[x][y] - InputImg2[x][y];

			if (data < 0)
				ResultImg[x][y] = 0;
			else
				ResultImg[x][y] = data;

		}
}

void CImageProDoc::Two_Image_Mul()
{
	// TODO: 여기에 구현 코드 추가.
	LoadTwoImages();

	int data = 0;

	for (int x = 0; x < 256; x++)
		for (int y = 0; y < 256; y++)
		{
			data = InputImg[x][y] | InputImg2[x][y];

			if (data > 255)
				ResultImg[x][y] = 255;
			else
				ResultImg[x][y] = data;

		}
}

void CImageProDoc::Two_Image_Div()
{
	// TODO: 여기에 구현 코드 추가.
	LoadTwoImages();

	int data = 0;

	for (int x = 0; x < 256; x++)
		for (int y = 0; y < 256; y++)
		{
			if (InputImg2[x][y] == 0) 
			{
				ResultImg[x][y] = InputImg[x][y];
			}
			else
			{
				ResultImg[x][y] = InputImg[x][y] / InputImg2[x][y];
			}
			
		}
}

void CImageProDoc::Histogram()
{
	// TODO: 여기에 구현 코드 추가.
	int k, value, m = 0;
	int histo[256];
	int temp[256][256];

	for (int z = 0; z < 256; z++) 
	{
		histo[z] = 0;
		for (int w = 0; w < 256; w++)
			temp[z][w] = 0;
	}

	for(int x=0; x<256; x++)
		for (int y = 0; y < 256; y++)
		{
			k = InputImg[x][y];
			histo[k] = histo[k] + 1;
		}
	for (int x = 0; x < 256; x++)
	{
		value = histo[x] / 5;

		if (value > 255)
			value = 255;

		for (int y = 0; y < value; y++)
			temp[y][x] = 128;
	}

	for(int x = 0; x < 256; x++)
		for (int y = 0; y < 256; y++)
		{
			m = (255 - x);
			ResultImg[m][y] = temp[x][y];
		}
}

void CImageProDoc::Histo_Strech()
{
	// TODO: 여기에 구현 코드 추가.
	int max = 255;
	int k, min = 0;
	int histo[256];

	for (int z = 0; z < 256; z++)
		histo[z] = 0;

	for (int x = 0; x < 256; x++)
		for (int y = 0; y < 256; y++)
		{
			k = InputImg[x][y];
			histo[k] = histo[k] + 1;
		}

	for (int z = 0; z < 256; z++)
	{
		if (histo[z])
		{
			min = z;
			break;
		}
	}

	for (int z = 255; z > 0; z--)
	{
		if (histo[z])
		{
			max = z;
			break;
		}
	}

	for (int x = 0; x < 256; x++)
		for (int y = 0; y < 256; y++)
		{
			ResultImg[x][y] = ((InputImg[x][y] - min) * 255) / (max - min);
		}
}
