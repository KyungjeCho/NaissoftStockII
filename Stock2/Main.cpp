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
	system("title Stock 2 - �ֽ� ���� 2");

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
			printf("\n �Ļ�... 3000�� ������ �帮�ڽ��ϴ�.");
			getchar();
			Loan(3000);
			system("cls");
		}

		gotoxy(57, 10 + order - 1);
		printf("  ");
		gotoxy(57, 10 + order + 1);
		printf("  ");
		gotoxy(57, 10 + order);
		printf("��");

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
			titleLine("�Ͻ� ����");
			printf(" 1. ��  ��\n\n 2. ��  ��\n\n 3. ��  ��\n\n 4. ��  ��\n\n 5. ������\n\n Esc ���ư���");

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
				printf("\n �����Ͻðڽ��ϱ�? ������� ���� ������ ������ϴ�.\n Y / N");

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
			printf("\n ������ ����Ǿ����ϴ�.");
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

		/* �Ϸ縶�� �� ȸ�� ��Ȳ�� �ٲ�ϴ�					*/
		/* 50% Ȯ���� ��Ȳ�� �������ų� �������ϴ�				*/
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

		/* �Ϸ縶�� ��ȯ �ݾ��� �����մϴ� */
		if (hour > 23)
		{
			hour = 0;
			Interest();
			day++;
		}

		/* �ſ� ������ ���ϴ� */
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
