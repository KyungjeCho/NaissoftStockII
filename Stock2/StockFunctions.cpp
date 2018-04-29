#include <stdio.h>
#include <time.h>
#include <conio.h>
#include <stdlib.h>
#include <Windows.h>

#include "StockFunctions.h"
#include "Stock.h"

unsigned long Money;
int StockPrice[MAX_COMPANY], prevStockPrice[MAX_COMPANY], StockDeal, loanMoney, companyOrder[MAX_COMPANY];
int Stocks;
int GraphData[MAX_COMPANY][48] = { 0 };
bool ifGood[MAX_COMPANY];

char *CompanyName[MAX_COMPANY] =
{
	"Naissoft",
	"HawTech",
	"암겨농업",
	"MK Electronics",
	"폭펭군수",
	"CJ 제일손연재",
	"KJS 시스템",
	"Fruit",
	"수배자 모터스",
	"기야조선",
};

/** Change each company's stock price 
* 만약 회사 상황이 좋다면 (ifGood) 50% 확률로 0 ~ 1000 원 증가합니다
* 아니면 50% 확률로 0 ~ 100원 감소합니다.
* 만약 회사 상황이 안좋다면 (ifBad) 50% 확률로 0 ~ 500 원 증가합니다
* 아니면 50% 확률로 0 ~ 1000원 감소합니다.
*
* @return void
*/
void ChangeStockPrice(void)
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
		if (StockPrice[i] < 2000) /* 각 회사의 주식 가격은 2000이하로 안 떨어집니다 */
			StockPrice[i] = 2000;

		StockPrice[i] = StockPrice[i] / 10 * 10; /* 가격의 일자리 수는 내림 합니다 */
	}
}

/** Draw stock price on console middle 
*
* @param mode
* Mode is view mode
* 만약 모드가 0이면 게임에서 설정한 순서로 주식 가격을 출력합니다
* 만약 모드가 1이면 오름차순으로 정렬하여 주식 가격을 출력합니다
* 만약 모드가 2이면 내림차순으로 정렬하여 주식 가격을 출력합니다
*
* @return void
*/
void ShowStockPrice(int mode)
{
	int order[MAX_COMPANY];
	int temp;

	if (mode == 0)
	{
		for (int i = 0; i < MAX_COMPANY; i++)
		{
			PrintStockPrice(i);
			companyOrder[i] = i; //what is this?
		}
		return;
	}

	for (int i = 0; i < MAX_COMPANY; i++) 
		order[i] = StockPrice[i];

	if (mode == 1)
	{
		/* Sort in ascending order */
		for (int i = 0; i < MAX_COMPANY; i++)
		{
			for (int j = 0; j < MAX_COMPANY; j++)
			{
				if (order[i] > order[j])
				{
					temp = order[i];
					order[i] = order[j];
					order[j] = temp;
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
		/* Sort in descending order */
		for (int i = 0; i < MAX_COMPANY; i++)
		{
			for (int j = 0; j < MAX_COMPANY; j++)
			{
				if (order[i] < order[j])
				{
					temp = order[i];
					order[i] = order[j];
					order[j] = temp;
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

/** 회사 주식을 출력합니다
* 현재 가격과 현재 가격과 이전 가격 차이를 출력합니다
*
* @param indexOfCompany
* Index of company's array
*
* @return void
*/
void PrintStockPrice(int indexOfCompany)
{
	int diffOfPrice;

	printf(" 회사 : ");
	if (ifGood[indexOfCompany])
	{
		textcolor(10);
		printf("%-20s", CompanyName[indexOfCompany]);
		textcolor(7);
	}
	else 
	{
		textcolor(12);
		printf("%-20s", CompanyName[indexOfCompany]);
		textcolor(7);
	}
	printf(" │ 가격 : %5d원  ", StockPrice[indexOfCompany]);

	diffOfPrice = StockPrice[indexOfCompany] - prevStockPrice[indexOfCompany];
	if (diffOfPrice >= 0)
	{
		textcolor(2);
		printf("▲%4d원 ", diffOfPrice);
		textcolor(7);
	}
	else
	{
		textcolor(14);
		printf("▼%4d원 ", -1 * diffOfPrice);
		textcolor(7);
	}
	printf("\n");
}

/** 대출합니다
*
* @param lmoney
* loan money
*
* @return void
*/
void Loan(int lmoney)
{
	loanMoney += lmoney;
	Money += lmoney;
}

/** 상환 금액이 이자만큼 증가합니다
* 이자는 5%입니다
*
* @return void
*/
void Interest(void)
{
	loanMoney += (int)(loanMoney * 0.05);
}

/** 대출을 상환합니다
*
* @return void
*/
void Payback()
{
	if (Money >= loanMoney)
	{
		Money -= loanMoney;
		loanMoney = 0;
	}
}

/** Buy stocks and insert into the stock linked list to save user's stocks
* 주식을 사고 유저의 주식들을 저장하기 위해 주식 연결리스트에 저장합니다
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

	/* 유저가 산 주식 개수만큼 반복합니다											*/
	/* 유저의 재산이 주식 가격보다 크면 주식을 하나씩 사서 연결리스트에 추가합니다	*/
	/* 유저의 돈이 주식 가격보다 적으면 사지 않습니다								*/
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
			printf(" %d원을 주고 번째 주식을 구입하였습니다. 주식이 %d개입니다.\n"
				, StockPrice[order], Stocks);
			Money -= StockPrice[order];
			printf(" 남은 돈은 %d원입니다.\n", Money);
		}
		else
		{
			printf(" 돈이 부족합니다. 주식을 살 수 없습니다.\n");
		}
	}
}

/** Sell a stock and delete it on list
*
* @param indexOfStock
* index of the list of stocks the user wants to sell 
*
* @return void
*/
void SellStock(int indexOfStock)
{
	Stock *saleStock = FindStock(indexOfStock - 1);
	if (saleStock == NULL) 
		return;
	
	Money += (StockPrice[saleStock->company]);
	DeleteStock(saleStock);	
}

/** Show list of stocks that user has
*
* @return void
*/
void ShowStockList(void)
{
	int numberOfStocks;
	int listPage; /* 한 페이지 당 10개의 주식을 출력합니다. */
	char key = '\0';

	system("cls");

	listPage = 1;
	if (Stocks <= 0) 
	{
		printf("\n 주식이 없습니다.\n");
		Sleep(600);
	}
	else
	{
		/* 유저는 A, D, Q 키를 입력합니다				*/
		/* 주식은 한 페이지 당 10개 씩 출력합니다		*/
		/* A키를 입력하면 이전 페이지를 출력합니다		*/
		/* D키를 입력하면 다음 페이지를 출력합니다		*/
		/* Q키를 입력하면 이 반복문을 중지합니다		*/
		while (key != 'Q' || key != 'q')
		{
			system("cls");
			titleLine("주식 목록 보기");

			printf("\n [ A, D로 더 보실 수 있습니다. ]\n\n");

			numberOfStocks = 1;
			/* 주식 연결리스트를 순회하면서 가지고 있는 회사 주식 가격을 출력합니다 */
			for (now = head->next; now != NULL; now = now->next)
			{
				/* 주식을 한 페이지 당 10개씩 출력합니다. */
				if (numberOfStocks >= listPage && numberOfStocks < listPage + 10) 
					printf("\n %d. 회사 : %-20s, 가격 : %d원", numberOfStocks, CompanyName[now->company], now->price);

				numberOfStocks++;
			}
			printf("\n 돌아가려면 Q를 누르세요.\n");

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

/** 주식 그래프의 데이터를 업데이트합니다
* 
* @return void
*/
void UpdateGraphData(void)
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
