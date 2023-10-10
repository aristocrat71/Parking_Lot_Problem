#include<iostream>
#include<string>
#include<vector>
#include<fstream>

using namespace std;

class Car {
    string reg_no;
    string color;
    friend class Parking;
    public:
        void displayInfo()
        {
            cout<<"Reg No: "<<this->reg_no<<"\nColor: "<<this->color<<endl;
        }
};

class Parking {
    friend class Car;
    Car cars[50];
    int slot[50] = {0}; //If slot 0 it is free; 1 it is occupied
    public: 
        void park(string _reg_no, string _color)
        {
            for(int i=0;i<50;i++)
            {
                if(cars[i].reg_no == _reg_no) {
                    cout<<"Registered number already present."<<endl;
                    return;
                }
            }

            for(int i=0;i<50;i++)
            {
                if(slot[i] == 0) {
                    slot[i] = 1;
                    cars[i].reg_no = _reg_no;
                    cars[i].color = _color;
                    break;
                }
            }
        }

        void unpark(string _reg_no)
        {   
            for(int i=0;i<50;i++)
            {
                if(slot[i] == 1 && cars[i].reg_no == _reg_no) {
                    slot[i] = 0;
                    cout<<"Unparked"<<endl;
                    return;
                }
            }
            cout<<"Car not present."<<endl;
        }

        void findSlot(int key)
        {
            if(slot[key] == 0)
                cout<<"Slot is empty"<<endl;
            else
                cars[key].displayInfo();
        }

        void findNumber(string _reg_no)
        {
            for(int i =0;i<50;i++) {
                if(slot[i] == 1 && cars[i].reg_no == _reg_no){
                    cars[i].displayInfo();
                    return;
                }
            }
            cout<<"Not Found."<<endl;
        }

        void find_color(string _color)
        {
            for(int i =0;i<50;i++) {
                if(slot[i] == 1 && cars[i].color == _color){
                    cars[i].displayInfo();
                }
            }    
        }

        void promptCmd() {
            string command;
            bool flag = true;
            cout<<"To start create a parking lot.\nUse the command -create_parking_lot\n";
            while(true)
            {
                cout<<"> ";
                getline(cin, command);
                if(command == "create_parking_lot") {
                    flag = true;
                    continue;
                }
                if(flag) {
                    if(command.substr(0, 4) == "park")
                    {
                        park(command.substr(5, 9), command.substr(15));
                        cout<<"Parked"<<endl;
                    }

                    if(command.substr(0,17) =="find_parking_slot")
                    {
                        findSlot(stoi(command.substr(18, 2))-1);
                    }

                    else if(command.substr(0, 6) == "unpark") {
                        unpark(command.substr(7, 9));
                    }

                    else if(command.substr(0,15) =="find_car_number") {
                        findNumber(command.substr(16));
                    }

                    else if(command.substr(0, 10) == "find_color")
                        find_color(command.substr(11));
                    
                    else if(command == "exit")
                    break;

                }
            }
        }

        void promptFile(fstream &file)
        {
            string command;
            bool flag = false;

            while(!file.eof()) {
                getline(file, command);
                cout<<"> "<<command<<endl;
                if(command == "create_parking_lot")
                {
                    cout<<"Parking created"<<endl;
                    flag = true;
                    continue;
                }

                if(flag) {
                    if(command.substr(0, 4) == "park")
                    {
                        park(command.substr(5, 9), command.substr(15));
                        cout<<"Parked"<<endl;
                    }

                    if(command.substr(0,17) =="find_parking_slot")
                    {
                        findSlot(stoi(command.substr(18, 2)));
                    }

                    else if(command.substr(0, 6) == "unpark") {
                        unpark(command.substr(7, 9));
                    }

                    else if(command.substr(0,15) =="find_car_number") {
                        findNumber(command.substr(16));
                    }

                    else if(command.substr(0, 10) == "find_color")
                        find_color(command.substr(11));
                    
                    else if(command == "exit")
                    break;

                }       
        }
        }
};


int main(int argc, char *argv[]) {
    fstream newfile;
    Parking obj;
    
    if(argc == 1)
        obj.promptCmd();

    else if(argc==2)
    {
        newfile.open(argv[1]);
        obj.promptFile(newfile);
    }
           
    return 0;
}