#include <stdio.h>
#include <time.h>
#include <conio.h>
#include <stdlib.h>
#include <Windows.h>

#include "StockFunctions.h"
#include "Stock.h"

unsigned long Money;
int StockPrice[MAX_COMPANY], PrevStockPrice[MAX_COMPANY], StockDeal, loanMoney, companyOrder[MAX_COMPANY];
int Stocks; // will change variable name. it shows how much stock user has
int GraphData[MAX_COMPANY][48] = { 0 };
bool ifGood[MAX_COMPANY];

char *CompanyName[MAX_COMPANY] =
{
	"Naissoft",
	"HawTech",
	"�ϰܳ��",
	"MK Electronics",
	"���뱺��",
	"CJ ���ϼտ���",
	"KJS �ý���",
	"Fruit",
	"������ ���ͽ�",
	"�������",
};

void ChangeStockPrice()
{
	srand((int)time(NULL));

	for (int i = 0; i < MAX_COMPANY; i++)
	{
		if (ifGood[i] == true)
		{
			if ((rand() % 2) == 0)
			{
				StockPrice[i] += (rand() % 1000);
			}
			else
			{
				StockPrice[i] -= (rand() % 100);
			}
		}
		else
		{
			if ((rand() % 2) == 0)
			{
				StockPrice[i] += (rand() % 500);
			}
			else
			{
				StockPrice[i] -= (rand() % 1000);
			}
		}
		if (StockPrice[i] < 2000) StockPrice[i] = 2000;
		StockPrice[i] = StockPrice[i] / 10 * 10;
	}
}

void ShowStockPrice(int mode)
{
	if (mode == 0)
	{
		for (int i = 0; i < MAX_COMPANY; i++)
		{
			PrintStockPrice(i);
			companyOrder[i] = i;
		}
		return;
	}

	int order[MAX_COMPANY], tmp;
	for (int i = 0; i < MAX_COMPANY; i++) order[i] = StockPrice[i];

	if (mode == 1)
	{
		for (int i = 0; i < MAX_COMPANY; i++)
		{
			for (int j = 0; j < MAX_COMPANY; j++)
			{
				if (order[i] > order[j])
				{
					tmp = order[i];
					order[i] = order[j];
					order[j] = tmp;
				}
			}
		}
		for (int i = 0; i < MAX_COMPANY; i++)
		{
			for (int j = 0; j < MAX_COMPANY; j++)
			{
				if (order[i] == StockPrice[j])
				{
					PrintStockPrice(j);
					order[i] = 0;
					companyOrder[i] = j;
				}
			}
		}
	}
	if (mode == 2)
	{
		for (int i = 0; i < MAX_COMPANY; i++)
		{
			for (int j = 0; j < MAX_COMPANY; j++)
			{
				if (order[i] < order[j])
				{
					tmp = order[i];
					order[i] = order[j];
					order[j] = tmp;
				}
			}
		}
		for (int i = 0; i < MAX_COMPANY; i++)
		{
			for (int j = 0; j < MAX_COMPANY; j++)
			{
				if (order[i] == StockPrice[j])
				{
					PrintStockPrice(j);
					order[i] = 0;
					companyOrder[i] = j;
				}
			}
		}
	}
}

void PrintStockPrice(int i)
{
	printf(" ȸ�� : ");
	if (ifGood[i])
	{
		textcolor(10);
		printf("%-20s", CompanyName[i]);
		textcolor(7);
	}
	else 
	{
		textcolor(12);
		printf("%-20s", CompanyName[i]);
		textcolor(7);
	}
	printf(" �� ���� : %5d��  ", StockPrice[i]);
	if (PrevStockPrice[i] < StockPrice[i])
	{
		textcolor(2);
		printf("��%4d�� ", StockPrice[i] - PrevStockPrice[i]);
		textcolor(7);
	}
	else if (PrevStockPrice[i] > StockPrice[i])
	{
		textcolor(14);
		printf("��%4d�� ", -1 * (StockPrice[i] - PrevStockPrice[i]));
		textcolor(7);
	}
	printf("\n");
}

void loan(int lmoney)
{
	loanMoney += lmoney;
	Money += lmoney;
}

void interest()
{
	loanMoney += (int)(loanMoney * 0.05);
}

void payback()
{
	Money -= loanMoney;
	loanMoney = 0;
}

/** Buy stocks and insert into the stock linked list to save user's stocks
* �ֽ��� ��� ������ �ֽĵ��� �����ϱ� ���� �ֽ� ���Ḯ��Ʈ�� �����մϴ�
*
* @param order
* Company number to identify companies
*
* @param amount
* Amount of stocks
*
* @return void
*/
void BuyStock(int order, int amount)
{
	Stock temp;

	/* ������ �� �ֽ� ������ŭ �ݺ��մϴ�											*/
	/* ������ ����� �ֽ� ���ݺ��� ũ�� �ֽ��� �ϳ��� �缭 ���Ḯ��Ʈ�� �߰��մϴ�	*/
	/* ������ ���� �ֽ� ���ݺ��� ������ ���� �ʽ��ϴ�								*/
	for (int i = 0; i < amount; i++)
	{
		if (StockPrice[order] <= Money)
		{
			system("cls");
			now = head;

			temp.company = order;
			temp.price = StockPrice[order];
			now = InsertStock(now, &temp);
			
			Stocks++;
			StockDeal++; 
			printf(" %d���� �ְ� ��° �ֽ��� �����Ͽ����ϴ�. �ֽ��� %d���Դϴ�.\n"
				, StockPrice[order], Stocks);
			Money -= StockPrice[order];
			printf(" ���� ���� %d���Դϴ�.\n", Money);
		}
		else
		{
			printf(" ���� �����մϴ�. �ֽ��� �� �� �����ϴ�.\n");
		}
	}
}

void sellStock(int i)
{
	Stock *f = FindStock(i - 1);
	if (f == NULL) return;
	
	Money += (StockPrice[f->company]);
	DeleteStock(f);
	
}

/** Show list of stocks that user has
*
* @return void
*/
void ShowStockList(void)
{
	int numberOfStocks;
	int listPage; /* �� ������ �� 10���� �ֽ��� ����մϴ�. */
	char key = '\0';

	system("cls");

	listPage = 1;
	if (Stocks <= 0) 
	{
		printf("\n �ֽ��� �����ϴ�.\n");
		Sleep(600);
	}
	else
	{
		/* ������ A, D, Q Ű�� �Է��մϴ�				*/
		/* �ֽ��� �� ������ �� 10�� �� ����մϴ�		*/
		/* AŰ�� �Է��ϸ� ���� �������� ����մϴ�		*/
		/* DŰ�� �Է��ϸ� ���� �������� ����մϴ�		*/
		/* QŰ�� �Է��ϸ� �� �ݺ����� �����մϴ�		*/
		while (key != 'Q' || key != 'q')
		{
			system("cls");
			titleLine("�ֽ� ��� ����");

			printf("\n [ A, D�� �� ���� �� �ֽ��ϴ�. ]\n\n");

			numberOfStocks = 1;
			/* �ֽ� ���Ḯ��Ʈ�� ��ȸ�ϸ鼭 ������ �ִ� ȸ�� �ֽ� ������ ����մϴ� */
			for (now = head->next; now != NULL; now = now->next)
			{
				/* �ֽ��� �� ������ �� 10���� ����մϴ�. */
				if (numberOfStocks >= listPage && numberOfStocks < listPage + 10) 
					printf("\n %d. ȸ�� : %-20s, ���� : %d��", numberOfStocks, CompanyName[now->company], now->price);

				numberOfStocks++;
			}
			printf("\n ���ư����� Q�� ��������.\n");

			key = getch();
			if (key == 'D' || key == 'd')
			{
				listPage += 10;
			}
			else if (key == 'A' || key == 'a')
			{
				if (listPage > 10)
					listPage -= 10;
			}
		}
	}
	system("cls");
}

void UpdateGraphData()
{
	for (int i = 0; i < MAX_COMPANY; i++)
	{
		for (int j = 46; j >= 0; j--)
		{
			GraphData[i][j + 1] = GraphData[i][j];
		}
		GraphData[i][0] = StockPrice[i];
	}
}
