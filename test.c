//Define the record
typedef struct {
	double searchKey; 
	int size;		//slots used so far
	int capacity; 	//total slotes 
	long *data;  	//array of timestamps
} Record;