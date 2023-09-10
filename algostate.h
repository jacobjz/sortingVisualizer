typedef enum {
	def,
	initialized,
	idle,
	shuffled,
	sorting,
	sorted,
	finished
}AlgorythmState;


void bubbleSort(void);
void shuffleArray(void);
typedef void (*FunctionPtr)(void);
FunctionPtr functionPointerArray[] = {bubbleSort, shuffleArray};
