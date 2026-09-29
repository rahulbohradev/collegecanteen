#include <iostream>
#include <cstdlib>
#include <string>
#include <iomanip>
using namespace std;


/* =========================================================
   FOOD ITEM
   ========================================================= */

class FoodItem
{
public:
    int id;
    string name;
    double price;
    int quantity;

    FoodItem()
    {
        id = 0;
        name = "";
        price = 0;
        quantity = 0;
    }

    FoodItem(int i, string n, double p, int q)
    {
        id = i;
        name = n;
        price = p;
        quantity = q;
    }

    void display()
    {
        cout << left
             << setw(5) << id
             << setw(20) << name
             << "Rs." << setw(10) << fixed << setprecision(2) << price
             << setw(10) << quantity << endl;
    }
};


/* =========================================================
   ORDER
   ========================================================= */

class Order
{
public:
    int orderId;
    string studentName;

    // Multiple food items in one order
    FoodItem items[10];
    int itemCount;
    double total;

    Order()
    {
        orderId = 0;
        studentName = "";
        itemCount = 0;
        total = 0;
    }

    void addItem(FoodItem item)
    {
        if (itemCount < 10)
        {
            items[itemCount] = item;
            itemCount++;
            total = total + (item.price * item.quantity);
        }
    }

    void display()
    {
        cout << "\n----------------------------------------";
        cout << "\nOrder ID : " << orderId;
        cout << "\nStudent  : " << studentName;
        cout << "\nItems:";

        for (int i = 0; i < itemCount; i++)
        {
            cout << "\n  " << items[i].name
                 << " x " << items[i].quantity
                 << " = Rs."
                 << fixed << setprecision(2)
                 << (items[i].price * items[i].quantity);
        }

        cout << "\nTotal    : Rs."
             << fixed << setprecision(2) << total;
        cout << "\n----------------------------------------";
    }
};


/* =========================================================
   QUEUE
   FIFO - PENDING ORDERS
   ========================================================= */

class Queue
{
public:
    Order q[50];
    int front, rear, max;

    Queue()
    {
        front = -1;
        rear = -1;
        max = 49;
    }

    void Insert(Order item)
    {
        if (rear == max)
        {
            cout << "\nQueue is Full!!";
        }
        else
        {
            if (front == -1)
            {
                front = 0;
            }

            rear++;
            q[rear] = item;
        }
    }

    Order Delete()
    {
        Order item;

        if (front == -1)
        {
            cout << "\nQueue is Empty";
            return item;
        }
        else
        {
            item = q[front];

            if (front == rear)
            {
                front = -1;
                rear = -1;
            }
            else
            {
                front++;
            }

            return item;
        }
    }

    Order* Peek()
    {
        if (front == -1)
        {
            return NULL;
        }

        return &q[front];
    }

    void Display()
    {
        if (front == -1)
        {
            cout << "\nQueue is Empty";
        }
        else
        {
            cout << "\n\n========== PENDING ORDERS ==========";

            for (int i = front; i <= rear; i++)
            {
                q[i].display();
            }
        }
    }

    bool isEmpty()
    {
        if (front == -1)
            return true;
        else
            return false;
    }
};


/* =========================================================
   STACK
   LIFO - COMPLETED ORDERS
   ========================================================= */

class Stack
{
public:
    Order arr[50];
    int top;

    Stack()
    {
        top = -1;
    }

    void Push(Order item)
    {
        if (top == 49)
        {
            cout << "\nStack Overflow";
        }
        else
        {
            top = top + 1;
            arr[top] = item;
        }
    }

    Order Pop()
    {
        Order item;

        if (top == -1)
        {
            cout << "\nStack Underflow";
            return item;
        }
        else
        {
            item = arr[top];
            top--;
            return item;
        }
    }

    void Display()
    {
        if (top == -1)
        {
            cout << "\nStack is Empty";
        }
        else
        {
            cout << "\n\n========== COMPLETED ORDERS ==========";

            for (int i = top; i >= 0; i--)
            {
                arr[i].display();
            }
        }
    }

    bool isEmpty()
    {
        if (top == -1)
            return true;
        else
            return false;
    }
};


/* =========================================================
   DISPLAY FOOD MENU
   ========================================================= */

void DisplayMenu(FoodItem menu[], int foodCount)
{
    cout << "\n\n============== FOOD MENU ==============";

    cout << "\n"
         << left
         << setw(5) << "ID"
         << setw(20) << "Food"
         << setw(14) << "Price"
         << setw(10) << "Quantity";

    cout << "\n-----------------------------------------------\n";

    for (int i = 0; i < foodCount; i++)
    {
        menu[i].display();
    }
}


/* =========================================================
   LINEAR SEARCH
   ========================================================= */

FoodItem* SearchFood(FoodItem menu[], int foodCount, int id)
{
    for (int i = 0; i < foodCount; i++)
    {
        if (menu[i].id == id)
        {
            return &menu[i];
        }
    }

    return NULL;
}


/* =========================================================
   REMOVE FOOD
   ARRAY DELETION
   ========================================================= */

void RemoveFood(FoodItem menu[], int &foodCount)
{
    int foodId;
    int pos = -1;

    cout << "\nEnter Food ID to remove: ";
    cin >> foodId;

    for (int i = 0; i < foodCount; i++)
    {
        if (menu[i].id == foodId)
        {
            pos = i;
            break;
        }
    }

    if (pos == -1)
    {
        cout << "\nFood item not found.";
        return;
    }

    for (int i = pos; i < foodCount - 1; i++)
    {
        menu[i] = menu[i + 1];
    }

    foodCount--;

    cout << "\nFood item removed successfully.";
}


/* =========================================================
   MAIN
   ========================================================= */

int main()
{
    FoodItem menu[50];

    int foodCount = 5;

    menu[0] = FoodItem(1, "Burger", 80, 20);
    menu[1] = FoodItem(2, "Pizza", 120, 15);
    menu[2] = FoodItem(3, "Sandwich", 60, 25);
    menu[3] = FoodItem(4, "French Fries", 50, 30);
    menu[4] = FoodItem(5, "Tea", 20, 50);


    /* DSA */
    Queue pendingOrders;
    Stack completedOrders;


    int nextOrderId = 101;
    int nextFoodId = 6;

    int mainChoice;


    while (1)
    {
        cout << "\n\n==========================================";
        cout << "\n       COLLEGE CANTEEN ORDERING SYSTEM";
        cout << "\n==========================================";

        cout << "\n1. Student / User";
        cout << "\n2. Admin";
        cout << "\n3. Exit";

        cout << "\n\nEnter choice: ";
        cin >> mainChoice;


        /* =================================================
           USER SIDE
           ================================================= */

        if (mainChoice == 1)
        {
            int userChoice;

            while (1)
            {
                cout << "\n\n================================";
                cout << "\n          USER MENU";
                cout << "\n================================";

                cout << "\n1. View Food Menu";
                cout << "\n2. Place Order";
                cout << "\n3. View Next Order";
                cout << "\n4. Back";

                cout << "\n\nEnter choice: ";
                cin >> userChoice;


                /* VIEW MENU */

                if (userChoice == 1)
                {
                    DisplayMenu(menu, foodCount);
                }


                /* PLACE ORDER */

                else if (userChoice == 2)
                {
                    string studentName;

                    cout << "\nEnter Student Name: ";
                    cin.ignore();
                    getline(cin, studentName);

                    Order newOrder;
                    newOrder.orderId = nextOrderId;
                    newOrder.studentName = studentName;

                    int addMore = 1;

                    while (addMore == 1)
                    {
                        DisplayMenu(menu, foodCount);

                        int foodId;
                        cout << "\nEnter Food ID: ";
                        cin >> foodId;

                        /* Linear Search */

                        FoodItem *food =
                            SearchFood(menu, foodCount, foodId);

                        if (food == NULL)
                        {
                            cout << "\nFood item not found.";
                            continue;
                        }

                        if (food->quantity <= 0)
                        {
                            cout << "\nFood is out of stock.";
                            continue;
                        }

                        int quantity;

                        cout << "\nEnter Quantity: ";
                        cin >> quantity;

                        if (quantity <= 0)
                        {
                            cout << "\nInvalid quantity.";
                            continue;
                        }

                        if (quantity > food->quantity)
                        {
                            cout << "\nOnly "
                                 << food->quantity
                                 << " items available.";
                            continue;
                        }

                        // Check that the same food is not already in cart
                        bool alreadyAdded = false;

                        for (int i = 0; i < newOrder.itemCount; i++)
                        {
                            if (newOrder.items[i].id == food->id)
                            {
                                alreadyAdded = true;
                                break;
                            }
                        }

                        if (alreadyAdded)
                        {
                            cout << "\nThis food is already added to the order.";
                            continue;
                        }

                        FoodItem selectedItem(
                            food->id,
                            food->name,
                            food->price,
                            quantity
                        );

                        newOrder.addItem(selectedItem);

                        // Reduce stock
                        food->quantity =
                            food->quantity - quantity;

                        cout << "\n"
                             << food->name
                             << " added to order.";

                        cout << "\n\nAdd another food item?";
                        cout << "\n1. Yes";
                        cout << "\n2. No";
                        cout << "\nEnter choice: ";
                        cin >> addMore;
                    }

                    if (newOrder.itemCount == 0)
                    {
                        cout << "\nNo item added. Order cancelled.";
                        continue;
                    }

                    /* Queue Insert */

                    pendingOrders.Insert(newOrder);

                    cout << "\n\n================================";
                    cout << "\n          ORDER PLACED";
                    cout << "\n================================";

                    newOrder.display();

                    cout << "\n\nOrder added to pending queue.";

                    nextOrderId++;
                }


                /* VIEW NEXT ORDER */

                else if (userChoice == 3)
                {
                    Order *order =
                        pendingOrders.Peek();

                    if (order == NULL)
                    {
                        cout << "\nNo pending orders.";
                    }
                    else
                    {
                        cout << "\n\n========== NEXT ORDER ==========";
                        order->display();
                    }
                }


                /* BACK */

                else if (userChoice == 4)
                {
                    break;
                }


                else
                {
                    cout << "\nInvalid choice.";
                }
            }
        }


        /* =================================================
           ADMIN SIDE
           ================================================= */

        else if (mainChoice == 2)
        {
            string password;

            cout << "\nEnter Admin Password: ";
            cin >> password;


            if (password != "admin123")
            {
                cout << "\nIncorrect password.";
                continue;
            }


            cout << "\nAdmin login successful!";


            int adminChoice;


            while (1)
            {
                cout << "\n\n================================";
                cout << "\n          ADMIN PANEL";
                cout << "\n================================";

                cout << "\n1. View Food Menu";
                cout << "\n2. Add Food Item";
                cout << "\n3. Remove Food Item";
                cout << "\n4. Update Food Quantity";
                cout << "\n5. Update Food Price";
                cout << "\n6. View Pending Orders";
                cout << "\n7. Process Next Order";
                cout << "\n8. View Completed Orders";
                cout << "\n9. Back";

                cout << "\n\nEnter choice: ";
                cin >> adminChoice;


                /* VIEW MENU */

                if (adminChoice == 1)
                {
                    DisplayMenu(menu, foodCount);
                }


                /* ADD FOOD */

                else if (adminChoice == 2)
                {
                    if (foodCount >= 50)
                    {
                        cout << "\nMenu is Full.";
                        continue;
                    }


                    string name;
                    double price;
                    int quantity;


                    cout << "\nEnter Food Name: ";

                    cin.ignore();
                    getline(cin, name);


                    cout << "Enter Price: ";
                    cin >> price;


                    cout << "Enter Quantity: ";
                    cin >> quantity;


                    if (price <= 0 || quantity < 0)
                    {
                        cout << "\nInvalid price or quantity.";
                        continue;
                    }


                    menu[foodCount] =
                        FoodItem(
                            nextFoodId,
                            name,
                            price,
                            quantity
                        );


                    cout << "\nFood item added successfully.";

                    cout << "\nFood ID: "
                         << nextFoodId;


                    foodCount++;
                    nextFoodId++;
                }


                /* REMOVE FOOD */

                else if (adminChoice == 3)
                {
                    RemoveFood(menu, foodCount);
                }


                /* UPDATE QUANTITY */

                else if (adminChoice == 4)
                {
                    int foodId;

                    cout << "\nEnter Food ID: ";
                    cin >> foodId;


                    FoodItem *food =
                        SearchFood(menu, foodCount, foodId);


                    if (food == NULL)
                    {
                        cout << "\nFood item not found.";
                        continue;
                    }


                    cout << "\nCurrent Quantity: "
                         << food->quantity;


                    int quantity;

                    cout << "\nEnter New Quantity: ";
                    cin >> quantity;


                    if (quantity < 0)
                    {
                        cout << "\nInvalid quantity.";
                        continue;
                    }


                    food->quantity = quantity;

                    cout << "\nQuantity updated successfully.";
                }


                /* UPDATE PRICE */

                else if (adminChoice == 5)
                {
                    int foodId;

                    cout << "\nEnter Food ID: ";
                    cin >> foodId;


                    FoodItem *food =
                        SearchFood(menu, foodCount, foodId);


                    if (food == NULL)
                    {
                        cout << "\nFood item not found.";
                        continue;
                    }


                    cout << "\nCurrent Price: Rs."
                         << food->price;


                    double price;

                    cout << "\nEnter New Price: ";
                    cin >> price;


                    if (price <= 0)
                    {
                        cout << "\nInvalid price.";
                        continue;
                    }


                    food->price = price;

                    cout << "\nPrice updated successfully.";
                }


                /* VIEW PENDING ORDERS */

                else if (adminChoice == 6)
                {
                    pendingOrders.Display();
                }


                /* PROCESS NEXT ORDER */

                else if (adminChoice == 7)
                {
                    if (pendingOrders.isEmpty())
                    {
                        cout << "\nNo pending orders.";
                        continue;
                    }


                    Order completedOrder =
                        pendingOrders.Delete();


                    /* Stack Push */

                    completedOrders.Push(completedOrder);


                    cout << "\n\n================================";
                    cout << "\n        ORDER COMPLETED";
                    cout << "\n================================";

                    completedOrder.display();

                    cout << "\n\nOrder moved from Queue to Stack.";
                }


                /* VIEW COMPLETED ORDERS */

                else if (adminChoice == 8)
                {
                    completedOrders.Display();
                }


                /* BACK */

                else if (adminChoice == 9)
                {
                    break;
                }


                else
                {
                    cout << "\nInvalid choice.";
                }
            }
        }


        /* EXIT */

        else if (mainChoice == 3)
        {
            cout << "\n\nThank you for using College Canteen!";
            break;
        }


        else
        {
            cout << "\nInvalid choice.";
        }
    }


    return 0;
}