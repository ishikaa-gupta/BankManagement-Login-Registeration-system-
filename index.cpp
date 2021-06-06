    #include<iostream>
    #include<string>
    #include<vector>
    #include<cstdlib>
    #include<fstream>
    using namespace std;
    
    #define MIN_BALANCE 1000
    
    class account
    {
        int accno;
        char name[50];
        int deposit;
        char type;
        static int acc;
    
        public:
        void create_account();
        void show_account() const;    
        void modify();
        void dep(int);
        void draw(int);
        void show_data() const;
        int get_accno() const;
        int get_deposit()const;
        char get_type() const;
    
    };
    
    int account:: acc=1;
    
    void account::create_account()
    {
        accno=acc++;
        cout<<"\n  Enter the Name of Account Holder: ";
        cin.ignore();
        cin.getline(name,50);
        cout<<"\n   Enter the Type of Account. Current or Savings (c/s): ";
        cin>>type;
        type=toupper(type);
        do{
            cout<<"\nEnter Initial Deposit Amount. (Must be greater than ₹1000/-): ";
            cin>>deposit;
            if(deposit<1000)
             cout<<"\nMinimum Deposit Amount is ₹1000/-";
        }while(deposit<MIN_BALANCE);
        cout<<"\n\n  **Account Successfully Created!** ";
        cout<<"\n Your Account Number is : "<<accno<<endl;
    }
    
    void account::show_account() const
    {
        cout<<"\n  Account No. :"<< accno;
        cout<<"\n  Account Holder Name : "<< name;
        cout<<"\n  Type of Account : "<<type;
        cout<<"\n  Balance Amount : "<< deposit;
    }
    
    void account::modify()
    {
        cout<<"\n  Account No. :" <<accno;
        cout<<"\n  Modify Account Holder's Name : ";
        cin.ignore();
        cin.getline(name,50);
        cout<<"\n  Modify Type of Account : ";
        cout<<"\n  Enter 'c' for Current and 's' of Savings Account";
        cin>>type;
        type=toupper(type);
        // cout<<"\n  Modify Balance Amount : ";
        // cin>> deposit;
         
    }
    
    void account::dep(int x)
    {
        deposit +=x;
    }
    
    void account::draw(int x)
    {
        deposit -=x;
    }
    
    void account::show_data () const
    {
        cout<< accno << setw(10) <<" "<<name <<setw(10) <<type<<setw(6)<< deposit<<endl;
    }
    
    int account::get_accno () const
    {
        return accno;
    }
    
    int account::get_deposit () const
    {
        return deposit;
    }
    
    char account::get_type() const
    {
        return type;
    }
    
    
    // function Declaration
    void write_account();
    void display(int);
    void modify_account(int);
    void delete_account(int);
    void display_all();
    void deposit_withdraw(int,int);
    
    
    void start()
    {


        int choice;
        int num;
        cout<<"        *** Bank System ***\n"<<endl;
        do{
    
            cout<<"\n      **Select One Option**"<<endl;
            cout<<"        1 Open New Account"<<endl;
            cout<<"        2 Deposit Amount"<<endl;
            cout<<"        3 Withdraw  Amount"<<endl;
            cout<<"        4 Balance Inquiry"<<endl;
            cout<<"        5 Show All Account Holders"<<endl;
            cout<<"        6 Close an Account"<<endl;
            cout<<"        7 Modify an Account"<<endl;
            cout<<"        8 Quit"<<endl;
    
            cout<<"Enter Your Selection : ";
            cin>>choice;
    
            switch(choice)
            {
            case 1 : write_account();
                    break;
            case 2 :cout<<"\n\n  Enter the Account No. : ";
                    cin>>num;
                    deposit_withdraw(num,1);
                    break;
            case 3 :cout<<"\n\n  Enter the Account No. : ";
                    cin>>num;
                    deposit_withdraw(num,2);
                    break;
            case 4 :cout<<"\n\n  Enter the Account No. : ";
                    cin>>num; 
                    display(num);
                    break;
            case 5 :display_all();
                    break;
            case 6 :cout<<"\n\n  Enter the Account No. : ";
                    cin>>num;
                    delete_account(num);
                    break;
            case 7 :cout<<"\n\n  Enter the Account No. : ";
                    cin>>num;
                    modify_account(num);
                    break;
            case 8 :cout<<"\n\n  **SYSTEM EXITED** ";
                    break;
            default: 
            cout<<"\n\nInvalid Choice";
            }
         
        }while (choice!=8); 
    
    }
    
    void write_account()
    {
        account ac;
        ofstream outFile;
        outFile.open("account.dat",ios::binary|ios::app);
        ac.create_account();
        outFile.write(reinterpret_cast<char*>(&ac), sizeof(account));
        outFile.close();
    }
    
    void display(int n)
    {
        account ac;
        bool flag=false;
        ifstream inFile;
        inFile.open("account.dat",ios::binary);
        if(!inFile)
        {
            cout<<"\n\n  File Could Not be Opened!!\n  Press any key...";
            return;
        }
        cout<<"\n  BALANCE DETAILS\n";
        while(inFile.read(reinterpret_cast<char*>(&ac),sizeof(account)))
        {
            if(ac.get_accno()==n)
            {
                ac.show_account();
                flag=true;
            }
        }
        cout<<endl;
        inFile.close();
        if(flag==false)
        cout<<"\n  Account Number Does Not Exist\n\n";
    }
    
    void modify_account(int n)
    {
        bool found=false;
        account ac;
        fstream File;
        File.open("account.dat",ios::binary | ios::in | ios::out);
        if(!File)
        {
            cout<<"\n\n  File Could Not be Opened!!\n  Press any key...";
            return;
        }
        while(!File.eof() && found==false)
        {
            File.read(reinterpret_cast<char*>(&ac),sizeof(account));
             if(ac.get_accno()==n)
             {
                 ac.show_account();
                 cout<<"\n  Enter The New Details of Account"<<endl;
                 ac.modify();
                 int pos=(-1) * static_cast<int>(sizeof(account));
                 File.seekp(pos,ios::cur);
                 File.write(reinterpret_cast<char*>(&ac),sizeof(account));
                 cout<<"\n\n  Record Updated";
                 found=true;
             }
        }
        File.close();
        if(found==false)
        cout<<"\n\n Record Not Found";
    }
    
    void delete_account(int n)
    {
        account ac;
        ifstream inFile;
        ofstream outfile;
        inFile.open("account.dat",ios::binary);
        if(!inFile)
        {
            cout<<"\n  File Could Not be Opened !! Press any key...";
            return;
        }
        outfile.open("Temp.dat",ios::binary);
        inFile.seekg(0,ios::beg);
        while(inFile.read(reinterpret_cast<char*> (&ac),sizeof(account)))
        {
            if(ac.get_accno()!=n)
            {
                outfile.write(reinterpret_cast<char*> (&ac),sizeof(account));
            }
        }
        inFile.close();
        outfile.close();
        remove("account.dat");
        rename("Temp.dat","account.dat");
        cout<<"\n\n  *Account Deleted*";
    
    }
    
    void display_all()
    {
        account ac;
        ifstream inFile;
        inFile.open("account.dat",ios::binary);
        if(!inFile)
        {
            cout<<"\n  File Could Not be Opened !! Press any key...";
            return;
        }
        cout<<"\n\n**Account Holder List**\n";
        cout<<"\nA/C NO.     NAME    TYPE    BALANCE\n";
       
        while(inFile.read(reinterpret_cast<char*> (&ac),sizeof(account)))
        {
            ac.show_data();
            cout<<endl;
        }
        inFile.close();
    }
    
    void deposit_withdraw(int n, int option)
    {
        int amt;
        bool found = false;
        account ac;
        fstream File;
        File.open("account.dat", ios::binary | ios::in | ios::out);
        if(!File)
        {
            cout<<"\n\nFile Could Not be Opened !! Press any key...";
            return;
        }
        while(!File.eof() && found==false)
        {
            File.read(reinterpret_cast<char*> (&ac),sizeof(account));
            if(ac.get_accno()==n)
            {
                ac.show_account();
                if(option==1)
                {
                    cout<<"\n\n  TO DEPOSIT AMOUNT";
                    cout<<"\n\n  ENTER THE AMOUNT TO BE DEPOSITED ";
                    cin>>amt;
                    ac.dep(amt);
                }
                if(option==2)
                {
                    cout<<"\n\n  TO WITHDRAW AMOUNT";
                    cout<<"\n\n  ENTER THE AMOUNT TO BE WITHDRAWN ";
                    cin>>amt;
                    int bal=ac.get_deposit()-amt;
                    if(bal< MIN_BALANCE )
                        cout<<"\n\n INSUFFICIENT BALANCE";
                    else
                        ac.draw(amt);
                }
    
                int pos=(-1) * static_cast<int>(sizeof(ac));
                File.seekp(pos,ios::cur);
                File.write(reinterpret_cast<char*>(&ac),sizeof(account));
                cout<<"\n\n RECORD UPDATED\n\n";
                found=true;
            }
        }
        File.close();
        if(found == false)
        cout<<"\n\n RECORD NOT FOUND";
    }
    
 //Registeration system

    do{
    cout<<"Choose 1 : to Register \nChoose 2 : Login"<<endl;
    cin>> choice;
    if(choice!=1 && choice!=2)
    {
        cout<< "Invalid Choice\nPlease Enter Again"<<endl;
    }
    }while(choice!=1 && choice!=2 );

    if(choice==1)
    {
      cout<<"Enter your User Id"<<endl;
      cin>>id;
      cout<<"Enter Your Password"<<endl;  
      cin>>pw;

      ofstream file;
      file.open("data_"+id+".txt");
      file <<id<<endl<<pw<<endl;
      file.close();
      cout<<"You Have Been Successfully Registered !"<<endl;

      cout<<"\n LOGIN TO YOU ACCOUNT "<<endl;
      Logged();
    }
    else{
        Logged();
    }
 }
