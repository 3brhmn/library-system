#include<bits/stdc++.h>
//#define endl "\n"
#define loop(n) for(int i=0;i<n;i++)
#define ll long long
#define ull unsigned long long
#define ld long double
#define pb(l) push_back(l)
#define pf(l) push_front(l)
#define pob(l) pop_back(l)
#define pof(l) pop_front(l)




using namespace std;

void fast()
{   cin.tie(0);
    cin.sync_with_stdio(0);
}

bool cmp(pair<string , int>x , pair<string , int>y)
{

}



struct book
{
    string name ;
    int id , quantity , amount_of_borrow = 0;
    string user_borrow_this_bok[50];
    int borrow_idx = 0;

    void add_book()
    {

        cout<<"enter the book name : "<<endl;
        cin>>name;

        cout<<"\nenter the book id : "<<endl;
        cin>>id;

        cout<<"\nenter the quantity of that book : "<<endl;
        cin>>quantity;
    }
    void book_detail()
    {
            cout<<"book name : "<<name<<endl;
            cout<<"book id : "<<id<<endl;
            cout<<"book quantity : "<<quantity<<endl;
            cout<<"number of peoble who borrow this books : "<<amount_of_borrow<<endl;
    }


};
struct user
{
    string name;
    int id;
    int id_of_borrowed_book[50]{};
    int id_idx = 0;

    void add_user()
    {
        cout<<"enter the user name : "<<endl;
        cin>>name;
        cout<<"enter the user id : "<<endl;
        cin>>id;
    }
    void print_the_user()
    {
            cout<<"user name : "<<name<<"\tuser id : "<<id<<endl;
            cout<<"id of the books i borrow : ";

            for(int j = 0;j<id_idx;j++)
                cout<<id_of_borrowed_book[j]<<" ";

            if(id_idx==0)cout<<"none";
            cout<<endl;

    }
};

struct library_system
{
    book books[50];
    int book_idx = 0;
    user users [50];
    int user_idx=0;

    void show_the_menu()
    {

        cout<<"1) add a book ."<<endl;
        cout<<"2) search for a book by suffix ."<<endl;
        cout<<"3) print the user who borrow a particular books ."<<endl;
        cout<<"4) sort the books by id ."<<endl;
        cout<<"5) sort the books by name ."<<endl;
        cout<<"6) add user ."<<endl;
        cout<<"7) to borrow a bock ."<<endl;
        cout<<"8) return a book ."<<endl;
        cout<<"9) print the users ."<<endl;
        cout<<"10) exit ."<<endl;
        cout<<"enter a number in range [ 1 , 10 ] : "<<endl;
    }
    void menu()
    {
        cout<<"library menu"<<endl;

        int num = 0;
        while(num!=10)
        {

           show_the_menu();
           cin>>num;
           cout<<endl;

           cout<<"\n*-----------------------------------------------*\n";

            if(num==1)
                books[book_idx++].add_book();
            else if(num==2)
            {
                cout<<"enter the prefix : "<<endl;

                string prefix ; cin>>prefix;

                search_for_books_by_prefix(prefix);
            }
            else if(num==3)who_borrow_this_book();
            else if(num==4)sort_by_id();
            else if(num==5)sort_by_name();
            else if(num==6)users[user_idx++].add_user();
            else if(num==7)borrow_a_book();
            else if(num==8)return_a_book();
            else if(num==9)print_the_user();

            cout<<"\n*-----------------------------------------------*\n\n";
        }
    }



    void search_for_books_by_prefix(string &prefix)
    {

        bool check_for_book = false;

        cout<<"\nthe books are : "<<endl;

        for(int i=0;i<book_idx;i++)
        {
            if(prefix<=books[i].name)
            {
                if(books[i].name.substr(0,prefix.length())==prefix)
                    cout<<books[i].name<<" " , check_for_book = true;;
            }
        }
        if(!check_for_book)cout<<"Nothing found with that prefix"<<endl;
    }


    void sort_based_on(bool id = false , bool name = false)
    {
        for(int i = 0;i<book_idx;i++)
        {
            for(int j=i+1;j<book_idx;j++)
            {
                if(id&&books[i].id>books[j].id)
                {
                    swap(books[i].id , books[j].id);
                    swap(books[i].name , books[j].name);
                    swap(books[i].quantity , books[j].quantity);

                }
                else if(name&&books[i].name>books[j].name)
                {
                    swap(books[i].id , books[j].id);
                    swap(books[i].name , books[j].name);
                    swap(books[i].quantity , books[j].quantity);

                }


            }
        }
    }
    void sort_by_id ()
    {
        sort_based_on(true,false);
        print_books_details();
    }
    void sort_by_name()
    {
        sort_based_on(false,true);
        print_books_details();
    }

    void print_books_details()
    {
        for(int i=0;i<book_idx;i++)
        {
            cout<<"book number ( "<<i+1<<" ) detail : "<<endl;
            books[i].book_detail();
            cout<<"\n---------------------------\n";

        }
    }

    void borrow_a_book()
    {
        string user_name , book_name;
        int id ;
        cout<<"enter the user name : "<<endl;
        cin>>user_name;
        cout<<"\nenter the book name : "<<endl;
        cin>>book_name;
        cout<<endl;

        bool check_for_quantity = false;

        for(int i = 0;i<book_idx;i++)
        {
            if(books[i].name==book_name)
            {
                if(books[i].quantity==0)
                {
                    check_for_quantity=true;
                    break;
                }
                else if(books[i].quantity>0)
                {
                    books[i].quantity--;
                    books[i].amount_of_borrow++;
                    id=books[i].id;
                    books[i].user_borrow_this_bok[books[i].borrow_idx++]=user_name;

                }
            }
        }
        for(int i = 0;i<user_idx&&!check_for_quantity;i++)
        {
            if(users[i].name==user_name)
                users[i].id_of_borrowed_book[users[i].id_idx++]=id;
        }
        if(check_for_quantity)cout<<"the quauntity of that book is zero "<<endl;
    }

    void return_a_book()
    {
        string user_name , book_name;
        int id ;
        cout<<"enter the user name : "<<endl;
        cin>>user_name;
        cout<<"\nenter the book name : "<<endl;
        cin>>book_name;
        cout<<endl;



        for(int i = 0;i<book_idx;i++)
        {
            if(books[i].name==book_name)
            {

                books[i].quantity++;
                books[i].amount_of_borrow--;
                books[i].borrow_idx--;
            }
        }
        for(int i = 0;i<user_idx;i++)
        {
            if(users[i].name==user_name)
                users[i].id_of_borrowed_book[--users[i].id_idx]=0;
        }
    }


    void print_the_user()
    {
        cout<<"the users details are : "<<endl;
        for(int i= 0 ; i<user_idx;i++)
        {
            users[i].print_the_user();
            cout<<"\n-------------------------\n";
        }
        if(user_idx==0)
            cout<<"No user here"<<endl;
    }

    void who_borrow_this_book()
    {
        string book_name;
        cout<<"enter the book name : "<<endl;
        cin>>book_name;
        cout<<endl;

        for(int i = 0;i<book_idx;i++)
        {
            if(books[i].name==book_name)
            {
                for(int j=0;j<books[i].borrow_idx;j++)
                    cout<<books[i].user_borrow_this_bok[j]<<endl;
            }
            break;
        }




    }
};



int main()
{

   fast();

   library_system obj;
   obj.menu();





    return 0;

}







