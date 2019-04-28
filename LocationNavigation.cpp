#include "stdlib.h"
#include <string>
#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>

using namespace std;

struct intersection{

	int number;
	string latitude;
	string longitude;
	string distfrom;
	string state;
	string nearestname;

	intersection(){

		number = 0;
		latitude = "";
		longitude = "";
		distfrom = "";
		state = "";
		nearestname = "";

	}

	intersection(string whoops,string a,string b,string c,string d,string f){

		number = whoops;
		latitude = a;
		longitude = b;
		distfrom = c;
		state = d;
		nearestname = f;

	}
};

struct connection{

	string roadname;
	string roadtype;
	intersection *A;
	intersection *B;
	string length;

	connection(){

		roadname = "";
		roadtype = "";
		A = NULL;
		B = NULL;
		length = "";

	}

	connection(string a,string b, intersection *c, intersection *d, string e){

		roadname = a;
		roadtype = b;
		A = c;
		B = d;
		length = e;

	}

	void print(){

		cout<<"Roadname: "<<roadname<<endl;
		cout<<"Road type: "<<roadtype<<endl;
		cout<<

	}

};

struct connectionnode{

	connection *data;
	connectionnode *next;

	connectionnode(){

		next = NULL;

	}

};

struct connectionlinked{

	connectionnode *first;

	connectionlinked(){

		first = NULL;

	}

	void addnode(connectionnode *temp){

		if(first == NULL){

			first = temp;
			return;

		}else{

			connectionnode *tptr = first;
			while(tptr->next!=NULL)tptr = tptr->next;
			tptr->next = temp;
			return;

		}
	}
};

struct connectionlist{

	connection **connections;
	int size;

	connectionlist(){

		connections = new connection*[50000];
		size = 0;

	}

	int addconnection(connection *temp){

		connections[size] = temp;
		size++;

	}

};


struct intersectionlist{

	intersection **intersections;
	int size;
	connectionlinked *connections;

	intersectionlist(){

		intersections = new intersection*[30000];
		size = 0;
		connections = NULL;
	
	}

	int addintersection(intersection *temp){

		size++;
		intersections[size] = temp;

	}

	intersection* findintersection(string temp){

		const char* cstr = (const char*)malloc(50*sizeof(char));
		cstr = temp.c_str();
		int index = atoi(cstr);
		if(index<size&&index>0) {
			cout<<temp<<intersections[index]<<endl;
			delete cstr;
		}
		else return NULL;

	}

	void printinfo(string temp){

		const char* cstr = (const char*)malloc(50*sizeof(char));
		cstr = temp.c_str();
		int index = atoi(cstr);
		if(index<size&&index>0){
			cout<< "Location: "<<index<<endl;
			cout<<"Latitude: "<<latitude<<endl;
			cout<<"Longitude: "<<longitude<<endl;
			cout<<"Distance from "<<nearestname<<", "<<state<<": "<<distfrom<<endl;
			int i = 0;
			if(connections->first!=NULL){
				while(tptr!=NULL){
					
				}
			}
		}
		else cout<<"Invalid entry, please try again."<<endl;
	}

	void printlist(){

		int i = 1;
		while(i<size){
			 cout<<intersections[i]->latitude<<endl;
			 i++;
		}
	}
};



void fillconnectionlinked(intersectionlist *tempintersections, connectionlist *tempconnections){

	int i = 0;
	connectionlinked *templinked;
	while(i<tempintersections->size){
		
		connectionlinked *templinked = new connectionlinked;
		intersection *temp = tempintersections->intersections[i];
		int j = 0;
		while(j<tempconnections->size){

			if(tempconnections->connections[j]->A == tempintersections->intersections[i]){

				connectionnode *newnode = new connectionnode;
				newnode->data = tempconnections->connections[j];
				templinked->addnode(newnode);
			
			}
			if(tempconnections->connections[j]->B == tempintersections->intersections[i]){

				connectionnode *newnode = new connectionnode;
				newnode->data = tempconnections->connections[j];
				templinked->addnode(newnode);
			
			}
			j++;
		}
		i++;
	}
	tempintersections->connections = templinked;
}



intersectionlist* fillintersections(){

	intersectionlist *newlist = new intersectionlist;
	fstream file("intersections.txt");
	if(file.fail()){

		cout<<"Get your shit together"<<endl;
		return newlist;
	}
	string newline;
	string lat;
	string lon;
	string dist;
	string state;
	string place;
	getline(file,newline);
	getline(file,newline);
	int i = 0;
	while(!file.eof()){
		i++;
		lat = newline.substr(0,9);
		lon = newline.substr(12,7);
		dist = newline.substr(21,6);
		state = newline.substr(28,2);
		place = newline.substr(31,27);
		intersection *tempintersection = new intersection(i,lat,lon,dist,state,place);
		newlist->addintersection(tempintersection);
		getline(file,newline);
	}
	return newlist;
}


connectionlist* fillconnections(intersectionlist *list){

	connectionlist *newlist = new connectionlist;
	fstream file("connections.txt");
	if(file.fail()){

		cout<<"Get your shit together"<<endl;
		return newlist;
	}
	string newline;
	string roadname;
	string roadtype;
	string intersectAstring;
	intersection *intersectA;
	string intersectBstring;
	intersection *intersectB;
	string length;
	getline(file,newline);
	getline(file,newline);
	while(!file.eof()){

		int i = 0;
		int z = 0;
		while(newline[i]!=' ') {
			i++;
			z++;
		}
		z++;
		int j = z;
		roadname = newline.substr(0,i);
		i = 0;
		while(newline[z]!=' '){
			i++;
			z++;
		}
		roadtype = newline.substr(j,i);
		z++;
		i = 0;
		j = z;
		while(newline[z]!=' '){
			i++;
			z++;
		}
		intersectAstring = newline.substr(j,i);
		z++;
		j = z;
		cout<<"one"<<endl;
		intersectA = list->findintersection(intersectAstring);
		cout<<"two"<<endl;
		i = 0;
		while(newline[z]!=' '){
			i++;
			z++;
		}
		intersectBstring = newline.substr(j,i);
		z++;
		j = z;
		cout<<"three"<<endl;
		//intersectB = list->findintersection(intersectBstring);
		cout<<"four"<<endl;
		i = 0;
		while(newline[z]!='\n'){
			i++;
			z++;
		}
		cout<<"five"<<endl;
		length = newline.substr(j,i);
		//connection *tempconnection = new connection(roadname,roadtype,intersectA,intersectB,length);
		//newlist->addconnection(tempconnection);
		getline(file,newline);

	}
	return newlist;
}

void main(){

	string temp= "";
	cout<<"Please enter a location to start: "<<endl;
	cin>>temp;
	intersectionlist *intlist = fillintersections();
	connectionlist *conlist = fillconnections(intlist);
	//fillconnectionlinked(intlist,conlist);
	//if(intlist->findintersection(temp)!=NULL){
	//	while(true){
			cout<<
	//	}
	//}
	//else return;


}
