/**
* Bernard Moussad
* Brm0029
* hw5_brm0029.cpp
* g++ hw5_brm0029.cpp
* Uncomment line 30 in order to enable UNIT_TESTING
* I researched how to implement pointers as nodes 
* I researched how to make stings lowercase in order to compare them correctly
* I researched how to perform unit testing using macros
*/
#include <iostream>
#include <string>
#include <assert.h>
using namespace std;


struct TriviaNode
{
	string question;
	string answer;
	int	points;
	TriviaNode* next;
};

int addQuestion(string question, string answer, int points, TriviaNode* &head, TriviaNode* &tail);
void initialTrivia(TriviaNode* &head, TriviaNode* &tail);
int askQuestion(TriviaNode* &head, int numToAsk);
void test_askQuestion(void);

// #define UNIT_TESTING
#ifdef	UNIT_TESTING

int main() {
	test_askQuestion();
}

#else
// This is the main driver.
// The user is able to add questions, answers, and points to a trivia list.
// They are then asked questions from a hardcoded trivia list and given points
// based on if they get the answers right or wrong.

int main() {
	TriviaNode* trivia = NULL;
	TriviaNode* tail = NULL;
	TriviaNode* ptrivia = NULL;
	TriviaNode* ptail = NULL;
	initialTrivia(trivia,tail);
	string player = "Bernie";
	cout<<"* * * Welcome to "<<player<<"'s trivia quiz game * * *"<<endl;
	string response;
	string question;
	string answer;
	int points;	

	do {
		cout<<"Enter a question: ";
		cin.ignore();
		getline(cin,question);
		cout<<"Enter an answer: ";
		cin.ignore();
		getline(cin,answer);
		cout<<"Enter award points: ";
		cin>>points;
		addQuestion(question, answer, points, ptrivia, ptail);
		cout<<"Continue? (Yes/No): ";
		cin.ignore();
		getline(cin,response);
		transform(response.begin(), response.end(), response.begin(), ::tolower);
	} while(response.compare("yes") == 0);
	 cout<<"\n";	
	 askQuestion(trivia, 3);
	 cout<<"\n*** Thank you for playing the trivia quiz game. Goodbye! ***";
	 delete trivia;
	 delete tail;
	 delete ptrivia;
	 delete ptail;	
}
#endif

// addQuestion takes the inputs of a question, answer, points, the head of a TriviaNode, and tail of TriviaNode.
// It creates a new TriviaNode and assigns the corresponding values to the appropriate fields.
// Then it checks to see if the passed in head points to NULL.
// If yes, then the new question gets pointed to by head and tail.
// If no, then the question gets appended to the trivia list.
int addQuestion(string question, string answer, int points, TriviaNode* &head, TriviaNode* &tail) {
	TriviaNode* q1 = new TriviaNode;
	if (q1 == NULL) {
		cout<<"ERROR: TriviaNode not created"<<endl;
		return -1;
	}
	q1->question = question;
	q1->answer = answer;
	q1->points = points;

	
	if (head == NULL) {	
		head = q1;
		tail = q1;		
	}
	else {
		tail->next = q1;
		tail = q1;
	}
	return 0;
}

// askQuestion takes the inputs of a trivia list and a number of questions to ask.
// It iterates through the trivia list based on the input of numToAsk. 
// It asks the question it currently is accessing, then compares the user's input to the answer.
// If they match, the user is awarded the corresponding points.
// Otherwise, they are told the correct answer and not awarded points.
// If numToask is less than 1 or greater than the length of the trivia list, 
// an error is thrown.
int askQuestion(TriviaNode* &head, int numToAsk) {
	
	if (numToAsk < 1) {
		cout<<"Warning - The number of trivia to be asked must be equal to or larger than 1.\n"<<endl;
		return 1;
	}
	if (numToAsk > 3) {
		cout<<"Warning - The are only three trivia in the list.\n"<<endl;
		return 1;
	}

	TriviaNode* access = new TriviaNode;
	string answer;
	access = head;
	
	int playerPoints = 0;
	for(int start = 0; access != NULL && start < numToAsk; access = access->next, start++) {
		cout<<"Question: "<<access->question<<endl;
		cout<<"Answer: ";
		getline(cin, answer);

		if ((access->answer).compare((answer)) == 0) {
			cout<<"Your answer is correct. You receive: "<<access->points<<" points"<<endl;
			playerPoints += access->points;
		}

		else {
			cout<<"Your answer is wrong. The correct answer is: "<<access->answer<<endl;
		}

		cout<<"Your total points is: "<<playerPoints<<"\n"<<endl;
	}
	return 0;
}

// initialTrivia takes the inputs of an trivia list's head and tail.
// It adds 3 hardcoded questions to the trivia list using the addQuestion 
// function. 
void initialTrivia(TriviaNode* &head, TriviaNode* &tail) {
	addQuestion("How long was the shortest war on record? (Hint: how many minutes)", "38", 100, head, tail);
	addQuestion("What was Bank of America's original name? (Hint: Bank of Italy or Bank of Germany)", "Bank of Italy", 50, head, tail);
	addQuestion("What is the best-selling video game of all time? (Hint: Minecraft or Tetris)", "Tetris", 20, head, tail);
}

//	This driver tests the functionality of the askQuestion method.
void test_askQuestion(void) {
	TriviaNode* head = NULL;
	TriviaNode* tail = NULL;
	initialTrivia(head, tail);
	cout<<"*** This is a debug version ***"<<endl;
	cout<<"Unit Test Case 1: Ask no questions. The program should give a warning message."<<endl;
	askQuestion(head, 0);
	cout<<"Unit Test Case 2.1: Ask 1 question in the linked list. The tester enters an incorrect answer."<<endl;
	assert(0 == askQuestion(head,1));
	cout<<"Case 2.1 passed..."<<endl;
	cout<<"Unit Test Case 2.2: Ask 1 question in the linked list. The tester enters a correct answer."<<endl;
	assert(0 == askQuestion(head,1));
	cout<<"Case 2.2 passed..."<<endl;
	cout<<"Unit Test Case 3.1: Ask 2 questions in the linked list. The tester enters an incorrect answer."<<endl;
	assert(0 == askQuestion(head,2));
	cout<<"Case 3.1 passed..."<<endl;
	cout<<"Unit Test Case 3.2: Ask 2 questions in the linked list. The tester enters a correct answer."<<endl;
	assert(0 == askQuestion(head,2));
	cout<<"Case 3.2 passed..."<<endl;
	cout<<"Unit Test Case 4.1: Ask 3 questions in the linked list. The tester enters an incorrect answer."<<endl;
	assert(0 == askQuestion(head,3));
	cout<<"Case 4.1 passed..."<<endl;
	cout<<"Unit Test Case 4.2: Ask 3 questions in the linked list. The tester enters a correct answer."<<endl;
	assert(0 == askQuestion(head,3));
	cout<<"Case 4.2 passed..."<<endl;
	cout<<"Unit Test Case 5: Ask five questions in the linked list."<<endl;
	askQuestion(head,5);
	cout<<"\n*** End of the Debug Version ***"<<endl;
}
