//
// Stock II
// (c) 2016~2018 Naissoft.
//
/*========================================================*/
/* Source : Main .cpp                                     */
/*                                                        */
/* Purpose : Main code where game is running              */
/*                                                        */
/* Author : Naissoft                                      */
/*                                                        */
/*========================================================*/

#include "GameFunctions.h"

int main(void)
{
	int menu, cnt, order;
	char key, pausemenu;


	//Set window console
	system("title Stock 2 - 주식 게임 2");

	system("mode con: cols=120 lines=40");

	//Copyright
	StartLogo();

	//Initialize game setting
	InitStock();
	Init();

	cnt = month = day = hour = order = 0;

	PrintMainMenu();
	scanf("%d", &menu);

	switch (menu)
	{

	case 1:
		ChangeStockPrice();
		Save();
		break;

	case 2:
		Load();
		break;

	case 3:
		return -1;

	default:
		//TODO: if user enter default value, program should announce 'it's wrong value
		break;
	}

	system("cls");

	DrawNewspaper(companyOrder[order]);

	while (true)
	{
		ShowMain();
		DrawGraph(companyOrder[order]);
		showCompanyReport(companyOrder[order]);

		if (Money <= 0)
		{
			printf("\n 파산... 3000원 대출해 드리겠습니다.");
			getchar();
			Loan(3000);
			system("cls");
		}

		gotoxy(57, 10 + order - 1);
		printf("  ");
		gotoxy(57, 10 + order + 1);
		printf("  ");
		gotoxy(57, 10 + order);
		printf("◀");

		key = '\0';
		getKey(&key);

		switch (key)
		{

			//Press 'b' or 'B' to buy stock
		case 'b':
		case 'B':
			BuyMenu(companyOrder[order]);
			break;

			//Press 'v' or 'V' to see the list of stocks
		case 'v':
		case 'V':
			ShowStockList();
			break;

			//Press 'esc' to pause game
		case 27:
			system("cls");
			titleLine("일시 정지");
			printf(" 1. 통  계\n\n 2. 대  출\n\n 3. 갚  기\n\n 4. 설  정\n\n 5. 끝내기\n\n Esc 돌아가기");

			pausemenu = getch();

			switch (pausemenu)
			{

			case '1':
				showStats();
				break;

			case '2':
				loanMenu();
				break;

			case '3':
				Payback();
				break;
			case '4':
				settingMenu();
				break;

			case '5':
				system("cls");
				printf("\n 종료하시겠습니까? 저장되지 않은 정보는 사라집니다.\n Y / N");

				char ch;
				ch = getch();

				if (ch == 'Y' || ch == 'y') 
					return 0;

				break;

			case 27:
				break;

			default:
				break;
			}
			system("cls");
			Sleep(100);
			break;

			//Press 's' or 'S' to sell some stock
		case 's':
		case 'S':
			SellMenu();
			break;

			//Press 'e' or 'E' to save game
		case 'E':
		case 'e':
			system("cls");
			Save();
			printf("\n 게임이 저장되었습니다.");
			Sleep(300);
			break;

			//Press 'w' or 'W' to increase 'cnt' variable
		case 'W':
		case 'w':

			if (timemode == 1)
			{
				while (cnt % 20 != 0) cnt++;
				cnt += 20;
				Sleep(100);
			}

			break;

			//Press 'i' or 'I' to see information of companies
		case 'I':
		case 'i':
			showCompanyInfo();
			break;

			//Press '2' to increase 'order' variable
			//If the 'order' variable increases, the cursor move down
		case '2':

			if (order < MAX_COMPANY - 1) 
				order++;

			DrawNewspaper(companyOrder[order]);
			break;

			//Press '8' to decrease 'order' variable
			//If the 'order' variable decreases, the cursor move up
		case '8':

			if (order > 0) 
				order--;

			DrawNewspaper(companyOrder[order]);
			break;

		default:
			break;
		}

		for (int i = 0; i < MAX_COMPANY; i++)
			prevStockPrice[i] = StockPrice[i];

		if (cnt % 20 == 0)
		{
			ChangeStockPrice();
			UpdateGraphData();
		}

		if (cnt % 20 == 0)
			hour++;

		if (cnt % 60 == 0)
			ShowTipNews();

		/* 하루마다 각 회사 상황이 바뀝니다					*/
		/* 50% 확률로 상황이 좋아지거나 나빠집니다				*/
		if (hour == 1)
		{
			for (int i = 0; i < MAX_COMPANY; i++)
			{
				if (rand() % 2 == 0)
					ifGood[i] = true;

				else
					ifGood[i] = false;
			}
		}

		/* 하루마다 상환 금액이 증가합니다 */
		if (hour > 23)
		{
			hour = 0;
			Interest();
			day++;
		}

		/* 매월 세금을 냅니다 */
		if (day > days[month] - 1)
		{
			day = 0;
			month++;
			Money -= TAX(Money);
		}

		if (month > 11)
			month = 0;

		if (timemode == 0)
		{
			clearbuffer();
			Sleep(DELAY);
			cnt++;
		}

		else if (timemode == 1)
		{
			clearbuffer();
			Sleep(DELAY);
		}
	}

	getchar();
	DeallocateStock();

	return 0;
}
