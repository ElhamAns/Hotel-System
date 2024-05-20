//--------------------------------------------
//----------------- Group1--------------------
//----------Elham Alansari 2210004022---------
//----------Ghada Alqahtani 2210005548--------
//----------Maha Baageel 2210002540-----------
//----------Reiman Almohana 2210003337--------
//----------Jana Almutairi 2210002877---------
//--------------------------------------------

#include<iostream>
#include<string>
#include<fstream>
#include <sstream>
#include <ctime>
using namespace std;

// Define Structs {customer, employee}
struct customer_details
{
    int id;
    string name;
    int age;
    string gender;
    int nights;
    int bill;
    int room_id;
};


struct employee_details
{
    int id;
    string name;
    int age;
    string gender;
    string job;
    double salary; // in months
    double WorkingTime; // in hours
};

//files name
string customer_file="customer_info.txt";
string modificationDetailsCustomerFile = "update_details_customer.txt";
string employee_file="employee_info.txt";
string modificationDetailsEmployeeFile = "update_details_employee.txt";


// customers functions
void displayMenu_cus();
void operation(customer_details customer[], int&);
void sort_fun(customer_details customer[], int counter);
int binarySearch(customer_details* arr, int l, int r, int x);
void display_info(customer_details customer[], int index);
void addcustmer(int& counter);
void load_data(string fileName , customer_details customer[], int& counter);
void update_file(customer_details customer[], int& counter);

// Employee functions
void displayMenu_emp();
void operation(employee_details employee[], int&);
void sort_fun(employee_details employee[], int counter);
int binarySearch(employee_details* arr, int l, int r, int x);
void display_info(employee_details employee[], int index);
void addemp(int& counter);
void load_data(string fileName , employee_details customer[], int& counter);
void update_file(employee_details employee[], int& counter);

// Initialise array of strcuts
customer_details *customer;     // global & user Input
employee_details *employee;


int cust_file_size = 0;
int emplo_file_size = 0;

int total_customer_bill=0;
int customer_added_session=0;
int employee_added_session=0;
int customer_bill_session=0;
int available_rooms=0;


int  main()
{
    
    int choice = 0;
    int employee_counter = 0;
    int customer_counter = 0;
    

    do {
        
        cout << "Choose from the following:"<< endl <<  "(1) Customer Page." << endl << "(2) Employee Page." << endl << "(0) EXIT." << endl;
        cin >> choice;
        cout <<endl;

        if (choice == 1) {
            ifstream cus_info (customer_file.c_str());

            if( cus_info.peek() == ifstream::traits_type::eof() ){ //is it empty??
                cus_info.close();
                
                cout << "How many rooms do you have in your hotel? "<< endl;
                cin >> cust_file_size;
                customer = new customer_details[cust_file_size];   // to let the array accepts the size from the user
                
                // to write in the file the size Customer array
                ofstream customer_file_size;
                customer_file_size.open(customer_file.c_str(),ios::app);
                customer_file_size << cust_file_size ;
                customer_file_size.close();
            }
            
            
            else if(customer_counter == 0){        // The array must be filled with value from the file
                string size;
                getline(cus_info, size);        // return the first line --> which is the size of the array
                
                stringstream ss;
                ss << size;
                ss >> cust_file_size;
                //cout << "size= " << size << endl;
                
                // to transfer the size from a string to an integer
                int size_int;
                stringstream str_to_int;
                str_to_int << cust_file_size;
                str_to_int >> size_int;
                
                customer = new customer_details[size_int];
                
                load_data(customer_file, customer, customer_counter);
                cus_info.close();
                
            }
            customer_added_session=0;
            customer_bill_session=0;
            operation(customer, customer_counter);    // must start always
        }
        
        
        else if (choice == 2) {
            ifstream emp_info (employee_file.c_str());

            if( emp_info.peek() == ifstream::traits_type::eof() ){ //is it empty??
                emp_info.close();
                

                cout << "How many employees work in the hotel? "<< endl;
                cin >> emplo_file_size;
                employee = new employee_details[emplo_file_size];            // to let the array accepts the size from the user
                
                // to specify how many employee in the array
                ofstream employee_file_size;
                employee_file_size.open(employee_file.c_str(),ios::app);
                employee_file_size << emplo_file_size ;
                employee_file_size.close();
            }
            
            else if ( employee_counter == 0){
                string size;
                getline(emp_info, size);        // return the first line --> which is the size of the array
                //cout << "size= " << size << endl;
                
                // to transfer the size from a string to an integer
                int size_int;
                stringstream ss;
                ss << size;
                ss >> size_int;
                
                employee = new employee_details[size_int];
                
                load_data(employee_file, employee, employee_counter);
                emp_info.close();

            }
            employee_added_session=0;
            operation(employee, employee_counter); //must start always
        }
        else if (choice !=1  && choice != 2 && choice != 0) {
            cout << "You have chosen a Wrong Number." << endl;
        }

    } while (choice != 0);


    return 0;
}


// Display manu functions ------------------------------------------------

void displayMenu_cus()
{
    cout << "\n ----------------------------------------- \n";
    cout << "\n Welcome to Group1 Hotel. \n";//hotel name
    cout << "\n ----------------------------------------- \n";
    cout << "\n Enter the number of operation as follow below: \n ";
    cout << "\n *  1. Register a new customer. \n";
    cout << "\n *  2. Search for a specific customer. \n ";
    cout << "\n *  3. Update existing record. \n";
    cout << "\n *  4. Delete existing record. \n ";
    cout << "\n *  5. Sort by room numbers. \n ";
    cout << "\n *  6. Display customer details. \n ";
    cout << "\n *  0. EXIT. \n";
}

void displayMenu_emp() {
    cout << " \n ----------------------------------------- \n";
    cout << " \n Welcome to Group1 Hotel. \n";//hotal name
    cout << "\n ----------------------------------------- \n";
    cout << "\n Enter the number of opearation as follow below: \n ";
    cout << "\n *  1. Register a new employee. \n";
    cout << "\n *  2. Search for specific a employee. \n ";
    cout << "\n *  3. Update existing record. \n";//read from file
    cout << "\n *  4. Delete existing record. \n ";//read from file
    cout << "\n *  5. Sort the ID of the employee. \n ";//read from file
    cout << "\n *  6. Display the employee details. \n ";
    cout << "\n *  0. EXIT. \n";
}



// Operation functions ------------------------------------------------

void operation(customer_details *customer, int& counter)
{
    int choice = 0;
    do {
        displayMenu_cus();
        cin >> choice;
        cout <<endl;

        switch (choice)
        {
            case 0:
            {
                ofstream mCFile;
                mCFile.open(modificationDetailsCustomerFile.c_str(), ios::app);
                mCFile<< "\n\nIn this session, "<<customer_added_session<<" customers added.\n";
                mCFile<< "In this session, "<<customer_bill_session<<" SAR money gained.\n";
                mCFile.close();
            }
                break;

            case 1:
            {
                if (cust_file_size==counter){
                    cout << "There is no rooms available.";
                }else{
                    customer_added_session++;
                    addcustmer(counter);
                }
                
                
            }
                break;

            case 2:
            {
                int Room_num = 0;
                cout << "Enter the Room Number of the customer you are searching for: ";
                cin >> Room_num;
                   cout <<endl;

                sort_fun(customer, counter);
                int result = binarySearch(customer, 0, counter + 1, Room_num);
                
                if (result == -1)
                    cout << "There is no customer in this room. ";
                    
                else
                {
                    cout << "Informations about the customer in room: " << customer[result].room_id << "." <<endl ;
                    cout <<endl;
                    display_info(customer, result);
                }

            }
                break;

            case 3:
            {
                   int room_id = 0;
                   string gender;
                   
                cout << "Enter the room number of the existing customer: ";
                cin >> room_id;
                cout <<endl;

                sort_fun(customer, counter);
                int result = binarySearch(customer, 0, counter + 1, room_id);

                

            	if(result > 0 || (result==0 && customer[0].room_id == room_id) )
                {
                    cin.ignore();
                    cout << "Enter new name: ";
                    getline(cin, customer[result].name);

                    cout << "\nEnter new age (numbers only): ";
                    cin >> customer[result].age;

                    do{
                        cout << "\nEnter new gender (Female , Male): ";
                        cin >> customer[result].gender;
                
                        gender = customer[result].gender;
                
                        if (gender != "female" && gender != "male" && gender != "Female" && gender != "Male" )
                        {
                            cout<< "Wrong input, you must enter (Female) or (Male).";
                        }
                
                    } while (gender != "female" && gender != "male" && gender != "Female" && gender != "Male");
            

                    cout << "\nEnter how many nights the customer wants to stay: ";
                    cin >> customer[result].nights;

                    customer[result].bill = customer[result].nights * 100;
                    
                    update_file(customer, counter);
            
                	cout<<" \n Data has updated successfully. \n";
                }
                else{
                	cout << "There is no customer in this room. ";
				}
                
            }
                break;

        
            case 4:
            {
                int delete_room, delete_index;
                
                if (counter > 0)
                {
                    cout << "Enter the customer room number you want to delete: ";
                    cin >> delete_room;

                    sort_fun(customer, counter);
                    delete_index = binarySearch(customer, 0, counter + 1, delete_room);

                    if (delete_index == -1)
                    {
                        cout << "There is no customer in this room. ";
                    }
                
                    else
                    {
                        ofstream mCFile;
                        mCFile.open(modificationDetailsCustomerFile.c_str());

                        for (int j = delete_index; j < counter - 1; j++)
                        {
                            customer[j].id = customer[j + 1].id;
                            customer[j].name = customer[j + 1].name;
                            customer[j].age = customer[j + 1].age;
                            customer[j].gender = customer[j + 1].gender;
                            customer[j].nights = customer[j + 1].nights;
                            customer[j].room_id = customer[j + 1].room_id;
                            customer[j].bill = customer[j + 1].bill;
                        }
                        counter--;
                        
                        customer_bill_session-=customer[delete_index].bill;
                        available_rooms= cust_file_size - counter;
                        

                        // current date/time based on current system
                            time_t now = time(0);
                           
                           // convert now to string form
                           char* dt = ctime(&now);
                    
                        update_file(customer, counter);            // TO update the file
                        mCFile<<"The last modification to the Customer Details File was made on:  "<<dt<<endl;
                         mCFile<< "You just deleted a customer.\n";
                 
                        
                         mCFile<<"The total number of Customer Records are: " <<counter<<endl;
                         mCFile<<"The total money gained is: " <<total_customer_bill<<" SAR\n";
                         mCFile<<"Rooms available: "<< available_rooms;
                         mCFile.close();
                    
                        cout<<" \n Data has deleted successfully. \n";
                    }
                }
            
                else
                {
                    cout << "There is no customer to delete. ";
                }
                
            }
                break;

            case 5:
            {
                if(counter < 2)
                {
                    cout << "The Customers' Rooms list has only "<< counter << " room, so it cannot be ordered." <<endl;
                }
            
                else
                {
                    sort_fun(customer, counter);
                    cout << "The Customers\'s Rooms list has been sorted." << endl;
                }
                
            }
                break;

            case 6:
            {
                for (int i = 0; i < counter; i++)
                {
                     display_info(customer, i);
                     
                }
                
            }
                break;
                        
        default:
            cout << "Wrong value.";
        }




    } while (choice != 0);
}


void operation(employee_details *employee, int& counter) {
    int choice = 0;
    do {
        displayMenu_emp();
        cin >> choice;
        cout <<endl;

        switch (choice)
        {
            case 0:{
                ofstream mEFile;
                mEFile.open(modificationDetailsEmployeeFile.c_str(), ios::app);
                mEFile<< "\n\nIn this session, "<<employee_added_session<<" employees added.\n";
                mEFile.close();
            }
                break;

            case 1:
            {
                if (emplo_file_size==counter){
                    cout << "There is no jobs available.";
                }else{
                    employee_added_session++;
                    addemp(counter);
                }
                
              }
              break;

            

            case 2:
            {
                int id = 0;
                cout << "Enter the ID of the employee you are searching for: ";
                cin >> id;

                sort_fun(employee, counter);
                int result = binarySearch(employee, 0, counter + 1, id);
                
                if (result == -1)
                    cout << "There is no employee in this hotel. ";
                    
                else
                {
                    cout << "Informations about the employee with the ID: " << employee[result].id << "." << endl;
                    cout <<endl;
                    display_info(employee, result);
                }
            }
                break;
            

            case 3:
            {
                int id = 0;
                double rate = 60, days = 30;
                string gender;
            
                cout << "Enter the existing the employee ID: ";
                cin >> id;

                sort_fun(employee, counter);
                int result = binarySearch(employee, 0, counter + 1, id);


                if(result > 0 || (result==0 && employee[0].id == id) )
                {
                    cin.ignore();
                    cout << "Enter new name: ";
                    getline(cin, employee[result].name);
                

                    cout << "\nEnter new age (numbers only): ";
                    cin >> employee[result].age;

                    do{
                        cout << "\nEnter new gender (Female , Male): ";
                        cin >> employee[result].gender;
                
                        gender = employee[result].gender;
                
                        if (gender != "female" && gender != "male" && gender != "Female" && gender != "Male" )
                        {
                            cout<< "Wrong input, you must enter (Female) or (Male).";
                        }
                
                    } while (gender != "female" && gender != "male" && gender != "Female" && gender != "Male");
            


                    cout << "\nEnter new position title: ";
                    cin >> employee[result].job;

                    cout << "\nEnter new working hours (per day): ";
                    cin >> employee[result].WorkingTime;

                    employee[result].salary = (employee[result].WorkingTime * rate) * days;
                    
                    cout<<" \n Data has updated successfully. \n";
                    update_file(employee, counter);
                }
                
                else{
                	cout << "There is no employee with this ID. ";
				}
            
                
            }
                break;
        

            case 4:
            {
                int delete_id, delete_index;
                if (counter > 0)
                {
                    cout << "Enter the employee number you want to delete: ";
                    cin >> delete_id;

                    sort_fun(employee, counter);
                    delete_index = binarySearch(employee, 0, counter + 1, delete_id);

                    if (delete_index == -1)
                    {
                        cout << "There is no employee with this ID. ";
                    }
                
                    else
                    {   ofstream mEFile;
                        mEFile.open(modificationDetailsEmployeeFile.c_str());

                        for (int j = delete_index; j < counter - 1; j++)
                        {
                            employee[j].id = employee[j + 1].id;
                            employee[j].name = employee[j + 1].name;
                            employee[j].age = employee[j + 1].age;
                            employee[j].gender = employee[j + 1].gender;
                            employee[j].job = employee[j + 1].job;
                            employee[j].WorkingTime = employee[j + 1].WorkingTime;
                            employee[j].salary = employee[j + 1].salary;
                        }
                        counter--;
                        update_file(employee, counter);
                    
                        cout<<" \n Data has deleted successfully. \n";
                    
                        

                        // current date/time based on current system
                            time_t now = time(0);
                           
                           // convert now to string form
                           char* dt = ctime(&now);
                           mEFile<<"The last modification to the Employee Details File was made on:  "<<dt<<endl;
                            mEFile<< "You just deleted an employee.\n";
                    
                           
                            mEFile<<"The total number of employee records are: " <<counter<<endl;
                            
                            mEFile.close();
                    }
                }
            
                else
                {
                    cout << "There is no employees to delete. ";
                }
                
            }
                break;

            case 5:
            {
                if(counter < 2)
                {
                    cout << "The employee list has only "<< counter << " employee, so it cannot be ordered." <<endl;
                }
            
                else
                {
                    sort_fun(employee, counter);
                    cout << "Employee list have been sorted." << endl;
                }
            
            }
                break;

            case 6:
            {
                for (int i = 0; i < counter; i++)
                {
                    
                 display_info(employee, i);
                 
                }
            
            }
                break;


            default:
                cout << "Wrong value.";
        }


    } while (choice != 0);
}


// display info functions ------------------------------------------------

void display_info(customer_details customer[], int index)
{
    cout << "ID: " << customer[index].id << endl;
    
    cout << "Name: " << customer[index].name << endl;

    cout << "Age: " << customer[index].age << endl;

    cout << "Gender: " << customer[index].gender << endl;

    cout << "Number of nights the customer will stay: " << customer[index].nights << endl;

    cout << "total bill: " << customer[index].bill<< endl;
    
    cout << "Room Number: " << customer[index].room_id << endl;

    cout << endl;

}

void display_info(employee_details employee[], int index)
{

    
    cout << "ID: " << employee[index].id << endl;

    cout << "Name: " << employee[index].name << endl;

    cout << "Age: " << employee[index].age << endl;

    cout << "Gender: " << employee[index].gender << endl;

    cout << "Your job is: " << employee[index].job << endl;

    cout << "Your working hours are: " << employee[index].WorkingTime << endl;

    cout << "Salary: " << employee[index].salary << endl;

    cout << endl;

}


// sort functions ------------------------------------------------

void sort_fun(customer_details customer[], int counter) {
    bool ordered = false;
    customer_details temp;

    if (counter < 2)
        cout<<""<<endl;
        
    else {
        for (int i = 0; i < counter - 1 && ordered == false; i++) {
            ordered = true;
            for (int j = 0; j < counter - 1; j++) {

                if (customer[j].room_id > customer[j + 1].room_id) {
                    ordered = false;
                    temp = customer[j];
                    customer[j] = customer[j + 1];
                    customer[j + 1] = temp;
                }
            }
        }
    }
}

void sort_fun(employee_details employee[], int counter) {
    bool ordered = false;
    employee_details temp;

    if (counter < 2)
        cout<<""<<endl;
        
    else {
        for (int i = 0; i < counter - 1 && ordered == false; i++) {
            ordered = true;
            
            for (int j = 0; j < counter - 1; j++) {

                if (employee[j].id > employee[j + 1].id) {
                    ordered = false;
                    temp  = employee[j];
                    employee[j] = employee[j + 1];
                    employee[j + 1] = temp;
                }
            }
        }
    }
}


// search functions ------------------------------------------------

int binarySearch(customer_details* arr, int first, int last, int room_num)//note
{
    // when the array just has one element
    if(last==2){  // last==2 because it's been called after it got increased by 1 (one element + 1) = 2
        return 0;
        
    }
    
    // when the array has got more than one element
    else{
    
        if (last >= first) {
        int mid = first + (last - first) / 2;

        // If the element is present at the middle
        // itself
        if (arr[mid].room_id == room_num)
            return mid;

        // If element is smaller than mid, then
        // it can only be present in left subarray
        if (arr[mid].room_id > room_num)
            return binarySearch(arr, first, mid - 1, room_num);

        // Else the element can only be present
        // in right subarray
        return binarySearch(arr, mid + 1, last, room_num);
    }

    // We reach here when element is not
    // present in array
    
    return -1;
    }
    
}


int binarySearch(employee_details* arr, int first, int last, int id)//note
{
        // when the array just has one element
    if(last==2){  // last==2 because it's been called after it got increased by 1 (one element + 1) = 2
        return 0;
    }
    
    else{
        
        if (last >= first) {
        int mid = first + (last - first) / 2;

        // If the element is present at the middle
        // itself
        if (arr[mid].id == id)
            return mid;

        // If element is smaller than mid, then
        // it can only be present in left subarray
        if (arr[mid].id > id)
            return binarySearch(arr, first, mid - 1, id);

        // Else the element can only be present
        // in right subarray
        return binarySearch(arr, mid + 1, last, id);
    }

    // We reach here when element is not
    // present in array
    return -1;
    }
    
}


// add functions ------------------------------------------------

void addcustmer(int& counter)
{
 
 ofstream outFile;
 ofstream mCFile; //this is for modification customer file
 outFile.open(customer_file.c_str(),ios::app);
 mCFile.open(modificationDetailsCustomerFile.c_str());
 
 if(outFile.is_open() )
 {
           
     
    int digit_count=0;
    string gender;
     
    do{
         int temp;
         digit_count=0;
         cout << "Enter the customer ID: ";
         cin >> customer[counter].id;

         // to make sure that id has 5 digits
         temp= customer[counter].id;
         
         while(temp != 0)
         {
             // Increment counter
             digit_count++;
             // Remove last digit of 'temp'
             temp /= 10;
         }
         
         if(digit_count !=5)
         {
             cout <<endl;
            cout<< "Wrong value, ID must consist of 5 digits.\n";
            cout <<endl;
         }

    } while (digit_count!= 5);

      
     
    outFile << endl << customer[counter].id;
     
    cin.ignore();
     
     
        cout << "\nEnter the customer name: ";
        getline(cin,customer[counter].name);
        outFile<< endl << customer[counter].name <<".";
     
     
        cout << "\nEnter the customer age (numbers only): ";
        cin >> customer[counter].age;
        outFile<< endl << customer[counter].age;
     
     
     do{
            cout << "\nEnter the customer gender (Female , Male): ";
            cin >> customer[counter].gender;
            
            gender =customer[counter].gender;
            
            if (gender != "female" && gender != "male" && gender != "Female" && gender != "Male" )
                cout<< "Wrong input, you must enter (Female) or (Male).";
                
     } while (gender != "female" && gender != "male" && gender != "Female" && gender != "Male" );
     
        outFile<< endl << customer[counter].gender;
     
     
        cout << "\nEnter how many nights the customer wants to stay: ";
        cin >> customer[counter].nights;
        outFile<< endl << customer[counter].nights;
        
        
        
        int check_room;
        do{
            cout << "\nEnter The room number: ";
            cin >> check_room;
            
            sort_fun(customer, counter);
            int result = binarySearch(customer, 0, counter + 1, check_room);
                        
            if(result == -1){
                break;
            }
            
            if (result == 0){
                
                if(check_room != customer[0].room_id){        // when there is only one elmenet in the struct, binarySearch will return 0
                    break;                                    // so we compare if either the first element in the array equals the one user has entered
                }
            }
            
            cout<<"\nWrong value, there is a customer in this room. ";
            
        }while(true);
        
        

        customer[counter].room_id=check_room;
        outFile<< endl << customer[counter].room_id;
     
     
        customer[counter].bill = customer[counter].nights * 100;
        outFile<< endl << customer[counter].bill;
        customer_bill_session+=customer[counter].bill;
        total_customer_bill+=customer[counter].bill;
        counter++;
        available_rooms= cust_file_size - counter;

        // current date/time based on current system
            time_t now = time(0);
           
           // convert now to string form
           char* dt = ctime(&now);
           mCFile<<"The last modification to the Customer Details File was made on:  "<<dt<<endl;
           
    
           
            mCFile<<"The total number of Customer Records are: " <<counter<<endl;
            mCFile<<"The total money gained is: " <<total_customer_bill<<" SAR\n";
            mCFile<<"Rooms available: "<< available_rooms;
          

          
}

    outFile.close();
    mCFile.close();
    cout<<" \n Data Saved successfully. \n";

}


void addemp(int& counter)
{
    ofstream outFile;
    ofstream mEFile;
    outFile.open(employee_file.c_str(),ios::app);
    mEFile.open(modificationDetailsEmployeeFile.c_str());
     if(outFile.is_open() )
     {
        double rate = 60, days = 30;
        int digit_count=0;
        string gender;
        
        do{
            int temp;
            digit_count=0;
            int id_input;
            cout << "Enter the employee ID: ";
            cin >> id_input;
            
            
            // to make sure that id has 5 digits
            temp= id_input;
            while(temp != 0) {
                // Increment counter
                digit_count++;
                // Remove last digit of 'temp'
                temp /= 10;
                }

                    
            sort_fun(employee, counter);
            int result = binarySearch(employee, 0, counter + 1, id_input);

            if(result == -1 && digit_count == 5){        //true condition
            	employee[counter].id = id_input;
                break;
            }
            
            
            
            else if (result == 0){
                if(id_input != employee[0].id && digit_count == 5){        // when there is only one elmenet in the struct, binarySearch will return 0
                	employee[counter].id = id_input;					  // so we compare if either the first element in the array equals the one user has entered
                    break;                                                   
                }
                
                if(digit_count != 5){
                    cout<< "\nWrong value, ID must consist of 5 digits and don't start with 0.\n";
                }
                if(id_input == employee[0].id){
                	cout<<"\nWrong value, there is an emplpoyee with the same ID. "<<endl;
				}
            }
            
            
            
            
            else{
            	if(result != -1){
            		cout<<"\nWrong value, there is an emplpoyee with the same ID. "<<endl;
				}
				
				if(digit_count != 5){
            		cout<< "Wrong value, ID must consist of 5 digits and don't start with 0.\n";
				}
                
            }
        } while (true);
        
            
            outFile << endl << employee[counter].id;
            
            cin.ignore();
            
            cout << "\nEnter the employee name: ";
            getline(cin, employee[counter].name);
            outFile << endl << employee[counter].name<<".";
            
                    
            cout <<  "\nEnter the employee age (numbers only): ";
            cin >> employee[counter].age;
            outFile << endl << employee[counter].age;
            
            
            do{
                cout << "\nEnter the gender of the employee (Female , Male): ";
                cin >> employee[counter].gender;
                
                gender =employee[counter].gender;
                
                if (gender != "female" && gender != "male" && gender != "Female" && gender != "Male")
                     cout<< "Wrong input, you must enter (Female) or (Male).";
                     
                } while (gender != "female" && gender != "male" && gender != "Female" && gender != "Male");
            
			outFile << endl << employee[counter].gender;
            
            
            cout << "\nEnter the position title: ";
            cin >> employee[counter].job;
            outFile << endl << employee[counter].job;
            
            
            cout << "\nEnter your working hours (per day): ";
            cin >> employee[counter].WorkingTime;
            outFile << endl << employee[counter].WorkingTime;
            
            
            employee[counter].salary = (employee[counter].WorkingTime * rate) * days;
            outFile << endl << employee[counter].salary;
            
            
            counter++;
            time_t now = time(0);
               
               // convert now to string form
            char* dt = ctime(&now);
            mEFile<<"The last modification to the Employee Details File was made on:  "<<dt<<endl;
            mEFile<<"\nThe total employees in the hotel: "<<counter<<endl;
         
     }
     outFile.close();
     mEFile.close();
     cout<<" \n Data Saved successfully. \n";
}


// load functions ------------------------------------------------

void load_data(string fileName , customer_details customer[], int& counter)
{
    string str;
    string full_name;
    string skip;
    ifstream read_info(customer_file.c_str());
    
    
    if (read_info.is_open()){
        
        while (! read_info.eof() ){    // to read all lines
        
              if (counter == 0){
                  read_info >> skip;            // To skip the array size which is located in the first line of the file
                  counter ++;
                  continue;
            }
            
            read_info>>customer[counter-1].id;        // to fill the array from the index counter - 1 --->
            
           
            getline(read_info, customer[counter-1].name, '.');
            
            // to delete the new line that "getline" function created
            for(int i=0;i<customer[counter-1].name.length();i++)
            if(customer[counter-1].name[i]=='\n') customer[counter-1].name.erase(customer[counter-1].name.begin()+i);
            
            read_info>>customer[counter-1].age;
            read_info>>customer[counter-1].gender;
            read_info>>customer[counter-1].nights;
            read_info>>customer[counter-1].room_id;
            read_info>>customer[counter-1].bill;
            
            //display_info(customer, counter-1);
            //cout<< "customer[counter-1].id= "<< customer[counter-1].id << endl;
            
            counter ++;
        }
    }
    
    else{
        cout << "Unable to open file.";
    }
              
    
    read_info.close();
    counter --;            // because the size of the array holds the first line.
 
}

void load_data(string fileName , employee_details employee[], int& counter)
{
    string str;
    string full_name;
    string skip;
    ifstream read_info(employee_file.c_str());
    
    
    
    if (read_info.is_open()){
        
        while (! read_info.eof() ){    // to read all lines
        
            if (counter == 0){
                read_info >> skip;            // To skip the array size which is located in the first line of the file
                counter ++;
                continue;
            }
            
            
            read_info>>employee[counter-1].id;       // to fill the array from the index counter - 1
            
            getline(read_info, employee[counter-1].name, '.');
           
              
    
            read_info>>employee[counter-1].age;
            read_info>>employee[counter-1].gender;
            read_info>>employee[counter-1].job;
            read_info>>employee[counter-1].WorkingTime;
            read_info>>employee[counter-1].salary;
           
            
            //display_info(employee, counter-1);
            //cout<< "employee[counter-1].id= "<< employee[counter-1].id << endl;
            
            counter ++;
        }
        
    }
    else{
        cout << "Unable to open file.";
    }
              
    read_info.close();
        counter --;            // because the size of the array holds the first line.
}


// updating files functions ------------------------------------------------------------

void update_file(customer_details customer[], int& counter) // *****************************************************
{
        
    ofstream temp_file_write;
    temp_file_write.open("temp.txt");
    temp_file_write << cust_file_size;
        
    for (int i = 0; i < counter; i++)
    {
        temp_file_write<< endl << customer[i].id;
        temp_file_write<< endl << customer[i].name <<".";
        temp_file_write<< endl << customer[i].age;
        temp_file_write<< endl << customer[i].gender;
        temp_file_write<< endl << customer[i].nights;
        temp_file_write<< endl << customer[i].room_id;
        temp_file_write<< endl << customer[i].bill;
        
    }
    temp_file_write.close();
    
    
    ofstream cus_info (customer_file.c_str());        //Remove + Write from begning
    ifstream temp_file_read("temp.txt");
    string line;
    
    bool size_index = true;
    
    while(getline(temp_file_read,line))
    {
        
        if(size_index)
        {                    // to save the size for the first time
            cus_info << line;
            size_index = false;
            continue;
        }
            
        cus_info << endl << line;
    }
     
//     temp_file_read>> endl >> cus_info; // to write

    cus_info.close();
    temp_file_read.close();
    
        
}


void update_file(employee_details employee[], int& counter)  // *****************************************************
{
        
    ofstream temp_file_write;
    temp_file_write.open("temp.txt");
    temp_file_write << emplo_file_size;
        
    for (int i = 0; i < counter; i++){
        temp_file_write<< endl << employee[i].id;
        temp_file_write<< endl << employee[i].name <<".";
        temp_file_write<< endl << employee[i].age;
        temp_file_write<< endl << employee[i].gender;
        temp_file_write<< endl << employee[i].job <<".";
        temp_file_write<< endl << employee[i].WorkingTime;
        temp_file_write<< endl << employee[i].salary;
        
    }
    temp_file_write.close();
    
    
    ofstream employee_info (employee_file.c_str());        //Remove + Write from begning
    ifstream temp_file_read("temp.txt");
    string line;
    
    bool size_index = true;
    
    while(getline(temp_file_read,line))
    {
        if(size_index)
        {                    // to save the size for the first time
            employee_info << line;
            size_index = false;
            continue;
        }
            
        employee_info << endl << line;
    }
     
//     temp_file_read>> endl >> employee_info; // to write

    employee_info.close();
    temp_file_read.close();
    
        
}




