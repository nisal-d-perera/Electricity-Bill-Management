#include <iostream>
#include <fstream>
#include <ctime>

using namespace std;

int main()
{
    string months[] = {"No records yet","January", "February", "March","April", "May", "June", "July", "August", "September", "October", "November", "December"};
    int month_number = 0;


    string month_name;
    string account_number;
    string text;
    fstream file1,file2;

    int LastMonth =0 ;
    double lastreading = 0;
    double meter_reading = 0;
    double Charge = 0;
    const double tax = 50;

    bool flag;

    do{
    flag = false;
    cout << "Enter the Account Number : ";
    cin >> account_number;
    cout <<endl;

    // creating a file using a variable entered.
    file1.open(account_number+".txt", ios::in);

    if(!file1){
        cout << "Invalid Account Number" << endl;
        flag = true;
       }
    }while(flag);



    // get line by line from file
    getline(file1,text);
    cout << "Owner      :"+text << endl;

    getline(file1,text);
    cout << "Address    :"+text << endl <<endl;

    file1.close();

    cout << endl;

    bool flag1 ;
    do {
    flag1=true;
    cout << "Enter the month number :  ";
    cin >> month_number;
    if (month_number > 0 && month_number < 13) {
        flag1=false;
        }
    }while(flag1);

    file2.open(account_number+"history.txt", ios::in);

    while(getline(file2,text)){
        if (text == months[month_number -1] ){

            cout << "LastMonth :" + text << endl;

            getline(file2,text);
            lastreading = stoi(text);// convert string to int
            cout << "Last month meter reading : " << lastreading << endl;

            getline(file2,text);
            cout << "Last month charge : " + text << endl;
        }
    }

    file2.close();

    cout << "Enter the meter reading : ";
    cin >> meter_reading;

    double CurrentUsage = meter_reading - lastreading;

    if(CurrentUsage >= 1 && CurrentUsage <=30 ){
       Charge = CurrentUsage * 7.85;
        }
        else if(CurrentUsage >= 31 && CurrentUsage <=60){
            Charge = (30 * 7.85) + (CurrentUsage - 30) * 7.85 ;
                }
                else if(CurrentUsage >= 61 && CurrentUsage <=90){
                    Charge = (60 * 7.85) + (CurrentUsage - 60) * 10.00;
                        }
                        else if(CurrentUsage >= 91 && CurrentUsage <=120){
                            Charge = (60 * 7.85) + 30 * 10.00 + (CurrentUsage - 90) * 27.75;
                            }
                            else if(CurrentUsage >= 121 && CurrentUsage <=180){
                                Charge = (60 * 7.85) + 30 * 10.00 + 30 * 27.75 + (CurrentUsage - 120) * 32.00;
                                }
                                else{
                                    Charge = (60 * 7.85) + 30 * 10.00 + 30 * 27.75 + 60 * 32.00 + (CurrentUsage - 180) * 45.00;
                                    }


    cout << "\n\t\t Electricity Bill for the month of " << months[month_number] << " \n" << endl;

    //declaring argument for time()
    time_t tt;
    //declaring variable to store return value of localtime()
    struct tm * ti;
    //applying time
    time(&tt);
    //using localtime()
    ti = localtime(&tt);
    cout << "Day date and time is :" << asctime(ti);

    cout <<  "\nYour current month usage is : "<<CurrentUsage << endl << endl;
    cout <<  "The payment for the meter reading Rs. " << Charge << endl << endl;
    cout << "Tax for the month : " << tax << endl << endl;
    cout <<  "Total payment for the month is Rs. " << Charge + tax << endl;

    ofstream file3 ;
    file3.open(account_number+"history.txt", fstream::app);
    file3 << months[month_number] << endl;// insert values to file of current month
    file3 << meter_reading << endl;
    file3 << Charge << endl;
    file3 << endl;
    file3.close();

    return 0;
}
