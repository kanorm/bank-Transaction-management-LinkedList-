/*=======================================================
                       github repo:              
  https://github.com/kanorm/bank-Transaction-management-LinkedList-  
=========================================================*/

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

bool is_date_format_valid(int);

/*----------  Transaction class  ----------*/

class Transaction{

private:

  int date;
  double amount_of_transaction;
  /*---------- True for settle , False for payable   ----------*/
  bool status;
  double remaining_money_after_transaction;

public:

  Transaction(){};
  Transaction(int date, double amount_of_transaction , bool status ,double remaining_Money ){

    this->date = date ; this->amount_of_transaction = amount_of_transaction ; this->status = status; this->remaining_money_after_transaction = remaining_Money; next = NULL;

  }

  Transaction *next;
  int getDate(){return date;}
  double getAmountOfTransaction(){ return amount_of_transaction;}
  bool getStatus(){return status;}
  double getRemainingMoneyAfterTransaction(){return remaining_money_after_transaction;}

};

/*----------  Transaction methodes defination  ----------*/

/*----------  Customer Class  ----------*/

class Customer{

private:

  string name;
  int oldest_transaction_date;
  int counter;
  double remaining_Money;
  long int customer_number;
  Transaction *Head;
  Transaction *Last;
  void pushBack(Transaction*);
  void ClearTransactions();

public:

  Customer();
  Customer(string,double,long int);
  void set(string,double,long int);
  void pushBack(int,double,bool);
  void printTransactionAfterSpecificDate(int);
  void printSetteledTransaction();
  void printPaidTransaction();
  void updateEssentialsParameter(int , double , bool);
  /*----------  file methods  ----------*/
  void printToTextualFile();
  void readFromTexualFile();
  void printToBinaryFile();
  void readFromBinaryFile();
  /*----------  security methods  ----------*/
  bool is_date_valid(int);
  bool is_amount_of_transaction_valid(int,bool);
  /*----------  testing methods  ----------*/
  void print();

};

/*----------  Customer's methods defination  ----------*/

/**
 * checking date that is entered is valid or not
 * @param  date [description]
 * @return      [description]
 */
bool Customer::is_date_valid(int date){

  if( is_date_format_valid(date) && date >= oldest_transaction_date ) return true;

  return false;
}

/**
 * checking amount of transaction entered is valid or not
 * @param  amount_of_transaction [description]
 * @param  status                [description]
 * @return                       [description]
 */
bool Customer::is_amount_of_transaction_valid(int amount_of_transaction,bool status){

  if( amount_of_transaction < 1 ) return false;

  /* checking amount of transaction based on Status ( True for settle , False for payable )  */
  if ( status ) return true;

  else

    if ( remaining_Money >= amount_of_transaction ) return true;

  return false;
}

Customer::Customer(){

  counter = 0 ; Head = NULL; Last = NULL; name = "No name"; remaining_Money = 0; customer_number = 111111; oldest_transaction_date = 0;

}

/**
 * cunstructor with initializing parameter
 */
Customer::Customer(string name, double remaining_Money , long int customer_number){

  counter = 0 ; this->name = name ; this->remaining_Money = remaining_Money ; this->customer_number = customer_number; oldest_transaction_date = 0; Head = NULL; Last = NULL;

}

void Customer::set(string name , double remaining_Money , long int customer_number){

  this->name = name ; this->remaining_Money = remaining_Money ; this->customer_number = customer_number;

}

/**
 * updating essinsial parameter after every transaction
 * @param date                  [description]
 * @param amount_of_transaction [description]
 * @param status                [description]
 */
void Customer::updateEssentialsParameter(int date , double amount_of_transaction , bool status){

  /* updating oldest date for checking transaction's date */
  if( date > oldest_transaction_date ) oldest_transaction_date = date;

  /* updating Balance based on Status ( True for settle , False for payable )  */
  if(status){

    remaining_Money += amount_of_transaction;

  }else{

    remaining_Money -= amount_of_transaction;

  }

}

/**
 * adding new transaction
 * @param date                  [description]
 * @param amount_of_transaction [description]
 * @param status                [description]
 */
void Customer::pushBack(int date, double amount_of_transaction , bool status ){

  
  if ( is_date_valid(date) && is_amount_of_transaction_valid(amount_of_transaction,status)){

    updateEssentialsParameter(date,amount_of_transaction,status);

    Transaction* new_transaction = new Transaction(date,amount_of_transaction,status,remaining_Money);

    if (Head == NULL) {

        Head = new_transaction;
        Last = new_transaction;
        counter++;
        return;

     }

     Last->next = new_transaction;
     Last = new_transaction;
     counter++;

  }else{

    /* for testing  */
    // cout << amount_of_transaction << " " << remaining_Money << " " << status << " " << date <<endl ;
    // cout << "date " << is_date_format_valid(date) << "  amount " << is_amount_of_transaction_valid(amount_of_transaction,status) << endl ;

     cout << "date or amount of transaction for paying is not vail :|" << endl;

  }

}

/**
 * private method
 * adding new Transaction By reading binary file 
 * @param transaction [description]
 */
void Customer::pushBack(Transaction* transaction){

   if(Head == NULL){

     Head = transaction;
     Last = transaction;
     return;

   }

   Last->next = transaction;
   Last = transaction;

}

/**
 * deleting all transactions
 */
void Customer::ClearTransactions(){

  Transaction* t = Head;
  while ( t != NULL ){

    Transaction* c = t;
    t = t->next;
    delete c;

  }

  Head = NULL;
  Last = NULL;
  counter = 0;
  oldest_transaction_date = 0;

}

/**
 * printing Transaction after specific Date
 * @param date [description]
 */
void Customer::printTransactionAfterSpecificDate(int date){

     int size = 0;

     for(Transaction* c=Head ; c != NULL ; c = c->next)

          if(c->getDate() > date) {

               size++;
               string status = c->getStatus() ? "settle" : "paid";
               cout << c->getDate() <<" " << status << " " << c->getAmountOfTransaction() << " " << c->getRemainingMoneyAfterTransaction() << endl;
          }

     if ( size == 0 ){

          cout << "nothing" << endl;
     }

}

/**
 * printing setteled Transaction
 */
void Customer::printSetteledTransaction(){

     int size = 0;

     for( Transaction* c=Head ; c!= NULL ; c = c->next )

          if(c->getStatus()){

               size++;
               string status = c->getStatus() ? "settle" : "paid";
               cout << c->getDate() <<" " << status << " " << c->getAmountOfTransaction() << " " << c->getRemainingMoneyAfterTransaction() << endl;
          }

     if( size == 0 ){

          cout << "nothing" << endl;

     }

}

/**
 * print Paid Transaction
 */
void Customer::printPaidTransaction(){

     int size = 0;

     for( Transaction* c=Head ; c != NULL ; c = c->next )

          if(!c->getStatus()){

               size++;
               string status = c->getStatus() ? "settle" : "paid";
               cout << c->getDate() <<" " << status << " " << c->getAmountOfTransaction() << " " << c->getRemainingMoneyAfterTransaction() << endl;
          }

     if( size == 0 ){

          cout << "nothing" << endl;

     }

}

/**
 * write all information to text file 
 */
void Customer::printToTextualFile(){

     fstream file;
     file.open("history_write1.txt", ios::out );

     if(!file.is_open()) { cout <<"err occured :|"; return; }

     double first_remaining_money = Head->getStatus() ? Head->getRemainingMoneyAfterTransaction() - Head->getAmountOfTransaction() : Head->getRemainingMoneyAfterTransaction() + Head->getAmountOfTransaction();

     file << customer_number << " " << name << " " << first_remaining_money << " " << counter << endl;

     Transaction* c = Head;

     while( c != NULL ){

          file << c->getDate() << " " << c->getStatus() << " " << c->getAmountOfTransaction() << " " << c->getRemainingMoneyAfterTransaction() << endl;
          c = c->next;
     }

     cout << "printing to text file done :D" << endl;
     file.close();

}

/**
 * reading all information to app from text file
 */
void Customer::readFromTexualFile(){

     fstream file;

     //file.open("history_read1.txt", ios::in );
     /*----------  for testing   ----------*/
     file.open("history_write1.txt", ios::in );

     if(!file.is_open()) { cout << "err occured :|"; return; }

     /* for avoiding repeated imports */  
     ClearTransactions();

     string name;
     double remaining_Money ,amount_of_transaction , remaining_money_after_transaction;
     bool status;
     int date,c;
     long int customer_number;

     file >> customer_number >> name >> remaining_Money >> c;
     set(name , remaining_Money , customer_number);

     int i = 0;
     while( i < c ){

          i++;
          file >> date >> status >> amount_of_transaction >> remaining_money_after_transaction;
          pushBack(date , amount_of_transaction , status );

     }

     file.close();

}

/**
 * writing all inforamtion to binary file
 */
void Customer::printToBinaryFile(){

     fstream file;
     file.open("history_write2.txt", ios::out | ios::binary );

     if(!file.is_open()) { cout <<"err occured :|"; return; }

     file.write(reinterpret_cast<char *>(&remaining_Money),sizeof(remaining_Money));
     file.write(reinterpret_cast<char *>(&customer_number),sizeof(customer_number));
     file.write(reinterpret_cast<char *>(&name),sizeof(name));
     file.write(reinterpret_cast<char *>(&oldest_transaction_date),sizeof(oldest_transaction_date));

     file.write(reinterpret_cast<char *>(&counter),sizeof(counter));
     Transaction* c = Head;
     while ( c != NULL ) {

       file.write(reinterpret_cast<char *>(c),sizeof(Transaction));
       c = c->next;
     }

     cout << "printing to binary file done :D" << endl;
     file.close();
}

/**
 * reading information from binary file
 */
void Customer::readFromBinaryFile(){

     fstream file;
    // file.open("history_read2.txt", ios::in | ios::binary );
    /*----------  for testing  ----------*/
    file.open("history_write2.txt", ios::in | ios::binary );

     if(!file.is_open()) { cout <<"err occured :|"; return; }

     /* for avoiding repeated imports */  
     ClearTransactions();

     file.read(reinterpret_cast<char *>(&remaining_Money),sizeof(remaining_Money));
     file.read(reinterpret_cast<char *>(&customer_number),sizeof(customer_number));
     file.read(reinterpret_cast<char *>(&name),sizeof(name));
     file.read(reinterpret_cast<char *>(&oldest_transaction_date),sizeof(oldest_transaction_date));

     file.read(reinterpret_cast<char *>(&counter),sizeof(counter));
     int count = 0;
     while(count < counter ){
       Transaction *c = new Transaction();
       file.read(reinterpret_cast<char *>(c),sizeof(Transaction));
       c->next = NULL;
       pushBack(c);
       count++;
     }

     file.close();
}

/**
 * print all information to console 
 * ( this method in for testing perpose )
 */
void Customer::print(){

  Transaction* h = Head;

  for(Transaction* c=Head ; c != NULL ; c = c->next)

    cout << customer_number << " " << name << " " << remaining_Money << " "<< c->getDate() << " " << c->getStatus() << " " << c->getAmountOfTransaction() << " " << c->getRemainingMoneyAfterTransaction() << endl;
}

int main(){

    /*=============================================
    =           for testing apllication          =
    =============================================*/
          
    Customer a("john",10000,12345535);
      a.pushBack(981230,2000,1);
      a.pushBack(990201,5000,1);
      a.pushBack(990201,10000,0);
      a.pushBack(990301,5000,0);
      cout << "simple output :" << endl;
      a.print();
      a.printToBinaryFile();
      a.printToTextualFile();
      cout << "-----------------------" << endl;
    Customer b;
      cout << "binary file output ( after added one Transaction ) :" << endl;
      b.readFromBinaryFile();
      b.readFromBinaryFile();
      b.pushBack(991203,1000,1);
      b.print();
      cout << "-----------------------" << endl;
    Customer c;
      cout << "text file output ( after added one Transaction ):" << endl;
      c.readFromTexualFile();
      c.readFromTexualFile();
      c.pushBack(991203,1000,1);
      c.print();
     
    /*=====  End of for testing apllication  ======*/

       return 0;

}
/**
 * validating date
 * @param  date [description]
 * @return      [description]
 */
bool is_date_format_valid(int date){

     if ( date < 10000 && date > 999999) { return false; }
     int d,m,y;
     d = date%100;
     m = (date/100)%100;
     y = (date/10000);

     if( y < 0 || y > 99 ) return false;
     if ( m < 0 || m > 12 ) return false;

     if( m < 7){

          if( d < 1 || d > 31 ) return false; else return true;

     }

     if ( m > 6 ){

          if ( d < 1 || d > 30 ) return false; else return true;
     }

}
