#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <map>
using namespace std;

class User;
class Cart;

class Product;
class ElectronicProduct;
class FashionProduct;

class BuyItems;

/*----------------------------------------------------------------------*/
class User
{
    string userID;
    string userName;
    Cart *userCart;

public:
    // Constructor
    User(string userId, string userName);
    // Setters
    void setID(string userId);
    void setName(string userName);
    // Getters
    string getID();
    string getName();
    // Methods
    void giveCart(Cart *cart);
    // Display
    void displayUserCart();
    void display();
};

/*-----------------------------------------------------------------------*/
class Cart
{
    double Bill;
    vector<BuyItems> Items;
    map<string, User> users;

public:
    // Constructor
    Cart();
    // Setters
    void setBill(double bill);
    // Getters
    double getBill();
    // Methods
    void addItem(BuyItems item);
    void removeItem(string productName);
    void makePayment();
    // Display
    void displayCart();
    void displayCartItems();
    // Destructor
    ~Cart();
};

/* ----------------------------------------------------------------------*/
class Product
{
    string name;
    double prices;

public:
    // Constructor
    Product(string name, double prices);
    // Setters
    void setName(string name);
    void setPrices(double prices);
    // Getters
    string getName();
    double getPrices();
    // Display
    virtual void display();
};

class ElectronicProduct : public Product
{
public:
    // Constructor
    ElectronicProduct(string name, double prices);
    // Display
    void display() override;
};

class FashionProduct : public Product
{
    double discount;

public:
    // Constructor
    FashionProduct(string name, double prices, double discount);
    // Setters
    void setDiscount(double discount);
    // Getters
    double getDiscount();
    // Display
    void display() override;
};

/*----------------------------------------------------------------------*/
class BuyItems
{
    Product *product;
    int quantity;

public:
    // Constructor
    BuyItems(Product *product, int quantity);
    // Setters
    void setProduct(Product *product);
    void setQuantity(int quantity);
    // Getters
    Product *getProduct() const;
    int getQuantity() const;
};

/*----------------------------------------------------------------------*/
// User
// Setters
void User::setID(string userId)
{
    userID = userId;
}
void User::setName(string userName)
{
    this->userName = userName;
}
// Getters
string User::getID()
{
    return userID;
}
string User::getName()
{
    return userName;
}
// Methods
void User::giveCart(Cart *cart)            // Cấp cho người dùng một giỏ hàng 
{
    this->userCart = cart;
}
// Display
void User::display()
{
    cout << "User ID: " << userID << ", User Name: " << userName << endl;
}
void User::displayUserCart()
{
    if (userCart)
    {
        display();
        userCart->makePayment();
        userCart->displayCart();
    }
    else
    {
        cout << "No cart assigned to user " << this->getName() << endl;
    }
}
// Constructor
User::User(string userId, string userName)
{
    setID(userId);
    setName(userName);
    userCart = nullptr;
}
/*----------*/
// Cart
// Setters
void Cart::setBill(double bill)
{
    Bill = bill;
}
// Getters
double Cart::getBill()
{
    return Bill;
}
// Methods
void Cart::addItem(BuyItems item)           // Thêm sản phẩm vào giỏ hàng
{
    Items.push_back(item);
}
void Cart::removeItem(string productName)
{
    auto it = remove_if(Items.begin(), Items.end(), [&](BuyItems &item)
                        { return item.getProduct()->getName() == productName; });
    if (it != Items.end())
    {
        Items.erase(it, Items.end());
    }
    else
    {
        cout << "Item not found in cart." << endl;
    }
}
void Cart::makePayment()                    // Tính tổng tiên trong giỏ hàng 
{
    double total = 0.0;
    for (auto &item : Items)
    {
        Product *product = item.getProduct();
        int quantity = item.getQuantity();

        // Kiểm tra xem sản phẩm có phải là FashionProduct không
        FashionProduct *fashionProduct = dynamic_cast<FashionProduct *>(product);
        if (fashionProduct && fashionProduct->getDiscount() > 0)
        {
            double discountedPrice = fashionProduct->getPrices() * (1 - fashionProduct->getDiscount() / 100);
            total += discountedPrice * quantity;
        }
        else
        {
            total += product->getPrices() * quantity;
        }
    }
    setBill(total);
}
void Cart::displayCart()
{
    cout << "Cart Bill: $" << getBill() << endl;
    cout << endl;
    displayCartItems();
}
void Cart::displayCartItems()
{
    cout << "Items in Cart:" << endl;
    for (const auto &item : Items)
    {
        item.getProduct()->display();
        cout << "Quantity: " << item.getQuantity() << endl;
        cout << endl;
    }
}
// Constructor
Cart::Cart()
{
    Bill = 0.0;
}
// Destructor
Cart::~Cart()
{
    for (auto &item : Items)
    {
        delete item.getProduct(); // Assuming ownership of Product pointers
    }
    Items.clear();
}
/*----------*/
// Product
// Setters
void Product::setName(string name)
{
    this->name = name;
}
void Product::setPrices(double prices)
{
    this->prices = prices;
}
// Getters
string Product::getName()
{
    return name;
}
double Product::getPrices()
{
    return prices;
}
// Display
void Product::display()
{
    cout << "Product Name: " << this->getName() << ", Price: $" << this->getPrices() << endl;
}
// Constructor
Product::Product(string name, double prices)
{
    setName(name);
    setPrices(prices);
}

// ElectronicProduct
// Constructor
ElectronicProduct::ElectronicProduct(string name, double prices) : Product(name, prices) {}
// Display
void ElectronicProduct::display()
{
    cout << "Electronic ";
    Product::display();
}

// FashionProduct
// Setters
void FashionProduct::setDiscount(double discount)
{
    this->discount = discount;
}
// Getters
double FashionProduct::getDiscount()
{
    return discount;
}
// Constructor
FashionProduct::FashionProduct(string name, double prices, double discount) : Product(name, prices)
{
    setDiscount(discount);
}
// Display
void FashionProduct::display()
{
    cout << "Fashion ";
    Product::display();
    cout << "Discount: " << this->getDiscount() << "%" << endl;
}
/*----------*/
// BuyItems
// Setters
void BuyItems::setProduct(Product *product)
{
    this->product = product;
}
void BuyItems::setQuantity(int quantity)
{
    this->quantity = quantity;
}
// Getters
Product *BuyItems::getProduct() const
{
    return product;
}
int BuyItems::getQuantity() const
{
    return quantity;
}
// Constructor
BuyItems::BuyItems(Product *product, int quantity)
{
    setProduct(product);
    setQuantity(quantity);
}

/*----------------------------------------------------------------------*/
int main()
{
    // 1. Tạo sản phẩm
    Product *laptop = new ElectronicProduct("Laptop", 1000);
    Product *tshirt = new FashionProduct("Áo thun", 50, 20); // 20% discount

    // 2. Tạo người dùng
    User alice("001", "Alice");

    // 3. Tạo giỏ hàng và gán cho Alice
    Cart *aliceCart = new Cart();
    alice.giveCart(aliceCart);

    // 4. Thêm sản phẩm vào giỏ
    aliceCart->addItem(BuyItems(laptop, 1)); // 1 laptop
    aliceCart->addItem(BuyItems(tshirt, 2)); // 2 áo thun

    // 5. In giỏ hàng + tổng tiền
    alice.displayUserCart();
    aliceCart->makePayment();

    // 6. Giải phóng bộ nhớ
    delete aliceCart;

    return 0;
}