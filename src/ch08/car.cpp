#include<iostream>
#include<string>
#include<fstream>
using namespace std;
// 引用：https://blog.csdn.net/qq_42442875/article/details/80819944
// 停车场统计系统 
class CPark{
    string C_num;
    int C_type;
    string Intime,Outtime;
    int Times;
    double C_money;
    int S_seat,MB_seat;
public:
    CPark(int s_seat=0,int mb_seat=0);
    void OccupyOne();
    void Pullout();
    void show();
};
 
CPark::CPark(int s_seat,int mb_seat){
        S_seat=s_seat;
        MB_seat=mb_seat;
    }
 
void CPark::OccupyOne(){
        int type=0;
        cout<<"Please input type(1 or 2):";
        cin>>type;
        switch (type){
        case 1:
            if(S_seat>0){
                S_seat--;
                C_type=type;
                cout<<"Input the car's information:"<<endl;
                cin>>C_num>>Intime;
            }
            else{
                type=0;
                cout<<"Don't have a seat!\n";
            }
           break;
        case 2:
            if(MB_seat>0){
                MB_seat--;
                C_type=type;
                cout<<"Input Twocar's information:"<<endl;
                cin>>C_num>>Intime;
            }
            else{
                type=0;
                cout<<"Don't have a seat!\n";
            }
           break;
        default:
            cout<<"Don't have the type!\n";
            break;
                    }
        if(type==1||type==2){
            ofstream f1("CarInfor.dat",ios::app);
            f1<<C_num<<" "<<C_type<<" "<<Intime<<endl;
            f1.close();
            cout<<"Information has been saved!\n";
            show();cout<<endl;
        }
    }
 
 void CPark::Pullout(){
    string c_num1,c_num2,c_num3="ab1234";
    cout<<"Input CarNumber :";
    cin>>c_num1;
    ifstream f2("CarInfor.dat",ios::in);
    while(getline(f2,c_num2)){
        for(int i=0;i<6;i++){
            c_num3[i]=c_num2[i];
        }
        if(c_num3==c_num1){
            cout<<"\nCarNumber: "<<c_num3<<"  Type: "<<c_num2[7]<<endl;
            cout<<"Come in time: \n"<<c_num2[9]<<c_num2[10]<<c_num2[11]<<c_num2[12];
            cout<<"-"<<c_num2[13]<<c_num2[14]<<"-"<<c_num2[15]<<c_num2[16]<<" ";
            cout<<c_num2[17]<<c_num2[18]<<":"<<c_num2[19]<<c_num2[20]<<endl;
            if(c_num2[7]=='1')S_seat++;
            else MB_seat++;
        }
    }
    f2.close();
    show();cout<<endl;
 }
 
 void CPark::show(){
    cout<<"     CarSeats!\n";
    cout<<"Type1: "<<S_seat<<"  Type2: "<<MB_seat<<endl;
 }
 
int main()
{
    CPark park1(200,100);
    int op1;
    cout<<"     (1)Come in a car\n     (2)Go out a car\n     (0)Exit!!!\nInput a operation:";
    cin>>op1;
    while(op1){
        switch(op1){
            case 1:
                park1.OccupyOne();
                break;
            case 2:
                park1.Pullout();
                break;
            default:
                cout<<"     Don't have the command!\n";
                break;
            }
        cout<<"Continue!!\n  (1)Come in a car  (2)Go out a car  (0)Exit!!!\nInput a operation:";
        cin>>op1;
    }
 
   return 0;
}