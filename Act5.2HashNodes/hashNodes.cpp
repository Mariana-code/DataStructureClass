/// Act 5.2 - Comprehensive activity on the use of hash codes (Competence evidence)
/// Author: Juan Jose Salazar Cortes
/// Author: Mariana Esquivel Hernandez
/// date: 11/23/2022

// #include <bits/stdc++.h>

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <typeinfo>
#include <queue>
#include <map>
#include <array>
#include <list>
#include <stdio.h>
#include <string.h>
#include <cstring>

using namespace std;

struct Node{
    int numAccess;
    string IP;
    list <string> ports;
    list <string> access;
    Node(string dataTime, string ip, string port){
        this-> numAccess = 1;
        this-> IP = ip;
        this-> ports.push_back (port);
        this-> access.push_back (dataTime);
    }
};

// obtain basic info from the IP address
string getDayMonth(string record){
    if(record[5] == ' ') return record.substr(0, 14);
    else return record.substr(0, 15);
} // Time Complexity O(1)

// take IP from line
string getIP(string record){
    long long contEsp = 0;
    long long indexBeg;
    long long indexEnd;
    bool aux = true;
    bool aux2 = true;
    for(long long i = 0; i < record.length(); i++){
        if(record[i] == ' ') contEsp ++;
        if(contEsp == 3 && aux) indexBeg = i + 1 , aux = false;
        if(contEsp == 4 && aux2) indexEnd = i - indexBeg , aux2 = false;
    }
    return record.substr(indexBeg, indexEnd); // "112.12.122.12.1111"
} // Time Complexity O(n)

// Take the IP without the port 
string getIPAccess(string IP){
    string access;
    for(int i = 0; i <= IP.length()-6; i++){
        access += IP[i];
    }
    return access;
} // Time Complexity O(n)

// Take the port of the IP
string getIPPort(string IP){
    string access;
    for(int i = 14; i <= IP.length(); i++){
        access += IP[i];
    }
    return access;
} // Time Complexity O(n)

class Hashtable{
    private:
        int size;
        list<Node> *table;
    public:
        Hashtable(){
            this-> size = 16807;
            table = new list<Node>[16807];
        }
        int hashFunction(string ip);
        void insert(Node n);
        void loadInfo(string file);
        void search(string ip);
        void print();
};

// Hash function 
int Hashtable::hashFunction(string ip){    
    int hash = 0;
    for(int i = 0; i < ip.length(); i++){
        hash += ip[i];
    }
    return hash % size;
}// Time Complexity O(n)

// Insert the node in the hash table and if the IP is already in the table, it will add the access to the list of accesses
void Hashtable::insert(Node value){
    int index = hashFunction(value.IP);
    if(table[index].empty()){
        table[index].push_back(value);
    }else{
        int i = 1;
        while (!table[index].empty() || table[index].front().IP == value.IP){
            if (table[index].front().IP == value.IP){
                table[index].front().ports.push_back(value.ports.front());
                table[index].front().access.push_back(value.access.front());
                table[index].front().numAccess ++;
                return;
            }
            index = (index + i * i) % size;
            i++;
        }
        table[index].push_back(value);
    }
}// Time Complexity O(n)

// Load the data from the file and insert the nodes in the hash table
void Hashtable::loadInfo(string file){
    ifstream document;
    document.open(file);
    string line;
    while(getline(document,line)){
        Node value(getDayMonth(line),getIPAccess(getIP(line)), getIPPort(getIP(line)));
        insert(value);
    }
    document.close();
}// Time Complexity O(n)

// Search the IP in the hash table and print the information of the node
void Hashtable::search (string ip){
    int index = hashFunction(ip);
    if (table[index].empty()){
        cout << "Ip not in record" << endl;
    } else {
        int i = 1;
        int j = 1;
        while (!table[index].empty() || table[index].front().IP == ip){
            if (table[index].front().IP == ip){
                cout << "\nIP: " << table[index].front().IP << endl;
                cout <<"\nNumber of access: "<<table[index].front().numAccess << endl;
                cout <<"\nDay and Time of the access: " << endl;
                for(auto it = table[index].front().access.begin(); it != table[index].front().access.end(); it ++){
                    cout <<"Access " << j << ": \t"<<*it << endl;
                    j++;
                }
                j = 1;
                cout<<"\nPort from access: "<<endl;
                for(auto it = table[index].front().ports.begin(); it != table[index].front().ports.end(); it ++){
                    cout <<"Access "<< j << ": "<< "\t*--- " << *it << " ---*" << endl;
                    j++;
                }
                return;
            }
            index=(index + i * i) % size;
            i++;
        }
        cout<<"Not in record"<<endl;
    }
}// Time Complexity O(n)

int main(){
    fflush(stdin);
    Hashtable Ips;
    Ips.loadInfo("bitacora.txt");
    string Ip;
    do {
        cout<< "\nWrite EXIT if you want to end the program" << endl;
        cout << "\n----------------------------IP info-----------------------------" << endl;
        cout << "\nIngresa la IP que buscas en el Siguiente Formato: " << endl;
        cout << "Example: xxx.xx.xxx.xx "; //423.2.230.77
        cin>>Ip;
        if(Ip == "EXIT") break;
        Ips.search(Ip);
    }
    while(Ip != "EXIT");
    return 0;
}// Time Complexity O(n)