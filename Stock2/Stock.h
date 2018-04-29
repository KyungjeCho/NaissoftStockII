
struct Stock
{
	int price;
	int company;
	bool ifChecked;
	
	Stock *prev;
	Stock *next;
};

extern Stock *head, *now, tmp;

void InitStock();

Stock *InsertStock(Stock *pTarget, Stock *aStock);

bool DeleteStock(Stock *Target);

void AppendStock(Stock);

Stock *FindStock(int);

void DeallocateStock();
