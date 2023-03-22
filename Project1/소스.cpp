 #include <windows.h>
#include <stdio.h>
#include "resource.h"
#include<math.h>
#include <mmsystem.h>
#include <Digitalv.h>//mciSendCommand
#include <stdlib.h>
#include <time.h>
#pragma comment(lib, "msimg32.lib")
#pragma comment (lib, "winmm.lib")


#define SPEED 5
#define NPCSPEED 15
#define FONTSIZE 40

MCI_PLAY_PARMS playBgm;
MCI_OPEN_PARMS openBgm;
static int dwID;


int Endingx = 0, Endingy = 0;

int x = 1000, y = 300;

RECT prt = { x, y + 100, x + 92, y + 160 };

RECT grt = { 170, 580, 1120, 1000 }, nrt = { 190, 505, 1120, 1000 };

HWND hWndMain;
HBITMAP hBit, P_Bit[4], P_IllBit[10];	//주인공

HBITMAP NPC1Bit[5], N1_IllBit[10];		//NPC1관련

HBITMAP NPC2Bit[5], N2_IllBit[10];		//NPC2관련

HBITMAP NPC3Bit[5], N3_IllBit[10];		//NPC3관련

HBITMAP NPC4Bit[5], N4_IllBit[10];		//NPC4관련

HBITMAP BokDoBit[5], LeftDoorBit[2], RightDoorBit[2];		//배경관련

HBITMAP TextBox[2], System[1], DiaryBit, MapBit, DayBit, DayCheckBit, MusicBit, ChoiceBit, SelectBit, EndDiaryBit, ArrowBit, TitleBit, BoomBit, OptionBit;		//UI관련


//오브젝트
HBITMAP SkeletonBit, SchoolDeskBit[4], BoardBit, BoxBit[3], ChairBit[5], PianoBit, BedBit, LectureTableBit,
LockerBit, OfficeDeskBit, CabinetBit, OfficeDeskBit2, IronBarBit[2], KeyBit, LockBit, LockPWBit, ClockBit, TimeBit;

//기타
HBITMAP Black[2], SeeBit;

//엔딩
HBITMAP Ending[10];


const TCHAR *name = TEXT("똘똘이");		//이름
const TCHAR* text = TEXT("이건 어떻게 하죠");		//내용
const TCHAR* ttext = TEXT("");		//내용 뒤에

const TCHAR* DayText = TEXT("");		//일기장 날짜

const TCHAR* MusicText = TEXT("악보");		//악보 글자

const TCHAR* DiaryText1 = TEXT("x월 1일\n오늘은 피아노가 치고 싶다. "
	"그러나 친구들은 날 내버려두지 않는다.\n 얘들이 재밌는 걸 보여준다면서 창고로 오라고 하였다.\n"
	"창고에 도착하니 친구들은 담배를 꺼내서 피기 시작했다.\n"
	"선생님들 몰래 담배를 피우는게 괜찮을까?\n 이런 짓을 해도 되는지 모르겠지만 그래도 친구니까..");	
//일기장1
const TCHAR* DiaryText2 = TEXT("5월 2일\n"
	"친구들에게 담배를 피며 나에게 담배 1대를 권하길래 담배는 좋지 않은 것 같다고 말을 꺼냈다가 남자 주제에 패기가 없다고 놀림을 받았다."
	"무시 받는게 싫어 “그냥 장난으로 꺼내 본 말이야”하고 넘겼다."
	"그런데 정해진 규칙을 어기는게 괜찮은 걸까 ?\n\n"

	"5월 3일\n"
	"학교에서 흡연 실태 조사를 설문지로 하였다."
	"아무래도 잘못된 행동이니까 친구들 3명 모두 흡연 사실을 적었다."
	"별 문제 없겠지?\n\n"

	"5월 4일\n"
	"기석이, 승찬이, 우진이가 교무실에서 선생님한테 5대씩 맞으며 혼나는 장면을 보았다."
	"이 참에 정신차리고 학생답게 열심히 공부했으면 좋겠다....\n\n"

	"5월 5일\n"
	"2시에 갑자기 선생님이 나를 교무실로 부르셨다….뒷이야기는 차마 일기장에 적진 못할 것 같다……");
//일기장2
const TCHAR* DiaryText3 = TEXT("5월 6일\n"
	"친구들이 나를 보는 눈빛들이 이상하다.\n"
	"제발... 기분 탓이기를....\n\n"

	"5월 8일\n"
	"오늘은               로 날씨가 좋았지만 나는 친구들에게 골목으로 끌려가 죽도록 맞았다...\n"
	"골목으로 지나가는 친구들이 있어 도와줬으면 했지만 모두 못 볼 걸 본 듯 빠르게 지나갔다.\n"
	"그렇게 정신을 차려 보니 애들은 모두 가고 해는 지고 있었다.\n");
//일기장3
const TCHAR* DiaryText4 = TEXT("5월 27일\n"
	"친구가 없어진 나는 심심해 종이로                 를 만들었다.\n"
	"물론 그것도 친구들이 보자 마자 발로 밟아 없애 버려 너무 서운하다.\n"
	"어쩌다 이렇게 된 걸까... 우리들은 친했었는데...");
//일기장4

const TCHAR* DiaryText5 = TEXT("9월 1일\n"
	"친구들의 폭력은 날이 갈수록 심해져 간다.\n"
	"여름방학에도 우리 집까지 찾아와 나를 때리기도 했다.\n"
	"아버지는 매일 술만 마시며 내 얼굴에 있는 상처에 관심조차 없으셔...\n 나 혼자 해결해야 해.\n\n"

	"9월 2일\n"
	"도현이가 학교에서 내게 말을 걸었다.\n"
	"뭐 ? 괜찮냐고 ? 이제 와서 ? 방관하는 것도 결국엔 너도 똑같은 가해자야!\n\n"

	"9월 4일\n"
	"이대로 가만히 있다간 무슨 일이 일어날지 모른다.\n"
	"집 뒤에 아무도 찾지 않는 산에 혼자 올라가                     를 보며 생각을 해 봤다.\n"
	"먼저...먼저 무슨 수를 써야해!\n\n"

	"9월 21일\n");
//일기장5

const TCHAR* DiaryText6 = TEXT("10월 3일\n"
	"실행하기에 앞서 애들의 정보를 모아보았다.\n"
	"기석 - 가족구성원 : 엄마, 아빠, 형\n"
	"시간과 동선 : 학교를 마치고 5시에 수학학원을 가며 10시에 집에 도착\n\n"

	"승찬 - 가족구성원 : 새엄마, 배 다른 누나\n"
	"가족과 사이가 안 좋아 보임\n"
	"시간과 동선 : 학교를 마치고 친구들과 자주 놀러 다녀 집에 늦게 들어감\n\n"

	"우진 - 가족구성원 : 아빠, 엄마, 형, 할머니\n"
	"시간과 동선 : 학교를 마치고 바로 집으로 귀가함\n\n"

	"10월 11일\n"
	"해냈다...우리집 뒷산 아무도 오지 않는 오두막에 시체를 숨기고 왔다.....\n\n"

	"10월 14일\n"
	"승찬이가 학교를 연속결석하자 도현이가 나의 안부와 승찬이의 대해 아는게 없냐고 물었다.\n"
	"미안 도현아 되돌리기엔 이미 너무 늦었어...\n\n");
//일기장6

const TCHAR* DiaryText7 = TEXT("어쩌다 이런 일이.. 나도 이러고 싶지 않았어.\n"
	"그저 평범하게 학교를 다니고 싶었을 뿐이라고...");
//일기장7




const TCHAR* EndingCredit = TEXT("THE END\n\n\n"
	"기획\n"
	"황병철\n"
	"이후겸\n\n"
	"프로그래밍\n"
	"성기정\n"
	"조남진\n"
	"이새롬\n\n"
	"그래픽\n"
	"박진희\n"
	"정희권\n"
	"안상혁\n");
//엔딩크레딧



bool direction = true, directionY = true;

bool Titleint = true;

int stage = 34, NPCstage1 = 51, NPCstage2 = 51, NPCstage3 = 51, NPCstage4 = 51;

int NPC1x = 170, NPC1y = 520;		//이수현
int NPC2x = 470, NPC2y = 500;		//김화진
int NPC3x = 770, NPC3y = 520;		//김미진
int NPC4x = 1070, NPC4y = 520;		//정수희

int pfrm = 0;			// 프레임
int dfrm = 0;			//죽는모션 프레임

int pwfrm1 = 0, pwfrm2 = 0, pwfrm3 = 0, pwfrm4 = 0;		//비밀번호 추리

bool stop = true;		// 플레이어가 정지해있을 때 (강제 정지 X)

bool Stop = false;		// 플레이어가 정지하게 함 (강제 정지 O)

int Time = -1;			// 시간 체크

int MaxX1, MaxY1, MaxX2, MaxY2;				// 플레이어 이동 제한

bool NPC1stop = true, NPC2stop = true, NPC3stop = true, NPC4stop = true;		// NPC 따라오게할지말지

bool NPC1int = false, NPC2int = false, NPC3int = false, NPC4int = false;		// NPC 상호작용 체크

int page = 0;		// 대화창


//대화 하게 만들기
bool MainDoorint = false, Skeletonint = false, SchoolDesk1int = false, SchoolDesk2int = false, SchoolDesk3int = false,
Diaryint = false, CloseDoorint = false, Boardint = false, Openint = false, Boxint = false, RealBox = false, Dayint = false, FakeBox = false, FakeBoxint = false,
Pianoint = false, FirstReadint = false, Startint = false, Prisonint = false, Keyint = false, Lelaint = false, Healint = false, HHealint = false, CloseDoor2int = false,
Boomint = false, BokDoBoxint = false, EndPianoint = false, Endingint = false;



int OpenDoor = 0, Class4Door = 0, BedDoor = 0, HealDoor = 0, Class2Door = 0, Door = 0, Class1Door = 0;		//문 열리게할지말지

int Inventory = -1, Map = -1, DayCheck = 0, DayCheckBar = 1, PianoMusic = -1, Choose = -1, SelectButton = -1, BGMCheck = 1;			//활성화 체크

double FirstRead = 0;	//처음 읽은거 체크

int PWCheck[4] = { 1, 3, 5, 2 }, PWCheck2[4] = { 5, 6, 5, 3 }, PWCheck3[4] = { 6, 1, 2, 5 }, PWCheck4[4] = { 5, 3, 1, 5 }, PWCheck5[4] = { 1, 0, 1, 1 };//비밀번호 체크

int hint = 0;	//힌트

int Choice = 1, Select = 1;		//선택

//일회용 변수들
bool PWDoor44 = false;		//교무실 비밀번호 방 활성화
int pw[4];
int Dap = 0;		// 비밀번호 맞췄을 경우
int Sound = 0;		//효과음 내기
int KeyCheck = 0;	//감옥열쇠 가지고있는지 체크

int NPCFree = 0;	//NPC해방

int lela = 0;		//신데렐라 체크
int Command = -5;	//커맨드 받는 변수
int boom = 0;		//방에 처음 들어가는거 체크
int BokDoBoxCheck = -1;	//복도박스 확인했는지 체크
int BoomPW = -1;		//폭탄 비번
int Free = 0;		//NPC폭탄 해체 성공 여부
int Push = 0;		//폭탄 키패드 누른 여부

int NPCDie = 0;		//NPC 죽은거 확인

int bandal = 0;			//마지막 피아노
int GunBan[15] = { 5,6,5,3,5,3,1,5,6,1,2,5,3 };		//정답
int GGunBan[15];
int ScanGunBan = 0;					//건반 입력하는 변수
int SpaceStop = 0;				//스페이스바 못누르게 하는 변수

int TitleSelect = 1;		//타이틀 화살표
int OptionSelect = 1;		//옵션 화살표
bool OptionCheck = 0;		//옵션 켜져있는지 확인





int Boon = 5;		//시간 체크
int Cho1 = 0;		//10의 자리
int Cho2 = 0;		//1의 자리




LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("제노비스 신드롬");

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance
	, LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst = hInstance;

	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = WndProc;
	WndClass.lpszClassName = lpszClass;
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&WndClass);

	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPED | WS_SYSMENU,
		//CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		320,150,1280,750,
		NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);

	hWndMain = hWnd;

	while (GetMessage(&Message, NULL, 0, 0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return (int)Message.wParam;
}
// WINDOWS API
double LengthPts(int x1, int y1, int x2, int y2)     //점과 점사이 거리 구하는 공식
{
	return(sqrt((float)((x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1))));
}	
// 점과 점사이의 거리 구하는 공식
BOOL InCircle(int x, int y, int nx, int ny , HBITMAP hBit) // x, y는 원의 중심 mx, my는 클릭한 지점
{
	BITMAP bit;
	int BSIZE = 100;
	int ix = 0;
	int iy = 0;
	GetObject(hBit, sizeof(BITMAP), &bit);
	ix = bit.bmWidth / 2;
	iy = bit.bmHeight / 2;

	/*if (iy + ix >= 140)		// 사람
	{
		BSIZE = 50;
	}
	if (iy + ix <= 100)		//상자
	{
		BSIZE = 50;
	}*/
	if (LengthPts(x + 45, y + 100, nx + ix, ny + iy) < BSIZE)return TRUE;
	else return FALSE;
}
// 원 충돌 판정
BOOL CheckPtInRect(HBITMAP hBit, int Obitx, int Obity, HBITMAP Pbit, int Pbitx, int Pbity) //저장할 좌표, 위치, 비트맵, 비트맵 위치
{
	int ox, oy;
	int px, py;
	BITMAP Obit, Pl_bit;
	RECT Temp, O_bit, P_bit;


	GetObject(hBit, sizeof(BITMAP), &Obit);
	ox = Obit.bmWidth;
	oy = Obit.bmHeight;

	O_bit.top = Obity;
	O_bit.left = Obitx;
	O_bit.right = Obitx + ox;
	O_bit.bottom = Obity + oy;

	GetObject(Pbit, sizeof(BITMAP), &Pl_bit);
	px = Pl_bit.bmWidth;
	py = Pl_bit.bmHeight;

	P_bit.top = Pbity;//+ 70;
	P_bit.left = Pbitx;//+ 10;
	P_bit.right = Pbitx + px;// -10;
	P_bit.bottom = Pbity + py;

	if (IntersectRect(&Temp, &O_bit, &P_bit))
	{
		return true;
	}
	else
	{
		return false;
	}

}
//사각형 충돌
BOOL CCheckPtInRect(HBITMAP hBit, int Obitx, int Obity) //저장할 좌표, 위치, 비트맵, 비트맵 위치
{
	int ox, oy;
	int px, py;
	BITMAP Obit, Pl_bit;
	RECT Temp, O_bit, P_bit;


	GetObject(hBit, sizeof(BITMAP), &Obit);
	ox = Obit.bmWidth;
	oy = Obit.bmHeight;

	O_bit.top = Obity - 20;
	O_bit.left = Obitx - 20;
	O_bit.right = Obitx + ox + 20;
	O_bit.bottom = Obity + oy + 20;

	GetObject(P_Bit[0], sizeof(BITMAP), &Pl_bit);
	px = Pl_bit.bmWidth;
	py = Pl_bit.bmHeight;

	P_bit.top = y + 70;
	P_bit.left = x + 10;
	P_bit.right = x + px - 10;
	P_bit.bottom = y + py;

	if (IntersectRect(&Temp, &O_bit, &P_bit))
	{
		return true;
	}
	else
	{
		return false;
	}

}
//상호작용 충돌
void Cresh(HBITMAP obit, int ox, int oy, int ostage)
{
	if (direction)
	{
		if (CheckPtInRect(obit, ox, oy, P_Bit[0], x, y) && x >= ox && stage == ostage)
		{
			if (MaxX2 > x)
			{
				x += SPEED;
			}
		}
	}
	else if (!direction)
	{
		if (CheckPtInRect(obit, ox, oy, P_Bit[0], x, y) && x <= ox && stage == ostage)
		{
			if (MaxX1 < x)
			{
				x -= SPEED;
			}
		}
	}

	if (directionY)
	{
		if (CheckPtInRect(obit, ox, oy, P_Bit[0], x, y) && y > oy && stage == ostage)
		{
			if (MaxY2 > y)
			{
				y += SPEED;
			}
		}
	}
	else if (!directionY)
	{
		if (CheckPtInRect(obit, ox, oy, P_Bit[0], x, y) && y < oy && stage == ostage)
		{
			if (MaxY1 < y)
			{
				y -= SPEED;
			}
		}
	}
}
//오브젝트 충돌
void TransBlt(HDC hdc, int x, int y, HBITMAP hbitmap, COLORREF clrMask)
{

	BITMAP bm;
	HDC hMemDC;
	POINT ptSize;
	HBITMAP hOldBitmap;

	hMemDC = CreateCompatibleDC(hdc);
	hOldBitmap = (HBITMAP)SelectObject(hMemDC, hbitmap);
	GetObject(hbitmap, sizeof(BITMAP), (LPSTR)&bm);
	ptSize.x = bm.bmWidth;
	ptSize.y = bm.bmHeight;

	TransparentBlt(hdc, x, y, ptSize.x, ptSize.y, hMemDC, 0, 0, ptSize.x, ptSize.y, clrMask);

	SelectObject(hMemDC, hOldBitmap);
	DeleteDC(hMemDC);
}
// 배경 지워서 그리기
void MoveTransBlt(HDC hdc, int x, int y, HBITMAP hbitmap, COLORREF clrMask, int frm)
{
	BITMAP bm;
	HDC hMemDC;
	POINT ptSize;
	HBITMAP hOldBitmap;

	hMemDC = CreateCompatibleDC(hdc);
	hOldBitmap = (HBITMAP)SelectObject(hMemDC, hbitmap);
	GetObject(hbitmap, sizeof(BITMAP), (LPSTR)&bm);
	ptSize.x = bm.bmWidth;
	ptSize.y = bm.bmHeight;
	

	if (hbitmap == NPC2Bit[2] || hbitmap == NPC2Bit[3])
	{
		TransparentBlt(hdc, x, y, 110, 170, hMemDC, frm * 110, 0, 110, ptSize.y, clrMask);
	}
	else
	{
		TransparentBlt(hdc, x, y, 92, 160, hMemDC, frm * 92, 0, 92, ptSize.y, clrMask);
	}
	
	SelectObject(hMemDC, hOldBitmap);
	DeleteDC(hMemDC);
}
// 움직이는 물체 배경 지워서 그리기
void PWTransBlt(HDC hdc, int x, int y, HBITMAP hbitmap, COLORREF clrMask, int frm)
{
	BITMAP bm;
	HDC hMemDC;
	POINT ptSize;
	HBITMAP hOldBitmap;

	hMemDC = CreateCompatibleDC(hdc);
	hOldBitmap = (HBITMAP)SelectObject(hMemDC, hbitmap);
	GetObject(hbitmap, sizeof(BITMAP), (LPSTR)&bm);
	ptSize.x = bm.bmWidth;
	ptSize.y = bm.bmHeight;


	TransparentBlt(hdc, x, y, 85, 30, hMemDC, frm * 85, 0, 85, ptSize.y, clrMask);



	SelectObject(hMemDC, hOldBitmap);
	DeleteDC(hMemDC);
}
//자물쇠비번 배경지워서 그리기
void BoomTransBlt(HDC hdc, int x, int y, HBITMAP hbitmap, COLORREF clrMask, int frm)
{
	BITMAP bm;
	HDC hMemDC;
	POINT ptSize;
	HBITMAP hOldBitmap;

	hMemDC = CreateCompatibleDC(hdc);
	hOldBitmap = (HBITMAP)SelectObject(hMemDC, hbitmap);
	GetObject(hbitmap, sizeof(BITMAP), (LPSTR)&bm);
	ptSize.x = bm.bmWidth;
	ptSize.y = bm.bmHeight;


	TransparentBlt(hdc, x, y, 105, 115, hMemDC, (frm - 1) * 105, 0, 105, ptSize.y, clrMask);



	SelectObject(hMemDC, hOldBitmap);
	DeleteDC(hMemDC);
}
//폭탄 비번 배경지워서 그리기
void TimeTransBlt(HDC hdc, int x, int y, HBITMAP hbitmap, COLORREF clrMask, int frm)
{
	BITMAP bm;
	HDC hMemDC;
	POINT ptSize;
	HBITMAP hOldBitmap;

	hMemDC = CreateCompatibleDC(hdc);
	hOldBitmap = (HBITMAP)SelectObject(hMemDC, hbitmap);
	GetObject(hbitmap, sizeof(BITMAP), (LPSTR)&bm);
	ptSize.x = bm.bmWidth;
	ptSize.y = bm.bmHeight;

	TransparentBlt(hdc, x, y, 13, 19, hMemDC, frm * 13, 0, 13, ptSize.y, clrMask);

	SelectObject(hMemDC, hOldBitmap);
	DeleteDC(hMemDC);
}
//시계 배경지워서 그리기
void DieTransBlt(HDC hdc, int x, int y, HBITMAP hbitmap, COLORREF clrMask, int frm)
{
	BITMAP bm;
	HDC hMemDC;
	POINT ptSize;
	HBITMAP hOldBitmap;

	hMemDC = CreateCompatibleDC(hdc);
	hOldBitmap = (HBITMAP)SelectObject(hMemDC, hbitmap);
	GetObject(hbitmap, sizeof(BITMAP), (LPSTR)&bm);
	ptSize.x = bm.bmWidth;
	ptSize.y = bm.bmHeight;


	if (hbitmap == NPC2Bit[4])
	{
		TransparentBlt(hdc, x - 88, y - 20, 180, 190, hMemDC, frm * 180, 0, 180, ptSize.y, clrMask);
	}
	else
	{
		TransparentBlt(hdc, x - 40, y - 10, 140, 160, hMemDC, frm * 140, 0, 140, ptSize.y, clrMask);
	}

	SelectObject(hMemDC, hOldBitmap);
	DeleteDC(hMemDC);
}
// 죽는 NPC 배경 지워서 그리기
void DrawBitmap(HDC hdc, int x, int y, HBITMAP hBit)
{
	HDC MemDC;
	HBITMAP OldBitmap;
	int bx, by;
	BITMAP bit;

	MemDC = CreateCompatibleDC(hdc);
	OldBitmap = (HBITMAP)SelectObject(MemDC, hBit);

	GetObject(hBit, sizeof(BITMAP), &bit);
	bx = bit.bmWidth;
	by = bit.bmHeight;

	BitBlt(hdc, x, y, bx, by, MemDC, 0, 0, SRCCOPY);

	SelectObject(MemDC, OldBitmap);
	DeleteDC(MemDC);
}
// 기본 그리기
void MoveAndStop(HDC hdc, int x, int y, HBITMAP bit[], int frm, bool direction, bool stop)
{
	if (direction && stop)
	{
		TransBlt(hdc, x, y, bit[0], RGB(75, 75, 75));	//플레이어
	}
	else if (stop)
	{
		TransBlt(hdc, x, y, bit[1], RGB(75, 75, 75));	//플레이어 좌우반전
	}
   else if (direction && !stop)
	{
		MoveTransBlt(hdc, x, y, bit[2], RGB(75, 75, 75), frm);	//플레이어
	}
	else if (!stop)
	{
		MoveTransBlt(hdc, x, y, bit[3], RGB(75, 75, 75), frm);	//플레이어 좌우반전
	}
}
// 플레이어 이동 및 정지 그리기
void NPCMoveAndStop(HDC hdc, int *mx, int *my, HBITMAP bit[], int frm, bool direction, bool stop, bool sstop)
{
	
	if (direction && stop && !sstop)
	{
		TransBlt(hdc, *mx, *my, bit[0], RGB(75, 75, 75));	//NPC
	}
	else if (stop && !sstop)
	{
		TransBlt(hdc, *mx, *my, bit[1], RGB(75, 75, 75));	//NPC 좌우반전
	}

	if (!sstop)
	{
		if (direction && !stop)
		{
			MoveTransBlt(hdc, *mx, *my, bit[2], RGB(75, 75, 75), frm);	//NPC 이동
		}
		else if (!stop)
		{
			MoveTransBlt(hdc, *mx, *my, bit[3], RGB(75, 75, 75), frm);	//NPC 좌우반전 이동
		}
	}
	else
	{
		TransBlt(hdc, *mx, *my, bit[1], RGB(75, 75, 75));	//NPC
	}
	
	if (!InCircle(x, y, *mx, *my, bit[0]) && !sstop)
	{
		if (x >= *mx)
		{
			*mx += NPCSPEED;
		}
		if (x <= *mx)
		{
			*mx -= NPCSPEED;
		}
		if (y >= *my)
		{
			*my += NPCSPEED;
		}
		if (y <= *my)
		{
			*my -= NPCSPEED;
		}
	}
}
// NPC 이동 및 정지 그리기

void StageMove()
{
	if (stage >= 2 && stage <= 4)	//복도 2~4
	{
		if (stage == 2)
		{
			if (y < 190 && x > 50 && x < 120 && Class2Door >= 1)		//1-2반
			{
				stage = stage * 10 + 4;
				x = 1040;
				y = 450;
				if (boom == 0)
				{
					Boomint = true;
				}
				PlaySound("Door.wav", NULL, SND_ASYNC);
			}
			else if (y < 190 && x > 50 && x < 120)
			{
				CloseDoor2int = true;
			}
		}
		else if (stage == 3)
		{
			if (y < 190 && x > 50 && x < 120 && OpenDoor >= 0)		//음악실
			{
				stage = stage * 10 + 4;
				x = 1040;
				y = 450;
				PlaySound("Door.wav", NULL, SND_ASYNC);
			}
			else if (y < 190 && x > 50 && x < 120)
			{
				CloseDoorint = true;
			}
		}
		else if (stage == 4)
		{
			if (y < 190 && x > 50 && x < 120 && OpenDoor >= 4)		//교무실 입구
			{
				stage = stage * 10 + 4;
				x = 1040;
				y = 450;
				PlaySound("Door.wav", NULL, SND_ASYNC);
				Openint = true;
			}
			else if (y < 190 && x > 50 && x < 120)
			{
				CloseDoorint = true;
			}
		}
		

		if(stage == 2)
		{
			if (y < 190 && x > 930 && x < 1010 && NPCFree >= 1)		//1-3반 입구
			{
				stage = stage * 10 + 3;
				x = 120;
				y = 450;
				PlaySound("Door.wav", NULL, SND_ASYNC);
			}
			else if (y < 190 && x > 930 && x < 1010)
			{
				CloseDoorint = true;
			}
		}
		else if (stage == 3)
		{
			if (y < 190 && x > 930 && x < 1010 && HealDoor >= 1)		//보건실 입구
			{
				stage = stage * 10 + 3;
				x = 120;
				y = 450;
				PlaySound("Door.wav", NULL, SND_ASYNC);
				if (HealDoor == 1)
				{
					Healint = true;
				}
			}
			else if (y < 190 && x > 930 && x < 1010)
			{
				CloseDoorint = true;
			}
		}
		else if (stage == 4)
		{
			if (y < 190 && x > 930 && x < 1010 && BedDoor >= 1)		//숙직실 입구
			{
				stage = stage * 10 + 3;
				x = 120;
				y = 450;
				PlaySound("Door.wav", NULL, SND_ASYNC);
			}
			else if (y < 190 && x > 930 && x < 1010)
			{
				CloseDoorint = true;
			}
		}
		
	}
	else if (stage % 10 == 3 && stage != 5)
	{
		if (y > 450 && x < 230)		//위 오른쪽 방 출구
		{
			stage = (stage - 3) / 10;
			x = 1000;
			y = 190;
			PlaySound("Door.wav", NULL, SND_ASYNC);
		}
	}
	else if (stage % 10 == 4 && stage != 5)
	{
		if (y > 450 && x > 950)		//위 왼쪽 방 출구
		{
			stage = (stage - 4) / 10;
			x = 120;
			y = 170;
			PlaySound("Door.wav", NULL, SND_ASYNC);
			if (OpenDoor == 5)
			{
				Openint = true;
			}
		}

	}

	if (stage == 1)		//복도 1
	{
		if (y > 435 && x < 600 && Class1Door >= 1)		//1-1반 입구
		{
			stage = stage * 10 + 1;
			x = 1000;
			y = 80;
			PlaySound("Door.wav", NULL, SND_ASYNC);
			if (Class1Door == 1)
			{
				Openint = true;
			}
		}
		else if (y > 435 && x < 600 && Class1Door == 0)
		{
			CloseDoorint = true;
		}
		else if (y < 190 && x > 920 && x < 1100)		//창고 입구
		{
			if (OpenDoor == 1)
			{
				Openint = true;
			}
			else if (OpenDoor >= 2)
			{
				stage = stage * 10 + 3;
				x = 65;
				y = 450;
				PlaySound("Door.wav", NULL, SND_ASYNC);
			}
			else if (OpenDoor == 0)
			{
				CloseDoorint = true;
			}
		}
	}

	if (stage % 10 == 1 && stage != 51 && stage != 52)
	{
		if (y < 60 && x > 930 && x < 1010)	//아래 왼쪽 방 출구
		{
			stage = stage / 10;

			x = 120;
			y = 430;
			PlaySound("Door.wav", NULL, SND_ASYNC);
		}
	}


	if (stage == 5)		//복도 5
	{
		if (y > 435 && x < 600)		//1-4반 입구
		{
			if (Class4Door >= 1)
			{
				Openint = true;
				stage = stage * 10 + 1;
				x = 1000;
				y = 80;
				PlaySound("Door.wav", NULL, SND_ASYNC);
			}
			else
			{
				CloseDoorint = true;
			}
		}
		else if (y > 435 && x > 600)		//1-5반 입구
		{
			stage = stage * 10 + 2;
			x = 65;
			y = 80;
			PlaySound("Door.wav", NULL, SND_ASYNC);
		}
		else if (y < 190 && x > 920 && x < 1100)		//방송실 입구
		{
			CloseDoorint = true;
		}
	}


	if (stage >= 51 && stage <= 52)
	{
		if (stage % 10 == 1)
		{
			if (y < 60 && x > 930 && x < 1010 && Class4Door >= 3 && KeyCheck != 1)	//아래 왼쪽 방 출구
			{
				stage = stage / 10;

				x = 120;
				y = 430;
			}
			else if (y < 60 && x > 930 && x < 1010 && Class4Door == 2)
			{
				Pianoint = true;		//피아노지만 감옥에서 못나가게 하기 위함
			}
			else if (y < 60 && x > 930 && x < 1010 && KeyCheck == 1)
			{
				Pianoint = true;		//피아노지만 감옥에서 못나가게 하기 위함
			}
		}
		else if (stage % 10 == 2)
		{
			if (y < 60 && x > 50 && x < 120)	//아래 오른쪽 방 출구
			{
				if (FirstRead == 1)
				{
					FirstReadint = true;
				}
				stage = stage / 10;

				x = 1040;
				y = 430;
			}
		}
	}

	if(stage == 3)
	{
		if (x >= 500 && x <= 700 && y > 435)		//정문 출구
		{
			MainDoorint = true;
		}
	}

}
// 맵 이동
void StageCheck()
{
	MaxX1 = -200;
	MaxX2 = 1350;
	MaxY1 = 170;
	MaxY2 = 430;
	if (stage == 1 || stage == 5)
	{
		if (stage == 1)		// 관리자방 못가게하는거
		{
			MaxX1 = 0;
			if (x > 65 && x < 220)	//파인곳 들어가게 해주는거
			{
				MaxY2 = 500;
			}
			if (y > 435 && x < 600)		//왼쪽아래 파인곳 양옆 막는곳
			{
				MaxX1 = 65;
				MaxX2 = 220;
			}
		}

		if (stage == 5)		// 관리자방 못가게하는거
		{
			MaxX2 = 1150;
			if (x > 65 && x < 220 || x > 970 && x < 1120)	//파인곳 들어가게 해주는거
			{
				MaxY2 = 500;
			}
			if (y > 435 && x < 600)		//왼쪽아래 파인곳 양옆 막는곳
			{
				MaxX1 = 65;
				MaxX2 = 220;
			}
			if (y > 435 && x > 600)		//오른쪽아래 파인곳 양옆 막는곳
			{
				MaxX1 = 970;
				MaxX2 = 1120;
			}
		}
	}

	if (stage == 3)				//정문
	{
		if (x >= 500 && x <= 700)		//파인 곳 들어가게 해주는거
		{
			MaxY2 = 500;
			if (y > 435)			//파인 곳 양옆 막는곳
			{
				MaxX1 = 500;
				MaxX2 = 700;
			}
		}
	}

	if (stage > 10)
	{
		MaxX1 = 0;
		MaxX2 = 1170;
		MaxY1 = 50;
		MaxY2 = 520;
	}
}
// 맵 최대 이동거리 제한
void PlayerDraw(HDC hdc)
{
	if (stage == 1)			//복도 1
	{
		Cresh(BoxBit[0], 330, 250, 1);
		TransBlt(hdc, 330, 250, BoxBit[0], RGB(75, 75, 75));

		Cresh(BoxBit[0], 400, 250, 1);
		TransBlt(hdc, 400, 250, BoxBit[0], RGB(75, 75, 75));

		Cresh(SchoolDeskBit[0], 470, 230, 1);
		TransBlt(hdc, 470, 230, SchoolDeskBit[0], RGB(75, 75, 75));

		Cresh(SchoolDeskBit[0], 570, 230, 1);
		TransBlt(hdc, 570, 230, SchoolDeskBit[0], RGB(75, 75, 75));

		Cresh(SchoolDeskBit[0], 670, 230, 1);
		TransBlt(hdc, 670, 230, SchoolDeskBit[0], RGB(75, 75, 75));
	}
	//복도 1 맵 구성

	if (stage == 2)			//복도 2
	{
		Cresh(BoxBit[0], 260, 480, 2);
		TransBlt(hdc, 260, 480, BoxBit[0], RGB(75, 75, 75));

		Cresh(BoxBit[0], 330, 480, 2);
		TransBlt(hdc, 330, 480, BoxBit[0], RGB(75, 75, 75));

		Cresh(BoxBit[0], 400, 480, 2);
		TransBlt(hdc, 400, 480, BoxBit[0], RGB(75, 75, 75));

		Cresh(BoxBit[0], 470, 480, 2);
		TransBlt(hdc, 470, 480, BoxBit[0], RGB(75, 75, 75));

		Cresh(ChairBit[3], 720, 230, 2);
		TransBlt(hdc, 720, 230, ChairBit[3], RGB(75, 75, 75));

		Cresh(ChairBit[3], 790, 230, 2);
		TransBlt(hdc, 790, 230, ChairBit[3], RGB(75, 75, 75));

		Cresh(ChairBit[3], 860, 230, 2);
		TransBlt(hdc, 860, 230, ChairBit[3], RGB(75, 75, 75));
	}
	//복도 2 맵 구성

	if (stage == 3)			//복도 3
	{
		Cresh(BoxBit[2], 260, 480, 3);
		TransBlt(hdc, 260, 480, BoxBit[2], RGB(75, 75, 75));

		Cresh(BoxBit[2], 330, 480, 3);
		TransBlt(hdc, 330, 480, BoxBit[2], RGB(75, 75, 75));

		Cresh(SchoolDeskBit[0], 470, 230, 3);
		TransBlt(hdc, 470, 230, SchoolDeskBit[0], RGB(75, 75, 75));

		Cresh(SchoolDeskBit[0], 570, 230, 3);
		TransBlt(hdc, 570, 230, SchoolDeskBit[0], RGB(75, 75, 75));

		Cresh(SchoolDeskBit[0], 670, 230, 3);
		TransBlt(hdc, 670, 230, SchoolDeskBit[0], RGB(75, 75, 75));

		Cresh(ChairBit[3], 770, 230, 3);
		TransBlt(hdc, 770, 230, ChairBit[3], RGB(75, 75, 75));

		Cresh(ChairBit[3], 840, 230, 3);
		TransBlt(hdc, 840, 230, ChairBit[3], RGB(75, 75, 75));
	}
	//복도 3 맵 구성

	if (stage == 4)			//복도 4
	{
		Cresh(BoxBit[0], 330, 480, 4);
		TransBlt(hdc, 330, 480, BoxBit[0], RGB(75, 75, 75));

		Cresh(BoxBit[0], 400, 480, 4);
		TransBlt(hdc, 400, 480, BoxBit[0], RGB(75, 75, 75));

		Cresh(BoxBit[0], 470, 480, 4);
		TransBlt(hdc, 470, 480, BoxBit[0], RGB(75, 75, 75));

		

		Cresh(CabinetBit, 625, 200, 4);
		TransBlt(hdc, 625, 200, CabinetBit, RGB(75, 75, 75));

		Cresh(CabinetBit, 725, 200, 4);
		TransBlt(hdc, 725, 200, CabinetBit, RGB(75, 75, 75));

		Cresh(CabinetBit, 825, 200, 4);
		TransBlt(hdc, 825, 200, CabinetBit, RGB(75, 75, 75));
	}
	//복도 4 맵 구성

	if (stage == 5)			//복도 5
	{
		Cresh(BoxBit[0], 240, 270, 5);
		TransBlt(hdc, 240, 270, BoxBit[0], RGB(75, 75, 75));

		Cresh(BoxBit[0], 310, 270, 5);
		TransBlt(hdc, 310, 270, BoxBit[0], RGB(75, 75, 75));

		Cresh(SchoolDeskBit[2], 380, 230, 5);
		TransBlt(hdc, 380, 230, SchoolDeskBit[2], RGB(75, 75, 75));

		Cresh(SchoolDeskBit[2], 450, 230, 5);
		TransBlt(hdc, 450, 230, SchoolDeskBit[2], RGB(75, 75, 75));

		Cresh(SchoolDeskBit[1], 520, 230, 5);
		TransBlt(hdc, 520, 230, SchoolDeskBit[1], RGB(75, 75, 75));

		Cresh(SchoolDeskBit[1], 590, 230, 5);
		TransBlt(hdc, 590, 230, SchoolDeskBit[1], RGB(75, 75, 75));

		Cresh(SchoolDeskBit[1], 660, 230, 5);
		TransBlt(hdc, 660, 230, SchoolDeskBit[1], RGB(75, 75, 75));
	}
	//복도 5 맵 구성

	if (stage == 11)	//1-1반
	{
		for (int i = 0; i < 4; i++)
		{
			int k = i % 2 + 1;
			Cresh(ChairBit[0], 990 - i * 220, 230, 11);		//의자
			TransBlt(hdc, 990 - i * 220, 230, ChairBit[0], RGB(75, 75, 75));

			Cresh(SchoolDeskBit[k], 950 - i * 220, 230, 11);	//책상
			TransBlt(hdc, 950 - i * 220, 230, SchoolDeskBit[k], RGB(75, 75, 75));
		}
		for (int i = 0; i < 4; i++)
		{
			int k = i % 2 + 1;
			Cresh(ChairBit[0], 330 + i * 220, 520, 11);		//의자
			TransBlt(hdc, 330 + i * 220, 520, ChairBit[0], RGB(75, 75, 75));

			Cresh(SchoolDeskBit[k], 290 + i * 220, 520, 11);	//책상
			TransBlt(hdc, 290 + i * 220, 520, SchoolDeskBit[k], RGB(75, 75, 75));
		}
		if (DayCheck == 7)
		{
			Cresh(SchoolDeskBit[1], 290 + 3 * 220, 520, 11);	//책상
			TransBlt(hdc, 290 + 3 * 220, 520, SchoolDeskBit[1], RGB(75, 75, 75));
		}

		Cresh(LectureTableBit, 100, 320, 11);	//교탁
		TransBlt(hdc, 100, 320, LectureTableBit, RGB(75, 75, 75));

		Cresh(CabinetBit, 0, 80, 11);	//캐비넷
		TransBlt(hdc, 0, 80, CabinetBit, RGB(75, 75, 75));

		Cresh(CabinetBit, 80, 80, 11);	//캐비넷
		TransBlt(hdc, 80, 80, CabinetBit, RGB(75, 75, 75));

		TransBlt(hdc, -5, 100, BoardBit, RGB(75, 75, 75));	//칠판

		TransBlt(hdc, 30, 480, ChairBit[1], RGB(75, 75, 75));	//오피스 의자

		Cresh(OfficeDeskBit, 100, 430, 11);	//오피스 책상
		TransBlt(hdc, 100, 430, OfficeDeskBit, RGB(75, 75, 75));

		Cresh(LockerBit, 1205, 140, 11);	//사물함
		TransBlt(hdc, 1205, 140, LockerBit, RGB(75, 75, 75));

		Cresh(LockerBit, 290, 320, 11);	//사물함
		TransBlt(hdc, 290, 400, SkeletonBit, RGB(75, 75, 75));
	}
	//1-1반 맵 구성

	if (stage == 13)		//창고 오브젝트
	{
		for (int j = 0; j < 4; j++)
		{
			int k = j % 3;
			Cresh(BoxBit[k], 1150, j * 150 + 100, 13);
			TransBlt(hdc, 1150, j * 150 + 100, BoxBit[k], RGB(75, 75, 75));
		}
		
		for (int i = 0; i < 3; i++)
		{
			int k = i % 3;
			Cresh(BoxBit[k], i * 200 + 350, 150, 13);
			TransBlt(hdc, i * 200 + 350, 150, BoxBit[k], RGB(75, 75, 75));
		}
		if (DayCheck <= 1)
		{
			Cresh(SchoolDeskBit[2], 50, 200, 13);
			TransBlt(hdc, 50, 200, SchoolDeskBit[2], RGB(75, 75, 75));
		}
		else
		{
			Cresh(SchoolDeskBit[1], 50, 200, 13);
			TransBlt(hdc, 50, 200, SchoolDeskBit[1], RGB(75, 75, 75));
		}
	}
	//창고 맵 구성

	if (stage == 24)	//1-2반
	{
		for (int i = 0; i < 3; i++)
		{
			int k = i % 2 + 1;
			Cresh(ChairBit[0], 770 - i * 220, 230, 24);		//의자
			TransBlt(hdc, 770 - i * 220, 230, ChairBit[0], RGB(75, 75, 75));

			Cresh(SchoolDeskBit[k], 730 - i * 220, 230, 24);	//책상
			TransBlt(hdc, 730 - i * 220, 230, SchoolDeskBit[k], RGB(75, 75, 75));
		}
		for (int i = 0; i < 3; i++)
		{
			int k = i % 2 + 1;
			Cresh(ChairBit[0], 330 + i * 220, 520, 24);		//의자
			TransBlt(hdc, 330 + i * 220, 520, ChairBit[0], RGB(75, 75, 75));

			Cresh(SchoolDeskBit[k], 290 + i * 220, 520, 24);	//책상
			TransBlt(hdc, 290 + i * 220, 520, SchoolDeskBit[k], RGB(75, 75, 75));
		}
		Cresh(LectureTableBit, 100, 320, 24);	//교탁
		TransBlt(hdc, 100, 320, LectureTableBit, RGB(75, 75, 75));

		TransBlt(hdc, -5, 100, BoardBit, RGB(75, 75, 75));	//칠판

		TransBlt(hdc, 30, 480, ChairBit[1], RGB(75, 75, 75));	//오피스 의자

		Cresh(OfficeDeskBit, 100, 430, 24);	//오피스 책상
		TransBlt(hdc, 100, 430, OfficeDeskBit, RGB(75, 75, 75));

		Cresh(CabinetBit, 950, 80, 24);	//캐비넷
		TransBlt(hdc, 950, 80, CabinetBit, RGB(75, 75, 75));

		Cresh(CabinetBit, 1030, 80, 24);	//캐비넷
		TransBlt(hdc, 1030, 80, CabinetBit, RGB(75, 75, 75));

		Cresh(LockerBit, 1205, 140, 24);	//사물함
		TransBlt(hdc, 1205, 140, LockerBit, RGB(75, 75, 75));

		TransBlt(hdc, 590, 10, ClockBit, RGB(75, 75, 75));		//시계

		TimeTransBlt(hdc, 619, 29, TimeBit, RGB(75, 75, 75), Boon);			//분
		TimeTransBlt(hdc, 635, 29, TimeBit, RGB(75, 75, 75), Cho1);			//10의 자리 초
		TimeTransBlt(hdc, 648, 29, TimeBit, RGB(75, 75, 75), Cho2);			//1의 자리 초
	}
	//1-2반 맵 구성

	if (stage == 23)	//1-3반
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				Cresh(SchoolDeskBit[0], 580 + i * 120, 100 + j * 100, 23);	//책상
				TransBlt(hdc, 580 + i * 120, 100 + j * 100, SchoolDeskBit[0], RGB(75, 75, 75));
			}
		}
		for (int i = 0; i < 6; i++)
		{
			Cresh(ChairBit[3], 400 + i * 80, 575, 23);		//의자
			TransBlt(hdc, 400 + i * 80, 575, ChairBit[3], RGB(75, 75, 75));
		}
		for (int i = 0; i < 3; i++)
		{
			Cresh(BoxBit[0], 350 + i * 80, 320, 23);		//상자
			TransBlt(hdc, 350 + i * 80, 320, BoxBit[0], RGB(75, 75, 75));
		}
		Cresh(LectureTableBit, 0, 50, 23);	//교탁
		TransBlt(hdc, 0, 50, LectureTableBit, RGB(75, 75, 75));

		Cresh(BoxBit[1], 1130, 150, 23);		//박스
		TransBlt(hdc, 1130, 150, BoxBit[1], RGB(75, 75, 75));	

		Cresh(BedBit, 0, 300, 23);	// 침대
		TransBlt(hdc, 0, 300, BedBit, RGB(75, 75, 75));

		Cresh(CabinetBit, 400, 80, 23);	//캐비넷
		TransBlt(hdc, 400, 80, CabinetBit, RGB(75, 75, 75));

		Cresh(CabinetBit, 480, 80, 23);	//캐비넷
		TransBlt(hdc, 480, 80, CabinetBit, RGB(75, 75, 75));

		Cresh(LockerBit, 1205, 140, 23);	//사물함
		TransBlt(hdc, 1205, 140, LockerBit, RGB(75, 75, 75));

		Cresh(SchoolDeskBit[2], 200, 140, 23);	//책 올린 책상
		TransBlt(hdc, 200, 140, SchoolDeskBit[2], RGB(75, 75, 75));

		if (DayCheck < 5)
		{
			Cresh(SchoolDeskBit[2], 1138, 530, 23);	//책 올린 책상
			TransBlt(hdc, 1138, 530, SchoolDeskBit[2], RGB(75, 75, 75));
		}
		else
		{
			Cresh(SchoolDeskBit[1], 1138, 530, 23);	//책 올린 책상
			TransBlt(hdc, 1138, 530, SchoolDeskBit[1], RGB(75, 75, 75));
		}
	}
	//1-3반 맵 구성

	if (stage == 33)	//보건실
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				Cresh(SchoolDeskBit[0], 320 + i * 100, 100 + j * 80, 33);	//책상
				TransBlt(hdc, 320 + i * 100, 100 + j * 80, SchoolDeskBit[0], RGB(75, 75, 75));
			}
		}
		for (int i = 0; i < 4; i++)
		{
			Cresh(BoxBit[0], 0 + i * 80, 100, 33);		//상자
			TransBlt(hdc, 0 + i * 80, 100, BoxBit[0], RGB(75, 75, 75));
		}

		if (DayCheck < 6)
		{
			Cresh(SchoolDeskBit[2], 0, 400, 33);	// 책 올린 책상
			TransBlt(hdc, 0, 400, SchoolDeskBit[2], RGB(75, 75, 75));
		}
		else
		{
			Cresh(SchoolDeskBit[1], 0, 400, 33);	//책상
			TransBlt(hdc, 0, 400, SchoolDeskBit[1], RGB(75, 75, 75));
		}

		for (int i = 0; i < 3; i++)
		{
			Cresh(CabinetBit, 780 + i * 80, 80, 33);		//캐비넷
			TransBlt(hdc, 780 + i * 80, 80, CabinetBit, RGB(75, 75, 75));
		}

		for (int i = 0; i < 2; i++)
		{
			Cresh(ChairBit[0], 620 + i * 80, 100, 33);		//정면 의자
			TransBlt(hdc, 620 + i * 80, 100, ChairBit[0], RGB(75, 75, 75));
		}

		for (int i = 0; i < 3; i++)
		{
			Cresh(ChairBit[1], 590 + i * 250, 560, 33);		//오피스 의자
			TransBlt(hdc, 590 + i * 250, 560, ChairBit[1], RGB(75, 75, 75));

			Cresh(BedBit, 650 + i * 250, 460, 33);		//침대
			TransBlt(hdc, 650 + i * 250, 460, BedBit, RGB(75, 75, 75));
		}

		Cresh(ChairBit[1], 1100, 120, 33);		//오피스 의자
		TransBlt(hdc, 1100, 120, ChairBit[1], RGB(75, 75, 75));

		Cresh(OfficeDeskBit, 1180, 100, 33);		//오피스 책상
		TransBlt(hdc, 1180, 100, OfficeDeskBit, RGB(75, 75, 75));

		Cresh(SkeletonBit, 100, 250, 33);		//해골
		TransBlt(hdc, 100, 250, SkeletonBit, RGB(75, 75, 75));
	}
	//보건실 맵 구성

	if (stage == 34)		// 음악실 오브젝트
	{
		Cresh(SkeletonBit, 950, 150, 34);	//해골
		TransBlt(hdc, 950, 150, SkeletonBit, RGB(75, 75, 75));

		Cresh(SchoolDeskBit[2], 450, 80, 34);	//책이 올려진 책상
		TransBlt(hdc, 450, 80, SchoolDeskBit[2], RGB(75, 75, 75));

		Cresh(SchoolDeskBit[3], 680, 80, 34);	//책이 올려진 책상
		TransBlt(hdc, 680, 80, SchoolDeskBit[3], RGB(75, 75, 75));

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				Cresh(ChairBit[0], 400 + i * 150, 350 + j * 100, 34);	//의자
				TransBlt(hdc, 400 + i * 150, 350 + j * 100, ChairBit[0], RGB(75, 75, 75));
			}
		}
		
		TransBlt(hdc, -5, 100, BoardBit, RGB(75, 75, 75));	//칠판

		Cresh(PianoBit, 120, 80, 34);						//피아노
		TransBlt(hdc, 120, 80, PianoBit, RGB(75, 75, 75));
					
		TransBlt(hdc, 50, 180, ChairBit[2], RGB(75, 75, 75));	//피아노 의자

		Cresh(LectureTableBit, 150, 450, 34);						//교탁
		TransBlt(hdc, 150, 450, LectureTableBit, RGB(75, 75, 75));

		Cresh(CabinetBit, 1180, 100, 34);						//캐비넷
		TransBlt(hdc, 1180, 100, CabinetBit, RGB(75, 75, 75));
	}
	//음악실 맵 구성

	if (stage == 43)	//숙직실
	{
		if (KeyCheck == 0)
		{
			Cresh(KeyBit, 765, 200, 43);		//열쇠
			TransBlt(hdc, 765, 200, KeyBit, RGB(75, 75, 75));
		}

		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				Cresh(BedBit, 770 + i * 380, 100+j*350, 43);		//침대
				TransBlt(hdc, 770 + i * 380, 100+j*350, BedBit, RGB(75, 75, 75));

				Cresh(SchoolDeskBit[0], 580 + i * 380, 100 + j * 410, 43);		//정면 책상
				TransBlt(hdc, 580 + i * 380, 100 + j * 410, SchoolDeskBit[0], RGB(75, 75, 75));

				Cresh(ChairBit[3], 595 + i * 380, 150 + j * 410, 43);		//정면 의자
				TransBlt(hdc, 595 + i * 380, 150 + j * 410, ChairBit[3], RGB(75, 75, 75));
			}
		}

		for (int j = 0; j < 3; j++)
		{
			Cresh(BoxBit[0], 200 + j * 80, 320, 43);	//상자
			TransBlt(hdc, 200 + j * 80, 320, BoxBit[0], RGB(75, 75, 75));
			
		}
		for (int j = 0; j < 2; j++)
		{
			Cresh(BoxBit[0], 240 + j * 80, 400, 43);	//상자
			TransBlt(hdc, 240 + j * 80, 380, BoxBit[0], RGB(75, 75, 75));
		}



		for (int i = 0; i < 3; i++)
		{
			Cresh(CabinetBit, 150 + i * 100, 80, 43);		//캐비넷
			TransBlt(hdc, 150 + i * 100, 80, CabinetBit, RGB(75, 75, 75));
		}


		Cresh(LockerBit,0 , 120, 43);		//캐비넷
		TransBlt(hdc, 0, 120 ,LockerBit, RGB(75, 75, 75));

	
	}
	//숙직실 맵 구성

	if (stage == 44)	//교무실
	{

		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				Cresh(ChairBit[1], 110 + i * 380, 130 + j * 360, 44);		//오피스 오른쪽 의자
				TransBlt(hdc, 110 + i * 380, 130 + j * 360, ChairBit[1], RGB(75, 75, 75));

				Cresh(OfficeDeskBit, 180 + i * 380, 90 + j * 340, 44);		//오피스 오른쪽 책상
				TransBlt(hdc, 180 + i * 380, 100 + j * 340, OfficeDeskBit, RGB(75, 75, 75));

				Cresh(ChairBit[4], 350 + i * 380, 130 + j * 350, 44);		//오피스 왼쪽 의자
				TransBlt(hdc, 350 + i * 380, 130 + j * 350, ChairBit[4], RGB(75, 75, 75));

				Cresh(OfficeDeskBit2, 260 + i * 380, 90 + j * 340, 44);		//오피스 왼쪽 책상
				TransBlt(hdc, 260 + i * 380, 100 + j * 340, OfficeDeskBit2, RGB(75, 75, 75));
			}
		}

		TransBlt(hdc, -5, 100, BoardBit, RGB(75, 75, 75));	//칠판

		if (DayCheck < 3)
		{
			Cresh(SchoolDeskBit[2], 1200, 380, 44);	//책 올린 책상
			TransBlt(hdc, 1200, 380, SchoolDeskBit[2], RGB(75, 75, 75));
		}
		else if (DayCheck >= 3)
		{
			Cresh(SchoolDeskBit[1], 1200, 380, 44);	//책 올린 책상
			TransBlt(hdc, 1200, 380, SchoolDeskBit[1], RGB(75, 75, 75));
		}

		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				Cresh(SchoolDeskBit[0], 1060 + i * 100, 100 + j * 80, 44);	//책상
				TransBlt(hdc, 1060 + i * 100, 100 + j * 80, SchoolDeskBit[0], RGB(75, 75, 75));
			}
		}

		Cresh(CabinetBit, 900, 80, 44);	//캐비넷
		TransBlt(hdc, 900, 80, CabinetBit, RGB(75, 75, 75));

		Cresh(CabinetBit, 980, 80, 44);	//캐비넷
		TransBlt(hdc, 980, 80, CabinetBit, RGB(75, 75, 75));
	}
	//교무실 맵 구성

	if (stage == 51)	//1-4반
	{
		if (NPC1stop)
		{
			Cresh(IronBarBit[0], 65, 470, 51);		//철창
			TransBlt(hdc, 65, 470, IronBarBit[0], RGB(75, 75, 75));
		}
		else
		{
			Cresh(IronBarBit[1], 65, 470, 51);
			TransBlt(hdc, 65, 470, IronBarBit[1], RGB(75, 75, 75));
		}

		if (NPC2stop)
		{
			Cresh(IronBarBit[0], 365, 470, 51);		//철창
			TransBlt(hdc, 365, 470, IronBarBit[0], RGB(75, 75, 75));
		}
		else
		{
			Cresh(IronBarBit[1], 365, 470, 51);
			TransBlt(hdc, 365, 470, IronBarBit[1], RGB(75, 75, 75));
		}

		if (NPC3stop)
		{
			Cresh(IronBarBit[0], 665, 470, 51);		//철창
			TransBlt(hdc, 665, 470, IronBarBit[0], RGB(75, 75, 75));
		}
		else
		{
			Cresh(IronBarBit[1], 665, 470, 51);
			TransBlt(hdc, 665, 470, IronBarBit[1], RGB(75, 75, 75));
		}

		if (NPC4stop)
		{
			Cresh(IronBarBit[0], 965, 470, 51);		//철창
			TransBlt(hdc, 965, 470, IronBarBit[0], RGB(75, 75, 75));
		}
		else
		{
			Cresh(IronBarBit[1], 965, 470, 51);
			TransBlt(hdc, 965, 470, IronBarBit[1], RGB(75, 75, 75));
		}



		if (DayCheck < 4)
		{
			Cresh(SchoolDeskBit[2], 50, 150, 51);		//책이 올려진 책상
			TransBlt(hdc, 50, 150, SchoolDeskBit[2], RGB(75, 75, 75));
		}
		else
		{
			Cresh(SchoolDeskBit[1], 50, 150, 51);		//책이 올려진 책상
			TransBlt(hdc, 50, 150, SchoolDeskBit[1], RGB(75, 75, 75));
		}
	}
	//1-4반 맵 구성

	if (stage == 52)		//1-5반 오브젝트
	{
		Cresh(SchoolDeskBit[2], 550, 500, 52);		// 일기장 책상
		if (DayCheck == 0)
		{
			TransBlt(hdc, 550, 500, SchoolDeskBit[2], RGB(75, 75, 75));
			TransBlt(hdc, 560, 520, KeyBit, RGB(75, 75, 75));	//열쇠
		}
		else
		{
			TransBlt(hdc, 550, 500, SchoolDeskBit[1], RGB(75, 75, 75));
		}
		Cresh(ChairBit[0], 600, 100, 52);		//의자
		TransBlt(hdc, 600, 100, ChairBit[0], RGB(75, 75, 75));
		Cresh(SchoolDeskBit[2], 550, 100, 52);		//책상
		TransBlt(hdc, 550, 100, SchoolDeskBit[2], RGB(75, 75, 75));

		Cresh(ChairBit[0], 350, 250, 52);		//의자
		TransBlt(hdc, 350, 250, ChairBit[0], RGB(75, 75, 75));
		Cresh(SchoolDeskBit[2], 300, 250, 52);		//책상
		TransBlt(hdc, 300, 250, SchoolDeskBit[2], RGB(75, 75, 75));

		Cresh(ChairBit[0], 860, 300, 52);		//의자
		TransBlt(hdc, 860, 300, ChairBit[0], RGB(75, 75, 75));
		Cresh(SchoolDeskBit[1], 810, 300, 52);		//책상
		TransBlt(hdc, 810, 300, SchoolDeskBit[1], RGB(75, 75, 75));

		TransBlt(hdc, -5, 100, BoardBit, RGB(75, 75, 75));	//칠판

		Cresh(LectureTableBit, 100, 320, 52);	//교탁
		TransBlt(hdc, 100, 320, LectureTableBit, RGB(75, 75, 75));

		Cresh(CabinetBit, 1100, 80, 52);	//캐비넷
		TransBlt(hdc, 1100, 80, CabinetBit, RGB(75, 75, 75));

		Cresh(CabinetBit, 1020, 80, 52);	//캐비넷
		TransBlt(hdc, 1020, 80, CabinetBit, RGB(75, 75, 75));

		TransBlt(hdc, -5, 100, BoardBit, RGB(75, 75, 75));	//칠판

		Cresh(LockerBit, 1205, 140, 52);	//사물함
		TransBlt(hdc, 1205, 140, LockerBit, RGB(75, 75, 75));

	}
	//1-5반 맵 구성

	if (!Endingint)
	{
		if (stage == NPCstage1 && NPCDie != 1)		//NPC1
		{
			NPCMoveAndStop(hdc, &NPC1x, &NPC1y, NPC1Bit, pfrm, direction, stop, NPC1stop);
		}
		else if (stage == NPCstage1 && NPCDie == 1)
		{
			DieTransBlt(hdc, NPC1x, NPC1y, NPC1Bit[4], RGB(75, 75, 75), dfrm);
		}

		if (stage == NPCstage2 && NPCDie != 2)		//NPC2
		{
			NPCMoveAndStop(hdc, &NPC2x, &NPC2y, NPC2Bit, pfrm, direction, stop, NPC2stop);
		}
		else if (stage == NPCstage2 && NPCDie == 2)
		{
			DieTransBlt(hdc, NPC2x, NPC2y, NPC2Bit[4], RGB(75, 75, 75), dfrm);
		}

		if (stage == NPCstage3 && NPCDie != 3)		//NPC3
		{
			NPCMoveAndStop(hdc, &NPC3x, &NPC3y, NPC3Bit, pfrm, direction, stop, NPC3stop);
		}
		else if (stage == NPCstage3 && NPCDie == 3)
		{
			DieTransBlt(hdc, NPC3x, NPC3y, NPC3Bit[4], RGB(75, 75, 75), dfrm);
		}

		if (stage == NPCstage4 && NPCDie != 4)		//NPC4
		{
			NPCMoveAndStop(hdc, &NPC4x, &NPC4y, NPC4Bit, pfrm, direction, stop, NPC4stop);
		}
		else if (stage == NPCstage4 && NPCDie == 4)
		{
			DieTransBlt(hdc, NPC4x, NPC4y, NPC4Bit[4], RGB(75, 75, 75), dfrm);
		}

		MoveAndStop(hdc, x, y, P_Bit, pfrm, direction, stop);		//플레이어

		if (!Endingint)
		{
			if (stage == 24 || stage == 51)
			{

			}
			else
			{
				TransBlt(hdc, x - 1235, y - 670, SeeBit, RGB(75, 75, 75));
			}
		}
	}
	//엔딩
}
//오브젝트와 플레이어 그리기
void BackGround(HDC hdc)
{
	if (stage == 1)
	{
		DrawBitmap(hdc, 0, 0, BokDoBit[0]);		// 복도1
	}
	if (stage == 2 || stage == 4)
	{
		DrawBitmap(hdc, 0, 0, BokDoBit[1]);		// 복도2 복도 4
	}
	if (stage == 3)
	{
		DrawBitmap(hdc, 0, 0, BokDoBit[2]);		// 복도3
	}
	if (stage == 5)
	{
		DrawBitmap(hdc, 0, 0, BokDoBit[4]);		// 복도5
	}

	if (stage > 10)
	{
		switch (stage % 10)
		{
		case 1:
			DrawBitmap(hdc, 0, 0, RightDoorBit[0]);		// 왼쪽 아래 방
			break;
		case 2:
			DrawBitmap(hdc, 0, 0, LeftDoorBit[0]);		// 오른쪽 아래 방
			break;
		case 3:
			DrawBitmap(hdc, 0, 0, RightDoorBit[1]);		// 오른쪽 위 방
			break;
		case 4:
			DrawBitmap(hdc, 0, 0, LeftDoorBit[1]);		// 왼쪽 위 방
			break;
		}
	}
}
// 배경 그리기
void Interaction()		//NPC1과 상호작용
{

	if (stage == 3)
	{
		if (CCheckPtInRect(BoxBit[2], 260, 480))		//복도 3 메모지
		{
			Boxint = true;
			Stop = true;
		}
	}

	if (stage == 11)
	{
		if (CCheckPtInRect(SkeletonBit, 290, 400))		//해골
		{
			Skeletonint = true;
			Stop = true;
		}

		if (CCheckPtInRect(SchoolDeskBit[2], 290 + 3 * 220, 520))		//해골
		{
			Diaryint = true;
			Stop = true;
		}
	}

	if (stage == 13)
	{
		if (CCheckPtInRect(SchoolDeskBit[2], 50, 200))		//창고 일기장
		{
			Diaryint = true;
			Stop = true;
		}

		for (int j = 0; j < 4; j++)		//창고 상자 위
		{
			if (CCheckPtInRect(BoxBit[0], 1150, j * 150 + 100))
			{
				if (j == 3)
				{
					RealBox = true;
				}
				Boxint = true;
			}
		}
		for (int i = 0; i < 3; i++)		//창고 상자 옆
		{
			if (CCheckPtInRect(BoxBit[0], i * 200 + 350, 150))
			{
				if (i == 2)
				{
					FakeBox = true;
				}
				FakeBoxint = true;
			}
		}
	}

	if (stage == 23)				//1-3반
	{
		if (CCheckPtInRect(SchoolDeskBit[2], 1138, 530))		//책상
		{
			Diaryint = true;
			Stop = true;
		}
	}

	if (stage == 24 && boom == 1)
	{
		if (CCheckPtInRect(NPC2Bit[0], 800, 400))		//1-2반 NPC 상호작용
		{
			Boomint = true;
			Stop = true;
		}
	}

	if (stage == 34)		//음악실 오브젝트 상호작용
	{
		if (CCheckPtInRect(SkeletonBit, 950, 150))		//해골
		{
			Skeletonint = true;
			Stop = true;
		}
		if (CCheckPtInRect(SchoolDeskBit[2], 450, 80))		//음악실 책상
		{
			SchoolDesk3int = true;
			Stop = true;
		}
		if (CCheckPtInRect(SchoolDeskBit[3], 680, 80))		//음악실 음악책 책상
		{
			SchoolDesk3int = true;
			Stop = true;
		}

		if (CCheckPtInRect(ChairBit[2], 50, 180))		//음악실 피아노
		{
			if (bandal == 1)
			{
				EndPianoint = true;
			}
			if (bandal == 0)
			{
				Pianoint = true;
			}
			Stop = true;
		}
	}

	if (stage == 33)		//보건실
	{
		if (CCheckPtInRect(SchoolDeskBit[2], 0, 400))
		{
			Diaryint = true;
			Stop = true;
		}

		if (CCheckPtInRect(SkeletonBit, 100, 250))
		{
			Skeletonint = true;
			Stop = true;
		}
	}

	if (stage == 43)		//숙직실
	{
		if (CCheckPtInRect(KeyBit, 765, 200))
		{
			Keyint = true;
			Stop = true;
		}
	}

	if (stage == 44)		//교무실
	{
		if (CCheckPtInRect(SchoolDeskBit[2], 1200, 380))		//교무실 일기장
		{
			Diaryint = true;
			Stop = true;
		}
	}

	if (stage == 51)				//1-4반
	{
		for (int i = 0; i < 4; i++)
		{
			if (CCheckPtInRect(IronBarBit[0], 65 + i * 300, 470))		//감옥
			{
				Prisonint = true;
				Stop = true;
			}
		}
		if (CCheckPtInRect(SchoolDeskBit[2], 50, 150))		//책상
		{
			Diaryint = true;
			Stop = true;
		}
	}

	if (stage == 52)
	{
		if (CCheckPtInRect(SchoolDeskBit[2], 550, 500))		//1-5반 일기장
		{
			Diaryint = true;
			Stop = true;
		}

		if (CCheckPtInRect(BoardBit, -5, 100))		// 1-5반 칠판 비상대피도
		{
			Boardint = true;
		}
	}


}
//상호작용

void FontSet(HDC hdc, RECT grt, RECT nrt, const TCHAR Text[], const TCHAR name[], const TCHAR Ttext[], HBITMAP bit[] , int emotion, int size, COLORREF color, int width, int textbox)
{	
	RECT irt;
	SetRect(&irt, 170 + width, 580, 1120, 1000);

	if (P_IllBit[0] == bit[0])
	{
		TransBlt(hdc, 0, 100, bit[emotion], RGB(75, 75, 75));	// 주인공 일러스트
	}
	else if (N1_IllBit[0] == bit[0]) //수현
	{
		TransBlt(hdc, 900, 100, bit[emotion], RGB(75, 75, 75));	//NPC 일러스트
	}
	else if (N2_IllBit[0] == bit[0])  //화진
	{
		TransBlt(hdc, 800, 100, bit[emotion], RGB(75, 75, 75));	//NPC 일러스트
	}
	else if (N3_IllBit[0] == bit[0])  //미진
	{
		TransBlt(hdc, 900, 100, bit[emotion], RGB(75, 75, 75));	//NPC 일러스트
	}
	else if (N4_IllBit[0] == bit[0])  //수희
	{
		TransBlt(hdc, 900, 100, bit[emotion], RGB(75, 75, 75));	//NPC 일러스트
	}
	else if (Black[0] == bit[0])
	{
		TransBlt(hdc, 900, 100, bit[emotion], RGB(75, 75, 75));	//NPC 일러스트
	}

	if (Black[0] == bit[0])
	{
		TransBlt(hdc, 100, 480, TextBox[1], RGB(75, 75, 75));		// 범인 텍스트 박스
	}
	else
	{
		TransBlt(hdc, 100, 480, TextBox[0], RGB(75, 75, 75));		// 기본 텍스트 박스
	}

	HFONT font, oldfont;

	SetBkMode(hdc, TRANSPARENT);
	font = CreateFont(size, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 3, 2, 1,
		VARIABLE_PITCH | FF_ROMAN, "맑은 고딕");
	oldfont = (HFONT)SelectObject(hdc, font);
	SetTextColor(hdc, RGB(255, 255, 255));
	DrawText(hdc, text, -1, &grt, DT_WORDBREAK);
	DeleteObject(SelectObject(hdc, oldfont));

	font = CreateFont(40, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 3, 2, 1,
		VARIABLE_PITCH | FF_ROMAN, "맑은 고딕");
	oldfont = (HFONT)SelectObject(hdc, font);
	if (Black[0] == bit[0])
	{
		SetTextColor(hdc, RGB(255, 255, 255));		// 하얀 이름
	}
	else
	{
		SetTextColor(hdc, RGB(0, 0, 0));		// 검은 이름
	}
	DrawText(hdc, name, -1, &nrt, DT_WORDBREAK);
	DeleteObject(SelectObject(hdc, oldfont));

	font = CreateFont(size, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 3, 2, 1,
		VARIABLE_PITCH | FF_ROMAN, "맑은 고딕");
	oldfont = (HFONT)SelectObject(hdc, font);
	SetTextColor(hdc, color);
	DrawText(hdc, ttext, -1, &irt, DT_WORDBREAK);
	DeleteObject(SelectObject(hdc, oldfont));


	text = TEXT("");
	ttext = TEXT("");

}
//폰트 출력
void UpFontSet(HDC hdc, RECT grt, RECT nrt, const TCHAR Text[], const TCHAR name[], const TCHAR Ttext[], HBITMAP bit[], int emotion, int size, COLORREF color, int width, int textbox)
{
	RECT irt;
	SetRect(&irt, 170 + width, 580, 1120, 1000);

	if (P_IllBit[0] == bit[0])
	{
		TransBlt(hdc, 0, 100, bit[emotion], RGB(75, 75, 75));	// 주인공 일러스트
	}
	else if (N1_IllBit[0] == bit[0]) //수현
	{
		TransBlt(hdc, 900, 100, bit[emotion], RGB(75, 75, 75));	//NPC 일러스트
	}
	else if (N2_IllBit[0] == bit[0])  //화진
	{
		TransBlt(hdc, 800, 100, bit[emotion], RGB(75, 75, 75));	//NPC 일러스트
	}
	else if (N3_IllBit[0] == bit[0])  //미진
	{
		TransBlt(hdc, 900, 100, bit[emotion], RGB(75, 75, 75));	//NPC 일러스트
	}
	else if (N4_IllBit[0] == bit[0])  //수희
	{
		TransBlt(hdc, 900, 100, bit[emotion], RGB(75, 75, 75));	//NPC 일러스트
	}
	else if (Black[0] == bit[0])
	{
		TransBlt(hdc, 900, 100, bit[emotion], RGB(75, 75, 75));	//NPC 일러스트
	}
	TransBlt(hdc, 100, 480, TextBox[textbox], RGB(75, 75, 75));		// 기본 텍스트 박스
	SetBkMode(hdc, TRANSPARENT);

	HFONT font, oldfont;

	font = CreateFont(size, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 3, 2, 1,
		VARIABLE_PITCH | FF_ROMAN, "맑은 고딕");
	oldfont = (HFONT)SelectObject(hdc, font);
	SetTextColor(hdc, RGB(255, 255, 255));
	DrawText(hdc, text, -1, &grt, DT_WORDBREAK);
	DeleteObject(SelectObject(hdc, oldfont));

	font = CreateFont(40, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 3, 2, 1,
		VARIABLE_PITCH | FF_ROMAN, "맑은 고딕");
	oldfont = (HFONT)SelectObject(hdc, font);
	SetTextColor(hdc, RGB(0, 0, 0));
	DrawText(hdc, name, -1, &nrt, DT_WORDBREAK);
	SetTextColor(hdc, color);
	DrawText(hdc, ttext, -1, &irt, DT_WORDBREAK);
	DeleteObject(SelectObject(hdc, oldfont));

	text = TEXT("");
	ttext = TEXT("");
}
//폰트 출력
void DiaryFontSet(HDC hdc, const TCHAR text[],int size, COLORREF color)
{
	RECT drt;
	SetRect(&drt, 440, 120, 830, 600);

	HFONT font, oldfont;

	font = CreateFont(size, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 3, 2, 1,
		VARIABLE_PITCH | FF_ROMAN, "맑은 고딕");
	SetBkMode(hdc, TRANSPARENT);
	oldfont = (HFONT)SelectObject(hdc, font);
	SetTextColor(hdc, color);
	DrawText(hdc, text, -1, &drt, DT_WORDBREAK);

	DeleteObject(SelectObject(hdc, oldfont));

}
//일기장 폰트 출력
void DayFontSet(HDC hdc, const TCHAR text[], int size, COLORREF color, int index)
{
	RECT drt;
	SetRect(&drt, 220, 115, 400, 115 + 60 * index);

	HFONT font, oldfont;

	font = CreateFont(size, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 3, 2, 1,
		VARIABLE_PITCH | FF_ROMAN, "맑은 고딕");
	SetBkMode(hdc, TRANSPARENT);
	oldfont = (HFONT)SelectObject(hdc, font);
	SetTextColor(hdc, color);
	DrawText(hdc, text, -1, &drt, DT_WORDBREAK);

	DeleteObject(SelectObject(hdc, oldfont));
}
//일기장 날짜 출력

void Title(HDC hdc)
{
	DrawBitmap(hdc, 0, 0, TitleBit);
	switch (page)
	{
	case 0:
		Stop = true;
		OptionCheck = 0;
		if (Endingy <= -1000)
		{
			if (TitleSelect == 1)
			{
				TitleSelect = 2;
			}
		}
		
		if (TitleSelect == 1 && Endingy >= -1000)
		{
			TransBlt(hdc, 820, 480, ArrowBit, RGB(0, 0, 0));
		}
		else if (TitleSelect == 2)
		{
			TransBlt(hdc, 820, 545, ArrowBit, RGB(0, 0, 0));
		}
		else if (TitleSelect == 3)
		{
			TransBlt(hdc, 820, 610, ArrowBit, RGB(0, 0, 0));
		}
		break;
	case 1:
		if (TitleSelect == 1)
		{
			Titleint = false;
			Stop = false;
			page = 0;
		}
		else if (TitleSelect == 2)
		{
			OptionCheck = 1;
			DrawBitmap(hdc, 388, 265, OptionBit);

			if (OptionSelect == 1)
			{
				TransBlt(hdc, 475, 370, ArrowBit, RGB(0, 0, 0));
			}
			if (OptionSelect == 2)
			{
				TransBlt(hdc, 660, 370, ArrowBit, RGB(0, 0, 0));
			}
		}
		else if (TitleSelect == 3)
		{
			PostQuitMessage(0);
		}
		break;
	case 2:
		if (OptionSelect == 1)
		{
			BGMCheck = 1;
		}
		if (OptionSelect == 2)
		{
			BGMCheck = 0;
		}
		page = 0;
		break;
	}



}
//타이틀

void Start(HDC hdc)
{
	switch (page)
	{
	case 0:
		Stop = true;
		if (Titleint)
		{
			page = 0;
		}
		name = TEXT("이도현");
		text = TEXT("으윽.. 여긴 어디지?");
		FontSet(hdc, grt, nrt, text, name, ttext, P_IllBit, 0, FONTSIZE, RGB(0, 0, 0), 0, 0);
		break;
	case 1:
		if (!Titleint)
		{
			name = TEXT("시스템");
			text = TEXT("(움직이는 키는 방향키이고, 상호작용 키는 스페이스 바(space bar)입니다.)");
			FontSet(hdc, grt, nrt, text, name, ttext, System, 0, FONTSIZE, RGB(0, 0, 0), 0, 0);
		}
		break;
	case 2:
		name = TEXT("시스템");
		text = TEXT("(이 게임은 대사가 아주 중요한 게임입니다.)");
		FontSet(hdc, grt, nrt, text, name, ttext, System, 0, FONTSIZE, RGB(0, 0, 0), 0, 0);
		break;
	case 3:
		name = TEXT("시스템");
		text = TEXT("(이 게임은 대사가 아주 중요한 게임입니다. 꼭 확인 해주세요)");
		FontSet(hdc, grt, nrt, text, name, ttext, System, 0, FONTSIZE, RGB(0, 0, 0), 0, 0);
		break;
	default:
		page = 0;
		Stop = false;
		Startint = false;
		break;
	}
}
//시작시 설명
void MainDoor(HDC hdc)
{
	switch (page)
	{
	case 0:
		Stop = true;
		if (Door == 0)
		{
			name = TEXT("시스템");
			text = TEXT("문이 열리지 않는다.");
			FontSet(hdc, grt, nrt, text, name, ttext, System, 0, FONTSIZE, RGB(0, 0, 0), 0, 0);
			if (Sound == 0)
			{
				PlaySound("Close.wav", NULL, SND_ASYNC);
				Sound = 1;
			}
		}
		else
		{
			name = TEXT("XXX");
			text = TEXT("잠깐");
			FontSet(hdc, grt, nrt, text, name, ttext, Black, 0, FONTSIZE, RGB(0, 0, 0), 0, 0);
		}
		break;
	case 1:
		if (Door == 0)
		{
			name = TEXT("이도현");
			text = TEXT("젠장!");
			FontSet(hdc, grt, nrt, text, name, ttext, P_IllBit, 2, FONTSIZE, RGB(0, 0, 0), 0, 0);
		}
		else
		{
			name = TEXT("XXX");
			text = TEXT("잠깐 나가기 전에 물어보고 싶은 게 있어.");
			FontSet(hdc, grt, nrt, text, name, ttext, Black, 0, FONTSIZE, RGB(0, 0, 0), 0, 0);
		}
		break;
	case 2:
		if (Door == 0)
		{
			page = 100;
		}
		else
		{
			name = TEXT("XXX");
			text = TEXT("왜 그때 나를 적극적으로 도와주지 않았지?");
			FontSet(hdc, grt, nrt, text, name, ttext, Black, 0, FONTSIZE, RGB(0, 0, 0), 0, 0);
		}
		break;
	case 3:
		name = TEXT("이도현");
		text = TEXT("….나도 아직까지 후회하며 살고 있었어…");
		FontSet(hdc, grt, nrt, text, name, ttext, P_IllBit, 0, FONTSIZE, RGB(0, 0, 0), 0, 0);
		break;
	case 4:
		name = TEXT("XXX");
		text = TEXT("…..");
		FontSet(hdc, grt, nrt, text, name, ttext, Black, 0, FONTSIZE, RGB(0, 0, 0), 0, 0);
		break;
	case 5:
		name = TEXT("XXX");
		text = TEXT("알겠으니까 나가봐.");
		FontSet(hdc, grt, nrt, text, name, ttext, Black, 0, FONTSIZE, RGB(0, 0, 0), 0, 0);
		break;
	default:
		if (Door == 1)
		{
			Endingint = true;
		}
		Sound = 0;
		page = 0;
		Stop = false;
		MainDoorint = false;
		break;
	}
}
//정문 상호작용
void Skeleton(HDC hdc)
{
	switch (page)
	{
	case 0:
		Stop = true;
		if (Class1Door == 0 && stage == 34)
		{
			name = TEXT("시스템");
			text = TEXT("교복을 입은 해골 위에 교복을 입은 학생들의 사진이 있다.");
			FontSet(hdc, grt, nrt, text, name, ttext, System, 0, FONTSIZE, RGB(0, 0, 0), 0, 0);
		}
		else if (stage == 33)
		{
			name = TEXT("시스템");
			text = TEXT("(상태가 10년 이상은 된 것 같다.)");
			FontSet(hdc, grt, nrt, text, name, ttext, System, 0, FONTSIZE, RGB(0, 0, 0), 0, 0);
		}
		else if (Class1Door == 2)
		{
			name = TEXT("시스템");
			text = TEXT("해골 위에 하얀 국화꽃이 놓여 있다.");
			FontSet(hdc, grt, nrt, text, name, ttext, System, 0, FONTSIZE, RGB(0, 0, 0), 0, 0);
		}
		break;
	case 1:
		if (Class1Door == 0 && stage == 34)
		{
			name = TEXT("이도현");
			text = TEXT("으악!!... 이… 이건.. 우리 중학교 교복인데!?....");
			FontSet(hdc, grt, nrt, text, name, ttext, P_IllBit, 3, FONTSIZE, RGB(0, 0, 0), 0, 0);
		}
		else
		{
			page = 10;
		}
		break;
	default:
		page = 0;
		Stop = false;
		Skeletonint = false;
		break;
	}
}
//해골 상호작용
void SchoolDesk3(HDC hdc)
{
	switch (page)
	{
	case 0:
		Stop = true;
		if (stage == 34 && CCheckPtInRect(SchoolDeskBit[2], 450, 80))
		{
			name = TEXT("이도현");
			text = TEXT("이건... 메모지인가?");
			FontSet(hdc, grt, nrt, text, name, ttext, P_IllBit, 0, FONTSIZE, RGB(0, 0, 0), 0, 0);
		}
		else if (stage == 34 && CCheckPtInRect(SchoolDeskBit[3], 680, 80))
		{
			name = TEXT("이도현");
			text = TEXT("음악책이다.");
			FontSet(hdc, grt, nrt, text, name, ttext, P_IllBit, 0, FONTSIZE, RGB(0, 0, 0), 0, 0);
		}
		break;
	case 1:
		if (stage == 34 && CCheckPtInRect(SchoolDeskBit[2], 450, 80))
		{
			name = TEXT("이도현");
			text = TEXT("궁금하면..");
			FontSet(hdc, grt, nrt, text, name, ttext, P_IllBit, 0, FONTSIZE, RGB(0, 0, 0), 0, 0);
		}
		else if (stage == 34 && CCheckPtInRect(SchoolDeskBit[3], 680, 80))
		{
			name = TEXT("시스템");
			text = TEXT("## 라장조 : 라를 으뜸음으로 하는 장음계이다.\n ex) 레를 도로 치는 식으로 한 음씩 내려서 치면 된다.");
			FontSet(hdc, grt, nrt, text, name, ttext, System, 0, FONTSIZE, RGB(0, 0, 0), 0, 0);
		}
		break;
	case 2:
		if (stage == 34 && CCheckPtInRect(SchoolDeskBit[2], 450, 80))
		{
			name = TEXT("이도현");
			text = TEXT("궁금하면.. 1-5반으로... 와?..");
			FontSet(hdc, grt, nrt, text, name, ttext, P_IllBit, 0, FONTSIZE, RGB(0, 0, 0), 0, 0);
		}
		else if (stage == 13)
		{
			name = TEXT("시스템");
			text = TEXT("일기장을 얻었습니다.");
			FontSet(hdc, grt, nrt, text, name, ttext, System, 0, FONTSIZE, RGB(0, 0, 0), 0, 0);
			DayCheck = 2;
		}
		else
		{
			page = 10;
		}
		break;
	case 3:
		if (stage == 34)
		{
			name = TEXT("이도현");
			text = TEXT("궁금하면.. 1-5반으로... 와?.. 이게 무슨 의미지...?");
			FontSet(hdc, grt, nrt, text, name, ttext, P_IllBit, 0, FONTSIZE, RGB(0, 0, 0), 0, 0);
		}
		break;
	case 4:
		if (stage == 34)
		{
			name = TEXT("이도현");
			text = TEXT("아마 1-5반은 복도 맨 오른쪽 밑에 있었지?...");
			FontSet(hdc, grt, nrt, text, name, ttext, P_IllBit, 0, FONTSIZE, RGB(0, 0, 0), 0, 0);
		}
		break;
	default:
		page = 0;
		Stop = false;
		SchoolDesk3int = false;
		break;
	}
}
//책이 있는 책상 상호작용
void Diary(HDC hdc)
{
	switch (page)
	{
	case 0:
		Stop = true;
		if (DayCheck == 0 && stage == 52)	//음악실
		{
			name = TEXT("이도현");
			text = TEXT("일기장?...누구 거지... 옆에는 창고..열쇠인가..?");
			FontSet(hdc, grt, nrt, text, name, ttext, P_IllBit, 0, FONTSIZE, RGB(0, 0, 0), 0, 0);
		}
		else if (stage == 13 && DayCheck == 1)	//창고
		{
			name = TEXT("시스템");
			text = TEXT("누구 거인지 알 수 없는 일기장이 놓여있다.");
			FontSet(hdc, grt, nrt, text, name, ttext, System, 0, FONTSIZE, RGB(0, 0, 0), 0, 0);
		}
		else if (stage == 44 && DayCheck == 2)
		{
			name = TEXT("이도현");
			text = TEXT("(! 또 일기장이 놓여 있다.)");
			FontSet(hdc, grt, nrt, text, name, ttext, P_IllBit, 3, FONTSIZE, RGB(0, 0, 0), 0, 0);
		}
		else if (stage == 51 && DayCheck == 3)
		{
			name = TEXT("이도현");
			text = TEXT("또…일기장…");
			FontSet(hdc, grt, nrt, text, name, ttext, P_IllBit, 0, FONTSIZE, RGB(0, 0, 0), 0, 0);
		}
		else if (stage == 23 && DayCheck == 4)
		{
			name = TEXT("이도현");
			text = TEXT("또 일기장이야? 지긋지긋해! 날 이렇게 갖고 노는 이유가 뭐야?!!");
			FontSet(hdc, grt, nrt, text, name, ttext, P_IllBit, 2, FONTSIZE, RGB(0, 0, 0), 0, 0);
		}
		else if (stage == 33 && DayCheck == 5)
		{
			name = TEXT("시스템");
			text = TEXT("여섯 번째 일기장을 볼 수 있습니다.");
			FontSet(hdc, grt, nrt, text, name, ttext, System, 0, FONTSIZE, RGB(0, 0, 0), 0, 0);
		}
		else if (stage == 11 && DayCheck == 6)
		{
			name = TEXT("시스템");
			text = TEXT("일곱 번째 일기장을 볼 수 있습니다.");
			FontSet(hdc, grt, nrt, text, name, ttext, System, 0, FONTSIZE, RGB(0, 0, 0), 0, 0);
		}
		else //빈 책상
		{
			name = TEXT("이도현");
			text = TEXT("빈 책상이네..");
			FontSet(hdc, grt, nrt, text, name, ttext, P_IllBit, 0, FONTSIZE, RGB(0, 0, 0), 0, 0);
		}
		break;
	case 1:
		if (DayCheck == 0 && stage == 52)	//음악실
		{
			name = TEXT("시스템");
			text = TEXT("일기장과 창고열쇠를 얻었습니다.");
			FontSet(hdc, grt, nrt, text, name, ttext, System, 0, FONTSIZE, RGB(0, 0, 150), 0, 0);
		}
		else if (stage == 13 && DayCheck == 1)	//창고
		{
			name = TEXT("이도현");
			text = TEXT("어.. 왜 이 곳에 또 일기장이…");
			FontSet(hdc, grt, nrt, text, name, ttext, P_IllBit, 0, FONTSIZE, RGB(0, 0, 0), 0, 0);
		}
		else if (stage == 44 && DayCheck == 2)
		{
			name = TEXT("시스템");
			text = TEXT("세 번째 일기장을 볼 수 있습니다.");
			FontSet(hdc, grt, nrt, text, name, ttext, System, 0, FONTSIZE, RGB(0, 0, 0), 0, 0);
		}
		else if (stage == 51 && DayCheck == 3)
		{
			name = TEXT("시스템");
			text = TEXT("네 번째 일기장을 볼 수 있습니다.");
			FontSet(hdc, grt, nrt, text, name, ttext, System, 0, FONTSIZE, RGB(0, 0, 0), 0, 0);
		}
		else if (stage == 23 && DayCheck == 4)
		{
			name = TEXT("시스템");
			text = TEXT(".....");
			FontSet(hdc, grt, nrt, text, name, ttext, System, 2, FONTSIZE, RGB(0, 0, 0), 0, 0);
		}
		else if (stage == 33 && DayCheck == 5)
		{
			DayCheck = 6;
		}
		else if (stage == 11 && DayCheck == 6)
		{
			DayCheck = 7;
		}
		else //빈 책상
		{
			page = 10;
		}
		break;
	case 2:
		if (DayCheck == 0 && stage == 52)	//음악실
		{
			name = TEXT("시스템");
			text = TEXT("I키를 누르면 일기장을 볼 수 있습니다.");
			FontSet(hdc, grt, nrt, text, name, ttext, System, 0, FONTSIZE, RGB(0, 0, 150), 0, 0);
		}
		else if (stage == 13 && DayCheck == 1)	//창고
		{
			name = TEXT("시스템");
			text = TEXT("두 번째 일기장을 볼 수 있습니다.");
			FontSet(hdc, grt, nrt, text, name, ttext, System, 0, FONTSIZE, RGB(0, 0, 150), 0, 0);
		}
		else if (stage == 23 && DayCheck == 4)
		{
			name = TEXT("시스템");
			text = TEXT("..........");
			FontSet(hdc, grt, nrt, text, name, ttext, System, 0, FONTSIZE, RGB(0, 0, 0), 0, 0);
		}
		else if (stage == 44 && DayCheck == 2)
		{
			DayCheck = 3;
		}
		else if (stage == 51 && DayCheck == 3)
		{
			DayCheck = 4;
		}
		else //빈 책상
		{
			page = 10;
		}
		break;
	case 3:
		if (stage == 52 && DayCheck == 0)
		{
			DayCheck = 1;
		}
		else if (stage == 13 && DayCheck == 1)
		{
			DayCheck = 2;
		}
		else if (stage == 23 && DayCheck == 4)
		{
			name = TEXT("시스템");
			text = TEXT("다섯 번째 일기장을 볼 수 있습니다.");
			FontSet(hdc, grt, nrt, text, name, ttext, System, 0, FONTSIZE, RGB(0, 0, 0), 0, 0);
		}
		else
		{
			page = 10;
		}
		break;
	case 4:
		if (stage == 23 && DayCheck == 4)
		{
			DayCheck = 5;
		}
		else
		{
			page = 10;
		}
		break;
	default:
		if (Inventory = -1)
		{
			Inventory = 0;
		}
		if (OpenDoor == 0)
		{
			OpenDoor = 1;
		}
		if (DayCheck == 5)
		{
			Time = 0;
		}
		page = 0;
		Stop = false;
		Diaryint = false;
		break;
	}
}
//일기장 상호작용
void CloseDoor(HDC hdc)
{
	switch (page)
	{
	case 0:
		Stop = true;
		name = TEXT("시스템");
		text = TEXT("자물쇠에 비밀번호가 달려있다.");
		FontSet(hdc, grt, nrt, text, name, ttext, System, 0, FONTSIZE, RGB(0, 0, 0), 0, 0);
		if (stage == 1 && y < 190 && x > 920 && x < 1100)
		{
			name = TEXT("시스템");
			text = TEXT("열쇠로 여는 자물쇠가 있다.");
			FontSet(hdc, grt, nrt, text, name, ttext, System, 0, FONTSIZE, RGB(0, 0, 0), 0, 0);
		}

		if (stage == 5 && y < 190 && x > 920 && x < 1100)
		{
			name = TEXT("시스템");
			text = TEXT("문에 나무들로 못질을 해 들어갈 수 없다.");
			FontSet(hdc, grt, nrt, text, name, ttext, System, 0, FONTSIZE, RGB(0, 0, 0), 0, 0);
		}
		break;
	case 1:
		if (stage == 1 && y < 190 && x > 920 && x < 1100)
		{
			page = 100;
		}
		else
		{
			name = TEXT("시스템");
			text = TEXT("비밀번호를 입력하시오.");
			FontSet(hdc, grt, nrt, text, name, ttext, System, 0, FONTSIZE, RGB(0, 0, 0), 0, 0);
		}
		if (stage == 5 && y < 190 && x > 920 && x < 1100)
		{
			name = TEXT("이도현");
			text = TEXT("왜 이 문만…");
			FontSet(hdc, grt, nrt, text, name, ttext, P_IllBit, 0, FONTSIZE, RGB(0, 0, 0), 0, 0);
		}
		break;
	case 2:
		if (y < 190 && x > 50 && x < 120 && stage == 4)
		{
			SelectButton = 1;

			name = TEXT("시스템");
			text = TEXT("비밀번호 4자리를 입력하시오.");
			FontSet(hdc, grt, nrt, text, name, ttext, System, 0, FONTSIZE, RGB(0, 0, 0), 400, 0);
			TransBlt(hdc, 500, 100, LockBit, RGB(75, 75, 75));
			PWTransBlt(hdc, 660, 320, LockPWBit, RGB(75, 75, 75), pwfrm1);
			PWTransBlt(hdc, 660, 370, LockPWBit, RGB(75, 75, 75), pwfrm2);
			PWTransBlt(hdc, 660, 420, LockPWBit, RGB(75, 75, 75), pwfrm3);
			PWTransBlt(hdc, 660, 470, LockPWBit, RGB(75, 75, 75), pwfrm4);

			TransBlt(hdc, 660, 320 + (Select - 1) * 50, SelectBit, RGB(75, 75, 75));

			pw[0] = pwfrm1;
			pw[1] = pwfrm2;
			pw[2] = pwfrm3;
			pw[3] = pwfrm4;
		}
		else if (stage == 5 && y > 435 && x < 600 && Class4Door == 0)
		{
			SelectButton = 1;

			name = TEXT("시스템");
			text = TEXT("비밀번호 4자리를 입력하시오.");
			FontSet(hdc, grt, nrt, text, name, ttext, System, 0, FONTSIZE, RGB(0, 0, 0), 400, 0);

			TransBlt(hdc, 500, 100, LockBit, RGB(75, 75, 75));
			PWTransBlt(hdc, 660, 320, LockPWBit, RGB(75, 75, 75), pwfrm1);
			PWTransBlt(hdc, 660, 370, LockPWBit, RGB(75, 75, 75), pwfrm2);
			PWTransBlt(hdc, 660, 420, LockPWBit, RGB(75, 75, 75), pwfrm3);
			PWTransBlt(hdc, 660, 470, LockPWBit, RGB(75, 75, 75), pwfrm4);

			TransBlt(hdc, 660, 320 + (Select - 1) * 50, SelectBit, RGB(75, 75, 75));

			pw[0] = pwfrm1;
			pw[1] = pwfrm2;
			pw[2] = pwfrm3;
			pw[3] = pwfrm4;
		}
		else if (stage == 4 && y < 190 && x > 930 && x < 1010 && BedDoor == 0)
		{
			SelectButton = 1;

			name = TEXT("시스템");
			text = TEXT("비밀번호 4자리를 입력하시오.");
			FontSet(hdc, grt, nrt, text, name, ttext, System, 0, FONTSIZE, RGB(0, 0, 0), 400, 0);

			TransBlt(hdc, 500, 100, LockBit, RGB(75, 75, 75));
			PWTransBlt(hdc, 660, 320, LockPWBit, RGB(75, 75, 75), pwfrm1);
			PWTransBlt(hdc, 660, 370, LockPWBit, RGB(75, 75, 75), pwfrm2);
			PWTransBlt(hdc, 660, 420, LockPWBit, RGB(75, 75, 75), pwfrm3);
			PWTransBlt(hdc, 660, 470, LockPWBit, RGB(75, 75, 75), pwfrm4);

			TransBlt(hdc, 660, 320 + (Select - 1) * 50, SelectBit, RGB(75, 75, 75));

			pw[0] = pwfrm1;
			pw[1] = pwfrm2;
			pw[2] = pwfrm3;
			pw[3] = pwfrm4;
		}
		else if (stage == 3 && y < 190 && x > 930 && x < 1010 && HealDoor == 0)
		{
			SelectButton = 1;

			name = TEXT("시스템");
			text = TEXT("비밀번호 4자리를 입력하시오.");
			FontSet(hdc, grt, nrt, text, name, ttext, System, 0, FONTSIZE, RGB(0, 0, 0), 400, 0);

			TransBlt(hdc, 500, 100, LockBit, RGB(75, 75, 75));
			PWTransBlt(hdc, 660, 320, LockPWBit, RGB(75, 75, 75), pwfrm1);
			PWTransBlt(hdc, 660, 370, LockPWBit, RGB(75, 75, 75), pwfrm2);
			PWTransBlt(hdc, 660, 420, LockPWBit, RGB(75, 75, 75), pwfrm3);
			PWTransBlt(hdc, 660, 470, LockPWBit, RGB(75, 75, 75), pwfrm4);

			TransBlt(hdc, 660, 320 + (Select - 1) * 50, SelectBit, RGB(75, 75, 75));

			pw[0] = pwfrm1;
			pw[1] = pwfrm2;
			pw[2] = pwfrm3;
			pw[3] = pwfrm4;
		}
		else if (stage == 3 && y < 190 && x > 930 && x < 1010 && NPCFree == 0)
		{
			SelectButton = 1;

			name = TEXT("시스템");
			text = TEXT("비밀번호 4자리를 입력하시오.");
			FontSet(hdc, grt, nrt, text, name, ttext, System, 0, FONTSIZE, RGB(0, 0, 0), 400, 0);

			TransBlt(hdc, 500, 100, LockBit, RGB(75, 75, 75));
			PWTransBlt(hdc, 660, 320, LockPWBit, RGB(75, 75, 75), pwfrm1);
			PWTransBlt(hdc, 660, 370, LockPWBit, RGB(75, 75, 75), pwfrm2);
			PWTransBlt(hdc, 660, 420, LockPWBit, RGB(75, 75, 75), pwfrm3);
			PWTransBlt(hdc, 660, 470, LockPWBit, RGB(75, 75, 75), pwfrm4);

			TransBlt(hdc, 660, 320 + (Select - 1) * 50, SelectBit, RGB(75, 75, 75));

			pw[0] = pwfrm1;
			pw[1] = pwfrm2;
			pw[2] = pwfrm3;
			pw[3] = pwfrm4;
		}
		else if (stage == 1 && y > 435 && x < 600 && NPCFree == 0)
		{
			SelectButton = 1;

			name = TEXT("시스템");
			text = TEXT("비밀번호 4자리를 입력하시오.");
			FontSet(hdc, grt, nrt, text, name, ttext, System, 0, FONTSIZE, RGB(0, 0, 0), 400, 0);

			TransBlt(hdc, 500, 100, LockBit, RGB(75, 75, 75));
			PWTransBlt(hdc, 660, 320, LockPWBit, RGB(75, 75, 75), pwfrm1);
			PWTransBlt(hdc, 660, 370, LockPWBit, RGB(75, 75, 75), pwfrm2);
			PWTransBlt(hdc, 660, 420, LockPWBit, RGB(75, 75, 75), pwfrm3);
			PWTransBlt(hdc, 660, 470, LockPWBit, RGB(75, 75, 75), pwfrm4);

			TransBlt(hdc, 660, 320 + (Select - 1) * 50, SelectBit, RGB(75, 75, 75));

			pw[0] = pwfrm1;
			pw[1] = pwfrm2;
			pw[2] = pwfrm3;
			pw[3] = pwfrm4;
		}
		else
		{
			page = 10;
		}
		break;
	case 3:
		if (y < 190 && x > 50 && x < 120 && stage == 4)
		{
			if (PWCheck[0] == pw[0] && PWCheck[1] == pw[1] && PWCheck[2] == pw[2] && PWCheck[3] == pw[3])	//교무실 비번
			{
				name = TEXT("이도현");
				text = TEXT("!!열렸다!");
				FontSet(hdc, grt, nrt, text, name, ttext, P_IllBit, 3, FONTSIZE, RGB(0, 0, 0), 0, 0);
				OpenDoor = 4;
				hint = 0;
				if (Sound == 0)
				{
					PlaySound("Open.wav", NULL, SND_ASYNC);
					Sound = 1;
				}
			}
			else
			{
				name = TEXT("이도현");
				text = TEXT("젠장…틀린건가");
				FontSet(hdc, grt, nrt, text, name, ttext, P_IllBit, 2, FONTSIZE, RGB(0, 0, 0), 0, 0);
				if (Sound == 0)
				{
					PlaySound("Close.wav", NULL, SND_ASYNC);
					Sound = 1;
				}
			}
		}
		else if (stage == 5 && y > 435 && x < 600 && Class4Door == 0)
		{
		
			if (PWCheck2[0] == pw[0] && PWCheck2[1] == pw[1] && PWCheck2[2] == pw[2] && PWCheck2[3] == pw[3])	//1-4반 비번
			{
				name = TEXT("시스템");
				text = TEXT("철컥");
				FontSet(hdc, grt, nrt, text, name, ttext, System, 0, FONTSIZE, RGB(0, 0, 0), 0, 0);
				Dap = 1;
				if (Sound == 0)
				{
					PlaySound("Open.wav", NULL, SND_ASYNC);
					Sound = 1;
				}
			}
			else if(Dap!=1)
			{
				name = TEXT("시스템");
				text = TEXT("철컥!철컥!");
				FontSet(hdc, grt, nrt, text, name, ttext, System, 0, FONTSIZE, RGB(0, 0, 0), 0, 0);
				if (Sound == 0)
				{
					PlaySound("Close.wav", NULL, SND_ASYNC);
					Sound = 1;
				}
			}
			else
			{
				page = 10;
			}
		}
		else if (stage == 4 && y < 190 && x > 930 && x < 1010 && BedDoor == 0)
		{
			if (PWCheck3[0] == pw[0] && PWCheck3[1] == pw[1] && PWCheck3[2] == pw[2] && PWCheck3[3] == pw[3])	//숙직실 비번
			{
				name = TEXT("시스템");
				text = TEXT("철컥");
				FontSet(hdc, grt, nrt, text, name, ttext, System, 0, FONTSIZE, RGB(0, 0, 0), 0, 0);
				Dap = 1;
				if (Sound == 0)
				{
					PlaySound("Open.wav", NULL, SND_ASYNC);
					Sound = 1;
				}
			}
			else if (Dap != 1)
			{
				name = TEXT("시스템");
				text = TEXT("철컥!철컥!");
				FontSet(hdc, grt, nrt, text, name, ttext, System, 0, FONTSIZE, RGB(0, 0, 0), 0, 0);
				if (Sound == 0)
				{
					PlaySound("Close.wav", NULL, SND_ASYNC);
					Sound = 1;
				}
			}
			else
			{
				page = 10;
			}
		}
		else if (stage == 3 && y < 190 && x > 930 && x < 1010 && HealDoor == 0)
		{
			if (PWCheck4[0] == pw[0] && PWCheck4[1] == pw[1] && PWCheck4[2] == pw[2] && PWCheck4[3] == pw[3])	//보건실 비번
			{
				name = TEXT("시스템");
				text = TEXT("철컥");
				FontSet(hdc, grt, nrt, text, name, ttext, System, 0, FONTSIZE, RGB(0, 0, 0), 0, 0);
				Dap = 1;
				if (Sound == 0)
				{
					PlaySound("Open.wav", NULL, SND_ASYNC);
					Sound = 1;
				}
			}
			else if (Dap != 1)
			{
				name = TEXT("시스템");
				text = TEXT("철컥!철컥!");
				FontSet(hdc, grt, nrt, text, name, ttext, System, 0, FONTSIZE, RGB(0, 0, 0), 0, 0);
				if (Sound == 0)
				{
					PlaySound("Close.wav", NULL, SND_ASYNC);
					Sound = 1;
				}
			}
			else
			{
				page = 10;
			}
		}
		else if (stage == 3 && y < 190 && x > 930 && x < 1010 && NPCFree == 0)
		{
			name = TEXT("시스템");
			text = TEXT("철컥철컥!");
			if (Sound == 0)
			{
				PlaySound("Close.wav", NULL, SND_ASYNC);
				Sound = 1;
			}
		}
		else if (stage == 1 && y > 435 && x < 600 && NPCFree == 0)
		{
			name = TEXT("시스템");
			text = TEXT("철컥철컥!");
			FontSet(hdc, grt, nrt, text, name, ttext, System, 0, FONTSIZE, RGB(0, 0, 0), 400, 0);
			if (Sound == 0)
			{
				PlaySound("Close.wav", NULL, SND_ASYNC);
				Sound = 1;
			}
		}
		else
		{
			page = 10;
		}
		break;
	case 4:
		if (FirstRead >= 2 && y < 190 && x > 50 && x < 120 && stage == 4 && OpenDoor == 3 && PWCheck != pw && hint == 2)
		{
			name = TEXT("이도현");
			text = TEXT("(일기장에 힌트가 있나 찾아보자.)");

			FontSet(hdc, grt, nrt, text, name, ttext, P_IllBit, 0, FONTSIZE, RGB(0, 0, 0), 400, 0);
		}
		else if (stage == 5 && y > 435 && x < 600 && Class4Door == 0)
		{
	
			if (Dap == 1)
			{
				name = TEXT("이도현");
				text = TEXT("역시!");
				FontSet(hdc, grt, nrt, text, name, ttext, P_IllBit, 0, FONTSIZE, RGB(0, 0, 0), 0, 0);
			}
			
		}

		if (hint == 2 && Dap == 0)
		{
		name = TEXT("이도현");
		text = TEXT("흠…일기장과 악보에 힌트가 있으려나.");
		FontSet(hdc, grt, nrt, text, name, ttext, P_IllBit, 0, FONTSIZE, RGB(0, 0, 0), 0, 0);
		}
		else if (Dap != 1)
		{
			page = 10;
		}

		break;
	default:
		if (!PWDoor44)
		{
			PWDoor44 = true;
		}

		if (OpenDoor < 3 && FirstRead >= 2)
		{
			OpenDoor = 3;
		}
		if (hint == 2)
		{
			hint %= 2;
		}
		hint++;
		if (Dap == 1)
		{
			hint = 0;
		}
		if (Dap == 1 && stage == 5 && y > 435 && x < 600)
		{
			Class4Door = 1;
		}
		if (Dap == 1 && stage == 4 && y < 190 && x > 930)
		{
			BedDoor = 1;
		}
		if (Dap == 1 && stage == 3 && y < 190 && x > 930)
		{
			HealDoor = 1;
		}
		Sound = 0;
		Dap = 0;
		SelectButton = -1;
		page = 0;
		Stop = false;
		CloseDoorint = false;
		break;
	}
}
//잠긴문 상호작용
void CloseDoor2(HDC hdc)
{
	switch (page)
	{
	case 0:
		Stop = true;
		name = TEXT("시스템");
		text = TEXT("자물쇠에 비밀번호가 달려있다.");
		FontSet(hdc, grt, nrt, text, name, ttext, System, 0, FONTSIZE, RGB(0, 0, 0), 0, 0);
		break;
	case 1:
		name = TEXT("시스템");
		text = TEXT("비밀번호를 입력하시오.");
		FontSet(hdc, grt, nrt, text, name, ttext, System, 0, FONTSIZE, RGB(0, 0, 0), 0, 0);
		break;
	case 2:
		SelectButton = 1;

		name = TEXT("시스템");
		text = TEXT("비밀번호 4자리를 입력하시오.");
		FontSet(hdc, grt, nrt, text, name, ttext, System, 0, FONTSIZE, RGB(0, 0, 0), 400, 0);
		TransBlt(hdc, 500, 100, LockBit, RGB(75, 75, 75));
		PWTransBlt(hdc, 660, 320, LockPWBit, RGB(75, 75, 75), pwfrm1);
		PWTransBlt(hdc, 660, 370, LockPWBit, RGB(75, 75, 75), pwfrm2);
		PWTransBlt(hdc, 660, 420, LockPWBit, RGB(75, 75, 75), pwfrm3);
		PWTransBlt(hdc, 660, 470, LockPWBit, RGB(75, 75, 75), pwfrm4);

		TransBlt(hdc, 660, 320 + (Select - 1) * 50, SelectBit, RGB(75, 75, 75));

		pw[0] = pwfrm1;
		pw[1] = pwfrm2;
		pw[2] = pwfrm3;
		pw[3] = pwfrm4;

		break;
	case 3:
		if (PWCheck5[0] == pw[0] && PWCheck5[1] == pw[1] && PWCheck5[2] == pw[2] && PWCheck5[3] == pw[3])
		{
			name = TEXT("시스템");
			text = TEXT("철컥!");
			FontSet(hdc, grt, nrt, text, name, ttext, System, 0, FONTSIZE, RGB(0, 0, 0), 0, 0);
			Dap = 1;
			if (Sound == 0)
			{
				PlaySound("Open.wav", NULL, SND_ASYNC);
				Sound = 1;
			}
		}
		else
		{
			name = TEXT("시스템");
			text = TEXT("철컥철컥!");
			FontSet(hdc, grt, nrt, text, name, ttext, System, 0, FONTSIZE, RGB(0, 0, 0), 0, 0);
			if (Sound == 0)
			{
				PlaySound("Close.wav", NULL, SND_ASYNC);
				Sound = 1;
			}
		}
		if (hint == 2 && Dap == 0)
		{
			name = TEXT("이도현");
			text = TEXT("주변에 단서가 더 없나 찾아봐야겠어..");
			FontSet(hdc, grt, nrt, text, name, ttext, P_IllBit, 0, FONTSIZE, RGB(0, 0, 0), 0, 0);
		}
		break;
	default:
		if (hint == 2)
		{
			hint %= 2;
		}
		hint++;
		if (Dap == 1)
		{
			hint = 0;
		}
		if (Dap == 1)
		{
			Class2Door = 1;
		}
		Sound = 0;
		Dap = 0;
		SelectButton = -1;
		page = 0;
		Stop = false;
		CloseDoor2int = false;
		break;
	}
}
//1-2반 문 상호작용
void Board(HDC hdc)
{
	switch (page)
	{
	case 0:
		Stop = true;
		if (stage == 52 && Map >= 0)
		{
			name = TEXT("이도현");
			text = TEXT("칠판이다.");
			FontSet(hdc, grt, nrt, text, name, ttext, P_IllBit, 0, FONTSIZE, RGB(0, 0, 0), 0, 0);
		}
		else if (stage == 52 && Map == -1)
		{
			name = TEXT("시스템");
			text = TEXT("비상대피도를 얻었습니다");
			FontSet(hdc, grt, nrt, text, name, ttext, System, 0, FONTSIZE, RGB(0, 0, 0), 0, 0);
		}
		break;
	case 1:
		if (stage == 52 && Map == -1)
		{
			name = TEXT("이도현");
			text = TEXT("비상대피도? 좋아 이거면 이동할 때 도움이 되겠어.");
			FontSet(hdc, grt, nrt, text, name, ttext, P_IllBit, 0, FONTSIZE, RGB(0, 0, 0), 0, 0);
		}
		else
		{
			page++;
		}
		break;
	case 2:
		if (stage == 52 && Map == -1)
		{
			name = TEXT("시스템");
			text = TEXT("M키를 누르면 비상대피도를 볼 수 있습니다.");
			FontSet(hdc, grt, nrt, text, name, ttext, System, 0, FONTSIZE, RGB(0, 0, 0), 0, 0);
		}
		else
		{
			page++;
		}
		break;
	default:
		if (stage == 52 && Map == -1)
		{
			Map = 0;
		}
		page = 0;
		Stop = false;
		Boardint = false;
		break;
	}
}
//칠판 상호작용
void Open(HDC hdc)
{
	switch (page)
	{
	case 0:
		Stop = true;
		if (OpenDoor == 1)
		{
			name = TEXT("시스템");
			text = TEXT("철컥!");
			FontSet(hdc, grt, nrt, text, name, ttext, System, 0, FONTSIZE, RGB(0, 0, 0), 0, 0);
			if (Sound == 0)
			{
				PlaySound("Open.wav", NULL, SND_ASYNC);
				Sound = 1;
			}
		}
		else if (OpenDoor == 4 && stage == 44)
		{
			name = TEXT("???");
			text = TEXT("(치직...)");
			FontSet(hdc, grt, nrt, text, name, ttext, Black, 0, FONTSIZE, RGB(0, 0, 0), 0, 0);
			if (Sound == 0)
			{
				PlaySound("Noise.wav", NULL, SND_ASYNC);
				Sound = 1;
			}
		}
		else if (OpenDoor == 5 && stage == 4)
		{
			name = TEXT("???");
			text = TEXT("(...치직) 아 맞다! 마지막으로 너 이 교무실에서 무슨 일이 발생했었는지 궁금해서 들어왔었지?");
			FontSet(hdc, grt, nrt, text, name, ttext, Black, 0, FONTSIZE, RGB(0, 0, 0), 0, 0);
			if (Sound == 0)
			{
				PlaySound("Noise.wav", NULL, SND_ASYNC);
				Sound = 1;
			}
		}
		else if (Class4Door == 1 && stage == 51)
		{
			name = TEXT("이도현");
			text = TEXT("!! 애들아!!!");
			ttext = TEXT("너희들이 왜 여기에!....");
			UpFontSet(hdc, grt, nrt, text, name, ttext, P_IllBit, 3, 50, RGB(255, 255, 255), 220, 0);
		}
		else if (Class4Door == 3 && KeyCheck == 1)
		{
			name = TEXT("XXX");
			text = TEXT("어때 누구를 꺼내 줄지 생각해 봤어?");
			UpFontSet(hdc, grt, nrt, text, name, ttext, Black, 0, FONTSIZE, RGB(0, 0, 0), 0, 0);
		}
		else if (Class1Door == 1)
		{
			name = TEXT("이도현");
			text = TEXT("어? 원래 여기 문이 열려 있었나?");
			UpFontSet(hdc, grt, nrt, text, name, ttext, P_IllBit, 0, FONTSIZE, RGB(0, 0, 0), 0, 0);
		}
		else
		{
			page = 100;
		}
		break;
	case 1:
		if (OpenDoor == 1)
		{
			name = TEXT("시스템");
			text = TEXT("창고 문이 열렸습니다!");
			FontSet(hdc, grt, nrt, text, name, ttext, System, 0, FONTSIZE, RGB(0, 0, 0), 0, 0);
		}
		else if (OpenDoor == 4 && stage == 44)
		{
			name = TEXT("???");
			text = TEXT("와우! 어떻게 여기까진 잘 찾아왔네?");
			FontSet(hdc, grt, nrt, text, name, ttext, Black, 1, FONTSIZE, RGB(0, 0, 0), 0, 0);
		}
		else if (OpenDoor == 5 && stage == 4)
		{
			name = TEXT("???");
			text = TEXT("그 날 5월 5일 교무실로 부른 선생님께선 나에게 담배 핀 친구들에 대해 더 자세하게 얘기해 달라고 하셨지");
			FontSet(hdc, grt, nrt, text, name, ttext, Black, 0, FONTSIZE, RGB(0, 0, 0), 0, 0);
		}
		else if (Class4Door == 1 && stage == 51)
		{
			name = TEXT("XXX");
			text = TEXT("ㅋㅋㅋㅋ놀랐어? 오랜만에 본 친구들이라 좋아할 줄 알았는데 아쉽네?");
			UpFontSet(hdc, grt, nrt, text, name, ttext, Black, 1, FONTSIZE, RGB(0, 0, 0), 0, 0);
		}
		else if (Class4Door == 3 && KeyCheck == 1)
		{
			name = TEXT("김미진");
			text = TEXT("뭐? 이도현 그게 무슨 말이야?");
			UpFontSet(hdc, grt, nrt, text, name, ttext, N3_IllBit, 1, FONTSIZE, RGB(0, 0, 0), 0, 0);
		}
		else
		{
			page = 100;
		}
		break;
	case 2:
		if (OpenDoor == 4 && stage == 44)
		{
			name = TEXT("이도현");
			text = TEXT("너 뭐야! 누군데 이런 짓을 벌이는 거지?");
			FontSet(hdc, grt, nrt, text, name, ttext, P_IllBit, 2, FONTSIZE, RGB(0, 0, 0), 0, 0);
		}
		else if (OpenDoor == 5 && stage == 4)
		{
			name = TEXT("???");
			text = TEXT("그런데 그 장면을 내 친구가 보고만 거야 그 뒤에 얘기는 말 안 해도 알겠지?");
			FontSet(hdc, grt, nrt, text, name, ttext, Black, 0, FONTSIZE, RGB(0, 0, 0), 0, 0);
		}
		else if (Class4Door == 1 && stage == 51)
		{
			name = TEXT("정수희");
			text = TEXT("으…머리야 어? 이도현?");
			UpFontSet(hdc, grt, nrt, text, name, ttext, N4_IllBit, 0, FONTSIZE, RGB(0, 0, 0), 0, 0);
		}
		else if (Class4Door == 3 && KeyCheck == 1)
		{
			name = TEXT("김미진");
			text = TEXT("뭐라고 말이라도 좀 해봐!!");
			UpFontSet(hdc, grt, nrt, text, name, ttext, N3_IllBit, 2, FONTSIZE, RGB(0, 0, 0), 0, 0);
		}
		else
		{
			page = 100;
		}
		break;
	case 3:
		if (OpenDoor == 4 && stage == 44)
		{
			name = TEXT("???");
			text = TEXT("오우…내가 누군지 아직도 감이 안 잡힌 거야?");
			FontSet(hdc, grt, nrt, text, name, ttext, Black, 0, FONTSIZE, RGB(0, 0, 0), 0, 0);
		}
		else if (OpenDoor == 5 && stage == 4)
		{
			name = TEXT("이도현");
			text = TEXT("…시끄러!! 관심 없으니까");
			FontSet(hdc, grt, nrt, text, name, ttext, P_IllBit, 2, FONTSIZE, RGB(0, 0, 0), 0, 0);
		}
		else if (Class4Door == 1 && stage == 51)
		{
			name = TEXT("김화진");
			text = TEXT("야!!");
			ttext = TEXT("이 싸이코패스 자식! 이거 어서 안 풀어!!?");
			UpFontSet(hdc, grt, nrt, text, name, ttext, N2_IllBit, 2, 50, RGB(255, 255, 255), 150, 0);
		}
		else if (Class4Door == 3 && KeyCheck == 1)
		{
			name = TEXT("이수현");
			text = TEXT("도…도현아? 거짓말이지?");
			UpFontSet(hdc, grt, nrt, text, name, ttext, N1_IllBit, 1, 20, RGB(0, 0, 0), 0, 0);
		}
		else
		{
			page = 100;
		}
		break;
	case 4:
		if (OpenDoor == 4 && stage == 44)
		{
			name = TEXT("???");
			text = TEXT("좋아! 그러면 내가 누군지 맞추면 니 친구들이 어디에 잡혀 있는지 알려주지");
			FontSet(hdc, grt, nrt, text, name, ttext, Black, 0, FONTSIZE, RGB(0, 0, 0), 0, 0);
		}
		else if (Class4Door == 1 && stage == 51)
		{
			name = TEXT("이수현");
			text = TEXT("도… 도현아… 이… 이것 좀 풀어줘….");
			FontSet(hdc, grt, nrt, text, name, ttext, N1_IllBit, 1, 20, RGB(0, 0, 0), 0, 0);
		}
		else if (Class4Door == 3 && KeyCheck == 1)
		{
			name = TEXT("김화진");
			text = TEXT("야 이도현! 우리 친구였잖아! 내 말 듣고 있는 거야?");
			UpFontSet(hdc, grt, nrt, text, name, ttext, N2_IllBit, 2, FONTSIZE, RGB(0, 0, 0), 0, 0);
		}
		else
		{
			page = 100;
		}
		break;
	case 5:
		if (OpenDoor == 4 && stage == 44)
		{
			name = TEXT("이도현");
			text = TEXT("내친구들? 너 이 자식…! 무슨 짓을 한 거냐!");
			FontSet(hdc, grt, nrt, text, name, ttext, P_IllBit, 2, FONTSIZE, RGB(0, 0, 0), 0, 0);
		}
		else if (Class4Door == 1 && stage == 51)
		{
			name = TEXT("김미진");
			text = TEXT("꺄아아악!!~");
			ttext = TEXT("짜증나! 어떤 또X이 자식이야!!!~");
			UpFontSet(hdc, grt, nrt, text, name, ttext, N3_IllBit, 2, 50, RGB(255, 255, 255), 250, 0);
		}
		else if (Class4Door == 3 && KeyCheck == 1)
		{
			name = TEXT("김화진");
			text = TEXT("너 나 안 꺼내면 내 손에 죽을 줄 알어!");
			UpFontSet(hdc, grt, nrt, text, name, ttext, N2_IllBit, 2, FONTSIZE, RGB(0, 0, 0), 0, 0);
		}
		else if (Class4Door == 3 && KeyCheck == 1)
		{
			name = TEXT("정수희");
			text = TEXT("....");
			UpFontSet(hdc, grt, nrt, text, name, ttext, N4_IllBit, 0, FONTSIZE, RGB(0, 0, 0), 0, 0);
		}
		else
		{
			page = 100;
		}
		break;
	case 6:
		if (OpenDoor == 4 && stage == 44)
		{
			name = TEXT("???");
			text = TEXT("흠…시끄럽고 문제나 맞추기나 해~");
			FontSet(hdc, grt, nrt, text, name, ttext, Black, 0, FONTSIZE, RGB(0, 0, 0), 0, 0);
		}
		else if (Class4Door == 3 && KeyCheck == 1)
		{
			name = TEXT("이도현");
			text = TEXT("이봐 XXX 모두를 꺼낼 방법은 없는 거야?");
			FontSet(hdc, grt, nrt, text, name, ttext, P_IllBit, 2, FONTSIZE, RGB(0, 0, 0), 0, 0);
		}
		else
		{
			page = 100;
		}
		break;
	case 7:
		if (OpenDoor == 4 && stage == 44)
		{
			name = TEXT("???");
			text = TEXT("문제는 간단해 내가 누구인지 맞추기만 하면 돼");
			FontSet(hdc, grt, nrt, text, name, ttext, Black, 0, FONTSIZE, RGB(0, 0, 0), 0, 0);
		}
		else if (Class4Door == 3 && KeyCheck == 1)
		{
			name = TEXT("XXX");
			text = TEXT("뭐? 그때는 내가 위험에 처해 있을 땐 본 체도 안 하더니 이제 와서 뭐?");
			FontSet(hdc, grt, nrt, text, name, ttext, Black, 0, FONTSIZE, RGB(0, 0, 0), 0, 0);
		}
		else
		{
			page = 100;
		}
		break;
	case 8:
		if (OpenDoor == 4 && stage == 44)
		{
			name = TEXT("???");
			text = TEXT("1번!");
			FontSet(hdc, grt, nrt, text, name, ttext, Black, 0, FONTSIZE, RGB(0, 0, 0), 0, 0);
		}
		else if (Class4Door == 3 && KeyCheck == 1)
		{
			name = TEXT("XXX");
			text = TEXT("이제 와서 이러는 이유가 뭐야? 그런다고 내가 봐주기나 할 거 같아? 고르기나 해!");
			FontSet(hdc, grt, nrt, text, name, ttext, Black, 0, FONTSIZE, RGB(0, 0, 0), 0, 0);
		}
		else
		{
			page = 100;
		}
		break;
	case 9:
		if (OpenDoor == 4 && stage == 44)
		{
			name = TEXT("???");
			text = TEXT("1번! 그냥 사람들 가지고 노는 걸 좋아하는 싸이코패스~");
			FontSet(hdc, grt, nrt, text, name, ttext, Black, 0, FONTSIZE, RGB(0, 0, 0), 0, 0);
		}
		else
		{
			page = 100;
		}
		break;
	case 10:
		if (OpenDoor == 4 && stage == 44)
		{
			name = TEXT("???");
			text = TEXT("2번!");
			FontSet(hdc, grt, nrt, text, name, ttext, Black, 0, FONTSIZE, RGB(0, 0, 0), 0, 0);
		}
		else
		{
			page = 100;
		}
		break;
	case 11:
		if (OpenDoor == 4 && stage == 44)
		{
			name = TEXT("???");
			text = TEXT("2번! 네가 들고 있는 일기장의 주인…");
			FontSet(hdc, grt, nrt, text, name, ttext, Black, 0, FONTSIZE, RGB(0, 0, 0), 0, 0);
		}
		break;
	case 12:
		if (OpenDoor == 4 && stage == 44)
		{
			Choose = 1;
			name = TEXT("");
			text = TEXT("                          1번                                   2번");
			FontSet(hdc, grt, nrt, text, name, ttext, Black, 0, FONTSIZE, RGB(0, 0, 0), 0, 0);
			if (Choice == 1)
			{
				TransBlt(hdc, 380, 550, ChoiceBit, RGB(75, 75, 75));
			}
			if (Choice == 2)
			{
				TransBlt(hdc, 700, 550, ChoiceBit, RGB(75, 75, 75));
			}
		}
		break;
	case 13:
		if (Choice == 1)
		{
			name = TEXT("???");
			ttext = TEXT("땡!");
			FontSet(hdc, grt, nrt, text, name, ttext, Black, 1, 50, RGB(255, 0, 0), 0, 0);
		}
		else if (Choice == 2)
		{
			page = 25;
		}
		break;
	case 14:
		name = TEXT("XXX");
		text = TEXT("틀렸어…아직도 날 모르다니…너 보기보단 멍청하구나?");
		FontSet(hdc, grt, nrt, text, name, ttext, Black, 0, FONTSIZE, RGB(0, 0, 0), 0, 0);
		break;
	case 15:
		name = TEXT("XXX");
		text = TEXT("나야 나! XXX! 이제야 알겠어?!");
		FontSet(hdc, grt, nrt, text, name, ttext, Black, 1, FONTSIZE, RGB(0, 0, 0), 0, 0);
		break;
	case 16:
		name = TEXT("이도현");
		text = TEXT("XXX…(중학교 내에서 가장 많은 괴롭힘을 당했던 아이다…)");
		FontSet(hdc, grt, nrt, text, name, ttext, P_IllBit, 0, FONTSIZE, RGB(0, 0, 0), 0, 0);
		break;
	case 17:
		name = TEXT("XXX");
		text = TEXT("그럼 약속대로 문제를 못 맞췄으니 친구들이 감금되어 있는 방은 네가 스스로 찾아");
		FontSet(hdc, grt, nrt, text, name, ttext, Black, 0, FONTSIZE, RGB(0, 0, 0), 0, 0);
		break;
	case 18:
		name = TEXT("XXX");
		text = TEXT("흠…그래도 조금 힌트를 주자면 1-4반, 숙직실 둘 중 하나야 잘 맞혀보라고~");
		FontSet(hdc, grt, nrt, text, name, ttext, Black, 0, FONTSIZE, RGB(0, 0, 0), 0, 0);
		break;
	case 25:
		name = TEXT("XXX");
		text = TEXT("맞아 정답이야 그 일기장의 주인");
		FontSet(hdc, grt, nrt, text, name, ttext, Black, 0, FONTSIZE, RGB(0, 0, 0), 0, 0);
		break;
	case 26:
		name = TEXT("XXX");
		text = TEXT("맞아 정답이야 그 일기장의 주인 XXX...");
		FontSet(hdc, grt, nrt, text, name, ttext, Black, 0, FONTSIZE, RGB(0, 0, 0), 0, 0);
		break;
	case 27:
		name = TEXT("이도현");
		text = TEXT("XXX…(중학교 내에서 가장 많은 괴롭힘을 당했던 아이다…)");
		FontSet(hdc, grt, nrt, text, name, ttext, P_IllBit, 0, FONTSIZE, RGB(0, 0, 0), 0, 0);
		break;
	case 28:
		name = TEXT("XXX");
		text = TEXT("그럼 약속대로 문제를 맞췄으니 친구들이 감금되어 있는 방을 알려주지 거긴 ");
		ttext = TEXT("\n            1-4반이야");
		FontSet(hdc, grt, nrt, text, name, ttext, Black, 0, FONTSIZE, RGB(255, 0, 0), 0, 0);
		break;
	default:
		if (OpenDoor == 1)
		{
			OpenDoor = 2;
		}
		else if (OpenDoor == 4)
		{
			OpenDoor = 5;
		}
		else if (OpenDoor == 5)
		{
			OpenDoor = 6;
		}
		if (Class4Door == 1)
		{
			Class4Door = 2;
		}
		if (Class1Door == 1)
		{
			Class1Door = 2;
		}
		Sound = 0;
		page = 0;
		Stop = false;
		Openint = false;
		break;
	}
}
//열쇠로 문 여는 상호작용
void Box(HDC hdc)
{
	switch (page)
	{
	case 0:
		Stop = true;
		if (FakeBox)
		{
			name = TEXT("이도현");
			text = TEXT("어...?");
			FontSet(hdc, grt, nrt, text, name, ttext, P_IllBit, 1, FONTSIZE, RGB(0, 0, 0), 0, 0);
		}
		else if (RealBox)
		{
			name = TEXT("시스템");
			text = TEXT("1-5반 몇몇 학생들의 정보들이 담긴 상자와 폐품이 들어있는 상자들이 있다.");
			FontSet(hdc, grt, nrt, text, name, ttext, System, 0, FONTSIZE, RGB(0, 0, 0), 0, 0);
		}
		else if (stage == 3 && HealDoor >= 2)
		{
			name = TEXT("이도현");
			text = TEXT("메모지? 읽어보자.");
			FontSet(hdc, grt, nrt, text, name, ttext, P_IllBit, 0, FONTSIZE, RGB(0, 0, 0), 0, 0);
		}
		else
		{
			name = TEXT("시스템");
			text = TEXT("빈 상자다.");
			FontSet(hdc, grt, nrt, text, name, ttext, System, 0, FONTSIZE, RGB(0, 0, 0), 0, 0);
		}
		break;
	case 1:
		if (FakeBox)
		{
			name = TEXT("이도현");
			text = TEXT("아무것도 없네..");
			FontSet(hdc, grt, nrt, text, name, ttext, P_IllBit, 0, FONTSIZE, RGB(0, 0, 0), 0, 0);
		}
		else if (stage == 3 && HealDoor >= 2)
		{
			name = TEXT("이도현");
			text = TEXT("일기장…");
			FontSet(hdc, grt, nrt, text, name, ttext, P_IllBit, 1, FONTSIZE, RGB(0, 0, 0), 0, 0);
		}
		else if (!RealBox)
		{
			page = 10;
		}
		else
		{
			name = TEXT("시스템");
			text = TEXT("이수현 - xx 회사 대리, 8시에 출근하여 9시에 회사 도착함 주로 10시에 퇴근함");
			ttext = TEXT("\n          (가장 쉬움)");
			FontSet(hdc, grt, nrt, text, name, ttext, N1_IllBit, 0, FONTSIZE, RGB(255, 0, 0), 0, 0);
		}
		break;
	case 2:
		if (FakeBox)
		{
			page = 10;
		}
		else if (stage == 3 && HealDoor >= 2)
		{
			name = TEXT("이도현");
			text = TEXT("일기장… 돌이키고 싶은 날…?");
			FontSet(hdc, grt, nrt, text, name, ttext, P_IllBit, 1, FONTSIZE, RGB(0, 0, 0), 0, 0);
		}
		else if(RealBox)
		{
			name = TEXT("시스템");
			text = TEXT("김화진 - xx 헬스장 헬스 트레이너, 10시에 출근해서 6시에 퇴근함, 술을 자주 마시는 것 같음");
			ttext = TEXT("\n                   (가장 힘듦)");
			FontSet(hdc, grt, nrt, text, name, ttext, N2_IllBit, 0, FONTSIZE, RGB(255, 0, 0), 100, 0);
		}
		else
		{
			page = 100;
		}
		break;
	case 3:
		if (stage == 3)
		{
			if (BokDoBoxCheck == 1)
			{
				if (NPCFree == 1)
				{
					name = TEXT("이수현");
					text = TEXT("ㅇ..어? ㅈ..정말로 있었네...!");
					FontSet(hdc, grt, nrt, text, name, ttext, N1_IllBit, 1, 20, RGB(0, 0, 0), 0, 0);
				}
				else if (NPCFree == 2)
				{
					name = TEXT("김화진");
					text = TEXT("야, 봐봐 내 말이 맞지! 내가 여기 있다고 했잖아");
					FontSet(hdc, grt, nrt, text, name, ttext, N2_IllBit, 3, FONTSIZE, RGB(0, 0, 0), 0, 0);
				}
				else if (NPCFree == 3)
				{
					name = TEXT("김미진");
					text = TEXT("내가 말했잖아! 복도에 있을거라고~");
					FontSet(hdc, grt, nrt, text, name, ttext, N3_IllBit, 3, FONTSIZE, RGB(0, 0, 0), 0, 0);
				}
				else if (NPCFree == 4)
				{
					name = TEXT("정수희");
					text = TEXT("역시.");
					FontSet(hdc, grt, nrt, text, name, ttext, N4_IllBit, 1, FONTSIZE, RGB(0, 0, 0), 0, 0);
				}
				else
				{
					page = 15;
				}
			}
		}
		else
		{
			name = TEXT("시스템");
			text = TEXT("김미진 - 직장이 없고 친구들과 자주 놀러 다님, 거주지는 부모님과 지내는 것 같음");
			ttext = TEXT("\n                 (무난함)");
			FontSet(hdc, grt, nrt, text, name, ttext, N3_IllBit, 0, FONTSIZE, RGB(255, 0, 0), 0, 0);
		}
		break;
	case 4:
		if (stage == 3)
		{
			page = 10;
		}
		else
		{
			name = TEXT("시스템");
			text = TEXT("정수희 - 프리랜서로 무슨 일이 있는 게 아니면 집에만 있음");
			ttext = TEXT("\n(어려움)");
			FontSet(hdc, grt, nrt, text, name, ttext, N4_IllBit, 0, FONTSIZE, RGB(255, 0, 0), 0, 0);
		}
		break;
	case 5:
		name = TEXT("시스템");
		text = TEXT("이도현 - 머리가 좋아 젊은 나이에 대학 교수를 하고 있음, 6시 30분에 출근하며 퇴근 시간이 매일 다름");
		ttext = TEXT("\n                                         (조금 어려움)");
		FontSet(hdc, grt, nrt, text, name, ttext, System, 0, FONTSIZE, RGB(255, 0, 0), 0, 0);
		break;
	case 6:
		name = TEXT("이도현");
		text = TEXT("여기에 왜 내 정보와 중학교 친구들의 정보가 있는 거지?");
		FontSet(hdc, grt, nrt, text, name, ttext, P_IllBit, 1, FONTSIZE, RGB(255, 0, 0), 0, 0);
		break;
	default:
		page = 0;
		Stop = false;
		RealBox = false;
		FakeBoxint = false;
		FakeBox = false;
		Boxint = false;
		break;
	}
}
//박스와 상호작용
void Piano(HDC hdc)
{
	switch (page)
	{
	case 0:
		Stop = true;
		if (KeyCheck == 1 || Class4Door == 2 )
		{
			name = TEXT("이도현");
			text = TEXT("멍청아! 지금은 나갈 때가 아니야");
			FontSet(hdc, grt, nrt, text, name, ttext, P_IllBit, 2, FONTSIZE, RGB(0, 0, 0), 0, 0);
		}
		else if (PianoMusic == -1)
		{
			name = TEXT("이도현");
			text = TEXT("악보? 흠… 도움이 될지 모르니 일단 가져가 보자");
			FontSet(hdc, grt, nrt, text, name, ttext, P_IllBit, 0, FONTSIZE, RGB(0, 0, 0), 0, 0);
		}
		else if (PianoMusic == 0)
		{
			name = TEXT("이도현");
			text = TEXT("여기에 뭐가 더 있는거 같지않네");
			FontSet(hdc, grt, nrt, text, name, ttext, P_IllBit, 0, FONTSIZE, RGB(0, 0, 0), 0, 0);
		}
		break;
	case 1:
		if (Class4Door == 2 || KeyCheck == 1)
		{
			page = 100;
		}
		else if (PianoMusic == -1)
		{
			name = TEXT("시스템");
			text = TEXT("I키를 누르면 악보를 볼 수 있습니다.");
			FontSet(hdc, grt, nrt, text, name, ttext, System, 0, FONTSIZE, RGB(0, 0, 0), 0, 0);
		}
		else if (PianoMusic == 0)
		{
			page = 100;
		}
		break;
	default:
		Inventory = 0;
		PianoMusic = 0;
		page = 0;
		Stop = false;
		Pianoint = false;
		break;
	}
}
//피아노와 상호작용
void FirstDiary(HDC hdc)
{
	switch (page)
	{
	case 0:
		Stop = true;
		if (FirstRead == 1)
		{
			name = TEXT("이도현");
			text = TEXT("일기장에 무슨 단서가 있으려나?..");
			FontSet(hdc, grt, nrt, text, name, ttext, P_IllBit, 0, FONTSIZE, RGB(0, 0, 0), 0, 0);
		}
		else if (FirstRead == 2)
		{
			name = TEXT("이도현");
			text = TEXT("교무실? 그 곳에서 무슨 일이 일어난 거지?");
			FontSet(hdc, grt, nrt, text, name, ttext, P_IllBit, 0, FONTSIZE, RGB(0, 0, 0), 0, 0);
		}
		else if (FirstRead == 3)
		{
			name = TEXT("이도현");
			text = TEXT("……………");
			FontSet(hdc, grt, nrt, text, name, ttext, P_IllBit, 0, FONTSIZE, RGB(0, 0, 0), 0, 0);
		}
		break;

	case 1:
		if (FirstRead == 1)
		{
			name = TEXT("시스템");
			text = TEXT("일기는 ↑↓키로 선택 할 수 있습니다.");
			FontSet(hdc, grt, nrt, text, name, ttext, System, 0, FONTSIZE, RGB(0, 0, 0), 0, 0);
		}
		else
		{
			page = 10;
		}
		break;
	default:
		page = 0;
		if (FirstRead == 1)
		{
			FirstRead = 1.5;
		}
		if (FirstRead == 2)
		{
			FirstRead = 2.5;
		}
		if (FirstRead == 3)
		{
			FirstRead = 3.5;
		}
		Stop = false;
		FirstReadint = false;
		break;
	}
}
//일기장 처음 읽었을 때
void Prison(HDC hdc)
{
	switch (page)
	{
	case 0:
		Stop = true;
		if (Class4Door == 2)
		{
			name = TEXT("이도현");
			text = TEXT("흐압");
			FontSet(hdc, grt, nrt, text, name, ttext, P_IllBit, 2, FONTSIZE, RGB(0, 0, 0), 0, 0);
			if (Sound == 0)
			{
				PlaySound("Close.wav", NULL, SND_ASYNC);
				Sound = 1;
			}
		}
		else if (Class4Door == 3 && KeyCheck == 0)
		{
			name = TEXT("이도현");
			text = TEXT("열쇠가 숙직실에 있다고했지..");
			FontSet(hdc, grt, nrt, text, name, ttext, P_IllBit, 2, FONTSIZE, RGB(0, 0, 0), 0, 0);
		}
		else if (Class4Door == 3 && KeyCheck == 1)
		{
			for (int i = 0; i < 4; i++)
			{
				if (CCheckPtInRect(IronBarBit[0], 65 + i * 300, 470))		//감옥
				{
					if (i == 0)
					{
						NPCFree = 1;
						name = TEXT("이도현");
						text = TEXT("수현아 나와");
						FontSet(hdc, grt, nrt, text, name, ttext, P_IllBit, 1, FONTSIZE, RGB(0, 0, 0), 0, 0);
					}
					if (i == 1)
					{
						NPCFree = 2;
						name = TEXT("이도현");
						text = TEXT("화진아 나와");
						FontSet(hdc, grt, nrt, text, name, ttext, P_IllBit, 1, FONTSIZE, RGB(0, 0, 0), 0, 0);
					}
					if (i == 2)
					{
						NPCFree = 3;
						name = TEXT("이도현");
						text = TEXT("미진아 나와");
						FontSet(hdc, grt, nrt, text, name, ttext, P_IllBit, 1, FONTSIZE, RGB(0, 0, 0), 0, 0);
					}
					if (i == 3)
					{
						NPCFree = 4;
						name = TEXT("이도현");
						text = TEXT("수희야 나와");
						FontSet(hdc, grt, nrt, text, name, ttext, P_IllBit, 1, FONTSIZE, RGB(0, 0, 0), 0, 0);
					}
				}
			}
		}
		else
		{
			page = 100;
		}
		
		break;
	case 1:
		if (Class4Door == 2)
		{
			name = TEXT("시스템");
			text = TEXT("단단한 철창은 꼼짝도 하지 않는다.");
			FontSet(hdc, grt, nrt, text, name, ttext, System, 0, FONTSIZE, RGB(0, 0, 0), 0, 0);
		}
		else if (Class4Door == 3 && KeyCheck == 1 && NPCFree == 1)
		{
			name = TEXT("이수현");
			text = TEXT("도..도현아? 고마워…");
			FontSet(hdc, grt, nrt, text, name, ttext, N1_IllBit, 1, 20, RGB(0, 0, 0), 0, 0);
		}
		else if (Class4Door == 3 && KeyCheck == 1 && NPCFree == 2)
		{
			name = TEXT("김화진");
			text = TEXT("도현아!~ 네가 날 꺼내 줄지 알고 있었다고~");
			FontSet(hdc, grt, nrt, text, name, ttext, N2_IllBit, 3, FONTSIZE, RGB(0, 0, 0), 0, 0);
		}
		else if (Class4Door == 3 && KeyCheck == 1 && NPCFree == 3)
		{
			name = TEXT("김미진");
			text = TEXT("이도현!~ 날 구해줄지 알고 있었어!");
			FontSet(hdc, grt, nrt, text, name, ttext, N3_IllBit, 3, FONTSIZE, RGB(0, 0, 0), 0, 0);
		}
		else if (Class4Door == 3 && KeyCheck == 1 && NPCFree == 4)
		{
			name = TEXT("정수희");
			text = TEXT("…? 어째서 날… 그래도 고마워….");
			FontSet(hdc, grt, nrt, text, name, ttext, N4_IllBit, 1, FONTSIZE, RGB(0, 0, 0), 0, 0);
		}
		else
		{
			page = 100;
		}
		break;
	case 2:
		if (Class4Door == 2)
		{
			name = TEXT("XXX");
			text = TEXT("푸ㅂ!…흡 하하하하!");
			ttext = TEXT("그게 힘으로 열릴 줄 알았어?");
			UpFontSet(hdc, grt, nrt, text, name, ttext, Black, 1, 50, RGB(255, 255, 255), 350, 0);
		}
		else if (Class4Door == 3 && KeyCheck == 1 && NPCFree >= 1)
		{
			name = TEXT("이도현");
			text = TEXT("…그래서 나머지 애들은 어떻게 할 생각이지 XXX?");
			FontSet(hdc, grt, nrt, text, name, ttext, P_IllBit, 2, FONTSIZE, RGB(0, 0, 0), 0, 0);
		}
		else
		{
			page = 100;
		}
		break;
	case 3:
		if (Class4Door == 2)
		{
			name = TEXT("XXX");
			text = TEXT("그건 걱정하지 마 숙직실에 열쇠가 있거든 그걸로 한 번 열어볼 수 있으면 열어봐! ");
			FontSet(hdc, grt, nrt, text, name, ttext, Black, 0, FONTSIZE, RGB(0, 0, 0), 0, 0);
		}
		else if (Class4Door == 3 && KeyCheck == 1 && NPCFree >= 1)
		{
			name = TEXT("XXX");
			text = TEXT("이 이야기는 해피엔딩이 될 수 없어 그 정돈 너도 알잖아?");
			FontSet(hdc, grt, nrt, text, name, ttext, Black, 0, FONTSIZE, RGB(0, 0, 0), 0, 0);
		}
		else
		{
			page = 100;
		}
		break;
	case 4:
		if (Class4Door == 3 && KeyCheck == 1 && NPCFree == 1)
		{
		name = TEXT("이도현");
		text = TEXT("걱정 마 애들아 내가 수현이와 저 녀석의 장난에 벗어나 경찰들을 불러올게");
		FontSet(hdc, grt, nrt, text, name, ttext, P_IllBit, 0, FONTSIZE, RGB(0, 0, 0), 0, 0);
		}
		else if(Class4Door == 3 && KeyCheck == 1 && NPCFree == 2)
		{
			name = TEXT("이도현");
			text = TEXT("걱정 마 애들아 내가 화진이와 저 녀석의 장난에 벗어나 경찰들을 불러올게");
			FontSet(hdc, grt, nrt, text, name, ttext, P_IllBit, 0, FONTSIZE, RGB(0, 0, 0), 0, 0);
		}
		else if (Class4Door == 3 && KeyCheck == 1 && NPCFree == 3)
		{
			name = TEXT("이도현");
			text = TEXT("걱정 마 애들아 내가 미진이와 저 녀석의 장난에 벗어나 경찰들을 불러올게");
			FontSet(hdc, grt, nrt, text, name, ttext, P_IllBit, 0, FONTSIZE, RGB(0, 0, 0), 0, 0);
		}
		else if (Class4Door == 3 && KeyCheck == 1 && NPCFree == 4)
		{
			name = TEXT("이도현");
			text = TEXT("걱정 마 애들아 내가 수희와 저 녀석의 장난에 벗어나 경찰들을 불러올게");
			FontSet(hdc, grt, nrt, text, name, ttext, P_IllBit, 0, FONTSIZE, RGB(0, 0, 0), 0, 0);
		}
		else
		{
			page = 100;
		}
		break;
	case 5:
		if (Class4Door == 3 && KeyCheck == 1 && NPCFree >= 1)
		{
			name = TEXT("XXX");
			text = TEXT("경찰? 난 너희들을 다 갖고 놀면 이 학교를 폭파시킬 계획이야 증거를 남기면 안되잖아?");
			FontSet(hdc, grt, nrt, text, name, ttext, Black, 0, FONTSIZE, RGB(0, 0, 0), 0, 0);
		}
		break;
	case 6:
		if (Class4Door == 3 && KeyCheck == 1 && NPCFree >= 1 && NPCFree != 3)
		{
			name = TEXT("김미진");
			text = TEXT("이도현… 죽어서도 평생 저주할 거야!");
			FontSet(hdc, grt, nrt, text, name, ttext, N3_IllBit, 2, FONTSIZE, RGB(0, 0, 0), 0, 0);
		}
		else if (Class4Door == 3 && KeyCheck == 1 && NPCFree == 3)
		{
			name = TEXT("김화진");
			text = TEXT("다 끝났어…이도현 이 배신자 자식…");
			FontSet(hdc, grt, nrt, text, name, ttext, N2_IllBit, 2, FONTSIZE, RGB(0, 0, 0), 0, 0);
		}
		break;
	case 7:
		if (Class4Door == 3 && KeyCheck == 1 && NPCFree == 2 || NPCFree == 3)
		{
			name = TEXT("이수현");
			text = TEXT("(덜덜덜덜…)나…난….죽기 싫어! 죽기 싫다고!!!!헉…헉…");
			FontSet(hdc, grt, nrt, text, name, ttext, N1_IllBit, 2, FONTSIZE, RGB(0, 0, 0), 0, 0);
		}
		else if (Class4Door == 3 && KeyCheck == 1 && NPCFree == 1 || NPCFree == 4)
		{
			name = TEXT("김화진");
			text = TEXT("다 끝났어…이도현 이 배신자 자식…");
			FontSet(hdc, grt, nrt, text, name, ttext, N2_IllBit, 2, FONTSIZE, RGB(0, 0, 0), 0, 0);
		}
		break;
	case 8:
		if (Class4Door == 3 && KeyCheck == 1 && NPCFree >= 1 && NPCFree != 4)
		{
			name = TEXT("정수희");
			text = TEXT("그래도 난 믿고 기다리고 있을게");
			FontSet(hdc, grt, nrt, text, name, ttext, N4_IllBit, 1, FONTSIZE, RGB(0, 0, 0), 0, 0);
		}
		else if (Class4Door == 3 && KeyCheck == 1 && NPCFree == 4)
		{
			name = TEXT("이수현");
			text = TEXT("(덜덜덜덜…)나…난….죽기 싫어! 죽기 싫다고!!!!헉…헉…");
			FontSet(hdc, grt, nrt, text, name, ttext, N1_IllBit, 2, FONTSIZE, RGB(0, 0, 0), 0, 0);
		}
		break;
	case 9:
		if (Class4Door == 3 && KeyCheck == 1)
		{
			name = TEXT("XXX");
			text = TEXT("어우…시끄러 됐고! 탈출하고 싶다고 했지? 그러면 1-3반으로 가봐 문은 열려 있을 거야");
			FontSet(hdc, grt, nrt, text, name, ttext, Black, 1, FONTSIZE, RGB(0, 0, 0), 0, 0);
		}
		break;
	default:
		if (Class4Door == 2)
		{
			Class4Door = 3;
		}
		if (KeyCheck == 1)
		{
			KeyCheck = 2;
		}
		if (NPCFree == 1)
		{
			NPC1stop = false;
		}
		if (NPCFree == 2)
		{
			NPC2stop = false;
		}
		if (NPCFree == 3)
		{
			NPC3stop = false;
		}
		if (NPCFree == 4)
		{
			NPC4stop = false;
		}
		page = 0;
		Stop = false;
		Prisonint = false;
		break;
	}
}
//감옥과 상호작용
void Key(HDC hdc)
{
	switch (page)
	{
	case 0:
		Stop = true;
		if (KeyCheck == 0)
		{
			name = TEXT("이도현");
			text = TEXT("! 이게 감옥 열쇠겠지?");
			FontSet(hdc, grt, nrt, text, name, ttext, P_IllBit, 3, FONTSIZE, RGB(0, 0, 0), 0, 0);
		}
		else
		{
			page = 100;
		}
		break;
	case 1:
		if (KeyCheck == 0)
		{
			name = TEXT("이도현");
			text = TEXT("….근데 왜 열쇠가 하나뿐이지? 하나로 다 열 수 있는 건가?");
			FontSet(hdc, grt, nrt, text, name, ttext, P_IllBit, 0, FONTSIZE, RGB(0, 0, 0), 0, 0);
		}
		break;
	case 2:
		if (KeyCheck == 0)
		{
			name = TEXT("XXX");
			text = TEXT("왜? 무슨 문제라도 있어? 설마 내가 한 명만 보내준다는 말을 안 했던가?~ㅋㅋㅋㅋ");
			FontSet(hdc, grt, nrt, text, name, ttext, Black, 1, FONTSIZE, RGB(0, 0, 0), 0, 0);
		}
		break;
	case 3:
		if (KeyCheck == 0)
		{
			name = TEXT("이도현");
			text = TEXT("이런 나쁜 자식!!…");
			FontSet(hdc, grt, nrt, text, name, ttext, P_IllBit, 2, FONTSIZE, RGB(0, 0, 0), 0, 0);
		}
		break;
	default:
		if (KeyCheck == 0)
		{
			KeyCheck = 1;
		}
		page = 0;
		Stop = false;
		Keyint = false;
		break;
	}
}
//열쇠와 상호작용
void Lela(HDC hdc)
{
	switch (page)
	{
	case 0:
		Stop = true;

		if (lela == 0)
		{
			if (Sound == 0)
			{
				mciSendCommand(dwID, MCI_CLOSE, 0, NULL);//정지 및 메모리에서 삭제
				dwID = 0;

				openBgm.lpstrDeviceType = "mpegvideo";// wave , "mpegvideo"; //mp3 형식
				openBgm.lpstrElementName = "BGM2_2.mp3";
				mciSendCommand(0, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD)(LPVOID)&openBgm);
				dwID = openBgm.wDeviceID;
				mciSendCommand(dwID, MCI_PLAY, MCI_DGV_PLAY_REPEAT, (DWORD)(LPVOID)&openBgm);
				Sound = 1;
			}

			name = TEXT("이도현");
			text = TEXT("! 오른쪽방에서 노래소리가 들리는 것 같은데?");
			FontSet(hdc, grt, nrt, text, name, ttext, P_IllBit, 3, FONTSIZE, RGB(0, 0, 0), 0, 0);
		}
		else
		{
			page = 100;
		}
		break;
	case 1:
		if (lela == 0)
		{
			if (NPCFree == 1)
			{
				name = TEXT("이수현");
				text = TEXT("나도 들은것 같아......");
				FontSet(hdc, grt, nrt, text, name, ttext, N1_IllBit, 1, 20, RGB(0, 0, 0), 0, 0);
			}
			else if (NPCFree == 2)
			{
				name = TEXT("김화진");
				text = TEXT("이 자식 옆방에 있는거 아니야?! 당장 가보자!!");
				FontSet(hdc, grt, nrt, text, name, ttext, N2_IllBit, 1, FONTSIZE, RGB(0, 0, 0), 0, 0);
			}
			else if (NPCFree == 3)
			{
				name = TEXT("김미진");
				text = TEXT("시끄럽게 이게 무슨 소리야!");
				FontSet(hdc, grt, nrt, text, name, ttext, N3_IllBit, 2, FONTSIZE, RGB(0, 0, 0), 0, 0);
			}
			else if (NPCFree == 4)
			{
				name = TEXT("정수희");
				text = TEXT("나도 들었어.");
				FontSet(hdc, grt, nrt, text, name, ttext, N4_IllBit, 1, FONTSIZE, RGB(0, 0, 0), 0, 0);
			}
			else
			{
				page = 100;
			}
		}
		else
		{
			page = 100;
		}
		break;
	case 3:
		name = TEXT("이도현");
		text = TEXT("들리는 소리로 봐서는 보건실쪽 같은데...");
		FontSet(hdc, grt, nrt, text, name, ttext, P_IllBit, 1, FONTSIZE, RGB(0, 0, 0), 0, 0);
		break;
	default:
		Sound = 0;
		lela = 1;
		Time = -1;
		page = 0;
		Stop = false;
		Lelaint = false;
		break;
	}
}
//일기장 읽은 후 자동 상호작용
void Heal(HDC hdc)
{
	switch (page)
	{
	case 0:
		Stop = true;

		if (HealDoor == 1 && Command == -5)
		{
			if (Sound == 0)
			{

				mciSendCommand(dwID, MCI_CLOSE, 0, NULL);//정지 및 메모리에서 삭제
				dwID = 0;

				openBgm.lpstrDeviceType = "mpegvideo";// wave , "mpegvideo"; //mp3 형식
				openBgm.lpstrElementName = "BGM2.mp3";
				mciSendCommand(0, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD)(LPVOID)&openBgm);
				dwID = openBgm.wDeviceID;
				mciSendCommand(dwID, MCI_PLAY, MCI_DGV_PLAY_REPEAT, (DWORD)(LPVOID)&openBgm);
				Sound = 1;
			}

			name = TEXT("XXX");
			text = TEXT("난 학생시절 음악을 참 좋아했었지.");
			FontSet(hdc, grt, nrt, text, name, ttext, Black, 1, FONTSIZE, RGB(0, 0, 0), 0, 0);
		}
		else if (Command == -1 && HealDoor > 1)
		{
			if (Sound == 0)
			{
				mciSendCommand(dwID, MCI_CLOSE, 0, NULL);//정지 및 메모리에서 삭제
				dwID = 0;
				if (BGMCheck != -1)
				{

					openBgm.lpstrDeviceType = "mpegvideo";// wave , "mpegvideo"; //mp3 형식
					openBgm.lpstrElementName = "BGM.mp3";
					mciSendCommand(0, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD)(LPVOID)&openBgm);
					dwID = openBgm.wDeviceID;
					mciSendCommand(dwID, MCI_PLAY, MCI_DGV_PLAY_REPEAT, (DWORD)(LPVOID)&openBgm);
					Sound = 1;
				}
			}
			name = TEXT("XXX");
			text = TEXT("방금… 그 웃긴 몸부림, 신호 준거 맞지?");
			FontSet(hdc, grt, nrt, text, name, ttext, Black, 1, FONTSIZE, RGB(0, 0, 0), 0, 0);
		}
		else
		{
			page = 100;
		}
		break;
	case 1:
		if (HealDoor == 1 && Command == -5)
		{
			name = TEXT("XXX");
			text = TEXT("...본론으로 넘어갈까.");
			FontSet(hdc, grt, nrt, text, name, ttext, Black, 0, FONTSIZE, RGB(0, 0, 0), 0, 0);
		}
		else if (Command == -1 && HealDoor > 1)
		{
			name = TEXT("XXX");
			text = TEXT("1번 기석, 2번 승찬, 3번 우진 자…정답은?");
			FontSet(hdc, grt, nrt, text, name, ttext, Black, 1, FONTSIZE, RGB(0, 0, 0), 0, 0);
		}
		else
		{
			page = 100;
		}
		break;
	case 2:
		if (HealDoor == 1 && Command == -5)
		{
			name = TEXT("XXX");
			text = TEXT("저 앞에 해골 보이지? 날 학창시절 괴롭히던 친구들 중 한명이야.");
			FontSet(hdc, grt, nrt, text, name, ttext, Black, 0, FONTSIZE, RGB(0, 0, 0), 0, 0);
		}
		else if (Command == -1 && HealDoor > 1)
		{
			Choose = 1;
			name = TEXT("");
			text = TEXT("                  1번                  2번                  3번");
			FontSet(hdc, grt, nrt, text, name, ttext, Black, 0, FONTSIZE, RGB(0, 0, 0), 0, 0);
			if (Choice == 1)
			{
				TransBlt(hdc, 250, 550, ChoiceBit, RGB(75, 75, 75));
			}
			if (Choice == 2)
			{
				TransBlt(hdc, 500, 550, ChoiceBit, RGB(75, 75, 75));
			}
			if (Choice == 3)
			{
				TransBlt(hdc, 700, 550, ChoiceBit, RGB(75, 75, 75));
			}
		}
		break;
	case 3:
		if (HealDoor == 1 && Command == -5)
		{
			name = TEXT("이도현");
			text = TEXT("왜 탈출할 기회를 주는 거지? 저들처럼 만들어도 됐잖아.");
			FontSet(hdc, grt, nrt, text, name, ttext, P_IllBit, 2, FONTSIZE, RGB(0, 0, 0), 0, 0);
		}
		else if (Command == -1 && HealDoor > 1 && Choice == 2)
		{
			Choose = -1;
			BokDoBoxCheck = 0;
			name = TEXT("XXX");
			text = TEXT("맞아 정답이야 너라면 맞출 줄 알았어. 다음 방은");
			ttext = TEXT("1-2반이야");
			FontSet(hdc, grt, nrt, text, name, ttext, Black, 1, FONTSIZE, RGB(255, 0, 0), 650, 0);
		}
		else if (Command == -1 && HealDoor > 1 && Choice != 2)
		{
			Choose = -1;
			BokDoBoxCheck = 0;
			name = TEXT("XXX");
			text = TEXT("땡 틀렸어 의외네… 다음 방은 네가 스스로 찾아야 겠어.");
			FontSet(hdc, grt, nrt, text, name, ttext, Black, 0, FONTSIZE, RGB(0, 0, 0), 0, 0);
		}
		else
		{
			page = 100;
		}
		break;
	case 4:
		if (HealDoor == 1 && Command == -5)
		{
			name = TEXT("XXX");
			text = TEXT("……….해골이 누구인지 알아냈으면 몸을 좌우로 흔들어서 내게 신호를 줘 내가 CCTV로 보고 있으니");
			FontSet(hdc, grt, nrt, text, name, ttext, Black, 0, FONTSIZE, RGB(0, 0, 0), 0, 0);
		}
		else
		{
			page = 100;
		}
		break;
	case 5:
		if (HealDoor == 1 && Command == -5)
		{
			name = TEXT("시스템");
			text = TEXT("정답을 알아냈다면 ←→←→ 키를 빠르게 누르시오.");
			FontSet(hdc, grt, nrt, text, name, ttext, System, 0, FONTSIZE, RGB(0, 0, 0), 0, 0);
		}
		else
		{
			page = 100;
		}
		break;
	default:
		if (Command == -1)
		{
			Command = -2;
		}
		if (Command == -5)
		{
			Command = 0;
		}

		Sound = 0;
		if (HealDoor == 1)
		{
			HealDoor = 2;
			Time = 0;
		}
		else if (Time >= 0)
		{
			Time = -1;
		}

		if (BokDoBoxCheck == 0)
		{
			Time = 0;
		}

		Sound = 0;
		page = 0;
		Stop = false;
		Healint = false;
		break;
	}
}
//보건실 입장 대사 상호작용
void HHeal(HDC hdc)
{
	switch (page)
	{
	case 0:
		Stop = true;

		if (NPCFree == 1)
		{
			name = TEXT("이수현");
			text = TEXT("저 노래…. 저 노래에 힌트가 있지 않을까?");
			FontSet(hdc, grt, nrt, text, name, ttext, N1_IllBit, 1, 20, RGB(0, 0, 0), 0, 0);
		}
		else if (NPCFree == 2)
		{
			name = TEXT("김화진");
			text = TEXT("상황에 맞지 않게 저런 노래는 왜 틀어 놓은 거야?");
			FontSet(hdc, grt, nrt, text, name, ttext, N2_IllBit, 1, FONTSIZE, RGB(0, 0, 0), 0, 0);
		}
		else if (NPCFree == 3)
		{
			name = TEXT("김미진");
			text = TEXT("어우 시끄러! 저 노래는 도대체 왜 틀어 놓은 거야? ");
			FontSet(hdc, grt, nrt, text, name, ttext, N3_IllBit, 2, FONTSIZE, RGB(0, 0, 0), 0, 0);
		}
		else if (NPCFree == 4)
		{
			name = TEXT("정수희");
			text = TEXT("혹시 노래에 힌트가 있는게 아닐까?");
			FontSet(hdc, grt, nrt, text, name, ttext, N4_IllBit, 1, FONTSIZE, RGB(0, 0, 0), 0, 0);
		}
		else
		{
			page = 100;
		}
		break;
	default:
		if (HealDoor == 2)
		{
			HealDoor = 3;
		}
		Sound = 0;
		Time = -1;
		page = 0;
		Stop = false;
		HHealint = false;
		break;
	}
}
//보건실 입장 대사가 끝난 후 자동 상호작용
void Boom(HDC hdc)
{
	switch (page)
	{
	case 0:
		Stop = true;
		if (boom == 0)
		{
			name = TEXT("XXX");
			text = TEXT("아 맞다. 혹시 내가 그걸 말 안 했던가?");
			FontSet(hdc, grt, nrt, text, name, ttext, Black, 0, FONTSIZE, RGB(0, 0, 0), 0, 0);
		}
		else if (boom == 1 && NPCDie == 0)
		{
			name = TEXT("이도현");
			text = TEXT("…준비 됐으면 시작할게….");
			FontSet(hdc, grt, nrt, text, name, ttext, P_IllBit, 2, FONTSIZE, RGB(0, 0, 0), 0, 0);
		}
		else
		{
			page = 13;
		}
		break;
	case 1:
		if (boom == 0)
		{
			name = TEXT("XXX");
			text = TEXT("감옥에서 도망갈 수도 있어서 니 친구들 심장 쪽에 작은 폭탄을 심어 놨거든?");
			FontSet(hdc, grt, nrt, text, name, ttext, Black, 1, FONTSIZE, RGB(0, 0, 0), 0, 0);
		}
		else if (boom == 1 && NPCDie == 0)
		{
			if (NPCFree == 1)
			{
				name = TEXT("이수현");
				text = TEXT("도.. 도현아.. 나.. 난 못 볼 것 같아 그냥 너만 믿을게…!");
				FontSet(hdc, grt, nrt, text, name, ttext, N1_IllBit, 2, FONTSIZE, RGB(0, 0, 0), 0, 0);
			}
			if (NPCFree == 2)
			{
				name = TEXT("김화진");
				text = TEXT("너. 너… 너…! 화…확실한 거 맞지!?");
				FontSet(hdc, grt, nrt, text, name, ttext, N2_IllBit, 2, FONTSIZE, RGB(0, 0, 0), 0, 0);
			}
			if (NPCFree == 3)
			{
				name = TEXT("김미진");
				text = TEXT("(꿀꺽) 나.. 난 준비됐어…!");
				FontSet(hdc, grt, nrt, text, name, ttext, N3_IllBit, 1, FONTSIZE, RGB(0, 0, 0), 0, 0);
			}
			if (NPCFree == 4)
			{
				name = TEXT("정수희");
				text = TEXT("….난 준비됐어.");
				FontSet(hdc, grt, nrt, text, name, ttext, N4_IllBit, 1, FONTSIZE, RGB(0, 0, 0), 0, 0);
			}
		}
		else
		{
			page = 100;
		}
		break;
	case 2:
		if (boom == 0)
		{
			name = TEXT("XXX");
			text = TEXT("5분 줄게 5분 안에 폭탄을 풀 수 있는 비밀번호를 알아오지 않으면 터져 죽고 말거야.");
			FontSet(hdc, grt, nrt, text, name, ttext, Black, 1, FONTSIZE, RGB(0, 0, 0), 0, 0);
			if (Sound == 0 && BGMCheck != -1)
			{

				mciSendCommand(dwID, MCI_CLOSE, 0, NULL);//정지 및 메모리에서 삭제
				dwID = 0;

				openBgm.lpstrDeviceType = "mpegvideo";// wave , "mpegvideo"; //mp3 형식
				openBgm.lpstrElementName = "BGM3.mp3";
				mciSendCommand(0, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD)(LPVOID)&openBgm);
				dwID = openBgm.wDeviceID;
				mciSendCommand(dwID, MCI_PLAY, MCI_DGV_PLAY_REPEAT, (DWORD)(LPVOID)&openBgm);
				Sound = 1;
			}
		}
		else if (boom == 1 && NPCDie == 0)
		{
			if (BoomPW == -1)
			{
				BoomPW = 1;
			}
			name = TEXT("시스템");
			text = TEXT("ESC : 취소\n방향키 좌우 : 순서 선택\n스페이스바 : 결정");
			if (NPCFree == 1)
			{
				FontSet(hdc, grt, nrt, text, name, ttext, N1_IllBit, 2, FONTSIZE, RGB(0, 0, 0), 0, 0);
			}
			if (NPCFree == 2)
			{
				FontSet(hdc, grt, nrt, text, name, ttext, N2_IllBit, 0, FONTSIZE, RGB(0, 0, 0), 0, 0);
			}
			if (NPCFree == 3)
			{
				FontSet(hdc, grt, nrt, text, name, ttext, N3_IllBit, 0, FONTSIZE, RGB(0, 0, 0), 0, 0);
			}
			if (NPCFree == 4)
			{
				FontSet(hdc, grt, nrt, text, name, ttext, N4_IllBit, 0, FONTSIZE, RGB(0, 0, 0), 0, 0);
			}

			BoomTransBlt(hdc, 600, 600, BoomBit, RGB(75, 75, 75), BoomPW);
		}
		else
		{
			page = 100;
		}
		break;
	case 3:
		if (boom == 0)
		{
			name = TEXT("XXX");
			text = TEXT("비밀번호의 힌트는 한자리 숫자며, 너희 5명 중 저 친구를 납치한 순서야.");
			FontSet(hdc, grt, nrt, text, name, ttext, Black, 1, FONTSIZE, RGB(0, 0, 0), 0, 0);
		}
		else if (boom == 1)
		{
			if (BoomPW == 1 && NPCFree == 1)
			{
				page = 20;
				Free = 1;
				BoomPW = -1;
			}
			else if (BoomPW == 2 && NPCFree == 3)
			{
				page = 20;
				Free = 1;
				BoomPW = -1;
			}
			else if (BoomPW == 5 && NPCFree == 2)
			{
				page = 20;
				Free = 1;
				BoomPW = -1;
			}
			else if (BoomPW == 4 && NPCFree == 4)
			{
				page = 20;
				Free = 1;
				BoomPW = -1;
			}
			else
			{
				page = 10;
				BoomPW = -1;
			}
		}
		break;
	case 4:
		if (boom == 0)
		{
			name = TEXT("XXX");
			text = TEXT("참고로 난 쉬운 일 먼저 하는 스타일이야~….");
			ttext = TEXT("그럼 시작!");
			FontSet(hdc, grt, nrt, text, name, ttext, Black, 1, FONTSIZE, RGB(255, 0, 0), 600, 0);
			SetTimer(hWndMain, 5, 1000, NULL);		//시간 재생
		}
		break;
	case 5:
		if (NPCFree == 1 )
		{
			name = TEXT("이수현");
			text = TEXT("히..히익! 포..폭탄!?");
			FontSet(hdc, grt, nrt, text, name, ttext, N1_IllBit, 2, 20, RGB(0, 0, 0), 0, 0);
		}
		else if (NPCFree == 2)
		{
			name = TEXT("김화진");
			text = TEXT("포..폭탄? 야 이 싸패자식아!! 그딴걸 우리가 어떻게 알아!!");
			FontSet(hdc, grt, nrt, text, name, ttext, N2_IllBit, 2, FONTSIZE, RGB(0, 0, 0), 0, 0);
		}
		else if (NPCFree == 3)
		{
			name = TEXT("김미진");
			text = TEXT("내가 납치된 순서? 그딴걸 우리가 어떻게 알아!!");
			FontSet(hdc, grt, nrt, text, name, ttext, N3_IllBit, 2, FONTSIZE, RGB(0, 0, 0), 0, 0);
		}
		else if (NPCFree == 4)
		{
			name = TEXT("정수희");
			text = TEXT("내가 납치된 순서?... 기억이 안 나는거 같아");
			FontSet(hdc, grt, nrt, text, name, ttext, N4_IllBit, 1, FONTSIZE, RGB(0, 0, 0), 0, 0);
		}
		else
		{
			page = 100;
		}
		break;
	case 6:
		name = TEXT("시스템");
		text = TEXT("친구는 이 자리에 있을 겁니다. 문제를 맞출 준비가 됐다면 친구에게 상호작용 하시오.");
		FontSet(hdc, grt, nrt, text, name, ttext, System, 0, FONTSIZE, RGB(0, 0, 0), 0, 0);
		break;
	case 7:
		page = 100;
		break;
	case 10:
		name = TEXT("시스템");
		text = TEXT("삐빅");
		FontSet(hdc, grt, nrt, text, name, ttext, System, 0, FONTSIZE, RGB(0, 0, 0), 0, 0);
		if (Sound == 0 && BGMCheck != -1)
		{

			mciSendCommand(dwID, MCI_CLOSE, 0, NULL);//정지 및 메모리에서 삭제
			dwID = 0;

			openBgm.lpstrDeviceType = "mpegvideo";// wave , "mpegvideo"; //mp3 형식
			openBgm.lpstrElementName = "BGM.mp3";
			mciSendCommand(0, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD)(LPVOID)&openBgm);
			dwID = openBgm.wDeviceID;
			mciSendCommand(dwID, MCI_PLAY, MCI_DGV_PLAY_REPEAT, (DWORD)(LPVOID)&openBgm);
			Sound = 1;
		}
		break;
	case 11:
		if (NPCFree == 1)
		{
			name = TEXT("이수현");
			text = TEXT("어?");
			FontSet(hdc, grt, nrt, text, name, ttext, N1_IllBit, 1, FONTSIZE, RGB(0, 0, 0), 0, 0);
			NPCDie = 1;
		}
		if (NPCFree == 2)
		{
			name = TEXT("김화진");
			text = TEXT("어?");
			FontSet(hdc, grt, nrt, text, name, ttext, N2_IllBit, 1, FONTSIZE, RGB(0, 0, 0), 0, 0);
			NPCDie = 2;
		}
		if (NPCFree == 3)
		{
			name = TEXT("김미진");
			text = TEXT("어?");
			FontSet(hdc, grt, nrt, text, name, ttext, N3_IllBit, 1, FONTSIZE, RGB(0, 0, 0), 0, 0);
			NPCDie = 3;
		}
		if (NPCFree == 4)
		{
			name = TEXT("정수희");
			text = TEXT("어?");
			FontSet(hdc, grt, nrt, text, name, ttext, N4_IllBit, 1, FONTSIZE, RGB(0, 0, 0), 0, 0);
			NPCDie = 4;
		}
		break;
	case 12:
		SetTimer(hWndMain, 6, 100, NULL);
		page = 13;
		break;
	case 13:
		name = TEXT("이도현");
		text = TEXT("안돼!");
		FontSet(hdc, grt, nrt, text, name, ttext, P_IllBit, 2, FONTSIZE, RGB(0, 0, 0), 0, 0);
		break;
	case 14:
		name = TEXT("이도현");
		text = TEXT("안돼! 젠장!!!");
		FontSet(hdc, grt, nrt, text, name, ttext, P_IllBit, 2, FONTSIZE, RGB(0, 0, 0), 0, 0);
		break;
	case 15:
		name = TEXT("이도현");
		text = TEXT("               젠장!!!!!");
		ttext = TEXT("안돼! 젠장!!!");
		UpFontSet(hdc, grt, nrt, text, name, ttext, P_IllBit, 2, 50, RGB(255, 255, 255), 0, 0);
		break;
	case 16:
		page = 27;
		break;
	case 20:
		name = TEXT("시스템");
		text = TEXT("툭");
		FontSet(hdc, grt, nrt, text, name, ttext, System, 0, FONTSIZE, RGB(0, 0, 0), 0, 0);
		KillTimer(hWndMain, 5);
		break;
	case 21:
		if (NPCFree == 1)
		{
			name = TEXT("이수현");
			text = TEXT("헉! 푸…풀렸어!... 고마워 도현아….. ");
			FontSet(hdc, grt, nrt, text, name, ttext, N1_IllBit, 1, FONTSIZE, RGB(0, 0, 0), 0, 0);
		}
		if (NPCFree == 2)
		{
			name = TEXT("김화진");
			text = TEXT("윽!... 어? 푸..풀린 건가? 나이스! 살았다!!");
			FontSet(hdc, grt, nrt, text, name, ttext, N2_IllBit, 3, FONTSIZE, RGB(0, 0, 0), 0, 0);
		}
		if (NPCFree == 3)
		{
			name = TEXT("김미진");
			text = TEXT("푸..풀렸다! 역시 이도현이야 믿고 있었어!! ");
			FontSet(hdc, grt, nrt, text, name, ttext, N3_IllBit, 3, FONTSIZE, RGB(0, 0, 0), 0, 0);
		}
		if (NPCFree == 4)
		{
			name = TEXT("정수희");
			text = TEXT("…풀렸다….");
			FontSet(hdc, grt, nrt, text, name, ttext, N4_IllBit, 1, FONTSIZE, RGB(0, 0, 0), 0, 0);
		}
		if (Sound == 0 && BGMCheck != -1)
		{

			mciSendCommand(dwID, MCI_CLOSE, 0, NULL);//정지 및 메모리에서 삭제
			dwID = 0;

			openBgm.lpstrDeviceType = "mpegvideo";// wave , "mpegvideo"; //mp3 형식
			openBgm.lpstrElementName = "BGM.mp3";
			mciSendCommand(0, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD)(LPVOID)&openBgm);
			dwID = openBgm.wDeviceID;
			mciSendCommand(dwID, MCI_PLAY, MCI_DGV_PLAY_REPEAT, (DWORD)(LPVOID)&openBgm);
			Sound = 1;
		}
		break;
	case 22:
		if (NPCFree == 4)
		{
			name = TEXT("정수희");
			text = TEXT("…풀렸다…. 고마워 도현아.");
			FontSet(hdc, grt, nrt, text, name, ttext, N4_IllBit, 1, FONTSIZE, RGB(0, 0, 0), 0, 0);
		}
		else
		{
			page = 23;
		}
		break;
	case 23:
		name = TEXT("이도현");
		text = TEXT("헉…헉….");
		FontSet(hdc, grt, nrt, text, name, ttext, P_IllBit, 3, FONTSIZE, RGB(0, 0, 0), 0, 0);
		break;
	case 24:
		name = TEXT("이도현");
		text = TEXT("헉…헉…. 다행이다…");
		FontSet(hdc, grt, nrt, text, name, ttext, P_IllBit, 3, FONTSIZE, RGB(0, 0, 0), 0, 0);
		
		break;
	case 25:
		name = TEXT("이도현");
		text = TEXT("헉…헉…. 다행이다… 정말….");
		FontSet(hdc, grt, nrt, text, name, ttext, P_IllBit, 3, FONTSIZE, RGB(0, 0, 0), 0, 0);
		break;
	case 26:
		name = TEXT("이도현");
		text = TEXT("헉…헉…. 다행이다… 정말…. 다행이야……..");
		FontSet(hdc, grt, nrt, text, name, ttext, P_IllBit, 3, FONTSIZE, RGB(0, 0, 0), 0, 0);
		break;
	case 27:
		name = TEXT("XXX");
		text = TEXT("…..피아노로              를 연주하면 정문을 열 수 있어. 음악실로 가봐.");
		ttext = TEXT("                어떤 노래");
		FontSet(hdc, grt, nrt, text, name, ttext, Black, 0, FONTSIZE, RGB(255, 0, 0), 0, 0);
		bandal = 1;
		break;
	default:
		Sound = 0;
		Time = -1;
		page = 0;
		if (boom == 0)
		{
			if (NPCFree == 1)
			{
				NPC1stop = true;
				NPC1x = 800;
				NPC1y = 300;
			}
			if (NPCFree == 2)
			{
				NPC2stop = true;
				NPC2x = 800;
				NPC2y = 300;
			}
			if (NPCFree == 3)
			{
				NPC3stop = true;
				NPC3x = 800;
				NPC3y = 300;
			}
			if (NPCFree == 4)
			{
				NPC4stop = true;
				NPC4x = 800;
				NPC4y = 300;
			}
			boom = 1;
		}
		if (Free == 1)
		{
			boom = 3;
			Time = -1;
			if (NPCFree == 1)
			{
				NPC1stop = false;
			}
			if (NPCFree == 2)
			{
				NPC2stop = false;
			}
			if (NPCFree == 3)
			{
				NPC3stop = false;
			}
			if (NPCFree == 4)
			{
				NPC4stop = false;
			}
		}
		Stop = false;
		Boomint = false;
		break;
	}
}
//5분 폭탄 상호작용
void BokDoBox(HDC hdc)
{
	switch (page)
	{
	case 0:
		Stop = true;
		if (BokDoBoxCheck == 0)
		{
			if (NPCFree == 1)
			{
				name = TEXT("이수현");
				text = TEXT(".....");
				FontSet(hdc, grt, nrt, text, name, ttext, N1_IllBit, 0, 20, RGB(0, 0, 0), 0, 0);
			}
			else if (NPCFree == 2)
			{
				name = TEXT("김화진");
				text = TEXT("아니");
				FontSet(hdc, grt, nrt, text, name, ttext, N2_IllBit, 1, FONTSIZE, RGB(0, 0, 0), 0, 0);
			}
			else if (NPCFree == 3)
			{
				name = TEXT("김미진");
				text = TEXT("이도현");
				FontSet(hdc, grt, nrt, text, name, ttext, N3_IllBit, 1, FONTSIZE, RGB(0, 0, 0), 0, 0);
			}
			else if (NPCFree == 4)
			{
				name = TEXT("정수희");
				text = TEXT("흠..");
				FontSet(hdc, grt, nrt, text, name, ttext, N4_IllBit, 0, FONTSIZE, RGB(0, 0, 0), 0, 0);
			}
			else
			{
				page = 15;
			}
		}
		else
		{
			page = 15;
		}
		break;
	case 1:
		if (BokDoBoxCheck == 0)
		{
			if (NPCFree == 1)
			{
				name = TEXT("이수현");
				text = TEXT("...ㅂ..복도에 ㄷ..단서가 숨겨져 있지... 않을까...?");
				FontSet(hdc, grt, nrt, text, name, ttext, N1_IllBit, 1, 20, RGB(0, 0, 0), 0, 0);
			}
			else if (NPCFree == 2)
			{
				name = TEXT("김화진");
				text = TEXT("야, 복도 좀 찾아봐라 이 답답아");
				FontSet(hdc, grt, nrt, text, name, ttext, N2_IllBit, 2, FONTSIZE, RGB(0, 0, 0), 0, 0);
			}
			else if (NPCFree == 3)
			{
				name = TEXT("김미진");
				text = TEXT("아니 저기 복도에 뭐 있잖아!");
				FontSet(hdc, grt, nrt, text, name, ttext, N3_IllBit, 2, FONTSIZE, RGB(0, 0, 0), 0, 0);
			}
			else if (NPCFree == 4)
			{
				name = TEXT("정수희");
				text = TEXT("복도에 단서가 숨겨져있을거 같은데..");
				FontSet(hdc, grt, nrt, text, name, ttext, N4_IllBit, 1, FONTSIZE, RGB(0, 0, 0), 0, 0);
			}
			else
			{
				page = 15;
			}
		}
		else
		{
			page = 15;
		}
		break;
	default:
		if (BokDoBoxCheck == 0)
		{
			BokDoBoxCheck = 1;
		}
		page = 0;
		Time = -1;
		BokDoBoxint = false;
		Stop = false;
		break;
	}
}
//복도박스에 관한 힌트
void EndPiano(HDC hdc)
{
	switch (page)
	{
	case 0:
		Stop = true;
		if (bandal == 1)
		{
			name = TEXT("시스템");
			text = TEXT("피아노 건반에 손을 얹었다.");
			FontSet(hdc, grt, nrt, text, name, ttext, System, 0, FONTSIZE, RGB(0, 0, 0), 0, 0);
		}
		else
		{
			page = 100;
		}
		break;
	case 1:
		Stop = true;
		if (bandal == 1)
		{
			name = TEXT("시스템");
			text = TEXT("(숫자키 1~8로 피아노를 칠 수 있습니다)");
			FontSet(hdc, grt, nrt, text, name, ttext, System, 0, FONTSIZE, RGB(0, 0, 0), 0, 0);
		}
		break;
	case 2:
		Stop = true;
	case 3:
		SpaceStop = 1;
		name = TEXT("시스템");
		text = TEXT("(피아노 사용 중...)");
		FontSet(hdc, grt, nrt, text, name, ttext, System, 0, FONTSIZE, RGB(0, 0, 0), 0, 0);
		GGunBan[0] = ScanGunBan;
		break;
	case 4:
		name = TEXT("시스템");
		text = TEXT("(피아노 사용 중...)");
		FontSet(hdc, grt, nrt, text, name, ttext, System, 0, FONTSIZE, RGB(0, 0, 0), 0, 0);
		GGunBan[1] = ScanGunBan;
		break;
	case 5:
		name = TEXT("시스템");
		text = TEXT("(피아노 사용 중...)");
		FontSet(hdc, grt, nrt, text, name, ttext, System, 0, FONTSIZE, RGB(0, 0, 0), 0, 0);
		GGunBan[2] = ScanGunBan;
		break;
	case 6:
		name = TEXT("시스템");
		text = TEXT("(피아노 사용 중...)");
		FontSet(hdc, grt, nrt, text, name, ttext, System, 0, FONTSIZE, RGB(0, 0, 0), 0, 0);
		GGunBan[3] = ScanGunBan;
		break;
	case 7:
		name = TEXT("시스템");
		text = TEXT("(피아노 사용 중...)");
		FontSet(hdc, grt, nrt, text, name, ttext, System, 0, FONTSIZE, RGB(0, 0, 0), 0, 0);
		GGunBan[4] = ScanGunBan;
		break;
	case 8:
		name = TEXT("시스템");
		text = TEXT("(피아노 사용 중...)");
		FontSet(hdc, grt, nrt, text, name, ttext, System, 0, FONTSIZE, RGB(0, 0, 0), 0, 0);
		GGunBan[5] = ScanGunBan;
		break;
	case 9:
		name = TEXT("시스템");
		text = TEXT("(피아노 사용 중...)");
		FontSet(hdc, grt, nrt, text, name, ttext, System, 0, FONTSIZE, RGB(0, 0, 0), 0, 0);
		GGunBan[6] = ScanGunBan;
		break;
	case 10:
		name = TEXT("시스템");
		text = TEXT("(피아노 사용 중...)");
		FontSet(hdc, grt, nrt, text, name, ttext, System, 0, FONTSIZE, RGB(0, 0, 0), 0, 0);
		GGunBan[7] = ScanGunBan;
		break;
	case 11:
		name = TEXT("시스템");
		text = TEXT("(피아노 사용 중...)");
		FontSet(hdc, grt, nrt, text, name, ttext, System, 0, FONTSIZE, RGB(0, 0, 0), 0, 0);
		GGunBan[8] = ScanGunBan;
		break;
	case 12:
		name = TEXT("시스템");
		text = TEXT("(피아노 사용 중...)");
		FontSet(hdc, grt, nrt, text, name, ttext, System, 0, FONTSIZE, RGB(0, 0, 0), 0, 0);
		GGunBan[9] = ScanGunBan;
		break;
	case 13:
		name = TEXT("시스템");
		text = TEXT("(피아노 사용 중...)");
		FontSet(hdc, grt, nrt, text, name, ttext, System, 0, FONTSIZE, RGB(0, 0, 0), 0, 0);
		GGunBan[10] = ScanGunBan;
		break;
	case 14:
		name = TEXT("시스템");
		text = TEXT("(피아노 사용 중...)");
		FontSet(hdc, grt, nrt, text, name, ttext, System, 0, FONTSIZE, RGB(0, 0, 0), 0, 0);
		GGunBan[11] = ScanGunBan;
		break;
	case 15:
		name = TEXT("시스템");
		text = TEXT("(연주를 완료했다.)");
		FontSet(hdc, grt, nrt, text, name, ttext, System, 0, FONTSIZE, RGB(0, 0, 0), 0, 0);
		GGunBan[12] = ScanGunBan;
		SpaceStop = 0;
		break;
	case 16:
		if (GGunBan[0] == GunBan[0] && GGunBan[1] == GunBan[1] && GGunBan[2] == GunBan[2] && GGunBan[3] == GunBan[3] && GGunBan[4] == GunBan[4] && GGunBan[5] == GunBan[5] && GGunBan[6] == GunBan[6] && GGunBan[7] == GunBan[7] && GGunBan[8] == GunBan[8] && GGunBan[9] == GunBan[9] && GGunBan[10] == GunBan[10] && GGunBan[11] == GunBan[11] && GGunBan[12] == GunBan[12])
		{
			name = TEXT("시스템");
			text = TEXT("어디선가 문들이 열리는 소리가 났다.");
			FontSet(hdc, grt, nrt, text, name, ttext, System, 0, FONTSIZE, RGB(0, 0, 0), 0, 0);
			if (Sound == 0 && BGMCheck != -1)
			{
				mciSendCommand(dwID, MCI_CLOSE, 0, NULL);//정지 및 메모리에서 삭제
				dwID = 0;

				openBgm.lpstrDeviceType = "mpegvideo";// wave , "mpegvideo"; //mp3 형식
				openBgm.lpstrElementName = "bandal.mp3";
				mciSendCommand(0, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD)(LPVOID)&openBgm);
				dwID = openBgm.wDeviceID;
				mciSendCommand(dwID, MCI_PLAY, MCI_DGV_PLAY_REPEAT, (DWORD)(LPVOID)&openBgm);
				Sound = 1;
			}
		}
		else
		{
			name = TEXT("이도현");
			text = TEXT("아무 일도 일어나지 않은 것 같다.");
			FontSet(hdc, grt, nrt, text, name, ttext, P_IllBit, 1, FONTSIZE, RGB(0, 0, 0), 0, 0);
		}
		break;
	case 17:
		if (GGunBan[0] == GunBan[0] && GGunBan[1] == GunBan[1] && GGunBan[2] == GunBan[2] && GGunBan[3] == GunBan[3] && GGunBan[4] == GunBan[4] && GGunBan[5] == GunBan[5] && GGunBan[6] == GunBan[6] && GGunBan[7] == GunBan[7] && GGunBan[8] == GunBan[8] && GGunBan[9] == GunBan[9] && GGunBan[10] == GunBan[10] && GGunBan[11] == GunBan[11] && GGunBan[12] == GunBan[12])
		{
			name = TEXT("이도현");
			text = TEXT("좋았어…! 이제 나가기만 하면 된다.");
			FontSet(hdc, grt, nrt, text, name, ttext, P_IllBit, 1, FONTSIZE, RGB(0, 0, 0), 0, 0);
			Door = 1;
			Class1Door = 1;
		}
		else if (hint == 2)
		{
			name = TEXT("이도현");
			text = TEXT("혹시 지금까지 모은 일기장과 악보에 힌트가 있으려나?");
			FontSet(hdc, grt, nrt, text, name, ttext, P_IllBit, 1, FONTSIZE, RGB(0, 0, 0), 0, 0);
		}
		else
		{
			hint++;
			page = 100;
		}
		break;
	default:
		Sound = 0;
		page = 0;
		Stop = false;
		EndPianoint = false;
		break;
	}
}
//마지막 피아노 상호작용
void End(HDC hdc)
{
	HFONT font, oldfont;

	x = 0;
	y = 0;
	stage = -1;
	if (Sound == 0)
	{
		SetTimer(hWndMain, 7, 10, NULL);
		Sound = 1;
	}

	DrawBitmap(hdc, 0, 0, BokDoBit[2]);
	

	TransBlt(hdc, 260, 480, BoxBit[2], RGB(75, 75, 75));
	TransBlt(hdc, 330, 480, BoxBit[2], RGB(75, 75, 75));
	TransBlt(hdc, 470, 230, SchoolDeskBit[0], RGB(75, 75, 75));
	TransBlt(hdc, 570, 230, SchoolDeskBit[0], RGB(75, 75, 75));
	TransBlt(hdc, 670, 230, SchoolDeskBit[0], RGB(75, 75, 75));
	TransBlt(hdc, 770, 230, ChairBit[3], RGB(75, 75, 75));
	TransBlt(hdc, 840, 230, ChairBit[3], RGB(75, 75, 75));
	
	//복도 3 맵 구성

	if (Endingy > -500)
	{
		if (NPCDie < 1)
		{
			if (NPCFree == 1)
			{
				DrawBitmap(hdc, 110, 0, Ending[1]);
			}
			if (NPCFree == 2)
			{
				DrawBitmap(hdc, 110, 0, Ending[2]);
			}
			if (NPCFree == 3)
			{
				DrawBitmap(hdc, 110, 0, Ending[3]);
			}
			if (NPCFree == 4)
			{
				DrawBitmap(hdc, 110, 0, Ending[4]);
			}
		}
		else
		{
			DrawBitmap(hdc, 110, 0, Ending[0]);
		}
	}

	RECT rt = { 1000,Endingy + 1250, 1280,  Endingy + 10000 };

	SetBkMode(hdc, TRANSPARENT);
	font = CreateFont(60, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 3, 2, 1,
		VARIABLE_PITCH | FF_ROMAN, "맑은 고딕");
	oldfont = (HFONT)SelectObject(hdc, font);
	SetTextColor(hdc, RGB(255, 255, 255));
	DrawText(hdc, EndingCredit, -1, &rt, DT_WORDBREAK);
	DeleteObject(SelectObject(hdc, oldfont));

	if (NPCDie > 0)
	{
		TransBlt(hdc, -200, Endingy + 1250, Ending[6], RGB(75, 75, 75));
	}
	else if(NPCDie == 0)
	{
		TransBlt(hdc, -200, Endingy + 1250, Ending[5], RGB(75, 75, 75));
	}

	if (Endingy < -2500)
	{
		DrawBitmap(hdc, 0, 0, Ending[7]);
		if (Sound == 1)
		{
			mciSendCommand(dwID, MCI_CLOSE, 0, NULL);//정지 및 메모리에서 삭제
			dwID = 0;

			openBgm.lpstrDeviceType = "mpegvideo";// wave , "mpegvideo"; //mp3 형식
			openBgm.lpstrElementName = "Fire.mp3";
			mciSendCommand(0, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD)(LPVOID)&openBgm);
			dwID = openBgm.wDeviceID;
			mciSendCommand(dwID, MCI_PLAY, MCI_DGV_PLAY_REPEAT, (DWORD)(LPVOID)&openBgm);
			Sound = 2;
		}
	}
	if (Endingy < -3000)
	{
		mciSendCommand(dwID, MCI_CLOSE, 0, NULL);//정지 및 메모리에서 삭제
		dwID = 0;

		page = 0;
		Sound = 0;
		Titleint = true;

		Endingint = false;
	}

}
//엔딩

void Storys(HDC hMemDC)
{

	if (Startint)			//시작 설명
	{
		Start(hMemDC);
	}

	if (MainDoorint)	//정문 대화
	{
		MainDoor(hMemDC);
	}

	if (Skeletonint)	//해골 대화
	{
		Skeleton(hMemDC);
	}

	if (SchoolDesk3int)	//책이 올려진 책상 대화
	{
		SchoolDesk3(hMemDC);
	}

	if (Diaryint)	//일기장과 대화
	{
		Diary(hMemDC);
	}

	if (Boardint)	//칠판과 대화
	{
		Board(hMemDC);
	}

	if (Openint)	//열수있을 때 잠긴문과 대화
	{
		Open(hMemDC);
	}

	if (Boxint)		//상자와 대화
	{
		Box(hMemDC);
	}

	if (FakeBoxint)		//가짜상자와 대화
	{
		Box(hMemDC);
	}

	if (Pianoint)		//피아노와 대화
	{
		Piano(hMemDC);
	}

	if (CloseDoorint)	//잠긴문 대화
	{
		CloseDoor(hMemDC);
	}

	if (CloseDoor2int)	//1-2반 문 대화
	{
		CloseDoor2(hMemDC);
	}

	if (FirstReadint)	//일기장 처음 읽었을 때 대화
	{
		FirstDiary(hMemDC);
	}

	if (Prisonint)	//1-4반 처음 들어갈 때 대화
	{
		Prison(hMemDC);
	}

	if (Keyint)	//열쇠 주울 때 대화
	{
		Key(hMemDC);
	}

	if (Lelaint)	//렐라 때 대화
	{
		Lela(hMemDC);
	}

	if (Healint)	//보건실 처음 입장 대화
	{
		Heal(hMemDC);
	}

	if (HHealint)	//커맨드 입력 후 대화
	{
		HHeal(hMemDC);
	}

	if (Boomint)	//1-2반 처음 입장 대화
	{
		Boom(hMemDC);
	}

	if (BokDoBoxint)	//복도 박스 오랜시간 못찾을 때 대화
	{
		BokDoBox(hMemDC);
	}

	if (EndPianoint)	//마지막 피아노 대화
	{
		EndPiano(hMemDC);
	}

	if (Endingint)	//엔딩
	{
		End(hMemDC);
	}













	if (Titleint)
	{
		Title(hMemDC);
	}
}
//상호작용

void ComeOn()
{
	if (NPCstage1 != stage && !NPC1stop)
	{
		if (LengthPts(x, y, NPC1x, NPC1y) > 50)
		{
			NPC1x = x - 10;
			NPC1y = y - 10;
		}
		NPCstage1 = stage;
	}
	if (NPCstage2 != stage && !NPC2stop)
	{
		if (LengthPts(x, y, NPC2x, NPC2y) > 50)
		{
			NPC2x = x - 10;
			NPC2y = y - 10;
		}
		NPCstage2 = stage;
	}
	if (NPCstage3 != stage && !NPC3stop)
	{
		if (LengthPts(x, y, NPC3x, NPC3y) > 50)
		{
			NPC3x = x - 10;
			NPC3y = y - 10;
		}
		NPCstage3 = stage;
	}
	if (NPCstage4 != stage && !NPC4stop)
	{
		if (LengthPts(x, y, NPC4x, NPC4y) > 50)
		{
			NPC4x = x - 10;
			NPC4y = y - 10;
		}
		NPCstage4 = stage;
	}
}
//NPC 따라오게 하기

void OnTimer()
{
	RECT crt;
	HDC hdc, hMemDC;
	HBITMAP OldBit;
	HFONT font = NULL, oldfont = NULL;

	GetClientRect(hWndMain, &crt);
	hdc = GetDC(hWndMain);

	if (!hBit)
	{
		hBit = CreateCompatibleBitmap(hdc, crt.right, crt.bottom);
	}

	hMemDC = CreateCompatibleDC(hdc);
	OldBit = (HBITMAP)SelectObject(hMemDC, hBit);

	ComeOn();

	if (Time >= 0 && !Stop)
	{
		Time++;
	}
	if (Time == 150 && HealDoor < 2)
	{
		Lelaint = true;
	}
	if (Time == 500 && HealDoor == 2 && BokDoBoxCheck == -1)
	{
		HHealint = true;
	}
	if (Time == 1500 && BokDoBoxCheck == 0 && HealDoor >= 2)
	{
		BokDoBoxint = true;
	}

	if (DayCheck == 0)
	{
		DayCheckBar = 8;
	}
	else if (DayCheck == 1 && PianoMusic == -1)
	{
		DayCheckBar = 1;
	}

	if (DayCheckBar == 1 && FirstRead < 1)		//일기장 처음읽은거 체크
	{
		FirstRead = 1;
	}
	if (DayCheckBar == 2 && FirstRead < 2)
	{
		FirstRead = 2;
	}
	if (DayCheckBar == 3 && FirstRead < 3)
	{
		FirstRead = 3;
	}

	if (Command == 4)
	{
		Command = -1;
		Healint = true;
	}

	if (x > 1200)		//stage 이동
	{
		stage++;
		x = -80;
	}
	if (x < -80)
	{
		stage--;
		x = 1200;
	}


	BackGround(hMemDC);				//배경


	PlayerDraw(hMemDC);				//플레이어 및 오브젝트

	Storys(hMemDC);				//스토리

	if (Inventory == 1)			//일기장 열었을 때
	{

		if (DayCheckBar == 7)
		{
			TransBlt(hMemDC, 200, 100, EndDiaryBit, RGB(75, 75, 75));
		}
		else
		{
			TransBlt(hMemDC, 200, 100, DiaryBit, RGB(75, 75, 75));
		}

		switch (DayCheckBar)
		{
		case 1:
			TransBlt(hMemDC, 205, 109, DayCheckBit, RGB(75, 75, 75));
			DiaryFontSet(hMemDC, DiaryText1, 30, RGB(0, 0, 0));
			break;
		case 2:
			TransBlt(hMemDC, 205, 170, DayCheckBit, RGB(75, 75, 75));
			DiaryFontSet(hMemDC, DiaryText2, 22, RGB(0, 0, 0));
			break;
		case 3:
			TransBlt(hMemDC, 205, 226, DayCheckBit, RGB(75, 75, 75));
			ttext = TEXT("\n\n\n\n\n            푸른하늘");
			DiaryFontSet(hMemDC, DiaryText3, 22, RGB(0, 0, 0));
			DiaryFontSet(hMemDC, ttext, 22, RGB(0, 0, 255));
			break;
		case 4:
			TransBlt(hMemDC, 205, 287, DayCheckBit, RGB(75, 75, 75));
			ttext = TEXT("\n                                                 하얀쪽배");
			DiaryFontSet(hMemDC, DiaryText4, 30, RGB(0, 0, 0));
			DiaryFontSet(hMemDC, ttext, 30, RGB(0, 0, 255));
			break;
		case 5:
			TransBlt(hMemDC, 205, 345, DayCheckBit, RGB(75, 75, 75));
			ttext = TEXT("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n은하수");
			text = TEXT("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n죽여야 하나? 죽여?!");
			DiaryFontSet(hMemDC, DiaryText5, 22, RGB(0, 0, 0));
			DiaryFontSet(hMemDC, ttext, 22, RGB(0, 0, 255));
			DiaryFontSet(hMemDC, text, 22, RGB(170, 0, 0));
			break;
		case 6:
			TransBlt(hMemDC, 205, 405, DayCheckBit, RGB(75, 75, 75));
			ttext = TEXT("\n\n\n\n\n\n\n\n\n\n\n\n                                                                   (힘듦)");
			text = TEXT("\n\n\n\n\n\n\n\n\n                    (쉬움)");
			name = TEXT("\n\n\n\n                   (보통)");
			DiaryFontSet(hMemDC, DiaryText6, 20, RGB(0, 0, 0));
			DiaryFontSet(hMemDC, ttext, 20, RGB(170, 0, 0));
			DiaryFontSet(hMemDC, text, 20, RGB(170, 0, 0));
			DiaryFontSet(hMemDC, name, 20, RGB(170, 0, 0));
			break;
		case 7:
			TransBlt(hMemDC, 205, 465, DayCheckBit, RGB(75, 75, 75));
			DiaryFontSet(hMemDC, DiaryText7, 30, RGB(0, 0, 0));
			break;
		case 8:
			TransBlt(hMemDC, 205, 526, DayCheckBit, RGB(75, 75, 75));
			TransBlt(hMemDC, 368, 100, MusicBit, RGB(75, 75, 75));
			break;
		}
		DayText = TEXT(" 첫번째 일기\n\n 두번째 일기\n\n 세번째 일기\n\n 네번째 일기\n\n다섯번째 일기\n\n여섯번째 일기\n\n일곱번째 일기");
		DayFontSet(hMemDC, DayText, 30, RGB(255, 255, 255), DayCheck);
		RECT mrt = { 265, 530, 500, 1000 };
		if (PianoMusic >= 0)
		{
			font = CreateFont(30, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 3, 2, 1,
				VARIABLE_PITCH | FF_ROMAN, "맑은 고딕");
			SetBkMode(hMemDC, TRANSPARENT);
			oldfont = (HFONT)SelectObject(hMemDC, font);
			SetTextColor(hMemDC, RGB(255, 255, 255));
			DrawText(hMemDC, MusicText, -1, &mrt, DT_WORDBREAK);

			DeleteObject(SelectObject(hMemDC, oldfont));
		}
	}
	if (Map == 1)				//비상대피도 열었을 때
	{
		TransBlt(hMemDC, 100, 100, MapBit, RGB(75, 75, 75));
	}

	SelectObject(hMemDC, OldBit);

	DeleteDC(hMemDC);
	ReleaseDC(hWndMain, hdc);
	InvalidateRect(hWndMain, NULL, FALSE);
}

void Create()
{
	for (int i = 0; i < 4; i++)
	{
		P_Bit[i] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP1 + i));			//PLAYER
	}
	for (int i = 0; i < 2; i++)
	{
		P_IllBit[i] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP4 + i));			//PLAYER 일러스트
	}
	P_IllBit[2] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP83));
	P_IllBit[3] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP84));


	for (int i = 0; i < 4; i++)
	{
		NPC1Bit[i] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP7 + i));		//NPC
	}
	for (int i = 0; i < 2; i++)
	{
		N1_IllBit[i] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP26 + i));		//NPC 일러스트
	}
	NPC1Bit[4] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP94));		//NPC1 사망
	N1_IllBit[2] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP85));


	for (int i = 0; i < 4; i++)
	{
		NPC2Bit[i] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP28 + i));		//NPC2
	}
	for (int i = 0; i < 2; i++)
	{
		N2_IllBit[i] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP40 + i));		//NPC2 일러스트
	}
	NPC2Bit[4] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP72));		//NPC2 사망
	N2_IllBit[2] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP88));
	N2_IllBit[3] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP89));


	for (int i = 0; i < 4; i++)
	{
		NPC3Bit[i] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP32 + i));		//NPC3
	}
	for (int i = 0; i < 2; i++)
	{
		N3_IllBit[i] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP42 + i));		//NPC3 일러스트
	}
	NPC3Bit[4] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP92));		//NPC3 사망
	N3_IllBit[2] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP86));
	N3_IllBit[3] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP87));


	for (int i = 0; i < 4; i++)
	{
		NPC4Bit[i] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP36 + i));		//NPC4
	}
	for (int i = 0; i < 2; i++)
	{
		N4_IllBit[i] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP44 + i));		//NPC4 일러스트
	}
	NPC4Bit[4] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP93));		//NPC4 사망


	for (int i = 0; i < 5; i++)
	{
		BokDoBit[i] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP16 + i));				//배경
	}
	for (int i = 0; i < 2; i++)
	{
		LeftDoorBit[i] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP22 + i));
		RightDoorBit[i] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP23 + i));
	}
	//UI...
	TextBox[0] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP25));
	TextBox[1] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP52));
	System[0] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP46));
	DiaryBit = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP51));
	MapBit = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP55));
	DayBit = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP59));
	DayCheckBit = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP73));
	MusicBit = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP74));
	ChoiceBit = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP78));
	LockBit = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP79));
	LockPWBit = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP80));
	SelectBit = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP81));
	EndDiaryBit = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP103));
	TitleBit = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP104));
	ArrowBit = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP105));
	BoomBit = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP106));
	OptionBit = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP107));



	//오브젝트...
	SkeletonBit = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP47));			//해골
	for (int i = 0; i < 3; i++)
	{
		SchoolDeskBit[i] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP49 + i));		//책상
	}
	SchoolDeskBit[3] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP82));		//음악실 책상
	BoardBit = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP54));
	for (int i = 0; i < 3; i++)
	{
		BoxBit[i] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP56 + i));			//상자
	}
	for (int i = 0; i < 5; i++)
	{
		ChairBit[i] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP60 + i));			//의자
	}
	PianoBit = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP65));			//피아노
	OfficeDeskBit = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP70));		//오피스 책상 오른쪽
	OfficeDeskBit2 = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP71));	//오피스 책상 왼쪽
	BedBit = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP66));		//침대
	CabinetBit = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP67));		//캐비넷
	LectureTableBit = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP68));		//교탁
	LockerBit = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP69));		//사물함
	for (int i = 0; i < 2; i++)
	{
		IronBarBit[i] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP14 + i));		//철창
	}
	KeyBit = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP75));		//열쇠
	ClockBit = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP90));
	TimeBit = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP91));



	//기타
	Black[0] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP76));
	Black[1] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP77));

	SeeBit = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP108));	//시야 가리개


	//엔딩
	Ending[0] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP99));		//솔로엔딩
	Ending[1] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP95));		//NPC1
	Ending[2] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP96));		//NPC2
	Ending[3] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP97));		//NPC3
	Ending[4] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP98));		//NPC4
	Ending[5] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP101));	//4구엔딩
	Ending[6] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP100));	//5구엔딩
	Ending[7] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP102));	//BLACK

}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	RECT crt;
	HDC hdc;
	PAINTSTRUCT ps;

	switch (iMessage) {

	case WM_CREATE:
		Create();

		Startint = true;

		SetTimer(hWnd, 1, 100, NULL);		//프레임 속도
		SetTimer(hWnd, 0, 10, NULL);		//OnTimer, GetKeyState
		SetTimer(hWnd, 2, 400, NULL);		// 걷는소리 내는 시간
		SetTimer(hWnd, 3, 1000, NULL);		//커맨드 입력받는 시간
		SetTimer(hWnd, 4, 10, NULL);		//배경음 체크

		return 0;

	case WM_TIMER:

		switch (wParam)
		{
		case 0:
			StageCheck();

			if (!Stop)
			{
				if (x > MaxX1)
				{
					if (GetKeyState(VK_LEFT) & 0x8000)            //가상 키코드 (현재 상태에 키보드 상태를 물어봄) 현재 상태에서 키가 눌렷는지 확인해봄(값이 0x 8000)
					{
						x -= SPEED;
						direction = true;
						stop = false;
					}
				}

				if (x < MaxX2)
				{
					if (GetKeyState(VK_RIGHT) & 0x8000)            //가상 키코드 (현재 상태에 키보드 상태를 물어봄)
					{
						x += SPEED;
						direction = false;
						stop = false;
					}
				}

				if (y > MaxY1)
				{
					if (GetKeyState(VK_UP) & 0x8000)            //가상 키코드 (현재 상태에 키보드 상태를 물어봄)
					{
						y -= SPEED;
						directionY = true;
						stop = false;
					}
				}

				if (y < MaxY2)
				{
					if (GetKeyState(VK_DOWN) & 0x8000)            //가상 키코드 (현재 상태에 키보드 상태를 물어봄)
					{
						y += SPEED;
						directionY = false;
						stop = false;
					}
				}
				
			}
			OnTimer();
			break;
		case 1:
			pfrm++;
			pfrm %= 4;
			break;
		case 2:
			if (!stop && !Stop)
			{
				PlaySound("Move_4.wav", NULL, SND_ASYNC);
			}
			break;
		case 3:
			if (Command == -1)
			{
				Command = -1;
				KillTimer(hWnd, 3);
			}
			if (Command > 0)
			{
				Command = 0;
			}
			break;
		case 4:
			if (BGMCheck == 1 && Titleint)
			{
				mciSendCommand(dwID, MCI_CLOSE, 0, NULL);//정지 및 메모리에서 삭제
				dwID = 0;

				openBgm.lpstrDeviceType = "mpegvideo";// wave , "mpegvideo"; //mp3 형식
				openBgm.lpstrElementName = "Mosaic.mp3";
				mciSendCommand(0, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD)(LPVOID)&openBgm);
				dwID = openBgm.wDeviceID;
				mciSendCommand(dwID, MCI_PLAY, MCI_DGV_PLAY_REPEAT, (DWORD)(LPVOID)&openBgm);
				BGMCheck = 2;
			}
			if (BGMCheck == 1)
			{
				mciSendCommand(dwID, MCI_CLOSE, 0, NULL);//정지 및 메모리에서 삭제
				dwID = 0;

				openBgm.lpstrDeviceType = "mpegvideo";// wave , "mpegvideo"; //mp3 형식
				openBgm.lpstrElementName = "BGM.mp3";
				mciSendCommand(0, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD)(LPVOID)&openBgm);
				dwID = openBgm.wDeviceID;
				mciSendCommand(dwID, MCI_PLAY, MCI_DGV_PLAY_REPEAT, (DWORD)(LPVOID)&openBgm);
				BGMCheck = 2;
			}
			else if (BGMCheck == 0)
			{
				mciSendCommand(dwID, MCI_CLOSE, 0, NULL);//정지 및 메모리에서 삭제
				dwID = 0;

				BGMCheck = -1;
			}
			break;
		case 5:
			Cho2--;
			if (Cho2 == -1)
			{
				Cho1--;
				Cho2 = 9;
			}
			if (Cho1 == -1)
			{
				Cho1 = 5;
				Boon--;
			}
			if (Cho1 == 0 && Cho2 == 0 && Boon == 0)
			{
				if (NPCFree == 1)
				{
					NPC1stop = true;
					NPCDie = 1;
				}
				if (NPCFree == 2)
				{
					NPC2stop = true;
					NPCDie = 2;
				}
				if (NPCFree == 3)
				{
					NPC3stop = true;
					NPCDie = 3;
				}
				if (NPCFree == 4)
				{
					NPC4stop = true;
					NPCDie = 4;
				}
				SetTimer(hWnd, 6, 100, NULL);
			}
			if (NPCDie > 0)
			{
				KillTimer(hWnd, 5);
			}
			break;
		case 6:
			dfrm++;
			if (dfrm == 3)
			{
				KillTimer(hWnd, 6);
			}
			break;
		case 7:
			Endingy -= 1;
			break;
		}
		return 0;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case 0x31:
			if (SpaceStop == 1)
			{
				PlaySound("도.wav", NULL, SND_ASYNC);
				ScanGunBan = 1;
				page++;
			}
			break;
		case 0x32:
			if (SpaceStop == 1)
			{
				PlaySound("레.wav", NULL, SND_ASYNC);
				ScanGunBan = 2;
				page++;
			}
			break;
		case 0x33:
			if (SpaceStop == 1)
			{
				PlaySound("미.wav", NULL, SND_ASYNC);
				ScanGunBan = 3;
				page++;
			}
			break;
		case 0x34:
			if (SpaceStop == 1)
			{
				PlaySound("파.wav", NULL, SND_ASYNC);
				ScanGunBan = 4;
				page++;
			}
			break;
		case 0x35:
			if (SpaceStop == 1)
			{
				
				if (page == 9)
				{
					PlaySound("낮은솔.wav", NULL, SND_ASYNC);
				}
				else
				{
					PlaySound("솔.wav", NULL, SND_ASYNC);
				}
				ScanGunBan = 5;
				page++;
			}
			break;
		case 0x36:
			if (SpaceStop == 1)
			{
				if (page == 10)
				{
					PlaySound("낮은라.wav", NULL, SND_ASYNC);
				}
				else
				{
					PlaySound("라.wav", NULL, SND_ASYNC);
				}
				ScanGunBan = 6;
				page++;
			}
			break;
		case 0x37:
			if (SpaceStop == 1)
			{
				PlaySound("시.wav", NULL, SND_ASYNC);
				ScanGunBan = 7;
				page++;
			}
			break;
		case 0x38:
			if (SpaceStop == 1)
			{
				PlaySound("높은도.wav", NULL, SND_ASYNC);
				ScanGunBan = 8;
				page++;
			}
			break;
		case VK_UP:
			if (Inventory == 1 && 1 < DayCheckBar)
			{
				DayCheckBar--;
			}
			if (PianoMusic >= 0 && DayCheckBar > DayCheck)
			{
				DayCheckBar = DayCheck;
			}
			if (SelectButton == 1)
			{
				if (Select != 1)
				{
					Select--;
				}
			}
			if (Command > 0)
			{
				Command = 0;
			}
			if (Titleint && TitleSelect != 1)
			{
				TitleSelect--;
			}
			break;
		case VK_DOWN:
			if (Inventory == 1 && DayCheck + 1 > DayCheckBar)
			{
				DayCheckBar++;
				if (PianoMusic == -1 && DayCheck + 1 == DayCheckBar)
				{
					DayCheckBar = DayCheck;
				}
			
				if (PianoMusic == -1)
				{
					if (DayCheck == 8)
					{
						DayCheck = 7;
					}
				}
			}
			if (SelectButton == 1)
			{
				if (Select != 4)
				{
					Select++;
				}
			}
			if (PianoMusic >= 0 && DayCheckBar == DayCheck + 1)
			{
				DayCheckBar = 8;
			}
			if (Command > 0)
			{
				Command = 0;
			}
			if (Titleint && TitleSelect != 3)
			{
				TitleSelect++;
			}
			break;
		case VK_LEFT:
			if (SelectButton == 1)
			{
				if (Select == 1)
				{
					pwfrm1--;
					pwfrm1 %= 10;
					if (pwfrm1 == -1)
					{
						pwfrm1 = 9;
					}
				}
				if (Select == 2)
				{
					pwfrm2--;
					pwfrm2 %= 10;
					if (pwfrm2 == -1)
					{
						pwfrm2 = 9;
					}
				}
				if (Select == 3)
				{
					pwfrm3--;
					pwfrm3 %= 10;
					if (pwfrm3 == -1)
					{
						pwfrm3 = 9;
					}
				}
				if (Select == 4)
				{
					pwfrm4--;
					pwfrm4 %= 10;
					if (pwfrm4 == -1)
					{
						pwfrm4 = 9;
					}
				}
			}
			if (Choose == 1)
			{
				if (Command == -1 && Choice != 1)
				{
					Choice--;
				}
				else
				{
					Choice = 1;
				}
			}
			if (Command == 0)
			{
				Command = 1;
			}
			if (Command == 2)
			{
				Command = 3;
			}
			if (BoomPW > 0 && BoomPW != 1)
			{
				BoomPW--;
			}
			if (OptionCheck == 1)
			{
				OptionSelect = 1;
			}
			break;
		case VK_RIGHT:
			if (SelectButton == 1)
			{
				if (Select == 1)
				{
					pwfrm1++;
					pwfrm1 %= 10;
				}
				if (Select == 2)
				{
					pwfrm2++;
					pwfrm2 %= 10;
				}
				if (Select == 3)
				{
					pwfrm3++;
					pwfrm3 %= 10;
				}
				if (Select == 4)
				{
					pwfrm4++;
					pwfrm4 %= 10;
				}
			}
			if (Choose == 1)
			{
				if (Command == -1 && Choice != 3)
				{
					Choice++;
				}
				if (Command != -1)
				{
					Choice = 2;
				}
			}
			if (Command == 1)
			{
				Command = 2;
			}
			if (Command == 3)
			{
				Command = 4;
			}
			if (BoomPW > 0 && BoomPW != 5)
			{
				BoomPW++;
			}
			if (OptionCheck == 1)
			{
				OptionSelect = 2;
			}
			break;
		case VK_ESCAPE:
			if (BoomPW > 0)
			{
				page = 100;
			}

			if (Inventory >= 0)
			{
				if (Map != 1)
				{
					if (Inventory == 1)
					{
						Inventory = 0;
						PlaySound("Book.wav", NULL, SND_ASYNC);
						if (FirstRead == 2)
						{
							FirstReadint = true;
						}
						if (FirstRead == 3)
						{
							FirstReadint = true;
						}
						Stop = false;
					}
				}
			}

			if (Map >= 0)
			{
				if (Inventory != 1)
				{
					if (Map == 1)
					{
						PlaySound("Book_2.wav", NULL, SND_ASYNC);
						Map = 0;
						Stop = false;
					}
				}
			}
			break;
		case VK_CONTROL:
			PostQuitMessage(0);
			break;
		case VK_SPACE:
			if (!Stop)
			{
				StageMove();
				Interaction();
			}
			else
			{
				if (Inventory != 1 && Map != 1 && SpaceStop == 0)
				{
					page++;
				}
			}
			break;
		case 'I':
			if (Inventory >= 0)
			{
				if (Map != 1)
				{
					if (Inventory == 0 && !Stop)
					{
						Inventory = 1;
						PlaySound("Book.wav", NULL, SND_ASYNC);
						Stop = true;
					}
					else if (Inventory == 1 && !EndPianoint)
					{
						Inventory = 0;
						PlaySound("Book.wav", NULL, SND_ASYNC);
						if (FirstRead == 2)
						{
							FirstReadint = true;
						}
						if (FirstRead == 3)
						{
							FirstReadint = true;
						}
						Stop = false;
					}
				}
				if (Inventory == 0 && EndPianoint)
				{
					Inventory = 1;
					PlaySound("Book.wav", NULL, SND_ASYNC);
					Stop = true;
				}
				else if (Inventory == 1 && EndPianoint)
				{
					Inventory = 0;
					PlaySound("Book.wav", NULL, SND_ASYNC);
				}
			}
			break;
		case 'M':
			if (Map >= 0)
			{
				if (Inventory != 1)
				{
					if (Map == 0 && !Stop)
					{
						PlaySound("Book_2.wav", NULL, SND_ASYNC);
						Map = 1;
						Stop = true;
					}
					else if (Map == 1)
					{
						PlaySound("Book_2.wav", NULL, SND_ASYNC);
						Map = 0;
						Stop = false;
					}
				}
			}
			break;
		case 'Z':
			OpenDoor++;
			break;
		}
	case WM_KEYUP:
		switch (wParam)
		{
		case VK_LEFT:
			if (!(GetKeyState(VK_DOWN) & 0x8000) && !(GetKeyState(VK_UP) & 0x8000) && !(GetKeyState(VK_LEFT) & 0x8000) && !(GetKeyState(VK_RIGHT) & 0x8000))
			{
				stop = true;
				PlaySound(NULL, NULL, 0);
			}
			break;
		case VK_RIGHT:
			if (!(GetKeyState(VK_DOWN) & 0x8000) && !(GetKeyState(VK_UP) & 0x8000) && !(GetKeyState(VK_LEFT) & 0x8000) && !(GetKeyState(VK_RIGHT) & 0x8000))
			{
				stop = true;
				PlaySound(NULL, NULL, 0);
			}
			break;
		case VK_UP:
			if (!(GetKeyState(VK_DOWN) & 0x8000) && !(GetKeyState(VK_UP) & 0x8000) && !(GetKeyState(VK_LEFT) & 0x8000) && !(GetKeyState(VK_RIGHT) & 0x8000))
			{
				stop = true;
				PlaySound(NULL, NULL, 0);
			}
			break;
		case VK_DOWN:
			if (!(GetKeyState(VK_DOWN) & 0x8000) && !(GetKeyState(VK_UP) & 0x8000) && !(GetKeyState(VK_LEFT) & 0x8000) && !(GetKeyState(VK_RIGHT) & 0x8000))
			{
				stop = true;
				PlaySound(NULL, NULL, 0);
			}
			break;
		}

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		DrawBitmap(hdc, 0, 0, hBit);

		EndPaint(hWnd, &ps);
		return 0;
	case WM_DESTROY:
		KillTimer(hWnd, 0);
		KillTimer(hWnd, 1);
		KillTimer(hWnd, 2);
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}
