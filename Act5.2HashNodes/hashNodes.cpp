/// Act 5.2 - Comprehensive activity on the use of hash codes (Competence evidence)
/// Author: Juan Jose Salazar Cortes
/// Author: Mariana Esquivel Hernandez
/// date: 11/02/2022

//#include <bits/stdc++.h>

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

using namespace std;

struct Node{
    string IP;
    vector<long long> ports;
    int rep;
    Node(string value): IP(value), rep(1){};
};

class maxHeap{
    private:
        int size = 0;
        vector<Node> heapTree = {};    
        int parent(int index) {
            return (index - 1) >> 1;
            }; 
        int left(int index) {
            return (index << 1) + 1;
            };  
        int right(int index) {
            return (index << 1) + 2;
            };  
    public:
        bool isEmpty() const {
            return size == 0;
            };
        void insertion(string value); 
        void top(int index);
        void shiftUp(int index); 
        void shiftDown(int index);
};

//Check if IP already exists and add to the repetitions and shift Up to move the IP further up the heap
//If it's a new value on the heap, insert it at the end and sift up to move it further up the heap
//If the heap is empty, insert the first element

void maxHeap::insertion(string value){
    if(size == 0){
        heapTree.push_back(Node(value));
        size+=1;
        return;
    }
    for(int i = 0; i < size; i++){
        if(heapTree[i].IP == value){
            heapTree[i].rep++;
            shiftUp(i);
            return;
        }
    }
    heapTree.push_back(Node(value));
    size+=1;
    shiftUp(size-1);
    return;
}//Time complexity: O(n)

void maxHeap::top(int index){
    string maxIP = heapTree[0].IP;    
    int maxReps = heapTree[0].rep;
    // for (int i = 0; i < maxReps; i++){
    //     cout << "Port-."<< index+1 << " "<< heapTree[0].ports[i] << endl;
    // }
    cout << "IP-."<< index+1 << " "<< maxIP + " is being repeated: " << to_string(maxReps) << " times "<< endl;
    swap(heapTree[0], heapTree[size-1]);
    shiftDown(0);
    size -= 1;
}//Time complexity: O(log n)

void maxHeap::shiftUp(int index){
    if(index == 0) return; 
    int parentIndex = parent(index);
    if(heapTree[parentIndex].rep < heapTree[index].rep){
        swap(heapTree[parentIndex], heapTree[index]);
    } 
    else if( heapTree[parentIndex].rep == heapTree[index].rep && heapTree[parentIndex].IP != heapTree[index].IP){ 
        swap(heapTree[parentIndex], heapTree[index]);
    }
    shiftUp(parentIndex);
}//Time complexity: O(log n)

void maxHeap::shiftDown(int index){
    if(size <= index){
        return; 
    }
    int aux = index;
    if((left(index) < size) && (heapTree[index].rep < heapTree[left(index)].rep)){
        aux = left(index);
    }
    if((right(index) < size) && (heapTree[aux].rep < heapTree[right(index)].rep)){
        aux = right(index);      
    }
    if(aux != index){
        swap(heapTree[index], heapTree[aux]);
        shiftDown(aux);
    }   
    return;
}//Time Complexity O(log n)

// Take the IP from the line
string getIP(string record){
    long long contEsp = 0;
    long long indexBeg;
    long long indexEnd;
    bool aux = true;
    bool aux2 = true;
    for(long long i = 0; i < record.length(); i++){
        if(record[i] == ' ') contEsp ++;
        if(contEsp == 3 && aux){
            indexBeg = i + 1 , aux = false;
        }
        if(contEsp == 4 && aux2){
            indexEnd = i - indexBeg , aux2 = false;
        }
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

// Modify the IP to have the same length
string configStr(string IP){ // 10.15.175.231:6166 -> 10.15.175.231
    long long consts = 0;
    long long constt = 0;
    long long constf = 0;
    long long dot = 0;
    
    for(long long i = IP.length(); i >= 0; i--){ 
        if (IP[i] == '.') dot++; 
        else if (dot == 0) consts++; 
        else if (dot == 1) constt++; 
        else if (dot == 2) constf++;
        if (consts < 2 && dot == 1){
            IP[i] = '0';
            consts++;
        }
        else if (constt < 3 && dot == 2){
            IP[i] = '0';
            constt++;
            if(constt < 3) IP.insert(i,"0");
        }
        else if (constf < 2 && dot == 3){
            IP[i] = '0';
            constf++;
        }
    }
    return IP;
} // Time Complexity O(n)

// Delete "." and ":" from the IP to sort it as an long longeger
long long getNumberIP(string IP){
    string newStr;
    // cout << IP << endl;
    for(long long i = 0; i < IP.length(); i++){
        // if(IP[i] != ':' && IP[i] != '.'){
        if(IP[i] != '.'){
            newStr += IP[i];
        } else{
            continue;
        }
    }
    return stoll(newStr);
} // Time Complexity O(n)

long long sequentialSearch(vector<string> &info, string IP){
    cout << IP << endl;
    for(long long i = 0; i < info.size(); i++){
        if(getNumberIP(configStr(getIP(info[i]))) == getNumberIP(configStr(IP))){
            return i;
        }
    }
    return -1;
} // Time Complexity O(n)

// Take the IP port 
long long getIPPort(string IP){
    string port;
    for(int i = IP.length()-4; i <= IP.length(); i++){
        port += IP[i];
    }
    return stoll(port);
} // Time Complexity O(n)

// Date and time
string getDateTime(string IP){
    string dateTime;
    long long aux = 0;
    for(long long i = 0; aux < 3; i++){
        if (IP[i] == ' '){
            aux ++;
        }
        dateTime += IP[i];
    }
    return (dateTime);
} // Time Complexity O(n)


int main(){
    fflush(stdin);
    vector<string> info; // vector of the IPs
    //vector<string> IP; // vector of the IPs without the port
    string record;
    string wantedIP;
    maxHeap* priorityQueue = new maxHeap();
    ifstream OurReadFile("bitacora.txt");
    vector<string> lines;
    vector<string> access;
    
    string line;
    long long portN;

    ifstream MyReadFile("bitacora.txt");

    while(getline(MyReadFile, record)){
        info.push_back(record);
        // h.insertItem(record);
    }
    MyReadFile.close();

    while(getline(OurReadFile,line)){
        priorityQueue->insertion(getIPAccess(getIP(line)));
    }//Time complexity: O(n log n)
    // OurReadFile.close();

    while (true){
        cout<< "\nPresiona ENTER si quieres salir del programa" << endl;
        cout << "\n----------------------------IP info-----------------------------" << endl;
        cout << "Ingresa la IP que buscas en el Siguiente Formato: " << endl;
        cout << "Example: xxx.xx.xxx.xx: ";
        getline(cin, wantedIP);
        cout << "\nwantedIP: " << wantedIP << endl;

        int indexIP = sequentialSearch(info, wantedIP);
        if (indexIP == -1){
            cout << "IP not found" << endl;
            continue;
        }
        portN = getIPPort(getIP(info[indexIP]));
        cout << "IP: " << info[indexIP] << endl;
        cout << "Port: " << portN << endl;
        cout << "Date and time: " << getDateTime(info[indexIP]) << endl;
        cout << "----------------------------Number of accesses for IP address-----------------------------" << endl;
        for(int i = 0; i < 5; i++){
            priorityQueue->top(i);
        }//Complexity O(nlogn)
    }

    return 0;
}