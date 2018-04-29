#include "Arts.h"

#define DEF_STOCK 9000
#define DEF_MONEY 50000
#define MAX_COMPANY 10

extern int companyOrder[MAX_COMPANY];
extern int GraphData[MAX_COMPANY][48];

void ChangeStockPrice(void);

void ShowStockPrice(int);

void PrintStockPrice(int);

void Loan(int);

void Interest(void);

void Payback();

void BuyStock(int order, int amount);

void SellStock(int);

void ShowStockList(void);

void UpdateGraphData(void);