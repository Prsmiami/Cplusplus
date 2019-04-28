#include "stdlib.h"
#include <string>
#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>

using namespace std;

int arrysize = 10000;

struct city{

	string *state;
	string *name;
	double *population;
	double *area;
	double *lat;
	double *lon;
	double *intersect;
	double *intersectdist;

};
	
city * makecity(){

	city *temp = new city;
	temp->state = new string;
	temp->name = new string;
	temp->population = new double;
	temp->area = new double;
	temp->lat = new double;
	temp->lon = new double;
	temp->intersect = new double;
	temp->intersectdist = new double;
	return temp;
	
}

struct citynode{

	city *data;
	citynode *next;

	citynode(){

		data = NULL;
		next = NULL;

	}
};

struct hasharray{

	int *size;
	citynode **cityarray;
	
	hasharray(){

		size = NULL;
		cityarray = new citynode*[arrysize];
	
	}
};

hasharray * makehash(const int arraysize){

	hasharray *newhash = new hasharray;
	newhash->size = new int;
	*(newhash->size) = arraysize;
	int i = 0;
	while(i<arrysize){

		newhash->cityarray[i] = NULL;
		i++;

	}
	return newhash;

};

int generatevalue(string tempstring){

	double ret = 0;
	int retint = 0;
	int z = 0;
	tempstring = tempstring.c_str();
	while(tempstring[z] != NULL) {
		z++;
	}
	int i = 0;
	double power = 0;
	while(i <= z){

		ret += tempstring[i]*pow( 3.0,power);
		i++;
		power++;

	}
	ret = fmod(ret, arrysize);
	retint = (int)ret;
	return(retint);
};

void addtotable(hasharray * hash, city * newcity){

	int slot = generatevalue(*newcity->name);
	citynode *tempnode = new citynode;
	tempnode->data = newcity;
	tempnode->next = NULL;
	if(hash->cityarray[slot] != NULL){

		citynode *travnode = hash->cityarray[slot];

		while(travnode->next != NULL) {

			travnode = travnode->next;
		
		}
		travnode->next = tempnode;

	}
	else{
		hash->cityarray[slot] = tempnode;

	}
	return;
};

hasharray * doublearray(hasharray * in){

	hasharray * out = makehash(*(in->size)*2);
	
	int i = 0;
	while(i < *(in->size)){

		out->cityarray[i] = in->cityarray[i];

	}
	return out;
};



string cutspacesfromend(string input){

	string output;
	int i = 0;
	while( !(input[i] == ' ' && input[i+1] == ' ')) i++;
	output = input.substr(0,i);
	return output;

}

double cutspacesfrombeginning(string input){

	string output;
	input = input.c_str();
	int i = 0;
	int z = 0;
	while(input[i] == ' ')	i++;
	while(input[i] != '\0'){

		output[z] = input[i];
		i++;
		z++;

	}
	z--;
	double ret = 0;
	int tempdigit = 0;
	double place = 0;
	while(z >= 0){

		char tempchar = output[z];
		tempdigit = atoi(&tempchar);
		ret += tempdigit*pow(10 , place);
		z--;
		place++;
	
	}
	return ret;
	
}

double cutspacesfrombeginningwithdecimalandneg(string input){

	bool nflag = 0;
	string output;
	input = input.c_str();
	int i = 0;
	while(input[i] == ' ' || input[i] == '-'){

		if(input[i] == '-'||input[i+1] == '-') nflag = 1;
		i++;
		
	}
	output = input.substr(i,input.length()-i);	

	int x = 0;

	while(output[x]!='.') x++;

	int strlength = output.length();
	string whole = output.substr(0,x);
	string dec = output.substr(x+1,output.length()-x+1);

	double ret = 0;
	int tempdigit = 0;
	double place = 0;
	strlength = whole.length();

	int z = strlength-1;

	while(z >= 0){

		char tempchar = output[z];
		int tempdigit = atoi(&tempchar);
		ret += tempdigit*pow(10 , place);
		z--;
		place++;
	
	}	
	
	place = 0; 
	strlength = dec.length();
	while(z < strlength){

		char tempchar = dec[z];
		tempdigit = atoi(&tempchar);
		ret += tempdigit*pow(10 , place);
		z++;
		place--;

	}

	if(nflag == 1) ret = ret*(-1);
	return ret;
	
}



hasharray * readfile(string filename){

	hasharray *ret = NULL;	

	fstream file("named-places.txt");
	if(file.fail()){
		
		cout << "You're a failure kill yourself" << endl;
		return ret;

	};
	ret = makehash(arrysize);
	string line = "";
	string tempstate = "";
	string tempname = "";
	string temppopstring = "";
	double temppopdouble = 0;
	string tempareastring = "";
	double tempareadouble = 0;
	string templatstring = "";
	double templatdouble = 0;
	string templonstring = "";
	double templondouble = 0;
	string tempintersectstring = "";
	double tempintersectdouble = 0;
	string tempintersectdiststring = "";
	double tempintersectdistdouble = 0;

	getline(file,line);
	getline(file,line);

	while(!file.eof()){
		
	city *tempcity = makecity();
		
		tempname = line.substr(10,40);
		tempname = cutspacesfromend(tempname);
		*(tempcity->name) = tempname;
		//cout << *(tempcity->name) <<endl;

		tempstate = line.substr(8,2);
		*(tempcity->state) = tempstate;
		//cout << *tempcity->state << endl;		
		
		temppopstring = line.substr(50,16);
		temppopdouble = cutspacesfrombeginning(temppopstring);
		*(tempcity->population) = temppopdouble;
		//cout << *(tempcity->population) << endl;

		tempareastring = line.substr(70,10);
		tempareadouble = cutspacesfrombeginningwithdecimalandneg(tempareastring);
		*(tempcity->area) = tempareadouble;
		//cout << *(tempcity->area) << endl;

		templatstring = line.substr(80,10);
		templatdouble = cutspacesfrombeginningwithdecimalandneg(templatstring);
		*(tempcity->lat) = templatdouble;
		//cout<<*(tempcity->lat)<<endl;

		templonstring = line.substr(90,11);
		templondouble = cutspacesfrombeginningwithdecimalandneg(templonstring);
		*(tempcity->lon) = templondouble;
		//cout<<*(tempcity->lon)<<endl;

		tempintersectstring = line.substr(101,5);
		tempintersectdouble = cutspacesfrombeginning(tempintersectstring);
		*(tempcity->intersect) = tempintersectdouble/10;
		//cout<<*(tempcity->intersect)<<endl;

		tempintersectdiststring = line.substr(106,8);
		tempintersectdistdouble = cutspacesfrombeginningwithdecimalandneg(tempintersectdiststring);
		*(tempcity->intersectdist) = tempintersectdistdouble;
		//cout<<*(tempcity->intersectdist)<<endl<<endl;

		addtotable(ret,tempcity);
		
		getline(file,line);
	}
	return ret;

};

void searchlist(hasharray * citylist){

	bool endflag = 0;
	string userentry = "";
	while(true){
		endflag = 0;
		cout << "Please print the name of a city you would like to see the details about. Type ctrl+c to exit." << endl;
		getline(cin,userentry);
		int slotvalue = generatevalue(userentry);
		if(citylist->cityarray[slotvalue] != NULL && endflag != 1){

			citynode *tptr = citylist->cityarray[slotvalue];
			cout << "Please select from the following states which city you would like to see the details of:"<<endl;

			while(tptr != NULL){
			
				cout <<*tptr->data->state<<endl;
				tptr = tptr->next;

			}
			
			tptr = citylist->cityarray[slotvalue];
			cin >> userentry;
			while(tptr != NULL){
				if(*tptr->data->state == userentry){
	
					cout<<*tptr->data->name<<", "<<*tptr->data->state<<":"<<endl;
					cout<<"Population: "<<*tptr->data->population<<endl;
					cout<<"Area: "<<*tptr->data->area<<endl;
					cout<<"Latitude: "<<*tptr->data->lat<<endl;
					cout<<"Longitude: "<<*tptr->data->lon<<endl;
					cout<<"Intersect: "<<*tptr->data->intersect<<endl;
					cout<<"Distance from the nearest intersection: "<<*tptr->data->intersectdist<<endl;
				}
				tptr = tptr->next;
			}	
			break;
		}
		else cout<<"No such city exists"<<endl;	

	}
	return;

};

int main(){

	hasharray *citylist = NULL;
	citylist = readfile("named-places.txt");
	searchlist(citylist);	



}
