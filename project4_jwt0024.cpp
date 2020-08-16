/*
   Name: Jared Thacker
   AU User ID: jwt0024
   File Name: project4_jwt0024.cpp
   Compilation instructions: g++ project4_jwt0024.cpp -o a.out
   help: found out about cin.clear and cin.ignore via stack exchange
         while( !(cin >> points) || points <= 0) I also used this code from stack exchange
*/

#include <iostream>
#include <cstdlib>
#include <string>
#include <cassert>
using namespace std;

//Define and intialize the total trivia points as a global
int PointsTot = 0;

//Define the TriviaNode structure
struct TriviaNode{

   string question;
   string answer;
   int points;
   TriviaNode* next;
      TriviaNode(string theQuestion,string theAnswer,int thePoints,TriviaNode* link) //constructor for the TriviaNode structure
         {this->question = theQuestion; 
          this->answer = theAnswer;
          this->points = thePoints;
          this->next = link;}
};

//Define the TriviaNode type definition and all the prototypes needed for this program
typedef TriviaNode* ptr_node;
ptr_node makeTriviaList(ptr_node current);
ptr_node hardCodedTrivia();
ptr_node addNewTriviaNode(string theQuestion,string theAnswer,int thePoints,ptr_node& theNext);
ptr_node customQuiz(ptr_node& head,string userAnswer);
int countTriviaQuestions(ptr_node& triviaList);
int triviaHost(ptr_node myList,int numberOfQuestions);
void test_TriviaHost() ;
void test_hardCodedTrivia();
void test_addNewTriviaNode();
void test_makeTriviaList();
void test_countTriviaQuestions();
void test_customQuiz();

//The define statement needed for maintaining the 2 versions
//#define UNIT_TESTING

int main(){
   int j;
   string inputAnswer;

   #ifdef UNIT_TESTING //The first version is the debugging version
      cout << "*** This is a debugging version ***" << endl;
      test_TriviaHost(); //The unit testing procedure as specified by the syllabus

/*//Uncomment for additional testing
      test_hardCodedTrivia();
      test_addNewTriviaNode();
      test_makeTriviaList();
      test_countTriviaQuestions();
      test_customQuiz();
*/

      cout << "*** End of the debugging version ***" << endl;
   #else //The second version is the production version
      cout << "*** Welcome to Jared's trivia quiz game ***" << endl; 
      cout << "Would you like to construct your own list of trivia questions? (Yes/No): ";
      getline(cin,inputAnswer);
      ptr_node head = NULL; 
      while(inputAnswer != "Yes" && inputAnswer != "No"){
         cout << "Please enter Yes (for yes)or No (for no): ";
         getline(cin,inputAnswer); 
      }
      if(inputAnswer == "Yes"){
         head = customQuiz(head,inputAnswer);
      } 
      else{
         head = hardCodedTrivia(); 
      }
      int n = countTriviaQuestions(head);
      cout << endl;
      j = triviaHost(head,n); 
      cout << "*** Thank you for playing the trivia quiz game. Good bye! ***" << endl;
   #endif
   return 0;

}
/*
   Function: makeTriviaList
   Inputs: current - the linked list structure that will be the trivia list in main()
   Outputs: head - the updated linked list structure that will be the trivia list in main()
*/
ptr_node makeTriviaList(ptr_node current){

   ptr_node head = current;
   string quest;
   string ans;
   int points;
   cout << "Enter your question: ";
   getline(cin,quest); //User inputs their question
   cout << "Enter the answer: ";
   getline(cin,ans); //User inputs their answer
   cout << "Enter the number of points the question is worth (an integer greater than 0): ";
   while( !(cin >> points) || points <= 0){ //While points is less than 1, prompt the use that points must be greater than 0
      cout << "The number of points must be a number greater than 0: ";
      cin.clear();
      cin.ignore(10000, '\n'); //clear the input buffer
   }
      cin.clear();
      cin.ignore(10000, '\n'); //clear the input buffer
   head = addNewTriviaNode(quest,ans,points,head);
   return head;
}

/*
   Function: addNewTriviaNode
   Inputs: theQuestion - the trivia question to be asked
           theAnswer - the trivia answer to the trivia question
           thePoints - the number of points the question is worth
           theNext - the link to the next TriviaNode in the list
   Outputs:theNext - the link to the first node in the list of trivia questions 
*/
ptr_node addNewTriviaNode(string theQuestion,string theAnswer,int thePoints,ptr_node& theNext){
      ptr_node location;
      ptr_node newNode = new TriviaNode(theQuestion,theAnswer,thePoints,NULL);
      location = theNext;
      if(theNext == NULL){
         theNext = newNode;
         return theNext;
      }
      //Add the a node to the end of the list, this enables the user to add questions in order
      while( location->next != NULL){
         location = location->next;
      }
      location->next = newNode;
      return theNext;
}

/*
   Function: hardCodedTrivia
   Inputs: None
   Outputs: The linked list of TriviaNode structures of hard-coded trivia question
*/
ptr_node hardCodedTrivia(){

   ptr_node head = NULL;
   string myQuestion,myAnswer;
   int myPoints;

   //hard-code the first trivia question into the default trivia game
   myQuestion = "How long was the shortest war on record? (Hint: how many minutes)";
   myAnswer = "38";
   myPoints = 100;
   head = addNewTriviaNode(myQuestion,myAnswer,myPoints,head);

   //Hard-code the second trivia question into the default trivia game
   myQuestion = "What was Bank of America's original name? (Hint: Bank of Italy or Bank of Germany)"; 
   myAnswer = "Bank of Italy";
   myPoints = 50;
   head = addNewTriviaNode(myQuestion,myAnswer,myPoints,head);

   //Hard-code the third trivia question into the default trivia game
   myQuestion = "What is the best-selling video game of all time? (Hint: Call of Duty or Wii Sports)";
   myAnswer = "Wii Sports";
   myPoints = 20;
   head = addNewTriviaNode(myQuestion,myAnswer,myPoints,head);

   return head;

}

/*
   Function: triviaHost
   Inputs: myList - The completed linked list of trivia questions 
   Outputs: 1 or 0 for failure or success respectively
*/
int triviaHost(ptr_node myList,int numberOfQuestions){
   ptr_node nextLink,head = myList;
   int n,i=0;
   string ans;
   n = countTriviaQuestions(head); //count the number of questions in the linked list

   if(head == NULL){
      cout << "Warning: The trivia list is empty" << endl;
      return 1;
   }else if(numberOfQuestions <= 0){
      cout << "Warning: The number of of trivia questions must be equal to or be larger than 1" << endl;
      return 1;
   }else if(n < numberOfQuestions){
         cout << "Warning: There's only "<< n <<" questions in the list." << endl;
         return 1;
   }else{
         nextLink = head; //set nextLink equal to head (which is initialized to myList at this point)
         for(i = 0; i < numberOfQuestions; i++){
            cout << "Question: " << nextLink->question << endl;
            cout << "Answer: ";
            getline(cin,ans);
            if(ans == nextLink->answer){ //if the correct answer is given
               cout << "The answer you gave is correct. You are awarded: " << nextLink->points << " points." << endl;
               PointsTot += nextLink->points; //award the necessary points
            }else{
               cout << "The answer you gave is incorrect. The answer was: " << nextLink->answer << endl; //otherwise, display the correct answer 
            }
            cout << "Total Points: " << PointsTot << endl;
            cout << endl;
            nextLink = nextLink->next; //move up a node in the linked list
         }
   return 0;
      
      }

   }

/*
   Function: countTriviaQuestions()
   Inputs: triviaList - the trivia list that you want to count the number of questions
   Outputs: i - the number of questions in the trivia linked list
*/
int countTriviaQuestions(ptr_node& triviaList){
   ptr_node location = triviaList;
   int i = 0;
   while(location != NULL){ //While the location node points to another node, increase the number of questions by 1
      location = location->next;
      i++;
   }
   return i;
}

/*
   Function: customQuiz
   Inputs: head - NULL linked list
           userAnswer - A binary string of "Yes" or "No" that indicates whether the user wants to add another question
   Outputs: head - the linked list of trivia questions 
*/
ptr_node customQuiz(ptr_node& head,string userAnswer){

         string userAnsTmp = userAnswer;

         while(userAnsTmp == "Yes"){ //While the user answers "Yes" add a new question
            head = makeTriviaList(head);
            cout << "Woud you like to add another question? (Yes/No): ";
            getline(cin,userAnsTmp);
            while(userAnsTmp != "Yes" && userAnsTmp != "No"){ //While the user doesn't enter "Yes" or "No", prompt user
               cout << "Please enter Yes (for yes)or No (for no): ";
               getline(cin,userAnsTmp); 
            }
         }
         return head; 
}

/*
   Function: test_triviaHost()
   Inputs: None
   Outputs: None (runs a test-driver)
*/
void test_TriviaHost() {

   ptr_node myTriviaList = hardCodedTrivia();
   int returnValue;

   //Unit Case 1: Ask no questions. The program should display a warning message.
   cout << "Unit Test Case 1: Ask no question. The program should display a warning message." << endl;
   returnValue = triviaHost(myTriviaList,0);
   assert(1 == returnValue);   
   cout << endl;
   cout << "Unit Test Case 1: Passed" << endl;
   cout << endl;

   //Unit Test Case 2.1: Ask 1 question in the linked list. The tester enters an incorrect answer.
   cout << "Unit Test Case 2.1: Ask 1 question in the linked list. The tester enters an incorrect answer." << endl;;
   returnValue = triviaHost(myTriviaList,1);
   assert(0 == returnValue && PointsTot == 0);
   cout << "Unit Test Case 2.1: Passed" << endl;
   cout << endl;

   //Unit Test Case 2.2: Ask 1 question in the linked list. The tester enters a correct answer.
   cout << "Unit Test Case 2.2: Ask 1 question in the linked list. The tester enters a correct answer." << endl;
   returnValue = triviaHost(myTriviaList,1);
   assert(0 == returnValue && PointsTot == 100);
   cout << "Unit Test Case 2.2: Passed" << endl;
   cout << endl;

   PointsTot = 0;
   //Unit Test Case 3.1: Ask all the questions in the linked list. The tester gives all correct answers.
   cout << "Unit Test Case 3.1: Ask all the questions in the linked list. The tester gives all correct answers." << endl;
   returnValue = triviaHost(myTriviaList,3);
   assert(0 == returnValue && PointsTot == 170);
   cout << "Unit Test Case 3.1: Passed" << endl;
   cout << endl;

   PointsTot = 0;
   //Unit Test Case 3.2: Ask all the question in the linked list. The tester gives all incorrect answers.
   cout << "Unit Test Case 3.2: Ask all the question in the linked list. The tester gives all incorrect answers." << endl;
   returnValue = triviaHost(myTriviaList,3);
   assert(0 == returnValue && PointsTot == 0);
   cout << "Unit Test Case 3.2: Passed." << endl;
   cout << endl;

   //Unit Test Case 4.1: Ask 5 questions that exceed the number of available trivia in the linked list
   cout << "Unit Test Case 4.1: Ask 5 questions that exceed the number of availabe trivia in the linked list" << endl;
   returnValue = triviaHost(myTriviaList,5);
   assert(1 == returnValue);
   cout << endl;
   cout << "Unit Test Case 4.1: Passed." << endl;
   cout << endl;
   

   //Unit Test Case 4.2: Ask 5 questions given a NULL linked list.
   cout << "Unit Test Case 4.2: Ask 5 questions given a NULL linked list." << endl;
   myTriviaList = NULL;
   returnValue = triviaHost(myTriviaList,5);
   assert(1 == returnValue);
   cout << endl;
   cout << "Unit Test Case 4.2: Passed." << endl;
   cout << endl;

}

/*
   Function: test_hardCodedTrivia()
   Inputs: None
   Outputs: None (runs a unit test-driver)
*/
void test_hardCodedTrivia(){

   cout << endl;
   cout << "*** Unit Testing for hardCodedTrivia() *** " << endl;
   cout << endl;

   //Unit Test Case 1: Verify question 1
   ptr_node myTriviaList = hardCodedTrivia();
   assert("How long was the shortest war on record? (Hint: how many minutes)" == myTriviaList->question);
   assert("38" == myTriviaList->answer);
   assert(100 == myTriviaList->points);
   cout << "Unit Test Case 1: Passed" << endl;

   //Unit Tst Case 2: Verify question 2
   myTriviaList = myTriviaList->next;
   assert("What was Bank of America's original name? (Hint: Bank of Italy or Bank of Germany)" == myTriviaList->question); 
   assert("Bank of Italy" == myTriviaList->answer);
   assert(50 == myTriviaList->points);
   cout << "Unit Test Case 2: Passed" << endl;
   
   //Unit Test Case 1: Verify question 3
   myTriviaList = myTriviaList->next;
   assert("What is the best-selling video game of all time? (Hint: Call of Duty or Wii Sports)" == myTriviaList->question);
   assert("Wii Sports" == myTriviaList->answer);   
   assert(20 == myTriviaList->points);
   cout << "Unit Test Case 3: Passed." << endl; 
   cout << endl;

}

/*
   Function: test_addNewTriviaNode()
   Inputs: None
   Outputs: None
*/
void test_addNewTriviaNode(){

   ptr_node nextLink;   

   cout << "*** Unit Testing for addNewTriviaNode() ***" << endl;
   cout << endl;

   //Unit Test Case 1: Add 1st question, verify first question.
   ptr_node myTriviaList = NULL;
   myTriviaList = addNewTriviaNode("Who am I?","Jared",10,myTriviaList);
   assert("Who am I?" == myTriviaList->question && "Jared" == myTriviaList->answer && 10 == myTriviaList->points && NULL == myTriviaList->next);
   cout << "Unit Test Cae 1: Passed." << endl;

   //Unit Test Case 2: Add 2nd question, verify correct order.
   myTriviaList = addNewTriviaNode("Who is the greatest TA?","The TA grading this project.",100,myTriviaList);
   assert("Who am I?" == myTriviaList->question && "Jared" == myTriviaList->answer && 10 == myTriviaList->points);
   myTriviaList = myTriviaList->next;   
   assert("Who is the greatest TA?" == myTriviaList->question && "The TA grading this project." == myTriviaList->answer && 100 == myTriviaList->points && NULL == myTriviaList->next);
   cout << "Unit Test Case 2: Passed." << endl;
   cout << endl;

}

/*
   Function: test_makeTriviaList()
   Inputs: None
   Outputs: None (runs a test-driver)
*/
void test_makeTriviaList(){

   //Unit Testing for makeTriviaList
   //Verify function takes user input and stores the input
   //into the appropriate memebers of our TriviaNode struct.
   //Multiple nodes will not be tested: that is 
   //makeNewTriviaNode()'s job.
   cout << "*** Unit Testing for makeTriviaList(): Enter a question and verify. ***" << endl;
   cout << endl;
   cout << "Use Question: What class is this?" << endl;
   cout << "Use Answer: COMP 2710." << endl;
   cout << "Use Points: 100." << endl; 
   ptr_node myTriviaList = NULL;   
   myTriviaList = makeTriviaList(myTriviaList);
   assert("What class is this?" == myTriviaList->question);
   assert("COMP 2710" == myTriviaList->answer);
   assert(100 == myTriviaList->points);
   assert(NULL == myTriviaList->next);
   cout << "Unit Testing for makeTriviaList(): Passed." << endl;
   cout << endl;
}

/*
   Function: test_countTriviaQuestions()
   Inputs: none
   Outputs: none (runs a test-driver)
*/
void test_countTriviaQuestions(){

   cout << "*** Unit Testing for countTriviaQuestions() ***" << endl;
   cout << endl;
   //Unit Test Case 1: Empy list.
   cout << "Unit Test Case 1: Empty list." << endl;
   ptr_node myTriviaList = NULL;
   int  n = countTriviaQuestions(myTriviaList);
   assert(0 == n);
   cout << "Unit Test Case 1: Passed." << endl;

   //Unit Test Case 2: Non-empty list.
   cout << "Unit Test Case 2: Non-empty list." << endl;
   myTriviaList = hardCodedTrivia();
   n = countTriviaQuestions(myTriviaList);
   assert(3 == n);
   cout << "Unit Test Case 2: Passed." << endl;
   cout << endl;

}

/*
   Function: test_customQuiz()
   Inputs: None
   Outputs: None (runs a unit test-driver)
*/
void test_customQuiz(){

   string input = "Yes";
   ptr_node headRef = NULL;
   cout << "*** Unit testing for customQuiz() ***" << endl;
   cout << endl;
   //Unit Test Case 1: The tester enters 1 question, verify correct questions, answer, points, etc.
   cout << "Unit Test Case 1: Tester enters 1 question.Use the following for question, answer, and points respectively: 'Who is the author?', 'Jared','10' " << endl;
   headRef = customQuiz(headRef,input);
   assert(headRef->question == "Who is the author?");
   assert(headRef->answer == "Jared");
   assert(headRef->points == 10);
   cout << endl;
   cout << "Unit Test Case 1: Passed." << endl;
   cout << endl;

   headRef = NULL; 
   input = "Yes";
   //Unit Test Case 2: The tester enters two question, verify correct questions, answers, points, etc
   cout << "Unit Test Case 2: Tester enters two questions. " << endl;
   cout << "For the questions: 'Who is the author?', 'Who is the professor?' " << endl;
   cout << "For the answers, respectively: 'Jared','Dr. Li'" << endl;
   cout << "For the points, respetivley: '10', '20'" << endl;
   headRef = customQuiz(headRef,input);
   assert(headRef->question == "Who is the author?");
   assert(headRef->answer == "Jared");
   assert(headRef->points == 10);
   headRef = headRef->next;
   assert(headRef->question == "Who is the professor?");
   assert(headRef->answer == "Dr. Li");
   assert(headRef->points == 20);
   cout << endl;
   cout << "Unit Test Case 2: Passed." << endl;
   cout << endl;


}
