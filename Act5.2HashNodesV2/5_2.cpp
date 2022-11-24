#include <iostream>
#include <list>
#include <fstream>
#include <cstring>  
#include <string>
#include <sstream>
using namespace std;
/* 
Act 5.2 - Comprehensive activity on the use of hash codes (Competence evidence)
Javier Eric Hernandez A01635390
Carlos Eduardo Arellano A01641620
 */
struct Node{
    string IP;
    int NumAccesos;
    list <string> accesos;
    list <string> puertos;
    Node(string mes,string dia,string hora,string ip,string puerto,string accion){
        this->IP=ip;//key
        this->NumAccesos=1;
        this->accesos.push_back(mes+" "+dia+" "+hora+" "+accion);
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
        // void print();
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
string* split(string str){
    int n = 0;
    string *arr = new string[6];
    stringstream ssin(str);
    for (int i = 0; n<5; i++) {
        if ((str[i] == ' ' && n<5) || (str[i] == ':' && n>2)) {
            n++;
        }else{
        arr[n] += str[i];
       }
    }
    // cout << arr << endl;
    return arr;
}
void Hashtable::cargarDatos(string file){
 //cargarDatos: O(n)
    //Loads the data from the file into the heap
    ifstream archivo;
    archivo.open(file);
    string line;
    while(getline(archivo,line)){
        // cout << line << endl;
        string *datos=split(line);
        Node n(datos[0],datos[1],datos[2],datos[3],datos[4],datos[5]);
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
        int i = 1;
        int j = 1;
        while(!table[index].empty()||table[index].front().IP==ip){
            if(table[index].front().IP==ip){
                cout<<"\nIP: "<<table[index].front().IP<<endl;
                cout<<"\nNumero de accesos: "<<table[index].front().NumAccesos<<endl;
                cout<<"\nHora y dia de accesos: "<<endl;
                for(auto it=table[index].front().accesos.begin();it!=table[index].front().accesos.end();it++){
                    cout<<"Acceso "<< j << ": "<<*it<<endl;
                    j++;
                }
                j = 1;
                cout<<"\nPuerto de cada acceso: "<<endl;
                for(auto it=table[index].front().puertos.begin();it!=table[index].front().puertos.end();it++){
                    cout<<"Acceso "<< j << ": "<<*it<<endl;
                    j++;
                }
                return;
            }
            index=(index+i*i)%size;
            i++;
        }
        cout<<"\nNo se encontro el registro"<<endl;
    }
}
// void Hashtable::print(){
//     //print: O(n)
//     //Prints the table
//     for(int i=0;i<size;i++){
//         if(!table[i].empty()&&table[i].front().NumAccesos>1){
//             cout<<i<<": "<<table[i].front().IP<<" :::"<<table[i].front().NumAccesos<<endl;
//             cout<<"\tAccesos: "<<endl;
//             for(auto it=table[i].front().accesos.begin();it!=table[i].front().accesos.end();it++){
//                 cout<<"\t\t"<<*it<<endl;
//             }
//             cout<<"\tPuertos: "<<endl;
//             for(auto it=table[i].front().puertos.begin();it!=table[i].front().puertos.end();it++){
//                 cout<<"\t\t"<<*it<<endl;
//             }
//         }
//     }
// }
int main(){
    fflush(stdin);
    Hashtable Ips;
    Ips.cargarDatos("bitacora.txt");
    // cout<<"Cargando datos..."<<endl;
    string Ip;
    do {
        cout<< "\nWrite EXIT if you want to end the program" << endl;
        cout << "\n----------------------------IP info-----------------------------" << endl;
        cout << "\nIngresa la IP que buscas en el Siguiente Formato: " << endl;
        cout << "Example: xxx.xx.xxx.xx "; //423.2.230.77
        // cout<<"Ingrese la IP a buscar: ";
        cin>>Ip;
        Ips.search(Ip);
    }
    while(Ip!="EXIT");
    return 0;
}