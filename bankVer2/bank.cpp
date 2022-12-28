//
// Created by user on 12/25/22.
//
#include "iostream"
#include "bank.h"
#include "fstream"
#include "string"

using namespace std;

int bank::welcome() {
    cout << "\nWelcome To Our Bank!!" << endl;
    loading();
    mainMenu();
}

int bank::mainMenu() {
    string option;
    cout<<"\n1:Register\n2:Login\n3:Quit"<<endl;
    cin>>option;
    if(option=="1"){
       reGister();
    } else if(option=="2"){
        login();
    } else if(option=="3"){
        quit_saving();
        exit(0);
    } else{
        cout<<"\nUnknown Input!!"<<endl;
        mainMenu();
    }
}

int bank::reGister(){
    string option;
    cout<<"\n1:Register\n2:Back"<<endl;
    cin>>option;
    if(option=="1") {
        nameRegister();
    }else if(option=="2"){
        mainMenu();
    } else{
        cout<<"\nUnknown Input!!"<<endl;
        reGister();
    }
}

int bank::login() {
    string option;
    cout<<"\n1:Login\n2:Back"<<endl;
    cin>>option;
    if(option=="1"){
      string name;
      cout<<"\nName: ";
      cin>>name;
      string password;
      cout<<"Password: ";
      cin>>password;
      currentUserID= checking_name_and_pass(name,userNameIndex,userNameArray);
      int checkPassword= checking_name_and_pass(password,userPasswordIndex,userPasswordArray);
      if(currentUserID!=-1 && checkPassword!=-1){
          cout<<"\nSuccessfully Logged In!!"<<endl;
          banking();
      } else{
          cout<<"\nCouldn't Log In!!"<<endl;
          login();
      }
    } else if(option=="2"){
        mainMenu();
    } else{
        cout<<"\nUnknown Input!!"<<endl;
        login();
    }
}


//banking option
int bank::banking() {
    string option;
    cout<<"\n1:Transfer\n2:Update\n3:My Info\n4:Main Menu"<<endl;
    cin>>option;
    if(option=="1"){
        transfer();
    } else if(option=="2"){
        update();
    } else if(option=="3"){
        myInfo();
    } else if(option=="4"){
        mainMenu();
    }else{
        cout<<"\nUnknown Input!!"<<endl;
        banking();
    }
}

int bank::myInfo() {
    cout<<"\nName: "<<userNameArray[currentUserID]<<endl;
    cout<<"Password: "<<userPasswordArray[currentUserID]<<endl;
    cout<<"Amount: "<<userAmountArray[currentUserID]<<" MMK"<<endl;
    banking();
}

int bank::transfer() {
   int transferMoney;
   cout<<"\nEnter Money To Transfer: ";
   cin>>transferMoney;
   if(transferMoney<=userAmountArray[currentUserID]-1000){
       string transferAcc;
       cout<<"Enter Acc To Transfer: ";
       cin>>transferAcc;
       int receiverID= checking_name_and_pass(transferAcc,userNameIndex,userNameArray);
       if(receiverID!=-1){
           userAmountArray[currentUserID]=userAmountArray[currentUserID]-transferMoney;
           userAmountArray[receiverID]=userAmountArray[receiverID]+transferMoney;
           cout<<"\nSuccessfully Transfer "<<transferMoney<<" MMK To "<<transferAcc<<endl;
           banking();
       }else{
           cout<<"\nThere Is No Acc With Username: "<<transferAcc<<endl;
           string option;
           cout<<"\n1:Transfer\n2:Back"<<endl;
           cin>>option;
           if(option=="1"){
               transfer();
           }else if(option=="2"){
               banking();
           } else{
               cout<<"\nUnknown Input!!"<<endl;
               cout<<"\n1:Transfer\n2:Back"<<endl;
               cin>>option;
           }
       }
   }else{
       cout<<"\nNot Enough Money!!"<<endl;
       string option;
       cout<<"\n1:Transfer\n2:Back"<<endl;
       cin>>option;
       if(option=="1"){
           transfer();
       }else if(option=="2"){
           banking();
       } else{
           cout<<"\nUnknown Input!!"<<endl;
           cout<<"\n1:Transfer\n2:Back"<<endl;
           cin>>option;
       }
   }
}

//read data form file
int bank::loading() {
    cout << "\nLoading..." << endl;
    string userNameData;
    ifstream userNameFile(userNameFileName);
    if (userNameFile.is_open()) {
        while (getline(userNameFile, userNameData)) {
            userNameArray[userNameIndex] = userNameData;
            userNameIndex++;
        }
        userNameFile.close();
    } else {
        cout << "\nUnable To Open " << userNameFileName << endl;
    }
    string userPasswordData;
    ifstream userPasswordFile(userPasswordFileName);
    if (userPasswordFile.is_open()) {
        while (getline(userPasswordFile, userPasswordData)) {
            userPasswordArray[userPasswordIndex] = userPasswordData;
            userPasswordIndex++;
        }
        userPasswordFile.close();
    } else {
        cout << "\nUnable To Open " << userPasswordFileName << endl;
    }
    int userData;
    string userAmountData;
    ifstream userAmountFile(userAmountFileName);
    if (userAmountFile.is_open()) {
        while (getline(userAmountFile,userAmountData)){
            int size=0;
            for(int i:userAmountData){
                size++;
            }
            userData= string_to_int(userAmountData,size);
            userAmountArray[userAmountIndex]=userData;
            userAmountIndex++;
        }
        userAmountFile.close();
    } else {
        cout << "\nUnable To Open " << userAmountFileName << endl;
    }
}

//check name already exist or not
int bank::checking_name_and_pass(string input,int index,string array[]) {
    for(int i=0; i<=index; i++){
        if(array[i]==input){
            return i;
        }
    }
    return -1;
}

int bank::quit_saving() {
    ofstream userNameFile(userNameFileName);
    if (userNameFile.is_open()){
        for(int i=0;i<userNameIndex;i++){
            userNameFile<<userNameArray[i]<<endl;
        }
    }else{
        cout << "\nUnable To Open " << userNameFileName<<endl;
    }

    ofstream userPasswordFile(userPasswordFileName);
    if (userPasswordFile.is_open()){
        for(int i=0;i<userPasswordIndex;i++){
            userPasswordFile<<userPasswordArray[i]<<endl;
        }
    }else{
        cout << "\nUnable To Open " << userPasswordFileName<<endl;
    }

    ofstream userAmountFile(userAmountFileName);
    if (userAmountFile.is_open()){
        for(int i=0;i<userAmountIndex;i++){
            userAmountFile<<userAmountArray[i]<<endl;
        }
    }else{
        cout << "\nUnable To Open " << userAmountFileName<<endl;
    }
}


int bank::nameRegister(){
    //name
    string name;
    cout<<"\nName: ";
    cin>>name;
    int checkName= checking_name_and_pass(name,userNameIndex,userNameArray);
    if(checkName==-1) {
        passwordRegister(name);
    }else{
        cout<<"\nUsername Has Been Taken!!"<<endl;
        reGister();
    }
}

int bank::passwordRegister(string name){
    string password1;
    cout << "Password: ";
    cin >> password1;
    string password2;
    cout << "Confirm Password: ";
    cin >> password2;
    if (password2 == password1){
        amountRegister(name,password2);
    } else{
        cout << "\nPassword Must Be Same!!\n" << endl;
        passwordRegister(name);
    }
}

int bank::amountRegister(string name,string password2) {
    int amount;
    cout << "Amount: ";
    cin >> amount;
    if (amount < 1000) {
        cout << "\nAmount Must Be At Least 1000 MMK" << endl;
        string option;
        cout << "\n1:Amount\n2:Back" << endl;
        cin >> option;
        if (option == "1") {
            amountRegister(name, password2);
        } else if (option == "2") {
            reGister();
        } else {
            cout << "\nUnknown Input!!" << endl;
            cout << "\n1:Amount\n2:Back" << endl;
            cin >> option;
        }
    } else{
        userNameArray[userNameIndex] = name;
        userPasswordArray[userPasswordIndex] = password2;
        userAmountArray[userAmountIndex] = amount;
        userNameIndex++;
        userPasswordIndex++;
        userAmountIndex++;
        cout << "\nSuccessfully Registered" << endl;
        mainMenu();
    }
}

int bank::update() {
    string option;
    cout<<"\n1:Money\n2:Username\n3:Password\n4:Delete Acc"<<endl;
    cin>>option;
    if(option=="1"){
      updateMoney();
    } else if(option=="2"){
       updateUsername();
    } else if(option=="3"){
        updatePassword();
    }else if(option=="4"){
        string password;
        cout<<"\nEnter Password: ";
        cin>>password;
        if(password==userPasswordArray[currentUserID]) {
            deleteAcc();
            mainMenu();
        }else{
            cout<<"\nWrong Password!!"<<endl;
            update();
        }
    }else {
        cout << "\nUnknown Input!!" << endl;
        update();
    }
}

int bank::updateMoney() {
    string option;
    cout<<"\n1:Input Money\n2:Withdraw\n3:Back"<<endl;
    cin>>option;
    if(option=="1"){
      inputMoney();
    } else if(option=="2"){
       wihtdraw();
    } else if(option=="3"){
        update();
    }else{
        cout<<"\nUnknown Input!!"<<endl;
        updateMoney();
    }
}

int bank::inputMoney() {
    int money;
    cout<<"\nEnter Money: ";
    cin>>money;
    userAmountArray[currentUserID]=userAmountArray[currentUserID]+money;
    cout << "\nSuccessfully Inputted Money!!" << endl;
    myInfo();
    update();
}

int bank::wihtdraw() {
    int money;
    cout<<"\nEnter Money To Withdraw: ";
    cin>>money;
    userAmountArray[currentUserID]=userAmountArray[currentUserID]-money;
    cout << "\nSuccessfully Withdrew Money!!" << endl;
    myInfo();
    update();
}

int bank::updateUsername() {
    string password;
    cout<<"\nEnter Your Password: ";
    cin>>password;
    if(password==userPasswordArray[currentUserID]){
        string username;
        cout<<"Enter New Username: ";
        cin>>username;
        int checkName= checking_name_and_pass(username,userNameIndex,userNameArray);
        if(checkName==-1){
            userNameArray[currentUserID]=username;
            cout<<"\nSuccessfully Updated Username!!"<<endl;
            myInfo();
            update();
        } else{
            cout<<"\nUsername Has Been Taken!!"<<endl;
            cout<<"Enter New Username: ";
            cin>>username;
            checkName= checking_name_and_pass(username,userNameIndex,userNameArray);
            if(checkName==-1) {
                userNameArray[currentUserID] = username;
                cout << "\nSuccessfully Updated Username!!" << endl;
                myInfo();
                update();
            }
        }
    } else{
        cout<<"\nWrong Password!!"<<endl;
        update();
    }
}

int bank::updatePassword() {
    string password;
    cout<<"\nEnter Old Password: ";
    cin>>password;
    if(password==userPasswordArray[currentUserID]){
        string newpass;
        cout<<"Enter New Password: ";
        cin>>newpass;
        if(newpass==userPasswordArray[currentUserID]){
            cout<<"\nNew Password Shouldn't Be Same With The Old One!!"<<endl;
            cout<<"Enter New Password: ";
            cin>>newpass;
        }
        userPasswordArray[currentUserID]=newpass;
        cout << "\nSuccessfully Updated Password!!" << endl;
        myInfo();
        update();
    } else{
        cout<<"\nWrong Password!!"<<endl;
        update();
    }
}

int bank::deleteAcc() {
   while(currentUserID<userNameIndex){
       userNameArray[currentUserID]=userNameArray[currentUserID+1];
       userPasswordArray[currentUserID]=userPasswordArray[currentUserID+1];
       userAmountArray[currentUserID]=userAmountArray[currentUserID+1];
       currentUserID++;
   }
   quit_saving();
   loading();
   cout<<"\nSuccessfully Deleted!!"<<endl;
   mainMenu();
}

int bank::string_to_int(string str,int size) {
  char strArr[10]={'0','1','2','3','4','5','6','7','8','9'};
  int intArr[10]={0,1,2,3,4,5,6,7,8,9};
  int returnNum=0;
  int multiNum=1;
    while (size>=0){
        for(int i=0;i<10;i++){
            if(str[size]==strArr[i]){
                returnNum+=intArr[i]*multiNum;
                multiNum*=10;
            }
        }
        size--;
    }
    return returnNum;
}