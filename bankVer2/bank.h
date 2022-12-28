//
// Created by user on 12/25/22.
//

#ifndef BANKVER2_BANK_H
#define BANKVER2_BANK_H

class bank {
public:
    int currentUserID;
    int userNameIndex=0;
    int userPasswordIndex=0;
    int userAmountIndex=0;
    std::string userNameFileName = "name.txt";
    std::string userPasswordFileName = "password.txt";
    std::string userAmountFileName = "amount.txt";
    std::string userNameArray[100];
    std::string userPasswordArray[100];
    int userAmountArray[100];
    //main methods
    int welcome();
    int mainMenu();
    int reGister();
    int login();
    int banking();
    int myInfo();
    int transfer();
    int update();
    //secondary methods
    int quit_saving();
    int loading();
    int inputMoney();
    int wihtdraw();
    int updateUsername();
    int updatePassword();
    int deleteAcc();
    //support methods
    int checking_name_and_pass(std::string input,int index,std::string array[]);
    int nameRegister();
    int passwordRegister(std::string name);
    int amountRegister(std::string name,std::string password2);
    int updateMoney();
    int string_to_int(std::string str,int size);
    };


#endif //BANKVER2_BANK_H
