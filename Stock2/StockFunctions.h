#include "Arts.h"

#define DEF_STOCK 9000
#define DEF_MONEY 500000
#define MAX_COMPANY 10

extern int companyOrder[MAX_COMPANY];
extern int GraphData[MAX_COMPANY][48];

void ChangeStockPrice();

void ShowStockPrice(int);

void PrintStockPrice(int);

void loan(int);

void interest();

void payback();

void BuyStock(int order, int amount);

void sellStock(int);

void ShowStockList(void);

void UpdateGraphData();