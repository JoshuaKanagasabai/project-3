/**
 * file: driver-proj3.cpp
 * author: Joshua Kanagasabai
 * course: CSI 3334
 * assignment: project 3
 * due date: October 11, 2019
 * version: 1.0
 *
 * This file reads input from a file representing a
 * number of commands relating to encryption/decryption
 * and outputs what these commands require
  *
 **/

#include <iostream>
#include "bst-student-proj3.h"

using namespace std;

/* main
 *  parameters:
 *      argc -- the number of arguments from the command line
 *      argv -- the command line argument values
 *  return value: 0 (indicating a successful run)
 *
 *  this function reads through a given input in a defined
 *  structure and executes the commands it contains to encrypt, decrypt,
 *  print, quit, remove, or insert from a encryption tree
 */

int main(int argc, char **argv) {
    int INDEX_OF_COMMAND_CHAR = 0;
    const unsigned int BEGINNING_OF_CLEAR_TEXT_MESSAGE = 3;
    const unsigned int INITIAL_SIZE = 0;
    const unsigned int INDEX_OF_CLEARTEXT_WORD = 2;
    EncryptionTree<string> theTree;
    string hold;
    bool go = true;
    while(go){
        getline(cin,hold);
        char command = hold[INDEX_OF_COMMAND_CHAR];
        if(command =='p') {
           theTree.printPreorder(cout);
        }
        else if(command =='q')
            go= false;
        else if(command == 'e'){
            string temp;
            unsigned int beg = BEGINNING_OF_CLEAR_TEXT_MESSAGE;
            unsigned int end = INITIAL_SIZE;
            for(unsigned int i=BEGINNING_OF_CLEAR_TEXT_MESSAGE;i<hold.length();i++){
                end++;
                if(hold[i]==' ' || i == hold.length()-1) {
                    temp = hold.substr(beg, end-1);
                    beg = i+1;
                    end = INITIAL_SIZE;
                    cout << theTree.encrypt(temp);
                    if(i!=hold.length()-1)
                        cout << " ";
                }
            }
            cout << endl;
        }
        else if(command == 'd'){
            string temp;
            unsigned int beg=BEGINNING_OF_CLEAR_TEXT_MESSAGE;
            unsigned int end=INITIAL_SIZE;
            for(unsigned int i=BEGINNING_OF_CLEAR_TEXT_MESSAGE;i<hold.length();i++){
                end++;
                if(hold[i]==' ' || i == hold.length()-1) {
                    temp = hold.substr(beg, end-1);
                    beg = i+1;
                    end=INITIAL_SIZE;
                    if(theTree.decrypt(temp)!=NULL)
                        cout << *(theTree.decrypt(temp));
                    else
                        cout << "?";
                    if(i!=hold.length()-1)
                        cout << " ";
                }
            }
            cout << endl;
        }
        else if(command == 'r'){
            string deletion = hold.substr(INDEX_OF_CLEARTEXT_WORD);
            theTree.remove(deletion);
        }
        else if(command == 'i'){
            string insertion = hold.substr(INDEX_OF_CLEARTEXT_WORD);
            theTree.insert(insertion);
        }
    }



    return 0;
}