# Code_OOP
#include <iostream>
#include <string.h>
#include <list>
using namespace std;

/*---------------------------------------------------------------------------------------*/
class BorrowerRecord;
/*CLass BOOK*/
class Book
{
    string theCatalogueNumber;
    string theAuthor;
    string theTitle;
    BorrowerRecord *theBorrower;

public:
    // Constructor
    Book(string aCatalogueNumber, string aAuthor, string aTitle);
    // Setter
    void setCatalogueNumber(string Number);
    void setAuthor(string Author);
    void setTitle(string Title);
    void setBorrower(BorrowerRecord *borrower);
    // Getter
    string getCatalogueNumber();
    string getAuthor();
    string getTitle();
    BorrowerRecord *getBorrower();
    // Display
    void display();
    // Method
    void attachBorrower(BorrowerRecord *Borrower);
    void detachBorrower();
};
// Setter
void Book::setCatalogueNumber(string Number)
{
    this->theCatalogueNumber = Number;
}
void Book::setAuthor(string Author)
{
    this->theAuthor = Author;
}
void Book::setTitle(string Title)
{
    this->theTitle = Title;
}
void Book::setBorrower(BorrowerRecord *Borrower)
{
    this->theBorrower = Borrower;
}
// Getter
string Book::getCatalogueNumber()
{
    return this->theCatalogueNumber;
}
string Book::getAuthor()
{
    return this->theAuthor;
}
string Book::getTitle()
{
    return this->theTitle;
}
BorrowerRecord *Book::getBorrower()
{
    return this->theBorrower;
}
// Display
void Book::display()
{
    cout << "The Catalog Number      : " << this->getCatalogueNumber() << endl;
    cout << "The Author              : " << this->getAuthor() << endl;
    cout << "The Title               : " << this->getTitle() << endl;
    cout << endl;
}
// Constructor
Book::Book(string aCatalogueNumber, string aAuthor, string aTitle)
{
    this->setCatalogueNumber(aCatalogueNumber);
    this->setAuthor(aAuthor);
    this->setTitle(aTitle);
    this->theBorrower = NULL;
}

/*---------------------------------------------------------------------------------------*/
/*Class Borrower Record*/
class BorrowerRecord
{
    string name;
    list<Book *> books;

public:
    BorrowerRecord(string Name);
    void setName(string name);
    void addBook(Book *book);
    string getName();
    list<Book *> getBooks();
    void display();
    void attachBook(Book *book);
    void detachBook(Book *book);
};
// Setter
void BorrowerRecord::setName(string Name)
{
    this->name = Name;
}
void BorrowerRecord::addBook(Book *book)
{
    this->books.push_back(book);
}
// Getter
string BorrowerRecord::getName()
{
    return this->name;
}
list<Book *> BorrowerRecord::getBooks()
{
    return this->books;
}
// Constructor
BorrowerRecord::BorrowerRecord(string aName)
{
    this->setName(aName);
}
// Display
void BorrowerRecord::display()
{
    cout << "The name                : " << this->getName() << endl;
}
/*---------------------------------------------------------------------------------------*/
/* RELATIONSHIP */
// Methods Book
void Book::attachBorrower(BorrowerRecord *borrower)
{
    if (this->theBorrower == NULL)
    {
        this->setBorrower(borrower);
        borrower->attachBook(this);
    }
}
void Book::detachBorrower()
{
    BorrowerRecord *borrower = this->getBorrower();
    if (borrower == NULL)
        return;
    this->setBorrower(NULL);
    borrower->detachBook(this);
}
// Methods Borrower
void BorrowerRecord::attachBook(Book *book)
{
    for (auto b : this->books)
    {
        if (b == book)
        {
            return;
        }
    }
    this->addBook(book);
}
void BorrowerRecord::detachBook(Book *book)
{
    this->books.remove(book);
}
/*---------------------------------------------------------------------------------------*/
// Class Libary
class Libary
{
    string theLibaryName;
    list<Book *> stock;
    list<BorrowerRecord *> borrower;

public:
    // Constructor
    Libary(string libName);
    // Setter
    void setLibaryName(string libName);
    // Getter
    string getLibaryName();
    list<Book *> getBook();
    // Display
    void displayLibaryName();
    void displayBooks(char Choice);
    void displayBorrowers(char Choice);
    void displayBookOnLoan(char Choice);
    void displayBookAvailableForLoan();
    void display(int choice);
    // Methods
    void registerOneBorrower(string aName);
    void addOneBook(Book *aBook);
    void lendOneBook(string catalougeNumber, string borrowerName);
    void returnOneBook(string catalougeNumber);
    // Destructor
    ~Libary();
};
// Setter
void Libary::setLibaryName(string Name)
{
    this->theLibaryName = Name;
}
// Getter
string Libary::getLibaryName()
{
    return this->theLibaryName;
}
list<Book *> Libary::getBook()
{
    return this->stock;
}
// Display
void Libary::displayLibaryName()
{
    cout << "The Name Of The Libary  : " << this->getLibaryName() << endl;
    cout << "----------------------------------------------------" << endl;
}
void Libary::displayBorrowers(char Choice)
{
    cout << "The list Borrowers: " << endl;
    if (Choice == 'Y')
    {
        for (BorrowerRecord *br : this->borrower)
        {
            br->display();
            cout << "Books Loan: " << endl;
            list<Book *> listBook = br->getBooks();
            for (auto b : listBook)
            {
                b->display();
            }
            cout << "------" << endl;
        }
    }
    else
    {
        for (BorrowerRecord *br : this->borrower)
        {
            br->display();
        }
    }

    cout << "----------------------------------------------------" << endl;
}
void Libary::displayBooks(char Choice)
{
    cout << "The List of the Books   :" << endl;
    if (Choice == 'Y')
    {
        for (auto i : this->stock)
        {
            cout << "Book: " << i->getTitle() << endl;
            auto br = i->getBorrower();
            if (br != NULL)
            {
                br->display();
            }
            i->display();
        }
    }
    else
    {
        for (auto i : this->stock)
        {
            cout << "Book: " << i->getTitle() << endl;
            i->display();
        }
    }
    cout << "----------------------------------------------------" << endl;
}
void Libary::displayBookOnLoan(char Choice)
{
    cout << "Book on Loan: ";
    int Check = 0;
    if (Choice == 'Y')
    {
        for (Book *b : stock)
        {
            if (b->getBorrower() != NULL)
            {
                Check++;
                cout << endl;
                BorrowerRecord *br = b->getBorrower();
                br->display();
                b->display();
            }
        }
        if (Check == 0)
        {
            cout << "No Book On Loan!" << endl;
        }
        else
        {
            cout << Check << " Book is on Loan!" << endl;
        }
    }
    else
    {
        for (Book *b : stock)
        {
            if (b->getBorrower() != NULL)
            {
                Check++;
                cout << endl;
                b->display();
            }
        }
        if (Check == 0)
        {
            cout << "No Book On Loan!" << endl;
        }
        else
        {
            cout << Check << " Book is on Loan!" << endl;
        }
    }
    cout << "----------------------------------------------------" << endl;
}
void Libary::displayBookAvailableForLoan()
{
    cout << "Book available for Loan: ";
    int Check = 0;
    for (auto b : stock)
    {
        if (b->getBorrower() == NULL)
        {
            Check++;
            cout << endl;
            b->display();
        }
    }
    if (Check == 0)
    {
        cout << "All Book is Loan" << endl;
    }
    else
    {
        cout << "Last " << stock.size() - Check << " book available for Loan!" << endl;
    }
    cout << "----------------------------------------------------" << endl;
}
void Libary::display(int Choice)
{
    if (Choice == 2)
        this->displayLibaryName();
    if (Choice == 3)
    {
        cout << "Do you want to know Which Borrower Loan the Book? " << endl;
        cout << "If: Yes -> Y, No -> N" << endl;
        cout << "----------------------------------------------------" << endl;
        char Choice;
        cin >> Choice;
        this->displayBooks(Choice);
    }
    if (Choice == 4)
    {
        cout << "Do you want to know Which Books Borrower Loan?" << endl;
        cout << "If: Yes -> Y, No -> N" << endl;
        cout << "----------------------------------------------------" << endl;
        char Choice;
        cin >> Choice;
        this->displayBorrowers(Choice);
    }
    if (Choice == 5)
    {
        cout << "Do you want to know Who Loan Book? " << endl;
        cout << "If: Yes -> Y, No -> N" << endl;
        cout << "----------------------------------------------------" << endl;
        char Choice;
        cin >> Choice;
        this->displayBookOnLoan(Choice);
    }
    if (Choice == 6)
        this->displayBookAvailableForLoan();
    if (Choice == 1)
    {
        for (int Index = 2; Index <= 6; Index++)
        {
            this->display(Index);
        }
    }
}
// Methods
void Libary::addOneBook(Book *aBook)
{
    this->stock.push_back(aBook);
}
void Libary::registerOneBorrower(string aName)
{
    BorrowerRecord *theBorrower = new BorrowerRecord(aName);
    this->borrower.push_back(theBorrower);
}
void Libary::lendOneBook(string catalougueNumber, string borrowerName)
{
    // Find Book with catalougueNumber in Stock
    Book *theBook = NULL;
    for (Book *b : this->stock)
    {
        if (b->getCatalogueNumber() == catalougueNumber)
        {
            theBook = b;
            break;
        }
    }
    // Check Book
    if (theBook == NULL)
    {
        cout << "Book not found! " << endl;
        return;
    }
    if (theBook != NULL)
    {
        if (theBook->getBorrower() != NULL)
        {
            cout << "Book on Loan!" << endl;
            return;
        }
    }
    // Find the Borrower:
    BorrowerRecord *theBorrower = NULL;
    for (BorrowerRecord *br : this->borrower)
    {
        if (br->getName() == borrowerName)
        {
            theBorrower = br;
            break;
        }
    }
    // Check Borrower
    if (theBorrower == NULL)
    {
        cout << "The Borrower not found! " << endl;
        return;
    }
    // Lend Book;
    theBook->attachBorrower(theBorrower);
}
void Libary::returnOneBook(string catalougeNumber)
{
    Book *theBook = NULL;
    // Find Book In Stock
    for (Book *b : this->stock)
    {
        if (b->getCatalogueNumber() == catalougeNumber)
        {
            theBook = b;
            break;
        }
    }
    if (theBook == NULL)
    {
        cout << "Book is not found!" << endl;
        return;
    }
    // Check Borrower
    if (theBook->getBorrower() == NULL)
    {
        cout << "Borrower is not found!" << endl;
        return;
    }
    if (theBook->getBorrower() != NULL)
    {
        theBook->detachBorrower();
    }
}
// Destructors
Libary::~Libary()
{
    this->stock.clear();
    for (BorrowerRecord *i : this->borrower)
    {
        delete (i);
    }
}
// Constructor
Libary::Libary(string libName)
{
    this->setLibaryName(libName);
}
/*---------------------------------------------------------------------------------------*/
/*                                  MAIN                                                 */
int main()
{
    cout << "The Library Application\n"
         << endl;
    Libary lib("Lib");

    // Tạo đám sách =))
    Book *first = new Book("000", "Aso Haro", "Alice in Borderland");
    Book second("001", "Ha Van Thao", "Co so lap trinh huong doi tuong");
    Book *third = new Book("002", "Nguyen Hien Luong", "Co so du lieu");
    Book fourth("003", "Le Thi Tuyet Nhung", "Toan roi rac");

    // Quăng mớ sách vô cái tủ :)))
    lib.addOneBook(first);
    lib.addOneBook(&second);
    lib.addOneBook(third);
    lib.addOneBook(&fourth);

    // Những thằng mượn sách ^^
    lib.registerOneBorrower("Minh Duy");
    lib.registerOneBorrower("Minh Huy");
    lib.registerOneBorrower("Nguyen Hieu");
    lib.registerOneBorrower("Thinh Le");

    // Cho mượn sách ):<
    lib.lendOneBook("000", "Minh Duy");
    lib.lendOneBook("003", "Minh Duy");

    // Xuất thông tin
    cout << " Information about Choice: " << endl;
    cout << " 0: Exit! " << endl;
    cout << " 1: All Informatition in the Libary! " << endl;
    cout << " 2: Information Libary! " << endl;
    cout << " 3: List of Book in the Libary!" << endl;
    cout << " 4: List of Borrowers had register!" << endl;
    cout << " 5: List of Books on Loan!" << endl;
    cout << " 6: List of Books Available For Loan! " << endl;
    cout << "----------------------------------------------------" << endl;
    cout << "Choose Choice to Display: ";
    int Choice;
    cin >> Choice;
    while (Choice > 0 && Choice <= 6)
    {
        lib.display(Choice);
        cout << "Press another Choice or Press 0 to exit: " ;
        cin >> Choice;
    }

    // Do khởi tạo kiểu con tro nên phải delete :3
    delete (first);
    delete (third);
    return 0;
}

