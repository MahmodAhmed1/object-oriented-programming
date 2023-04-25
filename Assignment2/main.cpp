#include <iostream>
using namespace std;

class Item
{
private:        //define variables
    int ID, quantity;
    string name;
    double price;
public:
    static int counter;  // static counter

    Item() //empty constructor
    {

        name = " ";
        quantity = 0;
        price = 0;
        ID = 0;
    }

    Item(string n, int q, int p)//parameterized constructor
    {

        name = n;
        quantity = q;
        price = p;
        ID = counter;

    }

    Item(const Item& obj) //copy constructor
    {
        this->name = name;
        this->quantity = quantity;
        this->price = price;
       this->ID = ID;
    }
    //setters
    void setname(string n)
    {
        name = n;
        counter++;
        ID = counter;
    }
    void setquantity(int q)
    {
        quantity = q;
    }
    void setprice(int p)
    {
        price = p;
    }
    //getters
    string getname() const
    {
        return name;
    }
    int getquantity() const
    {
        return quantity;
    }
    int getprice() const
    {
        return price;
    }
    int getId()
    {
        return ID;
    }


    bool operator==(const Item& obj) //== operator
    {
        return name == obj.name;
    }

    void operator+=(const int quantity)//+= operator
    {
        this->quantity += quantity;
    }

    void operator-=(const int quantity) //-= operator
    {
        this->quantity -= quantity;
    }

    friend istream& operator>>(istream& input, Item& obj)//>> operator
    {
        input >> obj.name >> obj.price >> obj.quantity;
        return input;
    }

    friend ostream& operator<<(ostream& output, Item& obj)//<< operator
    {
        output << "Name: " << obj.name << "\t" << "Price: " << obj.price << "\t" << "Quantity: " << obj.quantity << "\t" << "ID: " << obj.ID;
        return output;
    }
};

int Item::counter = 0; // define static counter

class Seller
{
private:
    string name, email; // define variables
    Item* items;

    int maxitems, num_of_item;
public:

    Seller(string name, string email, int maxitems)// parameterized constructor
    {
        this->name = name;
        this->email = email;
        this->maxitems = maxitems;
        items = new Item[maxitems];
        this->num_of_item = 0;
    }

    friend ostream& operator<<(ostream& output, Seller& obj)// << constructor
    {
        output << "Name: " << obj.name << "\t" << "Email: " << obj.email << "\t" << "Max Items: " << obj.maxitems << endl;
        return output;
    }

    bool addanitem(Item &obj) //add item function
    {
        for (int i = 0; i < num_of_item; i++)
        {
            if (items[i] == obj)
            {
                items[i] += obj.getquantity();
                return true;
            }
        }
        if (num_of_item < maxitems)
        {

            items[num_of_item] = obj;
            num_of_item++;
            return true;
        }
        else
            return false;
    }


    bool sellanitem(string name, int quantity)  //sell item function
    {
        for (int i = 0; i < num_of_item; i++)
        {
            if (items[i].getname() == name)
            {
                if (items[i].getquantity() >= quantity)
                {
                    items[i] -= quantity;
                    return true;
                }
                else
                    return false;

            }
        }
        return false;
    }

    void print() //print function
    {
        for (int i = 0; i < num_of_item; i++)
        {
            cout << items[i] << endl;
        }
    }

    Item& findanitem(int id) //find by ID function
    {
        for (int i = 0;i < num_of_item;i++)
        {
            if (items[i].getId() == id)
            {
                return items[i];
            }
        }
    }

    ~Seller() //destructor
    {
        delete[]items;
    }
};

int main()
{
    string name, email, nameitem;
    int maxitems, options = 0, quantity;
    double price;
    Item a(nameitem, quantity, price);
    cout << "Enter name: ";
    cin >> name;
    cout << "Enter email: ";
    cin >> email;
    cout << "Enter store capacity: ";
    cin >> maxitems;
    Seller x(name, email, maxitems);
    cout << "1-Print My Info." << "\n";
    cout << "2-Add An Item." << "\n";
    cout << "3-Sell An Item." << "\n";
    cout << "4-Print Items." << "\n";
    cout << "5-Find an Item by ID." << "\n";
    cout << "6-Exit." << "\n";

    while (options < 6)
    {
        cout << "\nchoose from following options from 1 to 6 only: ";
        cin >> options;

        if (options == 1) // print info
        {
            cout << endl;
            cout << x;
        }
        else if (options == 2) // add an item
        {
            cout << "\nEnter name item and quantity and price: ";
            cin >> nameitem >> quantity >> price;

            a.setname(nameitem);
            a.setprice(price);
            a.setquantity(quantity);
            x.addanitem(a);
            x.print();
        }
        else if (options == 3) //sell an item
        {
            cout << "\nEnter name item and quantity :";
            cin >> nameitem >> quantity;
            x.sellanitem(nameitem, quantity);
            x.print();
        }
        else if (options == 4) // print items
        {
            x.print();
        }
        else if (options == 5) // find by ID
        {
            int id;
            cout << "Enter the item by ID: ";
            cin >> id;
            cout << x.findanitem(id) << endl;
        }
    }

    return 0;
};
