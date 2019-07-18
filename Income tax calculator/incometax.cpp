#include<iostream>
#include<conio.h>
#include<fstream>
#include<iomanip>
#include<windows.h>
#include<string.h>

using namespace std;
//class



class it  //base class for inheritance
{ 
public:
		int tax;
	int	itax(int sal)//constructor with one parameter//For people with age below 60
	{
	
		if (sal <= 250000)
		{
			cout << "\nTotal Income does not exceed Rs. 2,50,000\n";
		}
		else if ((sal>250000) && (sal <= 500000))
		{
			cout << "\n Income is is between range Rs 250k-500k\n" << "Tax is 10% of total salary\n";
			tax= sal*(.10);
			return tax;
		}
		else if ((sal>500000) && (sal <= 1000000))
		{
			cout << "\nTotal Income is is between range Rs 500k-1000k\n" << "Tax is 20% of total salary\n";
			tax= sal*(.20);
			return tax;
		}
		else
			cout << "\nTotal Income exceed Rs.1000k\n" << "Tax is 30% of total salary\n";
			tax= sal*(.30);
			return tax;
	}

	int itax(int,int sal)//constructor with two parameter for overloading//age 60-80
	{
		if(sal<300000)
		{
		return 0;
		
		}
		else 
		{
			it i;
			i.itax(sal);
		}
	}
	int itax(float,int,int sal )// constructor with three parameter for overloading
	{
		if(sal<500000)
		{
			cout<<"Age > 80:";
		return 0;
		}
		else
		{
		it i;
		i.itax(sal);	//object for constructor with single parameter
	}}
	
};


class below : public it // derived class below inheriting itax class in public access
{

public:
	below(int sal)//calls base class's constructor with one parameter
	{	
		it i;
		i.itax(sal);
		system("cls");
		}
	//getch();
};


class middle : public it
{
public:
	middle(int sal) 
	{	
	it i;	
	 i.itax (0,sal);
	 system("cls");
	}

};
class high : public it
{

public:
	high(int sal)  
	{
		cout<<"Above 80";
		it i;
	i.itax (1.5,1, sal);	
	}

};

class citizen : public it
{
	protected:
	int id;
	char name[100];
	char ads[200];
	char occ[100];
	int age;
	int sal;
public:
	   	friend void intro(citizen c1)
       {
       	   cout<<"..........................................................................................................................\n";
       	   cout<<"                                 "<<"welcome to income tax calculator\n";
       	   cout<<".........................................................................................................................";
       }
	void getd();
	void disp();
     void cal();	
	void show_tabular();
	int retidno();
	int retit(int);
};
void citizen:: show_tabular()//table view for file
{
	cout <<"\n"<< id << setw(6) << "     " << name << setw(10) << occ << setw(10) << "" << setw(8)
		<< sal << setw(13) <<tax<< setw(10) <<age << setw(4) << "   " << ads << setw(6) << " " << " " << endl;
}

int citizen::retidno()
{
	return id;
}

void citizen::getd()// gets the details for citizen
{
	cout << "Enter details " << endl;
	cout << "Enter PAN Card Number:  ";
	cin >> id;
	cout << "Enter Name:  ";
	cin >> name;
	cout << "Enter Occupation:  ";
	cin >> occ;
	cout << "Enter address:  ";
	cin >> ads;
	cout << "Age: ";
	cin >> age;
	cout << endl << "Annual Income:";
	cin >> sal;
	it i;
	if (age <= 60)
	{
		below t1(sal);
		tax=i.itax(sal);
	}
	else if (age > 60 &&  age<80)
	{
		middle g1(sal);
		tax=i.itax(sal);
	}
	else
		{
		high c1(sal);
		tax=i.itax(sal);
		}	
	cout<<"Tax="<<tax;
}
	
void citizen::disp()//display the citizen details
{
	cout << "\nPAN Card No.  : " << id;
	cout << "\nName    : " << name;
	cout << "\nOccupation :" << occ;
	cout << "\nAddress : " << ads;
	cout << "\nsalary : " << sal;
	if (age <= 60) { cout << "\nAge : " << "Normal citizen"; }
	if (age > 60 &&  age<80) { cout << "\nAge : " << "senior citizen"; }
	if (age >= 80) { cout << "\nAge : " << "Very senior citizen"; }
	cout << "\nTax : " << tax;
}

void write_citizen();	//write the record 
void display_all();	//read all records from 
void display_sp(int);	//accept idno and read record from binary file
//void modify_citizen(int);	//accept rollno and update record of binary file
void delete_citizen(int);	//accept rollno and delete selected records from binary file
void total();	//display all records in tabular format from binary file
void displ();		//display  menu
void entry_menu();

//    	function to write in file
void write_citizen()
{
	citizen st;
	ofstream outFile;
	outFile.open("citizen.dat", ios::binary | ios::app);
	st.getd();
	outFile.write((char *)&st, sizeof(citizen));
	outFile.close();
	cout << "\n\nCitizen record Has Been Created ";
	cin.ignore();
	_getch();
}

void display_all()
//    	function to read all records from file
{
	citizen st;
	ifstream inFile;
	inFile.open("citizen.dat", ios::out);
	if (!inFile)
	{
		cout << "File could not be open !! Press any Key...";
	   	_getch();
		return;
	}
	cout << "\n\n\n\t\tDISPLAY ALL RECORD !!!\n\n";
	while (inFile.read((char *)&st, sizeof(citizen)))
	{
		st.disp();
		cout << "\n\n====================================\n";
	}
	inFile.close();
	_getch();
}

void display_sp(int n) //    	function to read specific record from file || when PAN number provided
{
	citizen st;
	ifstream inFile;
	inFile.open("citizen.dat", ios::binary);
	if (!inFile)
	{
		cout << "File could not be open !! Press any Key...";
		_getch();
		return;
	}

	int flag = 0;
	while (inFile.read((char *)&st, sizeof(citizen)))
	{
		if (st.retidno() == n)
		{
			st.disp();
			flag = 1;
		}
	}
	inFile.close();
	if (flag == 0)
		cout << "\n\nrecord not exist";
	_getch();
}

void modify_citizen(int n) //    	function to modify record of file
{
	int found = 0;
	citizen st;
	fstream File;
	File.open("citizen.dat", ios::binary | ios::in | ios::out);
	if (!File)
	{
		cout << "File could not be open !! Press any Key...";
		_getch();
		return;
	}
	while (File.read((char *)&st, sizeof(citizen)) && found == 0)
	{
		if (st.retidno() == n)
		{
			int pos;
			st.disp();
			cout << "\n\nPlease Enter The New Details of Current Citizen" << endl;
			st.getd();
			pos = (-1)*sizeof(st);
			File.seekp(pos, ios::cur);
			File.write((char *)&st, sizeof(citizen));
			cout << "\n\n\t Record Updated";
			found = 1;
		}
	}
	File.close();
	if (found == 0)
		cout << "\n\n Record Not Found ";
	_getch();
}

void delete_citizen(int n)//    	function to delete record of file
{
	citizen st;
	ifstream inFile;
	inFile.open("citizen.dat", ios::binary);
	if (!inFile)
	{
		cout << "File could not be open !! Press any Key...";
		_getch();
		return;
	}
	ofstream outFile;
	outFile.open("Temp.dat", ios::out);
	inFile.seekg(0, ios::beg);
	while (inFile.read((char *)&st, sizeof(citizen)))
	{
		if (st.retidno() != n)
		{
			outFile.write((char *)&st, sizeof(citizen));
		}
	}
	outFile.close();
	inFile.close();
	remove("citizen.dat");
	rename("Temp.dat", "citizen.dat");
	cout << "\n\n\tRecord Deleted ..";
	_getch();
}

void total() //    	function to display full records
{
	citizen st;
	ifstream inFile;
	inFile.open("citizen.dat", ios::binary);
	if (!inFile)
	{
		cout << "File could not be open !! Press any Key...";
		_getch();
		return;
	}
	cout << "\n\n\t\tALL Citizen RECORDS \n\n";
	cout << "==============================================================================\n";
	cout << "PAN No.   Name      Occupation       Salary        Tax       Age    address     " << endl;
	cout << "==============================================================================\n";
	while (inFile.read((char *)&st, sizeof(citizen)))
	{
		st.show_tabular();
	}
	_getch();
	inFile.close();
}

void displ()  //    	function to display  menu
{
	char ch;
	int idno;
	system("cls");
	cout << "\n\n\n\tCitizen Information";
	cout << "\n\n\n\t1. Information of all recorded Citizen";
	cout << "\n\n\t2. Particular CItizen Info";
	cout << "\n\n\t3. Back to Main Menu";
	cout << "\n\n\n\tEnter Choice (1/2/3)? ";
	cin >> ch;
	system("cls");
	switch (ch)
	{
	case '1':total(); break;
	case '2':cout << "\n\n\tEnter PAN Card Number Of Citizen : ";
		cin >> idno;
		display_sp(idno); break;
	case '3':break;
	default:cout << "\a";
	}
}

//    	ENTRY / EDIT MENU FUNCTION
void entry_menu()
{
	system("cls");
	char ch;
	int num;
	system("cls");
	cout << "\n\n\n\tENTRY MENU";
	cout << "\n\n\t1.CREATE CITIZEN RECORD";
	cout << "\n\n\t2.DISPLAY ALL CITIZEN RECORDS";
	cout << "\n\n\t3.SEARCH CITIZEN RECORD ";
	cout << "\n\n\t4.MODIFY CITIZEN RECORD";
	cout << "\n\n\t5.DELETE CITIZEN RECORD";
	cout << "\n\n\t6.BACK TO MAIN MENU";
	cout << "\n\n\tPlease Enter Your Choice (1-6) ";
	cin >> ch;
	system("cls");
	switch (ch)
	{
	case '1':	write_citizen(); break;
	case '2':	display_all(); break;
	case '3':	cout << "\n\n\tPlease Enter The PAN Card No "; cin >> num;
		display_sp(num); break;
	case '4':	cout << "\n\n\tPlease Enter PAN Card Number "; cin >> num;
		modify_citizen(num);break;
	case '5':	cout << "\n\n\tPlease Enter PAN card number "; cin >> num;
		delete_citizen(num);break;
	case '6':	break;
	default:	cout << "\a"; entry_menu();
	}
}
int main()
{
	citizen c1;
	system("cls");
	char ch;
	do
	{
		system("cls");
		intro(c1);
		cout << "\n\n\n\tMAIN MENU";
		cout << "\n\n\t01. View All records";
		cout << "\n\n\t02. ENTRY/EDIT MENU";
		cout << "\n\n\t03. EXIT";
		cout << "\n\n\tPlease Select Your Option (1-3) ";
		cin >> ch;
		switch (ch)
		{
		case '1': displ();
			break;
		case '2': entry_menu();
			break;
		case '3':
			break;
			case '4': system(" del citizen.dat");
			break;
		default:cout << "\a";
		}
	} while (ch != '3');
	return 0;
}


