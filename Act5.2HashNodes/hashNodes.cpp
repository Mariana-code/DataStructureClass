/// Act 5.2 - Comprehensive activity on the use of hash codes (Competence evidence)
/// Author: Juan Jose Salazar Cortes
/// Author: Mariana Esquivel Hernandez
/// date: 11/02/2022

#include <bits/stdc++.h>

using namespace std;

struct Node{
    string IP;
    int NumAccesos;
    list <string> accesos;
    list <string> puertos;
    Node(string fechaYHora, string ip,string puerto){
        this->IP=ip;
        this->NumAccesos=1;
        this->accesos.push_back(fechaYHora);
        this->puertos.push_back(puerto);
    }
};
class Hashtable{
    private:
        int size;
        list<Node> *table;
    public:
        Hashtable(){
            this->size=16807;
            table=new list<Node>[16807];
        }
        int hashFunction(string ip);
        void insert(Node n);
        void cargarDatos(string file);
        void search(string ip);
        void print();
};
int Hashtable::hashFunction(string ip){    
    //hashFunction:O(n)
    //Hash function
    int hash=0;
    for(int i=0;i<ip.length();i++){
        hash+=ip[i];
    }
    return hash%size;
}
void Hashtable::insert(Node n){
    //insert:O(n)
    //Quadratic probing overflow handling
    int index=hashFunction(n.IP);
    if(table[index].empty()){
        table[index].push_back(n);
    }else{
        int i=1;
        while(!table[index].empty()||table[index].front().IP==n.IP){
            if(table[index].front().IP==n.IP){
                table[index].front().NumAccesos++;
                table[index].front().accesos.push_back(n.accesos.front());
                table[index].front().puertos.push_back(n.puertos.front());
                return;
            }
            index=(index+i*i)%size;
            i++;
        }
        table[index].push_back(n);
    }
}

void Hashtable::cargarDatos(string file){
 //cargarDatos: O(n)
    //Loads the data from the file into the heap
    ifstream archivo;
    archivo.open(file);
    string line;
    while(getline(archivo,line)){
        Node n(getDayAndMonth(line),getIPAccess(getIP(line)), );
        insert(n);
    }
    archivo.close();
}
void Hashtable::search(string ip){
    //search: O(n)
    //Searches for a node in the table
    int index=hashFunction(ip);
    if(table[index].empty()){
        cout<<"No se encontro el registro"<<endl;
    }else{
        int i=1;
        while(!table[index].empty()||table[index].front().IP==ip){
            if(table[index].front().IP==ip){
                cout<<"IP: "<<table[index].front().IP<<endl;
                cout<<"Numero de accesos: "<<table[index].front().NumAccesos<<endl;
                cout<<"Accesos: "<<endl;
                for(auto it=table[index].front().accesos.begin();it!=table[index].front().accesos.end();it++){
                    cout<<*it<<endl;
                }
                cout<<"Puertos: "<<endl;
                for(auto it=table[index].front().puertos.begin();it!=table[index].front().puertos.end();it++){
                    cout<<*it<<endl;
                }
                return;
            }
            index=(index+i*i)%size;
            i++;
        }
        cout<<"No se encontro el registro"<<endl;
    }
}

void Hashtable::print(){
    //print: O(n)
    //Prints the table
    for(int i=0;i<size;i++){
        if(!table[i].empty()&&table[i].front().NumAccesos>1){
            cout<<i<<": "<<table[i].front().IP<<" :::"<<table[i].front().NumAccesos<<endl;
            cout<<"\tAccesos: "<<endl;
            for(auto it=table[i].front().accesos.begin();it!=table[i].front().accesos.end();it++){
                cout<<"\t\t"<<*it<<endl;
            }
            cout<<"\tPuertos: "<<endl;
            for(auto it=table[i].front().puertos.begin();it!=table[i].front().puertos.end();it++){
                cout<<"\t\t"<<*it<<endl;
            }
        }
    }
}

string getDayAndMonth(string record){
    if(record[5] == ' ') return record.substr(0, 5);
    else return record.substr(0, 6);
} // Time Complexity O(1)

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

int main(){
    Hashtable h;
    h.cargarDatos("bitacora.txt");
    cout<<"Cargando datos..."<<endl;
    string ip;
    cout<<"Ingrese la IP a buscar: ";
    cin>>ip;
    h.search(ip);
    return 0;
}